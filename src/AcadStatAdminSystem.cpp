#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\AcadStatAdminSystem.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Department.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Section.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Student.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Semester.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\Subject.h"
#include "C:\Users\hp\OneDrive\Documents\PROJECTS\Fun Activities\AcadStat\include\utils.h"


#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

AcadStatSystem::AcadStatSystem() {
    PassKey = loadAdminPasskeyFromEnv();
    if (PassKey.empty()) {
        cout << "Admin login disabled due to missing passkey.\n";
    }
}

int AcadStatSystem::displayDepartments() const {
    if(departments.empty()) {
        cout << "No departments available." << endl;
        return 0;
    }

    cout << "Department List:" << endl;
    for (size_t i = 0; i < departments.size(); ++i) {
        cout << "\t" << (i + 1) << ". " << departments[i].getDepartmentName() << endl;
    }
    return static_cast<int>(departments.size());
}

bool AcadStatSystem::adminLogin(const string& key) {
    return key == PassKey;
}

void AcadStatSystem::mainMenu() {
    while(true) {
        cout << "\nAdmin Main Menu:" << endl;
        cout << "\t1. Add Department" << endl;
        cout << "\t2. Add Section" << endl;
        cout << "\t3. Add Student" << endl;
        cout << "\t4. Manipulate Data" << endl;
        cout << "\t5. Add Subjects" << endl;
        cout << "\t6. Add Marks" << endl;
        cout << "\t7. Show Reports" << endl;
        cout << "\t8. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if(!cin || choice < 1 || choice > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 8." << endl;
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
                manipulateData();
                break;
            case 5:
                addSubjects();
                break;
            case 6:
                addMarks();
                break;
            case 7:
                showReports();
                break;
            case 8:
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

    int deptCount = displayDepartments();

    if (deptCount == 0) {
        cout << "No departments available. Add a department first.\n";
        return;
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
        cout << "Section already exists in this department." << endl;
        return;
    }

    selectedDept.addSection(Section(sectionName));
    cout << "Section added successfully." << endl;
}

void AcadStatSystem::addStudent() {
    cout << endl;

    int deptCount = displayDepartments();

    if (deptCount == 0) {
        cout << "No departments available. Add a department first.\n";
        return;
    }

    int deptChoice;

    while(true) {
        cout << "Select Department by number (or 0 to exit to main admin menu): ";

        cin >> deptChoice;
        if(!cin || deptChoice < 0 || deptChoice > deptCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid department number." << endl;
            continue;
        } else if (deptChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Department& selectedDept = departments[deptChoice - 1];

    int sectionCount = selectedDept.displaySections();

    if (sectionCount == 0) {
        cout << "No sections available in this department. Add a section first.\n";
        return;
    }

    int secChoice;

    while(true) {
        cout << "Select Section by number (or 0 to exit to main admin menu): ";

        cin >> secChoice;
        if(!cin || secChoice < 0 || secChoice > sectionCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid section number." << endl;
            continue;
        } else if (secChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Section& selectedSec = selectedDept.getSectionByIndex(secChoice - 1);
    
    string studentName, studentID;
    unsigned long long uniRollNo;

    cout << "Enter Student Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, studentName);

    cout << "Enter Student ID: ";
    cin >> studentID;

    cout << "Enter University Roll Number: ";
    cin >> uniRollNo;

    if (selectedSec.studentExists(studentID, uniRollNo)) {
        cout << "Student with this ID or University Roll Number already exists in the selected section." << endl;
        return;
    }

    Student newStudent(studentName, studentID, uniRollNo);
    selectedSec.addStudent(newStudent);

    cout << "Student added successfully.\n";
}

void AcadStatSystem::manipulateData() {
    cout << "Function to manipulate data (to be implemented)." << endl;
}

void AcadStatSystem::addSubjects() {
    cout << endl;

    int deptCount = displayDepartments();

    if (deptCount == 0) {
        cout << "No departments available. Add a department first.\n";
        return;
    }

    int deptChoice;

    while(true) {
        cout << "Select Department by number (or 0 to exit to main admin menu): ";

        cin >> deptChoice;
        if(!cin || deptChoice < 0 || deptChoice > deptCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid department number." << endl;
            continue;
        } else if (deptChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Department& selectedDept = departments[deptChoice - 1];

    int sectionCount = selectedDept.displaySections();

    if (sectionCount == 0) {
        cout << "No sections available in this department. Add a section first.\n";
        return;
    }

    int secChoice;

    while(true) {
        cout << "Select Section by number (or 0 to exit to main admin menu): ";

        cin >> secChoice;
        if(!cin || secChoice < 0 || secChoice > sectionCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid section number." << endl;
            continue;
        } else if (secChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Section& selectedSec = selectedDept.getSectionByIndex(secChoice - 1);

    unsigned long long uniRollNo;
    
    while(true) {
        cout << "Enter University Roll Number of the student to add marks (or 0 to exit to main admin menu): ";
        cin >> uniRollNo;

        if(!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid University Roll Number." << endl;
            continue;
        } else if (uniRollNo == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Student& selectedStudent = selectedSec.getStudentByRollNo(uniRollNo);

    int semNo;
    cout << "Enter Semester Number: ";
    cin >> semNo;

    if (selectedStudent.semesterExists(semNo)) {
        cout << "Semester already exists for this student." << endl;
        return;
    }

    Semester newSemester(semNo);
    selectedStudent.addSemester(newSemester);

    cout << "Semester added successfully. Now you can add subjects: " << endl;

    int subjectCount;

    while(true) {
        cout << "Enter number of subjects to add: ";
        cin >> subjectCount;
        if(!cin || subjectCount < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number of subjects." << endl;
            continue;
        }
        break;
    }

    Semester& selectedSem = selectedStudent.getSemesterByNumber(semNo);

    for(int i = 0; i < subjectCount; i++) {
        string subjectName, subjectCode;
        int MCode;

        cout << "Enter Subject Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, subjectName);

        cout << "Enter Subject Code: ";
        getline(cin, subjectCode);

        if (selectedSem.subjectExists(subjectCode)) {
            cout << "Subject with this code already exists in this semester." << endl;
            --i; 
            continue;
        }

        cout << "Enter MCode: ";
        cin >> MCode;

        if (selectedSem.subjectExists(MCode)) {
            cout << "Subject with this MCode already exists in this semester." << endl;
            --i; 
            continue;
        }

        Subject newSubject(subjectName, subjectCode, MCode, 0.0f);
        selectedSem.addSubject(newSubject);
    }
    cout << "Subjects added successfully to Semester " << semNo << " for student " << selectedStudent.getStudentID() << "." << endl;
}

void AcadStatSystem::addMarks() {
    cout << endl;

    int deptCount = displayDepartments();

    if (deptCount == 0) {
        cout << "No departments available. Add a department first.\n";
        return;
    }

    int deptChoice;

    while(true) {
        cout << "Select Department by number (or 0 to exit to main admin menu): ";

        cin >> deptChoice;
        if(!cin || deptChoice < 0 || deptChoice > deptCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid department number." << endl;
            continue;
        } else if (deptChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Department& selectedDept = departments[deptChoice - 1];

    int sectionCount = selectedDept.displaySections();

    if (sectionCount == 0) {
        cout << "No sections available in this department. Add a section first.\n";
        return;
    }

    int secChoice;

    while(true) {
        cout << "Select Section by number (or 0 to exit to main admin menu): ";

        cin >> secChoice;
        if(!cin || secChoice < 0 || secChoice > sectionCount) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid section number." << endl;
            continue;
        } else if (secChoice == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Section& selectedSec = selectedDept.getSectionByIndex(secChoice - 1);

    unsigned long long uniRollNo;
    
    while(true) {
        cout << "Enter University Roll Number of the student to add marks (or 0 to exit to main admin menu): ";
        cin >> uniRollNo;

        if(!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid University Roll Number." << endl;
            continue;
        } else if (uniRollNo == 0) {
            cout << "Exiting to main admin menu." << endl;
            return;
        }
        break;
    }

    Student& selectedStudent = selectedSec.getStudentByRollNo(uniRollNo);

    int semNo;
    cout << "Enter Semester Number: ";
    cin >> semNo;

    Semester& selectedSem = selectedStudent.getSemesterByNumber(semNo);

    if (!selectedStudent.semesterExists(semNo)) {
        cout << "Semester does not exist for this student.\n";
        return;
    }

    int subjectCount = selectedSem.displaySubjects();

    if (subjectCount == 0) {
        cout << "No subjects available in this semester. Add subjects first.\n";
        return;
    }

    for(int i = 0; i < subjectCount; i++) {
        float marks;

        while (true) {
            cout << "Enter Marks Obtained for subject " << (i + 1) << ": ";
            cin >> marks;
            
            if (!cin || marks < 0 || marks > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid marks. Enter a value between 0 and 100.\n";
                continue;
            }
            break;
        }

        selectedSem.updateMarksByIndex(i, marks);
    }
}

void AcadStatSystem::showReports() {
    cout << "Function to show Reports (to be implemented)." << endl;
}