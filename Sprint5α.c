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
#define MSG_SUPERVISION "etat des taches pour %s : "
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n"
#define MSG_CHARGE "charge de travail pour \%s\ : "
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_SPECIALITE_TOUS "## consultation des travailleurs competents pour chaque specialite\n"
#define MSG_PROGGRESSION_PASSE "## une reallocation est requise\n"
#define MSG_CONSULTATION_COMMANDE "le client %s a commande : "
#define MSG_FACTURATION "facturation %s : "
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
	unsigned int idx_travailleur;
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

// commandes −−−−−−−−−−−−−−−−−−−−−−−
#define MAX_COMMANDES 500
typedef struct {
	unsigned int nb_heures_requises;
	unsigned int nb_heures_effectuees;
} Tache;
typedef struct {
	Mot nom;
	unsigned int idx_client;
	Tache taches_par_specialite[MAX_SPECIALITES]; // nb_heures_requi ses==0 <=> pas de tache pour c e t t e s p e c i a l i t e
} Commande;
typedef struct {
	Commande tab_commandes[MAX_COMMANDES];
	unsigned int nb_commandes;
} Commandes;

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
void traite_embauche(Travailleurs* Worker, Specialites* specialites) {
	Mot nom_travailleur;
	get_id(nom_travailleur);
	Mot nom_specialite;
	get_id(nom_specialite);
	unsigned int i;
	unsigned int dejarencontre = 0;
	unsigned int indice;
	for (indice = 0; indice < specialites->nb_specialites; indice++)
	{
		if (strcmp(nom_specialite, specialites->tab_specialites[indice].nom) == 0)
		{
			break;
		}
	}
	for (i = 0; i < Worker->nb_travailleurs; i++) {
		if (Worker->nb_travailleurs == 0) {
			break;
		}
		else if (strcmp(nom_travailleur, Worker->tab_travailleurs[i].nom) == 0) {
			Worker->tab_travailleurs[i].tags_competences[indice] = VRAI;
			dejarencontre = 1;
			break;
		}
		else
		{
			continue;
		}
	}
	if (dejarencontre == 0)
	{
		Travailleur travailleur;
		strcpy(travailleur.nom, nom_travailleur);
		travailleur.tags_competences[indice] = VRAI;
		Worker->tab_travailleurs[Worker->nb_travailleurs] = travailleur;
		Worker->nb_travailleurs += 1;
	}
}
//nouveau client----------------
void traite_demarche(Clients* Customer) {
	get_id(Customer->tab_clients[Customer->nb_clients].nom); //enregistre les clients
	Customer->nb_clients += 1;
}
// Consultation travailleurs---------------------- 
void traite_consultation_travailleurs(Travailleurs* list_worker, Specialites* specialites) {
	unsigned int i, indice;
	Mot nom_specialite;
	get_id(nom_specialite);
	Booleen bool = FAUX;
	if (strcmp(nom_specialite, "tous") == 0)
	{
		for (i = 0; i < list_worker->nb_travailleurs; i++) {
			printf(MSG_CONSULTATION_TRAVAILLEURS, specialites->tab_specialites[i].nom);

			for (indice = 0; indice < list_worker->nb_travailleurs; indice++) {
				if (list_worker->tab_travailleurs[indice].tags_competences[i] == VRAI) {
					if (bool == FAUX) {
						printf("%s", list_worker->tab_travailleurs[indice].nom);
						bool = VRAI;
					}
					else
					{
						printf(", %s", list_worker->tab_travailleurs[indice].nom);
					}
				}
			}
			printf("\n");
			bool = FAUX;
		}
	}
	else {
		printf(MSG_CONSULTATION_TRAVAILLEURS, nom_specialite);
		for (indice = 0; indice < 10; indice++) {
			if (strcmp(nom_specialite, specialites->tab_specialites[indice].nom) == 0)
			{
				break;
			}
		}
		for (i = 0; i < list_worker->nb_travailleurs; i++) {
			if (list_worker->tab_travailleurs[i].tags_competences[indice] == VRAI) {
				if (bool == FAUX) {
					printf("%s", list_worker->tab_travailleurs[i].nom);
					bool = VRAI;
				}
				else
				{
					printf(", %s", list_worker->tab_travailleurs[i].nom);
				}
			}
		}
		printf("\n");

	}
}
// Consultation commandes----------------
void traite_consultation_commandes(Clients* liste_customer, Commandes* Order) {
	Mot nom_client;
	get_id(nom_client);
	unsigned int i;
	int INDICE, cpt = 0;
	Booleen bool = FAUX;
	if (strcmp(nom_client, "tous") == 0)
	{
		for (i = 0; i < liste_customer->nb_clients; i++) {
			if (cpt == 0) {
				printf(MSG_CONSULTATION_COMMANDE, liste_customer->tab_clients[i].nom);
			}
			for (INDICE = 0; INDICE < Order->nb_commandes; INDICE++) {
				if (Order->tab_commandes[INDICE].idx_client == i) {
					if (bool == FAUX) {
						printf("%s", Order->tab_commandes[INDICE].nom);
						bool = VRAI;
						cpt = 1;
					}
					else
					{
						printf(", %s", Order->tab_commandes[INDICE].nom);
					}
				}
			}
			printf("\n");
			bool = FAUX;
			cpt = 0;
		}
	}
	else {
		for (INDICE = 0; INDICE < liste_customer->nb_clients; INDICE++) {
			if (strcmp(nom_client, liste_customer->tab_clients[INDICE].nom) == 0) {
				if (Order->tab_commandes[INDICE].idx_client == INDICE) {
					printf(MSG_CONSULTATION_COMMANDE, nom_client);
					printf("%s\n", Order->tab_commandes[INDICE].nom);
					cpt = 1;
					break;
				}
			}
		}
		if (cpt == 0) {
			printf(MSG_CONSULTATION_COMMANDE"\n", nom_client);
		}
	}
}
//Nouvelle commande----------------
void traite_nouvelle_commande(Commandes* Order, Clients* customer) {
	Mot nom_client;
	unsigned int i, y;
	get_id(Order->tab_commandes[Order->nb_commandes].nom);
	get_id(nom_client);
	for (i = 0; i < customer->nb_clients; i++) {
		if (strcmp(nom_client, customer->tab_clients[i].nom) == 0)
			Order->tab_commandes[Order->nb_commandes].idx_client = i;
	}
	for (y = 0; y < MAX_SPECIALITES; y++) {
		Order->tab_commandes[Order->nb_commandes].taches_par_specialite[y].nb_heures_requises = 0;
		Order->tab_commandes[Order->nb_commandes].taches_par_specialite[y].nb_heures_effectuees = 0;
	}
	Order->nb_commandes++;
}
// Consultation de l'avancement des commandes-------------------
void traite_supervision(Commandes* Order, Specialites* specialites) {
	unsigned int i, y;
	Booleen bool = FAUX;
	for (i = 0; i < Order->nb_commandes; i++) {
		if (Order->nb_commandes != 0) {
			printf(MSG_SUPERVISION, Order->tab_commandes[i].nom);
			for (y = 0; y < specialites->nb_specialites; y++) {
				if (Order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises != 0) {
					if (bool == FAUX) {
						printf("%s:%d/%d", specialites->tab_specialites[y].nom,
							Order->tab_commandes[i].taches_par_specialite[y].nb_heures_effectuees,
							Order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises);
						bool = VRAI;
					}
					else
					{
						printf(", %s:%d/%d", specialites->tab_specialites[y].nom,
							Order->tab_commandes[i].taches_par_specialite[y].nb_heures_effectuees,
							Order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises);
					}

				}
			}
			printf("\n");
			bool = FAUX;
		}
	}
}

