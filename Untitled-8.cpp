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

// Structure for Issued Items
struct IssuedItem {
    int rollNo;
    int itemID;
};

// Abstract Class
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

    virtual void checkout() = 0;

    string getTitle() {
        return title;
    }

    int getItemID() {
        return itemID;
    }

    virtual void displayInfo() {
        cout << "Item ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publication Year: " << publicationYear << endl;
    }
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

// Search Function
void searchByTitle(LibraryItem* catalog[],
                   int size,
                   string searchTitle) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (catalog[i]->getTitle() == searchTitle) {
            cout << "\nBook Found:\n";
            catalog[i]->displayInfo();
            found = true;
        }
    }

    if (!found)
        cout << "Title not found.\n";
}

// Save Catalog
void saveCatalog(LibraryItem* catalog[], int size) {
    ofstream file("library.txt");

    for (int i = 0; i < size; i++) {
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

    cout << "\nCatalog Data:\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Return Item
void returnItem(int lateDays) {
    if (lateDays > 0) {
        double fine = lateDays * 20;
        throw OverdueException(fine);
    }

    cout << "Book returned on time.\n";
}

int main() {

    // Library Catalog
    LibraryItem* catalog[2];

    catalog[0] = new Book(
        101,
        "C++ Programming",
        "Bjarne Stroustrup",
        2020,
        "978-12345",
        "Programming",
        5
    );

    catalog[1] = new Book(
        102,
        "Data Structures",
        "Mark Allen",
        2019,
        "978-67890",
        "Computer Science",
        3
    );

    // Checkout
    catalog[0]->checkout();

    // Search By Title
    searchByTitle(
        catalog,
        2,
        "Data Structures"
    );

    // Save and Load
    saveCatalog(catalog, 2);
    loadCatalog();

    // Issued Items Tracking
    IssuedItem issued[10];

    issued[0].rollNo = 1001;
    issued[0].itemID = 101;

    cout << "\nIssued Record:\n";
    cout << "Roll No: "
         << issued[0].rollNo << endl;

    cout << "Item ID: "
         << issued[0].itemID << endl;

    // Overdue Exception
    try {
        returnItem(4);
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item Returned!\n";
        cout << "Fine = Rs."
             << e.getFine()
             << endl;
    }

    // Memory Cleanup
    for (int i = 0; i < 2; i++) {
        delete catalog[i];
    }

    return 0;
}