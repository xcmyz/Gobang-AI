#include<iostream>
#include<string> 
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include<windows.h> 
#include<conio.h>
//#include<ctime>
//#include<cstdlib>
//#define MAXN 1010

//Board size
#define HandL 15

//Hyperparameter
#define HYP_wight 0.5
//#define HYP_kase 3

//Offensive and Defensive for first
#define OFF_1 1
#define DEF_1 1

//Offensive and Defensive for second
#define OFF_2 1
#define DEF_2 1

//Define score
//Huo means two sides have nothing
#define ChengWu  100000
#define HuoSi  10000
#define HuoSan 1000
#define HuoEr  100
#define HuoYi 10
//Si means one sides have a chess piece
#define SiSi 1000
#define SiSan 100
#define SiEr 10

//Store grade
struct Grade {
	int grade;
	int h;
	int l;
};
typedef struct Grade Grade;

//For Attention
struct Attention {
	int h_min;
	int l_min;
	int h_max;
	int l_max;
};
typedef struct Attention Attention;

//Define a player, when equal to 1 is white hand, else is black hand
int player = 1;

//Human is for people, AI is for computer
int human;
int AI;

//board one
//Declare an array of 19 rows and 19 columns to store the board one 
int board_1[HandL][HandL];

//board two
//Declare an array of 19 rows and 19 columns to store the board two
int board_2[HandL][HandL];

//Value of position
int ValueofPosition[HandL][HandL];

//Define cursor
int X = (HandL - 1) / 2;
int Y = (HandL - 1) / 2;

using namespace std;

void print();
void initialization();
bool PlayerOperation(char key);
bool judge(int ifPVP);

