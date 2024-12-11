/* Program Name: Bowling
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This is a Multi-User Dungeons game
 * that supports a single user and several rooms.
 * 
 * TA Gaddy: Help me with pointer syntax.
 * */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Create Room Constructor for array.
struct Room
{
	int north = -1;
	int south = -1;
	int east = -1;
	int west = -1;
	string name;
	string description;
};

// Take in a direction char, return the room index in that direction.
int getExit(const Room &room, const char direction)
{
	int go;
	switch (direction)
	{
		case 'n':
			if (!(room.north == -1))
			{
				go = room.north;
			}
			else
			{
				go = -1;
			}
			break;
		case 'e':
			if (!(room.east == -1))
			{
				go = room.east;
			}
			else
			{
				go = -1;
			}
			break;
		case 's':
			if (!(room.south == -1))
			{
				go = room.south;
			}
			else
			{
				go = -1;
			}
			break;
		case 'w':
			if (!(room.west == -1))
			{
				go = room.west;
			}
			else
			{
				go = -1;
			}
			break;
		default:
			break;
	}
	return go;
}

// Print the room's name, description, and exits.
void look(const Room &room)
{

	cout << room.name << endl;
	cout << room.description << endl;
	cout << endl;
	cout << "Exits:";
	if (!(room.north == -1))
	{
		cout << " n";
	}
	if (!(room.south == -1))
	{
		cout << " s";
	}
	if (!(room.east == -1))
	{
		cout << " e";
	}
	if (!(room.west == -1))
	{
		cout << " w";
	}
	cout << endl;
}

// For debugging, print file information.
void dumpRooms(const Room *const rooms, const size_t roomCount)
{
	for (size_t i = 0; i < roomCount; ++i)
	{
		cout << "Room " << i << endl;
		cout << "  name: " << rooms[i].name << endl;
		cout << "  description: " << rooms[i].description << endl;
		cout << "  north: " << rooms[i].north << endl;
		cout << "  south: " << rooms[i].south << endl;
		cout << "  east:  " << rooms[i].east << endl;
		cout << "  west:  " << rooms[i].west << endl;
	}
}

// Create function to removes whitespace from before and after text.
void stripWhitespace(string &str)
{
	while (!str.empty() && isspace(str.back()))
	{
		str.pop_back();
	}
	while (!str.empty() && isspace(str.front()))
	{
		str.erase(str.begin());
	}
}

// Create function to take direction char and return the direction that char represents.
string getDirectionName(const char direction)
{
	string theWay;
	switch (direction)
	{
		case 'n':
			theWay = "NORTH";
			break;
		case 'e':
			theWay = "EAST";
			break;
		case 's':
			theWay = "SOUTH";
			break;
		case 'w':
			theWay = "WEST";
			break;

		default:
			break;
	}
	return theWay;
}

// Create function to load the contents of a file into an array.
const Room *loadRooms(const string dungeonFilename)
{

	// First, count number of rooms.
	size_t tildeCount = 0;

	// Open file and error check to see if it opens.
	ifstream fin(dungeonFilename);
	if (fin.fail())
	{
		cerr << "Error: failed to open file" << endl;
		exit(1);
	}

	string hold;
	while (getline(fin, hold, '~'))
	{
		tildeCount++;
	}
	size_t roomCount = 0;
	roomCount = tildeCount / 3;
	fin.clear();
	fin.seekg(0);

	// Create the array to hold the rooms with the Room constructor.
	Room *rooms = new Room[roomCount];
	// Read in the rooms
	for (size_t i = 0; i < roomCount; i++)
	{
		string buffer;

		// Read in room name.
		getline(fin, buffer, '~');
		stripWhitespace(buffer);
		(rooms + i)->name = buffer;

		// Read in room description.
		getline(fin, buffer, '~');
		stripWhitespace(buffer);
		(rooms + i)->description = buffer;

		// Read in room exits.
		getline(fin, buffer, '~');
		stripWhitespace(buffer);
		istringstream sin(buffer);
		string list;

		while (getline(sin, list))
		{
			istringstream ss(list);

			char d;
			int r;
			ss >> d >> r;

			switch (d)
			{
				case 'n':
					(rooms + i)->north = r;
					break;
				case 'e':
					(rooms + i)->east = r;
					break;
				case 's':
					(rooms + i)->south = r;
					break;
				case 'w':
					(rooms + i)->west = r;
					break;
			}
		}
	}
	fin.close();

	// Check rooms for format errors.
	dumpRooms(rooms, roomCount);

	return rooms;
}

int main(int argc, char **argv)
{
	// Read the filename from argv and error check.
	if (argc != 2)
	{
		cerr << "Usage: ./mud filename" << endl;
		return 1;
	}

	// Load rooms.
	const Room *room = loadRooms(argv[1]);

	int currentRoom = 0;
	int hold;

	// Start the game.
	while (true)
	{

		// Get user's command.
		char input;
		cout << "> ";
		cin >> input;

		switch (input)
		{

			// Quit if user types 'q'.
			case 'q':
				delete[] room;
				return 0;

				// Print information about the user's current room if
				// their command is 'l'.
			case 'l':
				look(room[currentRoom]);
				break;

				// Move in the direction of the user's command if possible.
			case 'n':
			case 'e':
			case 'w':
			case 's':
				hold = getExit(room[currentRoom], input);
				if (!(hold == -1))
				{
					currentRoom = hold;
					cout << "You moved " << getDirectionName(input) << "." << endl;
				}
				else
				{
					cout << "You can't go " << getDirectionName(input) << "!" << endl;
				}
				break;

			default:
				break;
		}
	}
}
