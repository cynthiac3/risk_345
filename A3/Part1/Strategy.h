#pragma once

class Player;

class Strategy {
protected:
	Player * p;
public:
	Strategy() {};
	~Strategy() {};
	// Game methods
	virtual void reinforce()=0;
	virtual void attack()=0;
	virtual void fortify()=0;
};