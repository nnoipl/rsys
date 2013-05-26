#ifndef RSYS_H
#define RSYS_H

#ifndef __GNUC__
  #error "Unsupported compiler"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
 * Platform
 ******************************************************************************/
#if defined(__unix__) || defined(__unix) || defined(unix)
  #define PLATFORM_UNIX
#else
  #error "Unsupported platform"
#endif

/*******************************************************************************
 * Symbol visibility
 ******************************************************************************/
#define EXPORT_SYM __attribute__((visibility("default")))
#define IMPORT_SYM
#define LOCAL_SYM __attribute__((visibility("hidden")))

#if defined(RSYS_SHARED_BUILD)
  #define RSYS_API extern EXPORT_SYM
#else
  #define RSYS_API extern IMPORT_SYM
#endif

/*******************************************************************************
 * Data alignment
 ******************************************************************************/
#define ALIGN(sz) __attribute__((aligned(sz)))
#define ALIGNOF(type) __alignof__(type)
#define ALIGN_SIZE(sz, algnt) (((sz) + ((algnt) - 1)) & ~((algnt) - 1))
#define IS_ALIGNED(addr, algnt) (((uintptr_t)(addr) & ((algnt)-1)) == 0)

/*******************************************************************************
 * Code checking
 ******************************************************************************/
#ifdef NDEBUG
  #define ASSERT(c) (void)0
#else
  #include <assert.h>
  #define ASSERT(c) assert(c)
#endif

#define STATIC_ASSERT(cond, msg) char STATIC_ASSERT_##msg[1 -  2*(!(cond))]

#define FATAL(msg)                                                             \
  {                                                                            \
    fprintf(stderr, msg);                                                      \
    exit(-1);                                                                  \
  } (void)0

#define CHECK(a, b)                                                            \
  {                                                                            \
    if((a) != (b))                                                             \
      FATAL("error:" STR( __FILE__ )":"STR( __LINE__ )"\n");                   \
  } (void)0

#define NCHECK(a, b)                                                           \
  {                                                                            \
    if((a) == (b))                                                             \
      FATAL("error:" STR( __FILE__ )":"STR( __LINE__ )"\n");                   \
  } (void)0

/*******************************************************************************
 * Branch prediction information
 ******************************************************************************/
#define LIKELY(x) __builtin_expect(x, 1)
#define UNLIKELY(x) __builtin_expect(x, 0)

/*******************************************************************************
 * SIMD instruction sets
 ******************************************************************************/
#ifdef __SSE__
  #define SIMD_SSE
#endif

#ifdef __SSE2__
  #define SIMD_SSE2
#endif

#ifdef __SSE3__
  #define SIMD_SSE3
#endif

#ifdef __SSSE3__
  #define SIMD_SSSE3
#endif

/*******************************************************************************
 * Miscellaneous
 ******************************************************************************/
#define BIT(num) (1 << (num))
#define CONCAT__(a, b) a ## b
#define CONCAT(a, b) CONCAT__(a, b)

#define CONTAINER_OF(ptr, type, member) \
  (type*)((uintptr_t)ptr - offsetof(type, member))

#define COUNTER __COUNTER__
#define FOR_EACH(var, start, end) for((var) = (start); (var)<(end); ++(var))

#define IS_MEMORY_OVERLAPPED(d0, sz0, d1, sz1)                                 \
  (((intptr_t)(d0) >= (intptr_t)(d1) &&                                        \
   (intptr_t)(d0) < ((intptr_t)(d1) + (intptr_t)(sz1))) ||                     \
  (((intptr_t)(d0) + (intptr_t)(sz0)) >= (intptr_t)(d1) &&                     \
   ((intptr_t)(d0) + (intptr_t)(sz0)) < ((intptr_t)(d1) + (intptr_t)(sz1))))

#define STR__(x) #x
#define STR(x) STR__(x)

#endif /* SNLSYS_H */

