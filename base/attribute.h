#pragma once

#   define XOCEAN_SUGGESTED_INLINE  inline
//#   define XOCEAN_INTERNAL

#if defined(__GNUC__)
#   define XOCEAN_THREAD_LOCAL  __thread
#   define XOCEAN_DEPRICATED    __attribute__((deprecated))
#   define XOCEAN_NODISCARD     __attribute__((warn_unused_result))
#   define XOCEAN_FORCE_INLINE  __attribute__((always_inline))
#   define XOCEAN_FLATTEN       __attribute__((flatten))
#   define XOCEAN_NO_INLINE     __attribute__((noinline))
#   define XOCEAN_LIKELY(x)     __builtin_expect(!!(x), 1)
#   define XOCEAN_UNLIKELY(x)   __builtin_expect(!!(x), 0)
#   define XOCEAN_UNREACHABLE() __builtin_unreachable()
#   define XOCEAN_RESTRICT      __restrict
#   define XOCEAN_NORETURN      __attribute__((noreturn))
#   define XOCEAN_FALLTHROUGH   __attribute__((fallthrough))
#   define XOCEAN_ALIGNAS(x)    __attribute__((aligned(x)))
#   define XOCEAN_PACKED        __attribute__((packed))
#   define XOCEAN_EXPORT        __attribute__((visibility("default")))
#   define XOCEAN_IMPORT        __attribute__((visibility("default")))
#   define XOCEAN_NOEXPORT      __attribute__((visibility("hidden"))) // wtf why gcc/linux always export all symbols on linux by default?!
#   define XOCEAN_PRIVATE_FUNC  __attribute__((visibility("internel")))
#   define XOCEAN_PURE          __attribute__((pure))
#   define XOCEAN_USED          __attribute__((used))
#   define XOCEAN_ABORT()       __builtin_trap()
#   define XOCEAN_ERRPRINTF(f,...) __buildin_printf(__VA_ARGS__)
#elif defined(_MSC_VER)
#   info "Warning:Missing feature for XOCEAN_LIKELY and XOCEAB_UNLIKELY"
#   define XOCEAN_DEPRICATED    __declspec(deprecated)
#   define XOCEAN_THREAD_LOCAL  __declspec(thread)
#   define XOCEAN_NODISCARD     __nodiscard
#   define XOCEAN_FORCE_INLINE  __forceinline
#   define XOCEAN_FLATTEN       __declspec(flatten)
#   define XOCEAN_NO_INLINE     __declspec(noinline)
#   define XOCEAN_LIKELY(x)     (x)
#   define XOCEAN_UNLIKELY(x)   (x)
#   define XOCEAN_UNREACHABLE() __assume(0)
#   define XOCEAN_RESTRICT      __restrict
#   define XOCEAN_NORETURN      __declspec(noreturn)
#   define XOCEAN_FALLTHROUGH   __fallthrough
#   define XOCEAN_ALIGNAS(x)    __declspec(align(x))
#   define XOCEAN_PACKED        __pragma(pack(push, 1)) __declspec(align(1))
#   define XOCEAN_EXPORT        __declspec(dllexport)
#   define XOCEAN_IMPORT        __declspec(dllimport)
#   define XOCEAN_PURE
#   define XOCEAN_CONSTRUCTOR          
#   define XOCEAN_USED
#   define XOCEAN_NOEXPORT

#   define XOCEAN_ABORT() __debugbreak()
#   define XOCEAN_ERRPRINT(f,...) printf(f,__VA_ARGS__)
#else
#   info "Warning:Your compiler is not recommanded, which means you may encounter some problems."
#   info "Missing feature for `likely`, `unlikely`, `noinline`, `export` and `import`"
#   info "`inline`and `fallthrough` may not work as expected."
#   define XOCEAN_THREAD_LOCAL _Thread_local
#   define XOCEAN_FORCE_INLINE XOCEAN_SUGGESTED_INLINE
#   define XOCEAN_DEPRECATED [[deprecated]]
#   define XOCEAN_NO_INLINE
#   define XOCEAN_LIKELY(x) (x)
#   define XOCEAN_UNLIKELY(x) (x)
#   define XOCEAN_UNREACHABLE() unreachable()
#   define XOCEAN_RESTRICT restrict
#   define XOCEAN_NORETURN _Noreturn
#   define XOCEAN_NODISCARD [[nodiscard]]
#   define XOCEAN_FALLTHROUGH [[fallthrough]]
#   define XOCEAN_ALIGNAS(x) alignas(x)
#   define XOCEAN_EXPORT
#   define XOCEAN_NOEXPORT
#   define XOCEAN_IMPORT
#   define XOCEAN_ABORT() abort()
#endif

#if defined(XOCEAN_WANT_STATIC_LIBRARY)
#   define XOCEAN_API
#else
#   define XOCEAN_API XOCEAN_EXPORT
#endif // defined(XOCEAN_WANT_STATIC_LIBRARY)

#if defined(__cplusplus)
#   define XOCEAN_DECLFUNC  extern "C"
#else
#   define XOCEAN_DECLFUNC
#endif

#define XOCEAN_IMPL(f) _##f
#define XOCEAN_DBG(f) _##f##_dbg

#if defined(XOCEAN_DEBUG)
#   define XOCEAN_INTERFACE(f) XOCEAN_DBG(f)
#else
#   define XOCEAN_INTERFACE(f) XOCEAN_IMPL(f)
#endif 

#define XOCEAN_GLOBAL_LOCAL static

#define XOCEAN_BUG(m) assert(m)
