#include "Department.h"
#include "Section.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

Department:: Department(string name) : departmentName(name) {}
        
string Department::getDepartmentName() const {
    return departmentName;
}

int Department::displaySections() const {
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

bool Department::sectionExists(const string& secName) const {
    for (const Section& sec : sections) {
        if (toLower(sec.getSectionName()) == toLower(secName))
            return true;
    }
    return false;
}

Section& Department::getSectionByIndex(int index) {
    return sections[index];
}

void Department::addSection(const Section& sec) {
    sections.push_back(sec);
}

