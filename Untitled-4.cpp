#include <iostream>
#include <string>
using namespace std;
class Person {
protected:
    string name;
    string CNIC;
    int age;
    string contact;
public:
    Person(string n, string cnic, int a, string con)
        : name(n), CNIC(cnic), age(a), contact(con) {}
    virtual void displayInfo() = 0; // Pure Virtual Function
};
class Staff : public Person {
private:
    int staffID;
    string role;
    float salary;
public:
    Staff(string n, string cnic, int a, string con,
          int id, string r, float s)
        : Person(n, cnic, a, con) {
        staffID = id;
        role = r;
        salary = s;
    }
    void displayInfo() override {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Staff ID: " << staffID << endl;
        cout << "Role: " << role << endl;
        cout << "Salary: " << salary << endl;
    }
};
int main() {
    Staff s("Ali Raza", "42101-1234567-1", 30,
            "03001234567", 1001, "Lab Assistant", 45000);
    s.displayInfo();
    return 0;
}