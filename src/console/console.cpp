#include "../headers/console.h"

/**
 * \brief       Constructeur de la classe console
 */
console::console()
{
}

/**
 * \brief       Destructeur de la classe console
 */
console::~console(){}

/**
 * \brief       Coeur du jeu.
 */
void console::launch(){

        initPlateau();

        placeOnPlateau(1,1,1);
        placeOnPlateau(2,1,7);
        placeOnPlateau(2,7,1);
        placeOnPlateau(1,7,7);

        int nbrepions1 = 2;
        int nbrePions2 = 2;
        bool game = true;

        int choixPions;
        int choixPionsDest;
        int x1,x2,y1,y2;
        cout << "+----------------------------------+" << endl;
        cout << "|  Bienvenue dans Ataxx Reloaded ! |" << endl;
        cout << "+----------------------------------+" << endl;
        AfficherPlateau();
        do{
            nbrepions1 = getScore(1);
            nbrePions2 = getScore(2);
            cout << "Score : O"<< nbrepions1 << " | X" << nbrePions2 << endl;
            cout << "Joueur O a vous de jouer !" << endl;
            do {
                afficherPositionPion(1);
                do{
                cout << "Entrez le pion a jouer :";
                cin >> choixPions;
                x1 = searchOnPlateau(choixPions,1).getX();
                y1 = searchOnPlateau(choixPions,1).getY();
                }while(x1 > 8 || x1 < 1 || y1 < 1 || y1 > 8);
                initCoupsPossible(x1,y1);
                afficherCoupsPossibles();
                cout << "Entrez maintenant la case d'arrivee :";
                cin >> choixPionsDest;
                x2 = searchOnPlateau(choixPionsDest,3).getX();
                y2 = searchOnPlateau(choixPionsDest,3).getY();

            } while (!move(1, x1,y1,x2,y2));
            AfficherPlateau();
            cout << "+-------------------------+" << endl;
            cout << "|    Contammination ...   |" << endl;
            cout << "+-------------------------+" << endl;
            contamine(1,x2,y2);
            AfficherPlateau();
            game = gameStatus(1);

            nbrepions1 = getScore(1);
            nbrePions2 = getScore(2);
            cout << "Score : O"<< nbrepions1 << " | X" << nbrePions2 << endl;
            cout << "Joueur X a vous de jouer !" << endl;

            do {
                afficherPositionPion(2);

                cout << "Entrez le pion a jouer :";
                cin >> choixPions;
                x1 = searchOnPlateau(choixPions,2).getX();
                y1 = searchOnPlateau(choixPions,2).getY();
                initCoupsPossible(x1,y1);
                afficherCoupsPossibles();
                cout << "Entrez maintenant la case d'arrivee :";

                cin >> choixPionsDest;
                x2 = searchOnPlateau(choixPionsDest,3).getX();
                y2 = searchOnPlateau(choixPionsDest,3).getY();

            } while (!move(2, x1, y1, x2, y2));
            AfficherPlateau();
            cout << "Contamination :" << endl;
            contamine(2,x2,y2);
            AfficherPlateau();
            game = gameStatus(2);
        }while(game);

}

/**
 * \brief       Initialise le plateau de jeu.
 */
void console::initPlateau() {
    for (int x = 0; x <= 8; x++) {

        for (int y = 0; y <= 8; y++) {

            if (y == 0 && x == 0) {

                this->plateau[x][y] = 4; // +

            } else if (y == 8 && x == 8) {

                this->plateau[x][y] = 4; // +

            } else if (y == 0 && x == 8) {

                this->plateau[x][y] = 4; // +

            } else if (y == 8 && x == 0) {

                this->plateau[x][y] = 4; // +

            } else if (y == 8 && x > 0 && x < 8) {

            this->plateau[x][y] = 6; // |

            }else if (y == 0 && x > 0 && x < 8) {

            this->plateau[x][y] = 6; // |

            } else if (x == 0 && y > 0 && y < 8) {

                this->plateau[x][y] = 5; // -

            } else if (x == 8 && y > 0 && y < 8) {

                this->plateau[x][y] = 5; // -

            } else {
                this->plateau[x][y] = 0; // .
            }
        }

    }
}

/**
 * \brief       Affiche le plateau de jeu.
 */
void console::AfficherPlateau() {
    for(int x = 0; x<=8; x++){

        for(int y = 0; y<= 8; y++) {
            int cas = plateau[x][y];
            switch (cas){
                    case 0 :
                    cout << ". ";
                    break;

                case 1 :
                    cout << "O ";
                    break;

                case 2 :
                    cout << "X ";
                    break;

                case 3 :
                    cout << "M ";
                    break;

                case 4 :
                    cout << "+";
                    break;

                case 5 :
                    cout << "--";
                    break;

                case 6 :
                    cout << "|";
                    break;
            }

        }
        cout << endl;
    }

}

