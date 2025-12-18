//Αγγελος Χοτζαί
//it2024104
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

void fourthChoice(struct List* head){       //implementation of sorting submenu
        int flag;
        do{
            system("clear");
            printf("\n\033[44;37m|-----------------------------|\n"
                "|         Sort Menu           |\n"
                "|-----------------------------|\033[0m\n\n");
            printf("a) Sort by title(alphabetically)\n"
                "b) Sort by author(alphabetically)\n"
                "c) Sort by publisher(alphabetically)\n"
                "d) Sort by publishing year\n"
                "e) Sort by ISBN\n"
                "Pick a-e: ");
            char x;
            scanf("%c",&x);
            while(getchar()!='\n');
        
            flag = 0;
            switch(x){
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                    ListSort(head,x);
                    break;
                default:
                    printf("\n\033[0;34mWrong input!\nPress any button to try again.\033[0m\n\n");
                    getchar();
                    flag = 1;
                    break;
            }
        }while(flag);
        printf("\n\033[0;34mThe database has been sorted succesfully! Press any key to continue\033[0m");
        getchar();
}

void inputHandler(struct List** head){
    char title[SIZE];
    printf("Enter book title: ");
    fgets(title,SIZE,stdin);
    title[strcspn(title,"\n")] = '\0';

    char author[SIZE];
    printf("Enter book author: ");
    fgets(author,SIZE,stdin);
    author[strcspn(author,"\n")] = '\0';

    char publisher[SIZE];
    printf("Enter book publisher: ");
    fgets(publisher,SIZE,stdin);
    publisher[strcspn(publisher,"\n")] = '\0';

    int year;
    do{
        printf("Enter book publishing year: ");
        if(scanf("%d",&year)!=1){
            printf("\n\033[0;34mInvalid Input! Try againg\n\033[0m");
            while(getchar()!='\n');
        } else {
            break;
        }

    }while(1);
    while(getchar()!='\n');


    char ISBN[20];
    printf("Enter book ISBN: ");
    fgets(ISBN,20,stdin);
    ISBN[strcspn(ISBN,"\n")] = '\0';

    push_end(head, title, author, publisher, year, ISBN);
}

void push_end(struct List** head, char* title, char* author, char* publisher, int year, char* ISBN){
    struct List* newNode = NULL;
    newNode = (struct List*)malloc(sizeof(struct List));
    if(newNode == NULL){
        printf("\n\033[0;34mList memory not allocated!\033[0m");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->title,title);               //we use a double pointer so that we can create the head 
    strcpy(newNode->author,author);             //of the list inside push_end
    strcpy(newNode->publisher,publisher);
    newNode->year = year;
    strcpy(newNode->ISBN,ISBN);
    newNode->prev= NULL;
    newNode->next = NULL;

    if(*head == NULL){          //initialize head if there isnt one
        *head = newNode;
    } else {                    // else add the new node at the end of the List
        struct List *curr = *head;
        while(curr->next != NULL){
            curr = curr->next;
        }  
        
        curr->next = newNode;
        newNode->prev = curr;
    } 
    
    return;
}

void freeList(struct List **head){
    struct List *curr = *head;
    struct List *temp;

    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    *head = NULL;
}