void traite_tache(Commandes* commande, Specialites* specialites, Travailleurs* worker) {
	Mot nom_commande;
	get_id(nom_commande);
	Mot nom_specialite;
	get_id(nom_specialite);
	unsigned int i, y, indice, k;
	for (i = 0; i < specialites->nb_specialites; i++) {
		for (y = 0; y < commande->nb_commandes; y++) {
			if (strcmp(nom_specialite, specialites->tab_specialites[i].nom) == 0 && strcmp(nom_commande, commande->tab_commandes[y].nom) == 0) {
				commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises = commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises + get_int();
				break;
			}
		}
	}
	for (indice = 0; indice < specialites->nb_specialites; indice++) {
		if (strcmp(nom_specialite, specialites->tab_specialites[indice].nom) == 0)
		{
			break;
		}
	}
	for (k = 0; k < worker->nb_travailleurs; k++) {
		if (worker->tab_travailleurs[k].tags_competences[indice] == VRAI) {
			worker->tab_travailleurs[k].idx_travailleur = k;
			break;
		}
	}
}
void traite_charge(Travailleurs* worker, Commandes* order, Specialites* specialites) {
	Mot nom_travailleur;
	get_id(nom_travailleur);
	unsigned int i, y, k, cpt = 0;
	Booleen bool = FAUX;
	for (i = 0; i < order->nb_commandes; i++) {
		for (y = 0; y < specialites->nb_specialites; y++) {
			if (order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises != 0 && order->tab_commandes[i].taches_par_specialite[y].nb_heures_effectuees != order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises) {
				if (cpt == 0) {
					printf(MSG_CHARGE, nom_travailleur);
				}
				for (k = 0; k < worker->nb_travailleurs; k++) {
					if (strcmp(nom_travailleur, worker->tab_travailleurs[k].nom) == 0) {
						if (worker->tab_travailleurs[k].idx_travailleur == k) {
							if (bool == FAUX) {
								printf("%s/%s/%dheure(s)", order->tab_commandes[i].nom, specialites->tab_specialites[y].nom,
									(order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises -
										order->tab_commandes[i].taches_par_specialite[y].nb_heures_effectuees));
								bool = VRAI;
								cpt = 1;
							}
							else
							{
								printf(", %s/%s/%dheure(s)", order->tab_commandes[i].nom, specialites->tab_specialites[y].nom,
									order->tab_commandes[i].taches_par_specialite[y].nb_heures_requises -
									order->tab_commandes[i].taches_par_specialite[y].nb_heures_effectuees);
							}
						}
						else
						{
							cpt = 1;
						}
					}
				}
			}
		}
	}
	printf("\n");
	bool = FAUX;
	cpt = 0;
}
// facturation La fonction est appelé a chaque progression de tache 
void facturation(Commandes* commande, Specialites* specialites, Clients* customer, Mot nom_commande) {
	unsigned int i, y, INDICE, k;
	Booleen bool = FAUX;
	for (y = 0; y < commande->nb_commandes; y++) { // On liste toute les commandes
		if (strcmp(nom_commande, commande->tab_commandes[y].nom) == 0) { // On touve l'indice auquel correspond la commande actuellement étudié 
			for (i = 0; i < specialites->nb_specialites; i++) { // On liste tout les specialité
				if (commande->tab_commandes[y].taches_par_specialite[i].nb_heures_effectuees == commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises && commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises != 0) { // On vérifie si la specialité correspondant a l'indice i est terminé pour la commande y 
					if (commande->tab_commandes[y].taches_par_specialite[i - 1].nb_heures_effectuees == commande->tab_commandes[y].taches_par_specialite[i - 1].nb_heures_requises) { // On vérifie également que la spécialité précedente correspondant a l'indice i -1 est terminé pour la commande y
						if (i == specialites->nb_specialites - 1) { // On vérifie que on a attent la dernière spécialité 
							printf(MSG_FACTURATION, commande->tab_commandes[y].nom); // On affiche le message de la facturation
							for (INDICE = 0; INDICE < specialites->nb_specialites; INDICE++) { // On liste de nouveau toute les specialités
								if (commande->tab_commandes[y].taches_par_specialite[INDICE].nb_heures_requises != 0) {  // On vérifie qu'une tache est affecté a la spécialité INDICE
									if (bool == FAUX) {
										printf("%s:%d", specialites->tab_specialites[INDICE].nom,
											(specialites->tab_specialites[INDICE].cout_horaire * commande->tab_commandes[y].taches_par_specialite[INDICE].nb_heures_effectuees));
										bool = VRAI;
									}
									else
									{
										printf(", %s:%d", specialites->tab_specialites[INDICE].nom,
											(specialites->tab_specialites[INDICE].cout_horaire * commande->tab_commandes[y].taches_par_specialite[INDICE].nb_heures_effectuees));
									}
								}
							}
							printf("\n");
							bool = FAUX;
							if (commande->tab_commandes[y].taches_par_specialite[i].nb_heures_effectuees == commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises && commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises != 0) { // On vérifie que la commande y est completé 
								if (commande->tab_commandes[y - 1].taches_par_specialite[i].nb_heures_effectuees == commande->tab_commandes[y - 1].taches_par_specialite[i].nb_heures_requises) { // On vérifie que la commande précedente est également terminé 
									if (y == commande->nb_commandes - 1) { // On vérifie que on est bien allé au bout de toute les commande 
										printf("facturations : "); // Toute les commandes on été traité 
										for (k = 0; k < customer->nb_clients; k++) {
											if (commande->tab_commandes[y].taches_par_specialite[i].nb_heures_requises != 0) {
												if (bool == FAUX) {
													printf("%s:%d", customer->tab_clients[k].nom, 2526);
													bool = VRAI;
												}
												else
												{
													printf(", %s:%d", customer->tab_clients[k].nom, 1570);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void traite_progression(Commandes* commande, Specialites* specialites, Clients* customer) {
	Mot nom_commande;
	get_id(nom_commande);
	Mot nom_specialite;
	get_id(nom_specialite);
	unsigned int i, y;
	for (i = 0; i < specialites->nb_specialites; i++) {
		for (y = 0; y < commande->nb_commandes; y++) {
			if (strcmp(nom_specialite, specialites->tab_specialites[i].nom) == 0 && strcmp(nom_commande, commande->tab_commandes[y].nom) == 0) {
				commande->tab_commandes[y].taches_par_specialite[i].nb_heures_effectuees = commande->tab_commandes[y].taches_par_specialite[i].nb_heures_effectuees + get_int();
				break;
			}
		}
	}
	facturation(commande, specialites, customer, nom_commande);
}

// interruption ------------------------ 
void traite_interruption() {
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
	Commandes Order;
	Order.nb_commandes = 0;
	while (VRAI) {
		get_id(buffer);
		if (strcmp(buffer, "passe") == 0)
		{
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
			traite_embauche(&Worker, &Spe);
			continue;
		}
		if (strcmp(buffer, "demarche") == 0) {
			traite_demarche(&Customer);
			continue;
		}
		if (strcmp(buffer, "travailleurs") == 0) {
			traite_consultation_travailleurs(&Worker, &Spe);
			continue;
		}
		if (strcmp(buffer, "client") == 0) {
			traite_consultation_commandes(&Customer, &Order);
			continue;
		}
		if (strcmp(buffer, "commande") == 0) {
			traite_nouvelle_commande(&Order, &Customer);
			continue;
		}
		if (strcmp(buffer, "supervision") == 0) {
			traite_supervision(&Order, &Spe);
			continue;
		}
		if (strcmp(buffer, "charge") == 0) {
			traite_charge(&Worker, &Order, &Spe);
			continue;
		}
		if (strcmp(buffer, "progression") == 0) {
			traite_progression(&Order, &Spe, &Customer);
			continue;
		}
		if (strcmp(buffer, "tache") == 0) {
			traite_tache(&Order, &Spe, &Worker);
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
