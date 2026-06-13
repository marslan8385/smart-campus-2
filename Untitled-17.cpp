#include <iostream>
using namespace std;

class Reports {
public:
    void campusReport() {
        cout << "\n===== Campus Report =====" << endl;
        cout << "Total Students      : 500" << endl;
        cout << "Total Teachers      : 40" << endl;
        cout << "Total Classrooms    : 25" << endl;
        cout << "Hostel Occupancy    : 80%" << endl;
        cout << "Library Books       : 10000" << endl;
        cout << "=========================" << endl;
    }

    void studentReport() {
        cout << "\n===== Student Report =====" << endl;
        cout << "Name      : Ali" << endl;
        cout << "Roll No   : CS-101" << endl;
        cout << "Semester  : 3" << endl;
        cout << "CGPA      : 3.75" << endl;
        cout << "==========================" << endl;
    }

    void hostelReport() {
        cout << "\n===== Hostel Report =====" << endl;
        cout << "Total Rooms     : 100" << endl;
        cout << "Occupied Rooms  : 80" << endl;
        cout << "Vacant Rooms    : 20" << endl;
        cout << "=========================" << endl;
    }
};

int main() {
    Reports r;

    r.campusReport();
    r.studentReport();
    r.hostelReport();

    return 0;
}