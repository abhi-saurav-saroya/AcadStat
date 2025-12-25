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
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

class Subject {
    private:
        string subjectName;
        string subjectCode;
        int MCode;
        float marksObtained;

    public:
        Subject(string name, string code, int mcode, float marks) : 
                subjectName(name), subjectCode(code), MCode(mcode), marksObtained(marks) {}

        string getSubjectCode() const {
            return subjectCode;
        }

        int getMCode() const {
            return MCode;
        }
};

class Semester {
    private:
        int semesterNumber;
        vector<Subject> subjects;

    public:
        Semester(int semNo) : semesterNumber(semNo) {}

        int getSemesterNumber() const {
            return semesterNumber;
        }

        bool subjectExists(const string& subcode) const {
            for (const Subject& sub : subjects) {
                if (toLower(subcode) == toLower(sub.getSubjectCode()))
                    return true;
            }
            return false;
        }

        bool subjectExists(int mcode) const {
            for (const Subject& sub : subjects) {
                if (mcode == sub.getMCode())
                    return true;
            }
            return false;
        }

        void addSubject(const Subject& sub) {
            subjects.push_back(sub);
        }
};

class Student {
    private:
        string studentName;
        string studentID;
        unsigned long long uniRollNo;
        vector<Semester> semesters;

    public:
        Student(string name, string id, unsigned long long roll)
            : studentName(name), studentID(id), uniRollNo(roll) {}

        string getStudentID() const {
            return studentID;
        }

        unsigned long long getUniRollNo() const {
            return uniRollNo;
        }

        bool semesterExists(int semNo) const {
            for (const Semester& sem : semesters) {
                if (sem.getSemesterNumber() == semNo)
                    return true;
            }
            return false;
        }

        Semester& getSemesterByNumber(int semNo) {
            for (Semester& sem : semesters) {
                if (sem.getSemesterNumber() == semNo) {
                    return sem;
                }
            }
            cout << "Semester not found." << endl;
        }

        void addSemester(const Semester& sem) {
            semesters.push_back(sem);
        }
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

        bool studentExists(const string& stuID, const unsigned long long& uniRollNo) const {
            for (const Student& stu : students) {
                if (toLower(stuID) == toLower(stu.getStudentID()) || stu.getUniRollNo() == uniRollNo)
                    return true;
            }
            return false;
        }

        Student& getStudentByRollNo(unsigned long long uniRollNo) {
            for (Student& student : students) {
                if (student.getUniRollNo() == uniRollNo) {
                    return student;
                }
            }
            cout << "Student not found." << endl;
        }

        void addStudent(const Student& stu){
            students.push_back(stu);
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

        int displaySections() const {
            if(sections.empty()) {
                cout << "No sections available in this department." << endl;
                return 0;
            }

            cout << "Section List:" << endl;
            for (size_t i = 0; i < sections.size(); ++i) {
                cout << "\t" << (i + 1) << ". " << sections[i].getSectionName() << endl;
            }
            return static_cast<int>(sections.size());
        }

        bool sectionExists(const string& secName) const {
            for (const Section& sec : sections) {
                if (toLower(sec.getSectionName()) == toLower(secName))
                    return true;
            }
            return false;
        }

        Section& getSectionByIndex(int index) {
            return sections[index];
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
        void manipulateData();
        void addSubjects();
        void addMarks();
        void showReports();

        int displayDepartments() const {
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
        cout << "\t4. Manipulate Data" << endl;
        cout << "\t5. Add Marks" << endl;
        cout << "\t6. Show Reports" << endl;
        cout << "\t7. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if(!cin || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 7." << endl;
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
                addMarks();
                break;
            case 6:
                showReports();
                break;
            case 7:
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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