#include <iostream>
#include <fstream>
#include <string>
using namespace std;
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
struct IssuedItem {
    int rollNo;
    int itemID;
};
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
void loadCatalog() {
    ifstream file("library.txt");
    string line;
    cout << "\nCatalog Data:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
void returnItem(int lateDays) {
    if (lateDays > 0) {
        double fine = lateDays * 20;
        throw OverdueException(fine);
    }
    cout << "Book returned on time.\n";
}
int main() {
    LibraryItem* catalog[2];
    catalog[0] = new Book(
        101,
        "C++ Programming",
        "Ahmed Ali",
        2020,
        "978-12345",
        "Programming",
        5
    );
    catalog[1] = new Book(
        102,
        "Data Structures",
        "Farhan ",
        2019,
        "978-67890",
        "Computer Science",
        3
    );
    catalog[0]->checkout();
    searchByTitle(
        catalog,
        2,
        "Data Structures"
    );
    saveCatalog(catalog, 2);
    loadCatalog();
    IssuedItem issued[10];
    issued[0].rollNo = 1001;
    issued[0].itemID = 101;
    cout << "\nIssued Record:\n";
    cout << "Roll No: "
         << issued[0].rollNo << endl;
    cout << "Item ID: "
         << issued[0].itemID << endl;
    try {
        returnItem(4);
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item Returned!\n";
        cout << "Fine = Rs."
             << e.getFine()
             << endl;
    }
    for (int i = 0; i < 2; i++) {
        delete catalog[i];
    }
    return 0;
}