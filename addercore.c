#include "adder.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void A_log(int loglevel, char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  A_log_va(loglevel, fmt, args);
  va_end(args);
}

void A_log_va(int loglevel, char* fmt, va_list args) {
  fprintf(stderr, "%s: ", Alog_get_level_name(loglevel));
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
}

char* Alog_get_level_name(int loglevel) {
  switch(loglevel) {
  case ALOG_TOTAL_FAILURE:
    return "TOTAL FAILURE";
  case ALOG_ERROR:
    return "ERROR";
  case ALOG_WARNING:
    return "WARN";
  case ALOG_INFO:
    return "INFO";
  case ALOG_DEBUG:
    return "DEBUG";
  default:
    return "UNKNOWN";
  }
}

void A_total_failure(char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  A_log_va(ALOG_TOTAL_FAILURE, fmt, args);
  va_end(args);
  abort();
}

void AType_init();
void A_init() {
  AType_init();
  ASym_init();
  AString_init();
  AList_init();
}

AType AType_type;

void AType_init() {
  AType_type = AType_create("type");
  AType_type->type = AType_type;
}

AType AType_create(char* name) {
  AType t = (AType)AGC_alloc(NULL, sizeof(struct AType_inline));
  t->name = name;
  t->gc_get_refs = NULL;
  t->gc_get_free_func = NULL;
  t->call = NULL;
  t->type = AType_type;
  return t;
}

char* A_dump(AObj obj) {
  /** Returns obj dump as temporary string. */
  if(obj == NULL) {
    return "#[NULL]";
  } else if(obj->type == NULL) {
    return A_format("#[obj at %p without type]", (void*)obj);
  } else if(obj->type->dump == NULL) {
    return A_format("#[obj of type '%s' at %p]", obj->type->name, (void*)obj);
  } else {
    return obj->type->dump(obj);
  }
}

AObj AObj_repr(AObj self) {
  return AString_make(A_dump(self));
}

char* A_format(char* fmt, ...) {
  /** Formats string like sprintf. Result is a temprary string. */
  va_list args;
  va_start(args, fmt);
  char* result = A_format_va(fmt, args);
  va_end(args);
  return result;
}

char* A_format_va(char* fmt, va_list args) {
  /** Formats string like sprintf. Result is a temprary string. */
  va_list args_copy;
  A_va_copy(args_copy, args);
  int size = vsnprintf(NULL, 0, fmt, args_copy);
  char* buffer = AGC_alloc_tmp_string(size + 1);
  int out_size = vsnprintf(buffer, size + 1, fmt, args);
  if(out_size != size)
    A_log(ALOG_ERROR, "A_format_va: list of arguments changed between two vsnprintf calls"
          "(output size changed from %d to %d)", size, out_size);
  return buffer;
}
