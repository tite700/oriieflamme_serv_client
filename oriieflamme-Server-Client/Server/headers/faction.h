#ifndef FACTION_H
#define FACTION_H
#include "carte.h"
#include "structure.h"

/*
On cree une structure pour représenter les factions
On stock dans ces structures :  le nom de la faction
                                le nombre de point DDRS de la faction
                                un entier a_pioche qui vaut 0 si la faction n'a pas repiocher et 1 si la faction à repiocher
                                un entier id qui permet de savoir qui a pose quelle carte
                                un tableau de huit cartes que la faction a pioché (les cartes sont déterminées par leur nom)
                                un tableau de cartes de la pioche que la faction peut piocher
                                un entier score_manche qui represente le nombre de manche que la faction a gagne
*/

typedef struct fac *faction;

struct fac {
    char* nom;
    int pts_ddrs;
    int a_pioche;
    int id;
    node main;
    node pioche;    //il y a 47 cartes
    int score_manche;
};


/*
assigns : f->pioche
requires : rien
ensures : remplie la pioche de la faction f sans melanger la pioche
*/
void init_pioche_faction(faction f);


/*
assigns : rien
requires : rien
ensures : reserve l'espace memoire pour une faction
*/
faction init_faction();


/*
assigns : rien
requires : rien
ensures : libere l'espace occupe par la faction f
*/
void free_faction(faction f);

/*
requires : rien
assigns : rien
ensures : renvoie la valeur contenue dans f->a_pioche qui vaut 0 si la faction n'a pas repiocher et 1 si la faction a repioché
*/
int deja_repioche(faction f);



/*
requires : le joueur n a pas deja repiocher (a_picher(f)==0)
assigns : f
ensures : melange la pioche de la faction, vide sa main dans la pioche et repioche 8 cartes et met f->a_piocher=1
*/
void repiocher(faction f);



/*
requires : rien
assigns : f
ensures : met le tableau f.main a : NULL
*/
void vide(faction f);



/*
requires : rien
assigns : f
ensures : melange le tableau de carte f->pioche
*/
void melange(faction f);



/*
requires : rien
assigns : f
ensures : on remplie le tableau f->main de 8 cartes qu'on pioche dans f.pioche (on prend les huits premieres cartes de la pioche qui a ete melangee avant)
*/
void pioche(faction f);



/*
requires : rien
assigns : rien
ensures : on récupère le nombre de points DDRS de la faction f
*/
int ptns_DDRS(faction f);



/*
requires : rien
assigns : f
ensures : on modifie le nombre de points DDRS de la faction f
*/
void modif_ptns_DDRS(faction f,int pts);





#endif
