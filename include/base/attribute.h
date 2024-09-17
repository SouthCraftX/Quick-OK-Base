#pragma once

#   define XOC_SUGGESTED_INLINE  inline
//#   define XOC_INTERNAL

#if defined(__GNUC__)
#   define XOC_THREAD_LOCAL  __thread
#   define XOC_DEPRICATED    __attribute__((deprecated))
#   define XOC_NODISCARD     __attribute__((warn_unused_result))
#   define XOC_FORCE_INLINE  __attribute__((always_inline))
#   define XOC_FLATTEN       __attribute__((flatten))
#   define XOC_NO_INLINE     __attribute__((noinline))
#   define XOC_NONNULL(...)   __attribute__((nonnull(__VA_ARGS__)))
#   define XOC_LIKELY(x)     __builtin_expect(!!(x), 1)
#   define XOC_UNLIKELY(x)   __builtin_expect(!!(x), 0)
#   define XOC_UNREACHABLE() __builtin_unreachable()
#   define XOC_RESTRICT      __restrict
#   define XOC_NORETURN      __attribute__((noreturn))
#   define XOC_FALLTHROUGH   __attribute__((fallthrough))
#   define XOC_ALIGNAS(x)    __attribute__((aligned(x)))
#   define XOC_PACKED        __attribute__((packed))
#   define XOC_EXPORT        __attribute__((visibility("default")))
#   define XOC_IMPORT        __attribute__((visibility("default")))
#   define XOC_NOEXPORT      __attribute__((visibility("hidden"))) // wtf why gcc/linux always export all symbols on linux by default?!
#   define XOC_PRIVATE_FUNC  __attribute__((visibility("internal")))
#   define XOC_PURE          __attribute__((pure))
#   define XOC_USED          __attribute__((used))
#   define XOC_ABORT()       __builtin_trap()
#   define XOC_STACK_ALLOC(n) __builtin_alloca(n)
#   define XOC_ERRPRINTF(f,...) __buildin_printf(__VA_ARGS__)
#elif defined(_MSC_VER)
#   info "Warning:Missing feature for XOC_LIKELY and XOCEAB_UNLIKELY"
#   define XOC_DEPRICATED    __declspec(deprecated)
#   define XOC_THREAD_LOCAL  __declspec(thread)
#   define XOC_NODISCARD     __nodiscard
#   define XOC_FORCE_INLINE  __forceinline
#   define XOC_NONNULL(...)       
#   define XOC_FLATTEN       __declspec(flatten)
#   define XOC_NO_INLINE     __declspec(noinline)
#   define XOC_LIKELY(x)     (x)
#   define XOC_UNLIKELY(x)   (x)
#   define XOC_UNREACHABLE() __assume(0)
#   define XOC_RESTRICT      __restrict
#   define XOC_NORETURN      __declspec(noreturn)
#   define XOC_FALLTHROUGH   __fallthrough
#   define XOC_ALIGNAS(x)    __declspec(align(x))
#   define XOC_PACKED        __pragma(pack(push, 1)) __declspec(align(1))
#   define XOC_EXPORT        __declspec(dllexport)
#   define XOC_IMPORT        __declspec(dllimport)
#   define XOC_PURE
#   define XOC_CONSTRUCTOR          
#   define XOC_USED
#   define XOC_NOEXPORT
#   define XOC_STACK_ALLOC(n) _alloca(n)
#   define XOC_ABORT() __debugbreak()
#   define XOC_ERRPRINT(f,...) printf(f,__VA_ARGS__)
#else
#   info "Warning:Your compiler is not recommanded, which means you may encounter some problems."
#   info "Missing feature for `likely`, `unlikely`, `noinline`, `export` and `import`"
#   info "`inline`and `fallthrough` may not work as expected."
#   define XOC_THREAD_LOCAL _Thread_local
#   define XOC_FORCE_INLINE XOC_SUGGESTED_INLINE
#   define XOC_DEPRECATED [[deprecated]]
#   define XOC_NO_INLINE
#   define XOC_LIKELY(x) (x)
#   define XOC_UNLIKELY(x) (x)
#   define XOC_UNREACHABLE() unreachable()
#   define XOC_RESTRICT restrict
#   define XOC_NORETURN _Noreturn
#   define XOC_NODISCARD [[nodiscard]]
#   define XOC_FALLTHROUGH [[fallthrough]]
#   define XOC_ALIGNAS(x) alignas(x)
#   define XOC_NONNULL(...) 
#   define XOC_EXPORT
#   define XOC_NOEXPORT
#   define XOC_IMPORT
#   define XOC_PURE
#   define XOC_STACK_ALLOC(n) xoc_alloc(n)
#   define XOC_ABORT() abort()
#endif

#if defined(XOC_WANT_STATIC_LIBRARY)
#   define XOC_API
#else
#   define XOC_API XOC_EXPORT
#endif // defined(XOC_WANT_STATIC_LIBRARY)

#if defined(__cplusplus)
#   define XOC_DECLFUNC  extern "C"
#else
#   define XOC_DECLFUNC
#endif

#define XOC_IMPL(f) _##f
#define XOC_DBG(f) _##f##_dbg

#if defined(XOC_DEBUG)
#   define XOC_INTERFACE(f) XOC_DBG(f)
#else
#   define XOC_INTERFACE(f) XOC_IMPL(f)
#endif 

#define XOC_GLOBAL_LOCAL static

