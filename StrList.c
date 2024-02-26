#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Node & List Data Structures
typedef struct _node {
    char* _data;
    struct _node* _next;
} Node;


struct _StrList {
    Node* _head;
    size_t _size;
};


// Node implementation
//------------------------------------------------



Node* Node_alloc(const char* data, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        return NULL;
    }
    
    // Allocate memory for the string data and copy the string
    p->_data = strdup(data);
    if (p->_data == NULL) {
        free(p); // Free the previously allocated node
        return NULL;
    } 
    
    // Set the next pointer
    p->_next = next;
    
    return p;
}

void Node_free(Node* node) {
	free(node->_data);
	free(node);
}
//------------------------------------------------

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc(){
    StrList* new_list = (StrList*)malloc(sizeof(StrList));
    if (new_list == NULL){
        printf("can not allocate memory");
        return NULL;
    } else {
    new_list->_head= NULL;
	new_list->_size= 0;
	return new_list;
    }
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList){
    if (StrList==NULL) return;
    Node* p1 = StrList-> _head;
    Node* p2;
    while(p1) {
        p2 =p1;
        p1 = p1->_next;
        Node_free(p2);
    }
     //StrList->_head = NULL;
    // free(StrList);
    // StrList = NULL;
    StrList->_head = NULL;
    StrList->_size = 0;
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList){
    
   return StrList ? StrList->_size : 0;
   
    
}


/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data){
   
   
   // Allocate memory for the new node
    Node* newNode = Node_alloc(data, NULL);
   
    if (StrList->_head == NULL){ //if it empty
        StrList->_head = newNode;
        StrList->_size++;
        return;
    }
    else {
    Node* ptr = StrList->_head;
    while (ptr->_next != NULL){
    ptr = ptr->_next;
   }
     ptr->_next = newNode;
    }
     StrList->_size++;
  }

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList, const char* data,int index){
    if (index < 0 || index > StrList->_size)
        return; // Invalid index

    Node* newNode = Node_alloc(data, NULL);
    if (newNode == NULL)
        return; 

    if (index == 0) { // Insert at the head
        newNode->_next = StrList->_head;
        StrList->_head = newNode;
        
    } else {
        Node* ptr = StrList->_head;
        for (int i = 0; i < index - 1 && ptr != NULL; i++) {
            ptr = ptr->_next;
        }
        if (ptr == NULL)
            return; // Index out of bounds
        newNode->_next = ptr->_next;
        ptr->_next = newNode;
    }

    StrList->_size++;
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList){
    if (StrList->_head != NULL) {
        return StrList->_head->_data;
    }
    //when list is empty
    return NULL; 
}


/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    
    if (StrList->_head == NULL) {
        printf("\n");
        return;
    }
     Node* ptr = StrList->_head;
    while (ptr != NULL){
        if (ptr->_next == NULL){
            printf("%s", ptr->_data); 
        }else {
        printf("%s ", ptr->_data); }
        ptr = ptr->_next;
    }
     printf("\n"); 
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index){
 
  if (index < 0 || index >= Strlist->_size)
        return; // Invalid index or index out of bounds
    
    Node* ptr = Strlist->_head;
    
    for (int i = 0; i < index; i++) {
        ptr = ptr->_next;
        if (ptr == NULL)
            return; // Index out of bounds
    }
    
    printf("%s\n", ptr->_data);
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist){
    
    int charsAmount = 0;
    Node* ptr = Strlist->_head;
    
    while (ptr !=NULL) {
        
        charsAmount = charsAmount + strlen(ptr->_data);
        
        ptr = ptr->_next;
        
    }
    
    return charsAmount;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data){
    
    int count =0;
    Node* ptr = StrList->_head;
    
    while (ptr !=0) {
        
        if (strcmp(ptr->_data, data) == 0){
            count ++;
        }
       ptr = ptr->_next; 
    }
    
    return count;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
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
