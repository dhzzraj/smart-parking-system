#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h> // For file existence check

using namespace std;

struct Vehicle {
    string licensePlateNumber;
    string vehicleType;
    int parkingSpotNumber;
};

const int MAX_VEHICLES = 50;
Vehicle parkingLot[MAX_VEHICLES];
int numVehicles = 0;

void displayMenu() {
    cout << "\n**********|| SMART PARKING SYSTEM ||**********" << endl;
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
        cout << "Enter license plate number: ";
        cin >> parkingLot[numVehicles].licensePlateNumber;
        cout << "Enter vehicle type (car, motorcycle, bicycle): ";
        cin >> parkingLot[numVehicles].vehicleType;
        parkingLot[numVehicles].parkingSpotNumber = numVehicles + 1;
        numVehicles++;
        cout << "Vehicle parked successfully!" << endl;
    } else {
        cout << "Parking lot is full!" << endl;
    }
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
            for (int j = i; j < numVehicles - 1; j++) {
                parkingLot[j] = parkingLot[j + 1];
            }
            numVehicles--;
            cout << "Vehicle unparked successfully!" << endl;
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
            cout << "Parking spot " << parkingLot[i].parkingSpotNumber << ": " << parkingLot[i].licensePlateNumber << " (" << parkingLot[i].vehicleType << ")" << endl;
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

void saveDataToFile() {
    ofstream file("parking_lot_data.txt");
    if (file.is_open()) {
        file << numVehicles << endl;
        for (int i = 0; i < numVehicles; i++) {
            file << parkingLot[i].licensePlateNumber << " " << parkingLot[i].vehicleType << " " << parkingLot[i].parkingSpotNumber << endl;
        }
        file.close();
        cout << "Data saved to file successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void loadDataFromFile() {
    if (fileExists("parking_lot_data.txt")) {
        ifstream file("parking_lot_data.txt");
        if (file.is_open()) {
            file >> numVehicles;
            for (int i = 0; i < numVehicles; i++) {
                file >> parkingLot[i].licensePlateNumber >> parkingLot[i].vehicleType >> parkingLot[i].parkingSpotNumber;
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
        }
    }
    return 0;
}
