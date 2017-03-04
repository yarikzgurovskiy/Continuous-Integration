#ifndef CI_H
#define CI_H
typedef struct Student Student;
typedef struct Teacher Teacher;
typedef struct List List;
typedef struct ListNode ListNode;

struct List * List_new(void);  //list constructor
void List_free(List ** self); //list destructor
void List_freeAllNodes(List * self);
void List_freeAllStudents(List * self);

struct ListNode * ListNode_new(void *ref); //node constructor
void ListNode_free(ListNode ** self); //node destructor

void List_addLast(List * self, void * ref);
void List_removeFirst(List * self);
void List_removeLast(List * self);
void List_removeAt(List * self, int position);

int List_count(List * self);
void * List_get(List * self, int position);

Student * Student_new(char * name, char * surname, int age, float mark);
Student * Student_newFromStringArray(char buffer[4][20]);
void Student_free(Student ** selfPtr);

char * Student_toString(Student * self, char * str);

Teacher * Teacher_new(char * name, char * surname, int age, char *subject);
void Teacher_free(Teacher ** selfPtr);

Teacher * Teacher_attachStudents(Teacher *self, List * students);
List * Teacher_getLowestScore(Teacher  *self, int count);

List * CsvToList(char * str);
char * ListToCsv(char * str, List * self);

#endif