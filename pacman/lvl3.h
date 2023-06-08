#pragma once
#include <iostream>
#include "Game.h"
#include "draw.h"
class lvl3 : public Game
{
public:
	int speed = 300;
	string map[23] = {
		"#####################",
		"#.....#.......#.....#",
		"#@###.#.#####.#.###@#",
		"#...................#",
		"###.#.###.#.###.#.###",
		"  # #.###.#.###.#.#  ",
		"###.#.....#.....#.###",
		"0  .###.#####.###.  1",
		"###....       ....###",
		"  #.### ##D## ###.#  ",
		"  #.#.. #&&&# ..#.#  ",
		"###.#.# ##### #.#.###",
		"0  ...#   *   #...  1",
		"###.#####.#.#####.###",
		"  #.......#.......#  ",
		"###.###.#####.###.###",
		"#@.................@#",
		"#.###.###.#.###.###.#",
		"#.###.#...#...#.###.#",
		"#.###.#.#####.#.###.#",
		"#...................#",
		"#####################"
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
	lvl3(TerminalControl* term) : Game(term, 21, 22) { init(map, speed); }
	~lvl3();
};

