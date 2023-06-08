#pragma once
#include <iostream>
#include "Game.h"
#include "draw.h"

class lvl2 : public Game
{
public:
	int speed = 300;
	string map[19] = {
		"###################",
		"#........#........#",
		"#@##.###.#.###.##@#",
		"#.................#",
		"#.##.#.#####.#.##.#",
		"#....#...#...#....#",
		"####.###.#.###.####",
		"   #.#       #.#   ",
		"####.# ##D## #.####",
		"0   .  #&&&#  .   1",
		"####.# ##### #.####",
		"   #.#   *   #.#   ",
		"####.###.#.###.####",
		"#....#...#...#....#",
		"#.##.#.#####.#.##.#",
		"#@...............@#",
		"#.##.###.#.###.##.#",
		"#........#........#",
		"###################"
	};
	/// <summary>
	/// update ghost entity
	/// function unique for every lvl
	/// </summary>
	/// <param name="ghost"></param>
	void updateGhost(Entity& ghost);
public:
	/// <summary>
	/// Class constructor
	/// </summary>
	/// <param name="term">terminal control object</param>
	lvl2(TerminalControl* term) : Game(term, 19, 19) { init(map, speed); }
	~lvl2();
};

