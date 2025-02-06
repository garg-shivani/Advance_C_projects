#include "main.h"
#include "search.h"
// void search_menu(void)
// {
//     printf("######### Address book #########\n");
//     printf("###### Search Contact to Edit by:\n\n");
//     printf("0. Back\n1. Name\n2. Phone No. 1\n3.Email Id1\n4.Serial no.\n\nPlesae select an option:");
// }
void display_id(Contact contact)
{
    printf("##########Address Book ###########\n");
    printf("##########Edit Contact:\n\n");
    printf("0. Back\n1. Name\t:%s\n2.phone No 1:\t%s\n3. Email Id 1:\t%s\n", contact.name, contact.contact, contact.email);
    printf("Please select an option : ");

}
void edit_name(AddressBook* addressbook, char* name, int s_no)
{
    strcpy(addressbook->contacts[s_no - 1].name , name);
    return;
}
void edit_phone(AddressBook* addressbook, char* phone, int s_no)
{
    strcpy(addressbook->contacts[s_no - 1].contact , phone);
    return;
}
void edit_email(AddressBook* addressbook, char* email, int s_no)
{
    strcpy(addressbook->contacts[s_no - 1].email , email);
    return;
}
void edit(AddressBook* addressbook)
{
    while(1)
    {
        search_menu();
        int option;
        scanf("%d", &option);
        switch(option)
        {
            case 0:
            {
                return;
            }
            case 1:
            {
                printf("Enter the Name: ");
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
                    printf("Select a Serial number (S.No.) to Edit: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id(addressbook->contacts[s-1]);
                        int option_edit;
                        scanf("%d",&option_edit);
                        switch(option_edit)
                        {
                            case 0:
                                return;
                            case 1:
                            {
                                printf("Enter the name to be changed :");
                                char name[MAX_NAME];
                                scanf("%s", name);
                                edit_name(addressbook, name, s);
                                break;
                            }    
                            case 2:
                            {
                                printf("Enter the phone to be changed :");
                                char phone[MAX_CONTACT];
                                scanf("%s", phone);
                                edit_phone(addressbook, phone, s);
                                break;
                            }  
                            case 3:
                            {
                                printf("Enter the email to be changed :");
                                char email[MAX_EMAIL];
                                scanf("%s", email);
                                edit_email(addressbook, email, s);
                                break;
                            }  
                            default:
                                printf("Enter a valid optin to edit contact\n");
                        }
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
                    printf("Select a Serial number (S.No.) to Edit: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id(addressbook->contacts[s-1]);
                        int option_edit;
                        scanf("%d",&option_edit);
                        switch(option_edit)
                        {
                            case 0:
                                return;
                            case 1:
                            {
                                printf("Enter the name to be changed :");
                                char name[MAX_NAME];
                                scanf("%s", name);
                                edit_name(addressbook, name, s);
                                break;
                            }    
                            case 2:
                            {
                                printf("Enter the phone to be changed :");
                                char phone[MAX_CONTACT];
                                scanf("%s", phone);
                                edit_phone(addressbook, phone, s);
                                break;
                            }  
                            case 3:
                            {
                                printf("Enter the email to be changed :");
                                char email[MAX_EMAIL];
                                scanf("%s", email);
                                edit_email(addressbook, email, s);
                                break;
                            }  
                            default:
                                printf("Enter a valid option to edit contact\n");
                        }
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
                    printf("Select a Serial number (S.No.) to Edit: ");
                    int s;
                    scanf("%d", &s);
                    while(1)
                    {
                        display_id(addressbook->contacts[s-1]);
                        int option_edit;
                        scanf("%d",&option_edit);
                        switch(option_edit)
                        {
                            case 0:
                                return;
                            case 1:
                            {
                                printf("Enter the name to be changed :");
                                char name[MAX_NAME];
                                scanf("%s", name);
                                edit_name(addressbook, name, s);
                                break;
                            }    
                            case 2:
                            {
                                printf("Enter the phone to be changed :");
                                char phone[MAX_CONTACT];
                                scanf("%s", phone);
                                edit_phone(addressbook, phone, s);
                                break;
                            }  
                            case 3:
                            {
                                printf("Enter the email to be changed :");
                                char email[MAX_EMAIL];
                                scanf("%s", email);
                                edit_email(addressbook, email, s);
                                break;
                            }  
                            default:
                                printf("Enter a valid option to edit contact\n");
                        }
                    }
                }
                break;
            }
            case 4:
            {
                printf("Enter the serial no: ");
                int serial_no;
                scanf("%d", &serial_no);
                search_adressbook_s_no(addressbook, serial_no);
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
                    while(1)
                    {
                        display_id(addressbook->contacts[serial_no-1]);
                        int option_edit;
                        scanf("%d",&option_edit);
                        switch(option_edit)
                        {
                            case 0:
                                return;
                            case 1:
                            {
                                printf("Enter the name to be changed :");
                                char name[MAX_NAME];
                                scanf("%s", name);
                                edit_name(addressbook, name, serial_no);
                                break;
                            }    
                            case 2:
                            {
                                printf("Enter the phone to be changed :");
                                char phone[MAX_CONTACT];
                                scanf("%s", phone);
                                edit_phone(addressbook, phone, serial_no);
                                break;
                            }  
                            case 3:
                            {
                                printf("Enter the email to be changed :");
                                char email[MAX_EMAIL];
                                scanf("%s", email);
                                edit_email(addressbook, email, serial_no);
                                break;
                            }  
                            default:
                                printf("Enter a valid option to edit contact\n");
                        }
                    }
                }
                break;
            }
            default:
                printf("Enter a valid option\n");
                break;
                
        }
    }
}