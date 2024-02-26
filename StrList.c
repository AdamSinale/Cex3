#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _Node{
    char *_data;
    struct _Node *_next;
}Node;

typedef struct _StrList{
    Node *_head;
    size_t _size;
}StrList;

Node* Node_alloc(const char* data, Node* next){
    Node *node = (Node*)malloc(sizeof(Node));
    if(node!=NULL){
        node->_data = strdup(data);
        node->_next = next;
    }
    return node;
}
StrList* StrList_alloc(){
    StrList *list = (StrList*)malloc(sizeof(StrList));
    list->_head = NULL;
    list->_size = 0;
    return list;
}

void Node_free(Node* node) {
	free(node->_data);
	free(node);
}
void StrList_free(StrList* StrList){
    Node* curr = StrList->_head;
    while (curr != NULL) {
        Node* toDelete = curr;
        curr = curr->_next;
        Node_free(toDelete);
    }
    StrList->_head = NULL;
}

size_t StrList_size(const StrList* StrList){  
   return StrList ? StrList->_size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data){
     StrList_insertAt(StrList, data, StrList->_size);
}

void StrList_insertAt(StrList* StrList, const char* data,int index){
    if(index < 0 || index > StrList->_size){ return; }
    if(index == 0 ){
        Node* newNode = Node_alloc(data, StrList->_head);
        StrList->_head = newNode;
    }else{
        Node* curNode = StrList->_head;
        for(int i=0; i<index-1; i++){ curNode = curNode->_next; }
        Node* newNode = Node_alloc(data, curNode->_next);
        curNode->_next = newNode;
    }
    StrList->_size++;
}

char* StrList_firstData(const StrList* StrList){
    if(StrList->_head == NULL){ return NULL; }
    return StrList->_head->_data;
}

void StrList_print(const StrList* StrList){
    Node* curNode = StrList->_head;
    if(curNode != NULL){
        while (curNode->_next != NULL){
            printf("%s ", curNode->_data);
            curNode = curNode->_next;
        }
        printf("%s", curNode->_data);
    }
    printf("\n");
}

void StrList_printAt(const StrList* Strlist,int index){
    if(index < 0 || index >= Strlist->_size){ return; }
    Node* curNode = Strlist->_head;
    for(int i=0; i<index; i++){ curNode = curNode->_next; }
    printf("%s\n", curNode->_data);
}

int StrList_printLen(const StrList* Strlist){
    int count=0;
    Node* curNode = Strlist->_head;
    while (curNode != NULL){ 
        count += strlen(curNode->_data);
        curNode = curNode->_next; 
    }
    return count;
}

int StrList_count(StrList* StrList, const char* data){
    int count=0;
    Node* curNode = StrList->_head;
    while (curNode != NULL){ 
        if(strcmp(curNode->_data,data) == 0){ count ++; }
        curNode = curNode->_next; 
    }
    return count;
}

void StrList_remove(StrList* StrList, const char* data){
    Node* curNode = StrList->_head;
    while(curNode != NULL && strcmp(curNode->_data,data) == 0){
        Node_free(curNode);
        curNode = curNode->_next;
        StrList->_size--; 
    }
    StrList->_head = curNode;
    while (curNode->_next != NULL){ 
        if(strcmp(curNode->_next->_data,data) == 0){ 
            Node* free = curNode->_next;
            curNode->_next = curNode->_next->_next;
            Node_free(free);
            StrList->_size--; 
        }
        curNode = curNode->_next; 
    }
}

void StrList_removeAt(StrList* StrList, int index){
    if(index < 0 || index >= StrList->_size){ return; }
    Node* curNode = StrList->_head;
    if(index == 0){
        StrList->_head = curNode->_next;
        Node_free(curNode);
    }
    else{
        for(int i=0; i<index-1; i++){ curNode = curNode->_next; }
        Node* free = curNode->_next;
        curNode->_next = curNode->_next->_next;
        Node_free(free);
    }
    StrList->_size--; 
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1->_size != StrList2->_size){ return FALSE; }
    Node* curNode1 = StrList1->_head;
    Node* curNode2 = StrList2->_head;
    for(int i=0; i<StrList1->_size; i++){
        if(strcmp(curNode1->_data,curNode1->_data) != 0){
            return FALSE;
        }
        curNode1 = curNode1->_next;
        curNode2 = curNode2->_next;
    }
    return TRUE;
}

StrList* StrList_clone(const StrList* Strlist){
    StrList* clone = StrList_alloc();
    Node* curNode = Strlist->_head;
    while(curNode != NULL){
        StrList_insertLast(clone, curNode->_data);
        curNode = curNode->_next;
    }
    return clone;
}

void StrList_reverse(StrList* list) {
    Node *prev = NULL, *current = list->_head, *next = NULL;
    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }
    list->_head = prev;
}

void StrList_sort(StrList* list) {
    if (list->_head == NULL || list->_head->_next == NULL) { return; }
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = list->_head;

        while (ptr1->_next != lptr) {
            if (strcmp(ptr1->_data, ptr1->_next->_data) > 0) {
                char* temp = ptr1->_data;
                ptr1->_data = ptr1->_next->_data;
                ptr1->_next->_data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->_next;
        }
        lptr = ptr1;
    } while (swapped);
}

int StrList_isSorted(StrList* StrList){
    if(StrList->_size < 2){ return TRUE; }
    Node* curNode = StrList->_head;
    while (curNode->_next != NULL){
        if(strcmp(curNode->_data, curNode->_next->_data) > 0){
            return FALSE;
        }
        curNode = curNode->_next;
    }
    return TRUE;
}
