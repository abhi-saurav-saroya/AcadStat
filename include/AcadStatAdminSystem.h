#ifndef ACADSTATADMINSYSTEM_H
#define ACADSTATADMINSYSTEM_H

#include <vector>
#include <string>
#include <cctype>
using namespace std;

#include "Department.h"

class AcadStatSystem {
    private:
        string PassKey;
        vector<Department> departments;

    public:
        AcadStatSystem();
        bool adminLogin(const string& key);
        void mainMenu();
        void addDepartment();
        void addSection();
        void addStudent();
        void manipulateData();
        void addSubjects();
        void addMarks();
        void showReports();
        int displayDepartments() const;
        void showbyDepartment();
        void showbyStudent();
        void showbySemester();
        void showbySection();
};

#endif