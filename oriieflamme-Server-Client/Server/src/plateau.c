#include "../headers/plateau.h"
// #include "../headers/faction.h"
// #include "../headers/carte.h"
// #include "../headers/structure.h"



plateau create_plateau_factions() {
    srand(time(NULL));
    plateau p;
    p = (plateau) malloc(sizeof(struct struct_plateau));
    p->taille = (int *) malloc(2 * sizeof(int));
    p->tab_factions = (faction *) malloc(NB_FACTIONS * sizeof(faction));
    for (int i = 0; i < NB_FACTIONS; i++) {
        p->tab_factions[i] = init_faction();
        p->tab_factions[i]->id=i;
        p->tab_factions[i]->score_manche=0;
    }
    p->cells = (carte **) malloc(sizeof(carte *));
    p->cells[0] = (carte *) malloc(sizeof(carte));
    p->taille[0] = 1;
    p->taille[1] = 1;
    for (int row = 0; row < p->taille[0]; row++) {
        for (int col = 0; col < p->taille[1]; col++) {
            p->cells[row][col] = NULL;
        }
    }
    return p;
}


void free_plateau(plateau p) {
    for (int i = 0; i < NB_FACTIONS; i++) {
        free_faction(p->tab_factions[i]);
    }
    free(p->tab_factions);    
    for (int i = 0; i < p->taille[0]; i++) {
        free(p->cells[i]);
    }
    free(p->cells);
    free(p->taille);
    free(p);
}


int init_manche(plateau p) {
    for (int i = 0; i < NB_FACTIONS; i++) {
        if (p->tab_factions[i]->score_manche == NB_MANCHE_GAGNANTE) {
            // afficherVainqueurPartie(p->tab_factions[i]);
            return 0;
        }
    }
    for (int i = 0; i < NB_FACTIONS; i++) {
        p->tab_factions[i]->pts_ddrs = 0;
        init_pioche_faction(p->tab_factions[i]);
        melange(p->tab_factions[i]);
        // pioche(p->tab_factions[i]);
    }
    p->cells = (carte **) realloc(p->cells, sizeof(carte *));
    p->cells[0] = (carte *) realloc(p->cells[0], sizeof(carte));
    p->taille[0] = 1;
    p->taille[1] = 1;


    for (int row = 0; row < p->taille[0]; row++) {
        for (int col = 0; col < p->taille[1]; col++) {
            p->cells[row][col] = NULL;
        }
    }

    return 1;
}


faction *liste_faction(plateau p) {
    return (p->tab_factions);
}

// int putCard(carte ** cells,int * taille, carte c, int * coordonees);

int poser_face_cachee(plateau p, carte carteAJouer, int *coordonnees) {
    
        // if (p->taille[0]==1 && p->taille[1]==1){
        //     if (coordonnees[0]==0 && coordonnees[1]==0){
        //         carteAJouer->retournee = 0;
        //         carte ** temp = putCard(p->cells, p->taille, carteAJouer, coordonnees);
        //         if (temp==NULL){
        //             return 0;
        //         }
        //         return 1;
        //     }
        //     else {
        //         return 0;
        //     }
        // }
        // else {
        //     if (coordonnees[0]==0) {
        //         //coin haut gauche
        //         if (coordonnees[1]==0){
        //             if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //                 return 0;
        //             }
        //         }
        //         //coin haut droit
        //         else if (coordonnees[1]==p->taille[1]-1){
        //             if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL){
        //                 return 0;
        //             }
        //         }
        //         //ligne du haut
        //         else if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //             return 0;
        //         }
        //     }

        //     else if (coordonnees[0]==p->taille[0]-1) {
        //         //coin bas gauche
        //         if (coordonnees[1]==0){
        //             if (getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //                 return 0;
        //             }
        //         }
        //         //coin bas droit
        //         else if (coordonnees[1]==p->taille[1]-1){
        //             if (getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL){
        //                 return 0;
        //             }
        //         }
        //         //ligne du bas
        //         else if (getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //             return 0;
        //         }
        //     }
        //     //colonne de gauche
        //     else if (coordonnees[1]==0){
        //         if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //             return 0;
        //         }
        //     }
        //     //colonne de droite
        //     else if (coordonnees[1]==p->taille[1]-1){
        //         if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL){
        //             return 0;
        //         }
        //     }
        //     else {
        //         if (getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL){
        //             return 0;
        //         }
        //     }

    // int nb_carte_posee = getSize(getVisibleCardNamed(p->cells, p->taille, "*", 0, 0));

    // printf("nb carte : %d\n", nb_carte_posee);



    if (p->taille[0]==1){
        if (coordonnees[0]==0 && coordonnees[1]==0){
            carteAJouer->retournee = 0;
            carte ** temp = putCard(p->cells, p->taille, carteAJouer, coordonnees);
            if (temp==NULL){
                free(coordonnees);
                return 0;
            }
            p->cells=temp;
            free(coordonnees);
            return 1;
        }
        else {
            free(coordonnees);
            return 0;
        }
    }
    else {
            if ( //nb_carte_posee != 0 
                getCard(p->cells,p->taille,(int []) {coordonnees[0]+1,coordonnees[1]},0)==NULL 
                && getCard(p->cells,p->taille,(int []) {coordonnees[0]-1,coordonnees[1]},0)==NULL 
                && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]+1},0)==NULL 
                && getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]-1},0)==NULL) {
                free(coordonnees);
                return 0;
            }
            else {
                carteAJouer->retournee = 0;
                carte ** temp = putCard(p->cells, p->taille, carteAJouer, coordonnees);
                if (temp==NULL){
                    free(coordonnees);
                    return 0;
                }
                p->cells = temp;
                free(coordonnees);
                return 1;
            // }
        }
    }
    
}


