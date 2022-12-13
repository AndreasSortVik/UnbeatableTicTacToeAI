#include <iostream>
#include <time.h>

char table[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int size = sizeof(table) / sizeof(table[0]);
int whichPlayer;

bool bPlayerOne = false; // Keeps track of which player's turn
bool bFirstTime = true; // Prints the table with only numbers
bool bEndGame = false; // Stops the game if one player has won or game is stalemate
bool bContinue = false; // Stops while loop in input function if player's input position is invalid (bContinue = true)
bool bWinner = false; // Keeps track if the game is stalemated or not
bool bRestart = true; // Restarts the game if 'true'

bool bAI = false;
bool bFirstAI = true;
bool bPlayerFirstTime = false;

int corner;
int AIFirstPos;

void buildTable()
{
	system("cls");

	std::cout << "---------------" << std::endl;

	for (int i = 0; i < size; i++)
	{
		if (bFirstTime) // Makes the table with 1-9 indexes
			table[i] = i + 49;

		std::cout << "| " << table[i] << " |";
		if (i % 3 == 2) // Makes a new line when 'i % 3 = 2'
		{
			std::cout << std::endl;
			std::cout << "---------------" << std::endl;
		}
	}
	bFirstTime = false;
}

void insertAt(int index)
{
	if (table[index] != 'X' && table[index] != 'O') // Makes sure player can not put it's piece on invalid position
	{
		bContinue = false;

		// AI starts first, and uses 'X'
		if (bAI)
		{
			if (bPlayerOne)
				table[index] = 'O';
			else
				table[index] = 'X';
		}
		else
		{
			if (bPlayerOne)
				table[index] = 'X';
			else
				table[index] = 'O';
		}
	}
	else
		bContinue = true;
}

void input()
{
	while (true)
	{
		whichPlayer = int(!bPlayerOne); // Converts bool to int
		std::cout << "Player " << whichPlayer + 1 << "'s turn: "; // When whichPlayer = 1 it's Player one's turn, and opposite

		char chInput;
		std::cin >> chInput;
		int dInput = int(chInput); // Converts the character input to an integer

		if (dInput >= 49 && dInput <= 57) // Checks if the character input is from 1 to 9
		{
			insertAt(dInput - 49);
			break;
		}
		else
			buildTable(); // Asks player to input again if the input is outside the range
	}
}

int convertCorner(int corner)
{
	int piece = INT_MAX;
	switch (corner)
	{
	case 0:
		piece = 0;
		break;
	case 1:
		piece = 2;
		break;
	case 2:
		piece = 6;
		break;
	case 3:
		piece = 8;
		break;
	}

	return piece;
}

void inputAI()
{
	srand(time(0));

	int inputAI;
	while (true)
	{
		if (bPlayerOne)
		{
			input();
			break;
		}

		else
		{
			// Places AI's piece in one of the corners at the start
			if (bFirstAI)
			{
				corner = rand() % 4;
				AIFirstPos = corner;
				inputAI = convertCorner(corner);

				insertAt(6);
				bFirstAI = false;
				bPlayerFirstTime = true;
			}

			else
			{
				corner++;
				if (corner > 3)
					corner = 0;

				if (bPlayerFirstTime) // Checks if player's first piece is in the middle of the table
				{
					bPlayerFirstTime = false;

					if (table[4] == 'O') // Player's first piece is in the middle
					{
						// Places AI's second piece in opposite corner of AI's first piece
						if (AIFirstPos == 0)
							insertAt(8);
						else if (AIFirstPos == 1)
							insertAt(6);
						else if (AIFirstPos == 2)
							insertAt(2);
						else if (AIFirstPos == 3)
							insertAt(0);

						break;
					}
				}


				// 1. Checks if AI can win when placing the next piece
				for (int i = 0; i < size; i++)
				{
					// Horizontal check
					if (i % 3 == 0) // Checks if 'i' is index 0, 3 or 6 in table
					{
						if (table[i] == 'X' && table[i + 1] == 'X' && table[i + 2] <= 57)
						{
							insertAt(i + 2);
							return;
						}
						else if (table[i] <= 57 && table[i + 1] == 'X' && table[i + 2] == 'X')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'X' && table[i + 1] <= 57 && table[i + 2] == 'X')
						{
							insertAt(i + 1);
							return;
						}
					}

					// Vertical check
					if (i == 0 || i == 1 || i == 2) // Checks if 'i' is index 0, 1 or 2 in table
					{
						if (table[i] == 'X' && table[i + 3] == 'X' && table[i + 6] <= 57)
						{
							insertAt(i + 6);
							return;
						}
						else if (table[i] <= 57 && table[i + 3] == 'X' && table[i + 6] == 'X')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'X' && table[i + 3] <= 57 && table[i + 6] == 'X')
						{
							insertAt(i + 3);
							return;
						}
					}

					// Diagonal check
					if (i == 0) // Checks if 'i' is index 0 in table
					{
						if (table[i] == 'X' && table[i + 4] == 'X' && table[i + 8] <= 57)
						{
							insertAt(i + 8);
							return;
						}
						else if (table[i] <= 57 && table[i + 4] == 'X' && table[i + 8] == 'X')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'X' && table[i + 4] <= 57 && table[i + 8] == 'X')
						{
							insertAt(i + 4);
							return;
						}
					}
					if (i == 2) // Checks if 'i' is index 2 in table
					{
						if (table[i] == 'X' && table[i + 2] == 'X' && table[i + 4] <= 57)
						{
							insertAt(i + 4);
							return;
						}
						else if (table[i] <= 57 && table[i + 2] == 'X' && table[i + 4] == 'X')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'X' && table[i + 2] <= 57 && table[i + 4] == 'X')
						{
							insertAt(i + 2);
							return;
						}
					}
				}


				// 2. Checks if player is about to win
				for (int i = 0; i < size; i++)
				{
					// Horizontal check
					if (i % 3 == 0)
					{
						if (table[i] == 'O' && table[i + 1] == 'O' && table[i + 2] <= 57)
						{
							insertAt(i + 2);
							return;
						}
						else if (table[i] <= 57 && table[i + 1] == 'O' && table[i + 2] == 'O')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'O' && table[i + 1] <= 57 && table[i + 2] == 'O')
						{
							insertAt(i + 1);
							return;
						}
					}

					// Vertical check
					if (i == 0 || i == 1 || i == 2)
					{
						if (table[i] == 'O' && table[i + 3] == 'O' && table[i + 6] <= 57)
						{
							insertAt(i + 6);
							return;
						}
						else if (table[i] <= 57 && table[i + 3] == 'O' && table[i + 6] == 'O')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'O' && table[i + 3] <= 57 && table[i + 6] == 'O')
						{
							insertAt(i + 3);
							return;
						}
					}

					// Diagonal check
					if (i == 0)
					{
						if (table[i] == 'O' && table[i + 4] == 'O' && table[i + 8] <= 57)
						{
							insertAt(i + 8);
							return;
						}
						else if (table[i] <= 57 && table[i + 4] == 'O' && table[i + 8] == 'O')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'O' && table[i + 4] <= 57 && table[i + 8] == 'O')
						{
							insertAt(i + 4);
							return;
						}
					}

					if (i == 2)
					{
						if (table[i] == 'O' && table[i + 2] == 'O' && table[i + 4] <= 57)
						{
							insertAt(i + 4);
							return;
						}
						else if (table[i] <= 57 && table[i + 2] == 'O' && table[i + 4] == 'O')
						{
							insertAt(i);
							return;
						}
						else if (table[i] == 'O' && table[i + 2] <= 57 && table[i + 4] == 'O')
						{
							insertAt(i + 2);
							return;
						}
					}
				}


				// 3. Checks if there is a free slot between the current AI's corner piece and the next one
				for (int i = 0; i < size; i++)
				{
					// Horizontal check
					if (i % 3 == 0)
					{
						if (table[i] == 'X' && table[i + 1] <= 57 && table[i + 2] <= 57)
						{
							insertAt(i + 2);
							return;
						}
						else if (table[i] <= 57 && table[i + 1] <= 57 && table[i + 2] == 'X')
						{
							insertAt(i);
							return;
						}
					}

					// Vertical check
					if (i == 0 || i == 1 || i == 2)
					{
						if (table[i] == 'X' && table[i + 3] <= 57 && table[i + 6] <= 57)
						{
							insertAt(i + 6);
							return;
						}
						else if (table[i] <= 57 && table[i + 3] <= 57 && table[i + 6] == 'X')
						{
							insertAt(i);
							return;
						}
					}

					// Diagonal check
					if (i == 0)
					{
						if (table[i] == 'X' && table[i + 4] <= 57 && table[i + 8] <= 57)
						{
							insertAt(i + 8);
							return;
						}
						else if (table[i] <= 57 && table[i + 4] <= 57 && table[i + 8] == 'X')
						{
							insertAt(i);
							return;
						}
					}

					if (i == 2)
					{
						if (table[i] == 'X' && table[i + 2] <= 57 && table[i + 4] <= 57)
						{
							insertAt(i + 4);
							return;
						}
						else if (table[i] <= 57 && table[i + 2] <= 57 && table[i + 4] == 'X')
						{
							insertAt(i);
							return;
						}
					}
				}

				inputAI = convertCorner(corner);
				insertAt(inputAI);
				break;
			}

			break;
		}
	}
}

