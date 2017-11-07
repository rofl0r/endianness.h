#define ENDIANESS_DEBUG
#include "endianess.h"

#include <stdio.h>

int main() {

#if __BYTE_ORDER == __LITTLE_ENDIAN
#    define STR "little"
#elif __BYTE_ORDER == __BIG_ENDIAN
#    define STR "big"
#else
#    error "unknown endianess"
#endif

	puts("this program was compiled for " STR " endian");
}