carte utilise_carte_haut_gauche(plateau p) {
    carte c = cherche_carte_haut_gauche(p, 0);
    if (c!=NULL){
        c->retournee = 1;
        effet_carte(p, c);
    }
    return c;
}

carte cherche_carte_haut_gauche(plateau p, int retournee) {
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) != NULL &&
                getCard(p->cells, p->taille, (int[]) {i, j}, 0)->retournee == retournee) { // si la carte existe et est retournée ou cachée selon l'argument de la fonction, on renvoit la carte
                return (getCard(p->cells, p->taille, (int[]) {i, j}, 0));
            }
        }
    }
    return NULL;
}


int existePositionCarte(plateau p, int *coordonnees) {
    carte C = getCard(p->cells,p->taille,(int []) {coordonnees[0],coordonnees[1]},0);
    if (C != NULL) { // s'il y a une carte on renvoit le booléen 1
        return 1;
    } else {    // 0 sinon
        return 0;
    }
}


carte carteCoordonnees(plateau p, int *coordonees) {
    carte C = getCard(p->cells,p->taille,(int []) {coordonees[0],coordonees[1]},0);
    return C; //retourne la carte à la position 'coordonees' (qui peut être null)
}


int nb_carte_plateau(plateau p) {
    int nb = 0;
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) != NULL) { // s'il y a une carte, on ajoute 1 au compteur
                nb += 1;
            }
        }
    }
    return nb;
}


int carteFace(plateau p, int *coordonees) {
    int i = coordonees[0];
    int j = coordonees[1];
    carte temp = getCard(p->cells, p->taille, (int[]) {i, j}, 0);
    if (temp == NULL) { //l'entier -1 correspond au cas 'pas de carte'
        return -1;
    } else {
        return temp->retournee; // on renvoie l'entier correspondant à face retournée ou cachée
    }
}


int nbCarteRetournee(plateau p) {
    int nb = 0;
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) != NULL &&
                getCard(p->cells, p->taille, (int[]) {i, j}, 0)->retournee == 1) { // si la carte existe et est retournée, on ajoute 1 au compteur
                nb += 1;
            }
        }
    }
    return nb;
}


int nbCarteCachee(plateau p) {
    int nb = 0;
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) != NULL &&
                getCard(p->cells, p->taille, (int[]) {i, j}, 0)->retournee == 0) { // si la carte existe et est face cachée, on ajoute 1 au compteur
                nb += 1;
            }
        }
    }
    return nb;
}



int *position_carte_haut_gauche(plateau p) {
    int *tab = malloc(sizeof(int) * 2);
    tab[0] = -1;
    tab[1] = -1;
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) != NULL) {
                tab[0] = i;
                tab[1] = j;
                return tab; // renvoie la position de la carte la plusen haut à gauche
            }
        }
    }

    return tab; // ce cas correspond au fait qu'il n'y ait aucune carte
}


int *position_carte(plateau p, carte c) {
    int *tab = malloc(sizeof(int) * 2);
    tab[0] = -1;
    tab[1] = -1;
    for (int i = 0; i < p->taille[0]; i++) {
        for (int j = 0; j < p->taille[1]; j++) {
            if (getCard(p->cells, p->taille, (int[]) {i, j}, 0) == c) { 
                tab[0] = i;
                tab[1] = j;
                return tab; // renvoie la position de la carte c
            }
        }
    }
    return tab; // ce cas correspond au fait qu'il n'y ait pas la carte c dans le plateau
}


