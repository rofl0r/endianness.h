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
#else /* if not already defined by compiler, try to get it from header */
# ifdef __linux
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

