#include "utils.h"

#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

string toLower(const string& s) {
    string result = s;
    for (char& ch : result) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

string loadAdminPasskeyFromEnv() {
    ifstream file(".env");
    if (!file) {
        cerr << "ERROR: .env file not found!\n";
        return "";
    }

    string line;
    while (getline(file, line)) {
        if (line.find("ADMIN_PASSKEY=") == 0) {
            return line.substr(14); // length of "ADMIN_PASSKEY="
        }
    }

    cerr << "ERROR: ADMIN_PASSKEY not found in .env file!\n";
    return "";
}