#include "StrList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct node {
    char* data;
    struct node * next;
} node;

typedef struct _StrList {
    node * _head;
    size_t _size;
} StrList;



void buildList(StrList* StrList, int length, char* str){
    int count = 0;
    int j = 0;
    

    for (int i = 0; i < length; i++)
    {
        char* substring;
        while (str[j] != ' ' && j < strlen(str))
        {
            count++;
            j++;
        }
        
        substring = (char*)malloc(count+1);
        strncpy(substring, str, count);
        substring[j] = '\0';
        
        StrList_insertLast(StrList, substring);
        
        
        j++;
        count = 0;
        str += j;
        j = 0;
        free(substring);
    }
}


void strcpy_custom(char *dest, const char *src) {
    while (strcmp(" ", src)) {
        *dest++ = *src++;
    }
    *dest = '\0'; // Null-terminate the destination string
}


/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc()
{
    StrList* p = (StrList*)malloc(sizeof(StrList));
    if (p == NULL) {
        printf("%s", "no space available");
        return NULL;
    }
    else {
        p->_head = NULL;
        p->_size = 0;
        return p;
    }
}


/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList)
{
    node* curr = StrList->_head;
    while (curr != NULL) {
        node* toDelete = curr;
        curr = curr->next;
        free(toDelete->data); // Free any dynamically allocated data in the node
        free(toDelete); // Free the node itself
    }
    StrList->_head = NULL;
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList){
 return StrList->_size;
}


/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data) 
{   
    if (StrList->_head == NULL) {
        StrList->_head = (node*)malloc(sizeof(node));
        StrList->_head->data = (char*)malloc(strlen(data) + 1);
        strcpy(StrList->_head->data, data);
        StrList->_head->next = NULL;
        return;
    }
    node * curr = StrList->_head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    node * new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_node->data = malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_node);
        return;
    }
    strcpy(new_node->data, data);
    new_node->next = NULL;

    if (StrList->_head == NULL) {
        StrList->_head = new_node;
    } else {
        curr->next = new_node;
    }
}


void StrList_insertAt(StrList* StrList, const char* data, int index) 
{
    node * curr = StrList->_head;
    for (int i = 0; i < index - 1; i++) {
        if (curr == NULL) {
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
        curr = curr->next;
    }
    node * new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_node->data = malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_node);
        return;
    }
    strcpy(new_node->data, data);
    new_node->next = NULL;
    if (index == 0) {
        new_node->next = StrList->_head;
        StrList->_head = new_node;
    } else {
        new_node->next = curr->next;
        curr->next = new_node;
    }
}


/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList)
{
    return StrList->_head->data;
}


/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    node* curNode = StrList->_head;
    if(curNode != NULL){
        while (curNode->next != NULL){
            printf("%s ", curNode->data);
            curNode = curNode->next;
        }
        printf("%s", curNode->data);
    }
    printf("\n");
}


void StrList_printAt(const StrList* Strlist,int index)
{
    node * curr = Strlist->_head;
    for (int i = 0; i<index; i++) {
        if (curr == NULL) {
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
        curr = curr->next;
    }
    if(curr != NULL)
    {
        puts(curr->data);
    }
    else {
        fprintf(stderr, "Index out of bounds\n");
    }
}



/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist)
{
    int ans = 0;
    node * curr = Strlist->_head;
    while(curr != NULL){
        ans += strlen(curr->data);
        curr = curr->next;
    }
    free(curr);
    return ans;
}


/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data)
{
    int ans = 0;
    node * curr = StrList->_head;
    while (curr != NULL) {
        if(strcmp(curr->data, data) == 0){
            ans += 1;
        }
        curr = curr->next;
    }
    return ans;
}


/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data)
{
    node * curr = StrList->_head;
    node * prev = NULL;
    while (curr != NULL) {
        if(strcmp(curr->data, data) == 0){
            if (prev == NULL) {    //if we want to delete the head
                StrList->_head = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            node * toDelete = curr;      //delete without losing track of original node
            curr = curr->next;
            free(toDelete->data);
            free(toDelete);
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}



/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    node * curr = StrList->_head;
    node * prev = NULL;

    if (index == 0) {
        node * toDelete = StrList->_head;
        StrList->_head = curr->next->next;
        free(toDelete->data);
        free(toDelete);
        return;
    }

    for (int i = 0; i<index; i++) {
        if (curr == NULL) {
            printf("index out of bounds");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Index out of bounds\n");
        return;
    }
    prev->next = curr->next;
    free(curr->data);
    free(curr);
}


int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    if (StrList1->_size != StrList2->_size) {
        return 0;
    }
    if (StrList1 == NULL || StrList2 == NULL) {
        return 0;
    }

    node * curr1 = StrList1->_head;
    node * curr2 = StrList2->_head;

    while (curr1 != NULL && curr2 != NULL) {
        if (strcmp(curr1->data, curr2->data) != 0){
            printf("not equal");
            return 0;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return curr1 == NULL && curr2 == NULL;
}


/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* Strlist)
{
    StrList *result = StrList_alloc();
    node * curr = Strlist->_head;
    
    while (curr != NULL) {
        StrList_insertLast(result, curr->data);
        curr = curr->next;
    }
    return result;
}


void StrList_reverse(StrList* list) {
    node *prev = NULL, *current = list->_head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->_head = prev;
}


void StrList_sort(StrList* list) {
    if (list->_head == NULL || list->_head->next == NULL) {
        // Empty or single-element list, no need to sort
        return;
    }

    int swapped;
    node *ptr1;
    node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list->_head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int StrList_isSorted(StrList* list) {
    node* current = list->_head;
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0; // Not sorted
        }
        current = current->next;
    }
    return 1; // Sorted
}



