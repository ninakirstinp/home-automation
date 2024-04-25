#include <iostream> //print text
#include <fstream> //needed for reading json file
#include "json.hpp" //modify includePath if needed
#include <vector> //dynamic array
#include <algorithm> //for sort function

using json = nlohmann::json; //for convenience

//store data types (i.e team/first_name/id/etc) under a single variable
struct Employee
{
    std::string team;
    std::string firstName;
};

int main()
{
    //to read data from json file and put into an instance
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;

    // vector array for respective teams
    std::vector<Employee> faxArray;
    std::vector<Employee> scanArray;

    //indexes of the arrays get put into one string for their respective team
    std::string fax; 
    std::string scan; 

    //put specific contents (i.e team/first_name/id/etc) into an instance
    //which then get put into the team of the instance into respective array
    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.team = jsonData[employee]["team"];
        emp.firstName = jsonData[employee]["first_name"];

        if(emp.team == "fax")
            faxArray.push_back(emp);
        else if (emp.team == "scan")
            scanArray.push_back(emp);
    }

    //indexes of the arrays get put into one string for their respective team
    for(const auto& emp : faxArray)
        fax += emp.firstName + ", ";
    fax.erase(fax.end() - 2);

    for(const auto& emp : scanArray)
        scan += emp.firstName + ", ";
    scan.erase(scan.end() - 2);

    std::cout << "Fax: " << fax << std::endl;
    std::cout << "Scan: " << scan << std::endl;

    return 0;
}