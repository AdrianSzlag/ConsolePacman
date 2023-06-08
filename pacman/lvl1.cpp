#include "lvl1.h"

void lvl1::updateGhost(Entity& ghost) {

	short movement = canMove(ghost.pos);

	int sum = 0;

	if (movement & UP && (ghost.movement != DOWN || movement - UP == 0)) sum++;
	if (movement & DOWN && (ghost.movement != UP || movement - DOWN == 0)) sum++;
	if (movement & LEFT && (ghost.movement != RIGHT || movement - LEFT == 0)) sum++;
	if (movement & RIGHT && (ghost.movement != LEFT || movement - RIGHT == 0)) sum++;

	if (sum != 0) {
		sum = rand() % sum;
		if (movement & UP && (ghost.movement != DOWN || movement - UP == 0) && sum-- == 0) ghost.movement = UP;
		if (movement & DOWN && (ghost.movement != UP || movement - DOWN == 0) && sum-- == 0) ghost.movement = DOWN;
		if (movement & LEFT && (ghost.movement != RIGHT || movement - LEFT == 0) && sum-- == 0) ghost.movement = LEFT;
		if (movement & RIGHT && (ghost.movement != LEFT || movement - RIGHT == 0) && sum-- == 0) ghost.movement = RIGHT;
	}

	moveEntity(ghost);
	teleports(ghost.pos);
}

lvl1::~lvl1()
{
	delete [] map;
}
