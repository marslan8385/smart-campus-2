#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Custom Exception Class
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

// Structure for Issued Items
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
    LibraryItem(int id, string t, string a, int year) {
        itemID = id;
        title = t;
        author = a;
        publicationYear = year;
    }

    virtual void checkout() = 0; // Pure Virtual Function

    string getTitle() {
        return title;
    }

    int getItemID() {
        return itemID;
    }

    void displayInfo() {
        cout << "Item ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publication Year: " << publicationYear << endl;
    }
};

// Derived Class
class Book : public LibraryItem {
public:
    Book(int id, string t, string a, int year)
        : LibraryItem(id, t, a, year) {}

    void checkout() override {
        cout << "Book \"" << title
             << "\" checked out successfully." << endl;
    }
};

// Search Function
void searchByTitle(LibraryItem* catalog[], int count, string searchTitle) {
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (catalog[i]->getTitle() == searchTitle) {
            cout << "\nBook Found:\n";
            catalog[i]->displayInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "\nBook not found!" << endl;
    }
}

// Save Catalog to File
void saveCatalog(LibraryItem* catalog[], int count) {
    ofstream file("library.txt");

    for (int i = 0; i < count; i++) {
        file << catalog[i]->getItemID() << " "
             << catalog[i]->getTitle() << endl;
    }

    file.close();
    cout << "\nCatalog saved to file." << endl;
}

// Load Catalog from File
void loadCatalog() {
    ifstream file("library.txt");

    string line;

    cout << "\nCatalog Loaded From File:\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Return Item Function
void returnItem(int lateDays) {
    if (lateDays > 0) {
        double fine = lateDays * 20; // Rs.20 per day
        throw OverdueException(fine);
    }

    cout << "Item returned successfully." << endl;
}

int main() {

    // Catalog Array
    LibraryItem* catalog[3];

    catalog[0] = new Book(101, "C++ Programming", "Bjarne", 2020);
    catalog[1] = new Book(102, "Data Structures", "Mark Allen", 2019);
    catalog[2] = new Book(103, "Database Systems", "Korth", 2021);

    int count = 3;

    // Checkout
    catalog[0]->checkout();

    // Search
    searchByTitle(catalog, count, "Data Structures");

    // Save and Load
    saveCatalog(catalog, count);
    loadCatalog();

    // Issued Items Tracking
    IssuedItem issued[10];

    issued[0].rollNo = 1001;
    issued[0].itemID = 101;

    cout << "\nIssued Item Record:" << endl;
    cout << "Roll No: " << issued[0].rollNo << endl;
    cout << "Item ID: " << issued[0].itemID << endl;

    // Overdue Exception
    try {
        returnItem(5); // 5 days late
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item!" << endl;
        cout << "Fine Amount: Rs. "
             << e.getFine() << endl;
    }

    // Memory Cleanup
    for (int i = 0; i < count; i++) {
        delete catalog[i];
    }

    return 0;
}