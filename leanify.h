#ifndef LEANIFY_H_
#define LEANIFY_H_

#include <cstddef>
#include <string>

extern int depth;
extern int max_depth;
extern bool is_fast;
extern bool is_verbose;
extern int iterations;

size_t ZlibRecompress(void* src, size_t src_len, size_t size_leanified = 0);

#endif  // LEANIFY_H_
