

#include <stdio.h>

#ifndef PUPIL_H
#define PUPIL_H

typedef struct pupil {
    char *name;    // имя
	char *surname; // фамилия
	short age;     // возраст 
	short grade;   // номер курса
	struct pupil* next;   // следующий элемент
	struct pupil* prev;   // предыдущий элемент
} pupil;

// Какая либо фатальная ошибка работы со структурой
// Которая должна привести к завершению работы программы
void pupil_error(const char*);

// Предупреждение об ошибке, не приводящей к завершению работы программы
void pupil_warning(const char*);

// наш безопасный вариант сравнения строк, который может обрабатывать NULL как пустую строку
short pupil_strcmp(const char*, const char*);

// Производит лексическое сравнение двух студентов
// возвращает -1, 0 или 1, аналогично функции strcmp
short pupil_cmp(pupil*, pupil*);

// Выделяет память под нового студента
pupil* pupil_new();

// Освобождает память одной структуры
short pupil_free(pupil*);

void pupil_set_name(pupil*, const char*, short);

void pupil_set_surname(pupil*, const char*, short);


// Освобождает память, занятую всем списком, по указателю
// на любой его элемент
short pupil_free_list(pupil *);

// Вставляет новый элемент в список после текущего элемента
short pupil_insert_after(pupil* current, pupil* new_element);  

// Вставляет новый элемент в список перед текущим элементом
short pupil_insert_before(pupil* current, pupil* new_element);

// Вставляет новый элемент в список, считая что он отсортирован 
// по алфавиту (сначала фамилия, потом имя), так что список остается
// отсортированным по алфавиту. Если элемент с таким же именем и фамилией
// то он добавляется после последнего элемента
// Возвращает указатель на тот элемент, после которого он добавлен
pupil* pupil_insert_alphabetically(pupil* any_list_element, pupil* new_element);

// Выбросить элемент из списка, не освобождая память
// Просто расцепить указатели и вернуть указатель на следующий 
// элемент списка если он есть, либо на предыдущий, либо NULL
// если список состоит из одного элемента или если входной указатель NULL
// "Отчислить студента" :-D
pupil* pupil_remove(pupil *current);

// Находит указатель на первый элемент списка 
// Если список циклический, произойдет зацикливание
pupil* pupil_first(pupil*);

// Указатель на последний элемент списка.
pupil* pupil_last(pupil*);

// Лексическая сортировка списка 
// Возвращает указатель на первый элемент после сортировки
pupil* pupil_sort(pupil* current);

// Выводит на экран краткую инфу об одном студенте
void pupil_print(pupil*);

// Выводит на экран весь список, по ссылке на любой элемент
void pupil_print_list(pupil*);

#endif

