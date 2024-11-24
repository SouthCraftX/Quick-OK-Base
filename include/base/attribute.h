#pragma once

#   define QO_SUGGESTED_INLINE  inline
//#   define QO_INTERNAL

#if defined(__GNUC__)
#   define QO_THREAD_LOCAL  __thread
#   define QO_DEPRICATED    __attribute__((deprecated))
#   define QO_NODISCARD     __attribute__((warn_unused_result))
#   define QO_FORCE_INLINE  __attribute__((always_inline))
#   define QO_FLATTEN       __attribute__((flatten))
#   define QO_NO_INLINE     __attribute__((noinline))
#   define QO_NONNULL(...)   __attribute__((nonnull(__VA_ARGS__)))
#   define QO_LIKELY(x)     __builtin_expect(!!(x), 1)
#   define QO_UNLIKELY(x)   __builtin_expect(!!(x), 0)
#   define QO_UNREACHABLE() __builtin_unreachable()
#   define QO_RESTRICT      __restrict
#   define QO_NORETURN      __attribute__((noreturn))
#   define QO_FALLTHROUGH   __attribute__((fallthrough))
#   define QO_ALIGNAS(x)    __attribute__((aligned(x)))
#   define QO_PACKED        __attribute__((packed))
#   define QO_EXPORT        __attribute__((visibility("default")))
#   define QO_IMPORT        __attribute__((visibility("default")))
#   define QO_NOEXPORT      __attribute__((visibility("hidden"))) // wtf why gcc/linux always export all symbols on linux by default?!
#   define QO_PRIVATE_FUNC  __attribute__((visibility("internal")))
#   define QO_PURE          __attribute__((pure))
#   define QO_NO_SIDE_EFFECTS  __attribute__((const))
#   define QO_USED          __attribute__((used))
#   define QO_ABORT()       __builtin_trap()
#   define QO_STACK_ALLOC(n) __builtin_alloca(n)
#   define QO_ERRPRINTF(f,...) __buildin_printf(__VA_ARGS__)
#elif defined(_MSC_VER)
#   info "Warning:Missing feature for QO_LIKELY and QOEAB_UNLIKELY"
#   define QO_DEPRICATED    __declspec(deprecated)
#   define QO_THREAD_LOCAL  __declspec(thread)
#   define QO_NODISCARD     __nodiscard
#   define QO_FORCE_INLINE  __forceinline
#   define QO_NONNULL(...)       
#   define QO_FLATTEN       __declspec(flatten)
#   define QO_NO_INLINE     __declspec(noinline)
#   define QO_LIKELY(x)     (x)
#   define QO_UNLIKELY(x)   (x)
#   define QO_UNREACHABLE() __assume(0)
#   define QO_RESTRICT      __restrict
#   define QO_NORETURN      __declspec(noreturn)
#   define QO_FALLTHROUGH   __fallthrough
#   define QO_ALIGNAS(x)    __declspec(align(x))
#   define QO_PACKED        __pragma(pack(push, 1)) __declspec(align(1))
#   define QO_EXPORT        __declspec(dllexport)
#   define QO_IMPORT        __declspec(dllimport)
#   define QO_PURE
#   define QO_CONSTRUCTOR          
#   define QO_USED
#   define QO_NOEXPORT
#   define QO_STACK_ALLOC(n) _alloca(n)
#   define QO_ABORT() __debugbreak()
#   define QO_ERRPRINT(f,...) printf(f,__VA_ARGS__)
#else
#   info "Warning:Your compiler is not recommanded, which means you may encounter some problems."
#   info "Missing feature for `likely`, `unlikely`, `noinline`, `export` and `import`"
#   info "`inline`and `fallthrough` may not work as expected."
#   define QO_THREAD_LOCAL _Thread_local
#   define QO_FORCE_INLINE QO_SUGGESTED_INLINE
#   define QO_DEPRECATED [[deprecated]]
#   define QO_NO_INLINE
#   define QO_LIKELY(x) (x)
#   define QO_UNLIKELY(x) (x)
#   define QO_UNREACHABLE() unreachable()
#   define QO_RESTRICT restrict
#   define QO_NORETURN _Noreturn
#   define QO_NODISCARD [[nodiscard]]
#   define QO_FALLTHROUGH [[fallthrough]]
#   define QO_ALIGNAS(x) alignas(x)
#   define QO_NONNULL(...) 
#   define QO_EXPORT
#   define QO_NOEXPORT
#   define QO_IMPORT
#   define QO_PURE
#   define QO_STACK_ALLOC(n) qo_alloc(n)
#   define QO_ABORT() abort()
#endif

#if defined(QO_WANT_STATIC_LIBRARY)
#   define QO_API
#else
#   define QO_API QO_EXPORT
#endif // defined(QO_WANT_STATIC_LIBRARY)

#if defined(__cplusplus)
#   define QO_DECLFUNC  extern "C"
#else
#   define QO_DECLFUNC
#endif

#define QO_IMPL(f) _##f
#define QO_DBG(f) _##f##_dbg

#if defined(QO_DEBUG)
#   define QO_INTERFACE(f) QO_DBG(f)
#else
#   define QO_INTERFACE(f) QO_IMPL(f)
#endif 

#define QO_GLOBAL_LOCAL static