int *nbPaire(plateau p){ //on rajoute le nombre d'occurence de chaque carte dans le tableau
    int *paire = malloc(sizeof(int) * 32);
    int nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Fise",1,0));
    paire[0] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Fisa",1,0));
    paire[1] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Fc",1,0));
    paire[2] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Ecologiie",1,0));
    paire[3] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Liiens",1,0));
    paire[4] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Soirée sans alcool",1,0));
    paire[5] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Alcool",1,0));
    paire[6] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Café",1,0));
    paire[7] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Thé",1,0));
    paire[8] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Ecocup",1,0));
    paire[9] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Reprographie",1,0));
    paire[10] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Isolation du bâtiment",1,0));
    paire[11] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Parcours sobriété numérique",1,0));
    paire[12] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Heures supplémentaires",1,0));
    paire[13] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Kahina Bouchama",1,0));
    paire[14] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Kevin Goilard",1,0));
    paire[15] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Massinissa Merabet",1,0));
    paire[16] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Vitéra Y",1,0));
    paire[17] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Jonas Senizergues",1,0));
    paire[18] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Fetia Bannour",1,0));
    paire[19] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Catherine Dubois",1,0));
    paire[20] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Anne-Laure Ligozat",1,0));
    paire[21] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Guillaume Burel",1,0));
    paire[22] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Christophe Mouilleron",1,0));
    paire[23] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Thomas Lim",1,0));
    paire[24] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Julien Forest",1,0));
    paire[25] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Dimitri Watel",1,0));
    paire[26] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Djibril-Aurélien Dembele-Cabot",1,0));
    paire[27] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Eric Lejeune",1,0));
    paire[28] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Lucienne Pacavé",1,0));
    paire[29] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Katrin Salhab",1,0));
    paire[30] = nb;
    nb = getSize(getVisibleCardNamed(p->cells,p->taille,"Laurent Prével",1,0));
    paire[31] = nb;
    return paire;
}

void supprime_ligne(plateau p, int l) {
    for (int j = 0; j < p->taille[1]; j++) {
        getCard(p->cells, p->taille, (int[]) {l, j}, 1); // supprime toutes les cartes de la ligne
    }
}


void supprime_colonne(plateau p, int c) {
    for (int i = 0; i < p->taille[0]; i++) {
        getCard(p->cells, p->taille, (int[]) {i, c}, 1); // supprime toutes les cartes de la colonne
    }
}


carte randomCarteCachee(plateau p) {
    int n = nbCarteCachee(p);
    int random = rand_range(1, n);
    node cachee = NULL;
    carte temp;
    int *taille = p->taille;
    for (int i = 0; i < taille[0]; i++) {
        for (int j = 0; j < taille[1]; j++) {
            if (existePositionCarte(p, (int[]) {i, j}) && carteFace(p, (int[]) {i, j}) == 0) {
                temp = p->cells[i][j];
                push(&cachee, temp); //on remplit un node avec toutes les cartes face cachée
            }
        }
    }
    shuffle(&cachee); // on mélange le node
    carte finale;
    while (random > 0) {
        finale = pop(&cachee); // on vient chercher notre carte au hasard grâce à l'entier 'random'
        random--;
    }
    return finale;
}


void effet_Fise(plateau p, carte c) {
    int id = c->id_faction;
    p->tab_factions[id]->pts_ddrs++; // on rajoute 1 point ddrs à la faction
}

void effet_Fisa(plateau p, carte c) {
    node temp = getVisibleCardNamed(p->cells, p->taille, "*",1,0);
    int nb = getSize(temp);
    if (nb % 2 == 0) {  // si le nombre de carte est pair
        int id = c->id_faction;
        p->tab_factions[id]->pts_ddrs += 2; // on rajoute 2 points ddrs à la faction
    }
}

void effet_Fc(plateau p, carte c) {
    int id = c->id_faction;
    node fc = getVisibleCardNamed(p->cells, p->taille, "Fc",1,0);
    int nb = getSize(fc); //nombre de carte Fc dans le plateau
    if (nb > 1) { //s'il y a une autre carte Fc
        p->tab_factions[id]->pts_ddrs += 4; // on rajoute 4 points ddrs à la faction
    }
}

void effet_Ecologiie(plateau p, carte c) {
    int id = c->id_faction;
    node fise = getVisibleCardNamed(p->cells, p->taille, "Fise",1,0);
    int nb_fise = getSize(fise);
    node fisa = getVisibleCardNamed(p->cells, p->taille, "Fisa",1,0);
    int nb_fisa = getSize(fisa);
    node fc = getVisibleCardNamed(p->cells, p->taille, "Fc",1,0);
    int nb_fc = getSize(fc);
    p->tab_factions[id]->pts_ddrs += (nb_fise + nb_fisa + nb_fc); // on compte le nombre de carte Fise, Fisa et Fc retournées et on rajoute ce nombre de points ddrs à la faction 
}

void effet_Liiens(plateau p) {
    node fise = getVisibleCardNamed(p->cells, p->taille, "Fise",1,1);
    node fisa = getVisibleCardNamed(p->cells, p->taille, "Fisa",1,1);
    node fc = getVisibleCardNamed(p->cells, p->taille, "Fc",1,1);
    node merged = mergeNode(fise, mergeNode(fisa, fc)); // on crée un node avec toutes les cartes Fise, Fisa et Fc retournées 
    shuffle(&merged); // on mélange
    while (merged != NULL) {
        int *pos = position_carte_haut_gauche(p);
        pos[1]-=1;
        carte temp = pop(&merged);
        poser_face_cachee(p, temp, pos); // on les pose une par une à gauche de la carte la plus en haut à gauche
        temp->retournee = 1; // on les retourne
    }
}

