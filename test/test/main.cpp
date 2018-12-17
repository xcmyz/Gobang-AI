#include "head.h"
#include "AI.h"

using namespace std;

int main()
{
	//Initial
	FILE* Temp;
	Temp = fopen("play_chess.txt", "wb+");
	fclose(Temp);
	string file_name = "play_chess.txt";


	//Define a board
	BN board[HandL][HandL];
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			board[i][j].value = 0;
			board[i][j].order = 0;
		}
	}

	//Define a board for cursor
	int Board_Cursor[HandL][HandL];
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			Board_Cursor[i][j] = 0;
			if ((i == (HandL - 1) / 2) && j == ((HandL - 1) / 2))
			{
				Board_Cursor[i][j] = 8;
			}
		}
	}

	//Define player
	int Human;
	int AI;

	//Define cursor
	int X = (HandL - 1) / 2;
	int Y = (HandL - 1) / 2;

	//Choose mode
	int mode;
	cin >> mode;

	//Start
	if (mode == 1) {
		//Clear all screen
		system("cls");

		//Let player choose first or latter
		cin >> Human;
		getchar();
		AI = (Human == 1) ? 2 : 1;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor), file_name);

		//Initialize player
		int Current_Player = 1;

		//Initialize AI
		AI_Class levi(AI, (*board));

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == AI)
			{
				Board_Cursor[Y][X] = 0;
				//AI first
				levi.decision((*board), Y, X);
				//cout << "Done";
				//Board_Cursor[X][Y] = 8;
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "AI win !" << endl;
					break;
				}
				Current_Player = Human;

				//Human
				while (true)
				{
					char key = _getch();
					int a = -1;
					if (Player_Operation(key, X, Y, Current_Player, (*board), (*Board_Cursor), a))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						//board[Y][X].order = Find_Biggest((*board)) + 1;
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Human win !" << endl;
					break;
				}
				Current_Player = AI;
			}
			else
			{
				//Human first
				while (true)
				{
					char key = _getch();
					int a = -1;
					if (Player_Operation(key, X, Y, Current_Player, (*board), (*Board_Cursor), a))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						//board[Y][X].order = Find_Biggest((*board)) + 1;
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Human win !" << endl;
					break;
				}
				Current_Player = AI;

				Board_Cursor[Y][X] = 0;
				//AI latter
				levi.decision((*board), Y, X);
				//cout << "Done";
				//Board_Cursor[X][Y] = 8;
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "AI win !" << endl;
					break;
				}
				Current_Player = Human;
			}
		}
	}
	else if (mode == 2) {

		int Human_1 = 1;
		int Human_2 = 2;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor), file_name);

		int Current_Player = 1;

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == Human_1)
			{
				while (true)
				{
					char key = _getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_2;

				while (true)
				{
					char key = _getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_1;
			}
			else
			{
				while (true)
				{
					char key = _getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_1;

				//AI latter
				while (true)
				{
					char key = _getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name);
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor), file_name, true);
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_2;
			}
		}
	}
	else if (mode == 3) {
		int AI1 = 1;
		int AI2 = 2;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor), file_name);

		//Initialize player
		int Current_Player = AI1;

		//Initialize AI
		AI_Class AI_1(AI1, (*board));
		AI_Class AI_2(AI2, (*board));

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == AI1)
			{
				Board_Cursor[Y][X] = 0;
				AI_1.decision((*board), Y, X);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI2;

				Board_Cursor[Y][X] = 0;
				AI_2.decision((*board), Y, X);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI1;
			}
			else
			{
				Board_Cursor[X][Y] = 0;
				AI_2.decision((*board), X, Y);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI1;

				Board_Cursor[X][Y] = 0;
				AI_1.decision((*board), X, Y);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor), file_name, true);
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI2;
			}
		}
	}

	system("pause");
	return 0;
}