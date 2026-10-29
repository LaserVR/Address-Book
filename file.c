#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    //Open file in write mode
    FILE *fp=fopen("addressbook.csv","w");
    //Check for NULL value
    if (fp == NULL) 
    {
        printf("Error: Could not open addressbook.csv for writing!\n");
        return;
    }
    //Save the Contact count in first line in file
    fprintf(fp,"%d\n",addressBook->contactCount);
    //Save each contact line by line in the file
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    //Close the file
    fclose(fp);
}
void loadContactsFromFile(AddressBook *addressBook) 
{
    //Count temp variable
    int count;
    //open file to load contacts
    FILE *fp=fopen("addressbook.csv","r");
    //Check for null pointer
    if(fp==NULL) 
    {
        //Error message
        printf("Error: Could not open addressbook.csv for reading!\n");
        return; 
    }
    //Read the contact from CSV file
    fscanf(fp,"%d\n",&count);
    //Check if address book is empty
    if(count==0)
    {
        printf("Addressbook is empty\n");
        return;
    }
    else
        //if not empty add count
        addressBook->contactCount=count;

    //Read contacts from file one by one
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    //Close the file
    fclose(fp);
}

