#include <iostream>
#include "gameManager.h"
using namespace std;

int main(){

    bool playing = true;
    GameManager *manager = new GameManager();
    manager->resetBoard();
    manager->printBoard();
    while(playing){
        manager->proceed_turn();
        manager->printBoard();
    }
    delete manager;
}