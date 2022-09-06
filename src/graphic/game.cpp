#include "../headers/game.h"

/**
 * \brief       Constructeur de la classe game
 */
game::game()
{

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/resources/sounds/bgsound1.mp3"));

    soundMoveEffect = new QMediaPlayer();
    soundMoveEffect->setMedia(QUrl("qrc:/sounds/resources/sounds/woosh1.mp3"));

    soundContamineEffect = new QMediaPlayer();
    soundContamineEffect->setMedia(QUrl("qrc:/sounds/resources/sounds/woosh3.mp3"));
}


/**
 * \brief       Destructeur de la classe game()
 */
game::~game(){

}

/**
 * \brief       Configure la partie
 * \details    Cette fonction utilise ses paramètres ppour configurer la partie qui va être joué,
 * \param    panelSize          Taille du plateau de jeu, utile pour parcourir le tableau de jeu
 * \param    nbPlayer           Le nombre de joueur, pour la configuration de la partie
 * \param    volumes            Le volume général, pour de futur mise à jour
 * \param    volumesMusic       Le volume de la musique
 * \param    volumeSoundEffects      Le volume des effets sonores
 */
void game::configure(int panelSize,
                     int nbPlayer,
                     int volumes,
                     int volumeMusic,
                     int volumeSoundsEffects,
                     graphicArray* table) {

  currentPlayer = 1;
  pionToHide.setPion(1000,1000);


  this->QtTable = table;
  this->panelSize = panelSize;

  this->nbPlayer = nbPlayer;



      switch (nbPlayer) {
        case 2:
          initPlateau2();
          break;
        case 4:
          initPlateau4();
          break;
      }


  this->volumes = volumes;
  this->volumeMusic = volumeMusic;
  this->volumeSoundsEffects = volumeSoundsEffects;

  // Musique de fond

  if (music->state() == QMediaPlayer::PlayingState) {
    music->stop();
  } else if (music->state() == QMediaPlayer::StoppedState) {
    music->setVolume(volumeMusic);
    music->play();
  }

  soundMoveEffect->setVolume(volumeSoundsEffects);

  soundContamineEffect->setVolume(volumeSoundsEffects);
}

/**
 * \brief       Initialise le plateau binaire pour une partie à 2 joueurs
 */
void game::initPlateau2()
{
    plateau = new int*[ panelSize ];
     for (int i=0; i < panelSize; i++)
       plateau[i] = new int[ panelSize ];

     coupsPossibles = new int*[ panelSize ];
      for (int i=0; i < panelSize; i++)
        coupsPossibles[i] = new int[ panelSize ];

     //remplissage tab de 0
     for (int x = 0; x < panelSize; x++) {
         for (int y = 0; y < panelSize; y++) {
             coupsPossibles[x][y] = 0;
         }
     }

    for (int i = 0; i <= panelSize-1; i++) {

        for (int j = 0; j <= panelSize-1; j++) {

            if (j == 0 && i == 0) {

                this->plateau[i][j] = 2; // bleu

            } else if (j == panelSize-1 && i == panelSize-1) {

                this->plateau[i][j] = 2; // bleu

            } else if (j == 0 && i == panelSize-1) {

                this->plateau[i][j] = 1; // rouge

            } else if (j == panelSize-1 && i == 0) {

                this->plateau[i][j] = 1; // rouge

            } else {
                this->plateau[i][j] = 0; // blanc
            }
        }
    }
}

/**
 * \brief       Initialise le plateau binaire pour une partie à 4 joueurs
 */
