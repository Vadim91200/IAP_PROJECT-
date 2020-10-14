void traite_consultation_travailleurs(Travailleurs* list_worker, Specialites* specialites) {
	unsigned int i, indice;
	Mot nom_specialite;
	get_id(nom_specialite);
	Booleen bool= FAUX;
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
