#pragma once
#include <iostream>
#include "draw.h"
#include <list>
#include <chrono>

#define LEFT 0b0001
#define DOWN 0b0010
#define RIGHT 0b0100
#define UP 0b1000

using namespace std;

class Entity {
public:

	Vector<int> pos;
	Vector<int> startingPos;

	short movement = 0;
	char c = ' ';

	/// <summary>
	/// Class constructor
	/// </summary>
	/// <param name="pos">Starting position</param>
	/// <param name="c">Entity char representation</param>
	Entity(Vector<int> pos, char c) : pos(pos), startingPos(pos), c(c) {}
	Entity() : pos(Vector<int>(0, 0)), startingPos(Vector<int>(0, 0)) {};
	/// <summary>
	/// move the entity to the starting point
	/// </summary>
	void reset();
};

class Game {
private:
	int score = 0;
	int lives = 3;
	int bonus = 0;
	int points = 0;

	bool doorsOpen = false;
	int doorsX, doorsY;

	char** map;
	const char map_size_x = 19, map_size_y = 19;

	chrono::time_point<chrono::steady_clock> GhostsLastUpdateTime = chrono::steady_clock::now();
	chrono::time_point<chrono::steady_clock> PlayerLastUpdateTime = chrono::steady_clock::now();
	chrono::time_point<chrono::steady_clock> DrugsStartTime = chrono::steady_clock::now();

	TerminalControl* terminal;
	char* screen_buffor_array;
	int buffor_height;
	int buffor_width;

	/// <summary>
	/// get proper box building character
	/// </summary>
	/// <param name="x">x</param>
	/// <param name="y">y</param>
	void GetProperWall(Vector<int> pos);

	/// <summary>
	/// interpret and build map
	/// </summary>
	void renderMap();

	/// <summary>
	/// draw in terminal
	/// </summary>
	void draw();
	
	/// <summary>
	/// check the keys pressed by user and adjust direction
	/// </summary>
	void updatePlayerMovementDirection();
	/// <summary>
	/// update player
	/// </summary>
	void updatePlayer();
	void updateEnemies();

protected:
	/// <summary>
	/// Did pacman take the pill
	/// </summary>
	bool onDrugs = false;
	/// <summary>
	/// time pacman is on boost
	/// </summary>
	int timeOnDrugs = 8000;
	/// <summary>
	/// speed of standard update interval
	/// </summary>
	int UpdateSpeedMs;
	/// <summary>
	/// pacman speed multiplier
	/// </summary>
	double pacmanSpeed = 1.0;
	/// <summary>
	/// ghosts speed multiplier
	/// </summary>
	double ghostsSpeed = 0.75;

	/// <summary>
	/// list of all ghosts
	/// </summary>
	list<Entity> ghosts;
	/// <summary>
	/// player class
	/// </summary>
	Entity player;

	/// <summary>
	/// check if entity can move to point (x, y)
	/// </summary>
	/// <param name="x">X</param>
	/// <param name="y">Y</param>
	/// <returns>true or false</returns>
	bool canMoveTo(Vector<int> pos);
	/// <summary>
	/// Move entity one block in direction
	/// </summary>
	void moveEntity(Entity& entity);
	/// <summary>
	/// check all the possible movement directions from point (x, y)
	/// </summary>
	/// <param name="x">X</param>
	/// <param name="y">Y</param>
	/// <returns>binary sum of posible direction</returns>
	short canMove(Vector<int> pos);
	/// <summary>
	/// check if entity crossed teleport point and move to the next point
	/// </summary>
	/// <param name="x">entity X pos</param>
	/// <param name="y">entity Y pos</param>
	void teleports(Vector<int> &pos);

	/// <summary>
	/// initialize game
	/// </summary>
	/// <param name="map">array of strings representing map</param>
	/// <param name="UpdateSpeedMs">speed of standard update interval</param>
	void init(string map[], int UpdateSpeedMs);

	/// <summary>
	/// update ghost
	/// virtual metod to be declared by lvl class
	/// </summary>
	/// <param name="ghost">ghost entity</param>
	virtual void updateGhost(Entity& ghost) = 0;
public:
	/// <summary>
	/// Class constructor
	/// </summary>
	/// <param name="term">Terminal control object</param>
	/// <param name="map_size_x">map size x</param>
	/// <param name="map_size_y">map size y</param>
	Game(TerminalControl* term, int map_size_x, int map_size_y);
	/// <summary>
	/// Play until game over or win
	/// </summary>
	/// <returns>player score</returns>
	int Play();
	~Game();
};
