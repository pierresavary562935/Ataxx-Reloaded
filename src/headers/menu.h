/**
 * \file          menu.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Génère la fenêtre de menu/accueil en mode graphique
 *
 * \details    Cette classe s'occupe de générer la page d'accueil dans une fenêtre
 *
 */

#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

public slots:
    void play();
    void optionsOpen();

signals:
    void playWindowShow();
    void optionsWindowShow();


private:

    QLabel * bg;
    QPushButton * playButton;
    QPushButton * optionsButton;

};

#endif // MENU_H
