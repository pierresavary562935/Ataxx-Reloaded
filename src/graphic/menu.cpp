#include "../headers/menu.h"


/**
 * \brief       Constructeur de la classe Menu
 */
Menu::Menu(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Ataxx Relaoded");


    //Image de fond
    bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/img/resources/img/home_bg.png"));
    bg->setMinimumSize(800,800);
    bg->setMaximumSize(800,800);

    //Bouton play
    playButton = new QPushButton(this);
    playButton->setIcon(QPixmap(":/img/resources/img/button_play.png"));
    //change color
    QString Buttonstyle = ("QPushButton {background-color: #BF4316; border:none; }");
    playButton->setStyleSheet(Buttonstyle);
    playButton->setIconSize(QSize(171,71));
    playButton->setMinimumSize(171,71);
    playButton->setMaximumSize(171,71);
    playButton->move(590,690);

    //Bouton options
    optionsButton = new QPushButton(this);
    optionsButton->setIcon(QPixmap(":/img/resources/img/options_icon.png"));
    optionsButton->setStyleSheet(Buttonstyle);
    optionsButton->setIconSize(QSize(50,50));
    optionsButton->setMinimumSize(50,50);
    optionsButton->setMaximumSize(50,50);
    optionsButton->move(740,10);




    //Detect click on button
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(optionsButton, SIGNAL(clicked()), this, SLOT(optionsOpen()));


}

/**
 * \brief       Destructeur de la classe Menu
 */
Menu::~Menu(){}

/**
 * \brief       Slot permettant d'afficher la fenêtre de jeu lors de l'appui sur le bouton
 */
void Menu::play(){
    emit playWindowShow();

}

/**
 * \brief       Slot permettant d'afficher la fenêtre des options lors de l'appui sur le bouton
 */
void Menu::optionsOpen(){
    emit optionsWindowShow();
}
