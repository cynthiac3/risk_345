#include <iostream>
#include <windows.h.>
#include "Graphics.h"
#include "MainDriver.h"
#include "MainGame.h"
#include "MainGameTournament.h"

using namespace std;

int main()
{
	Graphics graphics;
	MainGame singleGame;
	MainGameTournament tournament;

	//****************************** MAIN GAME LOOP ******************************
	do { // WELCOME Screen
		graphics.empty(8); graphics.riskLogo(); graphics.empty(5); 
		cout << "                 " << "[0] Play Single Game" << endl; graphics.empty(2);
		cout << "                 " << "[1] Simulate Tournament" << endl; graphics.empty(4);
		cout << "                 " << "Make your choice." << endl; graphics.empty(2);		
		// Player chooses which type of game to play
		int gameChoice;
		cin >> gameChoice;
		if (cin.fail()) { // Check for valid input
			cout << "Choose either [0] or [1]." << endl;
			cin.clear();
		}
		else {
			switch (gameChoice) {
			case 0: singleGame.run(); break; // Run Single Game
			case 1: tournament.run(); break; // Run Tournament
			default: cout << "Choose either [0] or [1]." << endl;
			}
		}
	} while (cin.get() != '\n');
	
//************************* GAME COMPLETE *************************
	// Game Exit Screen
	do {
		graphics.empty(10); cout << "                 " << "Thank you for playing" << endl;
		graphics.empty(5); graphics.riskLogo(); graphics.empty(9);
		cout << "                 " << "Press any key to exit." << endl;
	} while (cin.get() != '\n');

	return 0;
}
