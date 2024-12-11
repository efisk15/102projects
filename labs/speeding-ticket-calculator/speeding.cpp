/* Program Name: Speeding Ticket Calculator
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will ask the user for a ticket file,
 * and the range of dates the user wants information on fines from,
 * as well as the file name they want the fine information to be
 * printed to. The program will then print the information on the fines into
 * the file.*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Create array to hold months for output.
const string THREE_LETTER_MONTHS[] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec",
};

// Create const variables to hold fine multipliers.
const double INTERSTATE_MULTIPLIER = 5.2243;
const double HIGHWAY_MULTIPLIER = 9.4312;
const double RESIDENTIAL_MULTIPLIER = 17.2537;
const double DEFAULT_MULTIPLIER = 12.916;

// Create function to create an integer to represent the date for calculations
int serializeDate(const int year, const int month, const int day)
{
    int serialDate;
    serialDate = year * 10000 + month * 100 + day;
    return serialDate;
}

int main()
{
    // Inicialize fin and fout.
    ifstream fin;
    ofstream fout;

    // Create local variables.
    string ticketFile, reportFile, citation;
    char road;
    int month, day, year, clockSpeed, speedLimit, startMM, startDD, startYYYY, endMM, endDD, endYYYY, startDate, endDate;

    // Ask for ticket file and error check to make sure it opened.
    cout << "Enter a ticket file: ";
    cin >> ticketFile;
    fin.open(ticketFile);
    if (fin.fail())
    {
        cerr << "Unable to open " << ticketFile << "." << endl;
        return 1;
    }

    // Ask for report file and error check to make sure it opened.
    cout << "Enter a report file: ";
    cin >> reportFile;
    fout.open(reportFile);
    if (!fout.is_open())
    {
        cerr << "Unable to open " << reportFile << "." << endl;
        return 1;
    }

    // Ask for start and end dates for range of fines and store them in variables.
    cout << "Enter report start date (mm dd yyyy): ";
    cin >> startMM >> startDD >> startYYYY;
    cout << "Enter report end date   (mm dd yyyy): ";
    cin >> endMM >> endDD >> endYYYY;

    // Change user input of dates to one int for calculations.
    startDate = serializeDate(startYYYY, startMM, startDD);
    endDate = serializeDate(endYYYY, endMM, endDD);

    // Find the tickets that fall into the date range and print the necessary fines.
    while (fin >> citation >> month >> day >> year >> clockSpeed >> speedLimit >> road)
    {
        // Create case for if the month given is only 2 integers.
        if (year < 100)
        {
            year += 2000;
        }
        
        // Calculate the fine.
        double fine = clockSpeed - speedLimit;
        int hold = serializeDate(year, month, day);
        if (hold >= startDate && hold <= endDate)
        {
            // Multiply the fine amount by the necessary multiplier.
            switch (tolower(road))
            {
            case 'i':
                fine *= INTERSTATE_MULTIPLIER;
                break;
            case 'r':
                fine *= RESIDENTIAL_MULTIPLIER;
                break;
            case 'h':
                fine *= HIGHWAY_MULTIPLIER;
                break;
            default:
                fine *= DEFAULT_MULTIPLIER;
            }

            // Make a special case for if the fine is below $0.00.
            if (fine < 0)
            {
                fine = 0.00;
            }

            // Print fines to the output file.
            fout << fixed << setprecision(2);
            fout << setw(2) << setfill('0') << day << "-" << THREE_LETTER_MONTHS[month - 1] << "-" << year;
            fout << left << setfill(' ') << " " << setw(11) << citation << "$";
            fout << right << setw(9) << fine << endl;
        }
    }

    // Close fin and fout.
    fin.close();
    fout.close();
    return 0;
}