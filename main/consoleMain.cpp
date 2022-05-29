#include <iostream>
#include <string>
#include <GameMechanics.h>

int main(int argc, char* argv[]) {
    GameMechanics *game = new GameMechanics;
    std::cout << "Hello world!" << std::endl;
    int airRemaining = 25;
    std::cout<<"SUB (" << airRemaining << ")";
    for(int i = 0; i < game->getPath()->getPathSize(); i++){
        std::cout<<" --> "<< game->getPath()->getTile(i)->getDots() << " (" << i + 1 << ")";
    }
    std::cout<<std::endl;
    int numPlayers;
    std::cout<<"How many players (2 - 6): " << std::endl;
    std::cin>>numPlayers;
    while(numPlayers < 2 || numPlayers > 6){
        std::cout<<"Enter in the range!"<<std::endl;
        std::cout<<"How many players (2 - 6): " << std::endl;
        std::cin>>numPlayers;
    }
    std::cout<<"Available colors: Red, Blue, Green, Yellow, Purple, Pink"<<std::endl;
    std::string name;
    std::string color;
    for(int i = 0; i < numPlayers; i++){
        std::cout<<"Enter name: ";
        std::cin>>name;
        std::cout<<"Enter color from list: ";
        std::cin>>color;
        game->addPlayer(name, color);
        game->getPlayers()[i]->setLocation(0);
    }

    std::cout<<"We have: " << numPlayers << " players!" <<std::endl;
    std::cout<<"--------"<<std::endl;
    for(int i = 0; i < numPlayers; i++){
        std::cout<<"Player " << i + 1<<std::endl;
        std::cout<<game->getPlayers()[i]->getName()<<std::endl;
        std::cout<<game->getPlayers()[i]->getColor()<<std::endl;
        std::cout<<"--------"<<std::endl;
    }
    int round = 1; 
    int roll;
    while(round <= 3){
        airRemaining = 25;
        while(airRemaining > 0){
            for(int i = 0; i < numPlayers; i++){
                roll = game->rollDice() - game->getPlayers()[i]->getNumTreasure();
                std::cout<<game->getPlayers()[i]->getName()<<" rolled: " << roll << std::endl;
                std::string turnBack;
                if(!game->getPlayers()[i]->getTurnBack()){
                    std::cout<<"Do you want to turn back? (Y/N)";
                    std::cin>>turnBack;
                    if(turnBack == "Y"){
                        game->getPlayers()[i]->setTurnBack(true);
                    }
                }
                game->movePlayer(roll);
                std::string op;
                if(game->getPath()->getTile(game->getPlayers()[i]->getLocation()) != nullptr){
                    int tileDots = game->getPath()->getTile(game->getPlayers()[i]->getLocation())->getDots();
                    std::cout<<"The tile you landed on has: " << tileDots << " dot(s). Do you wish to take it? (Y/N)"<<std::endl;
                    std::cin>>op;
                    if(op == "Y"){
                        game->replaceTile(false);
                        std::cout<<game->getPlayers()[i]->getName()<<" has " << game->getPlayers()[i]->getNumTreasure() << " treasure(s)!"<<std::endl;
                    }
                } else if(game->getPlayers()[i]->getNumTreasure() >= 1){
                    std::cout<<"You have landed on a blank tile. Do you wish to replace you lowest treasure? (Y/N)";
                    std::cin>>op;
                    if(op == "Y"){
                        game->replaceTile(true);
                        std::cout<<game->getPlayers()[i]->getName()<<" has " << game->getPlayers()[i]->getNumTreasure() << " treasure(s)!"<<std::endl;
                    }
                }
                int idx = game->endTurn();
                std::cout<<"NEXT TURN IS: " << idx <<std::endl;
                airRemaining--;
            }
            std::cout<<"SUB (" << airRemaining << ")";
            for(int y = 0; y < game->getPath()->getPathSize(); y++){
                if(game->getPath()->getTile(y) == nullptr){
                    std::cout<<" --> X ( " << y + 1 << ")";
                } else {
                    std::cout<<" --> "<< game->getPath()->getTile(y)->getDots() << " (" << y + 1 << ")";
                }
            }
            for(int x = 0; x < numPlayers; x++){
                std::cout<<game->getPlayers()[x]->getName()<< " is at position: " << game->getPlayers()[x]->getLocation()<<std::endl;
            }
        }
    }
}