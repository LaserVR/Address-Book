/*
    Name:Vinay Rohan S
    Roll No:26015_275
    Start Date:31/08/26
    End Date:06/09/26
    Class:26018c
    Project 1 : AddressBook Design with C
    Functions:
        Create Contact
        Search Contact
        Edit Contact
        List Contact
        Delete Contact
        Store and retrieve contacts rom CSV file
*/
#include <stdio.h>
#include "contact.h"

int main() 
{
    //Get choice input from user to do specific task
    int choice;
    AddressBook addressBook;
    //Load 
    initialize(&addressBook); // Initialize the address book
    int sortCriteria;
    //Choice selection
    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch ((int)choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice!=6 && choice>=7);
    //if choice is 7 or 6 exit otherwise invalid
    return 0;
}
