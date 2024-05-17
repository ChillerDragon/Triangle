#ifndef SRC_DETECT_H
#define SRC_DETECT_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define OS_WINDOWS
#endif

#ifdef __APPLE__
#define OS_APPLE
#endif

#ifdef __linux__
#define OS_LINUX
#endif

#endif
