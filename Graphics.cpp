#include <iostream>
#include <windows.h.>
#include "Graphics.h"
using namespace std;

void riskLogo()
{
	space(10); cout << "ooooooooo.    o8o           oooo        " << endl;
	space(10); cout << "`888   `Y88.  `\"'           `888        " << endl;
	space(10); cout << " 888   .d88' oooo   .oooo.o  888  oooo" << endl;
	space(10); cout << " 888ooo88P'  `888  d88(  \"8  888 .8P'   " << endl;
	space(10); cout << " 888`88b.     888  `\"Y88b.   888888.    " << endl;
	space(10); cout << " 888  `88b.   888  o.  )88b  888 `88b.  " << endl;
	space(10); cout << "o888o  o888o o888o 8\"\"888P' o888o o888o" << endl;
}

// Create specific number of empty LINES (for visual spacing)
void empty(int lines) {
	for (int i = 0; i < lines; i++) {
		cout << "          " << endl;
	}
}

// Create specific number of empty SPACES (for visual spacing)
void space(int lines) {
	for (int i = 0; i < lines; i++) {
		cout << " ";
	}
}

void bigOne() {
	space(20); cout << "  1111111  " << endl;
	space(20); cout << " 1::::::1  " << endl;
	space(20); cout << "1:::::::1   " << endl;
	space(20); cout << "111:::::1   " << endl;
	space(20); cout << "   1::::1  " << endl;
	space(20); cout << "   1::::1  " << endl;
	space(20); cout << "   1::::1  " << endl;
	space(20); cout << "   1::::l  " << endl;
	space(20); cout << "   1::::l  " << endl;
	space(20); cout << "   1::::l  " << endl;
	space(20); cout << "   1::::l   " << endl;
	space(20); cout << "   1::::l   " << endl;
	space(20); cout << "111::::::111  " << endl;
	space(20); cout << "1::::::::::1  " << endl;
	space(20); cout << "1::::::::::1  " << endl;
	space(20); cout << "111111111111  " << endl;
}

void bigTwo() {
	space(20); cout << " 222222222222222   " << endl;
	space(20); cout << "2:::::::::::::::22  " << endl;
	space(20); cout << "2::::::222222:::::2   " << endl;
	space(20); cout << "2222222     2:::::2  " << endl;
	space(20); cout << "            2:::::2  " << endl;
	space(20); cout << "            2:::::2   " << endl;
	space(20); cout << "         2222::::2  " << endl;
	space(20); cout << "    22222::::::22   " << endl;
	space(20); cout << "  22::::::::222   " << endl;
	space(20); cout << " 2:::::22222   " << endl;
	space(20); cout << "2:::::2    " << endl;
	space(20); cout << "2:::::2   " << endl;
	space(20); cout << "2:::::2       222222  " << endl;
	space(20); cout << "2::::::2222222:::::2  " << endl;
	space(20); cout << "2::::::::::::::::::2  " << endl;
	space(20); cout << "22222222222222222222  " << endl;
}

void bigThree() {
	space(20); cout << " 333333333333333   " << endl;
	space(20); cout << "3:::::::::::::::33  " << endl;
	space(20); cout << "3::::::33333::::::3  " << endl;
	space(20); cout << "3333333     3:::::3  " << endl;
	space(20); cout << "            3:::::3  " << endl;
	space(20); cout << "            3:::::3  " << endl;
	space(20); cout << "    33333333:::::3  " << endl;
	space(20); cout << "    3:::::::::::3  " << endl;
	space(20); cout << "    33333333:::::3  " << endl;
	space(20); cout << "            3:::::3  " << endl;
	space(20); cout << "            3:::::3  " << endl;
	space(20); cout << "            3:::::3  " << endl;
	space(20); cout << "3333333     3:::::3  " << endl;
	space(20); cout << "3::::::33333::::::3  " << endl;
	space(20); cout << "3:::::::::::::::33  " << endl;
	space(20); cout << " 333333333333333  " << endl;
}

void bigFour() {
	space(20); cout << "       444444444  " << endl;
	space(20); cout << "      4::::::::4  " << endl;
	space(20); cout << "     4:::::::::4  " << endl;
	space(20); cout << "    4::::44::::4   " << endl;
	space(20); cout << "   4::::4 4::::4   " << endl;
	space(20); cout << "  4::::4  4::::4   " << endl;
	space(20); cout << " 4::::4   4::::4   " << endl;
	space(20); cout << "4::::444444::::444  " << endl;
	space(20); cout << "4::::::::::::::::4  " << endl;
	space(20); cout << "4444444444:::::444  " << endl;
	space(20); cout << "4::::4   " << endl;
	space(20); cout << "          4::::4  " << endl;
	space(20); cout << "          4::::4  " << endl;
	space(20); cout << "        44::::::44  " << endl;
	space(20); cout << "        4::::::::4  " << endl;
	space(20); cout << "        4444444444  " << endl;
}