/**
 * \brief       Place un joueur sur le plateau de jeu
 * \param   player       Le joueur à placer
 * \param    x, y        Case ciblée
 */
void console::placeOnPlateau(int player, int x, int y){
this->plateau[x][y] = player;
}

/**
 * \brief       Place un joueur sur le plateau de jeu
 * \param   Pion       Le pion à placer
 */
void console::placeOnPlateau(Pion p){
    this->plateau[p.getX()][p.getY()] = p.getPlayer();
}


/**
 * \brief       Affiche les coups possibles pour la case (x,y)
 * \details    Analyse toutes les cases à une distance inférieur à 3
 *             de la case choisi et change leur visuel et leur valeur dans le tableau binaire des coups possibles
 * \param    x, y        Case à analyser
 */
void console::initCoupsPossible(int x, int y) {
    //remplissage tab de 0
    for (int x = 0; x <= 8; x++) {
        for (int y = 0; y <= 8; y++) {
            coupsPossibles[x][y] = 0;

        }
    }
    int nbre = 1;
    for(int m = -2; m <= 2; m++){
        for(int n = -2; n <= 2;n++){
            if(x+m <= 8 && y+n <= 8 && x+m >= 0 && y+n >= 0 && plateau[x+m][y+n] == 0){ //plateau[x+m][y+n] == 0 && plateau[x+m][y+n] != 1 && plateau[x+m][y+n] != 2 &&

                coupsPossibles[x+m][y+n] = nbre;
                nbre++;
            }

        }

    }
}

/**
 * \brief       Contamine les pions ennemis autour de la case entrée en argument
 * \details         Analyse si les cases autour de la case (x,y) sont des ennemis
 * \param    player      Le joueur actuel
 * \param    x, y        Case à analyser
 */
void console::contamine(int player, int x, int y) {

    // croix
    if(this->plateau[x+1][y] == player%2+1) {
        this->placeOnPlateau(player, x + 1, y);
    }
    if(this->plateau[x-1][y] == player%2+1) {
        this->placeOnPlateau(player, x - 1, y);
    }
    if(this->plateau[x][y+1] == player%2+1) {
        this->placeOnPlateau(player, x, y+1);
    }
    if(this->plateau[x][y-1] == player%2+1) {
        this->placeOnPlateau(player, x, y-1);
    }

    //cases diagonale de la croix
    if(this->plateau[x+1][y+1] == player%2+1) {
        this->placeOnPlateau(player, x + 1, y+1);
    }
    if(this->plateau[x-1][y-1] == player%2+1) {
        this->placeOnPlateau(player, x - 1, y-1);
    }
    if(this->plateau[x-1][y+1] == player%2+1) {
        this->placeOnPlateau(player, x-1, y+1);
    }
    if(this->plateau[x+1][y-1] == player%2+1) {
        this->placeOnPlateau(player, x+1, y-1);
    }



}

/**
 * \brief       Affiche le plateau avec les pions du joueur en paramètres,
 * \details       Les pions sont numérotés et affichés en fonction du joueur actuel.
 * \param   player      Le joueur à afficher.
 */
void console::afficherPositionPion(int player) {

    int nbre = 1;

    for(int x = 0; x<=8; x++){

        for(int y = 0; y<= 8; y++) {

            int cas = plateau[x][y];
            switch (cas){
                case 0 :
                    cout << " . ";
                    break;

                case 1 :
                    if(player == 1) {
                        cout << " " << nbre << " ";
                        nbre = nbre + 1;
                    }else {
                        cout << " O ";
                    }
                    break;

                case 2 :
                    if(player == 2) {
                        cout << " " << nbre << " ";
                        nbre = nbre + 1;
                    }else {
                        cout << " X ";
                    }
                    break;

                case 3 :
                    cout << " . ";
                    break;

                case 4 :
                    cout << " + ";
                    break;

                case 5 :
                    cout << "---";
                    break;

                case 6 :
                    cout << " | ";
                    break;
            }

        }
        cout << endl;
    }

}

/**
 * \brief       Affiche le plateau avec les coups possibles pour le pion choisi,
 * \details         Les pions sont numérotés par l'intermédiaire de la fonction initCoupsPossibles()
 */
void console::afficherCoupsPossibles(){


    for(int x = 0; x<=8; x++){

        for(int y = 0; y<= 8; y++) {

            int cas = plateau[x][y];
            switch (cas){
                case 0 :
                    if(coupsPossibles[x][y] > 0){
                        if(coupsPossibles[x][y] < 10)cout << " " << coupsPossibles[x][y] << " ";
                        if(coupsPossibles[x][y] >= 10)cout << coupsPossibles[x][y] << " ";

                    }else {
                        cout << " . ";
                    }
                    break;

                case 1 :
                    if(coupsPossibles[x][y] > 0){
                        cout << "  " << coupsPossibles[x][y] << "  ";

                    }else {
                        cout << " O ";
                    }
                    break;

                case 2 :
                    if(coupsPossibles[x][y] > 0){
                        cout << "  " << coupsPossibles[x][y] << "  ";

                    }else {
                        cout << " X ";
                    }
                    break;

                case 3 :
                    cout << "M";
                    break;

                case 4 :
                    cout << " + ";
                    break;

                case 5 :
                    cout << "---";
                    break;

                case 6 :
                    cout << " | ";
                    break;
            }

        }
        cout << endl;
    }

}

