#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#   define XOCEAN_INTERNAL

#if defined(__GNUC__)
#   define XOCEAN_FORCE_INLINE __attribute__((always_inline))
#   define XOCEAN_NO_INLINE __attribute__((noinline))
#   define XOCEAN_LIKELY(x) __builtin_expect(!!(x), 1)
#   define XOCEAN_UNLIKELY(x) __builtin_expect(!!(x), 0)
#   define XOCEAN_UNREACHABLE() __builtin_unreachable()
#   define XOCEAN_RESTRICT __restrict
#   define XOCEAN_NORETURN __attribute__((noreturn))
#   define XOCEAN_FALLTHROUGH __attribute__((fallthrough))
#   define XOCEAN_ALIGNED(x) __attribute__((aligned(x)))
#   define XOCEAN_PACKED __attribute__((packed))
#   define XOCEAN_EXPORT __attribute__((visibility("default")))
#   define XOCEAN_IMPORT __attribute__((visibility("default")))
#elif defined(_MSC_VER)
#   info "Warning:Missing feature for `likely` and `unlikely`"
#   define XOCEAN_FORCE_INLINE __forceinline
#   define XOCEAN_NO_INLINE __declspec(noinline)
#   define XOCEAN_LIKELY(x) (x)
#   define XOCEAN_UNLIKELY(x) (x)
#   define XOCEAN_UNREACHABLE() __assume(0)
#   define XOCEAN_RESTRICT __restrict
#   define XOCEAN_NORETURN __declspec(noreturn)
#   define XOCEAN_FALLTHROUGH __fallthrough
#   define XOCEAN_ALIGNED(x) __declspec(align(x))
#   define XOCEAN_PACKED __pragma(pack(push, 1)) __declspec(align(1))
#   define XOCEAN_EXPORT __declspec(dllexport)
#   define XOCEAN_IMPORT __declspec(dllimport)
#else
#   info "Warning:Your compiler is not recommanded, which means you may encounter some problems."
#   info "Missing feature for `likely`, `unlikely`, `noinline`, `export` and `import`"
#   info "`inline`and `fallthrough` may not work as expected."
#   define XOCEAN_FORCE_INLINE inline
#   define XOCEAN_NO_INLINE
#   define XOCEAN_LIKELY(x) (x)
#   define XOCEAN_UNLIKELY(x) (x)
#   define XOCEAN_UNREACHABLE() unreachable()
#   define XOCEAN_RESTRICT restrict
#   define XOCEAN_NORETURN _Noreturn
#   define XOCEAN_FALLTHROUGH [[fallthrough]]
#   define XOCEAN_ALIGNED(x) alignas(x)
#   define XOCEAN_EXPORT
#   define XOCEAN_IMPORT
#endif

#define XOCEAN_BUG(m) assert(m)

#if defined(__cplusplus)
}
#endif // __cplusplus