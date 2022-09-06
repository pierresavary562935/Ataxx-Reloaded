#include "../headers/mainwindow.h"


/**
 * \brief       Constructeur de la classe MainWindow
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMaximumSize(800,800);
    this->setMinimumSize(800,800);
    setWindowIcon(QIcon(":/img/resources/img/icon.png"));
    setWindowTitle("Ataxx Relaoded");

    mode = 2;
    panelSize = 7;
    volumes = 100;
    volumeMusic = 100;
    volumeSoundsEffects = 100;
    nbPlayer = 2;

    ataxxMenu = new Menu;
    ataxxOptions = new options;
    ataxxGame = new graphicArray;

    ataxxGameCore = new game();

    ataxxWindows = new QStackedWidget();
    ataxxWindows->addWidget(ataxxMenu);
    ataxxWindows->addWidget(ataxxGame);
    ataxxWindows->addWidget(ataxxOptions);


    setCentralWidget(ataxxWindows);

    connect(ataxxMenu, SIGNAL(playWindowShow()), this, SLOT(changeWindowGame()));
    connect(ataxxMenu, SIGNAL(optionsWindowShow()), this, SLOT(changeWindowOptions()));
    connect(ataxxOptions, SIGNAL(optionsHaveBeenClosed()), this, SLOT(changeWindowGame()));

    connect(ataxxGame, SIGNAL(cellClickedSignal(int, int)), this, SLOT(cellClickedonTable(int, int)));
    connect(ataxxGame, SIGNAL(gameStopSignal()), this, SLOT(returnMenu()));


}


/**
 * \brief       Constructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{

}

/**
 * \brief       Fonction développé par Alexande Thomas,
 *                  permettant de récupérer les arguments en entrée du programme.
 */
QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> arguments) {
    for(int i=0; i<argc - 1; i++) {
        QString qarg(argv[i]);

        if(qarg.size() == 0)
            continue;

        if(qarg[0] != "-")
            continue;

        qarg = qarg.remove("-");

        arguments[qarg] = argv[i+1];
    }

    return arguments;
}

void MainWindow::setMode(int mode)
{
    this->mode = mode;
}

/**
 * \brief       Slot permettant d'afficher la fenêtre avec le plateau de jeu,
 *                  permet aussi de configurer le jeu à chaque lancement.
 */
void MainWindow::changeWindowGame(){

    cout << "Nombre de joueurs :" << ataxxOptions->getNbPlayer() << endl;
    cout << "Panel size :" << ataxxOptions->getPanelSize() << endl;
    cout << "Volume music setted :" << ataxxOptions->getVolumeMusic() << endl;
    cout << "VolumeSoundEffect setted :" << ataxxOptions->getVolumeSoundsEffects() << endl;

    panelSize = ataxxOptions->getPanelSize();
    volumeMusic = ataxxOptions->getVolumeMusic();
    volumeSoundsEffects = ataxxOptions->getVolumeSoundsEffects();
    nbPlayer = ataxxOptions->getNbPlayer();

    //ataxxGameCore = new game();

    ataxxGameCore->configure(panelSize,nbPlayer,mode,volumeMusic,volumeSoundsEffects, ataxxGame);
    ataxxGame->initPlateauQt(panelSize,nbPlayer);
    ataxxWindows->setCurrentWidget(ataxxGame);
}

/**
 * \brief       Slot permettant d'afficher la fenêtre d'accueil (menu) lors de l'appui sur le bouton
 */
void MainWindow::returnMenu(){
    ataxxGameCore->gameStop();
    ataxxWindows->setCurrentWidget(ataxxMenu);
}

/**
 * \brief       Slot permettant d'afficher la fenêtre des options lors de l'appui sur le bouton
 */
void MainWindow::changeWindowOptions(){
    ataxxWindows->setCurrentWidget(ataxxOptions);
}

/**
 * \brief       Slot permettant d'intéragir avec le QTableWidget.
 * \details     Envoie la case cliquée au coeur du jeu.
 */
void MainWindow::cellClickedonTable(int x, int y){
    ataxxGameCore->cellClickedonTable(x,y);


}
