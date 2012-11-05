struct Astr {
  int length;
  char* data;
};

typedef struct AObj_containing_str {
  AObj_HEADER;
  struct Astr str;
  char data;
} *AObj_containing_str;

AObj Astr_alloc(AType type, int additional_length, char* data, int data_length);
char* Astr_get_cstr(AObj obj);
int Astr_get_length(AObj obj);
char* Astr_escape(AObj obj);
