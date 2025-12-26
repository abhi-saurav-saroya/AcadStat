#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <string>
#include <cctype>
using namespace std;

#include "Section.h"

class Department {
    private:
        string departmentName;
        vector<Section> sections;

    public:
        Department(string name);
        string getDepartmentName() const;
        int displaySections() const;
        bool sectionExists(const string& secName) const;
        Section& getSectionByIndex(int index);
        void addSection(const Section& sec);
};

#endif