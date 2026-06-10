#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Custom Exception
class OverdueException {
private:
    double fine;

public:
    OverdueException(double f) {
        fine = f;
    }

    double getFine() {
        return fine;
    }
};

// Issued Item Record
struct IssuedItem {
    int rollNo;
    int itemID;
};

// Abstract Base Class
class LibraryItem {
protected:
    int itemID;
    string title;
    string author;
    int publicationYear;

public:
    LibraryItem(int id, string t, string a, int year)
        : itemID(id), title(t), author(a), publicationYear(year) {}

    virtual void checkout() = 0;

    string getTitle() {
        return title;
    }

    int getItemID() {
        return itemID;
    }

    virtual void displayInfo() {
        cout << "\nItem ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publication Year: " << publicationYear << endl;
    }

    virtual ~LibraryItem() {}
};

// Book Class
class Book : public LibraryItem {
private:
    string ISBN;
    string genre;
    int copiesAvailable;

public:
    Book(int id, string t, string a, int year,
         string isbn, string g, int copies)
        : LibraryItem(id, t, a, year) {

        ISBN = isbn;
        genre = g;
        copiesAvailable = copies;
    }

    void checkout() override {
        if (copiesAvailable > 0) {
            copiesAvailable--;
            cout << "Book issued successfully.\n";
        } else {
            cout << "No copies available.\n";
        }
    }

    void displayInfo() override {
        LibraryItem::displayInfo();
        cout << "ISBN: " << ISBN << endl;
        cout << "Genre: " << genre << endl;
        cout << "Copies Available: "
             << copiesAvailable << endl;
    }
};

// Journal Class
class Journal : public LibraryItem {
private:
    string ISSN;
    int volume;
    int issueNumber;

public:
    Journal(int id, string t, string a, int year,
            string issn, int vol, int issue)
        : LibraryItem(id, t, a, year) {

        ISSN = issn;
        volume = vol;
        issueNumber = issue;
    }

    void checkout() override {
        cout << "Journal issued successfully.\n";
    }

    void displayInfo() override {
        LibraryItem::displayInfo();
        cout << "ISSN: " << ISSN << endl;
        cout << "Volume: " << volume << endl;
        cout << "Issue Number: " << issueNumber << endl;
    }
};

// Library Class
class Library {
private:
    LibraryItem* catalog[100];
    int itemCount;

public:
    Library() {
        itemCount = 0;
    }

    void addItem(LibraryItem* item) {
        catalog[itemCount++] = item;
    }

    // Search By Title
    void searchByTitle(string title) {
        bool found = false;

        for (int i = 0; i < itemCount; i++) {
            if (catalog[i]->getTitle() == title) {
                catalog[i]->displayInfo();
                found = true;
            }
        }

        if (!found)
            cout << "Item not found.\n";
    }

    // Save Catalog
    void saveCatalog() {
        ofstream file("library.txt");

        for (int i = 0; i < itemCount; i++) {
            file << catalog[i]->getItemID()
                 << " "
                 << catalog[i]->getTitle()
                 << endl;
        }

        file.close();
        cout << "\nCatalog saved to file.\n";
    }

    // Load Catalog
    void loadCatalog() {
        ifstream file("library.txt");
        string line;

        cout << "\nCatalog Loaded:\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    ~Library() {
        for (int i = 0; i < itemCount; i++) {
            delete catalog[i];
        }
    }
};

// Return Item Function
void returnItem(int lateDays) {
    if (lateDays > 0) {
        double fine = lateDays * 20;
        throw OverdueException(fine);
    }

    cout << "Item returned on time.\n";
}

int main() {

    Library lib;

    // Add Books and Journals
    lib.addItem(new Book(
        101,
        "C++ Programming",
        "Bjarne",
        2020,
        "978-12345",
        "Programming",
        5));

    lib.addItem(new Journal(
        201,
        "AI Research",
        "John Smith",
        2024,
        "ISSN-5678",
        10,
        2));

    // Search
    cout << "\nSearching Title:\n";
    lib.searchByTitle("AI Research");

    // Save and Load
    lib.saveCatalog();
    lib.loadCatalog();

    // Issued Item Tracking
    IssuedItem issued[10];

    issued[0].rollNo = 1001;
    issued[0].itemID = 101;

    cout << "\nIssued Record:\n";
    cout << "Roll No: " << issued[0].rollNo << endl;
    cout << "Item ID: " << issued[0].itemID << endl;

    // Overdue Exception
    try {
        returnItem(5);
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item Returned!\n";
        cout << "Fine Amount = Rs."
             << e.getFine() << endl;
    }

    return 0;
}