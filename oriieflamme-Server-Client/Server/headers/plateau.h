#ifndef PLATEAU_H
#define PLATEAU_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "faction.h"
#include "interface.h"
// #include "carte.h"
// #include "structure.h"




/* crée un type abstrait plateau à partir d'un type concret sruct_plateau qui crée 
    un tableau de taille longueur x larguer de carte, ainsi qu'un tableau contenant les 2 factions  */
struct struct_plateau{
    int * taille;
    carte ** cells;
    faction * tab_factions;
};

typedef struct struct_plateau * plateau;

/*requires: rien
  assigns: rien
  ensures: crée un plateau et les 2 factions et les initialise */
plateau create_plateau_factions();


/*requires: rien
  assigns: p
  ensures: libère la mémoire du plateau et des 2 factions */
void free_plateau(plateau p);

/*requires: rien
  assigns: rien
  ensures: commence une nouvelle manche et renvoie 1 ou renvoie 0 si la partie est terminée  */

  // Il va récupérer le score de chaque faction, en déduire le nombre de manche déjà jouée, 
  // Puis autoriser ou pas le lancement d'une nouvelle manche
int init_manche(plateau p);

/*requires: rien
  assigns: rien
  ensures: renvoie la liste des deux factions du jeu  */
faction* liste_faction(plateau p);

/*requires: le plateau p est un tableau de 2 coordonnées
  assigns: rien
  ensures: vérifie si la carte peut être posée à cet endroit, renvoie 1 si c'est possible et la pose face cachée et renvoie 0 sinon  */
int poser_face_cachee(plateau p,carte carteAJouer,int* coordonnees);

/*requires: rien
  assigns: rien
  ensures: active l'effet de la carte la plus en haut à gauche  */
carte utilise_carte_haut_gauche(plateau p);

/*requires: rien
  assigns: rien
  ensures: recupere la carte la plus en haut à gauche selon si elle a été retournée (retournee == 1) pour l'utiliser pendant la manche (retournee == 0) ou à la fin en cas d'égalité (retournee == 1)
*/
carte cherche_carte_haut_gauche(plateau p, int retournee);

/*requires: rien
  assigns: rien
  ensures: renvoie 1 s'il ya une carte à la position (ligne, colonne) et 0 sinon
*/
int existePositionCarte(plateau p, int* coordonees);

/*requires: rien
  assigns: rien
  ensures: renvoie la carte se trouvant aux coordonnées 'coordonees'
*/
carte carteCoordonnees(plateau p, int* coordonees);

/*requires: rien
  assigns: rien
  ensures: renvoie le nombre de cartes sur le plateau
*/
int nb_carte_plateau(plateau p);


/*requires: rien
  assigns: rien
  ensures: renvoie 1 si la carte aux coordonées 'coordonees' est face retournée sur le plateau, 0 si elle est face cachée et -1 si il n'y a pas de carte
*/
int carteFace(plateau p, int*coordonees);

/*requires: rien
  assigns: rien
  ensures: renvoie le nombre de carte face retournée
*/
int nbCarteRetournee(plateau p);


/*requires: rien
  assigns: rien
  ensures: renvoie le nombre de carte face cachée
*/
int nbCarteCachee(plateau p);

/*requires: rien
  assigns: rien
  ensures: récupère la position de la carte la plus en haut à gauche
*/
int*position_carte_haut_gauche(plateau p);

/*requires: rien
  assigns: rien
  ensures: recupere la position de la carte c
*/
int*position_carte(plateau p, carte c);

/*requires: rien
  assigns: rien
  ensures: recupere le nombre d'occurence de chaque carte sur le plateau
*/
int *nbPaire(plateau p);

/*requires: rien
  assigns: p
  ensures: supprime les cartes de la ligne numérotée l
*/
void supprime_ligne(plateau p, int l);

/*requires: rien
  assigns: p
  ensures: supprime les cartes de la colonne numérotée c
*/
void supprime_colonne(plateau p, int c);

/*requires: rien
  assigns: rien
  ensures: choisit une carte cachée au hasard
*/
carte randomCarteCachee(plateau p);


/*requires: rien
  assigns: p
  ensures: active l'effet de la carte c
*/
void effet_carte(plateau p, carte c);


#endif