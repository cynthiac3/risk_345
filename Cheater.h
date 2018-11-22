#pragma once
#include "Strategy.h"

class Cheater : public Strategy {
public:
	Cheater(Player* player) { p = player; human = false; }; // Constructor assigns current player and human to false because it is a computer
	~Cheater() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};