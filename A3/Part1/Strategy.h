#pragma once

class Player;

class Strategy {
protected:
	Player * p;
	bool human; // to differentiate human and computer players
public:
	Strategy() {};
	~Strategy() {};
	// Game methods
	virtual void reinforce()=0;
	virtual void attack()=0;
	virtual void fortify()=0;
	bool isHuman() { return human; };
};