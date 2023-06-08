// pacman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <stdlib.h>
#include <Windows.h>

#include "draw.h"
#include "Game.h"
#include "lvl1.h"
#include "lvl2.h"
#include "lvl3.h"
#include "leaderboard.h"

#define MAX_NAME 64

using namespace std;

int main(int argc, char *argv[])
{
	
	int lvl = 1;

	if (argc == 1) {
		lvl = 1;
	}
	else if (argc != 2) {
		cout << "Wrong argument\n" << endl;
		cout << "Run:\pacman [lvl]\nLvls:\n1\n2\n3" << endl;
		return -1;
	}
	else if (strcmp(argv[1], "1") == 0) lvl = 1;
	else if (strcmp(argv[1], "2") == 0) lvl = 2;
	else if (strcmp(argv[1], "3") == 0) lvl = 3;
	else {
		cout << "Wrong lvl\n" << endl;
		cout << "Lvls:\n1\n2\n3" << endl;
		return -1;
	}
	
	saveTerminal();
	clearTerminal();
	TerminalControl term;
	Game* game;

	if(lvl == 3) game = new lvl3(&term);
	else if (lvl == 2) game = new lvl2(&term);
	else game = new lvl1(&term);

	string filename = "lvl" + to_string(lvl) + ".txt";
	leaderboard board(filename);
	board.load();
	board.sort();
	
	char leaderboardText[MAX_NAME];

	term.draw_rectangle_fill(Vector<int>(22, 0), 22, 21, '$');
	term.draw_rectangle_fill(Vector<int>(23, 1), 20, 19, ' ');
	term.print(Vector<int>(24, 2), "Leaderboard: ");
		
	int i = 1;
	for (user player : board.players) {
		if (i > 8) break;
		sprintf_s(leaderboardText, "%2d. %10s %4d", i, player.name.c_str(), player.score);
		term.print(Vector<int>(23, i * 2 + 2), leaderboardText, MAX_NAME);
		i++;
	}

	int score = game->Play();

	user player;
	term.draw_rectangle_fill(Vector<int>(12, 10), 23, 5, '@');
	term.draw_rectangle_fill(Vector<int>(13, 11), 21, 3, ' ');
	term.print(Vector<int>(15, 12), "Name: ");
	term.Draw();
	term.MoveCoursorTo(Vector<int>(22, 12));
	fflush(stdin);
	scanf_s("%s", leaderboardText, 10);

	player.name = leaderboardText;
	player.score = score;

	board.players.push_back(player);
	board.sort();
	board.save();

	delete game;
	restoreTerminal();
	
	return 0;
}
