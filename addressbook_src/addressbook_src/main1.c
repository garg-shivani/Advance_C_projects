#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 15
#define EMAIL_LEN 50

typedef struct{
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

Contact contact[MAX_CONTACTS];
int contact_count = 0;
void add_contact()
{
    if(contact_count >= MAX_CONTACTS) {
        printf("Address book is full!\n");
        return;
    }
    printf("Enter name: ");
    scanf(" %[^\n]", contact[contact_count].name);
    printf("Enter phone: ");
    scanf(" %[^\n]", contact[contact_count].phone);
    printf("Enter e-mail: ");
    scanf(" %[^\n]", contact[contact_count].email);
    contact_count++;
    printf("Contact added succesfully!\n");
}
void view_contact()
{
    if(contact_count==0)
    {
        printf("No contacts to display");
        return;
    }
    for(int i=0;i<contact_count;i++)
    {
        printf("Contact %d:\n", i+1);
        printf("Name %s\n", contact[i].name);
        printf("Phone %s\n", contact[i].phone);
        printf("E-mail %s\n", contact[i].email);
        printf("\n");
    }
}
void delete_contact()
{
    if(contact_count == 0)
    {
        printf("there is no contact to delete");
        return;

    }
    int index;
    printf("Enter the contact number to delete");
    scanf("%d",&index);
    if(index < 1 || index > contact_count )
    {
        printf("Invalid contact number\n");
        return;
    }
    for(int i= index - 1;i<contact_count-1;i++)
    {
        contact[i] = contact[i+1];
    }
    contact_count--;
    printf("Contact deleted succesfully");
}
void menu()
{
    printf("Address Book Menu: \n");
    printf("1. Add Contact\n");
    printf("2. View Contact\n");
    printf("3. Delete Contact\n");
    printf("4. Exit\n");
    printf("Choose an option");
}
int main()
{
    int choice;
    while(1)
    {
        menu();
        scanf(" %d",&choice);
        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                view_contact();
                break;
            case 3:
                delete_contact();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid option. Please try again./n");
        }
    }
    return 0;
}

