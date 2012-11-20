#include "addertest.h"
#include <stdio.h>

ADDER_TEST(adderob_string) {
  AObj obj = AString_make("foobar");
  ASSERT(strcmp(Astr_get_cstr(obj), "_foobar") == 0);
  //printf("CRASH! %d\n", *((int*)NULL));
} ADDER_TEST_END
