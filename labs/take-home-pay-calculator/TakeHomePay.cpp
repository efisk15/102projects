/* Program Name: Take Home Calculator
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID: STUDENT ID HERE (000-66-4328)
 * Program Description: This program allows the user to enter their salary as input and the
 * program will output their yearly salary, Social Security tax, Medicare tax, Income tax, take home salary,
 * and monthly take home salary.*/

#include <iomanip>
#include <iostream>

using namespace std;

// Create global variables.
const double MINIMUM_WAGE = 15080;
const double BRACKET1 = 10275;
const double BRACKET1_RATE = 0.10;
const double BRACKET2 = 41775;
const double BRACKET2_RATE = 0.12;
const double BRACKET3 = 89075;
const double BRACKET3_RATE = 0.22;
const double BRACKET4 = 170050;
const double BRACKET4_RATE = 0.24;
const double BRACKET5 = 215950;
const double BRACKET5_RATE = 0.32;
const double BRACKET6 = 539900;
const double BRACKET6_RATE = 0.35;
const double BRACKET7_RATE = 0.37;

int main() {

	// Create varibles.
	double salary;
	double incomeTax = 0;
	double socialSecurity;
	double medicare;
	double takeHome;
	double hold;

	// Ask for user input.
	cout << "Enter a salary: $";
	cin >> salary;

	// Handle the error of getting a number below minimum wage.
	if (salary < MINIMUM_WAGE) {
		cerr << "This is less than minimum wage for a yearly salary." << endl;
		return 1;
	}

	// Set a variable, hold, to hold the value of salary for calculations.
	hold = salary;

	// Solve for the user's incomeTax.
	if (salary > BRACKET6) {
		incomeTax += (hold - BRACKET6) * BRACKET7_RATE;
		hold = BRACKET6;
	}
	if (salary > BRACKET5) {
		incomeTax += (hold - BRACKET5) * BRACKET6_RATE;
		hold = BRACKET5;
	}
	if (salary > BRACKET4) {
		incomeTax += (hold - BRACKET4) * BRACKET5_RATE;
		hold = BRACKET4;
	}
	if (salary > BRACKET3) {
		incomeTax += (hold - BRACKET3) * BRACKET4_RATE;
		hold = BRACKET3;
	}
	if (salary > BRACKET2) {
		incomeTax += (hold - BRACKET2) * BRACKET3_RATE;
		hold = BRACKET2;
	}
	if (salary > BRACKET1) {
		incomeTax += (hold - BRACKET1) * BRACKET2_RATE;
	}

	// Store values in varibles to be printed.
	socialSecurity = salary * 0.062;
	medicare = salary * 0.0145;
	incomeTax = incomeTax + BRACKET1 * BRACKET1_RATE;
	takeHome = salary - incomeTax - medicare - socialSecurity;

	// Print output.
	cout << setw(36) << setfill('-') << "\n" << setfill(' ') << setprecision(2) << fixed;
	cout << setw(25) << left << "Yearly Salary:" << "$" << setw(9) << right << salary << endl;
	cout << setw(25) << left << "Social Security Tax:" << "$" << setw(9) << right << socialSecurity << endl;
	cout << setw(25) << left << "Medicare Tax:" << "$" << setw(9) << right << medicare << endl;
	cout << setw(25) << left << "Income Tax:" << "$" << setw(9) << right << incomeTax << endl;
	cout << setw(36) << setfill('-') << "\n" << setfill(' ');
	cout << setw(25) << left << "Take Home Salary:" << "$" << setw(9) << right << takeHome << endl;
	cout << setw(25) << left << "Monthly Take Home Pay:" << "$" << setw(9) << right << takeHome / 12 << endl;

	return 0;
}
