#include "headers/pion.h"

Pion::Pion()
{

}

Pion::~Pion() {}

int Pion::getX() { return this->X;}
int Pion::getY() {return this->Y;}
int Pion::getPlayer() {return this->Player;}


void Pion::setPion(int x, int y){
    this->X = x;
    this->Y = y;

}

void Pion::setPions(int player, int x, int y){
    this->Player = player;
    this->X = x;
    this->Y = y;

}
