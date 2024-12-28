#include <iostream>
#include <string>
#include <fstream>
#include <ctime> // For system time handling
#include <sys/stat.h> // For file existence check

using namespace std;

struct Vehicle {
    string licensePlateNumber;
    string vehicleType;
    int parkingSpotNumber;
    time_t parkingTime; // Store the time of parking using system time
};

const int MAX_VEHICLES = 50;
Vehicle parkingLot[MAX_VEHICLES];
int numVehicles = 0;
const int CHARGE_PER_HOUR = 10;

void saveDataToFile() {
    ofstream file("parking_lot_data.txt");
    if (file.is_open()) {
        file << numVehicles << endl;
        for (int i = 0; i < numVehicles; i++) {
            file << parkingLot[i].licensePlateNumber << " " << parkingLot[i].vehicleType << " "
                 << parkingLot[i].parkingSpotNumber << " " << parkingLot[i].parkingTime << endl;
        }
        file.close();
        cout << "Data saved to file successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void displayMenu() {
    cout << "\n*|| SMART PARKING SYSTEM ||*" << endl;
    cout << "\n1. Park Vehicle" << endl;
    cout << "2. Unpark Vehicle" << endl;
    cout << "3. Display Available Parking Spots" << endl;
    cout << "4. Display Occupied Parking Spots" << endl;
    cout << "5. Search for Vehicle" << endl;
    cout << "6. Save and Exit" << endl;
    cout << "-------------------" << endl;
}

bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void parkVehicle() {
    if (numVehicles < MAX_VEHICLES) {
        // Enter and validate license plate number
        string licensePlate;
        cout << "Enter license plate number: ";
        cin >> licensePlate;

        // Validate license plate length and format
        if (licensePlate.length() < 6) {
            cout << "Invalid license plate! License plate should be at least 6 characters long." << endl;
            return;
        } else if (!(isalpha(licensePlate[0]) && isalpha(licensePlate[1]))) {
            cout << "Invalid license plate! The first two characters must be letters." << endl;
            return;
        }

        // Enter vehicle type
        cout << "Enter vehicle type (car, motorcycle, bicycle): ";
        cin >> parkingLot[numVehicles].vehicleType;

        // Automatically store system time as parking time
        parkingLot[numVehicles].parkingTime = time(nullptr); // Get current system time

        // Assign parking spot and increment vehicle count
        parkingLot[numVehicles].parkingSpotNumber = numVehicles + 1;
        parkingLot[numVehicles].licensePlateNumber = licensePlate;
        numVehicles++;

        cout << "Vehicle parked successfully!" << endl;
    } else {
        cout << "Parking lot is full!" << endl;
    }
    saveDataToFile();
}

void unparkVehicle() {
    if (numVehicles == 0) {
        cout << "No vehicles to unpark!" << endl;
        return;
    }

    string licensePlateNumber;
    cout << "Enter license plate number: ";
    cin >> licensePlateNumber;
    for (int i = 0; i < numVehicles; i++) {
        if (parkingLot[i].licensePlateNumber == licensePlateNumber) {
            // Get the current system time
            time_t currentTime = time(nullptr);

            // Calculate the parking duration in hours
            double hoursParked = difftime(currentTime, parkingLot[i].parkingTime) / 3600.0;
            double charge = hoursParked * CHARGE_PER_HOUR;

            // Display charge and unpark vehicle
            cout << "Vehicle unparked successfully!" << endl;
            cout << "Parking duration: " << hoursParked << " hours" << endl;
            cout << "Total charge: Rs " << charge << endl;

            // Clear the parking spot
            parkingLot[i].licensePlateNumber = "null";
            parkingLot[i].vehicleType = "null";
            parkingLot[i].parkingSpotNumber = 0;
            parkingLot[i].parkingTime = 0;

            return;
        }
    }

    cout << "Vehicle not found!" << endl;
}

void displayAvailableParkingSpots() {
    if (MAX_VEHICLES - numVehicles == 0) {
        cout << "No available parking spots!" << endl;
    } else {
        cout << "Available parking spots: " << MAX_VEHICLES - numVehicles << endl;
    }
}

void displayOccupiedParkingSpots() {
    if (numVehicles == 0) {
        cout << "No occupied parking spots!" << endl;
    } else {
        cout << "Occupied parking spots: " << endl;
        for (int i = 0; i < numVehicles; i++) {
            if (parkingLot[i].licensePlateNumber != "null") {
                cout << "Parking spot " << parkingLot[i].parkingSpotNumber << ": "
                     << parkingLot[i].licensePlateNumber << " ("
                     << parkingLot[i].vehicleType << "), Parked at: "
                     << ctime(&parkingLot[i].parkingTime); // Convert time to readable format
            }
        }
    }
}

void searchForVehicle() {
    if (numVehicles == 0) {
        cout << "No vehicles in the parking lot!" << endl;
        return;
    }

    string licensePlateNumber;
    cout << "Enter license plate number: ";
    cin >> licensePlateNumber;
    for (int i = 0; i < numVehicles; i++) {
        if (parkingLot[i].licensePlateNumber == licensePlateNumber) {
            cout << "Vehicle found! Parking spot: " << parkingLot[i].parkingSpotNumber << endl;
            return;
        }
    }
    cout << "Vehicle not found!" << endl;
}

void loadDataFromFile() {
    if (fileExists("parking_lot_data.txt")) {
        ifstream file("parking_lot_data.txt");
        if (file.is_open()) {
            file >> numVehicles;
            for (int i = 0; i < numVehicles; i++) {
                file >> parkingLot[i].licensePlateNumber >> parkingLot[i].vehicleType
                     >> parkingLot[i].parkingSpotNumber >> parkingLot[i].parkingTime;
            }
            file.close();
            cout << "Data loaded from file successfully!" << endl;
        } else {
            cout << "Unable to open file!" << endl;
        }
    } else {
        cout << "No previous data found, starting fresh." << endl;
    }
}

int main() {
    loadDataFromFile();
    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                parkVehicle();
                break;
            case 2:
                unparkVehicle();
                break;
            case 3:
                displayAvailableParkingSpots();
                break;
            case 4:
                displayOccupiedParkingSpots();
                break;
            case 5:
                searchForVehicle();
                break;
            case 6:
                saveDataToFile();
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }}
        return 0;
}
