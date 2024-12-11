/* Program Name: Boiling Water
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will help a user figure out
 * what the boiling point is at a certain location from an input file
 * based on that location's elevation level gotten from that same input file.*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Solve for the boiling point at a given elevation.
double elevationToBoilingPoint(const double elevation)
{
    double boilingPoint = 0.0;
    double pressure;

    pressure = 29.921 * pow((1 - 0.0000068753 * elevation), 5.2559);
    boilingPoint = 49.161 * log(pressure) + 44.932;

    return boilingPoint;
}

int main(int argc, char **argv)
{
    //Create variables.
    string row;
    int i = 1;
    int choice;
    double boiling;
    vector<int> elevations;
    vector<string> cityNames;

    // Error check number of command line arguments.
    if (argc != 2)
    {
        cerr << "usage: ./boiling filename" << endl;
        return 1;
    }

    // Open file and error check to see if it opens.
    ifstream fin(argv[1]);
    if (fin.fail())
    {
        cerr << "File failed to open." << endl;
        return 1;
    }

    // Move past first row of the csv file.
    getline(fin, row);
    row.clear();

    // Output possible cities for user to choose from and store cities and
    // each city's elevation in vectors and ignore the city's states.
    cout << "Boiling Point at Altitude Calculator" << endl;
    while (getline(fin, row))
    {

        istringstream sin(row);
        string city, state, elevation;

        getline(sin, city, ',');
        cout << i << ". " << city << endl;
        cityNames.push_back(city);

        getline(sin, state, ',');
        state.clear();

        if (getline(sin, elevation))
        {
            elevations.push_back(stoi(elevation));
        }
        ++i;
    }
    fin.close();

    // Ask user for which city they want the boiling point of.
    cout << "Enter city number: ";
    cin >> choice;

    // Get boiling point.
    boiling = elevationToBoilingPoint(elevations[choice - 1]);

    // Output the boiling point of the city the user is in.
    cout << "The boiling point at " << cityNames[choice - 1] << " is " << boiling << " degrees Fahrenheit." << endl;

    return 0;
}