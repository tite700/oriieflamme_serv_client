#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "carte.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

struct s_node {
    carte value;
    struct s_node *next;
};

typedef struct s_node *node;

/*
Description : Ajouter une carte à la première position
Paramètres : node, correspond à la main d'une faction ou au deck
            carte, la carte qu'il faut ajouter
Retour : void
*/

void push(node *head, carte c);

/*
Description : Renvoi la première carte
Paramètres : node, correspond à la main d'une faction ou au deck
Retour : carte ou NULL si la liste est vide
*/

carte pop(node *head);

/*
Description : Renvoi la taille de la liste chainée
Paramètres : node, correspond à la main d'une faction ou au deck
Retour : un entier
*/
int getSize(node head);

/*
Description : Mélange la liste chainée passée en paramètre
Paramètres : node, correspond à la main d'une faction ou au deck
Retour : void
*/
void shuffle(node *head);

/*
Description : Récupère la n-ième carte
Paramètres : node, correspond à la main d'une faction ou au deck
            int index, l'index de la carte voulue
            int remove, Si à 1 on retire la carte de la liste
                        Sinon on la laisse
Retour : carte ou NULL si la liste est vide
*/
carte getNthCard(node *head, int index, int remove);

/*
Description : Renvoi une carte
Paramètres : plateau, permettant d'accéder au tableau 2D représentant le plateau de jeu
            Tableau de deux entiers qui représente la largeur et la longueur du tableau
            int * coordonnees, tableau d'entier de taille 2 tel que {x, y}
                avec x la position verticale (ligne) et y la position horizontale (colonne)
            int remove, Si à 1 on retire la carte du plateau
                        Sinon on la laisse
Retour : carte ou NULL si l'emplacement est vide
*/
carte getCard(carte **cells, int *taille, int *coordonees, int remove);

/*
Description : Place une carte sur le plateau
Paramètres : plateau, permettant d'accéder au tableau 2D représentant le plateau de jeu
             Tableau de deux entiers qui représente la largeur et la longueur du tableau
             carte, la carte à placer
             int * coordonnes, tableau d'entier de taille 2 tel que {x, y}
                avec x la position verticale (ligne) et y la position horizontale (colonne)
Retour : Un pointeur vers une copie du tableau avec la nouvelle carte
*/
carte **putCard(carte **cells, int *taille, carte c, int *coordonees);

/*
Description : Récupère la liste des cartes qui sont retournées et qui ont le nom passé en paramètre
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente la largeur et la longueur du tableau
             String le nom de la carte recherchée
             visible, Indique si on veut les cartes retournées ou non
             remove, indique si on souhaite retirer la carte du tableau, 1 : Oui, 0 : Non
Retour : liste chainée de carte
*/
node getVisibleCardNamed(carte **cells, int *taille, char *nom, int visible, int remove);

/*
Description : Fusionne deux listes chainées
Paramètres : Deux listes à fusionner
Retour : liste chainée de carte
*/
node mergeNode(node a, node b);

/*
Description : Supprime une ligne du tableau
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente la largeur et la longueur du tableau
             L'indice de la ligne à supprimer
Retour : void
*/
void removeRow(carte **cells, int *taille, int row);

/*
Description : Déplace toutes les cartes vers le bas
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente la largeur et la longueur du tableau
Retour : void
*/
void moveDown(carte **cells, int *taille);

/*
Description : Déplace toutes les cartes vers la droite
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente la largeur et la longueur du tableau
Retour : void
*/
void moveRight(carte **cells, int *taille);

/*
Description : Permet d'adapter la taille du tableau à une nouvelle taille
Paramètres : Tableau 2D représentant la disposition des cartes
             Tableau de deux entiers qui représente l'ancienne largeur, longueur du tableau
             Tableau de deux entiers qui représente la nouvelle largeur, longueur du tableau
Retour : void
*/
carte **grow(carte **old, int *old_taille, int *taille);

/*
Description : Renvoie un entier entre le min et le max passé en paramètre
Paramètres : Entier, borne inférieur
             Entier, borne supérieur
Retour : Entier
*/
int rand_range(int min_n, int max_n);


#endif //STRUCTURE_H