//Quick sort written by hands
int partition(vector<Grade> &arr, int p, int r) {
	Grade x = arr[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (arr[j].grade <= x.grade) {
			i += 1;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[r]);
	return i + 1;
}
//recursion
void QuickSort(vector<Grade> &arr, int p, int r) {
	if (p < r) {
		int q = partition(arr, p, r);
		QuickSort(arr, p, q - 1);
		QuickSort(arr, q + 1, r);
	}
}

inline void delay(int Default = 1000) {
	for (int i = 0; i < 20 * Default; i++) {
		for (int j = 0; j < 1000; j++) {}
	}
}

void display(string sentence) {
	int size = sentence.size();
	for (int i = 0; i < size; i++) {
		delay();
		cout << sentence[i];
	}
	cout << endl;
}

//The most important
void Levi(int AI);

int CountGrade(int Player, bool ifPredict = false);
void MatchBoard(vector<int>tempArr, int Player, int &score, bool ifPredict);

Attention attention() {
	static Attention tempAttention;
	tempAttention.h_max = (HandL + 1) / 2 - 1;
	tempAttention.h_min = (HandL + 1) / 2 - 1;
	tempAttention.l_max = (HandL + 1) / 2 - 1;
	tempAttention.l_min = (HandL + 1) / 2 - 1;
	for (int x = 0; x < HandL; x++) {
		for (int y = 0; y < HandL; y++) {
			if (board_2[x][y] != 0) {
				if (x < tempAttention.h_min)
					tempAttention.h_min = x;
				if (y < tempAttention.l_min)
					tempAttention.l_min = y;
				if (x > tempAttention.h_max)
					tempAttention.h_max = x;
				if (y > tempAttention.l_max)
					tempAttention.l_max = y;
			}
		}
	}
	if (tempAttention.h_min != 0)
		tempAttention.h_min = tempAttention.h_min - 2;
	if (tempAttention.h_max != 15)
		tempAttention.h_max = tempAttention.h_max + 2;
	if (tempAttention.l_min != 0)
		tempAttention.l_min = tempAttention.l_min - 2;
	if (tempAttention.l_max != 15)
		tempAttention.l_max = tempAttention.l_max + 2;

	return tempAttention;
}

void print() {
	//Print
	for (int h = 0; h < HandL; h++) {
		for (int l = 0; l < HandL; l++) {
			if (board_1[h][l] == 8) {
				//Changed over there
				cout << "�� ";
			}
			else if (board_2[h][l] == 0) {
				cout << "��";
			}
			else if (board_2[h][l] == 1) {
				cout << "��";
			}
			else if (board_2[h][l] == 2) {
				cout << "��";
			}
		}
		cout << endl;
		//cout << CountGrade() << endl;
	}
}

//initialization
void initialization() {
	//Assigning weights to positions
	for (int i = 0; i <= (HandL - 1) / 2; i++) {
		for (int x = i; x < HandL - i; x++) {
			ValueofPosition[i][x] = i;
			ValueofPosition[x][i] = i;
			ValueofPosition[HandL - 1 - i][x] = i;
			ValueofPosition[x][HandL - 1 - i] = i;
		}
	}

	//All elements are initializel(assigned), defaults to 0 values 
	for (int h = 0; h < HandL; h++) {
		for (int l = 0; l < HandL; l++) {
			//Defaults to 0 values
			board_1[h][l] = 0;
		}
	}

	//All elements are initializel(assigned), defaults to 0 values
	for (int h = 0; h < HandL; h++) {
		for (int l = 0; l < HandL; l++) {
			//Defaults to 0 values
			board_2[h][l] = 0;
		}
	}

	//Declare and initialize the horizontal and longitudinal coordinate of the cursor
	board_1[(HandL - 1) / 2][(HandL - 1) / 2] = 8;

	//Display
	for (int h = 0; h < HandL; h++) {
		for (int l = 0; l < HandL; l++) {
			if (board_1[h][l] == 8) {
				//Changed over there
				cout << "�� ";
			}
			else if (board_2[h][l] == 0) {
				cout << "��";
			}
			else if (board_2[h][l] == 1) {
				cout << "��";
			}
			else if (board_2[h][l] == 2) {
				cout << "��";
			}
		}
		cout << endl;
	}
}

bool PlayerOperation(char key) {
	int ifcontinue = 1;
	//Control
	switch (key) {
		//Operation
		//Up
	case 0x48:
		//Let longitudinal coordinate of corsor cut one
		if (Y > 0 && Y <= HandL - 1)
			Y = Y - 1;
		//Write corsor into board
		board_1[Y][X] = 8;
		//Restore the value of the original location 
		board_1[Y + 1][X] = 0;
		break;

		//Down
	case 0x50:
		if (Y >= 0 && Y < HandL - 1)
			Y = Y + 1;
		board_1[Y][X] = 8;
		board_1[Y - 1][X] = 0;
		break;

		//Left
	case 0x4B:
		if (X > 0 && X <= HandL - 1)
			X = X - 1;
		board_1[Y][X] = 8;
		board_1[Y][X + 1] = 0;
		break;

		//Right
	case 0x4D:
		if (X >= 0 && X < HandL - 1)
			X = X + 1;
		board_1[Y][X] = 8;
		board_1[Y][X - 1] = 0;
		break;

		//Chess moves
	case ' ':
		//Prevent to move in the same place again
		if (board_2[Y][X] == 0) {
			//When player is white hand
			if (player == 1) {
				//White hand moves
				board_2[Y][X] = 1;
				//After white hand moves, change player
				player = 2;
			}
			//When player is black hand
			else if (player == 2) {
				board_2[Y][X] = 2;
				player = 1;
			}
			ifcontinue = 0;
		}
		break;
	}
	if (ifcontinue)
		return 1;
	else
		return 0;
}

bool judge(int ifPVP) {
	//Chinese
	int shu = 1, heng = 1, pie = 1, na = 1;

	//Up
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y + i][X] == board_2[Y][X] && board_2[Y][X] != 0)
			shu++;
		else
			break;
	}

	//Down
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y - i][X] == board_2[Y][X] && board_2[Y][X] != 0)
			shu++;
		else
			break;
	}

	//Left
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y][X - i] == board_2[Y][X] && board_2[Y][X] != 0)
			heng++;
		else
			break;
	}

	//Right
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y][X + i] == board_2[Y][X] && board_2[Y][X] != 0)
			heng++;
		else
			break;
	}

	//Left down
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y + i][X - i] == board_2[Y][X] && board_2[Y][X] != 0)
			pie++;
		else
			break;
	}

	//Right up
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y - i][X + i] == board_2[Y][X] && board_2[Y][X] != 0)
			pie++;
		else
			break;
	}

	//Right down
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y + i][X + i] == board_2[Y][X] && board_2[Y][X] != 0)
			na++;
		else
			break;
	}

	//Left up
	for (int i = 1; i <= 4; i++) {
		if (board_2[Y - i][X - i] == board_2[Y][X] && board_2[Y][X] != 0)
			na++;
		else
			break;
	}

	int ifbreak = 0;
	if (ifPVP == 2) {
		if (shu == 5 || heng == 5 || pie == 5 || na == 5) {
			if (board_2[Y][X] == 1) {
				cout << "White hand win!";
				cout << endl;
				system("pause");
				ifbreak = 1;
			}
			else {
				cout << "Black hand win!";
				cout << endl;
				system("pause");
				ifbreak = 1;
			}
		}
	}
	else {
		if (shu == 5 || heng == 5 || pie == 5 || na == 5) {
			if (board_2[Y][X] == human) {
				cout << "You win!";
				cout << endl;
				system("pause");
				ifbreak = 1;
			}
			else {
				cout << "Levi wins!";
				cout << endl;
				system("pause");
				ifbreak = 1;
			}
		}
	}
	if (ifbreak)
		return 1;
	else
		return 0;
}

