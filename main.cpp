#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

//____field____
const short weight{ 20 };
const short height{ 10 };
//____snake____
const short max_size_snake{ weight * height - weight * 2 - (height - 2) * 2 };
short size_snake{ 1 };
//snake head position
short x{ weight/2 };
short y{ height/2 };
int position_body[max_size_snake][2]{ {x,y} };
//direction 
short state{};//up-1 down-2 left-3 right-4
//____apple____
short x_apple{};
short y_apple{};
//____state game____
bool game_over{ false };
//____function____
void render(char field[height][weight + 1], float);
void update(char field[height][weight + 1]);

int main() {
	float speed{ 0 };
	srand(time(NULL));

	char field[height][weight+1]{
		"####################",
		"#                  #",
		"#                  #",
		"#                  #",
		"#                  #",
		"#                  #",
		"#                  #",
		"#                  #",
		"#                  #",
		"####################"
	};
	render(field, speed);
	while (game_over != true) {
		speed = 503 - (3*size_snake);
		Sleep(speed);
		if (_kbhit()) {
			switch (_getch()) {
				//up
			case 27:
				game_over = true;
			case 32:
				state = 5;
				update(field);
				break;
			case 72:
				state = 1;
				update(field);
				break;
				//left
			case 75:
				state = 3;
				update(field);
				break;
				//right
			case 77:
				state = 4;
				update(field);
				break;
				//down
			case 80:
				state = 2;
				update(field);
				break;
			default:
				break;
			}
		}
		else {
			update(field);
		}
		render(field, speed);
	}
	return 0;
}
void create_field(size_t height, size_t weight) {
	return;
}
void update(char field[height][weight + 1]) {
	auto add = [&]() {
		if (position_body[size_snake - 1][1] != 0)
			field[position_body[size_snake - 1][1]][position_body[size_snake - 1][0]] = ' ';
		for (short i{size_snake - 1}; i >= 0; i--){
			if (i == 0) {
				position_body[i][0] = x;
				position_body[i][1] = y;
			}
			else {
				position_body[i][0] = position_body[i - 1][0];
				position_body[i][1] = position_body[i - 1][1];
			}
			field[position_body[i][1]][position_body[i][0]] = '@';
		}
		
		//generate apple
		
		if (field[y_apple][x_apple] == '*')
			return;
		else {
			while (field[y_apple][x_apple] != ' ') {
				x_apple = rand() % (weight - 2) + 1;
				y_apple = rand() % (height - 2) + 1;
			}
			field[y_apple][x_apple] = '*';
		}
		
	};
	//body_position
	if (state == 0)
		add();
	else if (state == 1) {

		if (field[y - 1][x] == '@' || field[y - 1][x] == '#') {
			game_over = true;
			return;
		}
		else {
			if (field[y - 1][x] == '*')
				size_snake++;
			--y;
		}
		add();
	}
	else if (state == 2) {
		if (field[y + 1][x] == '@' || field[y + 1][x] == '#') {
			game_over = true;
			return;
		}
		else {
			if (field[y + 1][x] == '*')
				size_snake++;
			++y;
		}
		add();
	}
	else if (state == 3) {
		if (field[y][x - 1] == '@' || field[y][x - 1] == '#') {
			game_over = true;
			return;
		}
		else {
			if (field[y][x - 1] == '*')
				size_snake++;
			--x;
		}
		add();
	}
	else if (state == 4) {
		if (field[y][x + 1] == '@' || field[y][x + 1] == '#') {
			game_over = true;
			return;
		}
		else {
			if (field[y][x + 1] == '*')
				size_snake++;
			++x;
		}
		add();
	}
	else if (state == 5)
		return;
}
void render(char field[height][weight+1], float speed) {
	system("cls");
	cout << "Points: " << size_snake <<"\t Speed: "<<speed << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (short i{}; i < height; i++) {
		cout << "\t";
		for (short x{}; x < weight+1; x++) {
			if (field[i][x] == '@') {
				SetConsoleTextAttribute(hConsole, 10);
				cout << field[i][x];
			}
			else if (field[i][x] == '#') {
				SetConsoleTextAttribute(hConsole, 15);
				cout << field[i][x];
			}
			else if (field[i][x] == '*') {
				SetConsoleTextAttribute(hConsole, 12);
				cout << field[i][x];
			}
			else {
				cout << field[i][x];
			}
		}
		cout << endl;
	}
}
