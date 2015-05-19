
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bidirectional_list.h"

// Для разнообразия проверим алгоритм сортировки не на учениках, а на обычных строках char*
short my_strcmp(void* s1, void* s2) {

    short cmp = 0;
    if (s1 == NULL && s2 == NULL) {
        return 0;
    } else if (s1 == NULL) {
        return -1;
    } else if (s2 == NULL) {
        return  1;
    } else {
        cmp = strcmp(s1, s2);
        return (cmp > 0 ? 1 : (cmp < 0 ? -1 : 0));
    }
}

char * my_make_string(const char * in) {

    if (in == NULL) {
        return NULL;
    }
    short len = strlen(in);
    char *p = (char*) malloc((len + 1) * sizeof(char));
    if (p == NULL) {
        printf("my_make_string: memory allocation error for string length: %d\n", len);
        exit(-1);
    }
    strncpy(p, in, len);
    *(p + len + 1) = '\0';
    return p;
}

// На всякий случай для контроля утечек памяти определим свой free с дебагом
void my_free_string(char *p)
{
    if (p == NULL) {
        return;
    }
    printf("free string: %s\n", p);
    free(p);
    p = NULL;
}

void my_print_string(void *str)
{
    char *s;
    if (str == NULL) {
        printf("<null string>\n");
        return;
    }
    s = (char*) str;
    printf("%s\n", s);
}

int main()
{
    bidirectional_list *first = bidirectional_list_new(my_make_string("z"));
    bidirectional_list_insert_after(first, bidirectional_list_new(my_make_string("y")));
    bidirectional_list_insert_after(
        bidirectional_list_last(first),
        bidirectional_list_new(my_make_string("x"))
    );
    bidirectional_list_insert_after(
        bidirectional_list_last(first),
        bidirectional_list_new(my_make_string("x"))
    );
    bidirectional_list_insert_after(
        bidirectional_list_last(first), 
        bidirectional_list_new(my_make_string("c"))
    );
    bidirectional_list_insert_after(
        bidirectional_list_last(first), 
        bidirectional_list_new(my_make_string("a"))
    );
    bidirectional_list_insert_after(
        bidirectional_list_last(first), 
        bidirectional_list_new(my_make_string("b"))
    );

    printf("Before sorting:\n");
    bidirectional_list_each(first, my_print_string);
    bidirectional_list_insertion_sort(first, my_strcmp, my_print_string);
    printf("After sorting:\n");
    bidirectional_list_each(first, my_print_string);
    printf("Starting free all:\n");
    bidirectional_list_free_all(first, my_free_string);
    return 0;
}
