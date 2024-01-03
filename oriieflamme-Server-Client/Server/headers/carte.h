#ifndef CARTE_H
#define CARTE_H
#include "constante.h"
typedef struct p * carte;


/*
on crée une structure pour représenter les cartes
on stock dans cette structure : le nom de la carte qui nous permettra de l'identifier plus tard
                                sa description
                                son nombre d'occurence pour calculer la probabilité de la piocher
                                un entier id_faction pour savoir a quelle faction appartient la carte sur le plateau (-1 par défaut)
                                un entier retournee pour savoir si la carte est face cachee (0) ou face visible (1)
*/
struct p {
    const char** nom;
    const char** description;
    int nb_occur;
    int id_faction;
    int retournee;
};

/*
requires : rien
assigns : rien
ensures : réserve l'espace memoire pour une carte
*/
carte init_carte();



/*
assigns : rien
requires : rien
ensures : libere l'espace reserver pour la carte
*/
void free_carte(carte c);


/*
requires : rien
assigns : un tableau tab de cartes
ensures : mélange le tableau de carte
*/
// void melangeCarte(char* tab[],int size);


/*
// CREATION DES CARTE DU JEU
carte fise=init_carte();
fise->nom="Fise";
fise->description="La faction qui a posé cette carte gagne 1 point DDRS.";
fise->retournee=0;
fise->nb_occur=NB_OCCUR_FISE;

carte fisa=init_carte();
fisa->nom="Fisa";
fisa->description="La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.";
fisa->retournee=0;
fisa->nb_occur=NB_OCCUR_FISA;

carte fc=init_carte();
fc->nom="Fc";
fc->description="La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon";
fc->retournee=0;
fc->nb_occur=NB_OCCUR_FC;

carte ecologiie=init_carte();
ecologiie->nom="Eclogiie";
ecologiie->description="	La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.";
ecologiie->retournee=0;
ecologiie->nb_occur=NB_OCCUR_Ecologiie;

carte liiens=init_carte();
liiens->nom="Liiens";
liiens->description="	Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.";
liiens->retournee=0;
liiens->nb_occur=NB_OCCUR_Liiens;

carte soiree_sans_alcool=init_carte();
soiree_sans_alcool->nom="Soiree sans alcool";
soiree_sans_alcool->description="	Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.";
soiree_sans_alcool->retournee=0;
soiree_sans_alcool->nb_occur=NB_OCCUR_Soiree_sans_alcool;

carte alcool=init_carte();
alcool->nom="Alcool";
alcool->description="Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).";
alcool->retournee=0;
alcool->nb_occur=NB_OCCUR_Alcool;

carte cafe=init_carte();
cafe->nom="Cafe";
cafe->description="	Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";
cafe->retournee=0;
cafe->nb_occur=NB_OCCUR_Cafe;

carte the=init_carte();
the->nom="The";
the->description="Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";
the->retournee=0;
the->nb_occur=NB_OCCUR_The;

carte ecocup=init_carte();
ecocup->nom="Ecocup";
ecocup->description="	Cette carte est sans effet.";
ecocup->retournee=0;
ecocup->nb_occur=NB_OCCUR_Ecocup;

carte reprographie=init_carte();
reprographie->nom="Reprographie";
reprographie->description="La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).";
reprographie->retournee=0;
reprographie->nb_occur=NB_OCCUR_Reprographie;

carte isolation_du_batiment=init_carte();
isolation_du_batiment->nom="Isolation du batiment";
isolation_du_batiment->description="Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.";
isolation_du_batiment->retournee=0;
isolation_du_batiment->nb_occur=NB_OCCUR_Isolation_du_batiment;

carte parcours_sobiete_numerique=init_carte();
parcours_sobiete_numerique->nom="Parcours sobiete numerique";
parcours_sobiete_numerique->description="Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.";
parcours_sobiete_numerique->retournee=0;
parcours_sobiete_numerique->nb_occur=NB_OCCUR_Parcours_sobiete_numerique;

carte heures_supplementaires=init_carte();
heures_supplementaires->nom="Heures supplementaires";
heures_supplementaires->description="La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).";
heures_supplementaires->retournee=0;
heures_supplementaires->nb_occur=NB_OCCUR_Heures_supp;

carte kahina_bouchama=init_carte();
kahina_bouchama->nom="Kahina Bouchama";
kahina_bouchama->description="Supprimez une carte non retournée du plateau choisie au hasard.	";
kahina_bouchama->retournee=0;
kahina_bouchama->nb_occur=NB_OCCUR_Kahina_Bouchama;

carte kevin_goilard=init_carte();
kevin_goilard->nom="Kevin Goilard";
kevin_goilard->description="Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.";
kevin_goilard->retournee=0;
kevin_goilard->nb_occur=NB_OCCUR_Kevin_Goilard;

carte massinissa_merabet=init_carte();
massinissa_merabet->nom="Massinissa Merabet";
massinissa_merabet->description="La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.";
massinissa_merabet->retournee=0;
massinissa_merabet->nb_occur=NB_OCCUR_Massinissa_Merabet;

carte vitera_y=init_carte();
vitera_y->nom="Vitera Y";
vitera_y->description="La faction qui a le moins de points DDRS gagne 3 points DDRS.";
vitera_y->retournee=0;
vitera_y->nb_occur=NB_OCCUR_Vitera_Y;

carte jonas_senizergues=init_carte();
jonas_senizergues->nom="Jonas Senizergues";
jonas_senizergues->description="Supprimez toutes les cartes Heures supplémentaires retournées du plateau.";
jonas_senizergues->retournee=0;
jonas_senizergues->nb_occur=NB_OCCUR_Jonas_Senizergues;

carte fetia_bannour=init_carte();
fetia_bannour->nom="Fetia Bannour";
fetia_bannour->description="Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.";
fetia_bannour->retournee=0;
fetia_bannour->nb_occur=NB_OCCUR_Fetia_Bannour;

carte catherine_dubois=init_carte();
catherine_dubois->nom="Catherine Dubois";
catherine_dubois->description="	Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.";
catherine_dubois->retournee=0;
catherine_dubois->nb_occur=NB_OCCUR_Catherine_Dubois;

carte anne_laure_ligozat=init_carte();
anne_laure_ligozat->nom="Anne-Laure Ligozat";
anne_laure_ligozat->description="Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).";
anne_laure_ligozat->retournee=0;
anne_laure_ligozat->nb_occur=NB_OCCUR_Anne_Laure_Ligozat;

carte guillaume_burel=init_carte();
guillaume_burel->nom="Guillaume Burel";
guillaume_burel->description="Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.";
guillaume_burel->retournee=0;
guillaume_burel->nb_occur=NB_OCCUR_Guillaume_Burel;

carte christophe_mouilleron=init_carte();
christophe_mouilleron->nom="Christophe Mouilleron";
christophe_mouilleron->description="Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.";
christophe_mouilleron->retournee=0;
christophe_mouilleron->nb_occur=NB_OCCUR_Christophe_Mouilleron;

carte thomas_lim=init_carte();
thomas_lim->nom="Thomas Lim";
thomas_lim->description="Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.";
thomas_lim->retournee=0;
thomas_lim->nb_occur=NB_OCCUR_Thomas_Lim;

carte julien_forest=init_carte();
julien_forest->nom="Julien Forest";
julien_forest->description="	La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.";
julien_forest->retournee=0;
julien_forest->nb_occur=NB_OCCUR_Julien_Forest;

carte dimitri_watel=init_carte();
dimitri_watel->nom="Dimitri Watel";
dimitri_watel->description="La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.";
dimitri_watel->retournee=0;
dimitri_watel->nb_occur=NB_OCCUR_Dimitri_Watel;

carte djibril_aurelien_dembele_cabot=init_carte();
djibril_aurelien_dembele_cabot->nom="Djibril-Aurelien Dembele-Cabot";
djibril_aurelien_dembele_cabot->description="S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";
djibril_aurelien_dembele_cabot->retournee=0;
djibril_aurelien_dembele_cabot->nb_occur=NB_OCCUR_Djibril_Aurelien_Dembele_Cabot;

carte eric_lejeune=init_carte();
eric_lejeune->nom="Eric Lejeune";
eric_lejeune->description="	Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.";
eric_lejeune->retournee=0;
eric_lejeune->nb_occur=NB_OCCUR_Eric_Lejeune;

carte lucienne_pacave=init_carte();
lucienne_pacave->nom="Lucienne Pacave";
lucienne_pacave->description="S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";
lucienne_pacave->retournee=0;
lucienne_pacave->nb_occur=NB_OCCUR_Lucienne_Pacave;

carte katrin_salhab=init_carte();
katrin_salhab->nom="Katrin Salhab";
katrin_salhab->description="Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.";
katrin_salhab->retournee=0;
katrin_salhab->nb_occur=NB_OCCUR_Katrin_Salhab;

carte laurent_prevel=init_carte();
laurent_prevel->nom="Laurent Prevel";
laurent_prevel->description="Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions.";
laurent_prevel->retournee=0;
laurent_prevel->nb_occur=NB_OCCUR_Laurent_Prevel;

char * nom[32]=["Fise";"Fisa";"Fc";"Ecologiie";"Liiens";"Soirée sans alcool";"Alcool";"Café";"Thé";"Ecocup";"Reprographie";"Isolation du batiment";"Parcours sobriété numérique";"Heures supplémentaires";"Kahina Bouchama";"Kevin Goilard";"Massinissa Merabet";"Vitéra Y";"Jonas Senizergues";"Fetia Bannour";"Catherine Dubois";"Anne-Laure Ligozat";"Guillaume Burel";"Christophe Mouilleron";"Thomas Lim";"Julien Forest";"Dimitri Watel";"Djibril-Aurélien Dembele-Cabot";"Eric Lejeune";"Lucienne Pacavé";"Katrin Salhab";"Laurent Prével"];
char * description[32]=["La faction qui a posé cette carte gagne 1 point DDRS.";"	La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.";"	La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon";"La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.";"Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.";"	Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.";"Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).";"Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";"Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.";"Cette carte est sans effet.";"	La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).";"Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.";"Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.";"La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).";"Supprimez une carte non retournée du plateau choisie au hasard.	";"	Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.";"La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.";"La faction qui a le moins de points DDRS gagne 3 points DDRS.";"Supprimez toutes les cartes Heures supplémentaires retournées du plateau.";"Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.";"Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.";"Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).";"Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.";"Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.";"Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.";"	La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.";"La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.";"S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";"Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.";"	S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.";"Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.";"Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions."]

// carte =init_carte();
// ->nom="";
// ->description="";
// ->retournee=0;
// ->nb_occur=NB_OCCUR_;


//Tableau de carte de jeu
int nb_carte_tot=0;
carte tab_carte[32];
tab_carte[0]=fise;
tab_carte[1]=fisa;
tab_carte[2]=fc;
tab_carte[3]=ecologiie;
tab_carte[4]=liiens;
tab_carte[5]=soiree_sans_alcool;
tab_carte[6]=alcool;
tab_carte[7]=cafe;
tab_carte[8]=the;
tab_carte[9]=ecocup;
tab_carte[10]=reprographie;
tab_carte[11]=isolation_du_batiment;
tab_carte[12]=parcours_sobiete_numerique;
tab_carte[13]=heures_supplementaires;
tab_carte[14]=kahina_bouchama;
tab_carte[15]=kevin_goilard;
tab_carte[16]=massinissa_merabet;
tab_carte[17]=vitera_y;
tab_carte[18]=jonas_senizergues;
tab_carte[19]=fetia_bannour;
tab_carte[20]=catherine_dubois;
tab_carte[21]=anne_laure_ligozat;
tab_carte[22]=guillaume_burel;
tab_carte[23]=christophe_mouilleron;
tab_carte[24]=thomas_lim;
tab_carte[25]=julien_forest;
tab_carte[26]=dimitri_watel;
tab_carte[27]=djibril_aurelien_dembele_cabot;
tab_carte[28]=eric_lejeune;
tab_carte[29]=lucienne_pacave;
tab_carte[30]=katrin_salhab;
tab_carte[31]=laurent_prevel;

//Nombre de carte total dans la pioche
for (int i=0;i<32;i+=1){
    nb_carte_tot+=tab_carte[i]->nb_occur;
}
#define NB_CARTE_TOTAL nb_carte_tot

carte pioche_jeu[NB_CARTE_TOTAL];
int k=0;
for (int i=0;i<32;i+=1){
    for (int j=0;j<tab_carte[i]->nb_occur;j+=1){
        pioche_jeu[k]=tab_carte[i];
        k+=1;
    }
}
//Tableau de carte de la pioche
#define PIOCHE_JEU pioche_jeu;*/

#endif