void game::initPlateau4() {

    plateau = new int*[ panelSize ];
     for (int i=0; i < panelSize; i++)
       plateau[i] = new int[ panelSize ];

     coupsPossibles = new int*[ panelSize ];
      for (int i=0; i < panelSize; i++)
        coupsPossibles[i] = new int[ panelSize ];

     //remplissage tab de 0
     for (int x = 0; x < panelSize; x++) {
         for (int y = 0; y < panelSize; y++) {
             coupsPossibles[x][y] = 0;
         }
     }

    for (int i = 0; i <= panelSize-1; i++) {

        for (int j = 0; j <= panelSize-1; j++) {

            if (j == 0 && i == 0) {

                this->plateau[i][j] = 2; // bleu

            } else if (j == panelSize-1 && i == panelSize-1) {

                this->plateau[i][j] = 1; // rouge

            } else if (j == 0 && i == panelSize-1) {

                this->plateau[i][j] = 4; // jaune

            } else if (j == panelSize-1 && i == 0) {

                this->plateau[i][j] = 3; // vert

            } else {
                this->plateau[i][j] = 0; // blanc
            }
        }

    }


}


/**
 * \brief       Passe au joueur suivant
 * \details    Le joueur suivant est définie en fonction du joueur actuel et du nombre de joueur
 * \param    currentPlayer         Le joueur actuel
 * \return    Un \e int représentant le joueur suivant.
 */
int game::switchPlayer(int currentPlayer){


    switch(currentPlayer){

    case 1 :
        QtTable->changeBG(1);
        this->currentPlayer = 2;
    break;
    case 2 :
        if(nbPlayer==4){
            QtTable->changeBG(6);
            this->currentPlayer = 3;
        }
        if(nbPlayer==2){
            QtTable->changeBG(2);
            this->currentPlayer = 1;
        }
    break;
    case 3 :
        QtTable->changeBG(7);
        this->currentPlayer = 4;
    break;
    case 4 :
        QtTable->changeBG(2);
        this->currentPlayer = 1;
    break;
    }

    return this->currentPlayer;
}

/**
 * \brief       Récupère la case cliquée
 * \param    x         x, coordonnée horizontale.
 * \param    y         y, coordonnée verticale.
 */
void game::cellClickedonTable(int x, int y){

        play(x,y);
}

/**
 * \brief       Coeur du jeu
 * \param    x         x, coordonnée horizontale.
 * \param    y         y, coordonnée verticale.
 */
