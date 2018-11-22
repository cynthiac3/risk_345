#pragma once
#include "Strategy.h"

class Benevolent : public Strategy {
public:
	Benevolent(Player* player) { p = player; human = false; }; // Constructor assigns current player and human to false because it is a computer
	~Benevolent() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};