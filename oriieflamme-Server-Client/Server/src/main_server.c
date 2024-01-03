#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "../headers/server.h"

// #include "../headers/interface_server.h"
#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/plateau.h"


int premier_joueur() {
    return rand_range(0,1); 
}

/*
requires : head est bien une liste chaine de carte, et res est bien une adresse vers un tableau de char
assigns : res
ensures : mets l affichage des cartes dans res
*/
void print_carte_server(node head,char **res) {
    // printf("%s\n\n",*res);
    char buffer[1000];
    // si la node est NULL, c'est vide
    if (head == NULL) {
        strcat(*res,"\n");
        return;
    }
    else {
        // s il n y a qu'un seul element, pas besoin de mettre le & à la fin
        if (getSize(head)==1){
            sprintf(buffer,"%s | %s\n", *head->value->nom, *head->value->description);
            strcat(*res,buffer);
            // printf("%s\n",*res);
            return;
        }
    
        else {
            // Sinon on affiche le nom de la carte
            sprintf(buffer,"%s | %s & ", *head->value->nom, *head->value->description);
            // Et on affiche la carte suivante
            strcat(*res,buffer);
            print_carte_server(head->next,res);
        }
    }
}

/*
requires : rien
assigns : rien
ensures : renvoie une chaine de caractere qui contient le protocole a envoyer pour afficher la main au client : MAIN nom_carte|description & nom_carte|description
*/
char * afficherMain_server(faction f) {
    char *res=malloc(8000*sizeof(char));
    // On affiche MAIN pour respecter le protocole, puis les cartes de la main
    sprintf(res,"MAIN ");
    print_carte_server(f->main,&res);
    // printf("%s",res);
    return res;
}

/*
requires : rien
assigns : rien
ensures : renvoie une chaine de caractere qui contient le protocole a envoyer pour afficher le plateau au client : PLATEAU 0|1|0&0|...|0
*/
char * afficherPlateau_server(plateau p){
    char *res=malloc(sizeof(char)*(p->taille[0])*(p->taille[1])*50+8+2*p->taille[1]);
    // On affiche PLATEAU pour respecter le protocole
    sprintf(res,"PLATEAU ");
    // si il n y a qu un ligne, alors il n y a qu une colonne, car c est le plateau vide, sinon on affiche dans une boucle les premieres lignes du tableau, et on affiche la derniere ligne a la fin pour ne pas y ajouter le &
    if (p->taille[0]>1){
        for (int i=0;i<p->taille[0]-1;i++){
            // On affiche d abord les premieres colonnes sauf la derniere pour ne pas mettre le | a la fin
            for (int j=0;j<p->taille[1]-1;j++){
                if (p->cells[i][j]==NULL){
                    strcat(res,"0|");
                }
                else {
                    if(p->cells[i][j]->retournee==0){
                        strcat(res,"1|");
                    }
                    else {
                        char buffer[50];
                        sprintf(buffer,"%s|",*p->cells[i][j]->nom);
                        strcat(res,buffer);
                    }
                }
            }
            int k=p->taille[1]-1;
            if (p->cells[i][k]==NULL){
                strcat(res,"0");
            }
            else {
                if(p->cells[i][k]->retournee==0){
                    strcat(res,"1");
                }
                else {
                    char buffer[50];
                    sprintf(buffer,"%s",*p->cells[i][k]->nom);
                    strcat(res,buffer);
                }
            }
            strcat(res,"&");
        }
        for (int j=0;j<p->taille[1]-1;j++){
            int i=p->taille[0]-1;
            if (p->cells[i][j]==NULL){
                strcat(res,"0|");
            }
            else {
                if(p->cells[i][j]->retournee==0){
                    strcat(res,"1|");
                }
                else {
                    char buffer[50];
                    sprintf(buffer,"%s|",*p->cells[i][j]->nom);
                    strcat(res,buffer);
                }
            }
        }
        int k=p->taille[1]-1;
        int i=p->taille[0]-1;
        if (p->cells[i][k]==NULL){
            strcat(res,"0");
        }
        else {
            if(p->cells[i][k]->retournee==0){
                strcat(res,"1");
            }
            else {
                char buffer[50];
                sprintf(buffer,"%s",*p->cells[i][k]->nom);
                strcat(res,buffer);
            }
        }
    }
    else {
        for (int j=0;j<p->taille[1];j++){
            int i=p->taille[0]-1;
            if (p->cells[i][j]==NULL){
                strcat(res,"0");
            }
            else {
                if(p->cells[i][j]->retournee==0){
                    strcat(res,"1");
                }
                else {
                    char buffer[50];
                    sprintf(buffer,"%s",*p->cells[i][j]->nom);
                    strcat(res,buffer);
                }
            }
        }
    }
    strcat(res,"\n");
    return res;
}


