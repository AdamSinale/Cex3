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
    
     Node* ptr = StrList->_head;
     Node* prev = NULL;
     
     while(ptr != NULL){
     
     if(strcmp(ptr->_data, data) == 0){ // Check if the data in the current node matches the given string
         if(prev == NULL){      //when the node is the head
             StrList->_head = ptr->_next;
         }
         else{
           prev->_next = ptr->_next;
         }
        // Free the memory allocated for the matched node
        Node* temp = ptr;
         ptr= ptr->_next;
         free(temp);
         StrList->_size --;
     } 
     else{ // No match found
         prev = ptr;
         ptr = ptr->_next;
       }
     }
}

/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    
    
     if (StrList->_head == NULL) {
        return;
    }
    if (index < 0 || index >= StrList->_size){
        return; // Invalid index or index out of bounds
    }
    Node* prev = NULL;
    Node* ptr = StrList->_head;
    for (int i = 0; i < index; i++) {
        
        prev = ptr;
        ptr = ptr->_next;
    }
    
     if(prev == NULL){      //when the node is the head
             StrList->_head = ptr->_next;
     }
     
     else{
           prev->_next = ptr->_next;
         }
         free(ptr);
         StrList->_size --;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    
    if (StrList1->_size != StrList2->_size) {
        return 0; // Lists are not equal
    }
    
    Node* ptr1 = StrList1->_head;
    Node* ptr2 = StrList2->_head;
    
    
    while(ptr1 != NULL && ptr2 != NULL){
    
        if (strcmp(ptr1->_data, ptr2->_data) != 0){
            return 0;
        }
        
        ptr1 = ptr1->_next;
        ptr2 = ptr2->_next;

    }
    
    return 1;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* Strlist){
    
    StrList* clone = StrList_alloc();
    

    Node* ptr1 = Strlist->_head;
    
    while(ptr1!= NULL){
        
        StrList_insertLast(clone,ptr1->_data);
        ptr1=ptr1->_next;
    }
    
    return clone;
    }

/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList){

    Node* prev = NULL;
    Node* curr = StrList->_head;
    Node* after = NULL;

    while (curr != NULL)
    {
        after = curr->_next;
        curr->_next = prev; //the change

        prev = curr;
        curr = after;

    }
    StrList->_head=prev;
}

// /*
//  * Sort the given list in lexicographical order 
//  */



    // Function to swap the data of two nodes
    void swap(Node* a, Node* b) {
        char* temp = a->_data;
        a->_data = b->_data;
        b->_data = temp;
    }
    void StrList_sort( StrList* StrList){
        if (StrList == NULL || StrList->_head == NULL || StrList->_head->_next == NULL)
        return; // Nothing to sort or only one element
    
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = StrList->_head;

        while (ptr1->_next != lptr) {
            if (strcmp(ptr1->_data, ptr1->_next->_data) > 0) {
                swap(ptr1, ptr1->_next);
                swapped = 1;
            }
            ptr1 = ptr1->_next;
        }
        lptr = ptr1;
    } while (swapped);
    
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList){
    Node* ptr = StrList->_head;

    
    while (ptr != NULL && ptr->_next != NULL) {
        if (strcmp(ptr->_data, ptr->_next->_data) > 0) {
            return 0; // Not sorted
        }
        ptr = ptr->_next;
    }
    return 1; 
}
