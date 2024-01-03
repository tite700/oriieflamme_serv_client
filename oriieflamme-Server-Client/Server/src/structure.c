#include "../headers/structure.h"

/*
 *
 * FONCTION POUR LINKEDLIST -> Utilisée dans le deck et la main
 *
 */

void push(node *head, carte c) {
    // On crée une nouvelle node
    node new_node = (node) malloc(sizeof(struct s_node));

    // On assigne la carte à la nouvelle node
    new_node->value = c;

    // On assigne notre paquet comme étant la suite de cette carte
    new_node->next = *head;

    // La première carte est maintenant la node qu'on vient de créer
    *head = new_node;
}

int getSize(node head) {
    // Si la tête est nulle, on est au bout de la liste
    if (head == NULL) {
        return 0;
    } else {
        // Sinon on compte 1 et on passe à l'élément suivant
        return 1 + getSize(head->next);
    }
}

int rand_range(int min_n, int max_n) {
    return rand() % (max_n - min_n + 1) + min_n;
}

// Echange deux cartes dans le tableau fournit
void swap(carte *card_array, int a, int b) {
    carte temp = card_array[a];
    card_array[a] = card_array[b];
    card_array[b] = temp;
}

// Mélange une linked list passée en paramètre
void shuffle(node *head) {

    // On récupère la taille de la liste chainée
    int node_size = getSize(*head);

    // On crée un tableau de carte de la taille de la liste
    carte *card_array = (carte *) malloc(sizeof(carte) * node_size);

    // On remplit le tableau avec les cartes de la liste chainée
    for (int i = 0; i < node_size; i++) {
        card_array[i] = pop(head);
    }

    // On utilise l'algo de Fisher-Yates pour mélanger le tableau
    for (int i = node_size - 1; i > 0; i--) {
        int r = rand_range(0, i);
        swap(card_array, r, i);
    }

    // On remplit la liste chainée avec les valeurs mélangées
    for (int i = 0; i < node_size; i++) {
        push(head, card_array[i]);
    }

    // On libère le tableau temporaire utilisé
    free(card_array);

}

carte getNthCard(node *head, int index, int remove) {
    // Si la tête est NULL, c'est qu'il n'y a plus de carte
    if (head == NULL) {
        return NULL;
    }

    // Si l'index est à 0, c'est qu'on demande de retirer la tête
    // Donc pop()
    if (index == 0) {
        return pop(head);
    }
        // Si l'index vaut 1
    else if (index == 1) {
        // On sauvegarde la node suivante
        node temp = (*head)->next;
        // On sauvegarde la carte voulue
        carte return_value = temp->value;
        // On raccroche la suite de la carte suivante à la carte en cours
        if (remove == 1) {
            (*head)->next = temp->next;
            free(temp);
        }

        return return_value;
    } else {
        // Sinon on n'est pas encore à la carte que l'on souhaite, on continue
        return getNthCard(&(*head)->next, index - 1, remove);
    }
}

carte pop(node *head) {

    // Si la tête vaut NULL c'est que le paquet est vide
    if (head == NULL) {
        return NULL;
    }

    // On récupère la suite
    node next_node = (*head)->next;
    // On récupère la première carte
    carte first_card = (*head)->value;
    // On libère la mémoire de la première node
    free(*head);
    // La nouvelle tête est maintenant la carte suivante
    *head = next_node;

    // On renvoie la carte que l'on avait enregistré
    return first_card;
}

/*
 * FONCTION POUR LE PLATEAU DE JEU
 *
 * On part sur une taille initiale de X, Y
 * Pour l'instant on agrandit le tableau que par 1
 * C'est pas le plus optimal car un malloc coûte
 * Mais l'affichage est grandement simplifié
 */

