#include <iostream>
#include <fstream>
#include "json.hpp" //modify includePath if needed
#include <vector>
#include <algorithm>

using json = nlohmann::json;

struct Employee
{
    std::string id;
    std::string firstName;
};

bool compareById(const Employee& emp1, const Employee& emp2) {return emp1.id < emp2.id;}

int main()
{
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;
    std::vector<Employee> arr; // [id][first_name]

    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.id = jsonData[employee]["id"];
        emp.firstName = jsonData[employee]["first_name"];
        arr.push_back(emp);
    }

    std::sort(arr.begin(), arr.end(), compareById);
    
    for(const auto& emp : arr)
        std::cout << emp.id << ", " << emp.firstName << std::endl;

    return 0;
}