void bigFive() {
	space(20); cout << "555555555555555555  " << endl;
	space(20); cout << "5::::::::::::::::5  " << endl;
	space(20); cout << "5::::::::::::::::5   " << endl;
	space(20); cout << "5:::::555555555555  " << endl;
	space(20); cout << "5:::::5     " << endl;
	space(20); cout << "5:::::5    " << endl;
	space(20); cout << "5:::::5555555555  " << endl;
	space(20); cout << "5:::::::::::::::5   " << endl;
	space(20); cout << "555555555555:::::5  " << endl;
	space(20); cout << "            5:::::5  " << endl;
	space(20); cout << "            5:::::5  " << endl;
	space(20); cout << "5555555     5:::::5  " << endl;
	space(20); cout << "5::::::55555::::::5  " << endl;
	space(20); cout << " 55:::::::::::::55   " << endl;
	space(20); cout << "   55:::::::::55   " << endl;
	space(20); cout << "     555555555   " << endl;
}

void bigGame() {
	space(10); cout << " .d8888b.    " << endl;
	space(10); cout << "d88P  Y88b   " << endl;
	space(10); cout << "888    888   " << endl;
	space(10); cout << "888         8888b.  88888b.d88b.   .d88b.   " << endl;
	space(10); cout << "888  88888     \"88b 888 \"888 \"88b d8P  Y8b   " << endl;
	space(10); cout << "888    888 .d888888 888  888  888 88888888  " << endl;
	space(10); cout << "Y88b  d88P 888  888 888  888  888 Y8b.   " << endl;
	space(10); cout << " \"Y8888P88 \"Y888888 888  888  888  \"Y8888   " << endl;
}

// "ANIMATED" VERSIONS OF THE NUMBERS THAT BUILD UP LINE BY LINE

void bigOneScrollUp() {
	space(20); cout << "  1111111  " << endl; Sleep(10);
	space(20); cout << " 1::::::1  " << endl; Sleep(10);
	space(20); cout << "1:::::::1   " << endl; Sleep(10);
	space(20); cout << "111:::::1   " << endl; Sleep(10);
	space(20); cout << "   1::::1  " << endl; Sleep(10);
	space(20); cout << "   1::::1  " << endl; Sleep(10);
	space(20); cout << "   1::::1  " << endl; Sleep(10);
	space(20); cout << "   1::::l  " << endl; Sleep(10);
	space(20); cout << "   1::::l  " << endl; Sleep(10);
	space(20); cout << "   1::::l  " << endl; Sleep(10);
	space(20); cout << "   1::::l   " << endl; Sleep(10);
	space(20); cout << "   1::::l   " << endl; Sleep(10);
	space(20); cout << "111::::::111  " << endl; Sleep(10);
	space(20); cout << "1::::::::::1  " << endl; Sleep(10);
	space(20); cout << "1::::::::::1  " << endl; Sleep(10);
	space(20); cout << "111111111111  " << endl; Sleep(10);
}

void bigTwoScrollUp() {
	space(20); cout << " 222222222222222   " << endl; Sleep(10);
	space(20); cout << "2:::::::::::::::22  " << endl; Sleep(10);
	space(20); cout << "2::::::222222:::::2   " << endl; Sleep(10);
	space(20); cout << "2222222     2:::::2  " << endl; Sleep(10);
	space(20); cout << "            2:::::2  " << endl; Sleep(10);
	space(20); cout << "            2:::::2   " << endl; Sleep(10);
	space(20); cout << "         2222::::2  " << endl; Sleep(10);
	space(20); cout << "    22222::::::22   " << endl; Sleep(10);
	space(20); cout << "  22::::::::222   " << endl; Sleep(10);
	space(20); cout << " 2:::::22222   " << endl; Sleep(10);
	space(20); cout << "2:::::2    " << endl; Sleep(10);
	space(20); cout << "2:::::2   " << endl; Sleep(10);
	space(20); cout << "2:::::2       222222  " << endl; Sleep(10);
	space(20); cout << "2::::::2222222:::::2  " << endl; Sleep(10);
	space(20); cout << "2::::::::::::::::::2  " << endl; Sleep(10);
	space(20); cout << "22222222222222222222  " << endl;
}

