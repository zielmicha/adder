// -------------------
// AList
// -------------------

AType_def(AList,
          AObj first;
          AObj rest;);

void AList_init();
AObj AList_make(AObj first, AObj rest);
AObj AList_makelist(int count, ...);
extern AType AList_type;
extern AObj A_nil;

#define AList_ITERATE(LIST, VARNAME) do {               \
  AList _##VARNAME##__it = (AList)(LIST);               \
  AObj VARNAME;                                         \
  while(_##VARNAME##__it != (AList)A_nil) {             \
  VARNAME = _##VARNAME##__it->first;                    \
  _##VARNAME##__it = (AList)_##VARNAME##__it->rest;

#define AList_ITERATE_END } } while(false)

// -------------------
// AString
// -------------------

AObj AString_make(char* data);
AObj AString_alloc(int length);
void AString_init();
AObj AString_join(char* sep, AObj list);

extern AType AString_type;
AType_def(AString,
          struct Astr data;);

// -------------------
// ASym
// -------------------

AObj ASym_make(char* data);
void ASym_init();

extern AType ASym_type;
AType_def(ASym,
          struct Astr data;);

// -------------------
// ADict
// -------------------
AType_def(ADict,
          struct Astr data;);
