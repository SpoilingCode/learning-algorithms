
/*
 Примеры "неправильного" использования структуры pupil,
 но все же не всегда приводящие к падению программы. :-)
 */


#include "pupil.h"

void ring_list()
{
    pupil* p = pupil_new();
    //p->next = p; // после этого вывод списка зациклится
    //p->prev = p; // после этого вывод списка зациклится
    //pupil_insert_after(p,p); // и после этого тоже. в этом случае он зациклится еще внутри pupil_first не дойдя до вывода
    //pupil_insert_before(p,p);
    pupil_print_list(p);
    pupil_free(p);
}

int main()
{
    ring_list();
    return 1;
}