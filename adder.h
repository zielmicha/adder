#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#define A_defstruct(name) struct name##_inline; typedef struct name##_inline *name

A_defstruct(AObj);
A_defstruct(AType);
A_defstruct(AList);
A_defstruct(ADict);
A_defstruct(AVector);
A_defstruct(AString);
A_defstruct(ASym);
A_defstruct(AKw);
A_defstruct(AInt);

A_defstruct(AFrame);

struct Astr;

#define AObj_HEADER struct AGC_Objheader gcheader; AType type
#define AObj_GC_GETREF_SEGMENT_SIZE 128
#define AGC_INITIAL_HEAP_SIZE (10 * 1024 * 1024) // 10 MB
#define AType_def(NAME, BODY) struct NAME##_inline { AObj_HEADER; BODY }; struct NAME##_nohdr { BODY }

#define AGC_LARGE 0x01

void A_init();
void A_log(int loglevel, char* fmt, ...);
void A_log_va(int loglevel, char* fmt, va_list args);
char* Alog_get_level_name(int loglevel);
void A_total_failure(char* msg, ...);
char* A_dump(AObj obj);
char* A_format(char* fmt, ...);
char* A_format_va(char* fmt, va_list args);

#ifdef va_copy
#define A_va_copy va_copy
#else
#error "va_copy not defined"
#endif

#define ALOG_TOTAL_FAILURE 100
#define ALOG_ERROR 80
#define ALOG_WARNING 60
#define ALOG_INFO 40
#define ALOG_DEBUG 20

AObj AGC_alloc(AType type, int size);
void AGC_add_root(AObj* root);
char* AGC_alloc_tmp_string(int size);

#define AObj_NEW(typename) ((typename)AGC_alloc(typename##_type, sizeof(struct typename##_inline)))
AObj AObj_repr(AObj self);

extern AType AType_type;
AType AType_create(char* name);


struct AGC_Objheader {
  unsigned short size; /* objects larger than 4KB are alloced with mmap and have AGC_LARGE flag */
  unsigned short flags;
  void* prev;
  void* next;
};

struct AObj_inline {
  // 16 byte overhead
  struct AGC_Objheader gcheader;
  AType type;
};

struct AObj {
  struct AGC_Objheader gcheader;
  AType type;
  void* body;
};

AType_def(AType,
          char* name;
          int (*gc_get_refs)(AObj self, int seg, AObj** refs);
          AObj (*gc_get_free_func)(AObj self);
          bool (*call)(AObj self, AFrame frame, AObj args);
          char* (*dump)(AObj self);
          );

#include "adderstr.h"
#include "adderob.h"
