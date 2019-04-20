#define _CRT_SECURE_NO_WARNINGS
#define HandL 15
#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;

const char* folder_1 = "folder_1";
const char* folder_2 = "folder_2";
const char* folder = "folder";
const char* board_1 = "folder_1/board_1.json";
const char* board_2 = "folder_2/board_2.json";
const char* coor_1 = "folder_1/coor_1.txt";
const char* coor_2 = "folder_2/coor_2.txt";

struct coor {
	int x;
	int y;
	int order;
};
typedef coor coor;

struct Board_Node
{
	int value;
	int order;
};
typedef Board_Node BN;

int order_max = 1;

vector<coor> orders;

void print_print() {
	FILE* Temp;
	Temp = fopen("play_chess.json", "wb+");
	fclose(Temp);

	int len = orders.size();
	ofstream location_out;
	location_out.open("play_chess.json", std::ios::out | std::ios::app);
	location_out << "[" << endl;
	for (int i = 0; i < len; i++)
	{
		int h = orders[i].x;
		int l = orders[i].y;
		location_out << "{" << "\"" << i + 1 << "\"" << ":";
		if (i == len - 1) {
			location_out << "\"" << h << " " << l << "\"" << "}" << endl;
		}
		else {
			location_out << "\"" << h << " " << l << "\"" << "}" << "," << endl;
		}
	}
	location_out << "]";
	location_out.close();
}

void print_board(const char* board_file) {
	if (!orders.size()) {
		FILE* board1;
		board1 = fopen(board_1, "wb+");
		fclose(board1);
		return;
	}

	FILE* Temp;
	Temp = fopen(board_file, "wb+");
	fclose(Temp);

	Temp = fopen("play_chess.json", "wb+");
	fclose(Temp);

	int len = orders.size();
	ofstream location_out;
	location_out.open("play_chess.json", std::ios::out | std::ios::app);
	location_out << "[" << endl;
	for (int i = 0; i < len; i++)
	{
		int h = orders[i].x;
		int l = orders[i].y;
		location_out << "{" << "\"" << i + 1 << "\"" << ":";
		if (i == len - 1) {
			location_out << "\"" << h << " " << l << "\"" << "}" << endl;
		}
		else {
			location_out << "\"" << h << " " << l << "\"" << "}" << "," << endl;
		}
	}
	location_out << "]";
	location_out.close();

	len = orders.size();
	location_out.open(board_file, std::ios::out | std::ios::app);
	location_out << "[" << endl;
	for (int i = 0; i < len; i++)
	{
		int h = orders[i].x;
		int l = orders[i].y;
		location_out << "{" << "\"" << i + 1 << "\"" << ":";
		if (i == len - 1) {
			location_out << "\"" << h << " " << l << "\"" << "}" << endl;
		}
		else {
			location_out << "\"" << h << " " << l << "\"" << "}" << "," << endl;
		}
	}
	location_out << "]";
	location_out.close();
}

bool _judge(BN* board, int X, int Y)
{
	//Chinese
	int shu = 1, heng = 1, pie = 1, na = 1;

	//Up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Left
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)* HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Right
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)* HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Left down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			na++;
		else
			break;
	}

	//Left up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			na++;
		else
			break;
	}

	int ifbreak = false;
	if (shu >= 5 || heng >= 5 || pie >= 5 || na >= 5)
	{
		ifbreak = true;
	}
	if (ifbreak)
		return true;
	else
		return false;
}

int judge() {
	//-1: error, 0: continue, 1: win

	//检测落子是否有重复
	for (int i = 0; i < orders.size(); i++) {
		for (int j = i + 1; j < orders.size(); j++) {
			if ((orders[i].x == orders[j].x) && (orders[i].y == orders[j].y)) {
				cout << "落子重复啦！" << endl;
				return -1;
			}
		}
	}

	//禁手
	if (orders.size() <= 3) {
		if (orders.size() == 1) {
			if (orders[0].x != 7 || orders[0].y != 7) {
				cout << "第一个落子不在天元！" << endl;
				return -1;
			}
		}

		if (orders.size() == 3) {
			if (orders[2].x <= 9 && orders[2].x >= 5 && orders[2].y <= 9 && orders[2].y >= 5) {
				cout << "第三子不符合禁手规则！" << endl;
				return -1;
			}
		}
	}

	BN board[HandL][HandL];
	for (int x = 0; x < HandL; x++) {
		for (int y = 0; y < HandL; y++) {
			board[x][y].value = 0;
			board[x][y].order = 0;
		}
	}
	for (int i = 0; i < orders.size(); i++) {
		board[orders[i].x][orders[i].y].value = (orders[i].order % 2) ? 1 : 2;
		board[orders[i].x][orders[i].y].order = orders[i].order;
	}
	bool symbol = false;
	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			if (_judge(*board, i, j)) {
				symbol = true;
				break;
			}
		}
	}

	if (symbol) {
		return true;
	}
	else {
		return false;
	}
}

void init() {
	CreateDirectory(folder_1, NULL);
	CreateDirectory(folder_2, NULL);
	CreateDirectory(folder, NULL);
}

int step_2() {
	print_board(board_1);
	//cout << "#########" << endl;

	while (true) {
		ifstream fin(coor_1);
		if (fin) {
			break;
		}
	}

	fstream coor_1_file;
	vector<char> t;
	int x, y;
	char c;
	coor_1_file.open(coor_1, ios::in);
	while (!coor_1_file.eof()) {
		coor_1_file >> c;
		t.push_back(c);
	}
	x = t[0] - 48;
	y = t[1] - 48;
	cout << x << " " << y << endl;
	coor_1_file.close();

	remove(coor_1);

	coor c_temp;
	c_temp.order = order_max;
	order_max = order_max + 1;
	c_temp.x = x;
	c_temp.y = y;
	orders.push_back(c_temp);

	for (int i = 0; i < orders.size(); i++) {
		cout << "x: " << orders[i].x << "; y: " << orders[i].y << "; order: " << orders[i].order << endl;
	}

	int out = judge();
	return out;
}

int step_4() {
	print_board(board_2);

	while (true) {
		ifstream fin(coor_2);
		if (fin) {
			break;
		}
	}

	fstream coor_2_file;
	vector<char> t;
	int x, y;
	char c;
	coor_2_file.open(coor_2, ios::in);
	while (!coor_2_file.eof()) {
		coor_2_file >> c;
		t.push_back(c);
	}
	x = t[0] - 48;
	y = t[1] - 48;
	coor_2_file.close();

	remove(coor_2);

	coor c_temp;
	c_temp.order = order_max;
	order_max = order_max + 1;
	c_temp.x = x;
	c_temp.y = y;
	orders.push_back(c_temp);

	for (int i = 0; i < orders.size(); i++) {
		cout << "x: " << orders[i].x << "; y: " << orders[i].y << "; order: " << orders[i].order << endl;
	}

	int out = judge();
	return out;
}


int main() {
	init();
	int winner;
	while (true) {
		int result_1 = step_2();
		cout << result_1 << endl;
		if (result_1) {
			winner = result_1;
			break;
		}
		int result_2 = step_4();
		if (result_2) {
			winner = result_2;
			break;
		}
	}
	print_print();
	cout << winner << endl;
	return 0;
}