void effet_Soiree_sans_alcool(plateau p, carte c) {
    int *taille = p->taille;
    if (getVisibleCardNamed(p->cells, p->taille, "Alcool",1,0) != NULL) { // s'il y a une carte Alcool retournée sur le plateau
        getVisibleCardNamed(p->cells, p->taille, "Fise",1,1);
        getVisibleCardNamed(p->cells, p->taille, "Fisa",1,1);
        getVisibleCardNamed(p->cells, p->taille, "Fc",1,1);     // on supprime toutes les cartes Fise, Fisa et Fc retournées
        removeRow(p->cells, p->taille, 1);
        removeRow(p->cells, p->taille, taille[0] - 2);  // on supprime la 1e et la dernière ligne
    }
    else {
        int id = c->id_faction;
        p->tab_factions[id]->pts_ddrs += 5; // sinon, on rajoute 5 points ddrs à la faction
    }
}

void effet_Alcool(plateau p, carte c) {
    int *pos = position_carte(p, c);
    getCard(p->cells, p->taille,(int []) {pos[0],pos[1]+1}, 1);
    getCard(p->cells, p->taille,(int []) {pos[0],pos[1]-1}, 1);
    getCard(p->cells, p->taille,(int []) {pos[0]+1,pos[1]}, 1);
    getCard(p->cells, p->taille,(int []) {pos[0]-1,pos[1]}, 1); // on supprime les cartes autour de Alcool
    free(pos);
}

void effet_Cafe(plateau p, carte c) {
    getVisibleCardNamed(p->cells, p->taille, "Thé",1,1);    
    getVisibleCardNamed(p->cells, p->taille, "Alcool",1,1); // on supprime toutes les cartes Thé et Alcool retournées
    int id = c->id_faction;
    if (getVisibleCardNamed(p->cells, p->taille, "Ecocup",1,0) == NULL) {   // s'il y a une carte Ecocup retournée, on rajoute 1 point ddrs, sinon on en enlève 1 à la faction
        p->tab_factions[id]->pts_ddrs--;
    }
    else {
        p->tab_factions[id]->pts_ddrs++;
    }
}

void effet_The(plateau p, carte c) {
    getVisibleCardNamed(p->cells, p->taille, "Café", 1, 1);
    getVisibleCardNamed(p->cells, p->taille, "Alcool", 1, 1); // on supprime toutes les cartes Café et Alcool retournées
    int id = c->id_faction;
    if (getVisibleCardNamed(p->cells, p->taille, "Ecocup",1,0) == NULL) {   // s'il y a une carte Ecocup retournée, on rajoute 1 point ddrs, sinon on en enlève 1 à la faction
        p->tab_factions[id]->pts_ddrs--;
    }
    else {
        p->tab_factions[id]->pts_ddrs++;
    }
}

void effet_Reprographie(plateau p, carte c) {
    int *paire = nbPaire(p);
    int id = c->id_faction;
    for (int i = 0; i < 32; i++){
        if (paire[i] % 2 == 0){
            int pts_perdu = (paire[i] / 2);
            p->tab_factions[1-id]->pts_ddrs-=pts_perdu; // on enlève le nombre de paires de chaque carte en points ddrs si le nombre cartes est paire
        }
        else{
            if (paire[i] == 3){
                p->tab_factions[1-id]->pts_ddrs-=3; // pour le cas 3 cartes identiques, on enlève 3 points dds
            }
            else{
                int pts_perdu = ((paire[i]-1) / 2);
                p->tab_factions[1-id]->pts_ddrs-=pts_perdu; // si le nombre de cartes est impair, on enlève le nombre de cartes moins 1 diviser par 2 en points ddrs
            }
        }
    }
    free(paire);
}

void effet_Isolation_du_batiment(plateau p) {
    int pos[2];
    int *taille = p->taille;
    for (int i = 0; i < taille[0]; i++) {
        for (int j = 0; j < taille[1]; j++) {
            pos[0] = i;
            pos[1] = j;
            if (existePositionCarte(p, pos)) {
                carte C = carteCoordonnees(p, pos);
                int id = C->id_faction;
                if (carteFace(p, pos) == 0) { //s'il y aune carte face cachée et que cette carte appartient à la faction, on rajoute 1 point ddrs
                    p->tab_factions[id]->pts_ddrs++;
                }
            }
        }
    }
}

void effet_Parcous_sobriete_numerique(plateau p) {
    int pos[2];
    int *taille = p->taille;
    for (int i = 0; i < taille[0]; i++) {
        int j = 0;
        while (j >= 0 && j <= taille[1]-1) {
            pos[0] = i;
            pos[1] = j;
            if (existePositionCarte(p, pos) && carteFace(p, pos) == 0) { // on ne retourne que la 1e carte face cachée de la ligne
                carte temp = getCard(p->cells,p->taille,pos,0);
                temp->retournee = 1;
                j = -10;    // on force la sortie du while
            }
            j++;
        }
        int k = taille[1] - 1;
        while (k >= 0) {
            pos[0] = i;
            pos[1] = k;
            if (existePositionCarte(p, pos) && carteFace(p, pos) == 0) { // on ne retourne que la dernière carte face cachée de la ligne
                carte temp = getCard(p->cells,p->taille,pos,0);
                temp->retournee = 1;
                k = -10;    // on force la sortie du while
            }
            k--;
        }
    }
}

