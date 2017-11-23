# endianness.h

A one-file library to determine endianness at compile time.
Just drop a copy of the header in your source tree, use it
and forget about all the platform-specific differences to
get a definition.

# Synopsis

```C
#include "endianness.h"
#if ENDIANNESS_LE
/* Little endian code here */
#elif ENDIANNESS_BE
/* Big endian code here */
#endif
```

# License

This file is published under the public domain. In case the concept of
public domain does not exists under your jurisdiction, you can consider it
to be dual licensed under the MIT, Apache and WTFPL licenses.

# Contribution

If you notice an issue on a platform you're using, feel
free to open a PR or issue.
