#include "Matchmaking.hpp"
#include <iostream>
using namespace std;

int main(){
   Matchmaking m;

   m.insert(Player(1, "Ana", 1000, 1));
   m.insert(Player(2, "Bruno", 1100, 2));
   m.insert(Player(3, "Carla", 1020, 3));
   m.insert(Player(4, "Dario", 900, 4));
   m.insert(Player(5, "Enpada", 900, 5));

   //m.removePlayer(2);

   m.sortByScoreInsertion();
   m.printWaitingPlayers();


   int n; 
   Player* players = m.getWaitingPlayers(&n);

   for(int i = 0; i < n; i++){
      cout <<players[i].getId() << " " << players[i].getName() << endl;
   }

   delete[] players;

   return 0;
}