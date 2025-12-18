//Αγγελος Χοτζαί
//it2024104

// The code was written on vscode (ubuntu)
// and compiled using gcc -Wall main.c books.c -o main
// or gcc -Wall -Wextra main.c books.c -o main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

int main(){
    struct List *head = NULL;
    
    RetrieveData(&head);
    //the data in the file is retrieved and saved automatically
    //when the program starts and when the user decides to exit

    do{
        system("clear");
        printf("\n\033[44;37m|-----------------------------|\n"
            "|         Main Menu           |\n"
            "|-----------------------------|\033[0m\n\n"
            "1. Add new record\n"
            "2. Delete record (based on ISBN)\n"
            "3. Modify record (based on ISBN)\n"
            "4. Sort records (ascending order)\n"
            "5. Search record (based on ISBN)\n"
            "6. Display all records in the database\n"
            "7. Exit program\n"
            "Pick 1-7: ");

        int x;
        scanf("%d",&x);
        while(getchar()!='\n');
        

        switch(x){          //every choice of the menu
            case 1:
                system("clear");
                char check[20];
                printf("Check if the book is in the system (ISBN): ");
                fgets(check,20,stdin);
                check[strcspn(check,"\n")] = '\0';

                if(CheckPresence(&head,check)){
                    printf("\n\033[0;34mRecord not found! Please enter the info:\033[0m\n");
                    inputHandler(&head);
                } else {
                    printf("\n\033[0;34mThis record is already present in the database!\n\033[0m");
                    printf("\033[0;34mPress any button to continue.\033[0m");
                    getchar();
                } 
                break;
            case 2:
                system("clear");
                char key[20];
                printf("\033[0;34mDelete (by ISBN): \033[0m");
                scanf("%s",key);
                while(getchar()!='\n');
                if(!CheckPresence(&head,key)){
                    deleteRecord(&head,key);
                } else {
                    printf("\033[0;34mRecord not found! \033[0m\n");
                    printf("\033[0;34mPress any button to continue.\033[0m");
                    getchar();
                }

                break;
            case 3:
                do{
                    system("clear");
                    printf("Find Record(ISBN): ");
                    fgets(check,20,stdin);
                    check[strcspn(check,"\n")] = '\0';
                    if(!CheckPresence(&head,check)){
                        ModifyRecord(&head,check);
                        break;
                    } else {
                        printf("\n\033[0;34mRecord doesnt exist! Press any key to try again\033[0m");
                        getchar();
                    }
                }while(1);
                break;
            case 4:
                system("clear");
                fourthChoice(head); //sorting submenu
                break;
            case 5:
                do{
                    system("clear");
                    printf("Find Record(ISBN): ");
                    fgets(check,20,stdin);
                    check[strcspn(check,"\n")] = '\0';
                    if(!CheckPresence(&head,check)){
                        DisplaySingleRecord(&head,check);
                        break;
                    } else {
                        printf("\n\033[0;34mRecord doesnt exist! Press any key to try again\033[0m");
                        getchar();
                    }
                }while(1);
                break;
            case 6:
                system("clear");
                displayDatabase(head);
                printf("\n\033[0;34mPress any button to continue!\033[0m");
                getchar();
                break;
            case 7:
                SaveData(&head);
                freeList(&head);
                return EXIT_SUCCESS;
            default:
                printf("\n\033[0;34mWrong input!\nPress any key to try again.\033[0m");
                getchar();
                break;
        }
    }while(1); 
}