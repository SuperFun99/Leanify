#include "leanify.h"

#include <algorithm>
#include <iostream>

#include <miniz/miniz.h>
#include <zopfli/zlib_container.h>

#include "utils.h"

using std::cerr;
using std::endl;

bool is_fast = false;
bool is_verbose = false;
int iterations = 15;
int depth = 1;
int max_depth = 5;

size_t ZlibRecompress(void* src, size_t src_len, size_t size_leanified /*= 0*/) {
  if (!is_fast) {
    size_t s = 0;
    uint8_t* buffer =
        static_cast<uint8_t*>(tinfl_decompress_mem_to_heap(src, src_len, &s, TINFL_FLAG_PARSE_ZLIB_HEADER));
    if (!buffer) {
      cerr << "Decompress Zlib data failed." << endl;
    } else {
      ZopfliOptions zopfli_options;
      ZopfliInitOptions(&zopfli_options);
      zopfli_options.numiterations = iterations;

      size_t new_size = 0;
      uint8_t* out_buffer = nullptr;
      ZopfliZlibCompress(&zopfli_options, buffer, s, &out_buffer, &new_size);
      mz_free(buffer);
      if (new_size < src_len) {
        memcpy(static_cast<uint8_t*>(src) - size_leanified, out_buffer, new_size);
        free(out_buffer);
        return new_size;
      }
      free(out_buffer);
    }
  }

  memmove(static_cast<uint8_t*>(src) - size_leanified, src, src_len);
  return src_len;
}