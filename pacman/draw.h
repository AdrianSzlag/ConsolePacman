#pragma once
#include <stdio.h>
#include <iostream>

#define clearTerminal() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y)+1, (x)+1)
#define saveTerminal() printf("\033[?1049h\033[H")
#define restoreTerminal() printf("\033[?1049l")
 
#define MAX_WIDTH 100
#define MAX_HEIGHT 26

using namespace std;

template <typename T>
class Vector {
public:
	T x, y;
	Vector() {};
	Vector(T x, T y) : x(x), y(y) {}

	/// <summary>
	/// operator ==
	/// </summary>
	/// <param name="lhs">lhs</param>
	/// <param name="rhs">rhs</param>
	/// <returns>true or false</returns>
	friend bool operator==(const Vector& lhs, const Vector& rhs) {return lhs.x == rhs.x && lhs.y == rhs.y;}
	/// <summary>
	/// operator +
	/// </summary>
	/// <param name="rhs"> rhs </param>
	/// <returns>sum</returns>
	Vector operator+(const Vector& rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	/// <summary>
	/// operator +=
	/// </summary>
	/// <param name="rhs">rhs</param>
	/// <returns>sum</returns>
	Vector& operator+=(const Vector& rhs) {
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		return *this;
	}
};



class TerminalControl
{
private:
	/// <summary>
	/// terminal buffors to store character data
	/// </summary>
	char screen_buffor_array[2][MAX_WIDTH * MAX_HEIGHT];
public:
	/// <summary>
	/// Constructor
	/// </summary>
	TerminalControl();
	/// <summary>
	/// fill screen with spacebars
	/// </summary>
	void clearScreen();
	/// <summary>
	/// draw rectangle using specific character
	/// </summary>
	/// <param name="pos">rectangle starting point</param>
	/// <param name="width">rectangle width</param>
	/// <param name="height">rectangle height</param>
	/// <param name="c">character to fill the rectangle with (default is full block)</param>
	void draw_rectangle_fill(Vector<int> pos, int width, int height, char c = (char)219);
	/// <summary>
	/// put char in the terminal 
	/// </summary>
	/// <param name="pos">starting point</param>
	/// <param name="c">char</param>
	void put_char(Vector<int> pos, char c);
	/// <summary>
	/// print c_str on screen
	/// </summary>
	/// <param name="pos">starting point</param>
	/// <param name="str">c_str to print</param>
	/// <param name="max">max c_string length</param>
	void print(Vector<int> pos, char* str, int max);
	/// <summary>
	/// print string on screen
	/// </summary>
	/// <param name="pos">starting point</param>
	/// <param name="str">c_str to print</param>
	void print(Vector<int> pos, string str);
	/// <summary>
	/// Get main screen buffor to draw outside this class
	/// </summary>
	/// <returns>returns char[MAX_WIDTH][MAX_HEIGHT]</returns>
	char* GetScreenBuffor();
	/// <summary>
	/// Get screen buffor height
	/// </summary>
	/// <returns>returns screen buffor height</returns>
	int GetScreenBufforHeight();
	/// <summary>
	/// Get screen buffor width
	/// </summary>
	/// <returns>returns screen buffor width</returns>
	int GetScreenBufforWidth();
	/// <summary>
	/// Move coursor to (x, y) point on screen 
	/// </summary>
	/// <param name="pos">starting point</param>
	void MoveCoursorTo(Vector<int> pos);
	/// <summary>
	/// Draw buffor in the terminal
	/// </summary>
	void Draw();
	~TerminalControl();
};

