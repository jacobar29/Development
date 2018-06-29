// simulate rolling up to six dice, graphically representing them in the command line 

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{

	int rolls[6] = { 7,7,7,7,7,7 };	//holds each roll, 7 represents the default value that will cause that roll to be skipped.
	int noOfRolls;
	char cont = 'c';   // if cont = c a new value is requested for number of rolls, else if n program exits

					   // segments holds every possible row required to visually represent the dice
	string segments[8] = { ".-------.",
		"|       |",
		"|     0 |",
		"|   0   |",
		"| 0     |",
		"| 0 0 0 |",
		"| 0   0 |",
		"\'-------\'" };

	// multidimensional array holding the required combination of segments to represent each possible dice roll
	int side_repr[6][5] = { { 0, 1, 3, 1, 7 },
	{ 0, 2, 1, 4, 7 },
	{ 0, 4, 3, 2, 7 },
	{ 0, 6, 1, 6, 7 },
	{ 0, 6, 3, 6, 7 },
	{ 0, 5, 1, 5, 7 } };

	srand(time(NULL));	  // seed random number

						  //====================================================================================================	

	cout << "welcome to DiceRoller" << endl << "*********************" << endl;

	while (cont != 'n')
	{
		// === change number of rolls ===
		if (cont = 'c')
		{
			cout << "how many dice would you like to roll? (1 - 6)" << endl;
			cin >> noOfRolls;

			// catches non integer values and integers out of range 
			while (cin.fail() || !(noOfRolls > 0 && noOfRolls < 7))
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "invalid value, enter a number between 1 and 6" << endl;
				cin >> noOfRolls;
			}
		}

		// === roll and draw dice =====

		// replace the required number of rolls with random values between 1 and 6
		for (int i = 0; i < noOfRolls; i++)
		{
			rolls[i] = rand() % 6;
		}

		// draw each roll one segment at a time	
		for (int i = 0; i< 5; i++)
		{
			for (auto roll : rolls) {
				if (roll != 7) {
					cout << segments[side_repr[roll][i]] << " ";
				}
			}
			cout << endl;
		}

		// reset rolls to default value;
		for (int i = 0; i < 5; i++)
		{
			rolls[i] = 7;
		}

		// === roll again? ===
		cout << "continue?" << endl << " [c] to change number of dice" << endl <<
			" [n] to exit" << endl << " any other key to roll again" << endl;
		cin >> cont;

	}

	return 0;
}
