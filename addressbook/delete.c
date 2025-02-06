#include "main.h"
#include "search.h"
void display_id_delete(AddressBook* addressbook, int s)
{
    for(int i=0;i<addressbook->contactCount;i++){
        printf("##########Address Book ###########\n");
        printf("##########Delete Contact:\n\n");
        printf("0. Back\n1. Name\t:%s\n2.phone No 1:\t%s\n3. Email Id 1:\t%s\n\n", addressbook->contacts[i].name, addressbook->contacts[i].contact, addressbook->contacts[i].email);
        printf("Enter 'Y' to delete. [Press any key to ignore]:");
    }
}
void delete(AddressBook* addressbook,int s)
{
    if(addressbook == NULL || addressbook->contacts == NULL)
    {
        printf("Addressbook is empty or not initialized\n");
        return;
    }
    int found = 0;
    // if (addressbook->contactCount == 1) {
    //     addressbook->contactCount--;  // Just decrement the count
    //     printf("Contact with serial number %d deleted.\n", s);
    //     return;
    // }
    for(int i =0;i<addressbook->contactCount;i++)
    {
        if(addressbook->contacts[i].id == s)
        {
            found = 1;
            for(int j=i;j<addressbook->contactCount-1;j++)
            {
                addressbook->contacts[j] = addressbook->contacts[j+1];
            }
            addressbook->contacts[addressbook->contactCount - 1].id = 0; // Assuming `id` is an int
            strcpy(addressbook->contacts[addressbook->contactCount - 1].name, "");
            strcpy(addressbook->contacts[addressbook->contactCount - 1].contact, "");
            strcpy(addressbook->contacts[addressbook->contactCount - 1].email, "");
            addressbook->contactCount--;
            printf("Contact with serial number %d deleted.\n", s);
            break;
        }
    }
    if(!found)
    {
        printf("Contact with serial number %d not found.\n", s);

    }

}
void delete_data(AddressBook* addressbook)
{
    while(1)
    {
        search_menu();
        int option;
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                return;
            case 1:
            {
                printf("Enter the name: ");
                char name[MAX_NAME];
                scanf("%s", name);
                search_adressbook_name(addressbook, name);
                printf("Press [s] = Select, [q] | cancel: ");
                getchar();
                char ch;
                scanf("%c", &ch);
                if(ch == 'q')
                {
                    return;
                }
                else if(ch == 's')
                {
                    printf("Select a Serial number (S.No.) to Delete: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id_delete(addressbook, s);
                        char ch;
                        getchar();
                        scanf("%c", &ch);
                        if(ch == 'Y' || ch == 'y')
                        {
                            delete(addressbook,s);
                        }
                        return;
                        

                    }
                }
                break;
            }
            case 2:
            {
                printf("Enter the phone: ");
                char phone[MAX_CONTACT];
                scanf("%s", phone);
                search_adressbook_phone(addressbook, phone);
                printf("Press [s] = Select, [q] | cancel: ");
                getchar();
                char ch;
                scanf("%c", &ch);
                if(ch == 'q')
                {
                    return;
                }
                else if(ch == 's')
                {
                    printf("Select a Serial number (S.No.) to Delete: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id_delete(addressbook, s);
                        char ch;
                        getchar();
                        scanf("%c", &ch);
                        if(ch == 'Y' || ch == 'y')
                        {
                            delete(addressbook,s);
                        }
                        return;


                    }
                }
                break;
            }
            case 3:
            {
                printf("Enter the email: ");
                char email[MAX_EMAIL];
                scanf("%s", email);
                search_adressbook_email(addressbook, email);
                printf("Press [s] = Select, [q] | cancel: ");
                getchar();
                char ch;
                scanf("%c", &ch);
                if(ch == 'q')
                {
                    return;
                }
                else if(ch == 's')
                {
                    printf("Select a Serial number (S.No.) to Delete: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id_delete(addressbook, s);
                        char ch;
                        getchar();
                        scanf("%c", &ch);
                        if(ch == 'Y' || ch == 'y')
                        {
                            delete(addressbook,s);
                        }
                    
                        
                        return;
                        

                    }
                }
                break;
            }
            case 4:
            {
                printf("Enter the serial no: ");
                int s_no;
                scanf("%d", &s_no);
                search_adressbook_s_no(addressbook, s_no);
                printf("Press [s] = Select, [q] | cancel: ");
                getchar();
                char ch;
                scanf("%c", &ch);
                if(ch == 'q')
                {
                    return;
                }
                else if(ch == 's')
                {
                    printf("Select a Serial number (S.No.) to Delete: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id_delete(addressbook, s);
                        char ch;
                        getchar();
                        scanf("%c", &ch);
                        if(ch == 'Y' || ch == 'y')
                        {
                            delete(addressbook,s);
                        }
                        return;

                    }
                }
                break;
            }
        }
    }
}