void game::play(int x, int y){

    scoreAnalize();

    //Joueur n
    if(x >= 0 && y >= 0 && x <= panelSize && y <= panelSize){ //si le pion existe

    while(choixPion==false){

        if(plateau[x][y] == currentPlayer){ //si le pion appartient au bon joueur

            if(pionToHide.getX() != 1000) removeCoupsPossible(pionToHide.getX(),pionToHide.getY());
        initCoupsPossible(x,y); //Affichage des coups possibles pour le pion choisi
        pionToHide.setPion(x,y);
        choixPion = true; //le joueur a bien choisi son pion
        pionToPlay.setPion(x,y); //stockage du pion choisi
        return;

        }else{
            if(pionToHide.getX() != 1000) removeCoupsPossible(pionToHide.getX(),pionToHide.getY());
            return;

        }

    }


        while(choixPion == true){ //tant qu'un pion est choisi
            if(currentPlayer == 2){
                QtTable->setItemInTable(pionToPlay.getX(),pionToPlay.getY(),2);
            }
            if(currentPlayer == 1){
                QtTable->setItemInTable(pionToPlay.getX(),pionToPlay.getY(),1);
            }
            if(currentPlayer == 3){
                QtTable->setItemInTable(pionToPlay.getX(),pionToPlay.getY(),7);
            }
            if(currentPlayer == 4){
                QtTable->setItemInTable(pionToPlay.getX(),pionToPlay.getY(),8);
            }
                    if(coupsPossibles[x][y] != 8){

                        choixPion = false;
                        play(x,y);
                        return;
                    }

                    if(coupsPossibles[x][y] == 8 && plateau[x][y] == 0){ //Si la case de déplacement est disponible
                        removeCoupsPossible(pionToPlay.getX(),pionToPlay.getY());

                                        if(!saut(pionToPlay.getX(),pionToPlay.getY(), x, y)){ // Si le déplacement est inférieur à 2

                                            soundMoveEffect->play();
                                            plateau[x][y] = currentPlayer;
                                            switch(currentPlayer){
                                            case 1 :
                                                QtTable->setItemInTable(x,y,currentPlayer);
                                                break;
                                            case 2:
                                                QtTable->setItemInTable(x,y,currentPlayer);
                                                break;
                                            case 3:
                                                QtTable->setItemInTable(x,y,7);
                                                break;
                                            case 4:
                                                QtTable->setItemInTable(x,y,8);
                                                break;

                                            }
                                            contamine(x,y);


                                        }else{  // Si le déplacement est supérieur à 2

                                            soundMoveEffect->play();
                                            plateau[pionToPlay.getX()][pionToPlay.getY()] = 0;
                                            QtTable->setItemInTable(pionToPlay.getX(),pionToPlay.getY(),3);
                                            plateau[x][y] = currentPlayer;
                                            switch(currentPlayer){
                                            case 1 :
                                                QtTable->setItemInTable(x,y,currentPlayer);
                                                break;
                                            case 2:
                                                QtTable->setItemInTable(x,y,currentPlayer);
                                                break;
                                            case 3:
                                                QtTable->setItemInTable(x,y,7);
                                                break;
                                            case 4:
                                                QtTable->setItemInTable(x,y,8);
                                                break;

                                            }
                                            contamine(x,y);

                                        }
                         choixPion = false;
                         do{
                             currentPlayer = switchPlayer(currentPlayer);
                         }while(getScore(currentPlayer)==0);
                         scoreAnalize();



                    }else{ //Si le déplacement n'est pas possible

                    choixPion = false;
                    return;

                    }


        }


    }else{
        //Pion inexistant

    }

}


/**
 * \brief       Analyse de l'état de la partie en cours
 */
void game::scoreAnalize(){
    QString score1,score2,score3,score4;
    score1.setNum(getScore(1));
    score2.setNum(getScore(2));
    score3.setNum(getScore(3));
    score4.setNum(getScore(4));

    QString newScoreLabel2 = "<font color=\"#2173a6\">" + score2 + "</font>" + "|" + "<font color=\"#bf4136\">" + score1 + "</font>";
    QString newScoreLabel4 = "<font color=\"#f2b33d\">" + score4 + "</font>" + "|" + "<font color=\"#027333\">" + score3 + "</font>";
    QtTable->changeScore(newScoreLabel2,newScoreLabel4);


    gameStatus = analyzeCoupsPossible();


if(nbPlayer == 2){
    // 2 or 3 = blue // 1 or 4 red // 3 green // 4 yellow
    //red win
    if(getScore(2) == 0 || (gameStatus == false && (getScore(1) > getScore(2)))){
        QtTable->changeBG(4);
        QtTable->changeBG(2);
    }
    //blue win
    if(getScore(1) == 0 || (gameStatus == false && (getScore(2) > getScore(1)))){
        QtTable->changeBG(3);
        QtTable->changeBG(1);
    }
    //Equality
    if((getScore(1) == getScore(2)) && gameStatus == false){
        QtTable->changeBG(5);
    }
}
if(nbPlayer == 4){
    //red win
    if((getScore(2) == 0 && getScore(3) == 0 && getScore(4) == 0) || (gameStatus == false && (getScore(1) > getScore(2) && getScore(1) > getScore(3) && getScore(1) > getScore(4)))){
        QtTable->changeBG(4);
        QtTable->changeBG(2);
    }
    //blue win
    if((getScore(1) == 0 && getScore(3) == 0 && getScore(4) == 0) || (gameStatus == false && (getScore(2) > getScore(1) && getScore(2) > getScore(3) && getScore(2) > getScore(4)))){
        QtTable->changeBG(3);
        QtTable->changeBG(1);
    }
    //green win
    if((getScore(2) == 0 && getScore(1) == 0 && getScore(4) == 0) || (gameStatus == false && (getScore(3) > getScore(2) && getScore(3) > getScore(1) && getScore(3) > getScore(4)))){
        QtTable->changeBG(8);
        QtTable->changeBG(6);
    }
    //yellow win
    if((getScore(2) == 0 && getScore(1) == 0 && getScore(3) == 0) || (gameStatus == false && (getScore(4) > getScore(2) && getScore(4) > getScore(1) && getScore(4) > getScore(3)))){
        QtTable->changeBG(9);
        QtTable->changeBG(7);
    }
    //Equality
    if((getScore(1) == getScore(2) && getScore(3) == getScore(4) && getScore(2) == getScore(4) ) && gameStatus == false){
        QtTable->changeBG(10);
    }
}
}

