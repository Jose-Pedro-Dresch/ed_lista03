#pragma once
#include <iostream>


/**
    * Classe representando um jogador do sistema, 
    * com id, nome, score e timestamp
*/
class Player
{


private:
    int id;
    std::string name;
    int score;
    int timestamp;

public:
    /**
        * Construtor sem parâmetros de um Player, 
        * usado ao alocar espaço de memória para a lista de 
        * jogadores do matchmaking
    */
    Player();

    /**
        * Construtor com parâmetros do Player
    */
    Player(int id, std::string name, int score, int timestamp);

    /**
        * Destrutor de Player;
    */
    ~Player();

    // Getters para os atributos de Player
    int getId();
    std::string getName();
    int getScore();
    int getTimestamp();
};