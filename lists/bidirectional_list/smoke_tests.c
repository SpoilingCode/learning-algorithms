
/* Примеры "правильного" использования структуры, когда
    ее элементы указатели на char* pupil* не трогаются явно,
    а модифицируются через функции библиотеки pupil_
   Понятное дело что можно и функциям передать неправильные
   указатели, но функции избавят нас по крайней-мере от самых
   тупых ошибок и кроме того с их использованием код будет
   более наглядным и легко модифицируемым. */
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

    pupil_set_name(p1, "Vasya", 0);
    compare_pupils_and_print(p1, p2);
    pupil_set_name(p2, "Vasya", 0);
    compare_pupils_and_print(p1, p2);
    pupil_set_name(p2, "Pavel", 0);
    compare_pupils_and_print(p1, p2);
    pupil_set_surname(p1, "Pupkin", 0);
    compare_pupils_and_print(p1, p2);
    pupil_set_surname(p2, "Ivanisenko", 0);
    compare_pupils_and_print(p1, p2);
}

void create_and_print_list()
{
    printf("\ncreate_and_print_list\n");
    pupil *l, *e;

    l = pupil_new();
    l->grade = 3;
    l->age = 21;
    pupil_set_name(l, "Vasya", 0);
    pupil_set_surname(l, "Pupkin", 0);
    pupil_print_list(l);

    e = pupil_new();
    e->grade = 2;
    e->age = 21;
    pupil_set_name(e, "Artur", 0);
    pupil_set_surname(e, "Testov", 0);
    pupil_insert_after(l, e);
    pupil_print_list(e);

    e = pupil_new();
    e->grade = 2;
    e->age = 21;
    pupil_set_name(e, "Filipp", 0);
    pupil_set_surname(e, "Testunov", 0);
    pupil_insert_before(l, e);
    pupil_print_list(e);

    pupil_remove(e);
    pupil_print_list(l);
    pupil_print_list(e);
    pupil_insert_after(l, e);
    pupil_print_list(e);

    printf("free %d list elements\n", pupil_free_list(e));
}

void insert_alphabetically()
{
    pupil *c, *p, *n;

    p = pupil_new();
    pupil_set_name(p, "a", 0);
    pupil_set_surname(p, "a", 0);
    
    c = pupil_new();
    pupil_set_name(c, "c", 0);
    pupil_set_surname(c, "c", 0);

    pupil_insert_after(p, c);

    p = pupil_new();
    pupil_set_name(p, "e", 0);
    pupil_set_surname(p, "e", 0);

    pupil_insert_after(c, p);

    pupil_print_list(c);

    n = pupil_new();
    pupil_set_name(n, "b", 0);
    pupil_set_surname(n, "b", 0);

    pupil_insert_alphabetically(c, n);
    pupil_print_list(c);

    n = pupil_new();
    pupil_set_name(n, "d", 0);
    pupil_set_surname(n, "d", 0);

    pupil_insert_alphabetically(pupil_first(c), n);
    pupil_print_list(c);
    n = pupil_new();
    pupil_set_name(n, "f", 0);
    pupil_set_surname(n, "f", 0);

    pupil_insert_alphabetically(pupil_first(c), n);
    pupil_print_list(c);

    n = pupil_new();
    pupil_set_name(n, "0", 0);
    pupil_set_surname(n, "0", 0);

    pupil_insert_alphabetically(pupil_last(c), n);
    pupil_print_list(c);

    printf("free %d list elements\n", pupil_free_list(c));
}

int main()
{
    create_and_print_pupil();
    compare_pupils();
    create_and_print_list();
    insert_alphabetically();
    return 1;
}