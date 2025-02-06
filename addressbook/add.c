#include "main.h"
#include "add.h"
void add_menu(void)
{
    printf("######### Address book #########\n");
    printf("###### Add contact:\n\n");
    printf("0. Back\n1. Name\n2. Phone No. 1\n3.Email Id1\n\nPlesae select an option:");
}
int validate_name(const char* str)
{
    if(str == NULL || str[0] == '\0' )
    {
        return FAILURE;
    }
    for(int i =0;str[i] != '\0' ;i++)
    {
        if(!isalpha((unsigned char )str[i]) )
        {
            return FAILURE;
        }

    }
    return SUCCESS;
}
int validate_phone(const char* phone)
{
    int length = strlen(phone);
    if(phone == NULL || length == 0)
    {
        return FAILURE;
    }
    int start = 0;
    if(phone[0] == '+')
    {
        start++;
    }
    for(int i = start;i<length;i++)
    {
        if(!isdigit(phone[i]))
        {
            return FAILURE;
        }
    }
    int digitcount = length - start;
    if(digitcount <10 || digitcount>15)
    {
        return FAILURE;
    }
    return SUCCESS;
}
int validate_email(const char* email)
{
    int atIndex = -1;
    int dotAfterAt = 0;

    //Ensure email is not empty
    if(email == NULL || strlen(email) == 0)
    {
        return FAILURE;
    }
    //traverse the email string
    for(int i=0;email[i] != '\0'; i++)
    {
        char ch = email[i];
        //check for valid char
        if(!isalnum(ch) && ch != '@' && ch!= '.' && ch!= '_' && ch != '-')
        {
            return FAILURE;
        }
        if(ch == '@')
        {
            if(atIndex != -1)
            {
                return FAILURE;//more than one @
            }
            atIndex = i;//mark the position of @
        }
        // check for dot after @
        if(atIndex != -1 &&  ch == '.')
        {
            dotAfterAt  = 1;//makr that ther eis dot 
        }
        //ensure that domain does not start or end with dot or hyphen
        int domainStart = atIndex+ 1;
        if(email[domainStart] == '.' || email[strlen(email) - 1] == '.' || email[domainStart] == '-' || email[strlen(email) - 1] == '-')
            return FAILURE;
        return SUCCESS;
    }

}
void add(AddressBook* addressbook)
{
    Contact contact;
    contact.name[0] = '\0';
    contact.email[0] = '\0';
    contact.contact[0] = '\0';
    contact.id = 0;
    while(1)
    {
        add_menu();
        int option;
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                return;
            case 1:
            {
                printf("Enter the name:\n");
                char name[MAX_NAME];
                scanf("%s", name);
                if(validate_name(name) == SUCCESS)
                {
                    strcpy(contact.name , name);
                }
                else
                {
                    printf("Enter a valid name\n");
                }
                
                break;
            }
            case 2:
            {
                printf("Enter the phone number:\n");
                char phone[MAX_CONTACT];
                scanf("%s", phone);
                if(validate_phone(phone) == SUCCESS)
                {
                    strcpy(contact.contact , phone);
                }
                else
                {
                    printf("Enter a valid phone number\n");
                }

                break;
            }
            case 3:
            {
                printf("Enter the email id:\n");
                char email[MAX_EMAIL];
                scanf("%s", email);
                if(validate_email(email) == SUCCESS)
                {
                    strcpy(contact.email , email);
                }
                else
                {
                    printf("Enter a valid email id\n");
                }
                break;
            }
            default:
                printf("Enter a valid option\n");

        }
    if(contact.name[0] == '\0' || contact.email[0] == '\0' || contact.contact[0] == '\0')
    {
        printf("Complete all fields name , email , contact , before adding a field\n");

    }
    else
    {
        contact.id = addressbook->contactCount+ 1;
        addressbook->contacts[addressbook->contactCount] = contact;
        addressbook->contactCount++;
        printf("contact added successfully\n");
        return;
    }

    }
}