/* Header file for EquipmentData.cpp, outlines class information and functions. */

#include <iostream>
#include <string>
#include <vector>

class EquipmentData
{
private:
    int m_VehicleID;
    std::string m_Brand;
    int m_Year;
    std::string m_Model;
    std::string m_Type;
    std::string m_PartsList;
    std::string m_RoutineInspections;
    std::string m_RoutineMaintenance;
    std::string m_RepairRecords;

public:
    EquipmentData();
    EquipmentData(int ID, std::string& brand, int year, std::string& model, std::string& type, std::string& partsList, std::string& routineInspections, std::string& routineMaintenance, std::string& repairRecords);
    ~EquipmentData();
    int getID() const;
    void setID(int ID);
    std::string getBrand() const;
    void setBrand(std::string& brand);
    int getYear() const;
    void setYear(int year);
    std::string getModel() const;
    void setModel(std::string& model);
    std::string getType() const;
    void setType(std::string& type);
    std::string getPartsList() const;
    void setPartsList(std::string& partsList);
    std::string getRoutineInspections() const;
    void setRoutineInspections(std::string& routineInspections);
    std::string getRoutineMaintenance() const;
    void setRoutineMaintenance(std::string& routineMaintenance);
    std::string getRepairRecords() const;
    void setRepairRecords(std::string& repairRecords);
    void printRecord();
    static std::vector<EquipmentData> readEquipmentData(const std::string& filename);
};