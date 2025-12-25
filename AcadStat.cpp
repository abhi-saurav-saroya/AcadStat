#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>
using namespace std;

class Subject {
    private:
        string subjectName;
        string subjectCode;
        int MCode;
        float marksObtained;
};

class Semester {
    private:
        int semesterNumber;
        vector<Subject> subjects;
};

class Student {
    private:
        string studentName;
        string studentID;
        unsigned long long uniRollNo;
        vector<Semester> semesters;
};

class Section {
    private:
        string sectionName;
        vector<Student> students;
};

class Department {
    private:
        string departmentName;
        vector<Section> sections;
};

class AcadStatSystem {
    private:
        static string PassKey;
        vector<Department> departments;

    public:
        bool adminLogin(const string& key);
        void mainMenu();
        void addDepartment();
        void addSection();
        void addStudent();
        void addMarks();
        void showReports();
};

string AcadStatSystem::PassKey = "admin123";

bool AcadStatSystem::adminLogin(const string& key) {
    return key == PassKey;
}

void AcadStatSystem::mainMenu() {
    while(true) {
        cout << "\nAdmin Main Menu:" << endl;
        cout << "\t1. Add Department" << endl;
        cout << "\t2. Add Section" << endl;
        cout << "\t3. Add Student" << endl;
        cout << "\t4. Add Marks" << endl;
        cout << "\t5. Show Reports" << endl;
        cout << "\t6. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if(!cin || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }

        switch(choice) {
            case 1:
                addDepartment();
                break;
            case 2:
                addSection();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                addMarks();
                break;
            case 5:
                showReports();
                break;
            case 6:
                cout << "Logging out..." << endl;
                return;
        }
    }
}

void AcadStatSystem::addDepartment() {
    cout << "Function to add Department (to be implemented)." << endl;
}

void AcadStatSystem::addSection() {
    cout << "Function to add Section (to be implemented)." << endl;
}

void AcadStatSystem::addStudent() {
    cout << "Function to add Student (to be implemented)." << endl;
}

void AcadStatSystem::addMarks() {
    cout << "Function to add Marks (to be implemented)." << endl;
}

void AcadStatSystem::showReports() {
    cout << "Function to show Reports (to be implemented)." << endl;
}

int main() {
    cout << "Academic Statistics Management System:" << endl << endl;
    AcadStatSystem admin;

    while(true) {
        cout << "\t1. Login as Admin" << endl;
        cout << "\t2. Login as User" << endl;
        cout << "\t3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if(!cin || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        if (choice == 1) {
            string inputKey;
            cout << "Enter Admin PassKey: ";
            cin >> inputKey;
            if(admin.adminLogin(inputKey)) {
                admin.mainMenu();
            } else {
                cout << "Incorrect PassKey. Access Denied." << endl;
            }
        } else if (choice == 2) {
            cout << "User functionality is under development." << endl;
        } else if (choice == 3) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }
    }
    return 0;
}