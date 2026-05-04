#include "Player.hpp"
#include "Matchmaking.hpp"
#include <iostream>

Matchmaking::Matchmaking(){
    size = 0;
}

Matchmaking::~Matchmaking(){}

bool Matchmaking::insert(Player player){
    if(size < MAX_PLAYERS) {
        players[size++] = player;
        return true; 
    } else {
        return false;
    }

    return true;
}

bool Matchmaking::removePlayer(int id){
    for(int i = 0; i < size; i++){
        if(players[i].getId() == id){
            for(int j = i; i < size; j++){
                players[j] = players[j+1];
            }
            size--;
            return true;
        }
    }
    return false;
    
}

void Matchmaking::sortByScoreInsertion(){
    int i, j;
    Player current;
    for(int i=1; i<size; i++) {
        j = i-1;
        current = players[i];

        while(j>=0 && 
            (players[j].getScore() > current.getScore() || 
            (players[j].getScore() == current.getScore() &&  
            players[j].getTimestamp() > current.getTimestamp()))
        ){
            players[j+1] = players[j];
            j = j-1;
        }
        players[j+1] = current;
    }
}

void Matchmaking::sortByScoreMerge(){}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n){
    return nullptr;
}

void Matchmaking::printWaitingPlayers(){}