void checkWin()
{
	int staleMate = 0; // Used to check if the table does not include a number
	for (int i = 0; i < size; i++)
	{
		// Horizontal win
		if (i % 3 == 0) // Checks if 'i' is index 0, 3 or 6 in table
		{
			if (table[i] > 57 && table[i + 1] > 57 && table[i + 2] > 57)
			{
				if (table[i] == table[i + 1] && table[i + 1] == table[i + 2])
				{
					bEndGame = true;
					return;
				}
			}
		}

		// Vertical win
		if (i == 0 || i == 1 || i == 2) // Checks if 'i' is index 0, 1 or 2 in table
		{
			if (table[i] > 57 && table[i + 3] > 57 && table[i + 6] > 57)
			{
				if (table[i] == table[i + 3] && table[i + 3] == table[i + 6])
				{
					bEndGame = true;
					return;
				}
			}
		}

		// Diagonal wins
		if (i == 0) // Checks if 'i' is index 0 in table
		{
			if (table[i] > 57 && table[i + 4] > 57 && table[i + 8] > 57)
			{
				if (table[i] == table[i + 4] && table[i + 4] == table[i + 8])
				{
					bEndGame = true;
					return;
				}
			}
		}
		if (i == 2) // Checks if 'i' is index 2 in table
		{
			if (table[i] > 57 && table[i + 2] > 57 && table[i + 4] > 57)
			{
				if (table[i] == table[i + 2] && table[i + 2] == table[i + 4])
				{
					bEndGame = true;
					return;
				}
			}
		}

		// Stalemate check
		if (table[i] > 57)
			staleMate++;

		if (staleMate == 9)
		{
			bEndGame = true;
			bWinner = false;
		}
		else
			bWinner = true;
	}
}

