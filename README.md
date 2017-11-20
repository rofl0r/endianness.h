# endianess.h

a one-file library to determine endianess at compile time.
just drop a copy of the header in your source tree, use it
and forget about all the platform-specific differences to
get a definition.

# synopsis

```
#include "endianess.h"
#if ENDIANESS_LE
/* little endian code here */
#elif ENDIANESS_BE
/* big endian code here */
#endif
```

# license

this file is published under the public domain.
even in jurisdictions where the "public domain" is not an
accepted opensource license, this header is too trivial
to even think about assigning a copyright.

# contribution

if you notice an issue on a platform you're using, feel
free to open a PR or issue.
