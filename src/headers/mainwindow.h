/**
 * \file          mainwindow.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Génère le visuel du jeu en mode graphique dans une fenêtre
 *
 * \details    Cette classe s'occupe d'afficher le jeu dans une fenêtre,
 *              et de d'afficher les différentes fenêtre (options, menu, jeu)
 *              demandées par le joueur.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QString>

#include "menu.h"
#include "graphicarray.h"
#include "game.h"
#include "options.h"


using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMode(int mode);

public slots:
    void changeWindowGame();
    void changeWindowOptions();
    void cellClickedonTable(int x, int y);
    void returnMenu();



private:

    graphicArray * ataxxGame;
    Menu * ataxxMenu;
    game * ataxxGameCore;
    options * ataxxOptions;

    QStackedWidget * ataxxWindows;
    QVBoxLayout * layout;

    //Game
    int mode;

    int panelSize;
    int volumes;
    int volumeMusic;
    int volumeSoundsEffects;
    int nbPlayer;
};

QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> defaultValues = QMap<QString, QString>());

#endif // MAINWINDOW_H
