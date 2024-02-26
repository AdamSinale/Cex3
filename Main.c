
#include <stdio.h>
#include <string.h>
#include "StrList.h"

#define TRUE 1
#define FALSE 0



int main(){
    StrList* list = StrList_alloc();
    int function;
    int storyLen;
    char story[1000];
    char word[100];
    int j=0, i;

    scanf("%d", &function);
    while(function != 0){
        switch(function){
            case 1:
                scanf("%d", &storyLen);  
                scanf("%s", story);
                printf("%s", story);
                for(i=0;i<strlen(story); i++){
                    j=0;
                    while(story[i] != ' ' && i<strlen(story)){
                        word[j] = story[i];
                        i++;
                        j++;
                    }
                    word[j] = '\0';
                    StrList_insertLast(list, word);
                }
                break;
            case 2:
                scanf("%d", &i);
                scanf("%s", word);
                StrList_insertAt(list, word, i);
                break;
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%ld\n", StrList_size(list));
                break;
            case 5:
                scanf("%d", &i);
                StrList_printAt(list, i);
                break;
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7:
                scanf("%s", word);
                printf("%d\n", StrList_count(list, word));
                break;
            case 8:
                scanf("%s", word);
                StrList_remove(list, word);
                break;
            case 9:
                scanf("%d", &i);
                StrList_removeAt(list, i);
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
                if(StrList_isSorted(list) == TRUE){
                    printf("true\n");
                }
                else{ printf("false\n"); }
                break;
            default:
                break;
        }
        scanf("%d", &function);
    }
    return 0;
}
