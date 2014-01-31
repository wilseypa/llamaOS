/* list.h
 * 
 * Copyright (C) 2006-2008 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* manage circular doubly linked lists.
 *
 * almost the same code than in the file list.h of SOS.
 *
 * elements listed are structures with at least 2 attributes which are
 * pointers to the previous and next element of the list.
 *
 * Each of these macros take three arguments not listed hereafter:
 * - 1st argument: the list (pointer to one of the element)
 * - last 2 arguments: name of those previous and next attribute in the
 *   element structure.
 *
 * available macros are:
 *
 * list_init(): create an empty list
 * list_singleton(item): create a list with one item
 * list_is_empty(): is the list empty ?
 * list_get_head(): give the item at the head
 * list_get_tail(): give the item at the tail
 * list_insert_after(after_this, item): insert item after after_this 
 * list_insert_before(before_this, item): insert item before before_this
 * list_add_head(item): insert item at the head
 * list_add_tail(item): insert item at the tail
 * list_delete(item): delete item from list
 * list_pop_head(): give the item at the head and delete it
 * list_foreach_forward(iter, nb_elt): loop on elts from head to tail
 * list_foreach_backward(iter, nb_elt): loop on elts from tail to head
 * list_foreach_f_early_break(iter, nb_elt): did foreach forward broke ?
 * list_foreach_b_early_break(iter, nb_elt): did foreach backward broke ?
 * list_collapse(iter): like list_foreach_forward, deleting items
 *
 * foreach can be used like this:
 *
 *      struct my_struct *list;
 *      struct my_struct *current;
 *      int nb_elts;
 *
 *      list_foreach_forward (list, current, nb_elts) {
 *          ... do something with current item...
 *      }
 *      if (list_foreach_f_early_break (list, current, nb_elts)) {
 *          ... some items have not been processed ...
 *      }
 *      else {
 *          ... all items have been processed ...
 *      }
 */

#ifndef _CROCOS_KLIBC_LIST_H
#define _CROCOS_KLIBC_LIST_H

#include <stddef.h>

#define list_init(list, prev, next) ((list) = NULL)

#define list_singleton(list, item, prev, next)  \
({  (item)->prev = (item)->next = (item);       \
    (list) = (item);                            \
 })

#define list_is_empty(list, prev, next) ((list) == NULL)

#define list_get_head(list, prev, next) (list)

#define list_get_tail(list, prev, next) \
    ((list != NULL) ? (list)->prev : NULL)

/* internal macro */
#define __list_insert_at_left(list, before_this, item, prev, next)  \
({  (before_this)->prev->next = (item);                             \
    (item)->next = (before_this);                                   \
    (item)->prev = (before_this)->prev;                             \
    (before_this)->prev = (item);                                   \
 })

#define list_insert_after(list, after_this, item, prev, next)   \
({  (after_this)->next->prev = (item);                          \
    (item)->prev = (after_this);                                \
    (item)->next = (after_this)->next;                          \
    (after_this)->next = (item);                                \
 })

#define list_insert_before(list, before_this, item, prev, next)     \
({  __list_insert_at_left (list, before_this, item, prev, next);    \
    if ((list) == (before_this)) (list) = (item);                   \
 })

#define list_add_head(list, item, prev, next)                   \
({  if ((list) != NULL) {                                       \
        __list_insert_at_left (list, list, item, prev, next);   \
        (list) = (item);                                        \
    }                                                           \
    else list_singleton (list, item, prev, next);               \
 })

#define list_add_tail(list, item, prev, next)                   \
({  if ((list) != NULL)                                         \
        __list_insert_at_left (list, list, item, prev, next);   \
    else list_singleton (list, item, prev, next);               \
 })

#define list_delete(list, item, prev, next)                     \
({  if ((item)->next == (item)) list_init (list, prev, next);   \
    else {                                                      \
        (item)->prev->next = (item)->next;                      \
        (item)->next->prev = (item)->prev;                      \
        if ((item) == (list)) (list) = (item)->next;            \
    }                                                           \
 })

#define list_pop_head(list, prev, next)                         \
({  typeof (list) __head_elt = (list);                          \
    if ((list) != NULL) list_delete (list, list, prev, next);   \
    __head_elt;                                                 \
 })

#define list_foreach_forward(list, iter, nb_elt, prev, next)        \
    for ((nb_elt) = 0, (iter) = (list);                             \
         ((iter) != NULL) && ((nb_elt == 0) || ((iter) != (list))); \
         (nb_elt)++, (iter) = (iter)->next)

#define list_foreach_backward(list, iter, nb_elt, prev, next)       \
    for ((nb_elt) = 0, (iter) = list_get_tail (list, prev, next);   \
         ((iter) != NULL) && ((nb_elt == 0) ||                      \
         ((iter) != list_get_tail (list, prev, next)));             \
         (nb_elt)++, (iter) = (iter)->prev)
                
#define list_foreach_f_early_break(list, iter, nb_elt, prev, next)  \
    ((list != NULL) && (((iter) != (list)) || (nb_elt == 0)))

#define list_foreach_b_early_break(list, iter, nb_elt, prev, next)      \
    ((list != NULL) && (((iter) != list_get_tail (list, prev, next))    \
    || (nb_elt == 0)))

#define list_collapse(list, iter, prev, next)                               \
    while ((iter) = (list),                                                 \
           ({ if ((list) != NULL) list_delete (list, list, prev, next); }), \
           ((iter) != NULL))

#endif /* _CROCOS_KLIBC_LIST_H */

