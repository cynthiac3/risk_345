#pragma once
#include "Strategy.h"

class Random : public Strategy {
public:
	Random(Player* player) { p = player; human = false; }; // Constructor assigns current player and human to false because it is a computer
	~Random() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};