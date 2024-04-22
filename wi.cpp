#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "json.hpp"

using json = nlohmann::json;

struct Employee {
    std::string first_name;
    std::string last_name;
    std::string id;
    std::string team;
};

bool compareById(const Employee &a, const Employee &b) {
    return std::stoi(a.id) < std::stoi(b.id);
}

bool compareByLastName(const Employee &a, const Employee &b) {
    return a.last_name < b.last_name;
}

int main() {
    std::ifstream file("employees.json");
    json data;
    file >> data;

    std::vector<Employee> employees;
    for (const auto &emp : data["employees"]) {
        Employee e;
        e.first_name = emp["first_name"];
        e.last_name = emp["last_name"];
        e.id = emp["id"];
        e.team = emp["team"];
        employees.push_back(e);
    }

    // Sorting employees by ID
    std::sort(employees.begin(), employees.end(), compareById);

    // Grouping employees by team
    std::map<std::string, std::vector<std::string>> teamMap;
    for (const auto &emp : employees) {
        teamMap[emp.team].push_back(emp.first_name + " " + emp.last_name);
    }

    // Sorting employees by last name
    std::sort(employees.begin(), employees.end(), compareByLastName);

    // Printing employees by ID
    std::cout << "Employees by ID:" << std::endl;
    for (const auto &emp : employees) {
        std::cout << emp.id << ", " << emp.first_name << std::endl;
    }

    // Printing employees grouped by team
    std::cout << "\nGroup by team:" << std::endl;
    for (const auto &pair : teamMap) {
        std::cout << pair.first << ": ";
        for (const auto &emp : pair.second) {
            std::cout << emp << ", ";
        }
        std::cout << std::endl;
    }

    // Printing employees by last name
    std::cout << "\nList last name with first name alphabetically:" << std::endl;
    for (const auto &emp : employees) {
        std::cout << emp.last_name << ", " << emp.first_name << std::endl;
    }

    return 0;
}
