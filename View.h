#pragma once

#include <fstream>

#include "Map.h"
#include "Observer.h"
#include "Player.h" 

using namespace std;


class View : public Observer {
	public:
		View();
		View(Map *s);
		~View();
		void Update(); 
    	void display(); 
		
		
	private:	
	Map* _subject;
	ofstream logFile;
};

