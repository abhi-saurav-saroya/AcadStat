#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>
#include<cctype>
using namespace std;

string toLower(const string& s) {
    string result = s;
    for (char& ch : result) {
        ch = tolower(ch);
    }
    return result;
}

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

    public:
        Section(string name) : sectionName(name) {}

        string getSectionName() const {
            return sectionName;
        }
};

class Department {
    private:
        string departmentName;
        vector<Section> sections;

    public:
        Department(string name) : departmentName(name) {}
        
        string getDepartmentName() const {
            return departmentName;
        }

        bool sectionExists(const string& secName) const {
            for (const Section& sec : sections) {
                if (toLower(sec.getSectionName()) == toLower(secName))
                    return true;
            }
            return false;
        }

        void addSection(const Section& sec) {
            sections.push_back(sec);
        }
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
    cout << endl;
    cout << "Add Department Name: ";
    
    string deptName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, deptName);

    for (const Department& dept : departments) {
        if (toLower(dept.getDepartmentName()) == toLower(deptName)) {
            cout << "Department already exists. Cannot add duplicate.\n";
            return;
        }
    }

    departments.push_back(Department(deptName));
    cout << "Department added successfully.\n";
}

void AcadStatSystem::addSection() {
    cout << endl;

    if (departments.empty()) {
        cout << "No departments available. Add a department first.\n";
        return;
    }

    cout << "Department List:" << endl;
    
    for (size_t i = 0; i < departments.size(); ++i) {
        cout << "\t" << (i + 1) << ". " << departments[i].getDepartmentName() << endl;
    }

    int deptChoice;

    while(true) {
        cout << "Select Department by number: ";

        cin >> deptChoice;
        if(!cin || deptChoice < 0 || deptChoice > static_cast<int>(departments.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid department number (or 0 to exit to main admin menu)." << endl;
            continue;
        } else if (deptChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Department& selectedDept = departments[deptChoice - 1];

    cout << "Add Section Name: ";
    string sectionName;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> sectionName;

    if (selectedDept.sectionExists(sectionName)) {
        cout << "Section already exists in this department.\n";
        return;
    }

    selectedDept.addSection(Section(sectionName));
    cout << "Section added successfully.\n";
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