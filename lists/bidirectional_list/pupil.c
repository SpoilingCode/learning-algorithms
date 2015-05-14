
#include <stdlib.h>
#include <string.h>
#include "pupil.h"

#ifndef PUPIL_C
#define PUPIL_C

void pupil_error(const char* message) 
{
    printf("pupil error: ");
    if (message == NULL) {
        printf("NULL");
    } else {
        printf("%s", message);
    }
    exit(-1);
}


void pupil_warning(const char* message)
{
    printf("pupil warning: ");
    if (message == NULL) {
        printf("NULL");
    } else {
        printf("%s", message);
    }
}

short pupil_strcmp(const char* s1, const char* s2)
{
    if (s1 == NULL) {
        pupil_warning("pupil_strcmp: left operand is null\n");
    }
    if (s2 == NULL) {
        pupil_warning("pupil_strcmp: right operand is null\n");
    }
    if (s1 == NULL && s2 == NULL) {
        return 0;
    } else if (s1 == NULL) {
        return -1;
    } else if (s2 == NULL) {
        return 1;
    } else {
        return strcmp(s1, s2);
    }
}

short pupil_cmp(pupil* p1, pupil* p2)
{
    short cmp;
    if (p1 == NULL) {
        pupil_warning("pupil_cmp: left operand is null\n");
    }
    if (p2 == NULL) {
        pupil_warning("pupil_cmp: right operand is null\n");
    }
    if (p1 == NULL && p2 == NULL) {
        return 0;
    } else if (p1 == NULL) {
        return -1;
    } else if (p2 == NULL) {
        return 1;
    } else {

        cmp = pupil_strcmp(p1->surname, p2->surname);
        return (cmp == 0 ? pupil_strcmp(p1->name, p2->name) : cmp);
    }
}

pupil* pupil_new()
{

    pupil* p = (pupil*) malloc(sizeof(pupil));
    if (p == NULL) {
        pupil_error("Can't allocate memory for pupil structure\n");
    }
    p->name = NULL;
    p->surname = NULL;
    p->age = 0;
    p->grade = 0;
    return p;
}

short pupil_free(pupil* p)
{
    if (p == NULL) {
        return 0;
    }
    p->next = NULL;
    p->prev = NULL;
    if (p->name != NULL) {
        free(p->name);
        p->name = NULL;
    }
    if (p->surname != NULL) {
        free(p->surname);
        p->surname = NULL;
    }
    free(p);
    return 1;
}

/*
 Вызов pupil_set_name(p, NULL, 0); освобождает память под имя студента
 Вызов pupil_set_name(p, '', 0); не делает ничего
 Вызов pupil_set_name(p, name, maxlength); maxlength > 0
 копирует в имя студента не более maxlength символов
 если maxlength = 0 => копирует всю строку в имя
 */
void pupil_set_name(pupil* p, const char* name, short maxlength)
{
    short len = 0, chars = 0;
    if (p == NULL) {
        pupil_warning("Can't set name on NULL pupil\n");
        printf("name: %s", name);
        return;
    }
    if (name == NULL) {

        if (p->name != NULL) {
            free(p->name);
            p->name = NULL;
        }
        return;
    }
    len = strlen(name);
    if (len <= 0) {
        return;
    }
    chars = (maxlength > 0 && len > maxlength ? maxlength : len);
    if (p->name != NULL) {
        free(p->name);
        p->name = NULL;
    }
    p->name = (char*) malloc(chars*sizeof(char));
    if (p->name == NULL) {
        pupil_error("Can't allocate memory for pupil->name\n");
    }
    strncpy(p->name, name, chars);
}

