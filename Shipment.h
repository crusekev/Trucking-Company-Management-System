/* Header file for Shipment.cpp, outlines class information and functions. */

#include <iostream>

class Shipment
{
private:
    std::string m_Type;
    std::string m_Company;
    std::string m_Address;
    std::string m_City;
    std::string m_State;
    int m_Zip;
    int m_VehicleID;
    std::string m_DepartureDateTime;
    std::string m_EstimatedArrivalDateTime;
    std::string m_ArrivalConfirmation;
    std::string m_Drivers;
    std::string m_Manifest;
    std::string m_PurchaseOrder;
public:
    Shipment();
    Shipment(std::string& type, std::string& company, std::string& address, std::string& city, std::string& state, int zip, int vehicleID, std::string& departureDateTime, std::string& estimatedArrivalDateTime, std::string& arrivalConfirmation, std::string& drivers, std::string& manifest, std::string& purchaseOrder);
    ~Shipment();
    std::string getType();
    void setType(std::string& type);
    std::string getCompany();
    void setCompany(std::string& company);
    std::string getAddress();
    void setAddress(std::string& address);
    std::string getCity();
    void setCity(std::string& city);
    std::string getState();
    void setState(std::string& state);
    int getZip() const;
    void setZip(int zip);
    int getVehicleID() const;
    void setVehicleID(int vehicleID);
    std::string getDepartureDateTime();
    void setDepartureDateTime(std::string& departureDateTime);
    std::string getEstimatedArrivalDateTime();
    void setEstimatedArrivalDateTime(std::string& estimatedArrivalDateTime);
    std::string getArrivalConfirmation() const;
    void setArrivalConfirmation(std::string& arrivalConfirmation);
    std::string getDrivers();
    void setDrivers(std::string& drivers);
    std::string getManifest();
    void setManifest(std::string& manifest);
    std::string getPurchaseOrder();
    void setPurchaseOrder(std::string& purchaseOrder);
    void printRecord();
    static std::vector<Shipment> readShipmentData(const std::string& filename);
};