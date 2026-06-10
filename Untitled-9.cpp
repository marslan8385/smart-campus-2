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
        cout << "Journal \"" << title
             << "\" checked out successfully."
             << endl;
    }

    void displayInfo() override {
        LibraryItem::displayInfo();
        cout << "ISSN: " << ISSN << endl;
        cout << "Volume: " << volume << endl;
        cout << "Issue Number: " << issueNumber << endl;
    }
};

// Search Function
void searchByTitle(LibraryItem* catalog[],
                   int size,
                   string searchTitle) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (catalog[i]->getTitle() == searchTitle) {
            cout << "\nItem Found:\n";
            catalog[i]->displayInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "Title not found!" << endl;
    }
}

// Save Catalog to File
void saveCatalog(LibraryItem* catalog[], int size) {
    ofstream file("library.txt");

    for (int i = 0; i < size; i++) {
        file << catalog[i]->getItemID()
             << " "
             << catalog[i]->getTitle()
             << endl;
    }

    file.close();
    cout << "\nCatalog saved successfully." << endl;
}

// Load Catalog from File
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
        double fine = lateDays * 25;
        throw OverdueException(fine);
    }

    cout << "Item returned on time." << endl;
}

int main() {

    // Catalog
    LibraryItem* catalog[2];

    catalog[0] = new Journal(
        201,
        "Computer Science Review",
        "John Smith",
        2024,
        "ISSN-1234",
        10,
        2
    );

    catalog[1] = new Journal(
        202,
        "AI Research Journal",
        "David Lee",
        2025,
        "ISSN-5678",
        15,
        1
    );

    // Checkout
    catalog[0]->checkout();

    // Search by Title
    searchByTitle(
        catalog,
        2,
        "AI Research Journal"
    );

    // Save and Load
    saveCatalog(catalog, 2);
    loadCatalog();

    // Issued Item Tracking
    IssuedItem issued[10];

    issued[0].rollNo = 1001;
    issued[0].itemID = 202;

    cout << "\nIssued Record:" << endl;
    cout << "Roll No: "
         << issued[0].rollNo << endl;
    cout << "Item ID: "
         << issued[0].itemID << endl;

    // Overdue Exception
    try {
        returnItem(4);
    }
    catch (OverdueException e) {
        cout << "\nOverdue Item Returned!" << endl;
        cout << "Fine Amount: Rs."
             << e.getFine() << endl;
    }

    // Memory Cleanup
    for (int i = 0; i < 2; i++) {
        delete catalog[i];
    }

    return 0;
}