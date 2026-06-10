#include <iostream>
#include <string>
using namespace std;

class Invoice {
private:
    static int nextID;   
    int invoiceID;
    string date;
    string items;
    float totalAmount;

public:
    
    Invoice(string d, string i, float amount) {
        invoiceID = ++nextID;
        date = d;
        items = i;
        totalAmount = amount;
    }

    void displayInvoice() {
        cout << "Invoice ID: " << invoiceID << endl;
        cout << "Date: " << date << endl;
        cout << "Items: " << items << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "------------------------" << endl;
    }
};


int Invoice::nextID = 0;

int main() {
    Invoice inv1("10-06-2026", "Laptop, Mouse", 85000);
    Invoice inv2("11-06-2026", "Keyboard, Headphones", 12000);

    inv1.displayInvoice();
    inv2.displayInvoice();

    return 0;
}