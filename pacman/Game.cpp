#include "Game.h"
#include <iostream>
#include <Windows.h>
#include "draw.h"
#include <chrono>

#define MAX_STR 64

void Game::GetProperWall(Vector<int> pos) {
	int x = pos.x;
	int y = pos.y;
	short neighbors = 0;
	if (x > 0)
		if (map[x - 1][y] == '#' || (unsigned)map[x - 1][y] >= 186)
			neighbors += LEFT;
	if (y > 0)
		if (map[x][y - 1] == '#' || (unsigned)map[x][y - 1] >= 186)
			neighbors += DOWN;
	if (x < map_size_x - 1)
		if (map[x + 1][y] == '#' || (unsigned)map[x + 1][y] >= 186)
			neighbors += RIGHT;
	if (y < map_size_y - 1)
		if (map[x][y + 1] == '#' || (unsigned)map[x][y + 1] >= 186)
			neighbors += UP;


	switch (neighbors)
	{
	case 0:
		map[x][y] = (char)207;
		return;
	case UP | DOWN | LEFT | RIGHT:
		map[x][y] = (char)206;
		return;

	case (LEFT | DOWN | RIGHT):
		map[x][y] = (char)202;
		return;
	case (LEFT | RIGHT | UP):
		map[x][y] = (char)203;
		return;
	case (DOWN | RIGHT | UP):
		map[x][y] = (char)204;
		return;
	case (LEFT | DOWN | UP):
		map[x][y] = (char)185;
		return;

	case (UP | RIGHT):
		map[x][y] = (char)201;
		return;
	case (DOWN | RIGHT):
		map[x][y] = (char)200;
		return;
	case (LEFT | DOWN):
		map[x][y] = (char)188;
		return;
	case (LEFT | UP):
		map[x][y] = (char)187;
		return;

	default:
		break;
	}

	if (neighbors & 0b00000101) {
		map[x][y] = (char)205;
		return;
	}
	if (neighbors & 0b00001010) {
		map[x][y] = (char)186;
		return;
	}
	map[x][y] = (char)219;
}

void Game::renderMap() {
	for (int i = 0; i < map_size_x; i++)
	{
		for (int j = 0; j < map_size_y; j++)
		{
			if (map[i][j] == '&') {
				ghosts.push_back(Entity(Vector<int>(i, j), '&'));
				map[i][j] = ' ';
				continue;
			}
			if (map[i][j] == '*') {
				player.pos.x = i;
				player.startingPos.x = i;
				player.pos.y = j;
				player.startingPos.y = j;
				player.c = 'c';
				map[i][j] = ' ';
				continue;
			}
			if (map[i][j] == '#')
				GetProperWall(Vector<int>(i, j));

			if (map[i][j] == '.')
				points++;

			if (map[i][j] == 'D') {
				map[i][j] = (char)177;
				doorsX = i;
				doorsY = j;
			}
		}
	}
}

void Game::init(string map_[], int UpdateSpeedMs){
	this->UpdateSpeedMs = UpdateSpeedMs;

	map = new char* [map_size_x];

	for (int i = 0; i < map_size_x; i++) {
		map[i] = new char[map_size_y];
		for (int j = 0; j < map_size_y; j++)
			map[i][j] = map_[j][i];
	}
	renderMap();
}

Game::Game(TerminalControl* term, int map_size_x, int map_size_y) : terminal(term), map_size_x(map_size_x), map_size_y(map_size_y){
	srand((unsigned)time(NULL));
	screen_buffor_array = term->GetScreenBuffor();
	buffor_height = term->GetScreenBufforHeight();
	buffor_width = term->GetScreenBufforWidth();
}

void Game::draw() {
	//draw map
	for (int i = 0; i < map_size_x; i++)
		if (i < buffor_width)
			for (int j = 0; j < map_size_y; j++)
				if (j < buffor_height) {
					screen_buffor_array[i * buffor_height + j] = map[i][j];
					if (map[i][j] == '0' || map[i][j] == '1') screen_buffor_array[i * buffor_height + j] = ' ';
				}
					
	//draw ghosts
	for (Entity& ghost : ghosts)
		terminal->put_char(ghost.pos, ghost.c);
	
	//draw player
	terminal->put_char(player.pos, player.c);

	//print score + lives
	char str[MAX_STR];
	sprintf_s(str, "Score %4d Lives %c%c%c", score, (lives > 2)? 'C': ' ', (lives > 1) ? 'C' : ' ', (lives > 0) ? 'C' : ' ');
	terminal->print(Vector<int>(0, map_size_y), str, MAX_STR);

	//force draw in terminal
	terminal->Draw();
}

