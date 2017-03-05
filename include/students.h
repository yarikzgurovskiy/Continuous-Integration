#ifndef STUDENTS_H
#define STUDENTS_H
#include "list.h"

typedef struct Student Student;
typedef struct Teacher Teacher;

Student * Student_new(char * name, char * surname, int age, float mark);
Student * Student_newFromStringArray(char buffer[4][20]);
void Student_free(Student ** selfPtr);

char * Student_toString(Student * self, char * str);

Teacher * Teacher_new(char * name, char * surname, int age, char *subject);
void Teacher_free(Teacher ** selfPtr);

Teacher * Teacher_attachStudents(Teacher *self, List * students);
List * Teacher_getLowestScore(Teacher  *self, int count);
List * Teacher_getStudents(Teacher * self);

void freeAllStudents(List * self);

#endif //STUDENTS_H