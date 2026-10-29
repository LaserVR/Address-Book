#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include <ctype.h>

//Find contact in the address book
int findContact(AddressBook *addressBook, char *search,int choice)
{
    //Search contact 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //switch choice based on phone email or name
        switch(choice)
        {
            case 1:
                if(strcasecmp(addressBook->contacts[i].name,search)==0)
                    return i;
            break;
            case 2:
                if(strcasecmp(addressBook->contacts[i].phone,search)==0)
                    return i;
            break;
            case 3:
                if(strcasecmp(addressBook->contacts[i].email,search)==0)
                    return i;
            break;
            //Return the index if found
        }
    }
    //return -1 if not found
    return -1;
}
//Check if email is valid
int validateEmail(char *email)
{
    //Count @ and . after @
    int atCount=0;
    int dotAfterAt=0;
    int len=strlen(email);
    
    //Check each character in email
    for (int i=0;email[i]!='\0';i++)
    {
        if(!isalnum(email[i]) && email[i] !='@' && email[i] !='.' && email[i]!='_' && email[i]!='-')
            return 0;
        if(email[i]=='@')
        //increment when @
            atCount++;
        if (atCount==1 && email[i]=='.')
        //if . after @ count
            dotAfterAt=1;
    }
    //Check the count
    if(atCount!=1)
        return 0;
    //Check @ position
    char *at=strchr(email, '@');
    if(*(at + 1) == '\0')
        return 0;
    //Check . position
    if (email[len-1]=='.')
        return 0;
    if (*(at + 1)=='.')
        return 0;
    return dotAfterAt;
}
void listContacts(AddressBook *addressBook) 
{

    int sortCriteria;
    char select[20];
    l6:
    //Get sort criteria input
    printf("Enter Sort Criteria:\n 1-Name\n 2-Phone\n 3-Email: ");
    scanf(" %19[^\n]",select);
    //Check if criteria is valid
    if(strlen(select)>1 && select[0]<'1'||select[0]>'3')
    {
        //if not get input again
        printf("Invalid Selection\n");
        goto l6;
    }
    sortCriteria=select[0]-'0';
    //Change to integer
    //Sort by name
    printf("Sorting by Name\n");
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            //Based on sort criteria
            int result;
            switch(sortCriteria)
            {
                case 1:
                    result=strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                break;
                case 2:
                    result=strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
                break;
                case 3:
                  result=strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
                break;
            }
            //if index is returned
            if(result>0)
            {
                //swap contacts
                Contact temp =addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
           }
        }
    }
    //Display the contacts 
    printf("%-8s %-20s %-15s %-30s\n","Sl.No", "Name", "Phone", "Email");
    for(int i=0;i<addressBook->contactCount;i++)
         printf("%-8d %-20.20s %-15.15s %-30.30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}

//Initialize the values rom the file
void initialize(AddressBook *addressBook) {
    addressBook->contactCount=0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    //Create temp string
    char temp[50];
    //Get name input
	printf("Enter name:");
    l1:
    scanf(" %50[^\n]",temp);
    //Check first character of name
    if(temp[0]>='A'&& temp[0]<='Z'||temp[0]>='a'&&temp[0]<='z');
    else
    {
        //if not valid name get input again
        printf("Enter valid name:");
        goto l1;
    }
    //Check each character of the name
    for(int i=0;temp[i]!='\0';i++)
    {
        if(temp[i]>='A'&& temp[i]<='Z'||temp[i]>='a'&&temp[i]<='z'||temp[i]>='0'&&temp[i]<='9'||temp[i]==' ')
            continue;
        else
        {
            //if not valid name get input again
            printf("Please enter valid name:");
            goto l1;
        }
    }
    //Once the name is valid copy to address book structure
    if(findContact(addressBook,temp,1)==-1) 
        strcpy(addressBook->contacts[(addressBook->contactCount)].name,temp);
    else
    {
        //if name already in contacts stop
        printf("Name already in contacts\n");
        return;
    }
    //Get phone number input
    printf("Enter phone number:");
    l2:
    scanf(" %20[^\n]",temp);
    //Check if phone number is valid 10 digits
    if(strlen(temp)!=10)
    {
        printf("Please enter valid phone number:");
        goto l2;
    }
    //Check each character in phone number
    for(int i=0;temp[i]!='\0';i++)
    {
        if(temp[i]<'0'||temp[i]>'9')
        {
            //if not valid get input again
            printf("Please enter valid phone number:");
            goto l2;
        }
    }
    //When phone number unique copy to address book
    if(findContact(addressBook,temp,2)==-1) 
        strcpy(addressBook->contacts[(addressBook->contactCount)].phone,temp);
    else
    {
        //if not unique stop
        printf("Phone number already in contacts\n");
        return;
    }
    l3:
    //get email input
    printf("Enter Email:");
    scanf(" %50[^\n]",temp);
    //Check if email is valid
    if(temp[0]>='A'&& temp[0]<='Z'||temp[0]>='a'&&temp[0]<='z');
    else
    {
        //if not valid get input again
        printf("Enter valid email:");
        goto l3;
    }
    //Validate email
    if(validateEmail(temp))
    {
        //if valid copy to addressbook
        if(findContact(addressBook,temp,3)==-1) 
            strcpy(addressBook->contacts[(addressBook->contactCount)].email,temp);
        else
        {
            //if not get input again
            printf("Email already in contacts\n");
            goto l3;
        }
    }
    else
    {
        //if not get input again
        printf("Enter valid email:");
        goto l3;
    }
    //Increment contact count
    addressBook->contactCount++;
    printf("Contact Created\n");

}
//Search contact
void searchContact(AddressBook *addressBook) 
{

    int searchCriteria;
    char temp[50];
    char select[20];
    //Enter any one contact to be searched(name,phone or email)
    printf("Enter the name or phone or email to be searched\n");
    scanf(" %50[^\n]",temp);
    l7:
    printf("Enter Search Criteria:\n 1-Name\n 2-Phone\n 3-Email: ");
    scanf(" %19[^\n]",select);
    //Get input criteria for name phone or email and check criteria validity
    if(strlen(select)>1 && select[0]<'1'||select[0]>'3')
    {
        printf("Invalid Selection\n");
        return;
    }
    searchCriteria=select[0]-'0';
    //convert criteria to integer 
    int index;
    //based on criteria use find contact function to search contact
    switch(searchCriteria)
    {
        case 1:
            index=findContact(addressBook,temp,searchCriteria);
            //Based on return value
            if(index!=-1)
                printf("%d\t%s\t%s\t%s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            else
                printf("Name not in contacts\n");
        break;
        case 2:
            index=findContact(addressBook,temp,searchCriteria);
            //Based on return value
            if(index!=-1)
                printf("%d\t%s\t%s\t%s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            else
                printf("Phone not in contacts\n");
        break;
        case 3:
            index=findContact(addressBook,temp,searchCriteria);
             //Based on return value
            if(index!=-1)
                printf("%d\t%s\t%s\t%s\n",index+1,addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
            else
                printf("Email not in contacts\n");
        break;
        default:
            printf("Enter valid search Criteria\n");
            goto l7;
    }
}
//Edit contact
void editContact(AddressBook *addressBook)
{
    int criteria;
    char temp[50];
    char select[20];
    l5:
    //Get contact input choice
	printf("Enter contact you want to edit:\n1-Name\n2-Phone\n3-Email:");
    scanf(" %19[^\n]",select);
    //Validate criteria
    if(strlen(select)>1 && select[0]<'1'||select[0]>'3')
    {
        printf("Invalid Selection\n");
        goto l5;
    }
    criteria=select[0]-'0';
    //Get contact input
    printf("Enter contact:");
    scanf(" %50[^\n]",temp);
    //Find contact
    int index=findContact(addressBook,temp,criteria);
    int criteria2;
    l8:
    //Select which to edit in contact
    printf("Do you want to edit:\n1-Name\n2-Phone\n3-Email\n4-ALL:");
    scanf(" %19[^\n]",select);
    //Validate choice
    if(strlen(select)>1 && select[0]<'1'||select[0]>'3')
    {
        printf("Invalid Selection\n");
        goto l8;
    }
    criteria2=select[0]-'0';
    //Based on choice get input
    switch(criteria2)
    {
        case 1:
            printf("Enter new Name:");
            scanf(" %50[^\n]",addressBook->contacts[index].name);
            break;
        case 2:
            printf("Enter new Phone:");
            scanf(" %50[^\n]",addressBook->contacts[index].phone);
            break;
        case 3:
            printf("Enter new Email:");
            scanf(" %50[^\n]",addressBook->contacts[index].email);
            break;
        case 4:
            printf("\nEnter new Name:");
            scanf(" %50[^\n]",addressBook->contacts[index].name);
            printf("\nEnter new Phone:");
            scanf(" %50[^\n]",addressBook->contacts[index].phone);
            printf("\nEnter new Email:");
            scanf(" %50[^\n]",addressBook->contacts[index].email);
            break;
        default:
            printf("Enter valid Criteria\n");
            goto l8;
    }
    //Save the edited contact
    printf("Contact Edited\n");
}
//Delete contact
void deleteContact(AddressBook *addressBook)
{
    int criteria;
    char temp[50];
    char select[20];
    l4:
    //Get choice input
	printf("Which contact do you want to delete?\n1-Name\n2-Phone\n3-Email:");
    scanf(" %19[^\n]",select);
    //Validate choice
    if(strlen(select)>1 && select[0]<'1'||select[0]>'3')
    {
        printf("Invalid Selection\n");
        goto l4;
    }
    criteria=select[0]-'0';
    //Get respective contact input
    printf("Enter the contact:");
    scanf(" %50[^\n]",temp);
    //Return index of contact
    int index=findContact(addressBook,temp,criteria);
    if(index!=-1)
    {
        //if contact found shift all other contacts up
        for(int i=index;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        //Decrement count
        printf("Contact Deleted\n");
    }
    //Else contact not found
    else
       printf("Contact not found\n");
        
}