/*
requires : rien
assigns : rien
ensures : renvoie la carte que le client a choisi de jouer
*/
carte demanderQuelleCarteJouer_server(faction f,client c) {
    int index_main = -1;
    char *response;
    
    // On récupère la taille de la main du joueur
    int size_main = getSize(f->main);
    carte retour = NULL;
    do {
        // On demande au client quelle carte il veut jouer
        sendMessage(c,"CARTE\n",6);
        response=readMessage(c);
        sscanf(response,"%i\n",&index_main);
        free(response);
        // On vérifie que la carte demandée est entre 0 et index_max de la main
        if (size_main > index_main && index_main > -1) {
            retour = getNthCard(&f->main, index_main, 1);
        } else {
            // Sinon affiche un message d'erreur et on réaffiche la main
            retour==NULL;
        }
        // On continue tant que le retour ne contient pas une carte
    } while (retour == NULL);

    // printf("Vous avez choisi de jouer la carte %s\n", *retour->nom);

    return retour;
}

/*
requires : rien
assigns : rien
ensures : renvoie la position a laquelle le client veut jouer sa carte
*/
int *demanderPositionCarte_server(client c){
    // On demande au client ou il veut jouer
    sendMessage(c,"POSITION\n",9);
    char *response=readMessage(c);

    int *position = malloc(sizeof(int) * 2);
    sscanf(response,"%i %i\n", &position[0], &position[1]);

    return position;
}


/*
requires : c est bien un tableau de clients
assigns : rien
ensures : envoie aux clients un message pour leur dire qui a gagne la manche
*/
void afficherVainqueurManche_server(faction f,client *c) {
    char *res=malloc(sizeof(char)*100);
    sprintf(res,"VAINQUEUR_MANCHE|%s\n", f->nom);
    for (int i=0;i<2;i++){
        char *rep;
        sendMessage(c[i],res,length(res));
        rep=readMessage(c[i]);
        free(rep);
    }
    free(res);
    // for (int i=0;i<2;i++){
    //     char *rep;
    //     rep=readMessage(c[i]);
    //     free(rep);
    // }
    return;
}

/*
requires : c est bien un tableau de clients
assigns : rien
ensures : envoie aux clients un message pour leur dire qui a gagne la partie
*/
void afficherVainqueurPartie_server(faction f,client *c) {
    char *res=malloc(sizeof(char)*100);
    sprintf(res,"VAINQUEUR_PARTIE|%s\n", f->nom);
    for (int i=0;i<2;i++){
        char *rep;
        sendMessage(c[i],res,length(res));
        rep=readMessage(c[i]);
        free(rep);
    }
    free(res);
    // for (int i=0;i<2;i++){
    //     char *rep;
    //     rep=readMessage(c[i]);
    //     free(rep);
    // }
    return;
}


/*
requires : clients est bien un tableau de clients
assigns : rien
ensures : envoie au client un chaine de caractere qui contient la carte et son effet en suivant le protocole : EFFET nom_carte|description
*/
void afficherEffetCarte_server(carte c,client *clients){
    if (c != NULL) {
        char *res=malloc(sizeof(char)*500);
        sprintf(res,"EFFET %s|%s\n", *c->nom,*c->description);
        for (int i=0;i<2;i++){
            char *rep;
            sendMessage(clients[i],res,length(res));
            rep=readMessage(clients[i]);
            free(rep);
        }
    free(res);
    return;
        
    }
}




/*
requires : clients est bien un tableau de clients
assigns : rien
ensures : envoie au client un chaine de caractere qui contient la carte et son effet en suivant le protocole : EFFET nom_carte|description
*/
void afficherEffetCarte_server1(carte c,client *clients){
    if (c != NULL) {
        char *res=malloc(sizeof(char)*500);
        sprintf(res,"EFFET1 %s|%s\n", *c->nom,*c->description);
        for (int i=0;i<2;i++){
            char *rep;
            sendMessage(clients[i],res,length(res));
            rep=readMessage(clients[i]);
            free(rep);
        }
    free(res);
    return;
        
    }
}

