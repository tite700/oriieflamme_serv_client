#include "../headers/server.h"


/*
requires : rien
assigns : rien
ensures : renvoie une chaine de caracteres qui contient ce que le client c envoie au serveur
*/
char * readMessage(client c) {

    char * response = calloc(258,sizeof(char));
    int i = 0;
    char temp;
    // On lit tant que on ne lit pas de \n
    do {
        read(c->cx, &temp, 1);
        // parfois les \0 se glisse dans la chaine, ce qui fausse la lecture, donc on les enleve
        if (temp!='\0'){
            response[i] = temp;
            i++;
        }
    } while (temp != '\n');
    return response;
}


/*
requires : message est une chaine de caractere
assigns : rien
ensures : envoie le message au client c
*/
int sendMessage(client c, char * message, int taille) {
    return write(c->cx,message,taille);
}


/*
requires : s est une chaine de caractere
assigns : rien
ensures : renvoie la taille de la chaine de caractere s
*/
int length(char *s){
    int i=0;
    while (s[i]!='\0'){
        i++;
    }
    return i;
}

void getTCPsap(struct sockaddr* sap, socklen_t*saplen,
               const char *host, const char* port)
{
    int status;
    struct addrinfo hints,*found;
    memset(&hints,0,sizeof(hints));
    hints.ai_flags    = host!=0 ? 0 : AI_PASSIVE;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    status=getaddrinfo(host,port,&hints,&found);
    if ( status!=0 ) {
        fprintf(stderr,"pb getaddrinfo : %s\n",gai_strerror(status));
        exit(1);
    }
    *sap    = *found->ai_addr;
    *saplen =  found->ai_addrlen;

    freeaddrinfo(found);
}


/*
requires : rien
assigns : rien
ensures : accept deux clients sur le serveur et renvoie un tableau de ces deux clients
*/
client * waitConnection(int sock) {

    client * clients = malloc(sizeof (client) * 2);

    int nb_connected = 0;


    // Pour chaque client qui se connecte, il doit envoyer JOIN a sa connection puis OK pour repondre au WAIT du serveur, sinon on ferme sa conection, 
    while ( nb_connected != 2) {
        int cx;
        struct sockaddr cltSAP;
        socklen_t cltSAPlen = sizeof(cltSAPlen);

        /* creation du flux de communication (cx) */
        if ((cx = accept(sock, &cltSAP, &cltSAPlen)) == -1) {
            printf("pb accept : sock=%d : %s\n",sock, strerror(errno));
            exit(1);
        }

        clients[nb_connected] = malloc(sizeof (client));
        clients[nb_connected]->cx = cx;

        // Verif conection
        char *PDU=readMessage(clients[nb_connected]);
        if (strcmp(PDU,"JOIN\n")!=0){
            free(PDU);
            close(cx);
        }
        else {
            sendMessage(clients[nb_connected],"OK\n",3);
            sendMessage(clients[nb_connected],"WAIT\n",5);
            char * recu = readMessage(clients[nb_connected]);
            if (strcmp(recu, "OK\n")!=0){
                free(recu);
                close(cx);
            }
            else{
                free(recu);
            }
            nb_connected++;
            free(PDU);
        }


    }

    return clients;
}