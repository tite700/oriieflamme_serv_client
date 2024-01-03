#include "../headers/carte.h"
#include "../headers/structure.h"

//Explique pourquoi pointeurs vers une description ?
carte init_carte() {
    carte c;
    c = (carte) malloc(sizeof(struct p));
    c->retournee = 0;
    return c;
}


void free_carte(carte c) {
    free(c);
}