/*
requires : f est un tableau de faction et c est un tableau de faction
assigns : rien
ensures : envoie aux clients les scores des deux factions en suivant le protocole : SCORE SCORE_faction1 SCORE_faction2
*/
void afficherScore_server(faction *f,client * c){
    char *res=malloc(sizeof(char)*50);        
    sprintf(res,"SCORE %d %d\n", f[0]->pts_ddrs, f[1]->pts_ddrs);
    for (int i=0;i<2;i++){
        sendMessage(c[i],res,length(res));
        char *rep=readMessage(c[i]);
        free(rep);
    }
    free(res);
}


int main(int argc, char** argv)
{

    /* création du SAP des clients */
    socklen_t cltsSAPlen;
    struct sockaddr cltsSAP;
    getTCPsap(&cltsSAP,&cltsSAPlen,0,"2000");

    /* creation du serveur */
    int sock;
    if ( (sock=socket(PF_INET,SOCK_STREAM,0))==-1 ) {
        fprintf(stderr,"pb socket: %s\n",strerror(errno));
        exit(1);
    }
    if ( bind(sock,&cltsSAP,cltsSAPlen)<0 ) {
        fprintf(stderr,"pb bind: %s\n",strerror(errno));
        exit(1);
    }
    if ( listen(sock,100)!=0 ) {
        fprintf(stderr,"pb listen:%s\n",strerror(errno));
        exit(1);
    }

    while (1){
        // conection des deux joueur
        client * clients = waitConnection(sock);


        // for (int i = 0 ; i < 2 ; i ++) {
        //     // Lancement de la partie
        //     sendMessage(clients[i], "GO\n", 3);
        //     if (strcmp(readMessage(clients[i]),"BOB\n")!=0){
                
        //     }
        // }

        
        // creation plateau
        plateau plate = create_plateau_factions();

        // premier joueur
        int quicommence=premier_joueur();
        if (quicommence==0){
            // demande nom faction
            for (int i = 0 ; i < 2 ; i ++) {
                // lancement partie
                sendMessage(clients[i], "GO\n", 3);
                char * response = readMessage(clients[i]);
                int l=length(response);
                response[l-1]='\0';
                plate->tab_factions[i]->nom=response;
                printf("%s\n", response);
                // free(response); ????????
            }
        }
        else {
            // demande nom faction
            for (int i = 0 ; i < 2 ; i ++) {
                sendMessage(clients[i], "GO\n", 3);
                char * response = readMessage(clients[i]);
                int l=length(response);
                response[l-1]='\0';
                plate->tab_factions[1-i]->nom=response;
                printf("%s\n", response);
                // free(response); ????????
            }
        }

        // On envoie les noms des joueurs aux joueurs
        char PDU[100];
        sprintf(PDU,"NAME %s|%s\n",plate->tab_factions[0]->nom,plate->tab_factions[1]->nom);
        for (int i=0;i<2;i++){
            sendMessage(clients[i],PDU,7+length(plate->tab_factions[0]->nom)+length(plate->tab_factions[1]->nom));
            char *c=readMessage(clients[i]);
            free(c);
        }
        

        while (init_manche(plate)){
            for (int j = 0; j < NB_FACTIONS; j++) {
                pioche(plate->tab_factions[j]); //Dans pioche on met pour chaque carte l'id_faction à la faction correspondante
                char *response=afficherMain_server(plate->tab_factions[j]);
                sendMessage(clients[j],response,length(response));
                response=readMessage(clients[j]);
                free(response);
            }

            // On demande aux joueurs au début de la manche si ils veulent changer leurs mains
            for (int j = 0; j < NB_FACTIONS; j++) {

                if (!deja_repioche(plate->tab_factions[j])) {
                    // printf("test2\n");
                    char *response=afficherMain_server(plate->tab_factions[j]);
                    // int veut_piocher = demanderChangementMain(plate->tab_factions[j]);
                    sendMessage(clients[j],response,length(response));
                    response=readMessage(clients[j]);
                    free(response);
                    sendMessage(clients[j],"REPIOCHE\n",9);
                    response=readMessage(clients[j]);
                    if (strcmp(response,"OUI\n")==0) {
                        free(response);
                        repiocher(plate->tab_factions[j]); //passer le a_pioche à 1
                        response=afficherMain_server(plate->tab_factions[j]); // on affiche le plateau après, à voir si l'un cache l'autre
                        sendMessage(clients[j],response,length(response));
                        free(response);
                        response=readMessage(clients[j]);
                        free(response);
                    }
                    else{
                        free(response);
                    }
                }
            }


            // Chacun son tour on place une carte 
            for (int i = 0; i < NB_CARTE_MAIN; i++) {
                for (int j = 0; j < NB_FACTIONS; j++) {

                    char *response=afficherPlateau_server(plate);
                    sendMessage(clients[j],response,length(response));
                    free(response);
                    
                    response=readMessage(clients[j]);
                    free(response);

                    response=afficherMain_server(plate->tab_factions[j]);
                    sendMessage(clients[j],response,length(response));
                    free(response);

                    response=readMessage(clients[j]);
                    free(response);


                    carte carteAJouer = demanderQuelleCarteJouer_server(plate->tab_factions[j],clients[j]);
                    afficherEffetCarte_server1(carteAJouer,clients);

                    // On demande où le joueur veux poser sa carte
                    // Si l'emplacement n'est pas valide, on recommence
                    int posee = 0;

                    while (!posee) {
                        char *response=afficherPlateau_server(plate);
                        sendMessage(clients[j],response,length(response));
                        free(response);

                        response=readMessage(clients[j]);
                        free(response);

                        int *coordonnees = demanderPositionCarte_server(clients[j]);

                        posee = poser_face_cachee(plate, carteAJouer, coordonnees);


                    }

                    response=afficherPlateau_server(plate);
                    sendMessage(clients[j],response,length(response));
                    free(response);
                    
                    response=readMessage(clients[j]);
                    free(response);

                    response=afficherMain_server(plate->tab_factions[j]);
                    sendMessage(clients[j],response,length(response));
                    free(response);

                    response=readMessage(clients[j]);
                    free(response);
                }
            }

            // On renvoie la main pour etre sur que la main est bien vide chez les clients

            // for (int j=0;j<2;j++){
            //     char *response=afficherMain_server(plate->tab_factions[j]);
            //     sendMessage(clients[j],response,length(response));
            //     free(response);

            //     response=readMessage(clients[j]);
            //     free(response);
            // }


            
            // afficherPlateau_server(plate);

            carte carte_en_jeu = NULL;
            carte derniere_carte = NULL;

            
            // On récupère toujours la carte face cachée la plus en haut à gauche 
            // Si on trouve NULL, c'est que toutes les cartes ont été retournées
            do {

                derniere_carte = carte_en_jeu; // On sauvegarde la dernière carte posée, pour la carte Laurent Prevel
                carte_en_jeu = utilise_carte_haut_gauche(plate);
                afficherEffetCarte_server(carte_en_jeu,clients);
                afficherScore_server(plate->tab_factions,clients);
                
                for (int j=0;j<2;j++){
                    char *response=afficherPlateau_server(plate);
                    sendMessage(clients[j],response,length(response));
                    free(response);
                        
                    response=readMessage(clients[j]);
                    free(response);
                }

            } while (carte_en_jeu != NULL);

            // Si la dernière carte révelée est Laurent Prevel, c'est le joueur qui l'a posée qui gagne
            if (strncmp(*derniere_carte->nom, "Laurent Prevel", 35) == 0) {
                afficherVainqueurManche_server(plate->tab_factions[derniere_carte->id_faction],clients);
                plate->tab_factions[derniere_carte->id_faction]->score_manche += 1;
            } else {
                // Sinon on compte les points DDRS
                if (plate->tab_factions[0]->pts_ddrs > plate->tab_factions[1]->pts_ddrs) {
                    afficherVainqueurManche_server(plate->tab_factions[0],clients);
                    plate->tab_factions[0]->score_manche += 1;
                } else if (plate->tab_factions[0]->pts_ddrs < plate->tab_factions[1]->pts_ddrs) {
                    afficherVainqueurManche_server(plate->tab_factions[1],clients);
                    plate->tab_factions[1]->score_manche += 1;
                } else {
                    // Si c'est égalité, c'est le jour avec la carte la plus en haut à gauche qui gagne

                    carte carte_haut_gauche = cherche_carte_haut_gauche(plate, 1);
                    int gagnant_egalite = carte_haut_gauche->id_faction;

                    afficherVainqueurManche_server(plate->tab_factions[gagnant_egalite],clients);
                    plate->tab_factions[gagnant_egalite]->score_manche += 1;
                }
            }

        }

        // On recherche le joueur qui a gagné le plus de manche
        // Il n'y a pas de possibiltiés d'égalité dans les règles actuelles
        int max = 0;
        int id_meilleur_joueur = 0;
        for (int j = 0; j < NB_FACTIONS; j++) {
            if (plate->tab_factions[j]->score_manche > max) {
                max = plate->tab_factions[j]->score_manche;
                id_meilleur_joueur = j;
            }
        }
        afficherVainqueurPartie_server(plate->tab_factions[id_meilleur_joueur],clients);

        free_plateau(plate);



    }
    
    close(sock);
    return 0;
}