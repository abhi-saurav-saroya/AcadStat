#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include <cctype>
using namespace std;

#include "Semester.h"

class Student {
    private:
        string studentName;
        string studentID;
        unsigned long long uniRollNo;
        vector<Semester> semesters;

    public:
        Student(string name, string id, unsigned long long roll);
        string getStudentID() const;
        unsigned long long getUniRollNo() const;
        bool semesterExists(int semNo) const;
        Semester& getSemesterByNumber(int semNo);
        void addSemester(const Semester& sem);
};

#endif