

#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H


typedef struct bidirectional_list {
    void* element;
    struct bidirectional_list *next;
    struct bidirectional_list *prev;
} bidirectional_list;

void bidirectional_list_error(const char *);

void bidirectional_list_warning(const char *);

bidirectional_list* bidirectional_list_new(void *);

void bidirectional_list_free(bidirectional_list *);

void bidirectional_list_free_all(bidirectional_list *, void ((*element_free)()));

void bidirectional_list_insert_after(bidirectional_list *, bidirectional_list *);

void bidirectional_list_insert_before(bidirectional_list *, bidirectional_list *);

void bidirectional_list_remove(bidirectional_list *);

bidirectional_list* bidirectional_list_first(bidirectional_list *);

bidirectional_list* bidirectional_list_last(bidirectional_list *);

void bidirectional_list_each(bidirectional_list* e, void ((*callback)()));

void bidirectional_list_insertion_sort(bidirectional_list* any_element,
        short ((*cmp)(void*, void*))); // указатель на функцию сравнения

#endif 