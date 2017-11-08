#ifndef ENDIANESS_H
#define ENDIANESS_H

/* this header is released under the public domain. grab it and drop
   it into your project, include it and use the following macros
   to determine endianess:

   __BYTE_ORDER, __LITTLE_ENDIAN, __BIG_ENDIAN

   e.g. #if __BYTE_ORDER == __LITTLE_ENDIAN ...

   define ENDIANESS_DEBUG to see warnings from where we take the defs.
*/

/* this should catch all modern GCCs and clang */
#if (defined __BYTE_ORDER__) && (defined __ORDER_LITTLE_ENDIAN__)
# ifdef ENDIANESS_DEBUG
#  warning "taking endianess from built-in __BYTE_ORDER__"
# endif
# define __BYTE_ORDER __BYTE_ORDER__
# define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
# define __BIG_ENDIAN __ORDER_BIG_ENDIAN__
/* try to derive from arch/compiler-specific macros */
#elif defined(_X86_) || defined(__x86_64__) || defined(__i386__) || \
      defined(__i486__) || defined(__i586__) || defined(__i686__) || \
      defined(__MIPSEL) || defined(_MIPSEL) || defined(MIPSEL) || \
      defined(__ARMEL__) || \
      (defined(__LITTLE_ENDIAN__) && __LITTLE_ENDIAN__ == 1) || \
      (defined(_LITTLE_ENDIAN) && _LITTLE_ENDIAN == 1) || \
      defined(_M_IX86) || defined(_M_AMD64) /* MSVC */
# ifdef ENDIANESS_DEBUG
#  warning "detected little endian target CPU"
# endif
# define __LITTLE_ENDIAN 1234
# define __BIG_ENDIAN 4321
# define __BYTE_ORDER __LITTLE_ENDIAN
# elif defined(__MIPSEB) || defined(_MIPSEB) || defined(MIPSEB) || \
       defined(__MICROBLAZEEB__) || defined(__ARMEB__) || \
       (defined(__BIG_ENDIAN__) && __BIG_ENDIAN__ == 1) || \
       (defined(_BIG_ENDIAN) && _BIG_ENDIAN == 1)
# ifdef ENDIANESS_DEBUG
#  warning "detected big endian target CPU"
# endif
# define __LITTLE_ENDIAN 1234
# define __BIG_ENDIAN 4321
# define __BYTE_ORDER __BIG_ENDIAN
/* try to get it from a header. */
#else
# if defined(__linux)
#  ifdef ENDIANESS_DEBUG
#   warning "taking endianess from endian.h"
#  endif
#  include <endian.h>
# else
#  ifdef ENDIANESS_DEBUG
#   warning "taking endianess from machine/endian.h"
#  endif
#  include <machine/endian.h>
# endif
#endif

#if (!defined(__BYTE_ORDER)) && (!defined(BYTE_ORDER))
#error "no __BYTE_ORDER macro found!"
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER BYTE_ORDER
#endif

#if (!defined(__LITTLE_ENDIAN)) && (!defined(LITTLE_ENDIAN))
#error "no __LITTLE_ENDIAN macro found!"
#endif

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __BIG_ENDIAN BIG_ENDIAN
#endif

#endif

