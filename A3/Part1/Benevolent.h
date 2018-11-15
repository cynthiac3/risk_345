#pragma once
#include "Strategy.h"

class Benevolent : public Strategy {
public:
	Benevolent(Player* player) { p = player; human = false; };
	~Benevolent() {};
	// Game methods
	void reinforce();
	void attack();
	void fortify();
};