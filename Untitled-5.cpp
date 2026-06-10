#include <iostream>
#include <string>
using namespace std;
class Faculty {
private:
    string name;
    string employeeID;
public:
    Faculty(string n, string id) {
        name = n;
        employeeID = id;
    }
    string getName() {
        return name;
    }
};
class Course {
private:
    string courseCode;
    string courseName;
    int creditHours;
    Faculty* instructor;
    int maxCapacity;
    int enrolledCount;
public:
    Course(string code, string name, int credits,
           Faculty* inst, int capacity) {
        courseCode = code;
        courseName = name;
        creditHours = credits;
        instructor = inst;
        maxCapacity = capacity;
        enrolledCount = 0;
    }
    void enrollStudent() {
        if (enrolledCount < maxCapacity) {
            enrolledCount++;
            cout << "Student Enrolled Successfully!" << endl;
        } else {
            cout << "Course is Full!" << endl;
        }
    }
    void displayCourse() {
        cout << "\nCourse Code: " << courseCode << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credit Hours: " << creditHours << endl;
        cout << "Instructor: " << instructor->getName() << endl;
        cout << "Maximum Capacity: " << maxCapacity << endl;
        cout << "Enrolled Students: " << enrolledCount << endl;
    }
};
int main() {
    Faculty f1("Ahmed Khan", "F101");
    Course c1("CS201", "Object Oriented Programming",
              3, &f1, 30);
    c1.enrollStudent();
    c1.enrollStudent();
    c1.displayCourse();
    return 0;
}