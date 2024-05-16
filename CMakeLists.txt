cmake_minimum_required(VERSION 3.12...3.27.4)

project(triangle)

include(CheckCCompilerFlag)

FILE(GLOB TRIANGLE_SOURCE_FILES src/*.c)

function(add_c_compiler_flag_if_supported FLAG)
    string(REGEX REPLACE "[^A-Za-z0-9]" "_" CONFIG_VARIABLE "FLAG_SUPPORTED${FLAG}")
    check_c_compiler_flag("${FLAG}" ${CONFIG_VARIABLE})
    if(${CONFIG_VARIABLE})
        add_definitions(${FLAG})
    endif()
endfunction()

function(add_c_compiler_flag_required FLAG)
    string(REGEX REPLACE "[^A-Za-z0-9]" "_" CONFIG_VARIABLE "FLAG_SUPPORTED${FLAG}")
    check_c_compiler_flag("${FLAG}" ${CONFIG_VARIABLE})
    if(${CONFIG_VARIABLE})
        add_definitions(${FLAG})
    else()
        message(SEND_ERROR "Your compiler does not support ${FLAG}")
    endif()
endfunction()

set(ALL_SOURCES
    ${TRIANGLE_SOURCE_FILES}
)

add_executable(triangle ${ALL_SOURCES})
add_library(trianglelib ${ALL_SOURCES})

add_c_compiler_flag_if_supported(-std=c99)
add_c_compiler_flag_if_supported(-O3)
add_c_compiler_flag_if_supported(-Wall)
add_c_compiler_flag_if_supported(-Wno-format-truncation)

include_directories(src)


set(LINK_LIBS_PLATFORM "")

if(APPLE)
    set(LINK_LIBS_PLATFORM "")
endif()

if(UNIX AND NOT APPLE)
    set(LINK_LIBS_PLATFORM dl m)
endif()

if(WIN32)
    set(LINK_LIBS_PLATFORM "ws2_32.lib")
endif()

add_definitions(-DGLEW_STATIC)
add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)
add_subdirectory(deps/glew EXCLUDE_FROM_ALL)

set(TRIANGLE_DEPS
    ${GLFW_LIBRARIES}
    ${CURL_LIBRARIES}
    ${LINK_LIBS_PLATFORM}
)

target_link_libraries(triangle
    PRIVATE glfw
    PRIVATE libglew_static
    ${TRIANGLE_DEPS}
)
target_link_libraries(trianglelib
    PRIVATE glfw
    PRIVATE libglew_static
    ${TRIANGLE_DEPS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)

