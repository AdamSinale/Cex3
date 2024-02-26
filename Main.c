#include "StrList.h"
#include <stdio.h>



int main(){

int choice;
StrList * list;
int index;
int _index;
char a [100];
char str[100];
int __index;


do{
    //printf("\nenter function");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            //printf("how many words\n");
            list = StrList_alloc();
            int number_of_words;
            scanf("%d", &number_of_words);  
            char story[1000];
            //printf("enter a string\n");
            scanf(" %[^\n]s", story);
            buildList(list, number_of_words, story);
            break;

        case 2:
            //printf("enter index");
            scanf("%d", &index);
            //printf("enter word");
            char word[1000];
            scanf("%s", word);
            StrList_insertAt(list, word, index);
            break;

        case 3:
            StrList_print(list);
            break;

        case 4:
            printf("%zu\n", StrList_size(list));
            break;

        case 5:
            //printf("enter index");
            scanf("%d", &_index);
            StrList_printAt(list,  _index);
            break;

        case 6:
            printf("%d\n",StrList_printLen(list));
            break;

        case 7:
            //printf("enter a string\n");
            scanf(" %[^\n]s", a);
            printf("%d\n" , StrList_count(list, a));
            break;

        case 8:
            //printf("enter string");
            scanf("%s", str);
            StrList_remove(list, str);
            break;

        case 9:
            //printf("enter index");
            scanf("%d", &__index);
            StrList_removeAt(list,  __index);
            break;

        case 10:
            StrList_reverse(list);
            break;

        case 11:
            StrList_free(list);
            break;

        case 12:
            StrList_sort(list);
            break;

        case 13:
            if(StrList_isSorted(list)){
                printf("true\n");
            }
            else {
                printf("false\n");
            }
            break;

        default:
            break;



    }
}while(choice != 0);



return 0;
}





