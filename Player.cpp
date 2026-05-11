#include "Player.hpp"
#include <iostream>

// Construtor padrão de Player (sem parâmetros)
Player::Player()
{
}

// Construtor com parâmetros de Player
Player::Player(int id, std::string name, int score, int timestamp)
{
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
}

// Destrutor de player
Player::~Player() {}

// Getters para os atributos de Player
int Player::getId() { return id; }
std::string Player::getName() { return name; }
int Player::getScore() { return score; }
int Player::getTimestamp() { return timestamp; }