void initValues()
{
	bPlayerOne = false;
	bFirstTime = true; 
	bEndGame = false; 
	bContinue = false; 
	bWinner = false; 
	bRestart = true; 

	bAI = false;
	bFirstAI = true;

	corner = INT_MAX;
}

int main()
{
	while (bRestart)
	{
		bRestart = false;

		while (true) // Asks which gamemode player would like to play
		{
			system("cls");

			std::cout << "****** WELCOME TO TIC TAC TOE ******" << std::endl << std::endl;

			char inputAI;
			std::cout << "Choose gamemode:" << std::endl
				<< "1. Multiplayer" << std::endl
				<< "2. Against unbeatable AI (AI starts first)" << std::endl
				<< std::endl << "Input your answer: ";
			std::cin >> inputAI;

			if (inputAI == '1')
			{
				bAI = false;
				break;
			}
			else if (inputAI == '2')
			{
				bAI = true;
				bPlayerOne = true;
				break;
			}
		}

		while (!bEndGame) // Repeats the game
		{
			if (!bContinue)
				bPlayerOne = !bPlayerOne; // Flips the Player one bool, changing who's turn it is

			buildTable();

			if (!bAI)
				input();
			else
				inputAI();

			checkWin();
		}

		while (true)
		{
			buildTable();
			whichPlayer = int(!bPlayerOne); // Converts bool to int

			if (bWinner)
			{
				if (bAI)
				{
					if (!bPlayerOne)
						std::cout << "The Unbeatable AI won the game!" << std::endl;
					else
						std::cout << "Player " << whichPlayer + 1 << " won the game!" << std::endl;
				}
				else
					std::cout << "Player " << whichPlayer + 1 << " won the game!" << std::endl;
			}
			else
				std::cout << "Game came to a stalemate!" << std::endl;


			char restart;
			std::cout << std::endl << "Would you like to play again? (y/n): "; 
			std::cin >> restart;

			if (restart == 'y' || restart == 'Y')
			{
				bRestart = true;
				initValues();
				break;
			}
			else if (restart == 'n' || restart == 'N')
			{
				bRestart = false;
				break;
			}
		}
	}

	return 0;
}