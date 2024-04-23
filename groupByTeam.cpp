#include <iostream>
#include <fstream>
#include "json.hpp" //modify includePath if needed
#include <vector>
#include <algorithm>

using json = nlohmann::json;

struct Employee
{
    std::string team;
    std::string firstName;
};

int main()
{
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;
    std::vector<Employee> faxArray;
    std::vector<Employee> scanArray; 
    std::string fax;
    std::string scan;

    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.team = jsonData[employee]["team"];
        emp.firstName = jsonData[employee]["first_name"];

        if(emp.team == "fax")
            faxArray.push_back(emp);
        else if (emp.team == "scan")
            scanArray.push_back(emp);
    }

    for(const auto& emp : faxArray)
        fax += emp.firstName + ", ";
    fax.erase(fax.end() - 2, fax.end());

    for(const auto& emp : scanArray)
        scan += emp.firstName + ", ";
    scan.erase(scan.end() - 2, scan.end());

    std::cout << "Fax: " << fax << std::endl;
    std::cout << "Scan: " << scan << std::endl;

    return 0;
}