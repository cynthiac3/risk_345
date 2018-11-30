#include <iostream>
#include "Graphics.h"
using namespace std;

void riskLogo()
{
	cout << "          " << "ooooooooo.    o8o           oooo        " << endl;
	cout << "          " << "`888   `Y88.  `\"'           `888        " << endl;
	cout << "          " << " 888   .d88' oooo   .oooo.o  888  oooo" << endl;
	cout << "          " << " 888ooo88P'  `888  d88(  \"8  888 .8P'   " << endl;
	cout << "          " << " 888`88b.     888  `\"Y88b.   888888.    " << endl;
	cout << "          " << " 888  `88b.   888  o.  )88b  888 `88b.  " << endl;
	cout << "          " << "o888o  o888o o888o 8\"\"888P' o888o o888o" << endl;
}

// Create specific number of empty lines (for visual spacing)
void empty(int lines) {
	for (int i = 0; i < lines; i++) {
		cout << "          " << endl;
	}
}

