/* Program Name: Vigenere Cipher
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will either encript or decript
 * text gotten from a file using a vigenere cipher depending on whether
 * the user enters a "d" (for decript) or an "e" (for encript). The
 * program will then print the result to another file.*/

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

const size_t ALPHABET_SIZE = 26;

// Create a constructor to be called to create the methods
// and variables needed for the cipher
class VigenereCipher {
	private:
		string mKey;
		char mVTable[ALPHABET_SIZE][ALPHABET_SIZE];
		string fileToString(const string inputFile) const;
		void stringToFile(const string message, const string outputFile) const;
		string makeKeystream(const string message) const;

	public:
		VigenereCipher(const string key);
		void encrypt(const string inputFile, const string outputFile) const;
		void decrypt(const string inputFile, const string outputFile) const;
		void printVTable() const;
};

// Create a method that will pull text out of a file.
string VigenereCipher::fileToString(const string inputFile) const {
	ifstream fin(inputFile);
	string message;
	char character;
	if (!fin.is_open()) {
		cerr << "file " << inputFile << " unable to open." << endl;
		exit(1);
	}
	while (fin.get(character)) {
		message.push_back(character);
	}
	fin.close();
	return message;
}

// Create a file that will print the variable message to an output file.
void VigenereCipher::stringToFile(const string message,
		const string outputFile) const {
	ofstream fout(outputFile);
	if (!fout.is_open()) {
		cerr << "output file " << outputFile << " unable to open." << endl;
		exit(1);
	}
	fout << message;
	fout.close();
}

// Make the keystream necessary for the cipher using the key word given.
string VigenereCipher::makeKeystream(const string message) const {

	string key;
	int j = 0;
	for(size_t i = 0; i < message.size(); i++) {

		if(message[i] <= 'z' && message[i] >= 'a') {
			key += mKey[j];
			j = (j+1)%mKey.size();
		}
		else {
			key += message[i];
		}
	}
	cout << "Keystream: " << key << endl;
	return key;
}

// Create the matrix that will be used to complete encriptions
// and decriptions.
VigenereCipher::VigenereCipher(const string key) {

	mKey = key;

	for (size_t i = 0; i < ALPHABET_SIZE; i++) {
		for (size_t j = 0; j < ALPHABET_SIZE; j++) {
			int k = (j + i)%26 + 97;
			mVTable[i][j] = char(k);
		}
	}

}

// Encript the message given by the input file and print it to the 
// output file.
void VigenereCipher::encrypt(const string inputFile,
		const string outputFile) const {
	ifstream fin(inputFile);
	ofstream fout(outputFile);

	// Create variables and get the keystring.
	string message, eAnswer;
	message = fileToString(inputFile);
	string lkey = makeKeystream(message);

	// Cipher the text.
	for(size_t i = 0; i < message.size() ; i++) {
		if(message[i] > 122 || message[i] < 97) {
			eAnswer += message[i];
		}
		else {
			int k = message[i] - 97;
			int g = lkey[i] - 97;
			eAnswer += mVTable[g][k];
		}
	}

	// Print the output to a file.
	stringToFile(eAnswer, outputFile);
}

// Decript the text given in the input file.
void VigenereCipher::decrypt(const string inputFile,
		const string outputFile) const {

	ifstream fin(inputFile);
	ofstream fout(outputFile);

	// Create variables and get the keystring for decription.
	string message, dAnswer;
	message = fileToString(inputFile);
	string lkey = makeKeystream(message);

	// Decript text.
	for(size_t i = 0; i < message.size() ; i++) {

		if(message[i] > 122 || message[i] < 97) {
			dAnswer += message[i];
		}
		else {
			for(size_t j = 0; j < ALPHABET_SIZE; j++) {
				int l = lkey[i] - 97;
				int y = mVTable[l][j];
				if (y == message[i] ) {
					dAnswer += j + 97;
					break;
				}
			}
		}
	}
	// Print text to the output file.
	stringToFile(dAnswer, outputFile);                            
}

// Print the matrix table if necessary.
void VigenereCipher::printVTable() const {
	for (size_t i = 0; i < ALPHABET_SIZE; i++) {
		for (size_t j = 0; j < ALPHABET_SIZE; j++) {
			std::cout << " " << mVTable[i][j] << " ";
		}
		std::cout << endl;
	}
}

// Create main function.
int main(int argc, char **argv) {

	// Error check to make sure the user used the correct format to
	// start the program.
	if(argc != 5) {
		cerr << "usage: ./vigenere inputFile outputFile key [e/d]" << endl;
		return 1;
	}

	// Create variables then store the commandline arguments in variables.
	string key, task, inputFile, outputFile;

	key =  argv[3];
	key.c_str();

	task = argv[4];
	task.c_str();

	inputFile = argv[1];
	outputFile = argv[2];

	// Create the cipher object in memory using the constructor.
	VigenereCipher cipher(key);

	// If the user entered an "e" on the commandline, encript.
	if(task == "e") {
		cipher.encrypt(inputFile, outputFile);
	}

	// If the user entered a "d" on the commandline, decript.
	if(task == "d") {
		cipher.decrypt(inputFile, outputFile);
	}
}
