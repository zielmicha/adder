#include "adder.h"

AType ADict_type;

char* ADict_dump(AObj self);
void ADict_init() {
  ADict_type = AType_create("dict");
  ADict_type->dump = ADict_dump;
  AGC_add_root((AObj*)&ADict_type);
}

AObj ADict_make() {
  return NULL;
}

void ADict_put(AObj self, AObj key, AObj val) {

}

AObj ADict_get(AObj self, AObj key) {
  return NULL;
}

char* ADict_dump(AObj self) {
  return "dict(...)";
}
