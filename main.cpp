#include "Matchmaking.hpp"
#include <iostream>
#include <string>

using namespace std;

void printSection(const string &title)
{
   cout << "\n========================================\n";
   cout << title << "\n";
   cout << "========================================\n";
}

int main()
{
   Matchmaking *m = new Matchmaking();

   printSection("1. Insercao de jogadores");
   m->insert(Player(1, "Ana", 1000, 5));
   m->insert(Player(2, "Bruno", 900, 2));
   m->insert(Player(3, "Carla", 1000, 1));
   m->insert(Player(4, "Diego", 900, 4));
   m->insert(Player(5, "Eduarda", 1250, 3));
   m->printWaitingPlayers();

   ////////////////////////////////////////////////////////////

   printSection("2. Recuperacao de dados (getWaitingPlayers)");
   int nPlayers;
   Player *currentPlayers = m->getWaitingPlayers(&nPlayers);
   cout << "Total de jogadores recuperados: " << nPlayers << "\n";
   if (currentPlayers != nullptr)
   {
      for (int i = 0; i < nPlayers; i++)
      {
         cout << "Recuperado -> ID: " << currentPlayers[i].getId()
              << " | Nome: " << currentPlayers[i].getName()
              << " | Score: " << currentPlayers[i].getScore() << "\n";
      }
      delete[] currentPlayers;
   }

   ////////////////////////////////////////////////////////////

   printSection("3. Remocao de jogador");
   bool removed = m->removePlayer(5); // Removendo Eduarda
   cout << "Jogador ID 5 removido? " << (removed ? "Sim" : "Não") << "\n\n";
   m->printWaitingPlayers();

   ////////////////////////////////////////////////////////////

   printSection("4. Ordenacao com Insertion Sort (com empate de score)");
   // Alocando o segundo objeto também na heap
   Matchmaking *mInsertion = new Matchmaking();
   mInsertion->insert(Player(1, "Ana", 1000, 5));
   mInsertion->insert(Player(2, "Bruno", 900, 2));
   mInsertion->insert(Player(3, "Carla", 1000, 1));
   mInsertion->insert(Player(4, "Diego", 900, 4));
   cout << "Antes da ordenacao:\n";
   mInsertion->printWaitingPlayers();
   mInsertion->sortByScoreInsertion();
   cout << "Apos Insertion Sort:\n";
   mInsertion->printWaitingPlayers();

   ////////////////////////////////////////////////////////////

   printSection("5. Ordenacao com Merge Sort (com empate de score)");
   cout << "Antes da ordenacao:\n";
   m->printWaitingPlayers();
   m->sortByScoreMerge();
   cout << "Apos Merge Sort:\n";
   m->printWaitingPlayers();

   ////////////////////////////////////////////////////////////

   printSection("6. Tentativa de formacao de grupo sem sucesso (3 pessoas, delta=10)");
   int groupSizeUnsuccessful;
   Player *invalidGroup = m->formGroup(3, 10, &groupSizeUnsuccessful);
   if (invalidGroup == nullptr)
   {
      cout << "Nenhum grupo formado. Jogadores permanecem na fila.\n\n";
   }
   m->printWaitingPlayers();

   ////////////////////////////////////////////////////////////

   printSection("7. Formacao bem-sucedida de grupo (2 pessoas, delta=50)");
   int groupSizeSuccessful;
   Player *validGroup = m->formGroup(2, 50, &groupSizeSuccessful);
   if (validGroup != nullptr)
   {
      cout << "Grupo formado com " << groupSizeSuccessful << " jogadores:\n";
      for (int i = 0; i < groupSizeSuccessful; i++)
      {
         cout << "[ " << validGroup[i].getId() << " | " << validGroup[i].getName() << " | "
              << validGroup[i].getScore() << " | " << validGroup[i].getTimestamp() << " ]\n";
      }
      delete[] validGroup;
   }

   ////////////////////////////////////////////////////////////

   printSection("8. Exibicao do estado do sistema pos-formacao");
   m->printWaitingPlayers();

   // Liberando a memória alocada
   delete m;
   delete mInsertion;

   return 0;
}