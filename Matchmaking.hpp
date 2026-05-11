#pragma once
#include <iostream>
#include "Player.hpp"

// Constante que define a capacidade máxima de jogadores
const int MAX_PLAYERS = 100000;

/**
    * Classe representando um sistema de matchmaking, 
    * responsável por armazenar jogadores em uma fila de espera e
    * formar grupos de jogadores com níveis de habilidade semelhantes
    * Contém uma lista de players com capacidade máxima de "MAX_PLAYERS"
    * e um atributo size representando a quantidade de jogadores atualmente 
    * presentes nessa lista de espera
*/
class Matchmaking
{

private:
    Player players[MAX_PLAYERS]; // Contém um array de jogadores com capacidade MAX_PLAYERS
    int size;

public:
    /**
        * Construtor padrão de um sistema de matchmaking
    */
    Matchmaking();

    /**
        * Destrutor de um sistema de matchmaking
    */
    ~Matchmaking();

    /**
        * Método para inserir uma jogador na lista de espera do sistema
        * quando há espaço disponível. Retorna true se foi possível armazenar e 
        * false caso contrário.
    */
    bool insert(Player player);

    /**
        * Método para remover uma jogador na lista de espera do sistema, 
        * dado o seu id. Retorna true se o jogador foi encontrado e removido, 
        * false caso contrário.
    */
    bool removePlayer(int id);

    /**
        * Método para ordenar os jogadores da lista de espera em ordem crescente
        * com o algoritmo insertion sort, considerando score e, para desempate, timestamp.
    */
    void sortByScoreInsertion();

    /**
        * Método para ordenar os jogadores da lista de espera em ordem crescente
        * com o algoritmo merge sort, considerando score e, para desempate, timestamp.
    */
    void sortByScoreMerge();

    /**
        * Método para formar o primeiro grupo válido de tamanho groupSize
        * na lista de jogadores do sistema de Matchmaking.
        * Em um grupo válido a diferença de score entre quaisquer 
        * dois jogadores é menor ou igual a delta.
        * Associa *n a 0 se não formou grupo e a groupSize se foi possível formar.
        * Retorna um ponteiro para o array de jogadores do grupo formado,
        * alocado dinamicamente. Se não foi possível formá-lo, retorna nullptr.
    */
    Player *formGroup(int groupSize, int delta, int *n);

    /**
        * Método que cria uma cópia dos jogadores atualmente na lista de espera
        * em um novo array alocado dinamicamente de tamanho *n = size.
        * Retorna nullptr e faz *n=0 se não há jogadores atualmente na lista.
    */
    Player *getWaitingPlayers(int *n);

    /**
        * Método para exibir cada jogador atualmente na lista de espera, 
        * com o id, nome, score e timestamp
    */
    void printWaitingPlayers();


    // Outros métodos auxiliares, se necessário

    /**
        * Método auxiliar para o merge sort utilizado para combinr duas listas 
        * ordenados em uma nova, ainda ordenada.
    */
    Player *merge(Player arr1[], int m1, Player arr2[], int m2);
    /**
        * Método auxiliar com implementação do algoritmo do Merge Sort 
        * utilizando chamadas recursivas
    */
    Player *mergeSort(Player *plays, int n);
};