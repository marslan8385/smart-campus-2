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

// Student Class
class Student : public Person {
private:
    int rollNo;
    int semester;
    float GPA;
    string enrolledCourses[3];

public:
    Student(string n, string cnic, int a, string con,
            int r, int sem, float g, string courses[])
        : Person(n, cnic, a, con) {
        rollNo = r;
        semester = sem;
        GPA = g;

        for (int i = 0; i < 3; i++) {
            enrolledCourses[i] = courses[i];
        }
    }

    // Override displayInfo()
    void displayInfo() override {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Semester: " << semester << endl;
        cout << "GPA: " << GPA << endl;

        cout << "Enrolled Courses: ";
        for (int i = 0; i < 3; i++) {
            cout << enrolledCourses[i] << " ";
        }
        cout << endl;
    }

    // Calculate Grade
    string calculateGrade() {
        if (GPA >= 3.7)
            return "A";
        else if (GPA >= 3.0)
            return "B";
        else if (GPA >= 2.0)
            return "C";
        else
            return "F";
    }
};

int main() {
    string courses[3] = {"OOP", "DSA", "Database"};

    Student s("Ali", "42101-1234567-1", 20, "03001234567",
              101, 4, 3.5, courses);

    s.displayInfo();

    cout << "Grade: " << s.calculateGrade() << endl;

    return 0;
}