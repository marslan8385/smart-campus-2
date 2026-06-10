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
class Book : public LibraryItem {
public:
    Book(int id, string t, string a, int year)
        : LibraryItem(id, t, a, year) {}
    void checkout() override {
        cout << "Book \"" << title
             << "\" checked out successfully." << endl;
    }
};
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
void saveCatalog(LibraryItem* catalog[], int count) {
    ofstream file("library.txt");
    for (int i = 0; i < count; i++) {
        file << catalog[i]->getItemID() << " "
             << catalog[i]->getTitle() << endl;
    }
    file.close();
    cout << "\nCatalog saved to file." << endl;
}
void loadCatalog() {
    ifstream file("library.txt");
    string line;
    cout << "\nCatalog Loaded From File:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
void returnItem(int lateDays) {
    if (lateDays > 0) {
        double fine = lateDays * 20; // Rs.20 per day
        throw OverdueException(fine);
    }
    cout << "Item returned successfully." << endl;
}
int main() {
    LibraryItem* catalog[3];
    catalog[0] = new Book(101, "C++ Programming", "Bjarne", 2020);
    catalog[1] = new Book(102, "Data Structures", "Mark Allen", 2019);
    catalog[2] = new Book(103, "Database Systems", "Korth", 2021);
    int count = 3;
    catalog[0]->checkout();
    searchByTitle(catalog, count, "Data Structures");
    saveCatalog(catalog, count);
    loadCatalog();
    IssuedItem issued[10];
    issued[0].rollNo = 1001;
    issued[0].itemID = 101;
    cout << "\nIssued Item Record:" << endl;
    cout << "Roll No: " << issued[0].rollNo << endl;
    cout << "Item ID: " << issued[0].itemID << endl;
    try {
        returnItem(5); // 5 days late
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item!" << endl;
        cout << "Fine Amount: Rs. "
             << e.getFine() << endl;
    }
    for (int i = 0; i < count; i++) {
        delete catalog[i];
    }
    return 0;
}