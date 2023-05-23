#ifndef ARC_H_
#define ARC_H_

#include <stdatomic.h>
#include <stdio.h>
#include <memory.h>

#ifndef ARC_ALLOC
#include <stdlib.h>
#define ARC_ALLOC malloc
#ifndef ARC_FREE
#define ARC_FREE free
#endif // ARC_FREE
#endif // ARC_ALLOC

typedef struct arc_inner {
  atomic_int ref_count;
  void* ref;
} ArcInner;

typedef struct arc {
  ArcInner* inner;
} Arc;

Arc arc_from_owned(void* owned_ref) {
  Arc arc;
  arc.inner = ARC_ALLOC(sizeof(struct arc_inner));
  atomic_init(&arc.inner->ref_count, 1);
  arc.inner->ref = owned_ref;
  return arc;
}

Arc arc_alloc(size_t bytes) {
  Arc arc;
  arc.inner = ARC_ALLOC(sizeof(struct arc_inner));
  atomic_init(&arc.inner->ref_count, 1);
  arc.inner->ref = (void *) ARC_ALLOC(bytes);
  return arc;
}

Arc arc_copy(void* from, void* to) {
  if (from > to) {
    fprintf(stderr, "eeeek");
    exit(0);
  }
  size_t bytes = (size_t) to - (size_t) from;
  Arc arc = arc_alloc(bytes);
  memcpy(from, arc.inner->ref, bytes); 
  return arc;
}

Arc arc_clone(Arc* arc) {
  atomic_fetch_add(&arc->inner->ref_count, 1);
  return *arc;
}

void arc_drop(Arc arc) {
  if (atomic_fetch_sub(&arc.inner->ref_count, 1) == 1) {
    ARC_FREE(arc.inner->ref);
    ARC_FREE(arc.inner);
  }
}

void* arc_as_ref(Arc arc) {
  return arc.inner->ref;
}

#endif // ARC_H_

#ifndef ARC_IMPL
#define ARC_IMPL

#endif // ARC_IMPL
