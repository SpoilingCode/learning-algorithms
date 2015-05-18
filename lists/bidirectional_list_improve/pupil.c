
#include "pupil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (cmp > 0) {
            return 1;
        } else if (cmp < 0) {
            return -1;
        } else {
            cmp = pupil_strcmp(p1->name, p2->name);
            if (cmp > 0) {
                return 1;
            } else if (cmp < 0) {
                return -1;
            } else {
                return 0;
            }
        }
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

void pupil_free(pupil* p)
{
    if (p == NULL) {
        return;
    }
    if (p->name != NULL) {
        free(p->name);
        p->name = NULL;
    }
    if (p->surname != NULL) {
        free(p->surname);
        p->surname = NULL;
    }
    free(p);
}


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
    p->name = (char*) malloc((chars + 1)*sizeof(char));
    if (p->name == NULL) {
        pupil_error("Can't allocate memory for pupil->name\n");
    }
    strncpy(p->name, name, chars);
    *(p->name + chars) = '\0';
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
    p->surname = (char*) malloc((chars + 1)*sizeof(char));
    if (p->surname == NULL) {
        pupil_error("Can't allocate memory for pupil->surname\n");
    }
    strncpy(p->surname, surname, chars);
    *(p->surname + chars) = '\0';
}

void pupil_print(pupil* p)
{
    if (p == NULL) {
        pupil_warning("pupil_print: NULL\n");
        return;
    }
    printf("%s %s (grade: %d, age: %d)\n", p->surname, p->name, p->grade, p->age);
}


#endif