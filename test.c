#define ENDIANNESS_DEBUG
#include "endianness.h"

#include <stdio.h>

int main() {

#if ENDIANNESS_LE
#    define STR "little"
#elif ENDIANNESS_BE
#    define STR "big"
#else
#    error "unknown endianness"
#endif

	puts("this program was compiled for " STR " endian");

	if(ENDIANNESS_LE) {
		puts("yes, the endianness is little!");
	} else if(ENDIANNESS_BE) {
		puts("yes, the endianness is BIG!");
	} else {
		puts("this code will never be reached!");
	}

}
