# Description

A one-file library to determine endianness at compile time.
Just drop a copy of the header in your source tree, use it
and forget about all the platform-specific differences to
get a definition. Some of the usual conversion functions are also provided.

# Synopsis

```C
#include "endianness.h"
#if ENDIANNESS_LE
/* Little Endian code here */
#elif ENDIANNESS_BE
/* Big Endian code here */
#endif
```

## Conversion functions

All the functions start with the `end_` prefix.
The conversion functions available are:

```
end_ntoh16(x)  // equivalent of ntohs(x) from <netinet/in.h>
end_hton16(x)  //               htons(x)
end_ntoh32(x)  //               ntohl(x)
end_hton32(x)  //               htonl(x)
end_ntoh64(x)
end_hton64(x)
```

or, more generally:

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

Finally the byteswap functions:
```
end_bswap16(x)
end_bswap32(x)
end_bswap64(x)
```

If all you need are these functions and not the compile-time detection macros
you may want to `#define ENDIANNESS_PORTABLE_CONVERSION`
prior to including this header, as shown below:

```C
#define ENDIANNESS_PORTABLE_CONVERSION
#include "endianness.h"
```

That way, when the endiannes can't be determined at compile time, the code
will fallback to a slower, but portable version of those functions.
However, if using it, it's not guaranteed that ENDIANNESS_LE/BE will be defined.

# License

This file is published under the public domain. In case the concept of
public domain does not exist under your jurisdiction, you can consider it
to be dual licensed under the [MIT](https://opensource.org/licenses/MIT),
[Apache](https://www.apache.org/licenses/LICENSE-2.0) and
[WTFPL](http://www.wtfpl.net/about/) licenses.

# Contribution

If you notice an issue on a platform you're using, feel
free to open a PR or issue.
