#include <iostream>
#include <windows.h.>
#include "Graphics.h"
#include "MainDriver.h"
#include "MainGame.h" // runSingleGame();
#include "MainGameTournament.h" // runTournament();
#include "Player.h" // used for Player's clearInput method
using namespace std;


int main()
{
	//****************************** MAIN GAME LOOP ******************************
	while (true) {  // Main Menu
		empty(8); riskLogo(); empty(5);
		cout << "                 " << "[0] Play Single Game" << endl; empty(2);
		cout << "                 " << "[1] Simulate Tournament" << endl; empty(4);
		cout << "                 " << "Make your choice." << endl; empty(2);
		// Player chooses which type of game to play
		int gameChoice;
		cin >> gameChoice;
		if (cin.fail()) { // Check for valid input
			clearInput();
		}
		else {
			switch (gameChoice) {
			case 0: runSingleGame(); break; // Run Single Game
			case 1: runTournament(); break; // Run Tournament
			default: cout << "Choose either [0] or [1]." << endl;
			}
		}
	}
	
//************************* GAME COMPLETE *************************
	// Game Exit Screen
	do {
		empty(10); cout << "                 " << "Thank you for playing" << endl;
		empty(5); riskLogo(); empty(9);
		cout << "                 " << "Press any key to exit." << endl;
	} while (cin.get() != '\n');

	return 0;
}
