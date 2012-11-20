#include "adder.h"

int main() {
  A_init();
  AObj str = AString_make("foobar");
  A_log(ALOG_INFO, "hello str == %s (adresses: %p, %p)", Astr_get_cstr(str), str, Astr_get_cstr(str));
  A_log(ALOG_INFO, "AString_type->name %s", AString_type->name);
  A_log(ALOG_INFO, "str->type == %s, str == %s, %s", A_dump((AObj)str->type), A_dump(str), str->type->name);
  AObj list = AList_make(str, A_nil);
  A_log(ALOG_INFO, "list: %s", A_dump(list));
  A_log(ALOG_INFO, "list: %s", A_dump(AList_makelist(3, str, str, str)));
  AObj exec = AList_makelist(2, ASym_make("print"), AString_make("Hello world!"));
  A_log(ALOG_INFO, "%s", A_dump(exec));
  AObj d = ADict_make();
  ADict_put(d, AString_make("Hello world!"), AInt_make(12));
  A_log(ALOG_INFO, "dict %s", A_dump(d));
  A_log(ALOG_INFO, "key hello world: %s", A_dump(ADict_get(d, AString_make("Hello world!"))));
}
