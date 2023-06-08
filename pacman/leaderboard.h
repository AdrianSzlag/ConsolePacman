#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_LINE 128

using namespace std;

struct user {
	/// <summary>
	/// player name
	/// </summary>
	string name;
	/// <summary>
	/// player score
	/// </summary>
	int score;
};

class leaderboard {
private:
	string file_name;
public:
	/// <summary>
	/// players stored in vector
	/// </summary>
	vector<user> players;
	/// <summary>
	/// Leaderboard constructor
	/// </summary>
	/// <param name="file_name">name of file</param>
	leaderboard(string file_name) : file_name(file_name) {}
	/// <summary>
	/// sort players scores
	/// </summary>
	void sort();
	/// <summary>
	/// load players from file
	/// </summary>
	void load();
	/// <summary>
	/// save players to file
	/// </summary>
	void save();
	~leaderboard();
};

