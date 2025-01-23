#include "main.h"
#include "search.h"

void search_menu(void)
{
    printf("######### Address book #########\n");
    printf("###### Search Contact by:\n\n");
    printf("0. Back\n1. Name\n2. Phone No. 1\n3.Email Id1\n4.Serial no.\n\nPlesae select an option:");
}
void displayy(Contact contact)
{
    printf("##########Address Book ###########\n");
    printf("##########Search Result\n\n");
    printf("===================================================\n");
    printf(": S.No. : Name\t\t\t:PhoneNo.\t\t\t:Email ID\n");
    printf("===================================================\n");
    printf(":%d :%s\t\t\t%s\t\t\t%s\n\n\n",contact.id, contact.name, contact.contact, contact.email);
    printf("===================================================\n");
}
void search_adressbook_name(AddressBook* addressbook, char* name)
{
    for(int i =0;i<addressbook->contactCount;i++)
    {
        if(strcmp(addressbook->contacts[i].name , name)== 0)
        {
            displayy(addressbook->contacts[i]);
            return;
        }
    }
    printf("Provided contact not present\n");
}
void search_adressbook_phone(AddressBook* addressbook, char* phone)
{
    for(int i =0;i<addressbook->contactCount;i++)
    {
        if(strcmp(addressbook->contacts[i].contact , phone))
        {
            displayy(addressbook->contacts[i]);
            return;
        }
    }
    printf("Provided contact not present\n");
}
void search_adressbook_email(AddressBook* addressbook, char* email)
{
    for(int i =0;i<addressbook->contactCount;i++)
    {
        if(strcmp(addressbook->contacts[i].email , email))
        {
            displayy(addressbook->contacts[i]);
            return;
        }
    }
    printf("Provided contact not present\n");
}
void search_adressbook_s_no(AddressBook* addressbook, int s_no)
{
    for(int i =0;i<addressbook->contactCount;i++)
    {
        if(addressbook->contacts[i].id == s_no)
        {
            displayy(addressbook->contacts[i]);
            return;
        }
    }
    printf("Provided contact not present\n");
}
void search(void)
{

    while(1)
    {
        search_menu();
        int option;
        AddressBook addressbook;
        load_addressbook_from_file(&addressbook, filename);
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                return;
            case 1:
            {
                char name[MAX_NAME];
                printf("Enter the name: ");
                scanf("%s", name);
                search_adressbook_name(&addressbook, name);
                break;
            }
            case 2:
            {   char phone[MAX_CONTACT];
                printf("Enter the phone no.: ");
                scanf("%s", phone);
                search_adressbook_phone(&addressbook, phone);
                break;
            }
            case 3:
            {
                char email[MAX_EMAIL];
                printf("Enter the email: ");
                scanf("%s", email);
                search_adressbook_email(&addressbook, email);
                break;
            }
            case 4:
            {
                int s_no;
                printf("Enter the s. no.: ");
                scanf("%d", &s_no);
                search_adressbook_s_no(&addressbook, s_no);
                break;
            }
            default:
                printf("Enter a valid option\n");
        }
        printf("Press [q] | cancel:");
        getchar();
        char ch;
        scanf("%c", &ch);
        if(ch == 'q')
        {
            return;
        }

    }



}