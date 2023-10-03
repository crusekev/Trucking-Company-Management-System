/*Main function for GUI, supports login window and
authentication-specific data access.*/
#include "Personnel.h"
#include "EquipmentData.h"
#include "Shipment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <QApplication>
#include <QtWidgets>

/* User struct, stores an account type for determining data access
privileges along with a username and password for the user. */
struct User {
    QString accountType;
    QString jobTitle;
    QString username;
    QString password;
};

int main(int argc, char *argv[])
{
    // User account data. Supports account type, job title, username, and password
    QList<User> authorizedUsers = {
            {"Full", "President", "alice", "password"},
            {"Full", "CFO", "blake", "password"},
            {"Full", "Office Personnel", "mike", "password"},
            {"Shipping Data", "Shipping Manager","bob", "password"},
            {"Maintenance Data", "Maintenance Worker", "charlie", "password"},
            {"Driver Data", "Driver", "Bill Smith", "password"}
    };

    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Login Form");

    // Create the title label
    QLabel titleLabel("Trucking Company Management System");
    QFont titleFont = titleLabel.font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel.setFont(titleFont);
    titleLabel.setAlignment(Qt::AlignCenter);

    // Create the form layout
    QFormLayout formLayout;
    window.setLayout(&formLayout);

    // Add the title label to the layout
    formLayout.addRow(&titleLabel);

    // Create the Account Type field
    QComboBox accountTypeComboBox;
    accountTypeComboBox.addItems({ "Full", "Shipping Data", "Maintenance Data", "Driver Data" });
    formLayout.addRow("Account Type:", &accountTypeComboBox);
    formLayout.setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout.setAlignment(Qt::AlignHCenter);

    // Create the Job Title layout
    QComboBox jobTitleComboBox;
    jobTitleComboBox.addItems({ "President", "CFO", "Office Personnel", "Shipping Manager", "Maintenance Worker", "Driver" });
    formLayout.addRow("Job Title:", &jobTitleComboBox);
    formLayout.setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout.setAlignment(Qt::AlignHCenter);

    // Create the Username field
    QLineEdit usernameLineEdit;
    formLayout.addRow("Username:", &usernameLineEdit);
    formLayout.setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout.setAlignment(Qt::AlignHCenter);

    // Create the Password field
    QLineEdit passwordLineEdit;
    passwordLineEdit.setEchoMode(QLineEdit::Password);
    formLayout.addRow("Password:", &passwordLineEdit);
    formLayout.setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout.setAlignment(Qt::AlignHCenter);

    // Create the Login button
    QPushButton loginButton("Login");
    formLayout.addRow("", &loginButton);
    formLayout.setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout.setAlignment(Qt::AlignHCenter);

    // Connect the Login button to a slot
    QObject::connect(&loginButton, &QPushButton::clicked, [&]()
    {
        // Get the text from the fields
        QString accountType = accountTypeComboBox.currentText();
        QString jobTitle = jobTitleComboBox.currentText();
        QString username = usernameLineEdit.text();
        QString password = passwordLineEdit.text();

        bool isAuthorized = false;
        bool invalidCredentials = false;

        // Check if the entered username and password match authorized user
        for(const auto& user : authorizedUsers)
        {
            if (user.accountType == accountType && user.jobTitle == jobTitle && user.username == username && user.password == password)
            {
                isAuthorized = true;
                break;
            }
            else if(user.accountType != accountType && user.username == username && user.password == password)
            {
                invalidCredentials = true;
                break;
            }
            else if(user.accountType == accountType && user.jobTitle != jobTitle && user.username == username && user.password == password)
            {
                invalidCredentials = true;
                break;
            }
        }
        // If login is valid...
        if (isAuthorized)
        {
            if(accountType == "Full")
            {
                // Read data from file, store into a vector of type Personnel
                std::vector<Personnel> personnel = Personnel::readPersonnelData("Personnel.csv");

                // Create table widget for Personnel data
                QTableWidget* personnelTableWidget = new QTableWidget;
                personnelTableWidget->setRowCount(personnel.size());
                personnelTableWidget->setColumnCount(11);
                personnelTableWidget->setHorizontalHeaderLabels({"ID", "Name", "Address", "City", "State", "Zip", "Home Phone", "Cell Phone", "Salary", "Employment Length", "Current Assignment"});

                // Iterate through the Personnel data and display it in the table
                int i = 0;
                for(Personnel employee : personnel)
                {
                    personnelTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(employee.getID())));
                    personnelTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(employee.getName()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(employee.getAddress()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(employee.getCity()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(employee.getState()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(employee.getZip())));
                    personnelTableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(employee.getHomePhoneNumber()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(employee.getCellPhoneNumber()), QTableWidgetItem::Type));
                    personnelTableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(employee.getSalary())));
                    personnelTableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(employee.getEmploymentLength())));
                    personnelTableWidget->setItem(i, 10, new QTableWidgetItem(QString::fromStdString(employee.getCurrentAssignment()), QTableWidgetItem::Type));
                    ++i;
                }
                personnelTableWidget->setColumnWidth(1, personnelTableWidget->columnWidth(0)*1.5);
                personnelTableWidget->setColumnWidth(2, personnelTableWidget->columnWidth(1)*1.25);
                personnelTableWidget->setColumnWidth(7, personnelTableWidget->columnWidth(6)*1.1);
                personnelTableWidget->setColumnWidth(9, personnelTableWidget->columnWidth(1)*1.05);
                personnelTableWidget->setColumnWidth(10, personnelTableWidget->columnWidth(9)*1.5);
                personnelTableWidget->resize(1400, 600);
                personnelTableWidget->show();

                // Read data from file, store into a vector of type EquipmentData
                std::vector<EquipmentData> vehicles = EquipmentData::readEquipmentData("EquipmentData.csv");

                // Create EquipmentData table widget
                QTableWidget* equipmentTableWidget = new QTableWidget;
                equipmentTableWidget->setRowCount(vehicles.size());
                equipmentTableWidget->setColumnCount(9);
                equipmentTableWidget->setHorizontalHeaderLabels({"Vehicle ID", "Brand", "Year", "Model", "Type", "Parts List", "Routine Inspections", "Routine Maintenance", "Repair Records"});

                // Iterate through EquipmentData and display it in the table
                int j = 0;
                for(EquipmentData vehicle : vehicles)
                {
                    equipmentTableWidget->setItem(j, 0, new QTableWidgetItem(QString::number(vehicle.getID())));
                    equipmentTableWidget->setItem(j, 1, new QTableWidgetItem(QString::fromStdString(vehicle.getBrand()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 2, new QTableWidgetItem(QString::number(vehicle.getYear())));
                    equipmentTableWidget->setItem(j, 3, new QTableWidgetItem(QString::fromStdString(vehicle.getModel()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 4, new QTableWidgetItem(QString::fromStdString(vehicle.getType()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 5, new QTableWidgetItem(QString::fromStdString(vehicle.getPartsList()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 6, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineInspections()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 7, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineMaintenance()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 8, new QTableWidgetItem(QString::fromStdString(vehicle.getRepairRecords()), QTableWidgetItem::Type));
                    ++j;
                }
                equipmentTableWidget->setColumnWidth(6, equipmentTableWidget->columnWidth(5)*1.15);
                equipmentTableWidget->setColumnWidth(7, equipmentTableWidget->columnWidth(5)*1.2);
                equipmentTableWidget->resize(1000, 600);
                equipmentTableWidget->show();

                // Read data from file, store into a vector of type Shipment
                std::vector<Shipment> shipments = Shipment::readShipmentData("ShippingData.csv");

                // Create Shipment table widget
                QTableWidget* shipmentTableWidget = new QTableWidget;
                shipmentTableWidget->setRowCount(shipments.size());
                shipmentTableWidget->setColumnCount(13);
                shipmentTableWidget->setHorizontalHeaderLabels({"Type", "Company", "Address", "City", "State", "Zip", "Vehicle ID", "Departure Date/Time", "Estimated Arrival Date/Time", "Arrival Confirmation", "Drivers", "Manifest", "Purchase Order"});

                // Iterate through Shipments and display it in the table
                int k = 0;
                for(Shipment shipment : shipments)
                {
                    shipmentTableWidget->setItem(k, 0, new QTableWidgetItem(QString::fromStdString(shipment.getType()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 1, new QTableWidgetItem(QString::fromStdString(shipment.getCompany()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 2, new QTableWidgetItem(QString::fromStdString(shipment.getAddress()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 3, new QTableWidgetItem(QString::fromStdString(shipment.getCity()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 4, new QTableWidgetItem(QString::fromStdString(shipment.getState()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 5, new QTableWidgetItem(QString::number(shipment.getZip())));
                    shipmentTableWidget->setItem(k, 6, new QTableWidgetItem(QString::number(shipment.getVehicleID())));
                    shipmentTableWidget->setItem(k, 7, new QTableWidgetItem(QString::fromStdString(shipment.getDepartureDateTime()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 8, new QTableWidgetItem(QString::fromStdString(shipment.getEstimatedArrivalDateTime()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 9, new QTableWidgetItem(QString::fromStdString(shipment.getArrivalConfirmation()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 10, new QTableWidgetItem(QString::fromStdString(shipment.getDrivers()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 11, new QTableWidgetItem(QString::fromStdString(shipment.getManifest()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(k, 12, new QTableWidgetItem(QString::fromStdString(shipment.getPurchaseOrder()), QTableWidgetItem::Type));
                    ++k;
                }
                shipmentTableWidget->setColumnWidth(1, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(7, shipmentTableWidget->columnWidth(0)*1.25);
                shipmentTableWidget->setColumnWidth(8, shipmentTableWidget->columnWidth(7)*1.25);
                shipmentTableWidget->setColumnWidth(9, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(11, shipmentTableWidget->columnWidth(9)*1.5);
                shipmentTableWidget->setColumnWidth(12, shipmentTableWidget->columnWidth(11)*1.2);
                shipmentTableWidget->resize(1500, 600);
                shipmentTableWidget->show();
            }
            else if(accountType == "Maintenance Data")
            {
                std::vector<EquipmentData> vehicles = EquipmentData::readEquipmentData("EquipmentData.csv");

                QTableWidget* equipmentTableWidget = new QTableWidget;
                equipmentTableWidget->setRowCount(vehicles.size());
                equipmentTableWidget->setColumnCount(9);
                equipmentTableWidget->setHorizontalHeaderLabels({"Vehicle ID", "Brand", "Year", "Model", "Type", "Parts List", "Routine Inspections", "Routine Maintenance", "Repair Records"});
                int i = 0;
                for(EquipmentData vehicle : vehicles)
                {
                    equipmentTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(vehicle.getID())));
                    equipmentTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(vehicle.getBrand()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(vehicle.getYear())));
                    equipmentTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(vehicle.getModel()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(vehicle.getType()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(vehicle.getPartsList()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineInspections()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineMaintenance()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(i, 8, new QTableWidgetItem(QString::fromStdString(vehicle.getRepairRecords()), QTableWidgetItem::Type));
                    ++i;
                }
                equipmentTableWidget->setColumnWidth(6, equipmentTableWidget->columnWidth(5)*1.15);
                equipmentTableWidget->setColumnWidth(7, equipmentTableWidget->columnWidth(5)*1.2);
                equipmentTableWidget->resize(1000, 600);
                equipmentTableWidget->show();
            }
            else if(accountType == "Shipping Data")
            {
                std::vector<Shipment> shipments = Shipment::readShipmentData("ShippingData.csv");

                QTableWidget* shipmentTableWidget = new QTableWidget;
                shipmentTableWidget->setRowCount(shipments.size());
                shipmentTableWidget->setColumnCount(13);
                shipmentTableWidget->setHorizontalHeaderLabels({"Type", "Company", "Address", "City", "State", "Zip", "Vehicle ID", "Departure Date/Time", "Estimated Arrival Date/Time", "Arrival Confirmation", "Drivers", "Manifest", "Purchase Order"});

                int i = 0;
                for(Shipment shipment : shipments)
                {
                    shipmentTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(shipment.getType()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(shipment.getCompany()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(shipment.getAddress()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(shipment.getCity()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(shipment.getState()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(shipment.getZip())));
                    shipmentTableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(shipment.getVehicleID())));
                    shipmentTableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(shipment.getDepartureDateTime()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 8, new QTableWidgetItem(QString::fromStdString(shipment.getEstimatedArrivalDateTime()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 9, new QTableWidgetItem(QString::fromStdString(shipment.getArrivalConfirmation()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 10, new QTableWidgetItem(QString::fromStdString(shipment.getDrivers()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 11, new QTableWidgetItem(QString::fromStdString(shipment.getManifest()), QTableWidgetItem::Type));
                    shipmentTableWidget->setItem(i, 12, new QTableWidgetItem(QString::fromStdString(shipment.getPurchaseOrder()), QTableWidgetItem::Type));
                    ++i;
                }
                shipmentTableWidget->setColumnWidth(1, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(7, shipmentTableWidget->columnWidth(0)*1.25);
                shipmentTableWidget->setColumnWidth(8, shipmentTableWidget->columnWidth(7)*1.25);
                shipmentTableWidget->setColumnWidth(9, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(11, shipmentTableWidget->columnWidth(9)*1.5);
                shipmentTableWidget->setColumnWidth(12, shipmentTableWidget->columnWidth(11)*1.2);
                shipmentTableWidget->resize(1500, 600);
                shipmentTableWidget->show();

                std::vector<EquipmentData> vehicles = EquipmentData::readEquipmentData("EquipmentData.csv");

                QTableWidget* equipmentTableWidget = new QTableWidget;
                equipmentTableWidget->setRowCount(vehicles.size());
                equipmentTableWidget->setColumnCount(9);
                equipmentTableWidget->setHorizontalHeaderLabels({"Vehicle ID", "Brand", "Year", "Model", "Type", "Parts List", "Routine Inspections", "Routine Maintenance", "Repair Records"});

                int j = 0;
                for(EquipmentData vehicle : vehicles)
                {
                    equipmentTableWidget->setItem(j, 0, new QTableWidgetItem(QString::number(vehicle.getID())));
                    equipmentTableWidget->setItem(j, 1, new QTableWidgetItem(QString::fromStdString(vehicle.getBrand()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 2, new QTableWidgetItem(QString::number(vehicle.getYear())));
                    equipmentTableWidget->setItem(j, 3, new QTableWidgetItem(QString::fromStdString(vehicle.getModel()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 4, new QTableWidgetItem(QString::fromStdString(vehicle.getType()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 5, new QTableWidgetItem(QString::fromStdString(vehicle.getPartsList()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 6, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineInspections()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 7, new QTableWidgetItem(QString::fromStdString(vehicle.getRoutineMaintenance()), QTableWidgetItem::Type));
                    equipmentTableWidget->setItem(j, 8, new QTableWidgetItem(QString::fromStdString(vehicle.getRepairRecords()), QTableWidgetItem::Type));
                    ++j;
                }
                equipmentTableWidget->setColumnWidth(6, equipmentTableWidget->columnWidth(5)*1.15);
                equipmentTableWidget->setColumnWidth(7, equipmentTableWidget->columnWidth(5)*1.2);
                equipmentTableWidget->resize(1000, 600);
                equipmentTableWidget->show();
            }
            else if(accountType == "Driver Data")
            {
                std::vector<Shipment> shipments = Shipment::readShipmentData("ShippingData.csv");

                QTableWidget* shipmentTableWidget = new QTableWidget;
                shipmentTableWidget->setRowCount(shipments.size());
                shipmentTableWidget->setColumnCount(13);
                shipmentTableWidget->setHorizontalHeaderLabels({"Type", "Company", "Address", "City", "State", "Zip", "Vehicle ID", "Departure Date/Time", "Estimated Arrival Date/Time", "Arrival Confirmation", "Drivers", "Manifest", "Purchase Order"});

                int i = 0;
                for(Shipment shipment : shipments)
                {
                    // Check if the Driver username == a Driver in ShipmentData
                    if(shipment.getDrivers() == username.toStdString())
                    {
                        shipmentTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(shipment.getType()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(shipment.getCompany()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(shipment.getAddress()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(shipment.getCity()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(shipment.getState()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(shipment.getZip())));
                        shipmentTableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(shipment.getVehicleID())));
                        shipmentTableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(shipment.getDepartureDateTime()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 8, new QTableWidgetItem(QString::fromStdString(shipment.getEstimatedArrivalDateTime()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 9, new QTableWidgetItem(QString::fromStdString(shipment.getArrivalConfirmation()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 10, new QTableWidgetItem(QString::fromStdString(shipment.getDrivers()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 11, new QTableWidgetItem(QString::fromStdString(shipment.getManifest()), QTableWidgetItem::Type));
                        shipmentTableWidget->setItem(i, 12, new QTableWidgetItem(QString::fromStdString(shipment.getPurchaseOrder()), QTableWidgetItem::Type));
                        ++i;
                    }
                }
                shipmentTableWidget->setColumnWidth(1, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(7, shipmentTableWidget->columnWidth(0)*1.25);
                shipmentTableWidget->setColumnWidth(8, shipmentTableWidget->columnWidth(7)*1.25);
                shipmentTableWidget->setColumnWidth(9, shipmentTableWidget->columnWidth(0)*1.15);
                shipmentTableWidget->setColumnWidth(11, shipmentTableWidget->columnWidth(9)*1.5);
                shipmentTableWidget->setColumnWidth(12, shipmentTableWidget->columnWidth(11)*1.2);
                shipmentTableWidget->resize(1500, 600);
                shipmentTableWidget->show();
            }
        }
        else if(invalidCredentials)
        {
            QMessageBox::warning(&window, "Login Failed", "You do not have access to this information.");
        }
        else
        {
            // User is not authorized, display error message
            QMessageBox::warning(&window, "Login Failed", "Incorrect username or password.");
        }

        // Clear the fields
        accountTypeComboBox.clear();
        usernameLineEdit.clear();
        passwordLineEdit.clear();
    });

    // Print the monthly payroll for all employees to the console
    std::vector<Personnel> personnel = Personnel::readPersonnelData("Personnel.csv");
    std::cout << "Monthly Payroll Report" << std::endl;
    for(Personnel employee : personnel)
    {
        std::cout << employee.getName() << "'s compensation: " << employee.getSalary() / 12 << std::endl;
    }

    // Show the window
    window.show();

    // Run the event loop
    return app.exec();
}