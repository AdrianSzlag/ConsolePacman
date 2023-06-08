#include "lvl3.h"

void lvl3::updateGhost(Entity& ghost) {

	short movement = canMove(ghost.pos);

	bool ok = true;
	short playerSeen = 0;
	if (player.pos.y == ghost.pos.y) {
		int i = ghost.pos.x;
		while (canMoveTo(Vector<int>(--i, ghost.pos.y)))
			if (player.pos.x == i) {
				playerSeen += LEFT;
				break;
			}
		i = ghost.pos.x;
		while (canMoveTo(Vector<int>(++i, ghost.pos.y)))
			if (player.pos.x == i) {
				playerSeen += RIGHT;
				break;
			}
	}
	else if (player.pos.x == ghost.pos.x) {
		int i = ghost.pos.y;
		while (canMoveTo(Vector<int>(ghost.pos.x, --i)))
			if (player.pos.y == i) {
				playerSeen += UP;
				break;
			}
		i = ghost.pos.y;
		while (canMoveTo(Vector<int>(ghost.pos.x, ++i)))
			if (player.pos.y == i) {
				playerSeen += DOWN;
				break;
			}
	}
	if (playerSeen) {
		if (!onDrugs) {
			if (playerSeen & UP) ghost.movement = UP;
			if (playerSeen & DOWN) ghost.movement = DOWN;
			if (playerSeen & LEFT) ghost.movement = LEFT;
			if (playerSeen & RIGHT) ghost.movement = RIGHT;
			ok = false;
		}
		else {
			if (playerSeen & UP && movement - UP != 0) movement -= UP;
			if (playerSeen & DOWN && movement - DOWN != 0) movement -= DOWN;
			if (playerSeen & LEFT && movement - LEFT != 0) movement -= LEFT;
			if (playerSeen & RIGHT && movement - RIGHT != 0) movement -= RIGHT;
		}
	}
	if (ok) {
		int sum = 0;
		short possible_move_directions[4];
		if (movement & UP && (ghost.movement != DOWN || movement - UP == 0))
			possible_move_directions[sum++] = UP;

		if (movement & DOWN && (ghost.movement != UP || movement - DOWN == 0))
			possible_move_directions[sum++] = DOWN;

		if (movement & LEFT && (ghost.movement != RIGHT || movement - LEFT == 0))
			possible_move_directions[sum++] = LEFT;

		if (movement & RIGHT && (ghost.movement != LEFT || movement - RIGHT == 0))
			possible_move_directions[sum++] = RIGHT;

		if (sum != 0) {
			int m = rand() % sum;
			ghost.movement = possible_move_directions[m];
		}
	}

	switch (ghost.movement) {
	case UP:
		ghost.pos += Vector<int>(0, -1);
		break;
	case DOWN:
		ghost.pos += Vector<int>(0, 1);
		break;
	case LEFT:
		ghost.pos += Vector<int>(-1, 0);
		break;
	case RIGHT:
		ghost.pos += Vector<int>(1, 0);
		break;
	}

	teleports(ghost.pos);
}

lvl3::~lvl3()
{
	delete[] map;
}

