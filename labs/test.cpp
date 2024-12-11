/* Program Name: PROGRAM NAME HERE
 * Student Name: YOUR NAME HERE
 * Net ID: NETID HERE
 * Student ID: STUDENT ID HERE (000-12-3456)
 * Program Description: BRIEF, 1-2 SENTENCE DESCRIPTION HERE */

//! Remember: your comments
//! Remember: your formatting and indentation
//  - auto-format in vim: gg=G in normal mode, in vscode: alt+shift+f
//! Remember: check your solution with the gradescripts
//  - gradescript command: `python3.11 scripts/test.py mpg.cpp`

#include <iostream>
#include <limits>
#include <string>

using namespace std;

/* Error check example for reference (delete later)
   while (true) {
   cout << "Enter a value: ";
   if (!(cin >> value)) {
// clear the error state. While cin is in an error state, it
cin.clear();
// ignore up to the next newline or EOF
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid input. Please try again." << endl;
} else {
cout << "Success! Value is: " << value << endl;
break;
}
}
*/

double checkString(string value) {
	int i;
	if(value.compare("\n")) {}

	for(i = 0 ; i < value.length(); i++) {
		int index = value.at(i);
		if(!(index < 57 && index > 48 || index == 46)) {
			break;
		}
	}
  if(i == 0) {
    return -1;
  }
	string answer = value.substr(0, i);

	return stod(answer);
}

int main() {
	//! You do not need a vector, you can keep track of all the information with
	//! doubles
	double milesTruck = 0.0;
	double gallonsTruck = 0.0;
	double milesCar = 0.0;
	double gallonsCar = 0.0;
	int cars;
	int trucks;
	double AvgMPGCar = 0.0;
	double AvgMPGTruck = 0.0;

	while(true) {
		string command;
		double miles = 0.0;
		double gallons = 0.0;

    //Error check user command
		while(true) {
			cout << "Enter command: ";
			do {
				getline(cin, command);
			}while(command.compare("") == 0);
			
			
			
			if(!cin.fail()) {
				if (command.compare("car") == 0 || command.compare("truck") == 0 || command.compare("done") == 0) {
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

    if(command.compare("done") == 0) {
			break;
		}

    //Ask for miles for command and error check.
		while(true) {
			cout << "Enter " << command << "'s miles: ";
			string input;
			do {
				getline(cin, input);
			}while(input.compare("") == 0);
			miles = checkString(input);
      if (!(miles <= 0)) {
        break;
      }
      input.clear();
		}
    while(true) {
			cout << "Enter " << command << "'s gallons: ";
			string input;
			do {
				getline(cin, input);
			}while(input.compare("") == 0);
			gallons = checkString(input);
      if (!(gallons <= 0)) {
        break;
      }
      input.clear();
		}

		if(!command.compare("car")) {
			milesCar += miles;
			gallonsCar += gallons;
			cars += 1;

		}
		if(!command.compare("truck")) {
			milesTruck += miles;
			gallonsTruck += gallons;
			trucks += 1;

		}

	}
	if (gallonsCar == 0) {
		gallonsCar = 1;
	}
	if (gallonsTruck == 0) {
		gallonsTruck = 1;
	}
	AvgMPGCar = milesCar / gallonsCar;
	AvgMPGTruck = milesTruck / gallonsTruck;

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

	// TODO
	return 0;
}