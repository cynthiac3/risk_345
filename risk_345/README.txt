g++ -std=c++11 Map_CPNT.cpp CGraph.cpp Map_loader.cpp ML_drive.cpp -o Map_loader
g++ -std=c++11 Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp -o map

* the num 1 or 0 at the end of execution it the bool return of the ConnectedGraph  tester.
* the CB maps doesn't load as a connected graph since it not one
