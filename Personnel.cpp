/* Code for Personnel object, contains function code for all Personnel methods. */

#include "Personnel.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

// default constructor
Personnel::Personnel()
{
    m_EmployeeID = 0;
    m_Name = "";
    m_Address = "";
    m_City = "";
    m_State = "";
    m_Zip = 0;
    m_HomePhoneNumber = "";
    m_CellPhoneNumber = "";
    m_Salary = 0;
    m_EmploymentLength = 0;
    m_CurrentAssignment = "";
}
// parameterized constructor
Personnel::Personnel(int ID, std::string& name, std::string& address, std::string& city, std::string& state, int zip, std::string& homePhoneNumber, std::string& cellPhoneNumber, double salary, int employmentLength, std::string& currentAssignment)
{
    this->m_EmployeeID = ID;
    this->m_Name = name;
    this->m_Address = address;
    this->m_City = city;
    this->m_State = state;
    this->m_Zip = zip;
    this->m_HomePhoneNumber = homePhoneNumber;
    this->m_CellPhoneNumber = cellPhoneNumber;
    this->m_Salary = salary;
    this->m_EmploymentLength = employmentLength;
    this->m_CurrentAssignment = currentAssignment;

}
// destructor
Personnel::~Personnel()
= default;

// get/set methods
int Personnel::getID() const
{
    return m_EmployeeID;
}

void Personnel::setID(int ID)
{
    this->m_EmployeeID = ID;
}

std::string Personnel::getName() const
{
    return m_Name;
}

void Personnel::setName(std::string& name)
{
    this->m_Name = name;
}

std::string Personnel::getAddress() const
{
    return m_Address;
}

void Personnel::setAddress(std::string& address)
{
    this->m_Address = address;
}

std::string Personnel::getCity() const
{
    return m_City;
}

void Personnel::setCity(std::string& city)
{
    this->m_City = city;
}

std::string Personnel::getState() const
{
    return m_State;
}

void Personnel::setState(std::string& state)
{
    this->m_State = state;
}

int Personnel::getZip() const
{
    return m_Zip;
}

void Personnel::setZip(int zip)
{
    this->m_Zip = zip;
}

std::string Personnel::getHomePhoneNumber() const
{
    return m_HomePhoneNumber;
}

void Personnel::setHomePhoneNumber(std::string& homePhoneNumber)
{
    this->m_HomePhoneNumber = homePhoneNumber;
}

std::string Personnel::getCellPhoneNumber() const
{
    return m_CellPhoneNumber;
}

void Personnel::setCellPhoneNumber(std::string& cellPhoneNumber)
{
    this->m_CellPhoneNumber = cellPhoneNumber;
}

double Personnel::getSalary() const
{
    return m_Salary;
}

void Personnel::setSalary(double salary)
{
    this->m_Salary = salary;
}

int Personnel::getEmploymentLength() const
{
    return m_EmploymentLength;
}

void Personnel::setEmploymentLength(int employmentLength)
{
    this->m_EmploymentLength = employmentLength;
}

std::string Personnel::getCurrentAssignment() const
{
    return m_CurrentAssignment;
}

void Personnel::setCurrentAssignment(std::string& currentAssignment)
{
    this->m_CurrentAssignment = currentAssignment;
}

// Prints all member variables
void Personnel::printRecord()
{
    std::cout << "Employee ID: " << m_EmployeeID << std::endl;
    std::cout << "Name: " << m_Name << std::endl;
    std::cout << "Address: " << m_Address << std::endl;
    std::cout << "City: " << m_City << std::endl;
    std::cout << "State: " << m_State << std::endl;
    std::cout << "Zip: " << m_Zip << std::endl;
    std::cout << "Home phone: " << m_HomePhoneNumber << std::endl;
    std::cout << "Cell phone: " << m_CellPhoneNumber << std::endl;
    std::cout << "Salary: " << std::fixed << std::setprecision(2) << m_Salary << std::endl;
    std::cout << "Employment length (years): " << m_EmploymentLength << std::endl;
    std::cout << "Current assignment: " << m_CurrentAssignment << std::endl;
    printf("\n");
}

// This function reads a .csv file and stores each column into fields[n]
// It then stores the fields into Personnel objects
std::vector<Personnel> Personnel::readPersonnelData(const std::string& filename)
{
    // Create a vector to hold personnel objects
    std::vector<Personnel> employees;
    // Create an input file stream and open the specified file
    std::ifstream file(filename);
    // Check if the file was successfully opened
    if(file)
    {
        // Create a string to hold each line of the file
        std::string line;
        // Read each line in the file
        while(getline(file, line))
        {
            // Create a string stream to extract each field from the line
            std::stringstream ss(line);
            // Create a string to hold each field and a vector to store all the fields
            std::string field;
            std::vector<std::string> fields;

            // Extract each field from the line and add it to the vector
            int index = 0;
            while(getline(ss, field, ','))
            {
                fields.push_back(field);
                index++;
            }
            // If the correct number of fields were read, create a personnel object and add it to the vector
            if(filename == "Personnel.csv")
            {
                // Convert the id, zip code, salary, and employment length fields to their appropriate data types
                // Handle exceptions if the conversion fails
                int employeeID, zip, employmentLength;
                double salary;
                for(int i = 0; i < fields.size(); ++i)
                {
                    try
                    {
                        switch(i)
                        {
                            case 0:
                                employeeID = stoi(fields[i]);
                                break;
                            case 5:
                                zip = stoi(fields[i]);
                                break;
                            case 8:
                                salary = stod(fields[i]);
                                break;
                            case 9:
                                employmentLength = stoi(fields[i]);
                                break;
                            default:
                                break;
                        }
                    }
                    catch(const std::invalid_argument& e)
                    {
                        std::cerr << "Error: Invalid argument for field " << i + 1 << ": " << e.what() << std::endl;
                        std::cerr << "Field value: " << fields[i] << std::endl;
                    }
                }
                std::string name = fields[1];
                std::string address = fields[2];
                std::string city = fields[3];
                std::string state = fields[4];
                std::string home_phone = fields[6];
                std::string cell_phone = fields[7];
                std::string current_assignment = fields[10];
                // Create a personnel object using the extracted and converted data
                Personnel employee;
                employee.setID(employeeID);
                employee.setName(name);
                employee.setAddress(address);
                employee.setCity(city);
                employee.setState(state);
                employee.setZip(zip);
                employee.setHomePhoneNumber(home_phone);
                employee.setCellPhoneNumber(cell_phone);
                employee.setSalary(salary);
                employee.setEmploymentLength(employmentLength);
                employee.setCurrentAssignment(current_assignment);
                // Add the personnel object to the vector
                employees.push_back(employee);
            }
                // If an incorrect number of fields were read, output an error message
            else
            {
                std::cerr << "Error: Incorrect file configuration" << std::endl;
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: could not open file \"" << filename << "\"" << std::endl;
    }
    // Return the vector of personnel objects
    return employees;
}