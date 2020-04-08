
МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ			

Федеральное государственное автономное образовательное учреждение высшего образования  

"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  

ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  

Кафедра компьютерной инженерии и моделирования

<br><br/>

### Отчёт по лабораторной работе № 4 <br/> по дисциплине "Программирование"

<br/>
студента 1 курса группы ИВТ-б-о-191-2
Чушева Сергея Александровича
направления подготовки 09.03.01 "Информатика и вычислительная техника"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>


Симферополь, 2019

## Лабораторная работа №4  Иксики-нолики
>Цель:

1. Закрепить навыки работы с перечислениями;
2. Закрепить навыки работы с структурами;
3. Освоить методы составления многофайловых программ.


>Ход работы

Создайте три файла:

1. Файл реализующий игру "Иксики-нолики" используя функции описанные в вспомогательном файле;
2. Вспомогательный файл. Содержит реализацию основных функций игры;
3. Заголовочный файл. Нужен для связи главного и вспомогательного файлов. Не забудьте добавить защиту от повторного включения файла.
>Основной файл (Osnovnoi.cpp)
>Код:
```C++
#include <iostream>
#include <time.h>
#include "header.h" 
using namespace std;
int main() {
	 int hwoper;
	Game game
	setlocale(LC_ALL, "rus");
	srand((unsigned)time(NULL));//чтоб первый всегда не ходил
	hwoper = rand() % 2;

	if (hwoper==1) {
		game.isUserTurn = true;
		game.userChar = 'X';
		game.botChar = 'O';
		game.status = PLAY;
	}
	else {
		game.isUserTurn = false;
		game.userChar = 'O';
		game.botChar = 'X';
		game.status = PLAY;
	}
	while (!updateGame(&game)) {//пока игра в работе
		if (game.isUserTurn) {
			userTurn(&game);
		}
		else {
			botTurn(&game);
		}
		updateDisplay(game);
	}

	switch (game.status) {
	case USER_WIN: cout << "Вы победили"; break;
	case BOT_WIN: cout << "Bы проиграли"; break;
	case NOT_WIN: cout << "Ничья"; break;
	}return 0;
}

```
>Вспомогательный файл(HelpFile.cpp)
>Код:
```C++
#include <iostream>
#include "header.h"
using namespace std;
Game game;
void updateDisplay(const Game game) {
	system("cls");
	cout << " _____0___1___2_" << endl;
	cout << " 0 " << " | " << game.bord[0][0] << " | " << game.bord[0][1] << " | " << game.bord[0][2] << " | " << endl;
	cout << "_________________" << endl;
	cout << " 1 " << " | " << game.bord[1][0] << " | " << game.bord[1][1] << " | " << game.bord[1][2] << " | " << endl;
	cout << "_________________" << endl;
	cout << " 2 " << " | " << game.bord[2][0] << " | " << game.bord[2][1] << " | " << game.bord[2][2] << " | " << endl;
	cout << "_________________" << endl;
}

void botTurn(Game* game) {
	bool CLEAR = true, BNCLEAR = false;
	int str;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (game->bord[i][j] == game->userChar || game->bord[i][j] == game->botChar) {
				CLEAR = false;
			}
		}
	}
	if (CLEAR) {
		game->bord[1][1] = game->botChar; game->isUserTurn = true;
	}
	else {
		for (int i = 0; i < 3; ++i) { 
			str = 0;
			if (game->bord[i][0] == game->userChar) {
				str++;
			}
			if (game->bord[i][1] == game->userChar) {
				str++;
			}
			if (game->bord[i][2] == game->userChar) { 
				str++; 
			}
			if (str > 1) {
				for (int j = 0; j < 3; ++j) { //пров столбц
					if (game->bord[i][j] != game->userChar && game->bord[i][j] != game->botChar) {
						game->bord[i][j] = game->botChar;game->isUserTurn = true;BNCLEAR = true;return;
					}
				}
				break;
			}
		}
		if (!BNCLEAR) {
			for (int j = 0; j < 3; ++j) { //чекаем столб
				str = 0;
				if (game->bord[0][j] == game->userChar) {
					str++;
				}
				if (game->bord[1][j] == game->userChar) {
					str++;
				}
				if (game->bord[2][j] == game->userChar) {
					str++;
				}
				if (str > 1) {
					for (int i = 0; i < 3; ++i) { 
						if (game->bord[i][j] != game->userChar && game->bord[i][j] != game->botChar) {
							game->bord[i][j] = game->botChar;game->isUserTurn = true;BNCLEAR = true;return;
						}
					}
					break;
				}
			}
		}
		if (!BNCLEAR) {//диагональ 00 11 22
			str = 0;
			for (int i = 0; i < 3; ++i) {
				if (game->bord[i][i] == game->userChar) {
					str++;
				}
			}
			if (str > 1) {
				for (int i = 0; i < 3; ++i) {
					if (game->bord[i][i] != game->userChar && game->bord[i][i] != game->botChar) {
						game->bord[i][i] = game->botChar;
						game->isUserTurn = true;
						BNCLEAR = true;
						return;
					}
				}
			}
		}
		if (!BNCLEAR) {//диагонал 02 11 20
			str = 0;
			if (game->bord[0][2] == game->userChar) {
				str++;
			}
			if (game->bord[1][1] == game->userChar) {
				str++;
			}
			if (game->bord[2][0] == game->userChar) {
				str++;
			}
			if (str > 1) {
				if ((game->bord[0][2] != game->userChar && game->bord[0][2] != game->botChar) && !BNCLEAR) {
					game->bord[0][2] = game->botChar;game->isUserTurn = true;BNCLEAR = true;return;
				}
				if ((game->bord[1][1] != game->userChar && game->bord[1][1] != game->botChar) && !BNCLEAR) {
					game->bord[1][1] = game->botChar;game->isUserTurn = true;BNCLEAR = true;return;
				}
				if ((game->bord[2][0] != game->userChar && game->bord[2][0] != game->botChar) && !BNCLEAR) {
					game->bord[2][0] = game->botChar;game->isUserTurn = true;BNCLEAR = true;return;
				}
			}
		}
		if (!BNCLEAR) {//рандомный 
			while (true) {
				int i = rand() % 3;
				int j = rand() % 3;
				if (game->bord[i][j] != game->userChar && game->bord[i][j] != game->botChar) {
					game->bord[i][j] = game->botChar;game->isUserTurn = true;BNCLEAR = true;break;
				}
			}

		}

	}

}
void userTurn(Game* game) {
	int i, j;
	while (true) {
		setlocale(LC_ALL, "rus");
		cout << "[строка][столбец]"; cin >> i >> j;
		if ((i >= 0) && (i <= 2) && (j >= 0) && (j <= 2)) {
			if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
				game->bord[i][j] = game->userChar;game->isUserTurn = false;break;
			}
			else cout << "Нельзя так " << endl;
		}
		else cout << "Нельзя так " << endl;
	}
}
bool updateGame(Game* game) {
	bool konec = true;
	char xoro;
	int str;
	if (!game->isUserTurn) xoro = game->userChar;
	else xoro = game->botChar;
	for (int i = 0; i < 3; ++i) {//строки
		str = 0;
		for (int j = 0; j < 3; ++j) {
			if (game->bord[i][j] == xoro) str++;
		}
		if (str == 3) {
			if (!game->isUserTurn) game->status = USER_WIN;
			else game->status = BOT_WIN;
			return konec;
		}
	}
	for (int j = 0; j < 3; ++j) {//ытолбы
		str = 0;
		for (int i = 0; i < 3; ++i) {
			if (game->bord[i][j] == xoro) str++;
		}
		if (str == 3) {
			if (!game->isUserTurn) game->status = USER_WIN;
			else game->status = BOT_WIN;
			return konec;
		}
	}
	str = 0;
	if (game->bord[0][0] == xoro) {
		str++;
	}
	if (game->bord[1][1] == xoro) {
		str++;
	}
	if (game->bord[2][2] == xoro) {
		str++;
	}
	if (str == 3) {
		if (!game->isUserTurn) game->status = USER_WIN;
		else game->status = BOT_WIN;return konec;
	}
	str = 0;
	if (game->bord[2][0] == xoro)  str++;
	if (game->bord[1][1] == xoro)  str++;
	if (game->bord[0][2] == xoro)  str++;
	if (str == 3) {
		if (!game->isUserTurn) game->status = USER_WIN;
		else game->status = BOT_WIN;return konec;
	}
	str = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
				str++;
			}
		}
	}
	if (!str) {
		game->status = NOT_WIN;
		return konec;
	}
	else konec = false;
	return konec;
}
Game initGame(char userChar) {
	int first = rand() % 2;
	char botChar;
	if (userChar == 'X') botChar = 'O';
	else botChar = 'X';
	game.userChar = userChar;
	game.botChar = botChar;
	if (first) game.isUserTurn = true;
	else game.isUserTurn = false;
	game.status = PLAY;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			game.bord[i][j] = ' ';
		}
	}
	return game;
}

```
>Заголовочный файл (header.h)
>Код:
```C++
#ifndef HEADER_H //от повторного 
#define HEADER_H
enum Status {
	PLAY,
	USER_WIN,
	BOT_WIN,
	NOT_WIN
};
struct Game {
	char bord[3][3];
	bool isUserTurn;
	char userChar;
	char botChar;
	Status status;
};
Game initGame(char userChar);
void updateDisplay(const Game game);
void botTurn(Game* game);
void userTurn(Game* game);
bool updateGame(Game* game);
#endif

```
**Вывод**: в ходе лабораторной работы я овладел практическими навыками разработки и программирования вычислительного процесса; закрепил навыки работы с перечислениями, закрепил навыки работы с структурами; освоил методы составления многофайловых программ.