#ifndef LIST_H
#define LIST_H

#include "rsys.h"

struct list_node {
  struct list_node* next;
  struct list_node* prev;
};

/*******************************************************************************
 * Private macros
 ******************************************************************************/
#define ADD_NODE__(Node, Prev, Next)                                           \
  {                                                                            \
    struct list_node* prev__ = (Prev);                                         \
    struct list_node* next__ = (Next);                                         \
    struct list_node* node__ = (Node);                                         \
    next__->prev = node__;                                                     \
    node__->next = next__;                                                     \
    node__->prev = prev__;                                                     \
    prev__->next = node__;                                                     \
  } (void)0

#define DEL_NODE__(Prev, Next)                                                 \
  {                                                                            \
    struct list_node* prev__ = (Prev);                                         \
    struct list_node* next__ = (Next);                                         \
    next__->prev = prev__;                                                     \
    prev__->next = next__;                                                     \
  } (void)0

/*******************************************************************************
 * Helper macros
 ******************************************************************************/
#define LIST_FOR_EACH(Pos, List)                                               \
  for(Pos = (List)->next; Pos != (List); Pos = Pos->next)

#define LIST_FOR_EACH_REVERSE(Pos, List)                                       \
  for(Pos = (List)->prev; Pos != (List); Pos = Pos->prev)

/* Safe against removal of list entry */
#define LIST_FOR_EACH_SAFE(Pos, Tmp, List)                                     \
  for(Pos = (List)->next, Tmp = Pos->next;                                     \
      Pos != (List);                                                           \
      Pos = Tmp, Tmp = Pos->next)

/* Safe against removal of list entry */
#define LIST_FOR_EACH_REVERSE_SAFE(Pos, Tmp, List)                             \
  for(Pos = (List)->prev, Tmp = Pos->prev;                                     \
      Pos != (List);                                                           \
      Pos = Tmp, Tmp = Pos->prev)

/*******************************************************************************
 * Node list public macros
 ******************************************************************************/
#define LIST_INIT(Node)                                                        \
  {                                                                            \
    (Node)->next = (Node);                                                     \
    (Node)->prev = (Node);                                                     \
  } (void)0

#define IS_LIST_EMPTY(Node) ((Node)->next == (Node))

#define LIST_HEAD(Node)                                                        \
  (                                                                            \
    ASSERT(!IS_LIST_EMPTY(Node)),                                              \
    (Node)->next                                                               \
  )

#define LIST_TAIL(Node)                                                        \
  (                                                                            \
    ASSERT(!IS_LIST_EMPTY(Node)),                                              \
    (Node)->prev                                                               \
  )

#define LIST_ADD(List, Node)                                                   \
  {                                                                            \
    ASSERT(IS_LIST_EMPTY(Node));                                               \
    ADD_NODE__(Node, List, (List)->next);                                      \
  } (void)0

#define LIST_ADD_TAIL(List, Node)                                              \
  {                                                                            \
    ASSERT(IS_LIST_EMPTY(Node));                                               \
    ADD_NODE__(Node, (List)->prev, List);                                      \
  } (void)0

#define LIST_DEL(Node)                                                         \
  {                                                                            \
    DEL_NODE__((Node)->prev, (Node)->next);                                    \
    LIST_INIT(Node);                                                           \
  } (void)0

#define LIST_MOVE(Node, List)                                                  \
  {                                                                            \
    DEL_NODE__((Node)->prev, (Node)->next);                                    \
    ADD_NODE__(Node, List, (List)->next);                                      \
  } (void)0

#define LIST_MOVE_TAIL(Node, List)                                             \
  {                                                                            \
    DEL_NODE__((Node)->prev, (Node)->next);                                    \
    ADD_NODE__(Node, (List)->prev, List);                                      \
  } (void)0

#endif /* LIST_H */

