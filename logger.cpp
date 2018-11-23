#include <string>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <iomanip>


using namespace std;

string hashfile(const char *filename){ 
	ifstream fp(filename);
	stringstream ss;

	// Unable to hash file, return an empty hash.
	if (!fp.is_open()) {
		return "";
	}

	// Hashing
	uint32_t magic = 5381;
	char c;
	while (fp.get(c)) {
		magic = ((magic << 5) + magic) + c; // magic * 33 + c
	}
	
	ss << hex << setw(8) << setfill('0') << magic;
	return ss.str();
}


void pause(int dur){
	int temp = time(NULL) + dur;
	while(temp > time(NULL));
}

int main(){
	system("Echo players world domination view > log.txt");
        system("type log.txt");

	string lastHash = hashfile("log.txt");
	string curentHash;
	do{
		pause(1);
		curentHash = hashfile("log.txt");
		if(curentHash.compare(lastHash) != 0){
			system("cls");
			system("type log.txt");
			lastHash = curentHash;
		}
	}while(1);
}	


