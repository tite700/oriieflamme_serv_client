#ifndef INTERFACE_H
#define INTERFACE_H

#include "faction.h"
#include "carte.h"
#include <stdio.h>
#include <ctype.h>
#include "structure.h"

/*
Description : Affiche le plateau sur la console
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente l'ancienne largeur, longueur du tableau
             Entier pour préciser si l'on veut effacer les affichages précédant
Retour : void
*/
void afficherPlateau(carte **cells, int *taille, int clear);


/*
Description : Demande à l'utilisateur d'appuyer sur la touche ENTREE pour continuer
Paramètres : void
Retour : void
*/
void pressToContinue();

/*
Description : Affiche la main de la faction concernée
Paramètres : Faction, va afficher le contenu du tableau main
Retour : void
*/
void afficherMain(faction f);

/*
Description : Affiche la faction victorieuse de la manche en cours
Paramètres : Faction
Retour : void
*/
void afficherVainqueurManche(faction f);

/*
Description : Affiche la faction victorieuse de la partie
Paramètres : Faction
Retour : void
*/
void afficherVainqueurPartie(faction f);

/*
Description : Affiche l'effet de la carte concernée 
Paramètres : carte, en se basant sur le nom et la description
Retour : void
*/
void afficherEffetCarte(carte c);

/*
Description : Demande au joueur de saisir l'emplacement où il souhaite placer sa carte
Paramètres : void
Retour : Renvoi [ligne, colonne] un tableau contentant la colonne à la première case et la ligne à la deuxième
*/
int *demanderPositionCarte();

/*
Description : Demande au joueur la carte qu'il veut jouer 
Paramètres : Faction, on va utiliser la main pour vérifier que le choix est valide avant de le renvoyer
Retour : carte
*/
carte demanderQuelleCarteJouer(faction f);


/*
Paramètres : void
Retour : int -> 1 pour Oui, 0 pour Non
*/
int demanderChangementMain(faction f);

/*
Description : Demande au joueur le nom qu'il souhaite donner à sa faction 
Paramètres : void
Retour : tableau de char
*/
char *demanderNomFaction();

/*
Description : Affiche un message d'erreur au joueur 
Paramètres : Tableau de char
Retour : void
*/
void message_erreur(char *);

/*
Description : Affiche le score des deux factions
Paramètres : Tableau de faction
Retour : void
*/
void afficherScore(faction *factions);

#endif