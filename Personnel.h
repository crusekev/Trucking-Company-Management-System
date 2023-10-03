/* Header file for Personnel.cpp, outlines class information and functions. */

#include <iostream>
#include <vector>

class Personnel
{
private:
    int m_EmployeeID;
    std::string m_Name;
    std::string m_Address;
    std::string m_City;
    std::string m_State;
    int m_Zip;
    std::string m_HomePhoneNumber;
    std::string m_CellPhoneNumber;
    double m_Salary;
    int m_EmploymentLength;
    std::string m_CurrentAssignment;
public:
    Personnel(); // Default constructor
    Personnel(int ID, std::string& name, std::string& address, std::string& city, std::string& state, int zip, std::string& homePhoneNumber, std::string& cellPhoneNumber, double salary, int employmentLength, std::string& currentAssignment); // Parameterized constructor
    ~Personnel(); // Destructor
    int getID() const;
    void setID(int ID);
    std::string getName() const;
    void setName(std::string& name);
    std::string getAddress() const;
    void setAddress(std::string& address);
    std::string getCity() const;
    void setCity(std::string& city);
    std::string getState() const;
    void setState(std::string& state);
    int getZip() const;
    void setZip(int zip);
    std::string getHomePhoneNumber() const;
    void setHomePhoneNumber(std::string& homePhoneNumber);
    std::string getCellPhoneNumber() const;
    void setCellPhoneNumber(std::string& cellPhoneNumber);
    double getSalary() const;
    void setSalary(double salary);
    int getEmploymentLength() const;
    void setEmploymentLength(int employmentLength);
    std::string getCurrentAssignment() const;
    void setCurrentAssignment(std::string& currentAssignment);
    void printRecord();
    static std::vector<Personnel> readPersonnelData(const std::string& filename);
};