#ifndef _FOUNTAIN_TYPE_H_
#define _FOUNTAIN_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>

#ifdef INT_MAX
#undef INT_MAX
#define INT_MAX		((int)(~0U>>1))
#endif

#ifdef INT_MIN
#undef INT_MIN
#define INT_MIN		(-INT_MAX - 1)
#endif

#ifdef UINT_MAX
#undef UINT_MAX
#define UINT_MAX	(~0U)
#endif

#ifdef LONG_MAX
#undef LONG_MAX
#define LONG_MAX	((long)(~0UL>>1))
#endif

#ifdef LONG_MIN
#undef LONG_MIN
#define LONG_MIN	(-LONG_MAX - 1)
#endif

#ifdef ULONG_MAX
#undef ULONG_MAX
#define ULONG_MAX	(~0UL)
#endif

#ifdef LLONG_MAX
#undef LLONG_MAX
#define LLONG_MAX	((long long)(~0ULL>>1))
#endif

#ifdef LLONG_MIN
#undef LLONG_MIN
#define LLONG_MIN	(-LLONG_MAX - 1)
#endif

#ifdef ULLONG_MAX
#undef ULLONG_MAX
#define ULLONG_MAX	(~0ULL)
#endif

typedef int8_t   S8;
typedef uint8_t  U8;
typedef int16_t  S16;
typedef uint16_t U16;
typedef int32_t  S32;
typedef uint32_t U32;
typedef int64_t  S64;
typedef uint64_t U64;

/*type of chunk handle*/
typedef int64_t chandle;

#define TRUE  1
#define FALSE 0

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
}
#endif

#endif //_FOUNTAIN_TYPE_H_
