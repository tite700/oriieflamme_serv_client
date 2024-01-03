#ifndef ORIIEFLAMME_SERVER_H
#define ORIIEFLAMME_SERVER_H

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

struct p_client {
    int cx;
};

typedef struct p_client * client;


/*
requires : rien
assigns : rien
ensures : renvoie une chaine de caracteres qui contient ce que le client c envoie au serveur
*/
char * readMessage(client c);


/*
requires : message est une chaine de caractere
assigns : rien
ensures : envoie le message au client c
*/
int sendMessage(client c, char * message, int taille);


/*
requires : rien
assigns : rien
ensures : accept deux clients sur le serveur et renvoie un tableau de ces deux clients
*/
client * waitConnection();

void getTCPsap(struct sockaddr* sap, socklen_t*saplen,
               const char *host, const char* port);

// int lire_data(char*buf, int cx, int n);


/*
requires : s est une chaine de caractere
assigns : rien
ensures : renvoie la taille de la chaine de caractere s
*/
int length(char *s);

#endif
