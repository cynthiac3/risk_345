#pragma once
#include "Strategy.h"

class Human : public Strategy {
public:
	Human(Player* player) { p = player; human = true; }; // Constructor assigns current player and human to true
	~Human() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};