carte getCard(carte **cells, int *taille, int *coordonees, int remove) {
    // On vérifie qu'on est bien dans le tableau
    if (coordonees[0] < 0 || coordonees[1] < 0
        || taille[0] <= coordonees[0] || taille[1] <= coordonees[1]) {
        return NULL;
    } else {
        // On enregistre la carte qui est à cette position
        carte temp = cells[coordonees[0]][coordonees[1]];
        if (remove) {
            // On enlève la carte du tableau si c'est demandé
            cells[coordonees[0]][coordonees[1]] = NULL;
        }
        return temp;
    }
}

/*
 * L'idée ici est de créer un tableau avec la nouvelle taille
 * Et de copier les données de l'ancien dans le nouveau
 * J'ai essayé de faire des realloc à la place
 * Mais impossible de faire fonctionner, pour une raison qui m'échappe totalement
 */
carte **grow(carte **old, int *old_taille, int *taille) {

    // On réserve un espace mémoire pour les lignes
    carte **cells = malloc(sizeof(carte *) * taille[0]);

    // On réserve un espace mémoire pour les colonnes
    for (int col = 0; col < taille[0]; col++) {
        cells[col] = malloc(sizeof(carte) * taille[1]);
    }

    // On initialise toutes les cases à NULL
    for (int row = 0; row < taille[0]; row++) {
        for (int col = 0; col < taille[1]; col++) {
            cells[row][col] = NULL;
        }
    }

    // On copie les données de l'ancien taille dans le nouveau
    for (int row = 0; row < old_taille[0]; row++) {
        for (int col = 0; col < old_taille[1]; col++) {
            cells[row][col] = old[row][col];
        }
    }

    // On libère les colonnes de l'ancien tableau
    for (int col = 0; col < old_taille[0]; col++) {
        free(old[col]);
    }

    // Puis on libère les lignes
    free(old);

    return cells;
}

/*
 * On déplace toutes les cartes vers le bas
 * L'objectif est d'ajouter une ligne en haut du tableau
 */

void moveDown(carte **cells, int *taille) {
    // on commence par la dernière ligne et on remonte
    for (int row = taille[0] - 1; row > 0; row--) {
        for (int col = 0; col < taille[1]; col++) {
            // La case choisit prend la valeur de la case du dessous
            cells[row][col] = cells[row - 1][col];
        }
    }
}

/*
 * On déplace toutes les cartes vers la droite
 * L'objectif est d'ajouter une colonne à gauche du tableau
 */

void moveRight(carte **cells, int *taille) {
    for (int row = 0; row < taille[0]; row++) {
        // On commence par la droite du tableau
        for (int col = taille[1] - 1; col > 0; col--) {
            // La case choisit prend la valeur de la case à sa gauche
            cells[row][col] = cells[row][col - 1];
        }
    }
}


carte **putCard(carte **cells, int *taille, carte c, int *coordonees) {

    // Si on essaie de placer une pièce sur des coordonnées négatives
    if (coordonees[0] < 0 || coordonees[1] < 0) {
        // Forcément invalide puisqu'on s'arrange pour toujours avoir la ligne du haut et la colonne de gauche de libre
        return NULL;
        // Si on essaie de placer dans le tableau sans les bords (première et dernière colonne, première et dernière ligne
    } else if (coordonees[0] < taille[0] - 1 && coordonees[1] < taille[1] - 1 && coordonees[0] > 0 &&
               coordonees[1] > 0) {
        // On vérifie s'il y a déjà une carte de poser à cet endroit
        if (cells[coordonees[0]][coordonees[1]] == NULL) {
            cells[coordonees[0]][coordonees[1]] = c;
            return cells;
        } else {
            return NULL;
        }
        // Sinon c'est qu'il faut agrandir le tableau
    } else {
        // On sauvegarde l'ancienne taille du tableau pour la copie
        int old_taille[2];
        old_taille[0] = taille[0];
        old_taille[1] = taille[1];

        // On ajoute 1 à la nouvelle taille si :
        // On est sur le bord du bas
        taille[0] += (coordonees[0] >= taille[0] - 1) ? 1 : 0;
        // On est sur le bord du haut
        taille[0] += (coordonees[0] == 0) ? 1 : 0;
        // On peut très bien remplir les deux conditions (le cas de la première carte posée)

        // Même principe pour la droite et la gauche
        taille[1] += (coordonees[1] >= taille[1] - 1) ? 1 : 0;
        taille[1] += (coordonees[1] == 0) ? 1 : 0;

        // On agrandit le tableau et on remplace le pointeur de l'ancien tableau par le nouveau
        cells = grow(cells, old_taille, taille);

        // Si on est sur le bord haut, on déplace toutes les cartes vers le bas
        // Et on pose la carte sur une coordonnée une case plus basse
        if (coordonees[0] == 0) {
            moveDown(cells, taille);
            coordonees[0]++;
        }

        // Même principe mais vers la droite
        if (coordonees[1] == 0) {
            moveRight(cells, taille);
            coordonees[1]++;
        }

        // On rappelle cette fonction et on tombera dans le cas où toutes les conditions seront remplies
        return putCard(cells, taille, c, coordonees);
    }
}

