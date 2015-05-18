

#ifndef PUPIL_H
#define PUPIL_H

typedef struct {
    char *name;    // имя
	char *surname; // фамилия
	short age;     // возраст
	short grade;   // номер курса
} pupil;

void pupil_error(const char*);

void pupil_warning(const char*);

short pupil_strcmp(const char*, const char*);

short pupil_cmp(pupil*, pupil*);

pupil* pupil_new();

void pupil_free(pupil*);

void pupil_set_name(pupil*, const char*, short);

void pupil_set_surname(pupil*, const char*, short);

void pupil_print(pupil*);

#endif 