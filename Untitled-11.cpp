#include <iostream>
using namespace std;

class FeeRecord {
private:
    int studentRef;
    float semesterFee;
    float hostelFee;
    float libraryFine;
    float totalPaid;
    float balance;

public:
    // Constructor
    FeeRecord(int ref, float semFee, float hostFee, float fine, float paid) {
        studentRef = ref;
        semesterFee = semFee;
        hostelFee = hostFee;
        libraryFine = fine;
        totalPaid = paid;

        balance = (semesterFee + hostelFee + libraryFine) - totalPaid;
    }

    // Display Fee Record
    void displayRecord() {
        cout << "Student Ref: " << studentRef << endl;
        cout << "Semester Fee: " << semesterFee << endl;
        cout << "Hostel Fee: " << hostelFee << endl;
        cout << "Library Fine: " << libraryFine << endl;
        cout << "Total Paid: " << totalPaid << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    FeeRecord f1(101, 50000, 10000, 500, 45000);

    f1.displayRecord();

    return 0;
}