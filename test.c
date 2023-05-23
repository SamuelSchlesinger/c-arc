#include <assert.h>

#include "arc.h"
#include "list.h"

int main() {
  char* xs = malloc(sizeof(char) * 4);
  xs[0] = 'S';
  xs[1] = 'a';
  xs[2] = 'm';
  xs[3] = '\0';
  List nil = list_build_nil();
  Arc item = arc_from_owned((void*) xs);
  List cons = list_build_cons(&item, &nil);  
  list_drop(cons);
  assert(((ListNode*) arc_as_ref(nil))->tag == Nil);
  list_drop(nil);
}
