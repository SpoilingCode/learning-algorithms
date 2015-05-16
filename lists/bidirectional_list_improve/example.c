
#include <stdio.h>

#include "bidirectional_list.h"
#include "pupil.h"


int main() {

    bidirectional_list *list;
    pupil *p = NULL;

    list = bidirectional_list_new(pupil_new());
    pupil_set_name(list->element, "Pavel", 0);
    pupil_set_surname(list->element, "Ivanisenko", 0);

    p = pupil_new();
    pupil_set_name(p, "Roman", 0);
    pupil_set_surname(p, "Ivanisenko", 0);
    bidirectional_list_insert_after(list, bidirectional_list_new(p));

    bidirectional_list_each(list, pupil_print);

    bidirectional_list_free_all(list, pupil_free);

    return 0;
}