void deleteRecord(struct List** head, char* ISBN){
    struct List *current = *head;

    if(current == NULL){
        printf("\033[0;34mList is empty! \033[0m");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    while(current != NULL){
        if(strcmp(current->ISBN,ISBN)==0){
            printf("Record Deleted!\n");
            if(current->next!=NULL){
                current->next->prev = current->prev;        //links the next and prev pointers of 
            }                                               //the current node so that we dont lose info
            if(current->prev!=NULL){
                current->prev->next = current->next;
            } else {
                *head = current->next;              //if the current node is the head we update the next node as the 
            }                                       //new head of the list
            free(current);                          //and then we free the current node
            printf("\033[0;34mPress any button to continue.\033[0m");
            getchar();

            return;
        }

        current = current->next;
    }
}

int CheckPresence(struct List** head, char* ISBN){
    struct List* curr = *head;

    if(curr == NULL){
        printf("\033[0;34mThe list is empthy! \033[0m\n");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    while(curr != NULL){
        if(strcmp(curr->ISBN,ISBN)==0){
            return 0;
        }
        curr = curr->next;
    }
    return 1;
}

void displayDatabase(struct List *head){
    struct List* curr = head;

    if(curr == NULL){
        printf("\033[0;34mList is Empty\033[0m\n");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    int i=1;
    while(curr != NULL){
        printf("\033[0;34mRecord #%d\033[0m\n", i);
        printf("Title: %s\nAuthor: %s\nPublisher: %s\nPublishing year: %d\nISBN: %s\n\n",
            curr->title, curr->author, curr->publisher, curr->year, curr->ISBN);

        curr = curr->next;
        i++;
    }
}

void ListSort(struct List* head, char choice){
    if (head == NULL || head->next == NULL){
        printf("\033[0;34mList has only one node\033[0m");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        return;
    }

    struct List *curr = head;
    size_t n = 0;
    while(curr != NULL){
        curr = curr->next;
        n++;
    }

    struct read_write_List array[n];
    struct read_write_List temp;
    
    int i=0;
    curr = head;
    while(curr != NULL){                            //copy the list in an array using another struct 
        strcpy(temp.title,curr->title);             //inbetween so that we dont change the pointers when we sort
        strcpy(temp.author,curr->author);
        strcpy(temp.publisher,curr->publisher);
        temp.year = curr->year;
        strcpy(temp.ISBN,curr->ISBN);
        array[i] = temp;

        curr = curr->next;
        i++;
    }
    
    
    switch(choice){
        case 'a':
            qsort(array,n,sizeof(struct read_write_List),compareByTitle);
            break;
        case 'b':
            qsort(array,n,sizeof(struct read_write_List),compareByAuthor);
            break;
        case 'c':
            qsort(array,n,sizeof(struct read_write_List),compareByPublisher);
            break;
        case 'd':
            qsort(array,n,sizeof(struct read_write_List),compareByYear);
            break;
        case 'e':
            qsort(array,n,sizeof(struct read_write_List),compareByISBN);
            break;
    }

    i=0;
    curr = head;
    while(curr != NULL){                        //copy the sorted array in the list maintaining 
        strcpy(curr->title,array[i].title);     //the original pointers
        strcpy(curr->author,array[i].author);
        strcpy(curr->publisher,array[i].publisher);
        curr->year = array[i].year;
        strcpy(curr->ISBN,array[i].ISBN);

        curr = curr->next;
        i++;
    }
}

void ModifyRecord(struct List **head, char *ISBN){
    struct List *curr = *head;
    if(curr == NULL){
        printf("\033[0;34mThe list is empthy! \033[0m\n");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    int i=0;
    while(curr != NULL){
        if(strcmp(curr->ISBN,ISBN)==0){
            printf("\033[0;34mRecord #%d\033[0m\n", i);
            printf("Title: %s\nAuthor: %s\nPublisher: %s\nPublishing year: %d\nISBN: %s\n\n\n",
                curr->title, curr->author, curr->publisher, curr->year, curr->ISBN);
            
            printf("\033[0;34mNew info:\033[0m\n");

            char title[SIZE];
            printf("Enter book title: ");
            fgets(title,SIZE,stdin);
            title[strcspn(title,"\n")] = '\0';

            char author[SIZE];
            printf("Enter book author: ");
            fgets(author,SIZE,stdin);
            author[strcspn(author,"\n")] = '\0';

            char publisher[SIZE];
            printf("Enter book publisher: ");
            fgets(publisher,SIZE,stdin);
            publisher[strcspn(publisher,"\n")] = '\0';

            int year;
            do{
                printf("Enter book publishing year: ");
                if(scanf("%d",&year)!=1){
                    printf("\n\033[0;34mInvalid Input! Try againg\n\033[0m");
                    while(getchar()!='\n');
                } else {
                    break;
                }

            }while(1);
            while(getchar()!='\n'); 

            //we dont change the ISBN

            strcpy(curr->title,title);
            strcpy(curr->author,author);
            strcpy(curr->publisher,publisher);
            curr->year = year;

            printf("\n\033[0;34mRrecord modified succesfully! Press any key to continue.\033[0m");
            getchar();
            return;
        }
        i++;
        curr = curr->next;
    }
}

void DisplaySingleRecord(struct List **head, char *ISBN){
    struct List *curr = *head;
    if(curr == NULL){
        printf("\033[0;34mThe list is empthy! \033[0m\n");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    int i=0;
    while(curr != NULL){
        if(strcmp(curr->ISBN,ISBN)==0){
            printf("\033[0;34mRecord #%d\033[0m\n", i);
            printf("Title: %s\nAuthor: %s\nPublisher: %s\nPublishing year: %d\nISBN: %s\n\n\n",
                curr->title, curr->author, curr->publisher, curr->year, curr->ISBN);

            printf("\n\n\033[0;34mPress any key to continue.\033[0m");
            getchar();
            return;
        }
        i++;
        curr = curr->next;
    }
}

void RetrieveData(struct List** head){
    struct read_write_List read_head;

    FILE *file = NULL;
    file = fopen("books.dat", "rb");
    if(file == NULL){
        printf("\033[0;34mFile not found Exception!\n\033[0m");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }
    
    while(fread(&read_head, sizeof(struct read_write_List), 1, file)){
        push_end(head,read_head.title, read_head.author, read_head.publisher, read_head.year, read_head.ISBN);
        if(ferror(file)){
            perror("Read ERROR:");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

void SaveData(struct List **head){

    FILE *file = NULL;
    file = fopen("books.dat", "wb");
    if(file == NULL){
        printf("\033[0;34mFile not found Exception!\n\033[0m");
        printf("\033[0;34mPress any button to continue.\033[0m");
        getchar();
        exit(EXIT_FAILURE);
    }

    struct List *curr = *head;
    while(curr != NULL){
        struct read_write_List write_head;
        memset(&write_head, 0, sizeof(struct read_write_List));         //clear the stdin buffer by initializing the write head before we write on the .dat file
        
        strcpy(write_head.title,curr->title);
        strcpy(write_head.author,curr->author);
        strcpy(write_head.publisher,curr->publisher);
        write_head.year = curr->year;
        strcpy(write_head.ISBN,curr->ISBN);

        fwrite(&write_head, sizeof(struct read_write_List), 1, file);
        if(ferror(file)){
            perror("Write ERROR:");
            exit(EXIT_FAILURE);
        }
        curr = curr->next;
    }

    fclose(file);
}

//all the compare functions used in qsort for the sorting submenu

int compareByTitle(const void *a,const void *b){
    struct read_write_List *RecordA = (struct read_write_List *)a;
    struct read_write_List *RecordB = (struct read_write_List *)b;
    return strcmp(RecordA->title,RecordB->title);
}

int compareByAuthor(const void *a,const void *b){
    struct read_write_List *RecordA = (struct read_write_List *)a;
    struct read_write_List *RecordB = (struct read_write_List *)b;
    return strcmp(RecordA->author,RecordB->author);
}

int compareByPublisher(const void *a,const void *b){
    struct read_write_List *RecordA = (struct read_write_List *)a;
    struct read_write_List *RecordB = (struct read_write_List *)b;
    return strcmp(RecordA->publisher,RecordB->publisher);
}

int compareByYear(const void *a,const void *b){
    struct read_write_List *RecordA = (struct read_write_List*)a;
    struct read_write_List *RecordB = (struct read_write_List *)b;
    return (RecordA->year - RecordB->year);
}

int compareByISBN(const void *a,const void *b){
    struct read_write_List *RecordA = (struct read_write_List *)a;
    struct read_write_List *RecordB = (struct read_write_List *)b;
    return strcmp(RecordA->ISBN,RecordB->ISBN);
}