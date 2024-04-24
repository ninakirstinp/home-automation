#include <iostream> //print text
#include <fstream> //needed for reading json file
#include "json.hpp" //modify includePath if needed
#include <vector> //dynamic array
#include <algorithm> //for sort function

using json = nlohmann::json; //for convenience

//store data types (i.e team/first_name/id/etc) under a single variable
struct Employee
{
    std::string id;
    std::string firstName;
};

//comparator to check if instance 1 is lesser than instance 2
bool compareById(const Employee& emp1, const Employee& emp2) {return emp1.id < emp2.id;}

int main()
{
    //to read data from json file and put into an instance
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;

    std::vector<Employee> arr; //vector array for employees

    //put specific contents (i.e team/first_name/id/etc) into an instance
    //which then get put into the team of the instance into respective array
    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.id = jsonData[employee]["id"];
        emp.firstName = jsonData[employee]["first_name"];
        arr.push_back(emp);
    }

    //sorts by less than to greater using comparator function
    std::sort(arr.begin(), arr.end(), compareById);
    
    //print loop: id, then name, then endl
    for(const auto& emp : arr)
        std::cout << emp.id << ", " << emp.firstName << std::endl;

    return 0;
}