void effet_Heures_supplementaires(plateau p, carte c) {
    node heures = getVisibleCardNamed(p->cells, p->taille, "Heures supplémentaires",1,0);
    int nb = 3*getSize(heures); // on a le nombre de cartes 'Heures supplémentaires' sur la plateau
    int id = c->id_faction;
    p->tab_factions[1 - id]->pts_ddrs -= nb; // on enlève 3 fois le nombre de cartes 'Heures suppémentaires' en points ddrs à la faction
}

void effet_Kahina_Bouchama(plateau p) {
    carte C = randomCarteCachee(p);
    int *coordonees = position_carte(p, C);
    getCard(p->cells, p->taille, coordonees, 1); // on supprime une carte face cachée au hasard
    free(coordonees);
}

void effet_Kevin_Goilard(plateau p, carte c) {
    int n1 = nb_carte_plateau(p);
    int *taille = p->taille;
    int n = rand_range(1,taille[0]-1);
    removeRow(p->cells, p->taille, n);
    int n2 = n1 - nb_carte_plateau(p); // on compare le nombre de carte sur le plateau avant et après avoir supprimé une ligne
    int id = c->id_faction;
    p->tab_factions[id]->pts_ddrs += 2 * n2; // on ajoute 2 fois la différence de nombre de cartes en points ddrs à la faction
}

void effet_Massinissa_Merabet(plateau p, carte c) {
    int *taille = p->taille;
    carte massinissa = c;
    int *coordonnees = position_carte(p,massinissa);
    int id = c->id_faction;
    for (int k = coordonnees[1]-1; k >= 0; k--){
        if (existePositionCarte(p,(int []) {coordonnees[0],k})){  // on remonte le tableau à partir de la carte 'Massinissa Merabet' pour chercher la dernière carte retournée
                carte C = getCard(p->cells,p->taille,(int []) {coordonnees[0],k},0);
                C->id_faction = id;
                effet_carte(p,C); // on active l'effet
                return;
        }
    }
    for (int i = coordonnees[0]-1; i >= 0; i--) {
        for (int j = taille[1]-1; j >= 0; j--) { // si la dernière carte retournée n'est pas sur la même ligne que la carte c, on continue à remonter le tableau
            if (existePositionCarte(p,(int []) {i,j})){
                carte C = getCard(p->cells,p->taille,(int []) {i,j},0);
                C->id_faction = id;
                effet_carte(p,C); // on active l'effet
                return;
            }
        }
    }
    free(coordonnees);
}

void effet_Vitera_Y(plateau p, carte c) {
    int id = c->id_faction;
    if (p->tab_factions[id]->pts_ddrs > p->tab_factions[1 - id]->pts_ddrs) {    // on compare les points ddrs pour que la faction qui a strictement moins de points gagne 3 points ddrs
        p->tab_factions[1 - id]->pts_ddrs += 3;
    } else if (p->tab_factions[id]->pts_ddrs < p->tab_factions[1 - id]->pts_ddrs) {
        p->tab_factions[id]->pts_ddrs += 3;
    }
}

void effet_Jonas_Senizergues(plateau p) { 
    getVisibleCardNamed(p->cells, p->taille, "Heures supplémentaires",1,1); // on supprime toutes les cartes 'Heures supplémentaires'
}



void effet_Fetia_Bannour(plateau p, carte c) {
    if (getVisibleCardNamed(p->cells, p->taille, "Heures supplémentaires",1,0) != NULL) {   // s'il y a au moins une carte 'Heures suppléméntaires'
        int *pos = position_carte(p,c);
        supprime_colonne(p, pos[1]);
        supprime_ligne(p, pos[0]);  // on supprime les cartes de la ligne et de la colonne de la carte c
        free(pos);
    }
    else {
        node dubois = getVisibleCardNamed(p->cells, p->taille, "Catherine Dubois",1,0);
        node ligozat = getVisibleCardNamed(p->cells, p->taille, "Anne-Laure Ligozat",1,0);
        node burel = getVisibleCardNamed(p->cells, p->taille, "Guillaume Burel",1,0);
        node mouilleron = getVisibleCardNamed(p->cells, p->taille, "Christophe Mouilleron",1,0);
        node lim = getVisibleCardNamed(p->cells, p->taille, "Thomas Lim",1,0);
        node forest = getVisibleCardNamed(p->cells, p->taille, "Julien Forest",1,0);
        node watel = getVisibleCardNamed(p->cells, p->taille, "Dimitri Watel",1,0);
        int nb = getSize(dubois) + getSize(ligozat) + getSize(burel) + getSize(mouilleron) + getSize(lim) + getSize(forest) + getSize(watel); // on a le nombre des cartes retorunées données ci-dessus
        int id = c->id_faction;
        p->tab_factions[id]->pts_ddrs += nb; // on rajoute le nombre de cartes en points ddrs à la faction
    }
}

