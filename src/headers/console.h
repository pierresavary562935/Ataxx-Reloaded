/**
 * \file          console.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Gère le jeu en mode console
 *
 * \details    Cette classe s'occupe de générer le jeu dans la console
 *              en version 2 joueurs
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <math.h>
#include <iostream>
#include "pion.h"



using namespace std;

class console
{
private:
    int plateau[9][9];
    int positionsPions1[9][9];
    int positionsPions2[9][9];
    int coupsPossibles[9][9];
public:
    console();
    ~console();

    int getScore(int player);

    void launch();
    bool gameStatus(int player);
    void initPlateau();
    void initPositionPions();
    void initCoupsPossible(int x, int y);
    void AfficherPlateau();
    void afficherPositionPion(int player);
    void afficherCoupsPossibles();

    Pion searchOnPlateau(int pion, int player);
    void placeOnPlateau(int player, int x, int y);
    void placeOnPlateau(Pion p);

    void contamine(int player, int x, int y);
    bool move(int player,int x1, int y1, int x2, int y2);

    void AfficherPlateauDebug();




};

#endif // CONSOLE_H
