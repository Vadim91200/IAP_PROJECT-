#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

// Messages emis par les instructions -----------------------------------------
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n" 
#define MSG_INTERRUPTION "## fin de programme\n" 
#define MSG_EMBAUCHE "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n" 
#define MSG_SPECIALITE "## consultation des specialites\n"
#define MSG_CONSULTATION_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n"
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_CONSULTATION_COMMANDE "## consultation des commandes effectuees par \"%s\"\n"
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n"
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_SPECIALITE_TOUS "## consultation des travailleurs competents pour chaque specialite\n"
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n"
#define MSG_PROGGRESSION_PASSE "## une reallocation est requise\n"
// Lexemes -------------------------------------------------------------------- 
#define LGMOT 35
#define NBCHIFFREMAX 5 
typedef char Mot[LGMOT + 1];
void get_id(Mot id) {
	scanf("%s", id);
	if (EchoActif) printf(">>echo %s\n", id);
}
int get_int() {
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);
	if (EchoActif) printf(">>echo %s\n", buffer);
	return atoi(buffer);
}
// Donnees
// s p e c i a l i t e s −−−−−−−−−−−−−−−−−−−−−
#define MAX_SPECIALITES 10
typedef struct{
Mot nom;
int cout_horaire;
} Specialite;
typedef struct{
Specialite tab_specialites[MAX_SPECIALITES];
unsigned int nb_specialites;
} Specialites;
// travailleurs −−−−−−−−−−−−−−−−−−−−
#define MAX_TRAVAILLEURS 50
typedef struct{
Mot nom;
Booleen tags_competences[MAX_SPECIALITES];
} Travailleur;
typedef struct{
Travailleur tab_travailleurs[MAX_TRAVAILLEURS];
unsigned int nb_travailleurs;
} Travailleurs;
// client −−−−−−−−−−−−−−−−−−−−−−−−−−
#define MAX_CLIENTS 10
typedef struct{
Mot tab_clients[MAX_CLIENTS];
unsigned int nb_clients;
} Clients;
// Instructions --------------------------------------------------------------- 
// developpe --------------------------- 
void traite_developpe() {
	Mot nom_specialite;
	get_id(nom_specialite);
	int cout_horaire = get_int();
	printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}
void traite_specialites() {
	printf(MSG_SPECIALITE);
}

void traite_embauche() {
	Mot nom_travailleur;
	Mot nom_specialite;
	get_id(nom_travailleur);
	get_id(nom_specialite);
	printf(MSG_EMBAUCHE, nom_travailleur, nom_specialite);
}
void traite_demarche() {
	Mot nom_client;
	get_id(nom_client);
	printf(MSG_DEMARCHE, nom_client);
}

void traite_consultation_travailleurs() {
	Mot nom_specialite;
	get_id(nom_specialite);
	if (strcmp(nom_specialite, "tous") == 0)
	{
		printf(MSG_SPECIALITE_TOUS, nom_specialite, nom_specialite);
	}
	else {
		printf(MSG_CONSULTATION_TRAVAILLEURS, nom_specialite);
	}
}
void traite_consultation_commandes() {
	Mot nom_client;
	get_id(nom_client);
	if (strcmp(nom_client, "tous") == 0)
	{
		printf(MSG_CLIENT_TOUS, nom_client);
	}
	else {
		printf(MSG_CONSULTATION_COMMANDE, nom_client);
	}
}
void traite_nouvelle_commande() {
	Mot nom_commande;
	Mot nom_client;
	get_id(nom_commande);
	get_id(nom_client);
	printf(MSG_COMMANDE, nom_commande, nom_client);
}
void traite_supervision() {
	printf(MSG_SUPERVISION);
}
void traite_tache() {
	Mot nom_commande;
	Mot nom_specialite;
	get_id(nom_commande);
	get_id(nom_specialite);
	int nombres_d_heures = get_int();
	printf(MSG_TACHE, nom_commande, nom_specialite, nombres_d_heures);
}
void traite_charge() {
	Mot nom_travailleur;
	get_id(nom_travailleur);
	printf(MSG_CHARGE, nom_travailleur);

}
void traite_progression() {
	Mot nom_commande;
	get_id(nom_commande);
	Mot nom_specialte;
	get_id(nom_specialte);
	int heures;
	heures = get_int();
	printf(MSG_PROGRESSION, nom_commande, nom_specialte, heures);
}
// interruption ------------------------ 
void traite_interruption() {
	printf(MSG_INTERRUPTION);
}
// Fonction prennant en paramètre la nouvelle spécialité et le cout horaire

//Boucle principale ---------------------------------------------------------- 
int main(int argc, char* argv[]) {
	if (argc >= 2 && strcmp("echo", argv[1]) == 0) {
		EchoActif = VRAI;
	}
	Mot buffer;
	while (VRAI) {
		get_id(buffer);
		if (strcmp(buffer, "passe") == 0)
		{
			printf(MSG_PROGGRESSION_PASSE);
			continue;
		}
		if (strcmp(buffer, "developpe") == 0) {
			traite_developpe();
			continue;
		}
		if (strcmp(buffer, "specialites") == 0) {
			traite_specialites();
			continue;
		}
		if (strcmp(buffer, "embauche") == 0) {
			traite_embauche();
			continue;
		}
		if (strcmp(buffer, "demarche") == 0) {
			traite_demarche();
			continue;
		}
		if (strcmp(buffer, "travailleurs") == 0) {
			traite_consultation_travailleurs();
			continue;
		}
		if (strcmp(buffer, "client") == 0) {
			traite_consultation_commandes();
			continue;
		}
		if (strcmp(buffer, "commande") == 0) {
			traite_nouvelle_commande();
			continue;
		}
		if (strcmp(buffer, "supervision") == 0) {
			traite_supervision();
			continue;
		}
		if (strcmp(buffer, "charge") == 0) {
			traite_charge();
			continue;
		}
		if (strcmp(buffer, "progression") == 0) {
			traite_progression();
			continue;
		}
		if (strcmp(buffer, "tache") == 0) {
			traite_tache();
			continue;
		}
		if (strcmp(buffer, "interruption") == 0) {
			traite_interruption();
			break;
		}
		printf("!!! instruction inconnue >%s< !!!\n", buffer);
	}
	return 0;
}