//The most important
//Iterate twice
//before I am shabi le
void Levi(int AI) {
	////Store grade
	//struct Grade {
	//	int grade;
	//	int h;
	//	int l;
	//};
	//typedef struct Grade Grade;

	//An array for storing grade
	//int kase = 0;
	vector<Grade>ArrForGrade;

	//Operation
	int before_grade_AI = CountGrade(AI);
	int before_grade_human = CountGrade(human);
	//Traversing an array
	Attention tempAttention_1 = attention();
	for (int h = tempAttention_1.h_min; h < tempAttention_1.h_max; h++) {
		for (int l = tempAttention_1.l_min; l < tempAttention_1.l_max; l++) {
			if (board_2[h][l] == 0) {
				board_2[h][l] = AI;
				int now_grade_AI = CountGrade(AI, 1);
				int now_grade_human = CountGrade(human, 1);
				//Increase
				int temp_AI = now_grade_AI - before_grade_AI;
				//Decrease
				int temp_human = before_grade_human - now_grade_human;
				int score_first = OFF_1 * temp_AI + DEF_1 * temp_human;
				//An operation
				int temp = score_first + ValueofPosition[h][l];

				//int temp = CountGrade(AI);
				/*ArrForGrade[kase].grade = temp;
				ArrForGrade[kase].h = h;
				ArrForGrade[kase].l = l;*/
				Grade tempGrade;
				tempGrade.grade = temp;
				tempGrade.h = h;
				tempGrade.l = l;
				ArrForGrade.push_back(tempGrade);
				//kase++;
				//Recurrence
				board_2[h][l] = 0;
			}
		}
	}

	//sort
	QuickSort(ArrForGrade, 0, ArrForGrade.size() - 1);

	//The second iteration
	/*int TempMaxGrade = ArrForGrade[ArrForGrade.size() - 1].grade;
	int StoNum = 0;
	for (int i = ArrForGrade.size() - 1;; i--) {
		if (ArrForGrade[i].grade == TempMaxGrade)
			StoNum++;
		else
			break;
	}*/
	//Elimination
	set<int>TempSet;
	TempSet.clear();
	for (int i = ArrForGrade.size() - 1; i >= 0; i--) {
		//Define kase
		/*if (TempSet.size() == HYP_kase)
			break;
		else
			TempSet.insert(ArrForGrade[i].grade);*/
		TempSet.insert(ArrForGrade[i].grade);
	}

	vector<Grade>StoForTwice;
	StoForTwice.clear();
	set<int>::iterator it;
	for (it = TempSet.begin(); it != TempSet.end(); it++) {
		for (int i = ArrForGrade.size() - 1; i >= 0; i--) {
			if (*it == ArrForGrade[i].grade) {
				StoForTwice.push_back(ArrForGrade[i]);
				break;
			}
		}
	}

	//Find the min from the max
	vector<Grade>StoForFinalGrade;
	StoForFinalGrade.clear();
	//Levi again
	for (int x = 0; x < StoForTwice.size(); x++) {
		//An array for storing grade
		vector<Grade>ArrForGrade_twice;

		//initialization
		board_2[StoForTwice[x].h][StoForTwice[x].l] = AI;

		//Operation for player
		int before_grade_human_2 = CountGrade(human);
		int before_grade_AI_2 = CountGrade(AI);
		//Traversing an array
		Attention tempAttention_2 = attention();
		for (int h = tempAttention_2.h_min; h < tempAttention_2.h_max; h++) {
			for (int l = tempAttention_2.l_min; l < tempAttention_2.l_max; l++) {
				if (board_2[h][l] == 0) {
					board_2[h][l] = human;
					int now_grade_human_2 = CountGrade(human, 1);
					int now_grade_AI_2 = CountGrade(AI, 1);
					//Increase
					int temp_human_2 = now_grade_human_2 - before_grade_human_2;
					//Decrease
					int temp_AI_2 = before_grade_AI_2 - now_grade_AI_2;
					int score_twice = OFF_2 * temp_human_2 + DEF_2 * temp_AI_2;
					//An operation
					int temp_twice = score_twice;
					Grade tempGrade;
					tempGrade.grade = temp_twice;
					tempGrade.h = h;
					tempGrade.l = l;
					ArrForGrade_twice.push_back(tempGrade);
					//kase++;
					//Recurrence
					board_2[h][l] = 0;
				}
			}
		}

		//sort
		QuickSort(ArrForGrade_twice, 0, ArrForGrade_twice.size() - 1);

		//Get max and get the final grade
		int MaxGrade = ArrForGrade_twice[ArrForGrade_twice.size() - 1].grade;
		StoForTwice[x].grade = StoForTwice[x].grade - HYP_wight * MaxGrade;
		StoForFinalGrade.push_back(StoForTwice[x]);


		//Recurrence
		board_2[StoForTwice[x].h][StoForTwice[x].l] = 0;
	}

	//Get the best
	int MaxGrade = StoForFinalGrade[0].grade;
	int Max_h = StoForFinalGrade[0].h;
	int Max_l = StoForFinalGrade[0].l;

	for (int i = 1; i < StoForFinalGrade.size(); i++) {
		int old = MaxGrade;
		MaxGrade = max(MaxGrade, StoForFinalGrade[i].grade);
		if (old != MaxGrade) {
			Max_h = StoForFinalGrade[i].h;
			Max_l = StoForFinalGrade[i].l;
		}
	}

	//Chess moves
	board_2[Max_h][Max_l] = AI;

	//Upgrade cursor
	board_1[Y][X] = 0;
	Y = Max_h;
	X = Max_l;

	//Players exchange
	player = 3 - AI;
}

