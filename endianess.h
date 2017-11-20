#ifndef ENDIANESS_H
#define ENDIANESS_H

/* this header is released under the public domain. grab it and drop
   it into your project, include it and use the following macros
   to determine endianess:

   ENDIANESS_LE, ENDIANESS_BE

   e.g. #if ENDIANESS_LE ...

   or, even nicer without littering your code with #ifdefs:

   if(ENDIANESS_BE) { big_endian_code(); } else { little_endian_code(); }

   ... since the compiler can optimize away unused branches, this makes your
   code easier to read while not loosing any of the advantage of using
   conditional compilation, plus you get a free compile-time check of the
   unused code path (rarely used conditonally compiled code paths often get
   defunct over time if nobody checks them all the time).

   to debug this header yourself, you can define ENDIANESS_DEBUG to see
   warnings from where we take the defs for the specific target.

*/

/* this should catch all modern GCCs and clang */
#if (defined __BYTE_ORDER__) && (defined __ORDER_LITTLE_ENDIAN__)
# ifdef ENDIANESS_DEBUG
#  warning "taking endianess from built-in __BYTE_ORDER__"
# endif
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define ENDIANESS_LE 1
# define ENDIANESS_BE 0
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
# define ENDIANESS_LE 0
# define ENDIANESS_BE 1
#endif
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
# define ENDIANESS_LE 1
# define ENDIANESS_BE 0
# elif defined(__MIPSEB) || defined(_MIPSEB) || defined(MIPSEB) || \
       defined(__MICROBLAZEEB__) || defined(__ARMEB__) || \
       (defined(__BIG_ENDIAN__) && __BIG_ENDIAN__ == 1) || \
       (defined(_BIG_ENDIAN) && _BIG_ENDIAN == 1)
# ifdef ENDIANESS_DEBUG
#  warning "detected big endian target CPU"
# endif
# define ENDIANESS_LE 0
# define ENDIANESS_BE 1
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

#ifndef ENDIANESS_LE
# undef ENDIANESS_BE
# if defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN)
#  if __BYTE_ORDER == __LITTLE_ENDIAN
#   define ENDIANESS_LE 1
#   define ENDIANESS_BE 0
#  elif __BYTE_ORDER == __BIG_ENDIAN
#   define ENDIANESS_LE 0
#   define ENDIANESS_BE 1
#  endif
# elif defined(BYTE_ORDER) && defined(LITTLE_ENDIAN)
#  if BYTE_ORDER == LITTLE_ENDIAN
#   define ENDIANESS_LE 1
#   define ENDIANESS_BE 0
#  elif BYTE_ORDER == BIG_ENDIAN
#   define ENDIANESS_LE 0
#   define ENDIANESS_BE 1
#  endif
# endif
#endif

/* in case the user passed one of -DENDIANESS_LE or BE in CPPFLAS,
   set the second one too. */
#if defined(ENDIANESS_LE) && !(defined(ENDIANESS_BE))
# if ENDIANESS_LE == 0
#  define ENDIANESS_BE 1
# else
#  define ENDIANESS_BE 0
# endif
#elif defined(ENDIANESS_BE) && !(defined(ENDIANESS_LE))
# if ENDIANESS_BE == 0
#  define ENDIANESS_LE 1
# else
#  define ENDIANESS_LE 0
# endif
#endif

#if !(defined(ENDIANESS_LE))
# error "sorry, we couldnt detect endianess for your system! please set -DENDIANESS_LE=1 or 0 using your CPPFLAGS/CFLAGS and open an issue for your system on https://github.com/rofl0r/endianess.h - thanks!"
#endif

#endif