node getVisibleCardNamed(carte **cells, int *taille, char *nom, int visible, int remove) {
    node retour = NULL;
    // On parcourt chaque case du tableau
    for (int row = 0; row < taille[0]; row++) {
        for (int col = 0; col < taille[1]; col++) {
            // On récupère la carte associée à chaque case
            carte temp = getCard(cells, taille, (int[]) {row, col}, 0);
            // Si la case n'est pas vide
            if (temp != NULL) {
                // On regarde si la carte concernée remplit les conditions demandées
                // Soit le nom correspond à celui demandé, ou * pour n'importe quel nom
                // Et le statut retourné ou non de la carte
                if ((strcmp(nom, *temp->nom) == 0 || strcmp(nom, "*") == 0) && temp->retournee == visible) {
                    // Et finalement on retire la carte du tableau si c'est demandé
                    if (remove == 1) {
                        getCard(cells, taille, (int[]) {row, col}, 1);
                    }
                    // On ajoute chaque carte qui répond aux critères dans une liste chainée
                    push(&retour, temp);
                }
            }
        }
    }
    return retour;
}

node mergeNode(node a, node b) {
    // Si A est vide, on renvoie B
    if (a == NULL)
        return b;
    // Si B et vide, on renvoie A
    if (b == NULL)
        return a;

    // Sinon la suite de A correspond à la fusion entre la suite de A et B
    a->next = mergeNode(a->next, b);

    return a;
}

void removeRow(carte **cells, int *taille, int row) {
    for (int col = 0; col < taille[1]; col++) {
        // On retire toutes les cartes une à une de la ligne passée en paramètre
        carte temp = getCard(cells, taille, (int[]) {row, col}, 1);
        free_carte(temp);
    }
}

