📒 Address Book Management System in C

An Address Book Management System developed in C to store, manage, search, edit, delete, and sort contacts. The project also implements CSV file handling so that contacts remain stored even after the program exits.

Features

- Add new contacts
- Search contacts
- Edit existing contacts
- Delete contacts
- Display all contacts
- Sort contacts by:
  - Name
  - Phone number
  - Email
- 💾 Save contacts to a CSV file
- 📂 Load contacts automatically when the program starts
- 🧩 Modular implementation using multiple `.c` and `.h` files
- 🛡️ Basic input validation

🛠️ Technologies Used

- Language: C
- Compiler: GCC
- Data Storage: CSV file
- Concepts Used:
  - Structures
  - Pointers
  - Arrays
  - Strings
  - Functions
  - File Handling
  - Searching
  - Sorting
  - Modular Programming

## 📁 Project Structure
AddressBook
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── contacts.txt
├── addressbook.csv
└── README.md

🧱 Data Structures

The project uses structures to represent individual contacts and the complete address book.

Each contact contains:

- Name
- Phone number
- Email address

The AddressBook structure stores up to 100 contacts.

🔄 How It Works
1. Program Initialization

When the program starts, the address book is initialized and existing contacts are loaded from: addressbook.csv

If the file does not exist, the program can start with an empty address book.

2. Create Contact
The user enters the contact's:

Name
Phone
Email

The contact is stored in the AddressBook structure.

3. Search Contact

Contacts can be searched using:
- Name
- Phone number
- Email

strcmp() is used for exact matching, while strstr() can be used when partial matching is required.

4. Edit Contact
The user first searches for an existing contact and then selects which information to modify:

1. Name
2. Phone
3. Email
4. All
5. Delete Contact

A contact can be located using its identifying information and removed from the address book.

6. Sort Contacts

Contacts can be sorted using Bubble Sort based on:

1. Name
2. Phone
3. Email

The project uses strcmp() to compare string fields.

7. File Storage
Contacts are stored in CSV format:

Name,Phone,Email

For example:

John,9876543210,john@gmail.com
Alice,9123456780,alice@gmail.com

The contacts are written using `fprintf()` and loaded using `fscanf()`.

💾 Data Persistence

One of the important improvements in the project was implementing persistent storage.

Initially, contacts were stored only in memory:

Program starts
      ↓
Contacts stored in RAM
      ↓
Program exits
      ↓
Contacts lost

File handling was added to solve this:

Program starts
      ↓
Load contacts from CSV
      ↓
Modify address book
      ↓
Save contacts to CSV
      ↓
Program exits
      ↓
Contacts remain stored


 📌 Example Menu

===== ADDRESS BOOK =====

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List Contacts
6. Save and Exit

Enter your choice:

Done By: Vinay Rohan S BE.

⭐ If you found this project useful, feel free to explore the source code and give it a star!
