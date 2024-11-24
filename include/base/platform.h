#pragma once
#define __QO_BASE_PLATFORM_H__

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define QO_POSIX_ACTIVE 0
#define QO_WINDOWS_ACTIVE 0
#define QO_LINUX_ACTIVE 0
#define QO_MACOS_ACTIVE 0

#if defined(__linux__)
#   undef QO_POSIX_ACTIVE 
#   define QO_POSIX_ACTIVE 1
#   undef QO_LINUX_ACTIVE
#   define QO_LINUX_ACTIVE 1
#endif // __linux__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN16)
#   undef QO_WINDOWS_ACTIVE
#   define QO_WINDOWS_ACTIVE 1
#endif // windows

#if defined(__APPLE__) 
#   undef QO_MACOS_ACTIVE
#   define QO_MACOS_ACTIVE 1
#   undef QO_POSIX_ACTIVE
#   define QO_POSIX_ACTIVE 1
#endif

#define QO_PLATFORM(p) (QO_##p##_ACTIVE)
#if !(QO_PLATFORM(POSIX) || QO_PLATFORM(WINDOWS) || QO_PLATFORM(LINUX) || \
    QO_PLATFORM(MACOS))
#   error "Unknown platform"
#endif 

#define QO_32BIT_ACTIVE 0
#define QO_64BIT_ACTIVE 0

#if QO_PLATFORM(WINDOWS)
#   if defined(_WIN64)
#       undef QO_64BIT_ACTIVE
#       define QO_64BIT_ACTIVE 1
#   elif defined(_WIN32)
#       undef QO_32BIT_ACTIVE
#       define QO_32BIT_ACTIVE 1
#   else
#       error "Unknown Windows platform"
#   endif // _WIN64 or _WIN32
#elif QO_PLATFORM(LINUX) || QO_PLATFORM(MACOS)
#   if defined(__x86_64__) || defined(__ppc64__) || defined(__LP64__) || \
       defined(__amd64) || defined(__alpha__) || defined(__aarch64__) || \
       defined(__ia64__) 
#       undef QO_64BIT_ACTIVE
#       define QO_64BIT_ACTIVE 1
#   elif defined(__i386__) || defined(__ppc__) || defined(__LP32__) || \
         defined(__x86_32__) || defined(__amd32) || defined(__m68k__)
#       undef QO_32BIT_ACTIVE
#       define QO_32BIT_ACTIVE 1
#   else
#       error "Unknown Linux platform"
#   endif // 64bit or 32bit
#endif // LINUX

#define QO_SYSTEM_BIT(x) (QO_##x##BIT_ACTIVE)
#if !(QO_SYSTEM_BIT(32) || QO_SYSTEM_BIT(64))
#   error "QOLib rary only support 32bit or 64bit system"
#endif // 

#define QO_BIG_ENDIAN_ACTIVE 0
#define QO_LITTLE_ENDIAN_ACTIVE 0

#if defined(__BYTE_ORDER__)
#   if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       undef QO_BIG_ENDIAN_ACTIVE
#       define QO_BIG_ENDIAN_ACTIVE 1
#   elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       undef QO_LITTLE_ENDIAN_ACTIVE
#       define QO_LITTLE_ENDIAN_ACTIVE 1
#   else
#       error "Unknown byte order"
#   endif 
#elif QO_PLATFORM(WINDOWS) // All devices running Windows are little endian
#   undef QO_LITTLE_ENDIAN_ACTIVE
#   define QO_LITTLE_ENDIAN_ACTIVE 1
#elif QO_PLATFORM(LINUX) || QO_PLATFORM(MACOS)
#    include <endian.h>
#    if (__BYTE_ORDER == __LITTLE_ENDIAN)
#       undef QO_LITTLE_ENDIAN_ACTIVE
#       define QO_LITTLE_ENDIAN_ACTIVE 1
#    elif (__BYTE_ORDER == __BIG_ENDIAN)
#       undef QO_BIG_ENDIAN_ACTIVE
#       define QO_BIG_ENDIAN_ACTIVE 1
#    else
#       error "Unknown byte order"
#    endif
#elif defined(__hppa__) || defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
      (defined(__MIPS__) && defined(__MIPSEB__)) || defined(__ppc__) || defined(__POWERPC__) ||\
      defined(__powerpc__) || defined(__PPC__) || defined(__sparc__)
#   undef QO_BIG_ENDIAN_ACTIVE
#   define QO_BIG_ENDIAN_ACTIVE 1
#endif // __BYTE_ORDER__

#define QO_ENDIAN(e) (QO_##e##_ENDIAN_ACTIVE)

#define QO_x86_ACTIVE 0
#define QO_ARM_ACTIVE 0

#if defined(__i386__) || defined(__x86_32__) || defined(__amd32) || \
    defined(__INTEL__) || defined(_M_IX86) || defined(_M_X64) || \
    defined(_X86_) || defined(_M_IA64) || defined(_M_AMD64)
#   undef QO_x86_ACTIVE
#   define QO_x86_ACTIVE 1
#elif defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || \
      defined(__TARGET_ARCH_THUMB) || defined(_ARM_) || defined(_M_ARM) || \
      defined(_M_ARMT) || defined(__aarch64__) || defined(_M_ARM64)
#   undef QO_ARM_ACTIVE
#   define QO_ARM_ACTIVE 1
#endif

#define QO_ARCH(a) (QO_##a##_ACTIVE)

#if defined(__cplusplus)
}
#endif // __cplusplus