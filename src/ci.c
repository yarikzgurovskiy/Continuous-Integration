#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "ci.h"

struct Student{
    char name[20];
    char surname[20];
    int age;
    float mark;
};

struct ListNode{
    ListNode * next;
    void * data;
};

struct List{
    ListNode * head;
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
    int i;
    int j;
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
    Student_freeAll(studs);
    List_clean(studs);
    List_free(&studs);
    return final;
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

void Student_freeAll(List * self){
    int len = List_count(self);
    int i; 
    for(i = 0; i < len; i++){
        Student * st = List_get(self, i);
        Student_free(&st);
    }
}

void Student_print(Student * self){
    printf("Name: %s\nSurname: %s\nAge: %i\nMark: %f\n",
    self->name, 
    self->surname, 
    self->age, 
    self->mark);
}

char * Student_toString(Student * self, char * str){
    sprintf(str,"%s,%s,%i,%f%c", self->name,self->surname, self->age, self->mark, '\0' );
    return str;
}

List * CsvToList(char * str){
    List * newList = List_new();
    char buffer[4][20];
    int word = 0;;
    int wordIndex = 0;
    int i;
    for(i = 0; i <= strlen(str); i++){
        char ch = str[i];
        if(isspace(ch) && ch != '\n'){
            continue;
        }else if(ch == ','){
            buffer[word][wordIndex] = '\0';
            word++;
            wordIndex = 0; 
        } else if(ch == '\n' || ch == '\0'){
            buffer[word][wordIndex] = '\0';
            word = 0;
            wordIndex = 0;
            Student * stud = Student_newFromStringArray(buffer);
            List_addLast(newList, stud);
        } else {
            buffer[word][wordIndex] = ch;
            wordIndex++;
        }
    }
    return newList;
}

char * ListToCsv(char * str, List * self){
    sprintf(str, "%c", '\0');
    char sign[2];
    sprintf(sign, "%c", '\n');
    int len = List_count(self);
    int i;
    for(i = 0; i < len; i++){
        char buf[50];
        Student_toString(List_get(self, i), buf);
        strcat(str, buf);
        if(i == len - 1) sprintf(sign, "%c" ,'\0');
        strcat(str, sign);
    }
    return str;
}

struct List * List_new(void) {
    struct List * list = (struct List *)malloc(sizeof(struct List));
    list->head = NULL;
    return list;
}

void List_free(List ** self) {
    assert(NULL != self);
    free(*self);
    *self = NULL;
}

struct ListNode * ListNode_new(void * data) {
    struct ListNode * node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->data = data;
    return node;
}

void ListNode_free(struct ListNode ** self) {
    assert(NULL != self);
    free(*self);
    *self = NULL;
}

void List_addLast(struct List * self, void * data) {
    struct ListNode * node = ListNode_new(data);
    if (self->head == NULL) {
          self->head = node;
          return;
    }
    struct ListNode * cur = self->head;
    while (cur->next != NULL) {
          cur = cur->next;
    }
    cur->next = node;
}

int List_count(List * self){
    ListNode * curr = self->head;
    int count = 0;
    while(curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

void List_removeFirst(struct List * self) {
    struct ListNode * node = self->head;
    if (node == NULL) return;
    self->head = node->next;
    ListNode_free(&node);
}
void List_removeLast(struct List * self) {
    struct ListNode * cur = self->head;
    if (cur == NULL) return;
    if (cur->next == NULL) {
          ListNode_free(&cur);
          self->head = NULL;
          return;
    }
    while (cur->next->next != NULL) {
          cur = cur->next;
    }
    ListNode_free(&(cur->next));
    cur->next = NULL;
}
void List_removeAt(struct List * self, int position) {
    if(position == 0) {
        List_removeFirst(self);
        return;
    }
    int i = 0;
    struct ListNode * cur = self->head;
    while (cur->next->next != NULL && i != position - 1) {
          i += 1;
          cur = cur->next;
    }
    if (i != position - 1) assert(0);
    struct ListNode * node = cur->next;
    cur->next = node->next;
    ListNode_free(&node);
}

void * List_get(List * self, int position){
    int len = List_count(self);
    if(position >= len || position < 0) throw("Index out of bounds!");
    ListNode * curr = self->head;
    int i;
    for(i = 0; i < len; i++){
        if(position == i) break;
        curr = curr->next;
    }
    return curr->data;
}

void List_clean(List * self){
    int len = List_count(self);
    int i;
    for(i = 0; i < len; i++){
        ListNode * curr = self->head;
        if(curr == NULL) return;
        if(curr->next == NULL){
            ListNode_free(&curr);
            self->head = NULL;
            return;
        }
        while(curr->next->next != NULL){
            curr = curr->next;
        }
        ListNode_free(&(curr->next));
        curr->next = NULL;
    }
}
