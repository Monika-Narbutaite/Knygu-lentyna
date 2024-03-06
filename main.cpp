#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Data structure to represent a book
struct Book {
    string title;
    string authorFirstName;
    string authorLastName;
    string borrowedBy;
};

// Function to parse a line from the file and create a Book object
Book parseBook(const string& line) {
    stringstream ss(line);
    Book book;
    getline(ss, book.title, '|');
    getline(ss, book.authorFirstName, '|');
    getline(ss, book.authorLastName, '|');
    getline(ss, book.borrowedBy, '|');
    return book;
}

// Function to sort books by author's last name
bool compareByAuthorLastName(const Book& book1, const Book& book2) {
    return book1.authorLastName < book2.authorLastName;
}

// Function to save books to file
void saveToFile(const vector<Book>& books) {
    ofstream outputFile("books.txt");
    if (!outputFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    for (const auto& book : books) {
        outputFile << book.title << "|" << book.authorFirstName << "|" << book.authorLastName << "|" << book.borrowedBy << endl;
    }

    outputFile.close();
}

int main() {
    vector<Book> books;
    ifstream inputFile("books.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Read books from file
    string line;
    while (getline(inputFile, line)) {
        books.push_back(parseBook(line));
    }

    inputFile.close();

    int choice;
    do {
        cout << "Meniu:\n1. Organize all books by author last name.\n2. Find the book the person borrowed.\n3. Add a new book.\n4. Close the program." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Sort books by author's last name
                sort(books.begin(), books.end(), compareByAuthorLastName);

                // Output sorted books
                for (const auto& book : books) {
                    cout << book.title << " | " << book.authorFirstName << " | " << book.authorLastName << " | " << book.borrowedBy << endl;
                }
                break;
            }
            case 2: {
                string input;
                cout << "Enter name of the person who borrowed it: ";
                cin.ignore();
                getline(cin, input);

                bool found = false;
                for (const auto& book : books) {
                    if (book.title == input || book.borrowedBy == input) {
                        cout << "Book Found: " << book.title << " | " << book.authorFirstName << " | " << book.authorLastName << " | " << book.borrowedBy << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 3: {
                Book newBook;
                cout << "Enter title of the book: ";
                cin.ignore();
                getline(cin, newBook.title);
                cout << "Enter author's first name: ";
                getline(cin, newBook.authorFirstName);
                cout << "Enter author's last name: ";
                getline(cin, newBook.authorLastName);
                newBook.borrowedBy = "";
                books.push_back(newBook);

                // Save the new book to file
                saveToFile(books);

                cout << "New book added successfully." << endl;
                break;
            }
            case 4: {
                // Save the modified data back to the file
                saveToFile(books);

                cout << "Closing the program..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
