--------------
ATAXX RELOADED
--------------

Ataxx est un jeu d�velopp� par Atari, sorti en 1990, j'ai voulu recr�er une version au go�t du jour.
Ainsi Ataxx Reloaded est n�.


Le jeu :
--------

Par d�faut, 2 joueurs s'affrontent sur un plateau carr� de 7 cases de c�t�, 
tour � tour les joueurs choisissent le pion qu'ils veulent jouer puis sa destination, 
le joueur peut se d�placer de 2 cases maximum,
si la case de destination se trouve � 2 cases de celle de d�part alors le pion est d�plac� sinon il se duplique.


Options de jeu :
--------------
 
Ataxx Reloaded se joue � 2 ou 4 joueurs sur un seul �cran.
Les volumes de la musique et des effets sonores sont r�glables (0-100).
La taille du plateau de jeu aussi (de 5 � 12 cases de c�t�).


Am�liorations futures :
---------------------

- une version 1 joueur (presque termin� mais pas encore fiable)
- des meilleurs commentaires
- une version console li�e � la version graphique
- un mode"mixed"
- un menu pour la version console (avec choix d'options : taille plateau et mode 2/4 joueurs)
- une version en ligne (2 et 4 joueurs)
- cr�ation d'obstacle sur le plateau de jeu
- mode 1 joueur contre un bot avec plusieurs niveaux de difficult�


Pour y jouer :
--------------

En version "normal" (graphic) :
- Ouvrir le dossier AtaxxReloaded sur QtCreator avec le fichier Ataxx.pro,
- Puis �xecuter le projet.

Pour la version "console" entrez en argument : --mode console
Par d�fault : --mode graphic


Liste des fichiers :
--------------------

Ataxx.pro		MakeFile

game.h/.cpp		coeur du jeu
graphicarray.h/.cpp	version graphique
console.h/.cpp		version console	
mainwindow.h/.cpp	class principale g�n�rant le visuel et g�rant les diff�rentes fen�tres
menu.h/.cpp		class g�n�rant la fen�tre du menu/accueil
options.h/.cpp		class g�n�rant la fen�tre des options
pion.h/.cpp		class utile � la sauvegarde des coordonn�es des pions

resources.qrc		incluant toutes les ressources "img" et "sounds"


Probl�mes rencontr�s :
----------------------

D�couverte des QTableWidget, pas simple � rendre esth�tiquement "beau"
Quelques probl�mes d'affichage al�atoire lors du passage du mode de jeu 2 joueurs � 4 joueurs et r�ciproquement.
Version console isol�e du reste
