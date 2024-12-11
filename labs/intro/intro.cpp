/* Program Name: intro
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID: 000664328
 * Program Description: Learning the basics of unix and c++ */
//! Remember: your comments
//! Remember: your formatting and indentation
//  auto-format in vim: gg=G in normal mode, in vscode: alt+shift+f

#include<iostream>
#include <string>

using namespace std;

int main() {
	string name;

	// Take user input
	cout << "What is your name? ";
	cin >> name;

	// Print user's name
	cout << "Hello, " << name << "!" << endl;
	return 0;
}
