#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
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

// Faculty Class
class Faculty : public Person {
private:
    int employeeID;
    string department;
    string designation;
    string assignedCourses[3];

public:
    Faculty(string n, string cnic, int a, string con,
            int id, string dept, string desig, string courses[])
        : Person(n, cnic, a, con) {

        employeeID = id;
        department = dept;
        designation = desig;

        for (int i = 0; i < 3; i++) {
            assignedCourses[i] = courses[i];
        }
    }

    // Override displayInfo()
    void displayInfo() override {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Employee ID: " << employeeID << endl;
        cout << "Department: " << department << endl;
        cout << "Designation: " << designation << endl;

        cout << "Assigned Courses: ";
        for (int i = 0; i < 3; i++) {
            cout << assignedCourses[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    string courses[3] = {"OOP", "Database", "Data Structures"};

    Faculty f("Ahmed Khan", "42101-1234567-1", 35, "03001234567",
              5001, "Computer Science", "Assistant Professor", courses);

    f.displayInfo();

    return 0;
}