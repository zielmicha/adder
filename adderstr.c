#include "adder.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/**
   "Superclass" for all types holding single constant string (ASym, AString, AKeyword).
   String data is kept in same allocated region.

   `struct Astr` needs to be first field in struct. Objects containing it need to be
   allocated using Astr_alloc, not AGC_alloc.

   Astr_alloc adds string length to size of struct containing it and calls AGC_alloc
   with modified size argument.
 */

AObj Astr_alloc(AType type, int additional_length, char* data, int data_length) {
  AObj obj = AGC_alloc(type, sizeof(struct AObj_inline) + additional_length + sizeof(struct Astr) + data_length + 1);
  AObj_containing_str obj_str = (AObj_containing_str)obj;
  obj_str->str.length = data_length;
  obj_str->str.data = &(obj_str->data) + additional_length;
  if(data == NULL)
    memset(obj_str->str.data, 0, data_length);
  else
    memcpy(obj_str->str.data, data, data_length);
  obj_str->str.data[data_length] = '\0';
  return obj;
}

char* Astr_get_cstr(AObj obj) {
  return ((AObj_containing_str)obj)->str.data;
}

int Astr_get_length(AObj obj) {
  return ((AObj_containing_str)obj)->str.length;
}

char* Astr_escape(AObj obj) {
  struct Astr str = ((AObj_containing_str)obj)->str;
  char* buffer = AGC_alloc_tmp_string(str.length * 4 + 1);
  char* current = buffer;
  for(int i=0; i<str.length; i++) {
    char ch = str.data[i];
    if(ch == '\0') {
      strcpy(current, "\\0");
      current += 2;
    } else if(ch == '\n') {
      strcpy(current, "\\n");
      current += 2;
    } else if(isalnum(ch) || (ispunct(ch) && ch != '"') || ch == ' ') {
      current[0] = ch;
      current += 1;
    } else {
      sprintf(current, "\\x%x%x", (unsigned)((ch / 16) % 16), (unsigned)(ch % 16));
      current += 4;
    }
  }
  *current = '\0';
  return buffer;
}
