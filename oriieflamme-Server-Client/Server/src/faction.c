#include "../headers/faction.h"
#include <stdlib.h>
#include <stdio.h>


int nbr_carte_pioche() {
    int nb_carte_pioche = 0;
    for (int i = 0; i < NB_CARTE_DIFFERENTES; i++) {
        nb_carte_pioche += nb_occur[i];
    }
    return nb_carte_pioche;
}


void init_pioche_faction(faction f) {
    f->pioche = NULL;
    for (int i = 0; i < NB_CARTE_DIFFERENTES; i++) {
        for (int j = 0; j < nb_occur[i]; j++) {
            carte c = init_carte();
            c->id_faction = f->id;
            c->nom = &nom[i];
            c->description = &description[i];
            push(&f->pioche, c);
        }
    }
}


int deja_repioche(faction f) {
    return (f->a_pioche);
}


void vide(faction f) {
    // int i;
    // for (i=0;i<NB_CARTE_MAIN;i++){
    //     f->main[i]=NULL;
    // }
    for (int i = 0; i < NB_CARTE_MAIN; i++) {
        push(&f->pioche, pop(&f->main));
    }
}

// void affiche_carte(carte c) {
//     if(c==NULL){
//         printf("NULL");
//     }
//     else {
//         printf("%s",c->nom);
//     }
// }

faction init_faction() {
    faction f;
    f = (faction) malloc(sizeof(struct fac));
    f->nom = (char *) malloc(50 * sizeof(char));
    f->main = NULL;
    f->a_pioche=0;
    // f->main=(node)malloc(sizeof(node));
    // f->pioche=(node)malloc(node);
    f->pioche=NULL;
    return f;
}

void free_faction(faction f) {
    while (f->pioche!=NULL){
        carte c1=pop(&f->pioche);
        free_carte(c1);
    }
    while (f->main!=NULL){
        carte c2=pop(&f->main);
        free_carte(c2);
    }
    // free(f->pioche);
    // free(f->main);
    free(f->nom);
    free(f);
}

// int appartient(int tab[],int r){
//     for(int j=0;j<nb_carte_pioche;j++){
//         if (r==tab[j]){
//             return 1;
//         }
//     }
//     return 0;
// }

void melange(faction f) {
    // int r;
    // int tab[47];
    // int k,i;
    // for (i=0;i<47;i++){
    //     tab[i]=-1;
    // }
    // for (i=0;i<47;i++){
    //     r=rand() % 47;
    //     //printf("%i\n",r);
    //     while (appartient(tab,r)==1) {
    //             if (r==46){
    //                 r=0;
    //             }
    //             else {
    //                 r+=1;
    //             }
    //     }
    //     k=0;
    //     while (tab[k]!=-1){
    //         k+=1;
    //     }
    //     tab[k]=r;
    // }
    // for (i=0;i<47;i++){
    //     f->pioche[i]=PIOCHE_JEU[tab[i]];   //PIOCHE_JEU est un tableau des 47 cartes qui est une variable globale
    // }
    shuffle(&f->pioche);
}


void pioche(faction f) {
    for (int i = 0; i < NB_CARTE_MAIN; i++) {
        push(&f->main, pop(&f->pioche));
    }
}


void repiocher(faction f) {
    vide(f);
    init_pioche_faction(f);
    melange(f);
    pioche(f);
    f->a_pioche = 1;
}


int ptns_DDRS(faction f){
    return f->pts_ddrs;
}


void modif_ptns_DDRS(faction f,int pts){
    f->pts_ddrs+=pts;
}


/*int main(){
    faction f=init_faction();
    vide(f);
    // printf("[");
    // for (int i=0;i<8;i++){
    //     affiche_carte(f->main[i]);
    //     printf(" ;");
    // }
    // printf("]\n");
    melange(f);
    free_faction(f);
    return 0;
}*/