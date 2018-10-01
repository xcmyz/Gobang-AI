#include "head.h"
#include "AI_Class.h"

using namespace std;

int main()
{
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

	//Let player choose first or latter
	cin >> Human;
	getchar();
	AI = (Human == 1) ? 2 : 1;

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
			/*while (true)
			{
				char key = getch();
				if (Player_Operation(key, X, Y, Current_Player, \
					(*board), (*Board_Cursor), Round_Number))
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
				}
				else
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
					break;
				}
			}
			if (judge((*board), X, Y, Current_Player))
			{
				cout << "AI win !" << endl;
				break;
			}
			Current_Player = Human;*/


			//AI first
			levi.decision((*board), X, Y);
			Print_Board((*board), (*Board_Cursor));
			if (judge((*board), X, Y, Current_Player))
			{
				cout << "AI win !" << endl;
				break;
			}
			Current_Player = Human;

			//Human
			while (true)
			{
				char key = getch();
				if (Player_Operation(key, X, Y, Current_Player, \
					(*board), (*Board_Cursor), Round_Number))
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
				}
				else
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
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
				char key = getch();
				if (Player_Operation(key, X, Y, Current_Player, \
					(*board), (*Board_Cursor), Round_Number))
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
				}
				else
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
					break;
				}
			}
			if (judge((*board), X, Y, Current_Player))
			{
				cout << "Human win !" << endl;
				break;
			}
			Current_Player = AI;

			//AI latter
			levi.decision((*board), X, Y);
			Print_Board((*board), (*Board_Cursor));
			if (judge((*board), X, Y, Current_Player))
			{
				cout << "AI win !" << endl;
				break;
			}
			Current_Player = Human;

			/*while (true)
			{
				char key = getch();
				if (Player_Operation(key, X, Y, Current_Player, \
					(*board), (*Board_Cursor), Round_Number))
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
				}
				else
				{
					system("cls");
					Print_Board((*board), (*Board_Cursor));
					break;
				}
			}
			if (judge((*board), X, Y, Current_Player))
			{
				cout << "AI win !" << endl;
				break;
			}
			Current_Player = Human;*/
		}
	}

	system("pause");
	return 0;
}
