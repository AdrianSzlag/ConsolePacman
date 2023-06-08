#include "leaderboard.h"

void leaderboard::sort()
{
	int size = players.size();
	if (size < 2) return;
	user* users = new user[size];
	copy(players.begin(), players.end(), users);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (users[i].score > users[j].score) {
				user buff = users[i];
				users[i] = users[j];
				users[j] = buff;
			}
	while (!players.empty()) players.pop_back();
	for (int i = 0; i < size; i++)
		players.push_back(users[i]);
}

void leaderboard::load()
{
	while (!players.empty()) players.pop_back();
	fstream plik(file_name, ios::in);
	string line;
	char c, number[MAX_LINE];
	int i = 0, j = 0;
	user* player;
	while (getline(plik, line)) {
		player = new user;
		int del = line.find(';');
		player->name = line.substr(0, del);
		sscanf_s(line.substr(del + 1, line.length() - del - 1).c_str(), "%d", &player->score);
		players.push_back(*player);
	}
	plik.close();
}

void leaderboard::save()
{
	fstream plik(file_name, ios::out);
	string line;
	int i = 0, j = 0;
	user* player;
	for (user player : players) {
		plik << player.name << ";" << player.score << endl;
	}
	plik.close();
}

leaderboard::~leaderboard()
{
	players.clear();
}
