#ifndef LIST_H
#define LIST_H
typedef struct List List;
typedef struct ListNode ListNode;

List * List_new(void);  //list constructor
void List_free(List ** self); //list destructor
void List_freeAllNodes(List * self);

int List_count(List * self);
void * List_get(List * self, int position);

ListNode * ListNode_new(void *ref); //node constructor
void ListNode_free(ListNode ** self); //node destructor

void List_addLast(List * self, void * ref);
void List_removeFirst(List * self);
void List_removeLast(List * self);
void List_removeAt(List * self, int position);
#endif //LIST_H