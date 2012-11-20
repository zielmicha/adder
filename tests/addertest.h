#include "adder.h"

#define ADDER_TEST(name) void _adder_testcase_##name()
#define ADDER_TEST_END
#define LOG(msg...) do { fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); fprintf(stderr, msg);  fprintf(stderr, "\n"); } while(0)
#define ASSERT(cond) if(!(cond)) { LOG("assertion failed: %s", #cond); exit(1); }

typedef void (*adder_test_func_t)();

int adder_call_test(adder_test_func_t test_ptr) {
  test_ptr();
}
