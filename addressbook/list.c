#include "main.h"


void display(AddressBook* addressbook)
{
        printf("#######AddressBook ######\n");
        printf("Search Result:\n\n");
        printf("===================================================\n");
        printf("S.NO. : Name            :Phone NO           : Email ID\n");
        printf("===================================================\n");
        for(int i =0;i <addressbook->contactCount;i++)
        {
        printf("%d  :%s             :%s                 :%s\n",addressbook->contacts[i].id, addressbook->contacts[i].name, addressbook->contacts[i].contact,addressbook->contacts[i].email);
        }
        printf("===================================================\n");

}
int list(AddressBook* addressbook, const char* filename)
{
    if(load_addressbook_from_file(addressbook, filename) == SUCCESS){
        display(addressbook);
 
    }
    else
    {
        printf("loading of adressbook is not successfull\n");
    }
    printf("Press [q] | Cancel:");
    char op;
    getchar();
    scanf("%c", &op);
    if(op == 'q')
    {
        return 0;
    }
    else
    {
        printf("you have preseed the wrong option\n");
    }


}