void pupil_set_surname(pupil* p, const char* surname, short maxlength)
{
    short len = 0, chars = 0;
    if (p == NULL) {
        pupil_warning("Can't set surname on NULL pupil\n");
        printf("surname: %s\n", surname);
        return;
    }
    if (surname == NULL) {

        if (p->surname != NULL) {
            free(p->surname);
            p->surname = NULL;
        }
        return;
    }
    len = strlen(surname);
    if (len <= 0) {
        return;
    }
    chars = (maxlength > 0 && len > maxlength ? maxlength : len);
    if (p->surname != NULL) {
        free(p->surname);
        p->surname = NULL;
    }
    p->surname = (char*) malloc(chars*sizeof(char));
    if (p->surname == NULL) {
        pupil_error("Can't allocate memory for pupil->surname\n");
    }
    strncpy(p->surname, surname, chars);
}

short pupil_free_list(pupil *p)
{
    pupil* var;
    pupil* first = pupil_first(p);
    short count = 0;
    while (first != NULL) {

        var = first->next;
        count += pupil_free(first);
        first = var;
    }
    return count;
}

short pupil_insert_after(pupil* current, pupil* new_element)
{
    if (current == NULL) {
        pupil_warning("pupil_insert_after: Can't insert after NULL\n");
        return 0;
    }
    if (new_element == NULL) {
        pupil_warning("pupil_insert_after: Can't insert NULL\n");
        return 0;
    }
    new_element->next = current->next;
    new_element->prev = current;
    current->next = new_element;
    if (new_element->next != NULL) {
        new_element->next->prev = new_element;
    }
    return 1;
}

short pupil_insert_before(pupil* current, pupil* new_element)
{
    if (current == NULL) {
        pupil_warning("pupil_insert_before: Can't insert before NULL\n");
        return 0;
    }
    if (new_element == NULL) {
        pupil_warning("pupil_insert_before: Can't insert NULL\n");
        return 0;
    }
    new_element->prev = current->prev;
    new_element->next = current;
    current->prev = new_element;
    if (new_element->prev != NULL) {
        new_element->prev->next = new_element;
    }
    return 1;
}

// Вставляет новый элемент в список, считая что он отсортирован 
// по алфавиту (сначала фамилия, потом имя), так что список остается
// отсортированным по алфавиту. Если элемент с таким же именем и фамилией
// то он добавляется после последнего элемента
// Возвращает указатель на тот элемент, после которого он добавлен
pupil* pupil_insert_alphabetically(pupil* any_list_element, pupil* new_element)
{
    return NULL;
}

// Выбросить элемент из списка, не освобождая память
// Просто расцепить указатели и вернуть указатель на следующий
// элемент списка если он есть, либо на предыдущий если его нет, либо NULL
// если список состоит из одного элемента или если входной указатель NULL
// "Отчислить студента" :-D
pupil* pupil_remove(pupil *current)
{
    pupil *p;
    pupil* n;
    if (current == NULL) {
        return NULL;
    }
    n = current->next;
    p = current->prev;
    if (n == NULL && p == NULL) {
        return NULL;
    } else if (p == NULL) {
        n->prev = NULL;
        current->next = NULL;
        return n;
    } else if (n == NULL) {
        p->next = NULL;
        current->prev = NULL;
        return p;
    } else {
        p->next = n;
        n->prev = p;
        current->next = NULL;
        current->prev = NULL;
        return n;
    }
}

pupil* pupil_first(pupil *p)
{
    pupil *current;
    if (p == NULL) {
        return NULL;
    }
    current = p;
    while(current->prev != NULL) {
        current = current->prev;
    }
    return current;
}

pupil* pupil_last(pupil *p)
{
    pupil *current;
    if (p == NULL) {
        return NULL;
    }
    current = p;
    while(current->next != NULL) {
        current = current->next;
    }
    return current;
}

void pupil_print(pupil* p)
{
    if (p == NULL) {
        pupil_warning("pupil_print: NULL\n");
        return;
    }
    printf("%s %s (grade: %d, age: %d)\n", p->surname, p->name, p->grade, p->age);
}

void pupil_print_list(pupil* p)
{
    pupil *first = pupil_first(p);
    while (first != NULL) {

        pupil_print(first);
        printf("\n");
        first = first->next;
    }
}

pupil* pupil_sort(pupil* current)
{
    return NULL;
}

#endif
