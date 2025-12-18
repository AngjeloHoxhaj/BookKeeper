//Αγγελος Χοτζαί
//it2024104

#ifndef BOOKS_H
#define BOOKS_H

#define SIZE 256

struct List{
    char title[SIZE];
    char author[SIZE];
    char publisher[SIZE];
    int year;
    char ISBN[20]; 
    struct List *next;
    struct List *prev; 
};

struct read_write_List{      //this this struct is used temporarely to pass
    char title[SIZE];        //values from the list to the file and vice versa
    char author[SIZE];       //this way we avoid saving the pointers in the database
    char publisher[SIZE];
    int year;
    char ISBN[20]; 
};



void RetrieveData(struct List**);       //retrieve data from a file and write it on a list

void SaveData(struct List**);       //save the data from a list into the file

void fourthChoice(struct List*);

void inputHandler(struct List**);      //Takes care for every input in the List fields

void push_end(struct List**, char*, char*, char*, int, char*);

void freeList(struct List**);       //deallocates the memory ocupied from the list

void deleteRecord(struct List**, char*);

void ModifyRecord(struct List**, char *);

void DisplaySingleRecord(struct List**, char*);

int CheckPresence(struct List**, char*);       //Check if there is a record with the given ISBN

void displayDatabase(struct List*);

void ListSort(struct List*, char);

int compareByTitle(const void *,const void *);

int compareByAuthor(const void *,const void *);

int compareByPublisher(const void *,const void *);

int compareByYear(const void *,const void *);

int compareByISBN(const void *,const void *);
#endif