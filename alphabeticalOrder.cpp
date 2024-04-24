#include <iostream> //print text
#include <fstream>  //needed for reading json file
#include "json.hpp" //modify includePath if needed
#include <vector> //dynamic array
#include <algorithm> //for sort function

using json = nlohmann::json; //for convenience

//store data types (i.e team/first_name/id/etc) under a single variable
struct Employee
{
    std::string last_name;
    std::string firstName;
};

//comparator to check if instance 1 is lesser than instance 2
bool compare(const Employee& emp1, const Employee& emp2) {return emp1.last_name < emp2.last_name;}

int main()
{
    //to read data from json file and put into an instance
    std::ifstream file("Employees.json");
    json jsonData;
    file >> jsonData;

    //vector array for employees
    std::vector<Employee> arr;

    //put specific contents (i.e team/first_name/id/etc) into an instance
    //which then get put into the team of the instance into respective array
    for(const auto& employee : jsonData["Employee"]["children"]){
        Employee emp;
        emp.last_name = jsonData[employee]["last_name"];
        emp.firstName = jsonData[employee]["first_name"];
        arr.push_back(emp);
    }

    //sorts by less than to greater using comparator function
    std::sort(arr.begin(), arr.end(), compare);
    
    //print loop: last name, then first name, then endl
    for(const auto& emp : arr)
        std::cout << emp.last_name << ", " << emp.firstName << std::endl;

    return 0;
}