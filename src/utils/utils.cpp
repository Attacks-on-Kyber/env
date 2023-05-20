#include "utils.h"

void print_hex(const unsigned char *data, size_t len){
  size_t i;
  for (i = 0; i < len; ++i) {
      printf("%02X", data[i]);
  }
  printf("\n");
}
