--------------
ATAXX RELOADED
--------------

Ataxx est un jeu développé par Atari, sorti en 1990, j'ai voulu recréer une version au goût du jour.
Ainsi Ataxx Reloaded est né.


Le jeu :
--------

Par défaut, 2 joueurs s'affrontent sur un plateau carré de 7 cases de côté, 
tour à tour les joueurs choisissent le pion qu'ils veulent jouer puis sa destination, 
le joueur peut se déplacer de 2 cases maximum,
si la case de destination se trouve à 2 cases de celle de départ alors le pion est déplacé sinon il se duplique.


Options de jeu :
--------------
 
Ataxx Reloaded se joue à 2 ou 4 joueurs sur un seul écran.
Les volumes de la musique et des effets sonores sont réglables (0-100).
La taille du plateau de jeu aussi (de 5 à 12 cases de côté).


Améliorations futures :
---------------------

- une version 1 joueur (presque terminé mais pas encore fiable)
- des meilleurs commentaires
- une version console liée à la version graphique
- un mode"mixed"
- un menu pour la version console (avec choix d'options : taille plateau et mode 2/4 joueurs)
- une version en ligne (2 et 4 joueurs)
- création d'obstacle sur le plateau de jeu
- mode 1 joueur contre un bot avec plusieurs niveaux de difficulté


Pour y jouer :
--------------

En version "normal" (graphic) :
- Ouvrir le dossier AtaxxReloaded sur QtCreator avec le fichier Ataxx.pro,
- Puis éxecuter le projet.

Pour la version "console" entrez en argument : --mode console
Par défault : --mode graphic


Liste des fichiers :
--------------------

Ataxx.pro		MakeFile

game.h/.cpp		coeur du jeu
graphicarray.h/.cpp	version graphique
console.h/.cpp		version console	
mainwindow.h/.cpp	class principale générant le visuel et gérant les différentes fenêtres
menu.h/.cpp		class générant la fenêtre du menu/accueil
options.h/.cpp		class générant la fenêtre des options
pion.h/.cpp		class utile à la sauvegarde des coordonnées des pions

resources.qrc		incluant toutes les ressources "img" et "sounds"


Problèmes rencontrés :
----------------------

Découverte des QTableWidget, pas simple à rendre esthétiquement "beau"
Quelques problèmes d'affichage aléatoire lors du passage du mode de jeu 2 joueurs à 4 joueurs et réciproquement.
Version console isolée du reste
