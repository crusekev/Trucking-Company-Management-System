/* Code for EquipmentData object, contains function code for all EquipmentData methods. */

#include "EquipmentData.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

EquipmentData::EquipmentData()
{
    m_VehicleID = 0;
    m_Brand = "";
    m_Year = 0;
    m_Model = "";
    m_Type = "";
    m_PartsList = "";
    m_RoutineInspections = "";
    m_RoutineMaintenance = "";
    m_RepairRecords = "";

}

EquipmentData::EquipmentData(int ID, std::string& brand, int year, std::string& model, std::string& type, std::string& partsList, std::string& routineInspections, std::string& routineMaintenance, std::string& repairRecords)
{
    this->m_VehicleID = ID;
    this->m_Brand = brand;
    this->m_Year = year;
    this->m_Model = model;
    this->m_Type = type;
    this->m_PartsList = partsList;
    this->m_RoutineInspections = routineInspections;
    this->m_RoutineMaintenance = routineMaintenance;
    this->m_RepairRecords = repairRecords;
}

EquipmentData::~EquipmentData()
=default;

// get/set methods
int EquipmentData::getID() const
{
    return m_VehicleID;
}

void EquipmentData::setID(int ID)
{
    this->m_VehicleID = ID;
}

std::string EquipmentData::getBrand() const
{
    return m_Brand;
}

void EquipmentData::setBrand(std::string& brand)
{
    this->m_Brand = brand;
}

int EquipmentData::getYear() const
{
    return m_Year;
}

void EquipmentData::setYear(int year)
{
    this->m_Year = year;
}

std::string EquipmentData::getModel() const
{
    return m_Model;
}

void EquipmentData::setModel(std::string& model)
{
    this->m_Model = model;
}

std::string EquipmentData::getType() const
{
    return m_Type;
}

void EquipmentData::setType(std::string& type)
{
    this->m_Type = type;
}

std::string EquipmentData::getPartsList() const
{
    return m_PartsList;
}

void EquipmentData::setPartsList(std::string& partsList)
{
    this->m_PartsList = partsList;
}

std::string EquipmentData::getRoutineInspections() const
{
    return m_RoutineInspections;
}

void EquipmentData::setRoutineInspections(std::string& routineInspections)
{
    this->m_RoutineInspections = routineInspections;
}

std::string EquipmentData::getRoutineMaintenance() const
{
    return m_RoutineMaintenance;
}

void EquipmentData::setRoutineMaintenance(std::string& routineMaintenance)
{
    this->m_RoutineMaintenance = routineMaintenance;
}

std::string EquipmentData::getRepairRecords() const
{
    return m_RepairRecords;
}

void EquipmentData::setRepairRecords(std::string& repairRecords)
{
    this->m_RepairRecords = repairRecords;
}

// Prints all member variables
void EquipmentData::printRecord()
{
    std::cout << "Vehicle ID: " << m_VehicleID << std::endl;
    std::cout << "Brand: " << m_Brand << std::endl;
    std::cout << "Year: " << m_Year << std::endl;
    std::cout << "Model: " << m_Model << std::endl;
    std::cout << "Type: " << m_Type << std::endl;
    std::cout << "Parts list: " << m_PartsList << std::endl;
    std::cout << "Routine inspections: " << m_RoutineInspections << std::endl;
    std::cout << "Routine maintenance: " << m_RoutineMaintenance << std::endl;
    std::cout << "Repair records: " << m_RepairRecords << std::endl;
    printf("\n");
}

// This function reads a .csv file and stores each column into fields[n]
// It then stores the fields into EquipmentData objects
std::vector<EquipmentData> EquipmentData::readEquipmentData(const std::string& filename)
{
    // Create a vector to hold Equipment Data objects
    std::vector<EquipmentData> cars;
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
            if(filename == "EquipmentData.csv")
            {
                int vehicleID, year;
                for (int i = 0; i < fields.size(); ++i)
                {
                    try
                    {
                        switch(i)
                        {
                            case 0:
                                vehicleID = stoi(fields[i]);
                                break;
                            case 2:
                                year = stoi(fields[i]);
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
                std::string brand =  fields[1];
                std::string model =  fields[3];
                std::string type = fields[4];
                std::string partsList = fields[5];
                std::string routineInspections = fields[6];
                std::string routineMaintenance = fields[7];
                std::string repairRecords = fields[8];
                // Create an Equipment Data object using the extracted and converted data
                EquipmentData car;
                car.setID(vehicleID);
                car.setBrand(brand);
                car.setYear(year);
                car.setModel(model);
                car.setType(type);
                car.setPartsList(partsList);
                car.setRoutineInspections(routineInspections);
                car.setRoutineMaintenance(routineMaintenance);
                car.setRepairRecords(repairRecords);
                cars.push_back(car);
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
    return cars;
}