int CountGrade(int Player, bool ifPredict) {
	//Temp score
	int score_human = 0;
	int score_AI = 0;

	//Search the board
	//Horizontal
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_1;
		for (int j = 0; j < HandL; j++) {
			tempArr_1.push_back(board_2[i][j]);
		}
		if (Player == AI)
			MatchBoard(tempArr_1, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_1, human, score_human, ifPredict);
	}
	//Vertical
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_2;
		for (int j = 0; j < HandL; j++) {
			tempArr_2.push_back(board_2[j][i]);
		}
		if (Player == AI)
			MatchBoard(tempArr_2, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_2, human, score_human, ifPredict);
	}

	//Left oblique
	//Upper Half part
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_3_1;
		for (int j = HandL; j >= i; j--) {
			tempArr_3_1.push_back(board_2[HandL - j][HandL - j + i]);
		}
		if (Player == AI)
			MatchBoard(tempArr_3_1, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_3_1, human, score_human, ifPredict);
	}
	//Lower half part
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_3_2;
		for (int j = HandL; j >= i; j--) {
			tempArr_3_2.push_back(board_2[HandL - j + i][HandL - j]);
		}
		if (Player == AI)
			MatchBoard(tempArr_3_2, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_3_2, human, score_human, ifPredict);
	}
	//Right oblique
	//Upper Half part
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_4_1;
		for (int j = 0; j <= i; j++) {
			tempArr_4_1.push_back(board_2[j][i - j]);
		}
		if (Player == AI)
			MatchBoard(tempArr_4_1, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_4_1, human, score_human, ifPredict);
	}
	//Lower half part
	for (int i = 0; i < HandL; i++) {
		vector<int>tempArr_4_2;
		for (int j = 0; j <= HandL - 1 - i; j++) {
			tempArr_4_2.push_back(board_2[i + j][HandL - 1 - j]);
		}
		if (Player == AI)
			MatchBoard(tempArr_4_2, AI, score_AI, ifPredict);
		else
			MatchBoard(tempArr_4_2, human, score_human, ifPredict);
	}

	//Get score
	if (Player == AI)
		return score_AI;
	else
		return score_human;
}

