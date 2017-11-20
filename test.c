#define ENDIANESS_DEBUG
#include "endianess.h"

#include <stdio.h>

int main() {

#if ENDIANESS_LE
#    define STR "little"
#elif ENDIANESS_BE
#    define STR "big"
#else
#    error "unknown endianess"
#endif

	puts("this program was compiled for " STR " endian");

	if(ENDIANESS_LE) {
		puts("yes, the endianess is little!");
	} else if(ENDIANESS_BE) {
		puts("yes, the endianess is BIG!");
	} else {
		puts("this code will never be reached!");
	}

}