void effet_Catherine_Dubois(plateau p, carte c) {
    int *taille = p->taille;
    int *pos = position_carte(p,c);
    int j = 0;
    while (j <= taille[1] - 1) { // on cherche seulement la première carte de la ligne pour la supprimer
        if (existePositionCarte(p, (int[]) {pos[0], j})) {
            getCard(p->cells, p->taille, (int[]) {pos[0], j}, 1);
            j = taille[1];
        }
        j++;
    }
    j = taille[1] - 1;
    while (j >= 0) {
        if (existePositionCarte(p, (int[]) {pos[0], j})) { // on cherche seulement la dernière carte de la ligne pour la supprimer
            getCard(p->cells, p->taille, (int[]) {pos[0], j}, 1);
            j = -1;
        }
        j--;
    }
    int k = 0;
    while (k <= taille[0] - 1) { // on cherche seulement la première carte de la colonne pour la supprimer
        if (existePositionCarte(p, (int[]) {k, pos[1]})) {
            getCard(p->cells, p->taille, (int[]) {k, pos[1]}, 1);
            k = taille[0];
        }
        k++;
    }
    k = taille[0] - 1;
    while (k >= 0) {
        if (existePositionCarte(p, (int[]) {k, pos[1]})) { // on cherche seulement la dernière carte de la colonne pour la supprimer
            getCard(p->cells, p->taille, (int[]) {k, pos[1]}, 1);
            k = -1;
        }
        k--;
    }
    free(pos);
}

void effet_Anne_Laure_Ligozat(plateau p, carte c) {
    node ecologiie = getVisibleCardNamed(p->cells, p->taille, "Ecologiie",1,0);
    int nb_ecologiie = getSize(ecologiie);
    node ecocup = getVisibleCardNamed(p->cells, p->taille, "Ecocup",1,0);
    int nb_ecocup = getSize(ecocup);
    node isolation = getVisibleCardNamed(p->cells, p->taille, "Isolation du bâtiment",1,0);
    int nb_isolation = getSize(isolation);
    node parcours = getVisibleCardNamed(p->cells, p->taille, "Parcours sobriété numérique",1,0);
    int nb_parcours = getSize(parcours);
    int nb = 3 * (nb_ecologiie + nb_ecocup + nb_isolation + nb_parcours); // on prend 3 fois le nombre de cartes retournées citées ci-dessus
    int id = c->id_faction;
    p->tab_factions[id]->pts_ddrs += nb; // on rajoute ce nombre en points ddrs à la faction
    int *taille = p->taille;
    for (int i = taille[0]-1; i >= 0; i--) {
        for (int j = taille[1]-1; j >= 0; j--) {
            if (existePositionCarte(p,(int []) {i,j}) && carteFace(p,(int []) {i,j}) == 0){ // on cherche la dernière carte face cachée sur le plateau, donc on parcourt le tableau à partir d'en bas à droite
                getCard(p->cells,p->taille,(int []) {i,j},1); // quand on trouve la carte, on la supprime
                return;
            }
        }
    }
}

void effet_Guillaume_Burel(plateau p, carte c) {
    int id = c->id_faction;
    if (p->tab_factions[1 - id]->pts_ddrs > p->tab_factions[id]->pts_ddrs) {   // premier cas selon l'identifiant, on vole 3 points ddrs
        p->tab_factions[id]->pts_ddrs += 3;
        p->tab_factions[1 - id]->pts_ddrs -= 3;
    } else if ( p->tab_factions[1 - id]->pts_ddrs < p->tab_factions[id]->pts_ddrs) { // second cas selon l'identifiant, on vole 3 points ddrs
        p->tab_factions[1 - id]->pts_ddrs += 3;
        p->tab_factions[id]->pts_ddrs -= 3;
    }
}

void effet_Christophe_Mouilleron(plateau p) {
    if (getVisibleCardNamed(p->cells, p->taille, "Heures supplémentaires",1,0) != NULL) {   // s'il y a au moins une carte 'Heures supplémentaires' sur la plateau
        int *taille = p->taille;
        for (int i = 0; i < taille[0]; i++) {
            for (int j = 0; j < taille[1]; j++) {
                if (existePositionCarte(p,(int[]) {i, j}) && carteFace(p,(int[]) {i, j}) &&
                    strcmp(*carteCoordonnees(p,(int[]) {i, j})->nom, "Christophe Mouilleron") != 0 &&
                    strcmp(*carteCoordonnees(p,(int[]) {i, j})->nom, "Heures supplémentaires") != 0) { // si la carte existe, est retournée et est diféérente de Christophe Mouilleron ou Heures supplémentaires, on la su   pprime
                    getCard(p->cells, p->taille, (int[]) {i, j}, 1);
                }
            }
        }
    }
}