void Game::updatePlayerMovementDirection() {
	short movement = canMove(player.pos);
	if (GetAsyncKeyState(VK_UP) & 0x8000 && movement & UP)
		player.movement = UP;
	
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && movement & DOWN) 
		player.movement = DOWN;
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && movement & LEFT) 
		player.movement = LEFT;
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && movement & RIGHT) 
		player.movement = RIGHT;
	
}
void Game::updateEnemies()
{
	if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - GhostsLastUpdateTime).count() > UpdateSpeedMs / ghostsSpeed) {
		GhostsLastUpdateTime = chrono::steady_clock::now();
		for (Entity& ghost : ghosts)
		{
			updateGhost(ghost);
		}
		draw();
	}
}
bool Game::canMoveTo(Vector<int> pos) {
	if (pos.x >= map_size_x || pos.y >= map_size_y || pos.x < 0 || pos.y < 0) return false;
	if (map[pos.x][pos.y] == ' ' || map[pos.x][pos.y] == '.' || map[pos.x][pos.y] == '0' || map[pos.x][pos.y] == '1' || map[pos.x][pos.y] == '@') return true;
	return false;
}
short Game::canMove(Vector<int> pos) {
	short movement = 0;
	if (canMoveTo(pos + Vector<int>(-1, 0)))
		movement += LEFT;
	if (canMoveTo(pos + Vector<int>(0, 1)))
		movement += DOWN;
	if (canMoveTo(pos + Vector<int>(1, 0)))
		movement += RIGHT;
	if (canMoveTo(pos + Vector<int>(0, -1)))
		movement += UP;
	return movement;
}

void Game::teleports(Vector<int> &pos) {
	if (map[pos.x][pos.y] == '0')
		while (map[++pos.x][pos.y] != '1');
	else if (map[pos.x][pos.y] == '1')
		while (map[--pos.x][pos.y] != '0');
}

void Game::updatePlayer() {
	if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - PlayerLastUpdateTime).count() > UpdateSpeedMs / pacmanSpeed) {
		PlayerLastUpdateTime = chrono::steady_clock::now();

		short movement = player.movement & canMove(player.pos);
		if (movement) {
			
			player.movement = movement;
			moveEntity(player);

			//animation
			
			if (onDrugs) {
				if (player.c == '@') player.c = 'b';
				else player.c = '@';
			}
			else {
				if (player.c == 'c') player.c = 'C';
				else player.c = 'c';
			}

			//points
			if (map[player.pos.x][player.pos.y] == '.') {
				points--;
				score++;
				map[player.pos.x][player.pos.y] = ' ';
			}
			//drugs
			if (map[player.pos.x][player.pos.y] == '@') {
				onDrugs = true;
				DrugsStartTime = chrono::steady_clock::now();
				map[player.pos.x][player.pos.y] = ' ';
			}

			//teleports
			teleports(player.pos);
		}
		if (onDrugs)
			if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - DrugsStartTime).count() > timeOnDrugs) {
				onDrugs = false;
				bonus = 0;
			}
				
		
			
		draw();
	}
}

int Game::Play() {
	while (true) {
		updatePlayerMovementDirection();
		if (player.movement != 0) {
			doorsOpen = true;
			map[doorsX][doorsY] = ' ';
		}
		updatePlayer();
		if (points == 0) {
			draw();
			return score;
		}
		for (Entity& ghost : ghosts)
		{
			if (player.pos == ghost.pos) {
				if (onDrugs) {
					ghost.reset();
					bonus += 10;
					score += bonus;
				}
				else {
					lives--;
					bonus = 0;
					onDrugs = false;
					if (lives == 0) {
						draw();
						return score;
					}
					player.reset();
					for (Entity& ghost : ghosts)
						ghost.reset();
					doorsOpen = false;
					map[doorsX][doorsY] = (char)177;
				}
			}
		}
		updateEnemies();
		Sleep(1);
	}
}
void Game::moveEntity(Entity& entity) {
	switch (entity.movement) {
	case UP:
		entity.pos += Vector<int>(0, -1);
		break;
	case DOWN:
		entity.pos += Vector<int>(0, 1);
		break;
	case LEFT:
		entity.pos += Vector<int>(-1, 0);
		break;
	case RIGHT:
		entity.pos += Vector<int>(1, 0);
		break;
	}
}

Game::~Game()
{
	ghosts.clear();
}

void Entity::reset()
{
	pos = startingPos;
	movement = 0;
}
