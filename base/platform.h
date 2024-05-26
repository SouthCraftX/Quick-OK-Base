#pragma once

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define XOCEAN_POSIX_ACTIVE 0
#define XOCEAN_WINDOWS_ACTIVE 0
#define XOCEAN_LINUX_ACTIVE 0
#define XOCEAN_MACOS_ACTIVE 0

#if defined(__linux__)
#   undef XOCEAN_POSIX_ACTIVE 
#   define XOCEAN_POSIX_ACTIVE 1
#   undef XOCEAN_LINUX_ACTIVE
#   define XOCEAN_LINUX_ACTIVE 1
#endif // __linux__

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN16)
#   undef XOCEAN_WINDOWS_ACTIVE
#   define XOCEAN_WINDOWS_ACTIVE 1
#endif // windows

#if defined(__APPLE__) 
#   undef XOCEAN_MACOS_ACTIVE
#   define XOCEAN_MACOS_ACTIVE 1
#   undef XOCEAN_POSIX_ACTIVE
#   define XOCEAN_POSIX_ACTIVE 1
#endif

#define XOCEAN_PLATFORM(p) (XOCEAN_##p##_ACTIVE)
#if !(XOCEAN_PLATFORM(POSIX) || XOCEAN_PLATFORM(WINDOWS) || XOCEAN_PLATFORM(LINUX) || \
    XOCEAN_PLATFORM(MACOS))
#   error "Unknown platform"
#endif 

#define XOCEAN_32BIT_ACTIVE 0
#define XOCEAN_64BIT_ACTIVE 0

#if XOCEAN_PLATFORM(WINDOWS)
#   if defined(_WIN64)
#       undef XOCEAN_64BIT_ACTIVE
#       define XOCEAN_64BIT_ACTIVE 1
#   elif defined(_WIN32)
#       undef XOCEAN_32BIT_ACTIVE
#       define XOCEAN_32BIT_ACTIVE 1
#   else
#       error "Unknown Windows platform"
#   endif // _WIN64 or _WIN32
#elif XOCEAN_PLATFORM(LINUX) || XOCEAN_PLATFORM(MACOS)
#   if defined(__x86_64__) || defined(__ppc64__) || defined(__LP64__) || \
       defined(__amd64) || defined(__alpha__) || defined(__aarch64__) || \
       defined(__ia64__) 
#       undef XOCEAN_64BIT_ACTIVE
#       define XOCEAN_64BIT_ACTIVE 1
#   elif defined(__i386__) || defined(__ppc__) || defined(__LP32__) || \ 
         defined(__x86_32__) || defined(__amd32) || defined(__m68k__)
#       undef XOCEAN_32BIT_ACTIVE
#       define XOCEAN_32BIT_ACTIVE 1
#   else
#       error "Unknown Linux platform"
#   endif // 64bit or 32bit
#endif // LINUX

#define XOCEAN_SYSTEM_BIT(x) (XOCEAN_##x##BIT_ACTIVE)
#if !(XOCEAN_SYSTEM_BIT(32) || XOCEAN_SYSTEM_BIT(64))
#   error "XOceanLib rary only support 32bit or 64bit system"
#endif // 

#define XOCEAN_BIG_ENDIAN_ACTIVE 0
#define XOCEAN_LITTLE_ENDIAN_ACTIVE 0

#if defined(__BYTE_ORDER__)
#   if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       undef XOCEAN_BIG_ENDIAN_ACTIVE
#       define XOCEAN_BIG_ENDIAN_ACTIVE 1
#   elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       undef XOCEAN_LITTLE_ENDIAN_ACTIVE
#       define XOCEAN_LITTLE_ENDIAN_ACTIVE 1
#   else
#       error "Unknown byte order"
#   endif 
#elif XOCEAN_PLATFORM(WINDOWS) // All devices running Windows are little endian
#   undef XOCEAN_LITTLE_ENDIAN_ACTIVE
#   define XOCEAN_LITTLE_ENDIAN_ACTIVE 1
#elif XOCEAN_PLATFORM(LINUX) || XOCEAN_PLATFORM(MACOS)
#    include <endian.h>
#    if (__BYTE_ORDER == __LITTLE_ENDIAN)
#       undef XOCEAN_LITTLE_ENDIAN_ACTIVE
#       define XOCEAN_LITTLE_ENDIAN_ACTIVE 1
#    elif (__BYTE_ORDER == __BIG_ENDIAN)
#       undef XOCEAN_BIG_ENDIAN_ACTIVE
#       define XOCEAN_BIG_ENDIAN_ACTIVE 1
#    else
#       error "Unknown byte order"
#    endif
#elif defined(__hppa__) || defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
      (defined(__MIPS__) && defined(__MIPSEB__)) || defined(__ppc__) || defined(__POWERPC__) ||\
      defined(__powerpc__) || defined(__PPC__) || defined(__sparc__)
#   undef XOCEAN_BIG_ENDIAN_ACTIVE
#   define XOCEAN_BIG_ENDIAN_ACTIVE 1
#endif // __BYTE_ORDER__

#define XOCEAN_ENDIAN(e) (XOCEAN_##e##_ENDIAN_ACTIVE)

#define XOCEAN_x86_ACTIVE 0
#define XOCEAN_ARM_ACTIVE 0

#if defined(__i386__) || defined(__x86_32__) || defined(__amd32) || \ 
    defined(__INTEL__) || defined(_M_IX86) || defined(_M_X64) || \
    defined(_X86_) || defined(_M_IA64) || defined(_M_AMD64)
#   undef XOCEAN_x86_ACTIVE
#   define XOCEAN_x86_ACTIVE 1
#elif defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || \
      defined(__TARGET_ARCH_THUMB) || defined(_ARM_) || defined(_M_ARM) || \ 
      defined(_M_ARMT) || defined(__aarch64__) || defined(_M_ARM64)
#   undef XOCEAN_ARM_ACTIVE
#   define XOCEAN_ARM_ACTIVE 1
#endif

#define XOCEAN_ARCH(a) (XOCEAN_##a##_ACTIVE)

#if defined(__cplusplus)
}
#endif // __cplusplus