void effet_Thomas_Lim(plateau p, carte c) {
    int id = c->id_faction;
    node fise = getVisibleCardNamed(p->cells, p->taille, "Fise",1,0);
    int nb = getSize(fise);
    node forest = getVisibleCardNamed(p->cells, p->taille, "Julien Forest",0,0);
    int nb_forest = getSize(forest);
    if (nb_forest > 0) { // s'il n'y a pas de carte 'Julien Forest' face cachée sur le plateau
        p->tab_factions[id]->pts_ddrs += (3 * nb);  // on rajoute 3 fois le nombre de carte Fise retournées sur le plateau aux points ddrs de la faction
        
    } else {
        p->tab_factions[1 - id]->pts_ddrs -= nb; // sinon on enlève ce nombre aux points ddrs de la faction
    }
}

void effet_Julien_Forest(plateau p, carte c) {
    if (getVisibleCardNamed(p->cells, p->taille, "Café",1,0) != NULL) { // s'il y a au moins une carte Café sur le plateau
        int id = c->id_faction;
        node fise = getVisibleCardNamed(p->cells, p->taille, "Fise",1,0);
        int nb = getSize(fise);
        p->tab_factions[id]->pts_ddrs += (6 * nb); // on rajoute 6 fois le nombre de carte Fise retournées sur le plateau aux points ddrs de la faction
    }
}

void effet_Dimitri_Watel(plateau p, carte c) {
    if (getVisibleCardNamed(p->cells, p->taille, "Thé",1,0) != NULL) {  // s'il y a au moins une carte Thé sur le plateau
        int id = c->id_faction;
        node fisa = getVisibleCardNamed(p->cells, p->taille, "Fisa",1,0);
        node fc = getVisibleCardNamed(p->cells, p->taille, "Fc",1,0);
        int nb = getSize(fisa) + getSize(fc);
        p->tab_factions[id]->pts_ddrs += (3 * nb); // on rajoute 3 fois le nombre de carte Fise et Fc retournées sur le plateau aux points ddrs de la faction
    }
}

void effet_Djibril_Aurelien_Dembele_Cabot(plateau p, carte c) {
    int *pos = position_carte(p, c);
    int id = c->id_faction;
    int *taille = p->taille;
    int compteur = -1; // on ne compte pas la carte c dans les cartes retournées de la ligne
    for (int i = 0; i < taille[1]; i++) {
        if (existePositionCarte(p, (int []) {pos[0],i}) && carteFace(p, (int []) {pos[0],i})) { // on compte le nombre de carte retournées sur la ligne de la carte c
            compteur++;
        }
    }
    if (compteur >= 3) { // si le compteur est supérieur à 3, la faction gagne 3 points ddrs
        p->tab_factions[id]->pts_ddrs += 5;
    }
    free(pos);
}

void effet_Eric_Lejeune(plateau p) {
    int nb = nbCarteRetournee(p); // on prend le nombre de cartes retournées sur le plateau
    int *taille = p->taille;
    int S;
    if (nb >= 5) {
        S = 5;
    } else {
        S = nb;
    }
    node list_carte = NULL;
    for (int k = 0; k < S; k++) { // on va prendre 5 cartes face cachées au hasard (ou alors toutes si il y en a moins de 5)
        int random = rand() % (nb - k);
        for (int i = 0; i < taille[0]; i++) {
            for (int j = 0; j < taille[1]; j++) {
                if (existePositionCarte(p, (int[]) {i, j})) {
                    carte temp = getCard(p->cells,p->taille,(int []) {i,j},0);
                    if (temp->retournee) {
                        if (random == 0) {
                            carte C = getCard(p->cells, p->taille, (int[]) {i, j}, 1);
                            push(&list_carte, C); // on insère les cartes prises au hasard dans un node (qui sont supprimées du plateau)
                            random--;
                        } else {
                            random--;
                        }
                    }
                }
            }
        }
    }
    node melange = NULL;
    while (list_carte != NULL) {
        carte P = pop(&list_carte);
        if (strcmp(*P->nom, "Catherine Dubois") == 0 || strcmp(*P->nom, "Anne-Laure Ligozat") == 0 ||
            strcmp(*P->nom, "Guillaume Burel") == 0 || strcmp(*P->nom, "Christophe Mouilleron") == 0 ||
            strcmp(*P->nom, "Thomas Lim") == 0 || strcmp(*P->nom, "Julien Forest") == 0 ||
            strcmp(*P->nom, "Dimitri Watel") == 0) {
            push(&melange, P); // si la carte est bien une de celles citées ci-dessus, on l'ajoute à un nouveau node
        }
    }
    shuffle(&melange); // on mélange
    while (melange != NULL) {
        int *pos = position_carte_haut_gauche(p);
        pos[1]-=1;
        carte Q = pop(&melange);
        poser_face_cachee(p, Q, pos); // on pose les cartes face cachées à gauche de la carte la plus en haut à gauche
        Q->retournee = 1; // on les retourne
    }
}

