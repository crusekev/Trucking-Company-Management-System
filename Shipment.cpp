/* Code for Shipment object, contains function code for all Shipment methods. */

#include "Shipment.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Shipment::Shipment()
{
    m_Type = "";
    m_Company = "";
    m_Address = "";
    m_City = "";
    m_State = "";
    m_Zip = 0;
    m_VehicleID = 0;
    m_DepartureDateTime = "";
    m_EstimatedArrivalDateTime = "";
    m_ArrivalConfirmation = "";
    m_Drivers = "";
    m_Manifest = "";
    m_PurchaseOrder = "";
}
Shipment::Shipment(std::string& type, std::string& company, std::string& address, std::string& city, std::string& state, int zip, int vehicleID, std::string& departureDateTime, std::string& estimatedArrivalDateTime, std::string& arrivalConfirmation, std::string& drivers, std::string& manifest, std::string& purchaseOrder)
{
    this->m_Type = type;
    this->m_Company = company;
    this->m_Address = address;
    this->m_City = city;
    this->m_State = state;
    this->m_Zip = zip;
    this->m_VehicleID = vehicleID;
    this->m_DepartureDateTime = departureDateTime;
    this->m_EstimatedArrivalDateTime = estimatedArrivalDateTime;
    this->m_ArrivalConfirmation = arrivalConfirmation;
    this->m_Drivers = drivers;
    this->m_Manifest = manifest;
    this->m_PurchaseOrder = purchaseOrder;
}
Shipment::~Shipment()
=default;

// get/set methods
std::string Shipment::getType()
{
    return m_Type;
}
void Shipment::setType(std::string& type)
{
    this->m_Type = type;
}
std::string Shipment::getCompany()
{
    return m_Company;
}
void Shipment::setCompany(std::string& company)
{
    this->m_Company = company;
}
std::string Shipment::getAddress()
{
    return m_Address;
}
void Shipment::setAddress(std::string& address)
{
    this->m_Address = address;
}
std::string Shipment::getCity()
{
    return m_City;
}
void Shipment::setCity(std::string& city)
{
    this->m_City = city;
}
std::string Shipment::getState()
{
    return m_State;
}
void Shipment::setState(std::string& state)
{
    this->m_State = state;
}
int Shipment::getZip() const
{
    return m_Zip;
}
void Shipment::setZip(int zip)
{
    this->m_Zip = zip;
}
int Shipment::getVehicleID() const
{
    return m_VehicleID;
}
void Shipment::setVehicleID(int vehicleID)
{
    this->m_VehicleID = vehicleID;
}
std::string Shipment::getDepartureDateTime()
{
    return m_DepartureDateTime;
}
void Shipment::setDepartureDateTime(std::string& departureDateTime)
{
    this->m_DepartureDateTime = departureDateTime;
}
std::string Shipment::getEstimatedArrivalDateTime()
{
    return m_EstimatedArrivalDateTime;
}
void Shipment::setEstimatedArrivalDateTime(std::string& estimatedArrivalDateTime)
{
    this->m_EstimatedArrivalDateTime = estimatedArrivalDateTime;
}
std::string Shipment::getArrivalConfirmation() const
{
    return m_ArrivalConfirmation;
}
void Shipment::setArrivalConfirmation(std::string& arrivalConfirmation)
{
    this->m_ArrivalConfirmation = arrivalConfirmation;
}
std::string Shipment::getDrivers()
{
    return m_Drivers;
}
void Shipment::setDrivers(std::string& drivers)
{
    this->m_Drivers = drivers;
}
std::string Shipment::getManifest()
{
    return m_Manifest;
}
void Shipment::setManifest(std::string& manifest)
{
    this->m_Manifest = manifest;
}
std::string Shipment::getPurchaseOrder()
{
    return m_PurchaseOrder;
}
void Shipment::setPurchaseOrder(std::string& purchaseOrder)
{
    this->m_PurchaseOrder = purchaseOrder;
}

// Prints all member variables
void Shipment::printRecord()
{
    std::cout << "Shipping type: " << m_Type << std::endl;
    std::cout << "Company: " << m_Company << std::endl;
    std::cout << "Address: " << m_Address << std::endl;
    std::cout << "City: " << m_City << std::endl;
    std::cout << "State: " << m_State << std::endl;
    std::cout << "Zip: " << m_Zip << std::endl;
    std::cout << "Vehicle ID: " << m_VehicleID << std::endl;
    std::cout << "Departure Date/Time: " << m_DepartureDateTime << std::endl;
    std::cout << "Estimated Arrival Date/Time: " << m_EstimatedArrivalDateTime << std::endl;
    std::cout << "Arrival Confirmation: " << m_ArrivalConfirmation << std::endl;
    std::cout << "Drivers: " << m_Drivers << std::endl;
    std::cout << "Manifest: " << m_Manifest << std::endl;
    std::cout << "Purchase Order: " << m_PurchaseOrder << std::endl;
}

// This function reads a .csv file and stores each column into fields[n]
// It then stores the fields into Shipment objects
std::vector<Shipment> Shipment::readShipmentData(const std::string& filename)
{
    // Create a vector to hold Equipment Data objects
    std::vector<Shipment> shipments;
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
            if(filename == "ShippingData.csv")
            {
                int zip, vehicleID;
                for (int i = 0; i < fields.size(); ++i)
                {
                    try
                    {
                        switch(i)
                        {
                            case 5:
                                zip = stoi(fields[i]);
                                break;
                            case 6:
                                vehicleID = stoi(fields[i]);
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
                std::string type = fields[0];
                std::string company = fields[1];
                std::string address = fields[2];
                std::string city = fields[3];
                std::string state = fields[4];
                std::string departureDateTime = fields[7];
                std::string estimatedArrivalDateTime = fields[8];
                std::string arrivalConfirmation = fields[9];
                std::string drivers = fields[10];
                std::string manifest = fields[11];
                std::string purchaseOrder = fields[12];
                // Create a Shipment object using the extracted and converted data
                Shipment shipment;
                shipment.setType(type);
                shipment.setCompany(company);
                shipment.setAddress(address);
                shipment.setCity(city);
                shipment.setState(state);
                shipment.setZip(zip);
                shipment.setVehicleID(vehicleID);
                shipment.setDepartureDateTime(departureDateTime);
                shipment.setEstimatedArrivalDateTime(estimatedArrivalDateTime);
                shipment.setArrivalConfirmation(arrivalConfirmation);
                shipment.setDrivers(drivers);
                shipment.setManifest(manifest);
                shipment.setPurchaseOrder(purchaseOrder);
                shipments.push_back(shipment);
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
    return shipments;
}