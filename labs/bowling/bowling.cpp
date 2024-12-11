/* Program Name: Bowling
 * Student Name: Eli Fisk
 * Net ID: efisk
 * Student ID:000-66-4328
 * Program Description: This program will calculate the scores from
 * a game of bowling based off of the number of pins knocked over each roll.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Create Constant Variables.
const size_t NUMBER_OF_FRAMES = 10;
const size_t ROLLS_PER_FRAME = 2;
const size_t TOTAL_ROLLS = NUMBER_OF_FRAMES * 2 + 1;
const int NUMBER_OF_PINS = 10;

vector<int> inputPlayerRolls()
{

	vector<int> playerRolls(TOTAL_ROLLS, 0);
	int rollInput;

	// Input first 20 rolls.
	for (size_t frame = 0; frame < NUMBER_OF_FRAMES; ++frame)
	{
		for (size_t roll = 0; roll < ROLLS_PER_FRAME; ++roll)
		{
			// Output prompt for score.
			cout << "Enter score for frame " << frame + 1 << ", roll " << roll + 1 << ": ";
			cin >> rollInput;

			// Calculate the rollIndex 0..19 for the current frame and roll.
			int rollIndex = frame * 2 + roll;
			playerRolls[rollIndex] = rollInput;

			// If roll is a strike, break out of the inner loop.
			if (rollInput == 10 && frame != 9)
			{
				break;
			}
		}
	}

	// Prompt and input the last roll if needed.
	if ((playerRolls[18] + playerRolls[19]) == 10 || playerRolls[18] == 10)
	{
		cout << "Enter score for frame 10, roll 3: ";
		cin >> rollInput;
		playerRolls[20] = rollInput;
	}

	return playerRolls;
}

// Solve for the score of one player.
int calculatePlayerScore(const vector<int> &playerRolls)
{
	int playerScore = 0;

	for (size_t frameNumber = 0; frameNumber < NUMBER_OF_FRAMES - 1;
			++frameNumber)
	{

		// Create constant varables to make calculations easier.
		const size_t currentFrame = frameNumber * 2;
		const size_t nextFrame = currentFrame + 2;
		const size_t nextNextFrame = nextFrame + 2;

		const int roll1 = playerRolls[currentFrame];
		const int roll2 = playerRolls[currentFrame + 1];

		const bool isStrike = roll1 == NUMBER_OF_PINS;
		const bool isSpare = roll1 + roll2 == NUMBER_OF_PINS;

		// Calculate the frame score.
		if (isStrike)
		{
			playerScore += 10;
			if (playerRolls[nextFrame] == 10)
			{
				if (frameNumber == 8)
				{
					playerScore += 10 + playerRolls[19];
				}
				else
				{
					playerScore += 10 + playerRolls[nextNextFrame];
				}
			}
			else
			{
				playerScore += (playerRolls[nextFrame] + playerRolls[nextFrame + 1]);
			}
		}
		else if (isSpare)
		{
			playerScore += 10 + playerRolls[nextFrame];
		}
		else
		{
			playerScore += (roll1 + roll2);
		}
	}

	// Calculate the 10th frame.
	if (playerRolls[18] == 10)
	{
		playerScore += 10 + playerRolls[19] + playerRolls[20];
	}
	else if (playerRolls[18] + playerRolls[19] == 10)
	{
		playerScore += 10 + playerRolls[20];
	}
	else
	{
		playerScore += playerRolls[18] + playerRolls[19];
	}

	return playerScore;
}

// Create Method to format.
void printGameSummary(const vector<string> &playerNames,
		const vector<int> &playerScores)
{

	if (playerNames.empty())
	{
		cout << "No players were entered." << endl;
		return;
	}

	cout << endl;

	// Print all players and their scores.
	for (size_t i = 0; i < playerNames.size(); i++)
	{
		cout << playerNames[i] << " scored " << playerScores[i] << "." << endl;
	}

	string worstPlayerName = playerNames[0];
	int worstPlayerScore = playerScores[0];

	string bestPlayerName = playerNames[0];
	int bestPlayerScore = playerScores[0];

	for (size_t i = 1; i < playerNames.size(); ++i)
	{
		// Find the best and worst score.
		if (bestPlayerScore < playerScores[i])
		{
			bestPlayerScore = playerScores[i];
			bestPlayerName = playerNames[i];
		}
		if (worstPlayerScore > playerScores[i])
		{
			worstPlayerScore = playerScores[i];
			worstPlayerName = playerNames[i];
		}
	}

	// Print results.
	cout << worstPlayerName << " did the worst by scoring " << worstPlayerScore << "." << endl;
	cout << bestPlayerName << " won the game by scoring " << bestPlayerScore << "." << endl;
}

int main()
{
	vector<string> playerNames;
	vector<int> playerScores;
	int i = 0;

	// Loop through a game of bowling until the user types "done".
	while (true)
	{
		string inputString;

		// Ask for initial playername or the "done" command.
		cout << "Enter player's name (done for no more players): ";
		cin >> inputString;

		// Break loop if user types "done".
		if (inputString == "done")
		{
			break;
		}

		// Add player's names to a vector.
		playerNames.push_back(inputString);

		// Ask for and add the player's rolls to a vector.
		const vector<int> playerRolls = inputPlayerRolls();

		// Call the method to calculate the players scores and add them to a vector.
		const int playerScore = calculatePlayerScore(playerRolls);
		playerScores.push_back(playerScore);

		// Prevents infinite loop if cin is in a bad state.
		if (!cin)
		{
			throw runtime_error("Invalid input");
		}
		i++;
	}

	// Call the game summary method.
	printGameSummary(playerNames, playerScores);

	return 0;
}
