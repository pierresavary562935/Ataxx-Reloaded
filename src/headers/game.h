/**
 * \file          game.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Gère le jeu en mode graphique
 *
 * \details    Cette classe est le coeur du jeu en version graphique,
 *               elle s'occupe de tous les calculs,
 *                  en prenant en compte les options choisis
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QMediaPlayer>
#include <QObject>
#include "graphicarray.h"
#include "pion.h"

using namespace std;

class game : public QObject
{
    Q_OBJECT
public:
    game();
    ~game();
    //Game config
    void configure(int panelSize, int nbPlayer, int volumes, int volumeMusic, int volumeSoundsEffects, graphicArray* table);

    //Game core
    void initPlateau2();
    void initPlateau4();

    void initCoupsPossible(int x, int y);
    void removeCoupsPossible(int x, int y);
    void play(int x, int y);
    int switchPlayer(int currentPlayer);
    bool saut(int x1, int y1, int x2, int y2);
    void contamine(int x, int y);

    bool analyzeCoupsPossible();
    bool analyzeCoupsPossible(int player);

    void cellClickedonTable(int x, int y);

    //Game status
    int getScore(int player);
    bool gameNoMorePionChoice();
    void scoreAnalize();
    void gameStop();

    //Debug
    void debug();

private:

    graphicArray * QtTable;
    int **plateau;
    int **coupsPossibles;

    //Game settings
    int panelSize;
    int volumes;
    int volumeMusic;
    int volumeSoundsEffects;
    int nbPlayer;

    //Game variables
    int currentPlayer;
    bool choixPion = false;

    bool gameStatus;

    Pion pionToPlay;
    Pion pionToHide;



    //Sounds
    QMediaPlayer * music;
    QMediaPlayer * soundMoveEffect;
    QMediaPlayer * soundContamineEffect;

};

#endif // GAME_H
