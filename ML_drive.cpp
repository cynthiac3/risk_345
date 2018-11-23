/*
	file: Map_loader.h
*/
	
#include ".\Map_loader.h"

int main(){
	//make a new map loader
	Map_loader Ml;
	
	//load the map
	Ml.parser(Ml.choose_file());
	//print map infor
	Ml.myInfo.printInfo();
	//print map graph	
	Ml.map_loaded.printGraph();
	
}
