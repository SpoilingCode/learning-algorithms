

#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H


typedef struct  {
    void *element; // Элементы, которые хранятся в контейнере
                   // В нашем случае это будут указатели на pupil
} bidirectional_list_container;

typedef struct bidirectional_list {
    bidirectional_list_container *container;
    struct bidirectional_list *next;
    struct bidirectional_list *prev;
} bidirectional_list;

bidirectional_list* bidirectional_list_new(void *);
void bidirectional_list_free(bidirectional_list *, void ((*element_free)(void *)));


void bidirectional_list_insertion_sort(bidirectional_list* any_element,
        short ((*cmp)(void*, void*))); // указатель на функцию сравнения

#endif 