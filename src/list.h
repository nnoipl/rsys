#ifndef LIST_H
#define LIST_H

#include "rsys.h"

struct list_node {
  struct list_node* next;
  struct list_node* prev;
};

/******************************************************************************
 * Private functions
 ******************************************************************************/
static FINLINE void
add_node__
  (struct list_node* node,
   struct list_node* prev,
   struct list_node* next)
{
  ASSERT(node && prev && next);
  next->prev = node;
  node->next = next;
  node->prev = prev;
  prev->next = node;
}

static FINLINE void
del_node__(struct list_node* prev, struct list_node* next)
{
  ASSERT(prev && next);
  next->prev = prev;
  prev->next = next;
}

/******************************************************************************
 * Helper macros
 ******************************************************************************/
#define LIST_FOR_EACH(Pos, List)                                               \
  for(struct list_node* Pos = (List)->next; Pos != (List); Pos = Pos->next)

#define LIST_FOR_EACH_REVERSE(Pos, List)                                       \
  for(struct list_node* Pos = (List)->prev; Pos != (List); Pos = Pos->prev)

/* Safe against removal of list entry. */
#define LIST_FOR_EACH_SAFE(Pos, List)                                          \
  for(struct list_node* Pos = (List)->next,* tmp ## COUNTER ## __ = Pos->next; \
      Pos != (List);                                                           \
      Pos = tmp ## COUNTER ## __ , tmp ## COUNTER ## __ = Pos->next)

/* Safe against removal of list entry. */
#define LIST_FOR_EACH_REVERSE_SAFE(Pos, List)                                  \
  for(struct list_node* Pos = (List)->prev,* tmp ## COUNTER ## __ = Pos->prev; \
      Pos != (List);                                                           \
      Pos = tmp ## COUNTER ## __, tmp ## COUNTER ## __ = Pos->prev)

/******************************************************************************
 * Node list functions
 ******************************************************************************/
static FINLINE void
list_init(struct list_node* node)
{
  ASSERT(node);
  node->next = node;
  node->prev = node;
}

static FINLINE int
is_list_empty(const struct list_node* node)
{
  ASSERT(node);
  return node->next == node;
}

static FINLINE struct list_node*
list_head(struct list_node* node)
{
  ASSERT(node && !is_list_empty(node));
  return node->next;
}

static FINLINE struct list_node*
list_tail(struct list_node* node)
{
  ASSERT(node && !is_list_empty(node));
  return node->prev;
}

static FINLINE void
list_add(struct list_node* list, struct list_node* node)
{
  ASSERT(list && node && is_list_empty(node));
  add_node__(node, list, list->next);
}

static FINLINE void
list_add_tail(struct list_node* list, struct list_node* node)
{
  ASSERT(list && node && is_list_empty(node));
  add_node__(node, list->prev, list);
}

static FINLINE void
list_del(struct list_node* node)
{
  ASSERT(node);
  del_node__(node->prev, node->next);
  list_init(node);
}

static FINLINE void
list_move(struct list_node* node, struct list_node* list)
{
  ASSERT(node && list);
  del_node__(node->prev, node->next);
  add_node__(node, list, list->next);
}

static FINLINE void
list_move_tail(struct list_node* node, struct list_node* list)
{
  ASSERT(node && list);
  del_node__(node->prev, node->next);
  add_node__(node, list->prev, list);
}

#endif /* LIST_H */

