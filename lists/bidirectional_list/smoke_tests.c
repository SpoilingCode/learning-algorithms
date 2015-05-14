

#include "pupil.h"

void create_and_print_pupil()
{
    printf("\ncreate_and_print_element\n");
    pupil_print(NULL);
    
    pupil* p = pupil_new();
    pupil_print(p);

    pupil_set_name(p, "Pavel", 0);
    pupil_set_surname(p, "Ivanisenko", 0);
    p->grade = 100;
    p->age = 29;
    pupil_print(p);

    pupil_set_name(p, "", 0);
    pupil_print(p);

    pupil_set_surname(p, "", 0);
    pupil_print(p);

    pupil_set_name(p, NULL, 0);
    pupil_print(p);

    p->age = 19;
    p->grade = 1;
    pupil_set_name(p, "Roman", 4);
    pupil_print(p);
    

    pupil_set_name(p, "Roman", 10);
    pupil_print(p);

    pupil_free(p);
    pupil_print(p);
}

void compare_pupils_and_print(pupil *p1, pupil *p2)
{
    printf("compare pupils: (\n");
    pupil_print(p1);
    pupil_print(p2);
    printf(") result = %d\n", pupil_cmp(p1, p2));
}

void compare_pupils()
{
    printf("\ncompare_pupils\n");

    compare_pupils_and_print(NULL, NULL);
    
    pupil *p1 = pupil_new();
    pupil *p2 = pupil_new();

    compare_pupils_and_print(p1, NULL);
    compare_pupils_and_print(NULL, p2);
    compare_pupils_and_print(p1, p2);
}

int main()
{
    create_and_print_pupil();
    compare_pupils();
    return 1;
}