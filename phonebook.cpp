/*

		Contact book programe that tracks name, mobile number, email and group

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

// Utility function to get user choice from 1 to num
int getChoice(int num)
{
	cout << "Enter Your Choice (from 1 to " << num << "):  ";
	string s;
	
	// Check on whether the given number is from 1 to num
	while (getline(cin, s) )
	{
		bool valid = true;
		int choice = 0;
		for (char k : s)
		{
			if (!isdigit(k) ) valid = false;
			else
			{
				choice *= 10;
				choice += k - '0';
			}
		}
		if (choice < 1 || choice > num) valid = false;
		
		// If it is number, return the value
		if (valid) return choice;
		else cout << "Please enter a number from 1 to " << num << ": ";
	}
	
	return 0;
}

// Contact class to store every contact
class Contact
{
	public:
	
	// Variables storing contact's information
	string name, number, email, group;
	
	// Utility function to create new contact
	void newContact()
	{
		cout << "\n.......CREATE NEW CONTACT.........\n";
		cout << "Enter Name          : ";
		getline(cin, name);
        cout << "Enter Mobile Number : ";
		getline(cin, number);
		
		// Simple check on whether the number given is actually a number
		while (true)
		{
			bool allDigits = true;
			for (char x: number)
			{
				if (!isdigit(x) ) allDigits = false;
			}
			if (allDigits) break;
			cout << "Please input only digits from 0-9\n";
			cout << "Enter Mobile Number : ";
			getline(cin, number);
		}
		
        cout << "Enter Email         : ";
		getline(cin, email);
        cout << "Enter Group         : ";
		getline(cin, group);
		cout << endl;
	}
	
	// Utility function to print contact
	void showData()
	{
        cout << "Name       : " << name << endl;
        cout << "Mobile No. : " << number << endl;
        cout << "Email      : " << email << endl;
        cout << "Group      : " << group << endl;
	}
	
	// Utility functions for custom comparators
	bool operator < (const Contact &other) const
	{
		string a = this->name + this->number + this->email + this->group;
		string b = other.name + other.number + other.email + other.group;
		return a < b;
	}
	bool operator == (const Contact &other) const
	{
		return name == other.name && number == other.number && email == other.email && group == other.group;
	}
};

// List to store the contacts in contact book
vector <Contact> contacts;
// BST for searching contacts by name, number, email or group
map <string, multiset<Contact> > forLookup[4];

// Utility function to add a contact
void addContact(Contact contact)
{
	contacts.push_back(contact);
	forLookup[0][contact.name].insert(contact);
	forLookup[1][contact.number].insert(contact);
	forLookup[2][contact.email].insert(contact);
	forLookup[3][contact.group].insert(contact);
}

// Function to create new contact
void createNewContact()
{
	Contact contact;
	contact.newContact();
	addContact(contact);
}

// Utility function to display all contacts
void displayAllContacts()
{
	cout << "\n...............CONTACT BOOK RECORD...............\n";
	for (int i = 0; i < (int) contacts.size(); i++)
	{
		cout << i+1 << endl;
		contacts[i].showData();
	}
}

// Function to search for a specific contact
void searchContact()
{
	cout << "\n::::::::::::::: PROGRAM MENU :::::::::::::::\n";
	cout << "How would you like to search your contact?\n";
    cout << "1. Name\n";
    cout << "2. Mobile Number\n";
    cout << "3. Email\n";
    cout << "4. Group\n";
    int choice = getChoice(4);
    
    switch (choice)
    {
		case 1: cout << "Enter your contact's name: ";
		break;
		case 2: cout << "Enter your contact's mobile number: ";
		break;
		case 3: cout << "Enter your contact's email: ";
		break;
		case 4: cout << "Enter your contact's group: ";
		break;
	}
	string s;
	getline(cin, s);
	
	// Check that the contact exists
	if (forLookup[choice - 1][s].empty() )
	{
		cout << "No such contact exists.\n\n";
		return;
	}
	
	// Print all valid contacts
	int num = 0;
	for (Contact contact: forLookup[choice - 1][s])
	{
		num++;
		cout << num << endl;
		contact.showData();
	}
}

// Function to delete a specific contact
void deleteContact()
{
	displayAllContacts();
	cout << "Which contact would you like to delete? ";
	int choice = getChoice(contacts.size()) - 1;
	
	Contact contact = contacts[choice];
	contacts.erase(contacts.begin() + choice);
	forLookup[0][contact.name].erase(forLookup[0][contact.name].find(contact));
	forLookup[1][contact.number].erase(forLookup[1][contact.number].find(contact));
	forLookup[2][contact.email].erase(forLookup[2][contact.email].find(contact));
	forLookup[3][contact.group].erase(forLookup[3][contact.group].find(contact));
}

// Function to modify a specific contact
void modifyContact()
{
	displayAllContacts();
	cout << "Which contact would you like to modify? ";
	int choice = getChoice(contacts.size()) - 1;
	Contact contact = contacts[choice];
	
	// Delete old data
	forLookup[0][contact.name].erase(forLookup[0][contact.name].find(contact));
	forLookup[1][contact.number].erase(forLookup[1][contact.number].find(contact));
	forLookup[2][contact.email].erase(forLookup[2][contact.email].find(contact));
	forLookup[3][contact.group].erase(forLookup[3][contact.group].find(contact));
	
	cout << "What would you like to modify?:\n";
	cout << "1. Name\n";
    cout << "2. Mobile Number\n";
    cout << "3. Email\n";
    cout << "4. Group\n";
    int newChoice = getChoice(4);
    switch(newChoice)
    {
		case 1:
		{
			cout << "Enter your contact's new name: ";
			string newName;
			getline(cin, newName);
			contact.name = newName;
			break;
		}
		case 2:
		{
			cout << "Enter your contact's new mobile number: ";
			string newNumber;
			getline(cin, newNumber);
			contact.number = newNumber;
			break;
		}
		case 3:
		{
			cout << "Enter your contact's new email: ";
			string newEmail;
			getline(cin, newEmail);
			contact.email = newEmail;
			break;
		}
		case 4:
		{
			cout << "Enter your contact's new group: ";
			string newGroup;
			getline(cin, newGroup);
			contact.group = newGroup;
			break;
		}
	}
	
	// Modify contact details
	contacts[choice] = contact;
	
	// Insert new data
	forLookup[0][contact.name].insert(contact);
	forLookup[1][contact.number].insert(contact);
	forLookup[2][contact.email].insert(contact);
	forLookup[3][contact.group].insert(contact);
}

// Main menu for contact book
void menu2()
{
	cout << "\n............................................\n";
    cout << "          CONTACT BOOK MANAGEMENT\n";
    cout << "............................................\n\n";
    cout << "::::::::::::::: PROGRAM MENU :::::::::::::::\n";
    cout << "1. Save New Contact\n";
    cout << "2. Display All Saved Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Modify Contact\n";
    cout << "6. Save and Exit\n";
    int choice = getChoice(6);
    
    switch(choice)
    {
		case 1: createNewContact();
		break;
		case 2: displayAllContacts();
		break;
		case 3: searchContact();
		break;
		case 4: deleteContact();
		break;
		case 5: modifyContact();
		break;
		case 6: return;
	}
	menu2();
}

// Utility variables
string fileName;
bool exitProgram;

// Utility function to open a file
void openFile()
{
	ifstream myFile(fileName + ".txt");
	Contact contact;
	while (getline(myFile, contact.name) )
	{
		getline(myFile, contact.number);
		getline(myFile, contact.email);
		getline(myFile, contact.group);
		addContact(contact);		
	}
	myFile.close();
	return;
}

// Utility function to close the file and save all edits
void closeFile()
{
	ofstream myFile(fileName + ".txt");
	for (Contact contact: contacts)
	{
		myFile << contact.name << endl;
		myFile << contact.number << endl;
		myFile << contact.email << endl;
		myFile << contact.group << endl;
	}
	myFile.close();
	return;
}

// Front menu for contact book
void menu1()
{
	cout << "............................................\n";
    cout << "          CONTACT BOOK MANAGEMENT\n";
    cout << "............................................\n\n";
    cout << "This is a contact book program which stores your contact's various information: name, mobile number, email and group.\n\n";
    cout << "::::::::::::::: PROGRAM MENU :::::::::::::::\n";
    cout << "1. Create a new contact book or access an existing contact book\n";
    cout << "2. Exit\n";
    int choice = getChoice(2);
	if (choice == 1)
	{
		cout << "Note:\n";
		cout << "If contact book already exists, the old contact book will be accessed and edited.\n";
		cout << "Otherwise, a new contact book will be created.\n";
		cout << "Enter the name of your contact book: ";
		getline(cin, fileName);
	}
	else if (choice == 2)
	{
		exitProgram=true;
		return;
	}
	return;
}

int main()
{
    menu1();
    if (exitProgram) return 0;
    openFile();
    menu2();
    closeFile();
    return 0;
}
