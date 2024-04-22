#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Employee {
    string name;
    string team;
};

struct Company {
    unordered_map<string, Employee> employees;
    vector<string> children;
};

// Function to extract value from JSON string
string extractValue(const string& json, const string& key) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == string::npos) {
        return ""; // Key not found
    }
    pos = json.find(":", pos);
    pos = json.find("\"", pos);
    size_t start = pos + 1;
    pos = json.find("\"", start + 1);
    size_t end = pos;
    return json.substr(start, end - start);
}

int main() {
    ifstream file("./sample.json");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string jsonStr = buffer.str();

    Company company;

    // Extracting children
    string childrenValue = extractValue(jsonStr, "children");
    size_t start = childrenValue.find("[");
    size_t end = childrenValue.find("]");
    string childrenStr = childrenValue.substr(start + 1, end - start - 1);
    stringstream childrenStream(childrenStr);
    string child;
    while (getline(childrenStream, child, ',')) {
        company.children.push_back(child);
    }

    // Extracting employee details
    for (const auto& child : company.children) {
        string employeeJson = extractValue(jsonStr, child);
        string name = extractValue(employeeJson, "name");
        string team = extractValue(employeeJson, "team");
        company.employees[child] = {name, team};
    }

    // Printing employee details
    for (const auto& [name, employee] : company.employees) {
        cout << "Name: " << employee.name << endl;
        cout << "Team: " << employee.team << endl;
    }

    return 0;
}
