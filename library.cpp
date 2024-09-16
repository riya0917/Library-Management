// Program 1: Library Management
// Course: CS 251, Fall 2023, UIC
// Professor: Ethan Ordentlich
// Author: Riya Patel
// The Library Management software application is designed to manage and track the books stored in a library
// This system provides a set of functions and features that enable librarians and users to perform various tasks

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
void printMenu();
void printCheckoutInfo(const string& title, const string& ISBN, const string& checkout);
void addEntry(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void clearLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void displayLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void loadLibrary(string filename, vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void outputFile(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void printCheckout(vector<string>& checkout);
void removeFromLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void searchLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);
void invalidEntries(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout);


int main()
{
    string command, filename, dataFile;
    vector<string> titles;
    vector<string> ISBN;
    vector<string> checkout;
    
    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        //Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";
        getline(cin, command);

       //Execute non-exit commands
        if(command == "a" || command == "A"){
            addEntry(titles, ISBN, checkout);
        }
        else if(command == "c" || command == "C"){ 
            clearLibrary(titles, ISBN, checkout); 
            }
        else if(command == "d" || command == "D"){
            displayLibrary(titles, ISBN, checkout);
        }
        else if(command == "i" || command == "I"){ 
            invalidEntries(titles, ISBN, checkout);    
        }   
        else if(command == "l" || command == "L"){
            cout << endl << "What database to read from? ";
            getline(cin, dataFile);
            loadLibrary(dataFile, titles, ISBN, checkout);
        }
        else if(command == "p" || command == "P"){  
            printCheckout(checkout);
        }
        else if(command == "o" || command == "O"){ 
            outputFile(titles, ISBN, checkout);
        }
        else if(command == "r" || command == "R"){
             removeFromLibrary(titles, ISBN, checkout);    
        }
        else if(command == "s" || command == "S"){ 
            searchLibrary(titles, ISBN, checkout);
        }
        cout << endl;
    } while (!(command == "x" || command == "X"));
        cout << endl;
    return 0;
}

void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

//This function is intended to print the title, ISBN and the specific location of the book
void printCheckoutInfo(const string& title, const string& ISBN, const string& checkout) {
    cout << title << " --- " << ISBN << " --- ";
    if (checkout == "1") {
        cout << "Checked Out";
    } else if (checkout == "2") {
        cout << "On Loan";
    } else if (checkout == "3") {
        cout << "Unknown State";
    } else if (checkout >= "4") {
        cout << "Invalid State";
    } else {
        cout << "In Library"; // Default state
    }
    cout << endl;
}

//This function is intended to add a book entry manually with the book name and book isbn
void addEntry(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){
    string bookTitle, bookCode, bookCheckout = "0";
    
    cout << endl << "What is the book title? ";
    getline(cin >> ws, bookTitle);

    if(bookTitle.find(',') != string::npos){
        cout << "The book title cannot contain commas." << endl;
        return;
    }
        cout << endl << "What is the 13-digit ISBN (with hyphens)? ";
        getline(cin, bookCode);
        
        titles.push_back(bookTitle);
        ISBN.push_back(bookCode);
        checkout.push_back(bookCheckout);
        
    

    cout << endl << "The Following Entry Was Added" << endl;
    cout << "-----------------------------" << endl;
    printCheckoutInfo(bookTitle, bookCode, bookCheckout);

}

//This function is intended to clear all the books from the database
void clearLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){
    //when using the erase function, the indexes are shifted to the left each time so a reverse loop 
    for(int i = titles.size() - 1; i >= 0; i--){
        titles.erase(titles.begin() + i);
        ISBN.erase(ISBN.begin() + i);
        checkout.erase(checkout.begin() + i);
    }
    cout << endl << "Your library is now empty." << endl;
}

//This function is intended to display the title, ISBN code and checkout statur for all the books
void displayLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){
    cout << endl << "Your Current Library" << endl;
    cout << "--------------------" << endl;
    if(titles.size() != 0 ){
      for(int i = 0; i < titles.size(); i++){
        printCheckoutInfo(titles.at(i), ISBN.at(i), checkout.at(i));
      }
    }else{
        cout << "The library has no books." << endl;
    }
}

//This function is intended to output invalid entries
void invalidEntries(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){
    cout << endl << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;
    bool found = false;
    if(titles.size() == 0) {
        cout << "The library has no books." << endl;
        return;
    }
    for(int i = 0; i < ISBN.size(); i++) {
        string cleanISBN = "";
        for(int j = 0; j < ISBN.at(i).size(); j++) {
            if(isdigit(ISBN.at(i)[j])) {
                cleanISBN += ISBN.at(i)[j];
            }
        }
        int sum = 0;
        for (int k = 0; k < 12; k++) {
            int eachDigit = cleanISBN[k] - '0';
            if(k % 2 == 0) {
                sum += eachDigit;
            }else{
                sum += 3 * eachDigit;
            }
        }

        int finalDigit = cleanISBN[12] - '0';
        int checkDigit = 10 - (sum % 10);
        if(checkDigit == 10){
            checkDigit = 0;
        }
        if(checkDigit != finalDigit || cleanISBN.size() != 13 || (checkout.at(i) >= "4" || checkout.at(i) < "0")) {
            printCheckoutInfo(titles.at(i), ISBN.at(i), checkout.at(i));
            found = true;
        }
    }
    if(!found){
        cout << "The library has no invalid entries." << endl;
    }
}

