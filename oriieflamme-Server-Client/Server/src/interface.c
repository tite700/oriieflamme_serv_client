#include "../headers/interface.h"

/*
 * Cette fonction va permettre de nettoyer le buffer stdin
 * Une fois que l'on aura récupéré ce que l'on souhaite
 */
void clearInputBuffer() {
    char enter = 0;
    // On récupère un char jusqu'a ce qu'on rencontre un caractère de fin de ligne
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

void pressToContinue() {
    printf("Appuyez sur ENTREE pour continuer\n");
    clearInputBuffer();
}

/*
 * Cette fonction va afficher l'entête du plateau afin de mieux se situer
 */
void printPlateauHeader(int taille_y) {
    // On formate l'entête sur 2 chars
    printf("  %s%2d%s ", BLUE, 0, RESET);
    for (int i = 1; i < taille_y; i++) {
        printf("%s%d%s ", BLUE, i, RESET);
    }
    printf("\n");
}

void afficherScore(faction *factions) {
    for (int joueur = 0; joueur < NB_FACTIONS; joueur++) {
        printf("%s a %d points ddrs\n", factions[joueur]->nom, factions[joueur]->pts_ddrs);
    }
    pressToContinue();
}

void afficherPlateau(carte **cells, int *taille, int clear) {
    // On efface les affichages précédant si demandé
    if (clear == 1)
        system("clear");
    // On affiche l'entête du tableau
    printPlateauHeader(taille[1]);
    for (int row = 0; row < taille[0]; row++) {
        // On affiche l'entête de chaque ligne
        printf("%s%2d%s ", BLUE, row, RESET);
        for (int col = 0; col < taille[1]; col++) {
            // Si il n'y pas de carte, on affiche un X
            if (cells[row][col] == NULL) {
                printf("%.2s", "X ");
            } else {
                // Si la carte est face cachée on affiche Y en rouge
                if (cells[row][col]->retournee == 0) {
                    printf("%s%s%s", RED, "Y ", RESET);
                } else {
                    // Sinon Z
                    printf("%s%s%s", RED, "Z ", RESET);
                }
            }
        }
        printf("\n");
    }
}

void print_carte(node head,int i) {
    // si la node est NULL, c'est vide
    if (head == NULL) {
        return;
    }
    else if (getSize(head)==1){
        printf("%i -> '%s' ",i, *head->value->nom);
    }
    else {
        // Sinon on affiche le nom de la carte
        printf("%i -> '%s'; ",i, *head->value->nom);
        // Et on affiche la carte suivante
        print_carte(head->next,i+1);
    }
}

void afficherMain(faction f) {
    printf("%s, votre main : [ ", f->nom);
    // On appelle la fonction récursive print_carte
    print_carte(f->main,0);
    printf("]\n");
}


void afficherVainqueurManche(faction f) {
    printf("Le vainqueur de la manche est : %s\n", f->nom);
    pressToContinue();
}

void afficherVainqueurPartie(faction f) {
    printf("Le vainqueur de la partie est : %s\n", f->nom);
    pressToContinue();
}

void afficherEffetCarte(carte c) {
    if (c != NULL) {
        printf("Carte : %s retournée !\n", *c->nom);
        printf("L'effet suivant va être appliqué : %s\n", *c->description);
    }
}

int *demanderPositionCarte() {
    printf("Saisir où vous voulez placer la carte sous ce format : 'X Y'\n");
    int *position = malloc(sizeof(int) * 2);
    scanf("%d %d", &position[0], &position[1]);
    clearInputBuffer();
    return position;
}

carte demanderQuelleCarteJouer(faction f) {
    int index_main = -1;
    // On récupère la taille de la main du joueur
    int size_main = getSize(f->main);
    carte retour = NULL;
    do {
        printf("Saisir la carte que vous voulez jouer sous ce format : 'X'\n");
        scanf("%d", &index_main);
        clearInputBuffer();
        // On vérifie que la carte demandée est entre 0 et index_max de la main
        if (size_main > index_main && index_main > -1) {
            retour = getNthCard(&f->main, index_main, 1);
        } else {
            // Sinon affiche un message d'erreur et on réaffiche la main
            message_erreur("Index invalide dans la main");
            afficherMain(f);
        }
        // On continue tant que le retour ne contient pas une carte
    } while (retour == NULL);

    system("clear");

    printf("Vous avez choisi de jouer la carte %s\n", *retour->nom);

    return retour;
}

int demanderChangementMain(faction f) {
    char choice = 'P';
    // Tant que le joueur n'a pas saisi 'o' ou 'n'
    while (choice != 'o' && choice != 'n') {
        // On lui demande s'il veut changer de main
        printf("%s, Voulez vous changer de main ? (O)ui (N)on\n", f->nom);
        scanf("\n%c", &choice);
        clearInputBuffer();
        // On met son choix en minuscule
        choice = tolower(choice);
    }

    system("clear");
    // Si le choix vaut 'o' on renvoie 1
    return choice == 'o';
}

char *demanderNomFaction() {
    char *name = malloc(sizeof(char) * 50);
    printf("Saisir le nom de votre faction\n");
    scanf("%s", name);
    clearInputBuffer();
    return name;
}

void message_erreur(char *message) {
    printf("%s%s%s\n", RED, message, RESET);
}
