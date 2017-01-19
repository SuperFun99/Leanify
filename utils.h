#ifndef UTILS_H_
#define UTILS_H_

#include <cstdint>

#ifdef _MSC_VER
#define BSWAP32(x) _byteswap_ulong(x)
#elif defined __GNUC__
#define BSWAP32(x) __builtin_bswap32(x)
#else
#define BSWAP32(x) _bswap(x)
#endif

#endif  // UTILS_H_
