#include <iostream>
#include <fstream>
#include "json.hpp" //modify includePath if needed
#include <vector>
#include <algorithm>

using json = nlohmann::json;

struct Employee
{
    std::string last_name;
    std::string firstName;
};

bool compare(const Employee& emp1, const Employee& emp2) {return emp1.last_name < emp2.last_name;}

int main()
{
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;
    std::vector<Employee> arr;

    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.last_name = jsonData[employee]["last_name"];
        emp.firstName = jsonData[employee]["first_name"];
        arr.push_back(emp);
    }

    std::sort(arr.begin(), arr.end(), compare);
    
    for(const auto& emp : arr)
        std::cout << emp.last_name << ", " << emp.firstName << std::endl;

    return 0;
}