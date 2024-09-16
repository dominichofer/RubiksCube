#pragma once
#include <cstdint>

// Predefined macros:
// __GNUC__           Compiler is gcc.
// __clang__          Compiler is clang.
// __INTEL_COMPILER   Compiler is Intel.
// _MSC_VER           Compiler is Microsoft Visual Studio.
// _M_X64             Microsoft specific macro when targeting 64 bit based machines.
// __x86_64           Defined by GNU C and Sun Studio when targeting 64 bit based machines.

#if defined(_MSC_VER)
	#include <intrin.h>
#elif defined(__GNUC__)
	#include <x86intrin.h>
#else
	#error compiler not supported!
#endif

inline uint64_t popcount(uint64_t b)
{
#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
	return _mm_popcnt_u64(b);
#else
	return __builtin_popcountll(b);
#endif
}
