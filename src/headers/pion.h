/**
 * \file          pion.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Class utile pour le jeu
 *
 * \details    Cette classe permet de créer pions avec des coordonnées et/ou un joueur,
 *              utilisée dans les deux modes de jeu (console ou graphique)
 */

#ifndef PION_H
#define PION_H


class Pion
{
public:

    Pion();
    ~Pion();

    void setPion(int x, int y);
    void setPions(int player, int x, int y);

    int getX();
    int getY();
    int getPlayer();

private:
    int X;
    int Y;
    int Player;

};


#endif // PION_H
