#include <iostream>
#include <string>
#include <ctime>
#include <cctype>

using namespace std;

class Utils {
public:

    // Convert string to uppercase
    static string toUpper(string text) {
        for (char &ch : text) {
            ch = toupper(ch);
        }
        return text;
    }

    // Convert string to lowercase
    static string toLower(string text) {
        for (char &ch : text) {
            ch = tolower(ch);
        }
        return text;
    }

    // Display current date
    static void displayDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        cout << "Current Date: "
             << ltm->tm_mday << "/"
             << 1 + ltm->tm_mon << "/"
             << 1900 + ltm->tm_year << endl;
    }

    // Check if string contains only digits
    static bool isNumeric(string str) {
        for (char ch : str) {
            if (!isdigit(ch))
                return false;
        }
        return !str.empty();
    }

    // Check if age is valid
    static bool isValidAge(int age) {
        return (age >= 1 && age <= 120);
    }
};

int main() {

    string name = "Muhammad Arslan";
    string number = "12345";

    cout << "Uppercase: "
         << Utils::toUpper(name) << endl;

    cout << "Lowercase: "
         << Utils::toLower(name) << endl;

    Utils::displayDate();

    if (Utils::isNumeric(number))
        cout << number << " is a valid numeric string." << endl;
    else
        cout << number << " is not numeric." << endl;

    int age = 20;
    if (Utils::isValidAge(age))
        cout << "Valid Age" << endl;
    else
        cout << "Invalid Age" << endl;

    return 0;
}