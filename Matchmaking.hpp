#pragma once
#include <iostream>
#include "Player.hpp"

const int MAX_PLAYERS = 100;

class Matchmaking {

private:
    
    Player players[MAX_PLAYERS];
    int size;

public:

    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    Player* formGroup(int groupSize, int delta, int* n);

    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();

    // Outros métodos auxiliares, se necessário

    Player* merge(Player arr1[], int m1, Player arr2[], int m2);
    Player* mergeSort(Player* plays, int n);

    // getters
    //Player* getPlayers();
    //int& getSize();

};