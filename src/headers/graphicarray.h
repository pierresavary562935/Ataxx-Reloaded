/**
 * \file          graphicarray.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Génère la fenêtre de jeu en mode graphique
 *
 * \details    Cette classe s'occupe de générer le QTableWidget réprésentant le plateau de jeu
 *                dans une fenêtre, en fonction du nombre de joueurs et de la taille du plateau de jeu
 *                  choisis dans la fenêtre des options
 */

#ifndef GRAPHICARRAY_H
#define GRAPHICARRAY_H

#include <QtWidgets>
#include <iostream>


class graphicArray : public QWidget
{
    Q_OBJECT
public:
    graphicArray(QWidget *parent = nullptr);
    ~graphicArray();

    void initPlateauQt(int panelSize, int color);
    void initTable2();
    void initTable4();
    QTableWidgetItem * createItem(int style);

    QTableWidget &getPanel();
    void setItemInTable(int x, int y, int style);
    void changeBG(int style);
    void changeScore(QString score2, QString score4);

public slots:
    void cellClickedSlot(int x, int y);
    void gameStop();
    void gameOverShow();

signals:
    void cellClickedSignal(int x, int y);
    void gameStopSignal();

private:
    QTableWidget * plateauQt;
    int panelSize;
    int nbPlayer;

    QLabel * bg;
    QLabel * scoreLabel2;
    QLabel * scoreLabel4;

    QLabel * endWindowRed;
    QLabel * endWindowBlue;
    QLabel * endWindow2Equal;
    QLabel * endWindowGreen;
    QLabel * endWindowYellow;
    QLabel * endWindow4Equal;
    QPushButton * quitButton;
    QPushButton * endButton;





};

#endif // GRAPHICARRAY_H