/**
 * \brief       Coupe la musique en fin de partie
 */
void game::gameStop(){
    music->stop();
}



/**
 * \brief       Calcule la distance entre deux points
 * \details    La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points.
 * \param    x1, y1         Point 1 pour le calcul de distance.
 * \param    x2, y2         Point 2 pour le calcul de distance.
 * \return    Un \e bool, \a false si le déplacement est inférieur à 2, \a true autrement.
 */
bool game::saut(int x1, int y1, int x2, int y2){
    //SI déplacement <3 cases AB = racine carré (xb - xa)^2 + (yb-ya)^2
            double x = pow(x2 - x1, 2);
            double y = pow(y2 - y1, 2);
            double result = sqrt(x + y);
            if (result < 2) return false;
            return true;
}

/**
 * \brief       Contamine les pions ennemis autour de la case entrée en argument
 * \details    Analyse si les cases autour de la case (x,y) sont des ennemis
 * \param    x, y        Case à analyser
 */
void game::contamine(int x, int y) {

for (int m = -1; m <= 1; m++) {
 for (int n = -1; n <= 1; n++) {

     if (x + m < 0 || x + m >= panelSize || y + n < 0 || y + n >= panelSize)
        continue;

     if (nbPlayer == 2 && (plateau[x + m][y + n] == (currentPlayer) % 2 + 1)) {
        soundContamineEffect->play();
        plateau[x + m][y + n] = currentPlayer;
        QtTable->setItemInTable(x + m, y + n, currentPlayer);
      }

      if (nbPlayer == 4 &&
          (plateau[x + m][y + n] == (currentPlayer) % 4 + 1 ||
           plateau[x + m][y + n] == (currentPlayer + 1) % 4 + 1 ||
           plateau[x + m][y + n] == (currentPlayer + 2) % 4 + 1)) {

        soundContamineEffect->play();
        plateau[x + m][y + n] = currentPlayer;

        switch (currentPlayer) {
          case 1:
            QtTable->setItemInTable(x + m, y + n, currentPlayer);
            break;
          case 2:
            QtTable->setItemInTable(x + m, y + n, currentPlayer);
            break;
          case 3:
            QtTable->setItemInTable(x + m, y + n, 7);
            break;
          case 4:
            QtTable->setItemInTable(x + m, y + n, 8);
            break;
        }
      }
    }
  }
}



/**
 * \brief       Calcule et affiche les coups possibles pour la case (x,y)
 * \details    Analyse toutes les cases à une distance inférieur à 3
 *             de la case choisi et change leur visuel et leur valeur dans le tableau binaire des coups possibles
 * \param    x, y        Case à analyser
 */
