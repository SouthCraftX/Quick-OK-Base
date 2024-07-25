#pragma once
#define __XOC_BASE_PLATFORM_H__

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define XOC_POSIX_ACTIVE 0
#define XOC_WINDOWS_ACTIVE 0
#define XOC_LINUX_ACTIVE 0
#define XOC_MACOS_ACTIVE 0

#if defined(__linux__)
#   undef XOC_POSIX_ACTIVE 
#   define XOC_POSIX_ACTIVE 1
#   undef XOC_LINUX_ACTIVE
#   define XOC_LINUX_ACTIVE 1
#endif // __linux__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN16)
#   undef XOC_WINDOWS_ACTIVE
#   define XOC_WINDOWS_ACTIVE 1
#endif // windows

#if defined(__APPLE__) 
#   undef XOC_MACOS_ACTIVE
#   define XOC_MACOS_ACTIVE 1
#   undef XOC_POSIX_ACTIVE
#   define XOC_POSIX_ACTIVE 1
#endif

#define XOC_PLATFORM(p) (XOC_##p##_ACTIVE)
#if !(XOC_PLATFORM(POSIX) || XOC_PLATFORM(WINDOWS) || XOC_PLATFORM(LINUX) || \
    XOC_PLATFORM(MACOS))
#   error "Unknown platform"
#endif 

#define XOC_32BIT_ACTIVE 0
#define XOC_64BIT_ACTIVE 0

#if XOC_PLATFORM(WINDOWS)
#   if defined(_WIN64)
#       undef XOC_64BIT_ACTIVE
#       define XOC_64BIT_ACTIVE 1
#   elif defined(_WIN32)
#       undef XOC_32BIT_ACTIVE
#       define XOC_32BIT_ACTIVE 1
#   else
#       error "Unknown Windows platform"
#   endif // _WIN64 or _WIN32
#elif XOC_PLATFORM(LINUX) || XOC_PLATFORM(MACOS)
#   if defined(__x86_64__) || defined(__ppc64__) || defined(__LP64__) || \
       defined(__amd64) || defined(__alpha__) || defined(__aarch64__) || \
       defined(__ia64__) 
#       undef XOC_64BIT_ACTIVE
#       define XOC_64BIT_ACTIVE 1
#   elif defined(__i386__) || defined(__ppc__) || defined(__LP32__) || \
         defined(__x86_32__) || defined(__amd32) || defined(__m68k__)
#       undef XOC_32BIT_ACTIVE
#       define XOC_32BIT_ACTIVE 1
#   else
#       error "Unknown Linux platform"
#   endif // 64bit or 32bit
#endif // LINUX

#define XOC_SYSTEM_BIT(x) (XOC_##x##BIT_ACTIVE)
#if !(XOC_SYSTEM_BIT(32) || XOC_SYSTEM_BIT(64))
#   error "XOCLib rary only support 32bit or 64bit system"
#endif // 

#define XOC_BIG_ENDIAN_ACTIVE 0
#define XOC_LITTLE_ENDIAN_ACTIVE 0

#if defined(__BYTE_ORDER__)
#   if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       undef XOC_BIG_ENDIAN_ACTIVE
#       define XOC_BIG_ENDIAN_ACTIVE 1
#   elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       undef XOC_LITTLE_ENDIAN_ACTIVE
#       define XOC_LITTLE_ENDIAN_ACTIVE 1
#   else
#       error "Unknown byte order"
#   endif 
#elif XOC_PLATFORM(WINDOWS) // All devices running Windows are little endian
#   undef XOC_LITTLE_ENDIAN_ACTIVE
#   define XOC_LITTLE_ENDIAN_ACTIVE 1
#elif XOC_PLATFORM(LINUX) || XOC_PLATFORM(MACOS)
#    include <endian.h>
#    if (__BYTE_ORDER == __LITTLE_ENDIAN)
#       undef XOC_LITTLE_ENDIAN_ACTIVE
#       define XOC_LITTLE_ENDIAN_ACTIVE 1
#    elif (__BYTE_ORDER == __BIG_ENDIAN)
#       undef XOC_BIG_ENDIAN_ACTIVE
#       define XOC_BIG_ENDIAN_ACTIVE 1
#    else
#       error "Unknown byte order"
#    endif
#elif defined(__hppa__) || defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
      (defined(__MIPS__) && defined(__MIPSEB__)) || defined(__ppc__) || defined(__POWERPC__) ||\
      defined(__powerpc__) || defined(__PPC__) || defined(__sparc__)
#   undef XOC_BIG_ENDIAN_ACTIVE
#   define XOC_BIG_ENDIAN_ACTIVE 1
#endif // __BYTE_ORDER__

#define XOC_ENDIAN(e) (XOC_##e##_ENDIAN_ACTIVE)

#define XOC_x86_ACTIVE 0
#define XOC_ARM_ACTIVE 0

#if defined(__i386__) || defined(__x86_32__) || defined(__amd32) || \
    defined(__INTEL__) || defined(_M_IX86) || defined(_M_X64) || \
    defined(_X86_) || defined(_M_IA64) || defined(_M_AMD64)
#   undef XOC_x86_ACTIVE
#   define XOC_x86_ACTIVE 1
#elif defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || \
      defined(__TARGET_ARCH_THUMB) || defined(_ARM_) || defined(_M_ARM) || \
      defined(_M_ARMT) || defined(__aarch64__) || defined(_M_ARM64)
#   undef XOC_ARM_ACTIVE
#   define XOC_ARM_ACTIVE 1
#endif

#define XOC_ARCH(a) (XOC_##a##_ACTIVE)

#if defined(__cplusplus)
}
#endif // __cplusplus