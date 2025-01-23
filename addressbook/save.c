#include "main.h"

void save_addressbook_to_file(AddressBook* addressbook,const char* filename )
{
    FILE* fp = fopen(filename, "a");
    if(fp == NULL)
    {
        printf("Error in creating file\n");
        return;
    }
    for(int i =0;i<addressbook->contactCount;i++)
    {
        fprintf(fp, "Serial no.:%d\n", addressbook->contacts[i].id);
        fprintf(fp, "Name:%s\n", addressbook->contacts[i].name);
        fprintf(fp, "Phone:%s\n", addressbook->contacts[i].contact);
        fprintf(fp, "Email:%s\n", addressbook->contacts[i].email);
        fprintf(fp,"-----------------------------------\n");
    }
    fclose(fp);
    printf("Addressbook saved to '%s'\n", filename);
    return;
}
int save(AddressBook* addressbook, const char* filename)
{

    char option;

    while (1)
    {
        printf("Enter 'N to Ignore and 'Y' to Save: " );
        getchar();
        scanf("%c", &option);
        option = tolower(option);
        switch(option)
        {
            case 'y':
                save_addressbook_to_file(addressbook, filename);
                printf("Exiting. Data Saved in %s\n", filename);
                break;
            case 'n':
                return 0;
                
        }
    }
    

    

}
