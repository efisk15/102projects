/* Program Name: MPG Calculator
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program calculates the average miles per gallon of the cars and 
 * trucks in a fleet. */

//  - gradescript command: `python3.11 scripts/test.py mpg.cpp`

#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {

	// Create variables that will be held throughout the program.
	double milesTruck = 0.0;
	double gallonsTruck = 0.0;
	double milesCar = 0.0;
	double gallonsCar = 0.0;
	double AvgMPGCar = 0.0;
	double AvgMPGTruck = 0.0;

	while(true) {

		// Create varibles for calculations.
		string command;
		double miles = 0.0;
		double gallons = 0.0;

		//Error check user command.
		while(true) {
			cout << "Enter command: ";
			cin >> command;

			if(!cin.fail()) {
				if (command.compare("car") == 0 || command.compare("truck") == 0 || command.compare("done") == 0) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				} 
				else {
					cout << "Unknown command." << endl;
					continue;
				}
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Exit the loop asking for information from the user if the user types "done" as the command.
		if(command.compare("done") == 0) {
			break;
		}

		//Ask for the number of miles for given command and error check.
		while(true) {
			cout << "Enter " << command << "'s miles: ";
			string input;
			cin >> miles;
			if(!cin.fail()) {
				break;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//Ask for the number of gallons for given command and error check.
		while(true) {
			cout << "Enter " << command << "'s gallons: ";
			string input;
			cin >> gallons;
			if(!cin.fail()) {
				break;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Add the miles and gallons given by the user to the total miles and gallons
		// of the given command. 
		if(!command.compare("car")) {
			milesCar += miles;
			gallonsCar += gallons;

		}
		if(!command.compare("truck")) {
			milesTruck += miles;
			gallonsTruck += gallons;
		}
	}

	// Make a special case for if the user does not give input for either cars or trucks.
	if (gallonsCar == 0) {
		gallonsCar = 1;
	}
	if (gallonsTruck == 0) {
		gallonsTruck = 1;
	}

	// Calculate the cars' and trucks' average mpg.
	AvgMPGCar = milesCar / gallonsCar;
	AvgMPGTruck = milesTruck / gallonsTruck;

	// Output the average mph of both the cars and truck. Make a special case for if
	// there are not any of either vehicles.
	if(AvgMPGCar != 0) {
		cout << "Average car MPG = " << AvgMPGCar << endl;
	}
	else {
		cout << "Fleet has no cars." << endl;
	}
	if(AvgMPGTruck != 0) {
		cout << "Average truck MPG = " << AvgMPGTruck << endl;
	}
	else {
		cout << "Fleet has no trucks." << endl;
	}

	return 0;
}