void MatchBoard(vector<int>tempArr, int Player, int &score, bool ifPredict) {
	//Get size
	int size = tempArr.size();
	for (int i = 0; i < size;) {
		if (tempArr[i] == Player) {
			int kase = 0;
			int end;
			for (int x = i; x < size; x++) {
				if (tempArr[x] == Player) {
					kase++;
					end = x;
				}
				else {
					end = x - 1;
					break;
				}
			}
			//0 for neither; 1 for one side; 2 for both sides
			int iflive = 0;
			//Front
			if (i == 0)
				iflive++;
			else {
				if (tempArr[i - 1] == 3 - Player)
					iflive++;
				else if (tempArr[i - 1] == Player)
					printf("There are some errors in the Levi. \n");
			}
			//Tail
			if (end == size - 1)
				iflive++;
			else {
				if (tempArr[end + 1] == 3 - Player)
					iflive++;
				else if (tempArr[end + 1] == Player)
					printf("There are some errors in the Levi. \n");
			}
			//Add score
			if (iflive == 2) {
				//forbid 0 11110
				//???
				if ((kase == 5) && (ifPredict == true)) {
					score += ChengWu;
				}
			}
			else if (iflive == 1) {
				switch (kase) {
					//Fuck Fuck Fuck
				case 5:
					score += ChengWu;
					break;
				case 4:
					score += SiSi;
					break;
				case 3:
					score += SiSan;
					break;
				case 2:
					score += SiEr;
					break;
				default:
					break;
				}
			}
			else {
				switch (kase) {
				case 5:
					score += ChengWu;
					break;
				case 4:
					score += HuoSi;
					break;
				case 3:
					score += HuoSan;
					break;
				case 2:
					score += HuoEr;
					break;
				case 1:
					score += HuoYi;
					break;
				default:
					break;
				}
			}
			//Operation of i
			i = end + 1;
		}
		else
			i++;
	}
}

int main() {
	//Main

	//Display
	system("title Gobang");
	system("mode con cols=30 lines=16");
	system("color E0");

	//Introduce operation
	string FirstSen = "Hi, I'm Levi. ";
	string SecondSen = "I'm happy to see you come here. ";
	string ThirdSen = "Let me introduce the operation of the game. ";
	string FourthSen = "W is for up; A is for left; D is for right. S is for down. ";
	string FifthSen = "Space is for chess moving. ";
	display(FirstSen);
	display(SecondSen);
	display(ThirdSen);
	display(FourthSen);
	display(FifthSen);
	delay(10000);
	system("pause");

	//Clear screen operation   
	system("cls");

	//Let player choose either PVP or fight with AI
	string Sen_1 = "What would you like to play with ?";
	display(Sen_1);
	string Sen_2 = "If you want to play with me, please enter 1. ";
	display(Sen_2);
	string Sen_3 = "If you like PVP, please enter 2. ";
	display(Sen_3);
	delay(10000);
	cout << "enter : ";
	int choose_2;
	scanf("%d", &choose_2);
	if (choose_2 != 1 && choose_2 != 2) {
		printf("ERROR\n");
		system("pause");
		return 0;
	}

	//Clear screen operation   
	system("cls");

	//Let player choose first or latter
	if (choose_2 == 1) {
		cout << "Choose first or later. 1 is for first, 2 is for latter : ";
		getchar();
		int choose_1;
		scanf("%d", &choose_1);
		if (choose_1 == 1) {
			human = 1;
			AI = 2;
		}
		else if (choose_1 == 2) {
			human = 2;
			AI = 1;
		}
		else {
			printf("ERROR!\n");
			system("pause");
			return 0;
		}

		//Clear screen operation   
		system("cls");
	}

	//Initialization
	initialization();

	//Input control
	while (true) {
		//Console gets a character from the keyboard 
		if (human == player) {
			while (true) {
				char key = getch();
				if (!(PlayerOperation(key))) {
					//Clear screen operation   
					system("cls");
					//Print
					print();
					break;
				}
				else {
					//Clear screen operation   
					system("cls");
					//Print
					print();
				}
			}
		}
		else {
			while (true) {
				if (choose_2 == 2) {
					char key = getch();
					if (!(PlayerOperation(key))) {
						//Clear screen operation   
						system("cls");
						//Print
						print();
						break;
					}
					else {
						//Clear screen operation   
						system("cls");
						//Print
						print();
					}
				}
				else {
					Levi(AI);
					//Clear screen operation   
					system("cls");
					//Print
					print();
					break;
				}
			}
		}

		//Law of game
		if (judge(choose_2))
			break;
	}

	return 0;
}
