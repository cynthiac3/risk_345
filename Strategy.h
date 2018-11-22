#pragma once

class Player;

struct Country;

class Strategy {
protected:
	Player * p;
	bool human; // to differentiate human and computer players
	
	// Helper methods
	void clearInput();
	void moveArmies(Country* receiver, Country* giver);
	bool checkValidNeighbors_Attack(Country* attacking);
	bool checkValidNeighbors_Fortify(Country* attacking);
	void defenderEliminated(Player* p1, Player* p2);

public:
	Strategy() {};
	~Strategy() {};
	// Game methods
	virtual void reinforce()=0;
	virtual void attack()=0;
	virtual void fortify()=0;
	bool isHuman() { return human; };


};