// Fonction de test pour le développement (non utilisée lors du rendu)
/*void test_plateau() {

    int *taille = malloc(sizeof(int) * 2);
    // On choisit la taille du plateau
    taille[0] = 1;
    taille[1] = 1;

    // On initialise le tableau 2D à NULL
    carte **cells = malloc(sizeof(carte *) * taille[0]);

    for (int i = 0; i < taille[0]; i++) {
        cells[i] = malloc(sizeof(carte) * taille[1]);
    }

    for (int i = 0; i < taille[0]; i++) {
        for (int j = 0; j < taille[1]; j++) {
            cells[i][j] = NULL;
        }
    }

    printf("%s\n", "TEST DE L'AFFICHAGE DU PLATEAU");
    print_plateau(cells, taille);

    printf("%s\n", "TEST DE L'INSERTION D'UNE CARTE");

    const char *nom = "1";
    carte c = malloc(sizeof(carte));
    c->nom = &nom;

    int coordonees[2];
    coordonees[0] = 0;
    coordonees[1] = 0;

    cells = putCard(cells, taille, c, (int[]) {0, 0});
    print_plateau(cells, taille);

    cells = putCard(cells, taille, c, (int[]) {1, 0});
    print_plateau(cells, taille);

    cells = putCard(cells, taille, c, (int[]) {2, 0});
    print_plateau(cells, taille);

    removeRow(cells, taille, 1);
    print_plateau(cells, taille);

    printf("Placement d'une carte sur une position qui ne necessite pas de modification de tableau"
           ": (%d,%d)\n", coordonees[0], coordonees[1]);



    print_plateau(cells, taille);
    assert(getCard(cells, taille, coordonees, 0) == c);


    coordonees[0] = taille[0];
    printf("Test du dépassement par la droite : (%d,%d)\n", coordonees[0], coordonees[1]);
    putCard(cells, taille, c, coordonees);
    assert(getCard(cells, taille, coordonees, 0) == c);
    print_plateau(cells, taille);

    exit(-1);


    coordonees[1] = 0;
    printf("Test du dépassement par la gauche : (%d,%d)\n", coordonees[0], coordonees[1]);
    putCard(cells, taille, c, coordonees);
    assert(getCard(cells, taille, coordonees, 0) == c);
    print_plateau(cells, taille);

    coordonees[0] = taille[0] - 1;
    printf("Test du dépassement par le bas : (%d,%d)\n", coordonees[0], coordonees[1]);
    putCard(cells, taille, c, coordonees);
    assert(getCard(cells, taille, coordonees, 0) == c);
    print_plateau(cells, taille);

    coordonees[0] = 0;
    printf("Test du dépassement par le haut : (%d,%d)\n", coordonees[0], coordonees[1]);
    putCard(cells, taille, c, coordonees);
    assert(getCard(cells, taille, coordonees, 0) == c);
    print_plateau(cells, taille);


}*/


// Fonction de test pour la liste chainée
void test_linked_list() {
// On crée 3 cartes avec pour nom 1, 2 et 3
    /*const char * nom = "1";
    const char * nom1 = "2";
    const char * nom2 = "3";

    carte c = malloc(sizeof(carte));
    c->nom = &nom;

    carte c1 = malloc(sizeof(carte));
    c1->nom = &nom1;

    carte c2 = malloc(sizeof(carte));
    c2->nom = &nom2;

    printf("%s\n", "TEST DU PUSH");
    node d = NULL;
    // TEST DU PUSH
    // On insère les 3 cartes
    push(&d, c);
    push(&d, c1);
    push(&d, c2);

    // On affiche
    print_carte(d);

    // TEST DU POP
    printf("%s\n", "TEST DU POP");
    // On retire la première carte
    assert(pop(&d) == c2);
    // On affiche après le pop
    print_carte(d);

    // On remet la carte
    push(&d, c2);

    // On enlève une carte à l'index i
    printf("%s\n", "TEST DU REMOVE BY INDEX");
    assert(getNthCard(&d, 1, 0) == c1);

    print_carte(d);

    printf("%s\n", "TEST DE LA TAILLE");

    d = NULL;
    printf("%s : %d \n", "Taille NULL", getSize(d));
    assert(getSize(d) == 0);

    push(&d, c1);

    printf("%s : %d \n", "Taille 1", getSize(d));
    assert(getSize(d) == 1);

    pop(&d);
    printf("%s : %d \n", "Taille 0", getSize(d));
    assert(getSize(d) == 0);

    push(&d, c1);
    push(&d, c2);
    printf("%s : %d \n", "Taille 2", getSize(d));
    assert(getSize(d) == 2);

    // TEST DU SHUFFLE
    printf("%s\n", "TEST DU SHUFFLE");
    print_carte(d);
    shuffle(&d);
    print_carte(d);*/
}


/*void print_carte(node head) {
    // si la node est NULL, c'est vide
    if ( head == NULL ) {
        return;
    } else {
        // Sinon on affiche le nom de la carte
        printf("%s, ", *head->value->nom);
        // Et on affiche la carte suivante
        print_carte(head->next);
    }
}


int main() {

    // On teste le bon fonctionnement du push et pop
    //test_linked_list();

    // On teste la structure choisie pour le plateau
    test_plateau();

}

*/