#include "main.h"
const char* filename = "output.txt";
void print_menu(void)
{
    system("clear");
    printf("######### Address book #########\n");
    printf("###### Features:\n\n");
    printf("0. Exit\n1. Add contact\n2. Search Contact\n3.Edit Contact\n4. Delete Contact\n5. List Contacts\n6. Save\n\nPlesae select an option:");
}
int load_addressbook_from_file(AddressBook *addressbook, const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("File not read\n");
        return FAILURE;
    }
    addressbook->contactCount = 0;
    while(!feof(fp))
    {
        Contact contact;
        if(fscanf(fp, "Serial no.: %d\n", &contact.id) != 1) break;
        if(fscanf(fp, "Name: %[^\n]\n", contact.name) != 1) break;
        if(fscanf(fp, "Phone: %[^\n]\n", contact.contact) != 1) break;
        if(fscanf(fp, "Email: %[^\n]\n", contact.email) != 1) break;
    
    char separator[50];
    fgets(separator, sizeof(separator), fp);
    addressbook->contacts[addressbook->contactCount] = contact;
    addressbook->contactCount++;
    }
    fclose(fp);
    printf("Addressbook loaded successfully\n");
    return SUCCESS;
}
int main()
{   
    AddressBook addressbook;
    addressbook.contactCount = 0;
    while(1)
    {
        print_menu();
            int option;
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                exit(0);
                break;
            case 1:
                
                add(&addressbook);
                break;
            case 2:
                search();
                break;
            case 3:
                // edit();
                break;
            case 4:
                // delete();
                break;
            case 5:
            {
                AddressBook adrr;
                if(list(&adrr, filename) == SUCCESS);
                else
                {
                    printf("Error while listing filecontents\n");
                }
                break;
            }
            case 6:
                save(&addressbook, filename);
                break;
            default:
                printf("Enter a valid option\n");

        }
    }



    return 0;
}