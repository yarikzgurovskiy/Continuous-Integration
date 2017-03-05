#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "list.h"
#include "students.h"

struct Student{
    char name[20];
    char surname[20];
    int age;
    float mark;
};

struct Teacher{
    char name[20];
    char surname[20];
    int age;
    char subject[20];
    List * students;
};

#define throw(MSG) assert(0 && MSG);

Teacher * Teacher_new(char * name, char * surname, int age, char *subject){
    Teacher * self = malloc(sizeof(Teacher));
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    self->age = age;
    strcpy(self->subject, subject);
    self->students = NULL;
    return self;
}

void Teacher_free(Teacher ** selfPtr){
    free(*selfPtr);
    *selfPtr = NULL;
}

Teacher * Teacher_attachStudents(Teacher *self, List * students){
    self->students = students;
    return self;
}

List * Teacher_getLowestScore(Teacher  *self, int count){
    if(count > List_count(self->students)) return NULL;
    List * studs = List_new();
    List * final = List_new();
    List * students = self->students;
    int i = 0;
    int j = 0;
    for(i = 0; i < List_count(students); i++){
        Student * st = List_get(students, i);
        Student * new = Student_new(st->name, st->surname, st->age, st->mark);
        List_addLast(studs, new); 
    }
    Student * min = NULL;
    
    for(j = 0; j < count; j++){
        int minIndex = 0;
        int len = List_count(studs);
        for(i = 1; i < len; i++){
            min = List_get(studs, minIndex);
            Student * curr = List_get(studs, i);
            if(curr->mark < min->mark){
                minIndex = i;
            }
        }
        Student * new = Student_new(min->name, min->surname, min->age, min->mark);
        List_addLast(final, new);
        Student_free(&min);
        List_removeAt(studs, minIndex);
    }
    //free additional memory
    freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
    return final;
}

List * Teacher_getStudents(Teacher * self){
    return self->students;
}

Student * Student_new(char * name, char * surname, int age, float mark){
    Student * self = malloc(sizeof(Student));
    strcpy(self->name, name);
    strcpy(self->surname, surname);
    self->age = age;
    self->mark = mark;
    return self;
}

Student * Student_newFromStringArray(char buffer[4][20]){
    Student * self = malloc(sizeof(Student));
    strcpy(self->name, buffer[0]);
    strcpy(self->surname, buffer[1]);
    self->age = atoi(buffer[2]);
    self->mark = atof(buffer[3]);
    return self;
}

void Student_free(Student ** selfPtr){
    free(*selfPtr);
    *selfPtr = NULL;
}

char * Student_toString(Student * self, char * str){
    sprintf(str,"%s,%s,%i,%.2f%c", self->name,self->surname, self->age, self->mark, '\0' );
    return str;
}

void freeAllStudents(List * self){
    int len = List_count(self);
    int i = 0; 
    for(i = 0; i < len; i++){
        Student * st = List_get(self, i);
        Student_free(&st);
    }
}
