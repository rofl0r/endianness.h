#define ENDIANNESS_DEBUG
#include "endianness.h"

#include <stdio.h>
#include <assert.h>

static void printPlatformEndianness();
static void executeTests();

int main()
{
	printPlatformEndianness();
	executeTests();

	return 0;
}

void printPlatformEndianness()
{
	#if ENDIANNESS_LE
	#	define STR "little"
	#elif ENDIANNESS_BE
	#	define STR "big"
	#else
	#	error "unknown endianness"
	#endif

	puts("\nThis program was compiled for " STR " endian.");

	if(ENDIANNESS_LE) {
		puts("\tYes, the endianness is little!");
	} else if(ENDIANNESS_BE) {
		puts("\tYes, the endianness is BIG!");
	} else {
		puts("\tThis code shall never be reached!");
	}
}

static const uint8_t bigEndian[sizeof(uint64_t)] =
{
	0xDE, 0xAD,
	0xBE, 0xEF,
	0xCA, 0xFE,
	0xBA, 0xBE
};

static const size_t bigEndian_count = sizeof(bigEndian) / sizeof(*bigEndian);

static const uint8_t littleEndian[sizeof(uint64_t)] =
{
	bigEndian[bigEndian_count - 1],
	bigEndian[bigEndian_count - 2],
	bigEndian[bigEndian_count - 3],
	bigEndian[bigEndian_count - 4],
	bigEndian[bigEndian_count - 5],
	bigEndian[bigEndian_count - 6],
	bigEndian[bigEndian_count - 7],
	bigEndian[bigEndian_count - 8],
};

static const size_t littleEndian_count =
						sizeof(littleEndian)
						/ sizeof(*littleEndian);

static const uint16_t host_16bit = 0xDEADu;
static const uint32_t host_32bit = 0xDEADBEEFu;
static const uint64_t host_64bit = 0xDEADBEEFCAFEBABEu;


static void executeBigEndianConversionTests();
static void executeLittleEndianConversionTests();
static void printTestData();

void executeTests()
{
	puts("\nExecuting conversion tests:");
	printTestData();

	executeBigEndianConversionTests();
	executeLittleEndianConversionTests();
}

void printVarLayout(
	char const * const name,
	uint8_t const * const var,
	size_t size);

#define printVarNameAndLayout(var) \
	printVarLayout(#var, (const uint8_t*)&var, sizeof(var))

void printTestData()
{
	puts("\tTest data:");
	printVarNameAndLayout(host_64bit);
	printVarNameAndLayout(littleEndian);
	printVarNameAndLayout(bigEndian);
	puts("");
}

void printVarLayout(
	char const * const name,
	uint8_t const * const var,
	size_t size)
{
	printf("\t\t%s:\t", name);

	for(size_t i = 0; i < size; ++i)
	{
		printf("%X ", var[i]);
	}

	puts("");
}

void executeBigEndianConversionTests()
{
	puts("\t# Network order (big-endian) to host:");

	assert(host_16bit == end_ntoh16( *(const uint16_t*)bigEndian));
	assert(host_16bit == end_be16toh(*(const uint16_t*)bigEndian));

	assert(host_32bit == end_ntoh32( *(const uint32_t*)bigEndian));
	assert(host_32bit == end_be32toh(*(const uint32_t*)bigEndian));

	assert(host_64bit == end_ntoh64( *(const uint64_t*)bigEndian));
	assert(host_64bit == end_be64toh(*(const uint64_t*)bigEndian));
	puts("\t\t OK!");

	puts("\t# Host to network order (big-endian):");
	assert(*((const uint16_t*)bigEndian) == end_hton16( host_16bit));
	assert(*((const uint16_t*)bigEndian) == end_htobe16(host_16bit));

	assert(*((const uint32_t*)bigEndian) == end_hton32( host_32bit));
	assert(*((const uint32_t*)bigEndian) == end_htobe32(host_32bit));

	assert(*((const uint64_t*)bigEndian) == end_hton64( host_64bit));
	assert(*((const uint64_t*)bigEndian) == end_htobe64(host_64bit));
	puts("\t\t OK!");
}

void executeLittleEndianConversionTests()
{
	const uint16_t* littleEndian_16bit =
		(const uint16_t*)&littleEndian[littleEndian_count - sizeof(uint16_t)];

	const uint32_t* littleEndian_32bit =
		(const uint32_t*)&littleEndian[littleEndian_count - sizeof(uint32_t)];

	const uint64_t* littleEndian_64bit = (const uint64_t*)littleEndian;

	puts("\t# Little-endian to host:");
	assert(host_16bit == end_le16toh(*littleEndian_16bit));
	assert(host_32bit == end_le32toh(*littleEndian_32bit));
	assert(host_64bit == end_le64toh(*littleEndian_64bit));

	puts("\t\t OK!");

	puts("\t# Host to little-endian:");
	assert(*littleEndian_16bit == end_htole16(host_16bit));
	assert(*littleEndian_32bit == end_htole32(host_32bit));
	assert(*littleEndian_64bit == end_htole64(host_64bit));
	puts("\t\t OK!");
}
