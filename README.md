# Description

A one-file public-domain library to determine endianness at compile time.
Just drop a copy of the header in your source tree, use it and forget about all
the platform-specific differences to get that endianess definition!

The usual conversion functions are also provided.

# Rationale

If someone needs to know the endianess at compile time, there are 2 different
use cases:

- in some rare cases one needs to know the endianess to lay out structs and the
  like, for example an RGB union; or directly in the code.

- in 99% of the cases, just a conversion from one endian to the other is needed,
  e.g. when a protocol defines that a value is stored in a specific endianness.

# Use case 1 - compile time endianness detecion macro

The header tries its best to determine the endianess from a number of possible
sources, and if successful, defines both `ENDIANNESS_LE` and `ENDIANNESS_BE`
macros to 0 or 1.

```C
#include "endianness.h"
#if ENDIANNESS_LE +0 == 1
/* Little Endian code here */
#elif ENDIANNESS_BE +0 == 1
/* Big Endian code here */
#endif
```

or if the macro is to be used directly from the code, you can even use the nicer
form (taking advantage of dead code elimination done by the compiler):

```C
if (ENDIANNESS_LE) {
    ...
} else {
    ...
}
```

Note that on very exotic platforms, the detection may fail. The header then
throws an error and tells the user to define the macros by hand (and report the
system here so we can get it fixed).
However, if your use case is just conversion, there's a way to avoid erroring
out. Read on!

# Use case 2 - endian conversion

In the majority of use cases, one wants just to convert from little to big
endian, and vice versa (or actually to and from host endianness!).

The provided endian conversion functions/macros start with the `end_` prefix.

```
end_htobe16(x)  // Host to Big Endian 16
end_be16toh(x)
end_htobe32(x)
end_be32toh(x)  // Big Endian 32 to Host
end_htobe64(x)
end_be64toh(x)
end_htole16(x)
end_le16toh(x)
end_htole32(x)  // Host to Little Endian 32
end_le32toh(x)
end_htole64(x)
end_le64toh(x)  // Little Endian 64 to Host
```

For conversion of network byte order (big endian) to host order:
```
end_ntoh16(x)  // equivalent of ntohs(x) from <netinet/in.h>
end_hton16(x)  //               htons(x)
end_ntoh32(x)  //               ntohl(x)
end_hton32(x)  //               htonl(x)
end_ntoh64(x)
end_hton64(x)
```

General purpose byteswap functions:
```
end_bswap16(x)
end_bswap32(x)
end_bswap64(x)
```

In case the endianness detection failed and you need only those conversions,
you can avoid erroring out by defining `ENDIANNESS_PORTABLE_CONVERSION` prior to
including the header:

```C
#define ENDIANNESS_PORTABLE_CONVERSION
#include "endianness.h"
```

That way, the code will fallback to a slightly slower, but portable version of
the conversion functions. On modern compilers like GCC 8.0 these compile into
a single move and a byteswap instruction.

However, if `ENDIANNESS_PORTABLE_CONVERSION` is in use, there's no guarantee
that the macros for use case 1 will be defined!

# License

This file is published under the public domain. In case the concept of
public domain does not exist under your jurisdiction, you can consider it
to be dual licensed under the [MIT](https://opensource.org/licenses/MIT),
[Apache](https://www.apache.org/licenses/LICENSE-2.0) and
[WTFPL](http://www.wtfpl.net/about/) licenses.

# Contribution

If you notice an issue on a platform you're using, feel free to open a PR or
issue on the Github repository https://github.com/rofl0r/endianness.h .

# Appendix A: Methodology used to detect endianness

The header first tries to use the macro `__BYTE_ORDER__` which is built into
all GCC versions >= 4.6 and all clang versions >= 3.1. Recent ICC versions
also support it.
As GCC 4.6.0 was released in 2011, this should already cover the vast majority
of available toolchains for UNIX platforms and other platforms targetted by
GCC/Clang, such as mingw.

If that fails, a number of CPU-specific macros is tested.
The list was assembled carefully by looking at built-in macros for compilers
targeting all platforms supported by musl libc (which includes e.g.
`powerpc`, `mips`, `arm`, `aarch64`, `microblaze` and many others), but also
by looking at predefined macros for compilers like MSVC and others.
For architectures that support both little and big endian configuration, we
only test for them when a macro to detect the subarch, e.g. `mipsel` exists,
in order to not produce wrong results.
Older compilers targeting one such architecture, `avr`, don't provide a macro
that could be used to determine the endianness, and even though 99% of users
use avr in little-endian configuration, we do not hardcode that avr equals
little endian.

If even this does not yield detection, we next try to open the header `endian.h`
which is unfortunately not standardized and available in different locations
in different Operating Systems. Here we use a list of OS detection macros to
derive the correct location of endian.h and then use the macros it provides.
Note that getting at this point requires that either a really old or a really
exotic compiler is used, and that one targetting a really exotic architecture.
If even this pass fails, we're dealing with an exotic compiler, an exotic
architecture, and an exotic OS - most likely a bare-metal toolchain for
embedded development.
