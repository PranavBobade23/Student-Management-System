#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string branch;
    float cgpa;

    Student() {}

    Student(int r, string n, int a, string b, float c) {
        rollNo = r;
        name = n;
        age = a;
        branch = b;
        cgpa = c;
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    string filename = "students.txt";

public:

    // Load data from file
    void loadFromFile() {
        students.clear();

        ifstream fin(filename);

        if (!fin)
            return;

        string line;

        while (getline(fin, line)) {
            stringstream ss(line);

            Student s;
            string temp;

            getline(ss, temp, '|');
            s.rollNo = stoi(temp);

            getline(ss, s.name, '|');

            getline(ss, temp, '|');
            s.age = stoi(temp);

            getline(ss, s.branch, '|');

            getline(ss, temp, '|');
            s.cgpa = stof(temp);

            students.push_back(s);
        }

        fin.close();
    }

    // Save data to file
    void saveToFile() {
        ofstream fout(filename);

        for (auto &s : students) {
            fout << s.rollNo << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.branch << "|"
                 << s.cgpa << endl;
        }

        fout.close();
    }

    // Add Student
    void addStudent() {

        Student s;

        cout << "\nEnter Roll Number: ";
        cin >> s.rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, s.name);

        cout << "Enter Age: ";
        cin >> s.age;

        cin.ignore();

        cout << "Enter Branch: ";
        getline(cin, s.branch);

        cout << "Enter CGPA: ";
        cin >> s.cgpa;

        students.push_back(s);

        saveToFile();

        cout << "\nStudent Added Successfully!\n";
    }

    // Display Students
    void displayStudents() {

        if (students.empty()) {
            cout << "\nNo Records Found.\n";
            return;
        }

        cout << "\n-------------------------------------------------------------\n";
        cout << "Roll\tName\t\tAge\tBranch\t\tCGPA\n";
        cout << "-------------------------------------------------------------\n";

        for (auto &s : students) {
            cout << s.rollNo << "\t"
                 << s.name << "\t\t"
                 << s.age << "\t"
                 << s.branch << "\t\t"
                 << s.cgpa << endl;
        }
    }

    // Search Student
    void searchStudent() {

        int roll;
        cout << "\nEnter Roll Number: ";
        cin >> roll;

        for (auto &s : students) {

            if (s.rollNo == roll) {

                cout << "\nStudent Found\n";

                cout << "Roll No : " << s.rollNo << endl;
                cout << "Name    : " << s.name << endl;
                cout << "Age     : " << s.age << endl;
                cout << "Branch  : " << s.branch << endl;
                cout << "CGPA    : " << s.cgpa << endl;

                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }

    // Update Student
    void updateStudent() {

        int roll;

        cout << "\nEnter Roll Number to Update: ";
        cin >> roll;

        for (auto &s : students) {

            if (s.rollNo == roll) {

                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, s.name);

                cout << "Enter New Age: ";
                cin >> s.age;

                cin.ignore();

                cout << "Enter New Branch: ";
                getline(cin, s.branch);

                cout << "Enter New CGPA: ";
                cin >> s.cgpa;

                saveToFile();

                cout << "\nRecord Updated Successfully!\n";
                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }

    // Delete Student
    void deleteStudent() {

        int roll;

        cout << "\nEnter Roll Number to Delete: ";
        cin >> roll;

        for (auto it = students.begin(); it != students.end(); it++) {

            if (it->rollNo == roll) {

                students.erase(it);

                saveToFile();

                cout << "\nRecord Deleted Successfully!\n";
                return;
            }
        }

        cout << "\nStudent Not Found!\n";
    }
};

int main() {

    StudentManagementSystem sms;

    sms.loadFromFile();

    int choice;

    do {

        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            sms.addStudent();
            break;

        case 2:
            sms.displayStudents();
            break;

        case 3:
            sms.searchStudent();
            break;

        case 4:
            sms.updateStudent();
            break;

        case 5:
            sms.deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}