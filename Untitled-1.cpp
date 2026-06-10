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
    virtual void displayInfo() = 0;
};
class Student : public Person {
public:
    Student(string n, string cnic, int a, string con)
        : Person(n, cnic, a, con) {}
    void displayInfo() override {
        cout << "Name: " << name << endl;  
        cout << "CNIC: " << CNIC << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
    }
};
int main() {
    Student s("Ali", "42101-1234567-1", 20, "03001234567");
    s.displayInfo();
    return 0;
}