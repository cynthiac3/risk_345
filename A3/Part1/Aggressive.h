#pragma once
#include "Strategy.h"

class Aggressive : public Strategy {
public:
	Aggressive(Player* player) { p = player; human = false; };
	~Aggressive() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};