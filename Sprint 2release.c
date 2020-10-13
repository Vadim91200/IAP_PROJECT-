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
#define MSG_SPECIALITE "## consultation des specialites \n"
#define MSG_CONSULTATION_TRAVAILLEURS "la specialite \%s\ peut etre prise en charge par : "
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n"
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_SPECIALITE_TOUS "## consultation des travailleurs competents pour chaque specialite\n"
#define MSG_PROGGRESSION_PASSE "## une reallocation est requise\n"
#define MSG_CONSULTATION_COMMANDE "le client \%s\ a commande : \n"
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

//Donnees--------------------------------------------
//specialites---------------------
#define MAX_SPECIALITES 10
typedef struct specialite {
	Mot nom;
	int cout_horaire;
} Specialite;
typedef struct specialites {
	Specialite tab_specialites[MAX_SPECIALITES];
	unsigned int nb_specialites;
} Specialites;

// travailleurs −−−−−−−−−−−−−−−−−−−−
#define MAX_TRAVAILLEURS 50
typedef struct {
	Mot nom;
	Booleen tags_competences[MAX_SPECIALITES];
} Travailleur;
typedef struct {
	Travailleur tab_travailleurs[MAX_TRAVAILLEURS];
	unsigned int nb_travailleurs;
} Travailleurs;

// client −−−−−−−−−−−−−−−−−−−−−−−−−−
#define MAX_CLIENTS 10
typedef struct {
	Mot nom;
} Client;
typedef struct {
	Client tab_clients[MAX_CLIENTS];
	unsigned int nb_clients;
} Clients;


// Instructions --------------------------------------------------------------- 
// developpe --------------------------- 
void traite_developpe(Specialites* Spe) {
	get_id(Spe->tab_specialites[Spe->nb_specialites].nom);
	Spe->tab_specialites[Spe->nb_specialites].cout_horaire = get_int();
	Spe->nb_specialites += 1;

}
//specialtes--------------
void traite_specialites(Specialites* liste_spe) {
	unsigned int i;
	printf("specialites traitees : ");
	for (i = 0; i < liste_spe->nb_specialites - 1; i++) {
		printf("%s/%d, ", liste_spe->tab_specialites[i].nom, liste_spe->tab_specialites[i].cout_horaire);
	}
	printf("%s/%d\n", liste_spe->tab_specialites[liste_spe->nb_specialites - 1].nom, liste_spe->tab_specialites[liste_spe->nb_specialites - 1].cout_horaire);

}

//nouveau travailleurs-----------------
void traite_embauche(Travailleurs* Worker) {
	Mot nom_travailleur;
	get_id(nom_travailleur);
	unsigned int i;
	unsigned int dejarencontre = 0;
	for (i = 0; i < Worker->nb_travailleurs; i++) {
		if (Worker->nb_travailleurs == 0) {
			break;
		}
		else if (strcmp(nom_travailleur, Worker->tab_travailleurs[i].nom) == 0) {
			unsigned int k;
			for (k = 0; k < 10; k++) {
				Worker->tab_travailleurs[i].tags_competences[k]
			}
			dejarencontre = 1;
			break;
		}
		else
		{
			continue;
		}
	}
	if (dejarencontre == 1){
	
	}
	else
	{
		strcpy(Worker->tab_travailleurs[i].nom, nom_travailleur);
		get_id(Worker->tab_travailleurs[i].tags_competences);
		Worker->nb_travailleurs += 1;
	}
	
}
//nouveau client----------------
void traite_demarche(Clients* Customer) {
	get_id(Customer->tab_clients[Customer->nb_clients].nom); //enregistre les clients
	Customer->nb_clients += 1;
}
// Consultation travailleurs---------------------- (test a ne pas calculer)
void traite_consultation_travailleurs(Travailleurs* list_worker) {
	unsigned int i;
	Mot nom_specialite;
	get_id(nom_specialite);
	if (strcmp(nom_specialite, "tous") == 0)
	{
		for (i = 0; i < list_worker->nb_travailleurs; i++) {
			printf("la specialite %s peut etre prise en charge par : %s \n", list_worker->tab_travailleurs[i].tags_competences, list_worker->tab_travailleurs[i].nom);
		}
	}
	else {
		printf(MSG_CONSULTATION_TRAVAILLEURS, nom_specialite);
		for (i = 0; i <= list_worker->nb_travailleurs-1; i++) {
			if (strcmp(nom_specialite, list_worker->tab_travailleurs[i].tags_competences) == 0){
				printf("%s,", list_worker->tab_travailleurs[i].nom);
			}
		}
		printf("%s\n", list_worker->tab_travailleurs[list_worker->nb_travailleurs].nom);

	}
}

// Consultation commandes----------------
void traite_consultation_commandes(Clients* liste_customer) {
	Mot nom_client;
	get_id(nom_client);
	unsigned int i;
	if (strcmp(nom_client, "tous") == 0)
	{
		for (i = 0; i < liste_customer->nb_clients; i++)
			printf(MSG_CONSULTATION_COMMANDE, liste_customer->tab_clients[i].nom); //Permet d'afficher tous les clients enregistres dans la base
	}
	else {
		for (i = 0; i < liste_customer->nb_clients; i++)
			if (strcmp(nom_client, liste_customer->tab_clients[i].nom) == 0) {
				printf(MSG_CONSULTATION_COMMANDE, liste_customer->tab_clients[i].nom);
			}
	}
}
//Nouvelle commande----------------
void traite_nouvelle_commande() {
	Mot nom_commande;
	Mot nom_client;
	get_id(nom_commande);
	get_id(nom_client);
	printf(MSG_COMMANDE, nom_commande, nom_client);
}
// Consultation de l'avancement des commandes-------------------
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
	Specialites Spe;
	Spe.nb_specialites = 0;
	Travailleurs Worker;
	Worker.nb_travailleurs = 0;
	Clients Customer;
	Customer.nb_clients = 0;
	while (VRAI) {
		get_id(buffer);
		if (strcmp(buffer, "passe") == 0)
		{
			printf(MSG_PROGGRESSION_PASSE);
			continue;
		}
		if (strcmp(buffer, "developpe") == 0) {
			traite_developpe(&Spe);
			continue;
		}
		if (strcmp(buffer, "specialites") == 0) {
			traite_specialites(&Spe);
			continue;
		}
		if (strcmp(buffer, "embauche") == 0) {
			traite_embauche(&Worker);
			continue;
		}
		if (strcmp(buffer, "demarche") == 0) {
			traite_demarche(&Customer);
			continue;
		}
		if (strcmp(buffer, "travailleurs") == 0) {
			traite_consultation_travailleurs(&Worker);
			continue;
		}
		if (strcmp(buffer, "client") == 0) {
			traite_consultation_commandes(&Customer);
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
