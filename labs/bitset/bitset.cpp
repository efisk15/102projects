/* Program Name: Bitset
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will allow the user to create
 * and manipulate bits using commands and indexes to access specific bits.*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Create bitset class.
class BITSET
{
	vector<int> mSets;

	public:
	BITSET();
	bool Test(int index) const;
	void Set(int index);
	void Clear(int index);
	int GetNumSets() const;
	int GetSet(int index) const;
};

string ToBinary(int bit_set, int spacing = 4);

int main()
{
	// Call constructor to create a class.
	BITSET sets;
	string command;
	int which;
	do
	{
		cout << "> ";
		if (!(cin >> command) || "q" == command)
		{
			break;
		}
		// Create commands for user to call and error check.
		if ("t" == command)
		{
			if (!(cin >> which))
			{
				cout << "Invalid index\n";
			}
			else
			{
				cout << sets.Test(which) << '\n';
			}
		}
		else if ("s" == command)
		{
			if (!(cin >> which))
			{
				cout << "Invalid index\n";
			}
			else
			{
				sets.Set(which);
			}
		}
		else if ("g" == command)
		{
			int spacing;
			string line;
			getline(cin, line);
			istringstream sin{line};
			if (!(sin >> which))
			{
				cout << "Invalid index\n";
			}
			else
			{
				if (!(sin >> spacing))
				{
					spacing = 4;
				}
				cout << ToBinary(sets.GetSet(which), spacing) << '\n';
			}
		}
		else if ("c" == command)
		{
			if (!(cin >> which))
			{
				cout << "Invalid index\n";
			}
			else
			{
				sets.Clear(which);
			}
		}
		else if ("n" == command)
		{
			cout << sets.GetNumSets() << endl;
		}
		else
		{
			cout << "Unknown command '" << command << "'\n";
		}
	} while (true);
	return 0;
}

// Create function to convert number to binary for printing.
string ToBinary(int bit_set, int spacing)
{
	string ret;
	for (int i = 31; i >= 0; i--)
	{

		int mask = 1 << i;
		if (bit_set & mask)
		{
			ret += '1';
		}
		else
		{
			ret += '0';
		}

		// Format the bits.
		if (((32 - i) % spacing == 0) && i != 0)
		{
			ret += ' ';
		}
	}
	return ret;
}

// BITSET Class Members.
BITSET::BITSET() : mSets(1, 0) {}

// Create function to test whether a bit is on or off.
bool BITSET::Test(int index) const
{
	int which_set = index / 32;
	int which_bit = index - which_set * 32;
	if (which_set >= GetNumSets())
	{
		return false;
	}

	int mask = 1 << which_bit;
	return (GetSet(which_set) & mask);
}

// Create function to turn a specified bit on if it is not already on.
void BITSET::Set(int index)
{
	int which_set = index / 32;
	int which_bit = index - which_set * 32;

	if (int(which_set) >= int(mSets.size()))
	{
		mSets.resize(which_set + 1);
	}
	int mask = 1 << which_bit;
	mSets.at(which_set) = mSets.at(which_set) | mask;
}

// Create function to turn off a bit that is on.
void BITSET::Clear(int index)
{
	int which_set = index / 32;
	int which_bit = index - which_set * 32;
	if (which_set < GetNumSets())
	{
		int mask = 1 << which_bit;
		mSets.at(which_set) = mSets.at(which_set) & (~mask);

		// Truncate empty sets--sets that are 0.
		int top = mSets.size();
		for (int i = top; i > 1; i--)
		{
			if (mSets.at(i - 1) == 0)
			{
				mSets.resize(i - 1);
				continue;
			}
			break;
		}
	}
}

// Create function that will return the number of sets.
int BITSET::GetNumSets() const { return static_cast<int>(mSets.size()); }

// Create a function that will return a specific set.
int BITSET::GetSet(int which_set) const
{
	if (int(which_set) > int(mSets.size() - 1))
	{
		return 0;
	}
	return mSets.at(which_set);
}
