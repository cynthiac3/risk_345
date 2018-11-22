#pragma once
#include "Strategy.h"

class Aggressive : public Strategy {
public:	
	Aggressive(Player* player) { p = player; human = false; }; // Constructor assigns current player and human to false because it is a computer
	~Aggressive() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};