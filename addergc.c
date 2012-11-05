#include "adder.h"
#include <sys/mman.h>
#include <stdio.h>

char* heap;
char* heap_ptr;
char* heap_end;
int heap_size;
AObj heap_first;
AObj heap_last;

static void gc_grow_heap();
static void gc_init();

AObj AGC_alloc(AType type, int size) {
  if(size > 4096) {
    A_total_failure("AGC_alloc for size > 4096 not implemented");
  }
  if(!heap){
    gc_init();
  }
  AObj obj = (AObj)heap_ptr;
  heap_ptr += size;
  if(heap_ptr >= heap_end) {
    gc_grow_heap();
  }

  obj->type = type;
  obj->gcheader.size = size;
  obj->gcheader.flags = 0;
  obj->gcheader.prev = heap_last;
  obj->gcheader.next = NULL;

  if(heap_last != NULL) {
    heap_last->gcheader.next = obj;
    heap_last = obj;
  } else {
    heap_last = heap_first = obj;
  }
  return obj;
}

char* AGC_alloc_tmp_string(int size) {
  /** Allocates string for logging/debugging use.
      May be freed on next garbage colletion. */
  return Astr_get_cstr(Astr_alloc(AString_type, 0, NULL, size));
}

void AGC_add_root(AObj* root) {

}

void AGC_perform_gc() {
  A_total_failure("AGC_perform_gc not implemented");
}

static void gc_grow_heap() {
  A_total_failure("gc_grow_heap not implemented");
}

static void gc_init() {
  heap_size = AGC_INITIAL_HEAP_SIZE;
  heap_ptr = heap = (char*)mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if(heap_ptr == MAP_FAILED || heap_ptr == NULL) {
    perror("mmap");
    A_total_failure("failed to allocate heap of size %d", heap_size);
  }
  heap_end = heap_ptr + heap_size;
}