void game::initCoupsPossible(int x, int y) {

    if(currentPlayer == 1){
        QtTable->setItemInTable(x,y,5);
    }
    if(currentPlayer == 2){
        QtTable->setItemInTable(x,y,6);
    }
    if(currentPlayer == 3){
        QtTable->setItemInTable(x,y,9);
    }
    if(currentPlayer == 4){
        QtTable->setItemInTable(x,y,10);
    }


    for(int m = -2; m <= 2; m++){
        for(int n = -2; n <= 2;n++){
            if(x+m <= panelSize-1 && y+n <= panelSize-1 && x+m >= 0 && y+n >= 0 && plateau[x+m][y+n] == 0){ //plateau[x+m][y+n] == 0 && plateau[x+m][y+n] != 1 && plateau[x+m][y+n] != 2 &&
                QtTable->setItemInTable(x+m,y+n,4);
                coupsPossibles[x+m][y+n] = 8;
            }
        }
    }

}

/**
 * \brief       Retire les coups possibles pour la case (x,y)
 * \details    Analyse toutes les cases à une distance inférieur à 3
 *             de la case choisi et change leur visuel et leur valeur dans le tableau binaire des coups possibles
 * \param    x, y        Case à analyser
 */
void game::removeCoupsPossible(int x, int y) {


    for(int m = -2; m <= 2; m++){
        for(int n = -2; n <= 2;n++){
            if(x+m <= panelSize-1 && y+n <= panelSize-1 && x+m >= 0 && y+n >= 0 && coupsPossibles[x+m][y+n] == 8){
                QtTable->setItemInTable(x+m,y+n,3);
                coupsPossibles[x+m][y+n] = 0;
            }
        }
    }

}

/**
 * \brief       Analyse le statut de la partie en cours
 * \details    Vérifie le statut de la partie en cours en vérifiant les coups possibles du joueur actuel
 * \return    Un \e bool représentant le statut de la partie en cours
 *                \a false si terminée.
 */
bool game::analyzeCoupsPossible(){
    int count = 0;
    //SCAN TABLE
    for (int i = 0; i <= panelSize-1; i++) {

        for (int j = 0; j <= panelSize-1; j++) {

            //SELECT PLAYERS
            if(plateau[i][j] == currentPlayer){
                count++;
                //SCAN COUPS POSSIBLES
                for(int m = -2; m <= 2; m++){
                    for(int n = -2; n <= 2;n++){

                        if(i+m <= panelSize-1 && j+n <= panelSize-1 && i+m >= 0 && j+n >= 0 && plateau[i+m][j+n] == 0){
                            return true;
                        }

                    }
                }

            }

        }
    }

    //RETURN GAME STATUS
    if(count == getScore(currentPlayer)){
        if(nbPlayer==2)
        {
            //GAME FINISH
            return false;
        }
        if(nbPlayer==4 && gameNoMorePionChoice()==true){
            //GAME CONTINUE
            switchPlayer(currentPlayer);
            return true;
        }
        if(nbPlayer==4 && gameNoMorePionChoice()==false){
            //GAME FINISH
            return false;
        }



    }
        //GAME CONTINUE
        count = 0;
        return true;

}



/**
 * \brief       Calcule le score du joueur demandé
 * \details    Analyse le tableau binaire de la partie et compte le nombre de case du joueur en paramètre
 * \param    player         player, le joueur à analyser.
 * \return    Un \e int représentant le score du joueur demandé.
 */
int game::getScore(int player){
    int score = 0;

    for (int i = 0; i <= panelSize-1; i++) {

        for (int j = 0; j <= panelSize-1; j++) {

            if(plateau[i][j] == player){
                score++;
            }
        }
    }
    return score;
}

/**
 * \brief       Analyse le plateau de jeu et renvoie le statut de la partie en cours
 * \details    Analyse le tableau binaire de la partie, si une case vide est trouvée la partie continue.
 * \return    Un \e bool représentant le statut de la partie, \a true si en cours, \a false s'il faut la  stopper.
 */
bool game::gameNoMorePionChoice(){
    for (int i = 0; i <= panelSize-1; i++) {

        for (int j = 0; j <= panelSize-1; j++) {

            if(plateau[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}



