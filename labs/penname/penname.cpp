/* Program Name: Penname
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will ask for some information about the user, then it will output new
 * personal information, based off of the user's original input, for the user to use as a penname*/

#include <iostream>
#include <string>

using namespace std;

int main() {
	// Create Variables for user input
	string firstName, lastName, streetName, streetType, birthCity;
	int age, streetNum, newAddress, newAge;

	// Take user input and store it in variables
	cout << "Enter your first and middle names: ";
	cin >> firstName >> lastName;
	cout << "Enter your age: ";
	cin >> age;
	cout << "Enter your street number, name, and type: ";
	cin >> streetNum >> streetName >> streetType;
	cout << "Enter your city of birth: ";
	cin >> birthCity;

	// Create new address number and new age
	newAddress = age * 425 / streetNum;
	newAge = streetNum % age * 3;

	// Print penname information
	cout << endl;
	cout << "Your penname name is " << birthCity << " " << streetName << "." << endl;
	cout << "You will write as a " << newAge << " year old." << endl;
	cout << "Your address is " << newAddress << " " << lastName << " " << streetType << "." << endl;

	return 0;
}