//This function is intended to read in data from a csv file and store the data in corresponding vectors
void loadLibrary(string filename, vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){
    string line, bookTitle, bookCode, bookCheckout;
    ifstream file;
    file.open(filename);
    int count = 0;

    if(!file.is_open()){
        cout << endl << "Could not find the database file." << endl;
        return;

    }else{
        while(getline(file, line)){
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);
            //checks if a comma is found in the line
            if(firstComma != string::npos){
                bookTitle = line.substr(0, firstComma);
                //accounts for the case where title, ISBN and checkout code is there
                if(secondComma != string::npos){
                    //- 2 and + 2 makes sure no commas are added in the vectors
                    bookCode = line.substr(firstComma + 2, secondComma - firstComma - 2); 
                    bookCheckout = line.substr(secondComma + 2);
                }else{
                    //accounts for the case there is no checkout code
                    bookCode = line.substr(firstComma + 2);
                    //default in library
                    bookCheckout = "0";
                }
            }else{
                //accounts for the case that there is only a title
                bookTitle = line;
                bookCode = "000-0-00-000000-0";
                bookCheckout = "0";

            }
            titles.push_back(bookTitle);
            ISBN.push_back(bookCode);
            checkout.push_back(bookCheckout);
            count++;
        }
    }
    cout << endl << "Read in " << count << " lines from the file." << endl;
}

//This function is intended to output the data into a new text file using ofstream;
void outputFile(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout){

    string output;
    int count = 0;
    cout << endl << "Where should the database output to? ";
    getline(cin >> ws, output);
    ofstream fstr(output);
    for(int i = 0; i < titles.size(); i++){
        fstr << titles.at(i) << ", " << ISBN.at(i) << ", " << checkout.at(i) << endl;
        count++;
    }
    cout << endl << count << " lines of data written to " << output << endl;
}

//This function is intended to print out the checkout status of all the books in the database
void printCheckout(vector<string>& checkout){
    int bookOut = 0, bookOnLoan = 0, bookUnknownState = 0, bookInvalidState = 0, bookInLibrary = 0, bookTotal = 0;
    cout << endl << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;
    for(int i = 0; i < checkout.size(); i++){
        if(checkout.at(i) == "1"){
           bookOut++;
        }else if(checkout.at(i) == "2"){
            bookOnLoan++;
        }else if(checkout.at(i) == "3"){
            bookUnknownState++;
        }else if(checkout.at(i) >= "4"){
            bookInvalidState++;
        }else{
            bookInLibrary++;
        }
        bookTotal++;
    }
    cout << "Total Books: " << bookTotal << endl;
    cout << "   In Library: " << bookInLibrary << endl;
    cout << "   Checked Out: " << bookOut << endl;
    cout << "   On Loan: " << bookOnLoan << endl;
    cout << "   Unknown: " << bookUnknownState << endl;
    cout << "   Other: " << bookInvalidState << endl;

}

//This function is intended to erase a book entry
void removeEntry(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout, int index) {
    cout << "\nThe Following Entry Was Removed From The Library\n";
    cout << "------------------------------------------------\n";
    printCheckoutInfo(titles.at(index), ISBN.at(index), checkout.at(index));
    titles.erase(titles.begin() + index); 
    ISBN.erase(ISBN.begin() + index);
    checkout.erase(checkout.begin() + index);
}

//This function is intended to remove a book entry and display it on the output
void removeFromLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout) {
    string numChoice, bookChoice, ISBNChoice;
    bool found = false;
    
    cout << endl <<  "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin >> ws, numChoice);
    
    if(numChoice == "1"){
        cout << "\nEnter the book name: ";
        getline(cin >> ws, bookChoice);
        for(int i = titles.size() - 1; i >= 0; i--) { 
            if(titles.at(i) == bookChoice) {
                removeEntry(titles, ISBN, checkout, i);
                return;
            }
        }
    }else if(numChoice == "2"){
        cout << endl << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin >>ws, ISBNChoice);
        for (int i = ISBN.size() - 1; i >= 0; i--) { 
            if(ISBN.at(i) == ISBNChoice) {
                removeEntry(titles, ISBN, checkout, i);
                return;
            }
        }
    }else{
        cout << "\nInvalid remove by choice option." << endl;
        return;
    }
    if(!found){
        cout << "\nThe Following Entry Was Removed From The Library\n";
        cout << "------------------------------------------------\n";
        cout << "No matching entry found in the library.\n";
        return;
    }
}

//This function is intended to search and display a book entry;
void searchEntry(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout, int index){
    cout << endl << "The Following Are Your Search Results" << endl;
            cout << "-------------------------------------" << endl;
            printCheckoutInfo(titles.at(index), ISBN.at(index), checkout.at(index));
}

//This function is intended to search for a book entry and display it on the output
void searchLibrary(vector<string>& titles, vector<string>& ISBN, vector<string>& checkout) {
    string numChoice, bookChoice, ISBNChoice;
    bool found = false;

    cout << endl << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin >> ws, numChoice);

    if(numChoice == "1"){
        cout << endl << "Enter the book name: ";
        getline(cin >> ws, bookChoice);
        for(int i = titles.size() - 1; i >= 0; i--){
            if(titles.at(i) == bookChoice){
                searchEntry(titles, ISBN, checkout, i);
                found = true;
                return;
            }
        }
    }else if(numChoice == "2"){
        cout << endl << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin >> ws, ISBNChoice);
        for(int i = ISBN.size() - 1; i >= 0; i--){
            if(ISBN.at(i) == ISBNChoice){
                searchEntry(titles, ISBN, checkout, i);
                found = true;
                return;
            }
        }
    }else{
        cout << endl << "Invalid search by choice option." << endl;
        return;
    }

    if(!found){
        cout << endl << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        cout << "No matching entry found in the library." << endl;
        return;
    }
}