void effet_Lucienne_Pacave(plateau p, carte c) {
    int *pos = position_carte(p, c);
    int id = c->id_faction;
    int *taille = p->taille;
    int b = 0;  // on pose un booléen à 0
    carte ligne;
    carte colonne;
    for (int i = 0; i < taille[1]; i++) {
        if (existePositionCarte(p,(int []) {pos[0],i})){
            ligne = getCard(p->cells,p->taille,(int []) {pos[0],i},0);
            if (strcmp(*ligne->nom, "Fisa") == 0 && carteFace(p,(int []) {pos[0],i})) { // s'il y a une carte Fisa sur la ligne de la carte c, on met le booléen à 1
                b = 1;
            }
        }
    }
    for (int j = 0; j < taille[0]; j++) {
        if (existePositionCarte(p,(int []) {j,pos[1]})){
            colonne = getCard(p->cells,p->taille,(int []) {j,pos[1]},0);
            if (strcmp(*colonne->nom, "Fisa") == 0 && carteFace(p,(int []) {j,pos[1]})) { // s'il y a une carte Fisa sur la colonne de la carte c, on met le booléen à 1
                b = 1;
            }
        }
    }
    if (b == 1) { // si le booléen est à 1, la faction gagne 5 points ddrs
        p->tab_factions[id]->pts_ddrs += 5;
    }
    free(pos);
}

void effet_Katrin_Salhab(plateau p, carte c) {
    int id = c->id_faction;
    if (getVisibleCardNamed(p->cells, p->taille, "Djibril-Aurélien Dembele-Cabot",1,0) != NULL &&
        getVisibleCardNamed(p->cells, p->taille, "Eric Lejeune",1,0) != NULL &&
        getVisibleCardNamed(p->cells, p->taille, "Lucienne Pacavé",1,0) != NULL) { //s'il y a au moins une carte 'Djibril-Aurélien Dembele-Cabot' et 'Eric Lejeune' et 'Lucienne Pacavé', la faction gagne 10 points ddrs
        p->tab_factions[id]->pts_ddrs += 10;
    } else {
        int *pos = position_carte(p, c);
        int *taille = p->taille;
        for (int j = 0; j < taille[1]; j++) {
            if (existePositionCarte(p,(int []) {pos[0],j})){
                carte temp = carteCoordonnees(p, (int []) {pos[0],j});
                if (temp->retournee == 0) { // on retourne toutes les cartes sur la la même ligne que la carte c
                    temp->retournee = 1;
                }
            }
        }
        free(pos);
    }
}


int id_nom_carte(carte c) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(*c->nom, nom[i]) == 0) {
            return i; // renvoie un entier entre 0 et 31 correspondant à chaque carte
        }
    }
    return -1;
}

void effet_carte(plateau p, carte c) {
    int num = id_nom_carte(c);
    switch (num) {  // on active l'effet de la carte selon l'identifiant de la carte donné
        case 0:
            effet_Fise(p, c);    
            break;

        case 1:
            effet_Fisa(p, c);    
            break;

        case 2:
            effet_Fc(p, c);  
            break;

        case 3:
            effet_Ecologiie(p, c);   
            break;

        case 4:
            effet_Liiens(p);  
            break;

        case 5:
            effet_Soiree_sans_alcool(p, c);  
            break;

        case 6:
            effet_Alcool(p, c);  
            break;

        case 7:
            effet_Cafe(p, c);  
            break;

        case 8:
            effet_The(p, c);     
            break;

        case 10:
            effet_Reprographie(p, c);  
            break;

        case 11:
            effet_Isolation_du_batiment(p);  
            break;

        case 12:
            effet_Parcous_sobriete_numerique(p);  
            break;

        case 13:
            effet_Heures_supplementaires(p, c);  
            break;

        case 14:
            effet_Kahina_Bouchama(p);  
            break;

        case 15:
            effet_Kevin_Goilard(p, c);  
            break;

        case 16:
            effet_Massinissa_Merabet(p,c);  
            break;

        case 17:
            effet_Vitera_Y(p, c);  
            break;

        case 18:
            effet_Jonas_Senizergues(p);  
            break;

        case 19:
            effet_Fetia_Bannour(p, c);  
            break;

        case 20:
            effet_Catherine_Dubois(p,c);     
            break;

        case 21:
            effet_Anne_Laure_Ligozat(p, c);  
            break;

        case 22:
            effet_Guillaume_Burel(p, c);  
            break;

        case 23:
            effet_Christophe_Mouilleron(p);  
            break;

        case 24:
            effet_Thomas_Lim(p, c);  
            break;

        case 25:
            effet_Julien_Forest(p, c);   
            break;

        case 26:
            effet_Dimitri_Watel(p, c);  
            break;

        case 27:
            effet_Djibril_Aurelien_Dembele_Cabot(p, c);  
            break;

        case 28:
            effet_Eric_Lejeune(p);  
            break;

        case 29:
            effet_Lucienne_Pacave(p, c);  
            break;

        case 30:
            effet_Katrin_Salhab(p, c);  
            break;

        default:
            break;
    }
}