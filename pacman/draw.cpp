#include "draw.h"

TerminalControl::TerminalControl() {
	saveTerminal();
	clearTerminal();
	int i, j;
	for (i = 0; i < MAX_WIDTH; i++)
		for (j = 0; j < MAX_HEIGHT; j++)
		{
			screen_buffor_array[0][i * MAX_HEIGHT + j] = ' ';
			screen_buffor_array[1][i * MAX_HEIGHT + j] = ' ';
		}
}

void TerminalControl::clearScreen() {
	int i, j;
	for (i = 0; i < MAX_WIDTH; i++)
		for (j = 0; j < MAX_HEIGHT; j++)
		{
			screen_buffor_array[1][i * MAX_HEIGHT + j] = ' ';
		}
}

void TerminalControl::draw_rectangle_fill(Vector<int> pos, int width, int height, char c) {
	int i, j;
	for (i = pos.x; i < pos.x + width; i++) {
		if (i >= MAX_WIDTH) continue;
		for (j = pos.y; j < pos.y + height; j++)
		{
			if (j >= MAX_HEIGHT) continue;
			screen_buffor_array[1][i * MAX_HEIGHT + j] = c;
		}
	}
}
void TerminalControl::put_char(Vector<int> pos, char c) {
	if (pos.x >= MAX_WIDTH || pos.y >= MAX_HEIGHT) return;
	screen_buffor_array[1][pos.x * MAX_HEIGHT + pos.y] = c;
}

void TerminalControl::TerminalControl::print(Vector<int>pos, char* str, int max) {
	for (int i = 0; i < max && str[i] != '\0'; i++)
		put_char(Vector<int>(pos.x + i, pos.y), str[i]);
}
void TerminalControl::print(Vector<int> pos, string str) {
	for (int i = 0; i < str.length(); i++)
		put_char(Vector<int>(pos.x + i, pos.y), str[i]);
}

char* TerminalControl::GetScreenBuffor() {
	return screen_buffor_array[1];
}
int TerminalControl::GetScreenBufforHeight() {
	return MAX_HEIGHT;
}
int TerminalControl::GetScreenBufforWidth() {
	return MAX_WIDTH;
}
void TerminalControl::MoveCoursorTo(Vector<int> pos) {
	if (pos.x >= MAX_WIDTH || pos.y >= MAX_HEIGHT) return;
	gotoxy(pos.x, pos.y);
}

void TerminalControl::Draw() {
	int i, j, next;
	for (j = 0; j < MAX_HEIGHT; j++) {
		next = 0;
		for (i = 0; i < MAX_WIDTH; i++) {
			if (screen_buffor_array[0][i * MAX_HEIGHT + j] != screen_buffor_array[1][i * MAX_HEIGHT + j]) {
				if (next == 0) gotoxy(i, j);
				putchar(screen_buffor_array[1][i * MAX_HEIGHT + j]);
				screen_buffor_array[0][i * MAX_HEIGHT + j] = screen_buffor_array[1][i * MAX_HEIGHT + j];
				next = 1;
			}
			else next = 0;
		}
	}
	gotoxy(MAX_WIDTH - 1, MAX_HEIGHT - 1);
}

TerminalControl::~TerminalControl()
{
	restoreTerminal();
}
