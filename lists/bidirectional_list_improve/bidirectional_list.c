
#include "bidirectional_list.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef BIDIRECTIONAL_LIST_C
#define BIDIRECTIONAL_LIST_C

void bidirectional_list_error(const char *message)
{
    printf("bidirectional_list error: ");
    if (message == NULL) {
        printf("NULL");
    } else {
        printf("%s", message);
    }
    exit(-1);
}

void bidirectional_list_warning(const char *message)
{
    printf("bidirectional_list warning: ");
    if (message == NULL) {
        printf("NULL");
    } else {
        printf("%s", message);
    }
}

bidirectional_list* bidirectional_list_new(void *element)
{
    bidirectional_list *p = (bidirectional_list*) malloc(sizeof(bidirectional_list));
    if (p == NULL) {
        bidirectional_list_error("Can't allocate memory for bidirectional_list structure\n");
    }
    p->element = element;
    return p;
}

void bidirectional_list_free(bidirectional_list *e)
{
    if (e == NULL) {
        return;
    }
    if (e->element != NULL) {
        bidirectional_list_warning("bidirectional_list_free: element at container is not null");
    }
    free(e);
}

void bidirectional_list_free_all(bidirectional_list *e, void ((*element_free)()))
{
    bidirectional_list* first = bidirectional_list_first(e);
    bidirectional_list *next, *current;
    if (first == NULL) {
        return;
    }

    next = first;
    while(next != NULL) {
        if (element_free != NULL && next->element != NULL) {
            element_free(next->element);
        }
        current = next;
        next = next->next;
        current->element = NULL;
        bidirectional_list_free(current);
    }
}

void bidirectional_list_insert_after(bidirectional_list * blist, bidirectional_list *e)
{
    if (blist == NULL) {
        bidirectional_list_warning("bidirectional_list_insert_after: Can't insert after NULL\n");
        return;
    }
    if (e == NULL) {
        bidirectional_list_warning("bidirectional_list_insert_after: Can't insert NULL\n");
        return;
    }
    e->next = blist->next;
    e->prev = blist;
    blist->next = e;
    if (e->next != NULL) {
        e->next->prev = e;
    }
}

void bidirectional_list_insert_before(bidirectional_list *blist, bidirectional_list *e)
{
    if (blist == NULL) {
        bidirectional_list_warning("bidirectional_list_insert_before: Can't insert before NULL\n");
        return;
    }
    if (e == NULL) {
        bidirectional_list_warning("bidirectional_list_insert_before: Can't insert NULL\n");
        return;
    }
    e->prev = blist->prev;
    e->next = blist;
    blist->prev = e;
    if (e->prev != NULL) {
        e->prev->next = e;
    }
}

void bidirectional_list_remove(bidirectional_list *e)
{
    if (e == NULL) {
        return;
    }
    bidirectional_list *p;
    bidirectional_list *n;
    if (e == NULL) {
        return;
    }
    n = e->next;
    p = e->prev;
    if (n == NULL && p == NULL) {
        return;
    } else if (p == NULL) {
        n->prev = NULL;
        e->next = NULL;
        return;
    } else if (n == NULL) {
        p->next = NULL;
        e->prev = NULL;
        return;
    } else {
        p->next = n;
        n->prev = p;
        e->next = NULL;
        e->prev = NULL;
        return;
    }
}

bidirectional_list* bidirectional_list_first(bidirectional_list *e)
{
    if (e == NULL) {
        return NULL;
    }
    bidirectional_list *current = e;
    while(current->prev != NULL) {
        current = current->prev;
    }
    return current;
}

bidirectional_list* bidirectional_list_last(bidirectional_list *e)
{
    if (e == NULL) {
        return NULL;
    }
    bidirectional_list *current = e;
    while(current->next != NULL) {
        current = current->next;
    }
    return current;
}

void bidirectional_list_each(bidirectional_list* e, void ((*callback)()))
{
    bidirectional_list* first = bidirectional_list_first(e);
    bidirectional_list *next;
    if (first == NULL) {
        return;
    }
    if (callback == NULL) {
        return;
    }

    next = first;
    while(next != NULL) {
        
        if (next->element != NULL) {
            callback(next->element);
        }
        next = next->next;
    }
}

void bidirectional_list_insertion_sort(bidirectional_list* any_element,
        short ((*cmp)(void*, void*)), void ((*printfunc)()))
{
    bidirectional_list *first = bidirectional_list_first(any_element);
    if (first == NULL) {
        return;
    }
    if (cmp == NULL) {
        return;
    }
    bidirectional_list *cursor = first; // Указатель на начало неотсортированной части списка
    bidirectional_list *sorted, *item;
    while (cursor != NULL) {

        //printf("Main loop: cursor: ");
        //printfunc(cursor->element);
        item = cursor->prev;
        if (item == NULL) {
            cursor = cursor->next;
            continue;
        }
        sorted = item->prev;
        if (sorted == NULL) {
            cursor = cursor->next;
            continue;
        }
        bidirectional_list_remove(item);
        while (sorted != NULL) {

            //printf("Inner loop: cursor: ");
            //printfunc(cursor->element);
            //printf("item: ");
            //printfunc(item->element);
            //printf("sorted: ");
            //printfunc(sorted->element);
            if (cmp(sorted->element, item->element) < 0) {
                //printf("Inserting after: sorted => item: \n");
                //printfunc(sorted->element);
                //printfunc(item->element);
                bidirectional_list_insert_after(sorted, item);
                cursor = cursor->next;
                break;
            }
            if (sorted->prev == NULL) {
                //printf("Inserting before: sorted => item: \n");
                //printfunc(sorted->element);
                //printfunc(item->element);
                bidirectional_list_insert_before(sorted, item);
                cursor = cursor->next;
                break;
            }
            sorted = sorted->prev;
        }
    }

    item = bidirectional_list_last(first);
    if (item == NULL) {
        return;
    }
    sorted = item->prev;
    bidirectional_list_remove(item);
    while (sorted != NULL) {

        //printf("Last loop: item: ");
        //printfunc(item->element);
        //printf("sorted: ");
        //printfunc(sorted->element);
        if (cmp(sorted->element, item->element) < 0) {
            //printf("Inserting after: sorted => item: \n");
            //printfunc(sorted->element);
            //printfunc(item->element);
            bidirectional_list_insert_after(sorted, item);
            break;
        }
        if (sorted->prev == NULL) {
            //printf("Inserting before: sorted => item: \n");
            //printfunc(sorted->element);
            //printfunc(item->element);
            bidirectional_list_insert_before(sorted, item);
            break;
        }
        sorted = sorted->prev;
    }
}

#endif

