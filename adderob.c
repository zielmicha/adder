#include "adder.h"
#include <string.h>

// ---------------
// AList
// ---------------

AType AList_type;
AObj A_nil;

int AList_gc_get_refs(AObj self, int seg, AObj** refs);
char* AList_dump(AObj self);

void AList_init() {
  AList_type = AType_create("list");
  AList_type->gc_get_refs = AList_gc_get_refs;
  AList_type->dump = AList_dump;
  A_nil = (AObj)AList_make(NULL, NULL);

  AGC_add_root((AObj*)&AList_type);
  AGC_add_root((AObj*)&A_nil);
}

int AList_gc_get_refs(AObj self, int seg, AObj** refs) {
  AList l = (AList)self;
  refs[0] = &l->first;
  refs[1] = &l->rest;
  return 2;
}

AObj AList_make(AObj first, AObj rest) {
  AList l = AObj_NEW(AList);
  l->first = first;
  l->rest = rest;
  return (AObj)l;
}

AObj AList_makelist(int count, ...) {
  AObj current = A_nil;
  va_list ap;

  va_start(ap, count);
  while(count--) {
    current = AList_make(va_arg(ap, AObj), current);
  }
  va_end(ap);
  return current;
}

char* AList_dump(AObj self) {
  if(self == A_nil)
    return "nil";
  AObj quoted = A_nil;
  AList_ITERATE(self, item) {
    quoted = (AObj)AList_make(AObj_repr(item), quoted);
  } AList_ITERATE_END;
  return A_format("(%s)", Astr_get_cstr(AString_join(" ", quoted)));
}

// ---------------
// AString
// ---------------

AType AString_type;

char* AString_dump(AObj self);
void AString_init() {
  AString_type = AType_create("string");
  AString_type->dump = AString_dump;
  AGC_add_root((AObj*)&AString_type);
}

AObj AString_make(char* data) {
  return Astr_alloc(AString_type, 0, data, strlen(data));
}

AObj AString_alloc(int length) {
  return Astr_alloc(AString_type, 0, NULL, length);
}

char* AString_dump(AObj self) {
  return A_format("\"%s\"", Astr_escape(self));
}

AObj AString_join(char* sep, AObj list) {
  int length = 0;
  int seplength = strlen(sep);

  AList_ITERATE(list, item) {
    if(item->type != AString_type)
      A_total_failure("AString_join list argument contains non-string item");
    length += Astr_get_length(item) + seplength;
  } AList_ITERATE_END;

  length -= seplength;
  AObj str = AString_alloc(length);
  char* buff = Astr_get_cstr(str);
  int index = 0;

  AList_ITERATE(list, item) {
    if(item->type != AString_type)
      A_total_failure("AString_join list argument contains non-string item");
    int curr_length = Astr_get_length(item);
    memcpy(buff + index, Astr_get_cstr(item), curr_length);
    index += curr_length;
    if(index >= length) break;
    strcpy(buff + index, sep);
    index += seplength;
  } AList_ITERATE_END;
  return str;
}

// ---------------
// ASym
// ---------------

AType ASym_type;

char* ASym_dump(AObj self);
void ASym_init() {
  ASym_type = AType_create("sym");
  ASym_type->dump = ASym_dump;
  AGC_add_root((AObj*)&ASym_type);
}

char* ASym_dump(AObj self) {
  return A_format("%s", Astr_escape(self));
}

AObj ASym_make(char* data) {
  return Astr_alloc(ASym_type, 0, data, strlen(data));
}

// ---------------
// AInt
// ---------------


AType AInt_type;

char* AInt_dump(AObj self);
void AInt_init() {
  AInt_type = AType_create("int");
  AInt_type->dump = AInt_dump;
  AGC_add_root((AObj*)&AInt_type);
}

AObj AInt_make(long value) {
  AInt n = AObj_NEW(AInt);
  n->value = value;
  return (AObj)n;
}

char* AInt_dump(AObj self) {
  return A_format("%ld", ((AInt)self)->value);
}
