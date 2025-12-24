#include<iostream>
#include<fstream>
#include<vector>
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

int main() {
    cout << "Academic Statistics Management System" << endl;
    
    return 0;
}