/**
 * \brief       Vérifie la nature du déplacement et l'effectue (1 ou 2 cases)
 * \details    La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points.
 * \param    x1, y1         Point 1 pour le calcul de distance.
 * \param    x2, y2         Point 2 pour le calcul de distance.
 * \return    Un \e bool, \a false si le déplacement est supérieur à 2, \a true autrement.
 */
bool console::move(int player, int x1, int y1, int x2, int y2) {

    //SI le pion existe
    if(this->plateau[x1][y1] != player) {
        cout << "Pas de pion !";
        return false;
    }

    if(this->plateau[x1][y1] == player ) {
        //SI déplacement <3 cases AB = racine carré (xb - xa)^2 + (yb-ya)^2
        int x = int(pow(x2 - x1, 2));
        int y = int(pow(y2 - y1, 2));
        int result = int(sqrt(x + y));
        if (result < 2) {
            plateau[x2][y2] = player;
            return true;
        } else if (result >= 2 && result < 3) {
            plateau[x1][y1] = 0;
            plateau[x2][y2] = player;
            return true;
        } else {
            cout << "Beaucoup trop loin ! Réessaye" << endl;
            return false;
        }
    }

    return false;
}

/**
 * \brief       Recherche le pion à jouer par l'intermédiaire du tableau de position des pions
 * \param    pion         pion, le numéro du pion choisi par le joueur.
 * \param    player       player, le joueur actuel.
 * \return    Un \e Pion, avec les coordonnées du pion à jouer.
 */
Pion console::searchOnPlateau(int pion, int player) {

    Pion pionsToPlay;
    initPositionPions();
    for(int x = 0; x<=8; x++){
      for(int y = 0; y<= 8; y++) {

            if(player == 1){
                if(positionsPions1[x][y] == pion){

                    pionsToPlay.setPions(1,x,y);
                    return pionsToPlay;
                }
            }

          if(player == 2){
              if(positionsPions2[x][y] == pion){

                  pionsToPlay.setPions(2,x,y);
                  return pionsToPlay;
              }
          }

          if(player == 3){
              if(coupsPossibles[x][y] == pion){
                  pionsToPlay.setPions(3,x,y);
                  return pionsToPlay;
              }
          }


        }

    }

        pionsToPlay.setPions(player,1000,1000);
        cout << "erreur." << endl;
        return pionsToPlay;

}


/**
 * \brief       Initialise le tableau de position des pions,
 *                  utilisé pour faciliter le choix du pion à jouer.
 */
void console::initPositionPions() {

    int nbre1 = 1;
    int nbre2 = 1;

    for(int x = 0; x<=8; x++){

        for(int y = 0; y<= 8; y++) {

            int cas = plateau[x][y];
            switch (cas){


                case 1 :

                positionsPions1[x][y] = nbre1;
                    positionsPions2[x][y] = 0;
                nbre1 = nbre1 + 1;


                    break;

                case 2 :
                    positionsPions2[x][y] = nbre2;
                    positionsPions1[x][y] = 0;
                    nbre2 = nbre2 + 1;

                    break;



                default:
                    positionsPions1[x][y] = 0;
                    positionsPions2[x][y] = 0;
                    break;
            }

        }

    }
}

/**
 * \brief       Vérifie l'état de la partie en cours
 * \details    Analyse le tableau binaire de la partie et vérifie si le joueur en paramètre
 *                  à encore un pion. Génère aussi le message de fin de partie.
 * \param    player         player, le joueur à analyser.
 * \return    Un \e bool représentant l'état de la partie.
 */
bool console::gameStatus(int player){

    for(int x = 0; x<=8; x++){
        for(int y = 0; y<= 8; y++) {

            if(player == 1){
                if(plateau[x][y] == 2){

                    return true;
                }
            }
            if(player == 2){
                if (plateau[x][y] == 1) {

                    return true;
                }
            }


        }
    }
    if(player == 2)cout << "Joueur O remporte la partie !";
    if(player == 1)cout << "Joueur X remporte la partie !";
    return false;
}

/**
 * \brief       Calcule le score du joueur demandé
 * \details    Analyse le tableau binaire de la partie et compte le nombre de case du joueur en paramètre
 * \param    player         player, le joueur à analyser.
 * \return    Un \e int représentant le score du joueur demandé.
 */
int console::getScore(int player){
    int score = 0;

    for (int i = 0; i <= 8; i++) {

        for (int j = 0; j <= 8; j++) {

            if(plateau[i][j] == player){
                score++;
            }
        }
    }
    return score;
}