void bigThreeScrollUp() {
	space(20); cout << " 333333333333333   " << endl; Sleep(10);
	space(20); cout << "3:::::::::::::::33  " << endl; Sleep(10);
	space(20); cout << "3::::::33333::::::3  " << endl; Sleep(10);
	space(20); cout << "3333333     3:::::3  " << endl; Sleep(10);
	space(20); cout << "            3:::::3  " << endl; Sleep(10);
	space(20); cout << "            3:::::3  " << endl; Sleep(10);
	space(20); cout << "    33333333:::::3  " << endl; Sleep(10);
	space(20); cout << "    3:::::::::::3  " << endl; Sleep(10);
	space(20); cout << "    33333333:::::3  " << endl; Sleep(10);
	space(20); cout << "            3:::::3  " << endl; Sleep(10);
	space(20); cout << "            3:::::3  " << endl; Sleep(10);
	space(20); cout << "            3:::::3  " << endl; Sleep(10);
	space(20); cout << "3333333     3:::::3  " << endl; Sleep(10);
	space(20); cout << "3::::::33333::::::3  " << endl; Sleep(10);
	space(20); cout << "3:::::::::::::::33  " << endl; Sleep(10);
	space(20); cout << " 333333333333333  " << endl; Sleep(10);
}

void bigFourScrollUp() {
	space(20); cout << "       444444444  " << endl; Sleep(10);
	space(20); cout << "      4::::::::4  " << endl; Sleep(10);
	space(20); cout << "     4:::::::::4  " << endl; Sleep(10);
	space(20); cout << "    4::::44::::4   " << endl; Sleep(10);
	space(20); cout << "   4::::4 4::::4   " << endl; Sleep(10);
	space(20); cout << "  4::::4  4::::4   " << endl; Sleep(10);
	space(20); cout << " 4::::4   4::::4   " << endl; Sleep(10);
	space(20); cout << "4::::444444::::444  " << endl; Sleep(10);
	space(20); cout << "4::::::::::::::::4  " << endl; Sleep(10);
	space(20); cout << "4444444444:::::444  " << endl; Sleep(10);
	space(20); cout << "4::::4   " << endl; Sleep(10);
	space(20); cout << "          4::::4  " << endl; Sleep(10);
	space(20); cout << "          4::::4  " << endl; Sleep(10);
	space(20); cout << "        44::::::44  " << endl; Sleep(10);
	space(20); cout << "        4::::::::4  " << endl; Sleep(10);
	space(20); cout << "        4444444444  " << endl; Sleep(10);
}

void bigFiveScrollUp() {
	space(20); cout << "555555555555555555  " << endl; Sleep(10);
	space(20); cout << "5::::::::::::::::5  " << endl; Sleep(10);
	space(20); cout << "5::::::::::::::::5   " << endl; Sleep(10);
	space(20); cout << "5:::::555555555555  " << endl; Sleep(10);
	space(20); cout << "5:::::5     " << endl; Sleep(10);
	space(20); cout << "5:::::5    " << endl; Sleep(10);
	space(20); cout << "5:::::5555555555  " << endl; Sleep(10);
	space(20); cout << "5:::::::::::::::5   " << endl; Sleep(10);
	space(20); cout << "555555555555:::::5  " << endl; Sleep(10);
	space(20); cout << "            5:::::5  " << endl; Sleep(10);
	space(20); cout << "            5:::::5  " << endl; Sleep(10);
	space(20); cout << "5555555     5:::::5  " << endl; Sleep(10);
	space(20); cout << "5::::::55555::::::5  " << endl; Sleep(10);
	space(20); cout << " 55:::::::::::::55   " << endl; Sleep(10);
	space(20); cout << "   55:::::::::55   " << endl; Sleep(10);
	space(20); cout << "     555555555   " << endl; Sleep(10);
}

void bigGameScrollUp() {
	space(10); cout << " .d8888b.    " << endl; Sleep(10);
	space(10); cout << "d88P  Y88b   " << endl; Sleep(10);
	space(10); cout << "888    888   " << endl; Sleep(10);
	space(10); cout << "888         8888b.  88888b.d88b.   .d88b.   " << endl; Sleep(10);
	space(10); cout << "888  88888     \"88b 888 \"888 \"88b d8P  Y8b   " << endl; Sleep(10);
	space(10); cout << "888    888 .d888888 888  888  888 88888888  " << endl; Sleep(10);
	space(10); cout << "Y88b  d88P 888  888 888  888  888 Y8b.   " << endl; Sleep(10);
	space(10); cout << " \"Y8888P88 \"Y888888 888  888  888  \"Y8888   " << endl; Sleep(10);
}

void mapBig() {
	space(10); cout << "     e    e                        " << endl;
	space(10); cout << "    d8b  d8b       /~~~8e  888-~88e " << endl;
	space(10); cout << "   d888bdY88b          88b 888  888b" << endl;
	space(10); cout << "  / Y88Y Y888b    e88~-888 888  8888" << endl;
	space(10); cout << " /   YY   Y888b  C888  888 888  888P" << endl;
	space(10); cout << "/          Y888b  \"88_ - 888 888 - _88\" " << endl;
	space(10); cout << "                           888      " << endl;
}
