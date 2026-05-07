#include "Player.hpp"
#include "Matchmaking.hpp"
#include <iostream>
using namespace std;

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
}

bool Matchmaking::removePlayer(int id){
    for(int i = 0; i < size; i++){
        if(players[i].getId() == id){
            for(int j = i; j < size-1; j++){
                players[j] = players[j+1];
            }
            size--;
            return true;
        }
    }
    return false;
    
}

void Matchmaking::sortByScoreInsertion(){
    Player current;
    for(int i=1; i<size; i++) {
        int j = i-1;
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

Player* Matchmaking::merge(Player arr1[], int m1, Player arr2[], int m2){
    Player* merged = new Player[m1+m2];
    int i = 0,j = 0;
    while(i< m1 && j<m2){
        Player p1 = arr1[i];
        Player p2 = arr2[j];

        if(p1.getScore() > p2.getScore() ||
        (p1.getScore()==p2.getScore() && p1.getTimestamp()>p2.getTimestamp())
        ){
            merged[i+j] = p2;
            j++;
        } else {
            merged[i+j] = p1;
            i++;
        }   
    }
    while(i < m1){
        merged[i+j] = arr1[i];
        i++;
    }
    while(j<m2){
        merged[i+j] = arr2[j];
        j++;
    }
    return merged;
}

Player* Matchmaking::mergeSort(Player* plays, int n){
    if(n == 1){
        Player* single = new Player[1];
        single[0] = plays[0];
        return single;
    }
    int mid = n/2;
    Player* left = mergeSort(plays, mid);
    Player* right = mergeSort(plays+mid, n-mid);
    Player* sorted = merge(left, mid, right, n-mid);

    delete[] left;                                  
    delete[] right; 

    return sorted;
}

void Matchmaking::sortByScoreMerge(){
    if(size == 0 || size == 1){
        return;
    }
    Player* aux  = mergeSort(players, size);

    for(int i = 0; i < size; i++){
        players[i] = aux[i];
    }

    delete[] aux;
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    if(size == 0 || groupSize > size){
        *n = 0;
        return nullptr;
    }
    for(int i = 0; i<size-groupSize+1; i++){
        if((players[i+groupSize-1].getScore() - players[i].getScore()) <= delta){
            cout << "Grupo formado com sucesso!";
            Player* group = new Player[groupSize];
            for(int j = i; j<=i+groupSize-1;j++){
                group[j-i] = players[j];
                this->removePlayer(players[j].getId());
            }
            *n = groupSize;
            return group;
        }
    }
    *n = 0;
    return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n){
    *n = size;
    if(*n == 0){
        return nullptr;
    }
    Player* plays = new Player[size];
    for(int i = 0; i < *n; i++){
        plays[i] = players[i];
    }
    return plays;
}

void Matchmaking::printWaitingPlayers(){
    if(size == 0){
        cout << "(empty)";
    } else {
        cout << "Waiting Players: \n";
        for(int i = 0; i < size; i++){
            Player p = players[i];
            cout << "[ " << p.getId() << " | " << p.getName() << " | " << p.getScore() << " | " << p.getTimestamp() << " ]\n";
        }
        cout << endl;
    }
}
