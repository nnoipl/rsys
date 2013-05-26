#include "list.h"
/*#include "mem_allocator.h"*/
#include "rsys.h"

int
main(int argc, char** argv)
{
  struct elmt {
    struct list_node node;
    char c;
  } elmt0, elmt1, elmt2;
  struct list_node list, list1;
  struct list_node* n = NULL;
  struct list_node* tmp = NULL;
  int i = 0;

  (void)argc;
  (void)argv;

  LIST_INIT(&list);
  LIST_INIT(&list1);
  LIST_INIT(&elmt0.node);
  LIST_INIT(&elmt1.node);
  LIST_INIT(&elmt2.node);

  CHECK(IS_LIST_EMPTY(&list), 1);

  elmt0.c = 'a';
  LIST_ADD(&list,  &elmt0.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(LIST_HEAD(&list), &elmt0.node);

  elmt1.c = 'b';
  LIST_ADD(&list,  &elmt1.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(elmt1.node.next, &elmt0.node);
  CHECK(elmt1.node.prev, &list);
  CHECK(elmt1.node.next->prev, &elmt1.node);
  CHECK(LIST_HEAD(&list), &elmt1.node);

  elmt2.c = 'c';
  LIST_ADD_TAIL(&list,  &elmt2.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(elmt2.node.next, &list);
  CHECK(elmt2.node.prev, &elmt0.node);
  CHECK(elmt2.node.prev->prev, &elmt1.node);
  CHECK(elmt1.node.next->next, &elmt2.node);
  CHECK(elmt0.node.next, &elmt2.node);
  CHECK(LIST_HEAD(&list), &elmt1.node);
  CHECK(LIST_TAIL(&list), &elmt2.node);

  LIST_DEL(&elmt0.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(elmt2.node.next, &list);
  CHECK(elmt2.node.prev, &elmt1.node);
  CHECK(elmt1.node.next, &elmt2.node);
  CHECK(elmt1.node.prev, &list);
  CHECK(LIST_HEAD(&list), &elmt1.node);
  CHECK(LIST_TAIL(&list), &elmt2.node);

  LIST_DEL(&elmt2.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(elmt1.node.next, &list);
  CHECK(elmt1.node.prev, &list);
  CHECK(LIST_HEAD(&list), &elmt1.node);
  CHECK(LIST_TAIL(&list), &elmt1.node);

  LIST_DEL(&elmt1.node);
  CHECK(IS_LIST_EMPTY(&list), 1);

  LIST_ADD(&list,  &elmt2.node);
  LIST_ADD(&list,  &elmt1.node);
  LIST_ADD(&list,  &elmt0.node);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(elmt2.node.next, &list);
  CHECK(elmt2.node.prev, &elmt1.node);
  CHECK(elmt1.node.next, &elmt2.node);
  CHECK(elmt1.node.prev, &elmt0.node);
  CHECK(elmt0.node.next, &elmt1.node);
  CHECK(elmt0.node.prev, &list);
  CHECK(LIST_HEAD(&list), &elmt0.node);
  CHECK(LIST_TAIL(&list), &elmt2.node);

  CHECK(IS_LIST_EMPTY(&list1), 1);
  LIST_MOVE(&elmt1.node, &list1);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(IS_LIST_EMPTY(&list1), 0);
  CHECK(elmt2.node.next, &list);
  CHECK(elmt2.node.prev, &elmt0.node);
  CHECK(elmt1.node.next, &list1);
  CHECK(elmt1.node.prev, &list1);
  CHECK(elmt0.node.next, &elmt2.node);
  CHECK(elmt0.node.prev, &list);
  CHECK(LIST_HEAD(&list), &elmt0.node);
  CHECK(LIST_TAIL(&list), &elmt2.node);
  CHECK(LIST_HEAD(&list1), &elmt1.node);
  CHECK(LIST_TAIL(&list1), &elmt1.node);

  LIST_MOVE_TAIL(&elmt2.node, &list1);
  CHECK(IS_LIST_EMPTY(&list), 0);
  CHECK(IS_LIST_EMPTY(&list1), 0);
  CHECK(elmt2.node.next, &list1);
  CHECK(elmt2.node.prev, &elmt1.node);
  CHECK(elmt1.node.next, &elmt2.node);
  CHECK(elmt1.node.prev, &list1);
  CHECK(elmt0.node.next, &list);
  CHECK(elmt0.node.prev, &list);
  CHECK(LIST_HEAD(&list), &elmt0.node);
  CHECK(LIST_TAIL(&list), &elmt0.node);
  CHECK(LIST_HEAD(&list1), &elmt1.node);
  CHECK(LIST_TAIL(&list1), &elmt2.node);

  LIST_MOVE(&elmt0.node, &list1);
  CHECK(IS_LIST_EMPTY(&list), 1);
  CHECK(IS_LIST_EMPTY(&list1), 0);
  CHECK(elmt2.node.next, &list1);
  CHECK(elmt2.node.prev, &elmt1.node);
  CHECK(elmt1.node.next, &elmt2.node);
  CHECK(elmt1.node.prev, &elmt0.node);
  CHECK(elmt0.node.next, &elmt1.node);
  CHECK(elmt0.node.prev, &list1);
  CHECK(LIST_HEAD(&list1), &elmt0.node);
  CHECK(LIST_TAIL(&list1), &elmt2.node);

  i = 0;
  LIST_FOR_EACH(n, &list1) {
    struct elmt* e = CONTAINER_OF(n, struct elmt, node);
    CHECK(e->c, 'a' + i);
    ++i;
  }
  CHECK(i, 3);

  i = 3;
  LIST_FOR_EACH_REVERSE(n, &list1) {
    struct elmt* e = CONTAINER_OF(n, struct elmt, node);
    --i;
    CHECK(e->c, 'a' + i);
  }
  CHECK(i, 0);

  i = 0;
  LIST_FOR_EACH_SAFE(n, tmp, &list1) {
    struct elmt* e = NULL;
    LIST_MOVE_TAIL(n, &list);
    e = CONTAINER_OF(n, struct elmt, node);
    CHECK(e->c, 'a' + i);
    ++i;
  }
  CHECK(i, 3);
  CHECK(IS_LIST_EMPTY(&list1), 1);
  CHECK(IS_LIST_EMPTY(&list), 0);

  i = 3;
  LIST_FOR_EACH_REVERSE_SAFE(n, tmp, &list) {
    struct elmt* e = NULL;
    LIST_MOVE(n, &list1);
    e = CONTAINER_OF(n, struct elmt, node);
    --i;
    CHECK(e->c, 'a' + i);
  }
  CHECK(i, 0);
  CHECK(IS_LIST_EMPTY(&list1), 0);
  CHECK(IS_LIST_EMPTY(&list), 1);

  i = 0;
  LIST_FOR_EACH(n, &list1) {
    struct elmt* e = CONTAINER_OF(n, struct elmt, node);
    CHECK(e->c, 'a' + i);
    ++i;
  }
  CHECK(i, 3);

  LIST_MOVE(&elmt1.node, &list1);
  CHECK(elmt2.node.next, &list1);
  CHECK(elmt2.node.prev, &elmt0.node);
  CHECK(elmt1.node.next, &elmt0.node);
  CHECK(elmt1.node.prev, &list1);
  CHECK(elmt0.node.next, &elmt2.node);
  CHECK(elmt0.node.prev, &elmt1.node);
  CHECK(LIST_HEAD(&list1), &elmt1.node);
  CHECK(LIST_TAIL(&list1), &elmt2.node);

  LIST_MOVE_TAIL(&elmt0.node, &list1);
  CHECK(elmt2.node.next, &elmt0.node);
  CHECK(elmt2.node.prev, &elmt1.node);
  CHECK(elmt1.node.next, &elmt2.node);
  CHECK(elmt1.node.prev, &list1);
  CHECK(elmt0.node.next, &list1);
  CHECK(elmt0.node.prev, &elmt2.node);
  CHECK(LIST_HEAD(&list1), &elmt1.node);
  CHECK(LIST_TAIL(&list1), &elmt0.node);

/*  CHECK(MEM_ALLOCATED_SIZE(&mem_default_allocator), 0);*/

  return 0;
}

