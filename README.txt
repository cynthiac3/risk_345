g++ -std=c++11 Map_CPNT.cpp CGraph.cpp Map_loader.cpp ML_drive.cpp -o Map_loader
g++ -std=c++11  Deck.cpp Player.cpp Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp -o map

g++ -std=c++11 Dice.cpp Subject.cpp Observer.cpp Deck.cpp Hand.cpp Strategy.cpp Random.cpp Aggressive.cpp Cheater.cpp Benevolent.cpp Human.cpp Player.cpp Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp View.cpp ViewDriver.cpp -o view

* the num 1 or 0 at the end of execution it the bool return of the ConnectedGraph  tester.
* the CB maps doesn't load as a connected graph since it not one

g++ -std=c++11 Dice.cpp Subject.cpp Observer.cpp Deck.cpp Hand.cpp Strategy.cpp Random.cpp Aggressive.cpp Cheater.cpp Benevolent.cpp Human.cpp Player.cpp Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp View.cpp MainGame.cpp -o MG
g++ -std=c++11 Dice.cpp Subject.cpp Observer.cpp Deck.cpp Hand.cpp Strategy.cpp Random.cpp Aggressive.cpp Cheater.cpp Benevolent.cpp Human.cpp Player.cpp Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp View.cpp MainGameTournament.cpp -o MGM


///////compile game
g++ -std=c++11 Dice.cpp Subject.cpp Observer.cpp Deck.cpp Hand.cpp Strategy.cpp Random.cpp Aggressive.cpp Cheater.cpp Benevolent.cpp Human.cpp Player.cpp Map_CPNT.cpp CGraph.cpp Map_loader.cpp Map.cpp View.cpp Graphics.cpp MainGameTournament.cpp MainGame.cpp MainDriver.cpp -o GAME
