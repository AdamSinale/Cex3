#include <stdio.h>
#include "StrList.h"

int main() {

    StrList* list = StrList_alloc();
     int index2=0;
     char sentence[500];  
    int wordCnt=0,choice = 0,index =0;
    
    //switch case of 1-13 +0 
      
   do {
      // printf("enter your choice \n");
       scanf("%d",&choice);
        getchar();


        switch (choice) {
           
           case 0:
                exit(0);
            break;
           
           
            case 1:
             //the scan func
    
    //printf("enter the number of word \n");
    scanf("%d",&wordCnt);
    getchar();
    
    //printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);


    // Tokenize the sentence into words and insert each word into the StrList
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        // Remove newline character if present
        if (token[strlen(token) - 1] == '\n') {
            token[strlen(token) - 1] = '\0';
        }
        StrList_insertLast(list, token);  // Insert the word into the StrList
        token = strtok(NULL, " ");  // Move to the next word
    }
                
                break;
            case 2:// Insert string in some index
                   // printf("enter index\n");
                    scanf("%d", &index);
                   // printf("enter word\n");
                    scanf("%s", sentence);
                    StrList_insertAt(list, sentence, index);
        
                break;
             case 3: //print the list
                    StrList_print(list);
                    break;
            case 4:
                   printf("%zu\n", StrList_size(list));
                    break;
            case 5:
               // printf("5 -enter index");
                scanf("%d", &index2);
                StrList_printAt(list ,index2);
                    break;
            case 6:
                printf("%d\n", StrList_printLen(list)); 
                    break;
            case 7:
                //printf("7- enter a string");
                scanf("%s", sentence);
                printf("%d\n",StrList_count(list,sentence));
                    break;
            case 8:
                //printf("8 -enter a string");
                scanf("%s", sentence);
                StrList_remove(list,sentence);
                     break;
            case 9:
                //printf(" 9 -enter index");
                scanf("%d", &index2);
                StrList_removeAt(list,index2);
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
                    printf("Invalid choice\n");
                     break;
        }
       
    }
   
   while(choice !=0);
   
 

    // // Print the contents of the list
    // printf("Words in the list:\n");
    // StrList_print(list);

    // Free the memory allocated for the list
    StrList_free(list);

   
    
    return 0;
}



 
