#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCONTACTS 100
#define MAX_NAME     50
#define MAX_EMAIL   50
#define MAX_CONTACT  30
#define SUCCESS 0
#define FAILURE 1
typedef struct 
{
    char contact[30];
    char name[50];
    char email[50];
    int id;
}Contact;

typedef struct {
    Contact contacts[MAXCONTACTS];
    int contactCount;
}AddressBook;
void add(AddressBook*);
void search(void);
void save_addressbook_to_file(AddressBook*, const char* );
int list(AddressBook*, const char* );
int save(AddressBook* , const char* );
extern const char* filename;
int load_addressbook_from_file(AddressBook*, const char* );


#endif