void tour_piece_ig2(COULP couleurJoueur, int *nbrePionJoueur);
void afficher_gagnant(int nbrePionJ1,int nbrePionJ2);
BOOL redemander_partie(int nbrePionJ1,int nbrePionJ2);


void afficher_gagnant(int nbrePionJ1,int nbrePionJ2)
{
	POINT ptTexteGagnant;
	
	ptTexteGagnant.x=50; ptTexteGagnant.y=HAUT_FENETRE-50;
	
	if( tester_fin_jeu(coul1,nbrePionJ1) == 1)
	{
		aff_pol("Le joueur 1 n'a plus de pion. Le joueur 2 gagne!",20,ptTexteGagnant,blanc);
	}
	
	if( tester_fin_jeu(coul2,nbrePionJ2) == 1)
	{
		aff_pol("Le joueur 2 n'a plus de pion. Le joueur 1 gagne!",20,ptTexteGagnant,blanc);
	}
	
	
	if( tester_fin_jeu(coul1,nbrePionJ1) == 2)
	{
		aff_pol("Le joueur 1 est bloqué. Le joueur 2 gagne!",20,ptTexteGagnant,blanc);
	}
	
	if( tester_fin_jeu(coul2,nbrePionJ2) == 2)
	{
		aff_pol("Le joueur 2 est bloqué. Le joueur 1 gagne!",20,ptTexteGagnant,blanc);
	}
	
	affiche_all();
}

BOOL redemander_partie(int nbrePionJ1,int nbrePionJ2)
{
	POINT ptOui,ptNon,clicRedemanderPartie;
	BOOL rejouer=false;

	ptOui.x=(LARG_FENETRE/3)+150;ptOui.y=HAUT_FENETRE/2;
	ptNon.x=(LARG_FENETRE/3)+250;ptNon.y=ptOui.y;
	
	fill_screen(noir);
	afficher_gagnant(nbrePionJ1,nbrePionJ2);
	afficher_texte_redemander_partie(ptOui,ptNon);
	clicRedemanderPartie=recuperer_clic_redemander_partie(ptOui,ptNon);
	rejouer=savoir_si_rejouer_partie(ptOui,ptNon,clicRedemanderPartie);
	
	return rejouer;
}


void tour_piece_ig2(COULP couleurJoueur, int *nbrePionJoueur)
{
	int positionCasesLibres = 0, positionCasesLibresAttaque = 0;
	POINT centreCasePionChoisi, centreCaseDestination;
	NUMCASE numCasePionChoisi, numCaseDestination;
	BOOL multiAttaque = 0;
	
	do
	{
		effacer_cases_libres_choisies_ig2(centreCasePionChoisi,positionCasesLibres,positionCasesLibresAttaque);
		choisir_pion_valide_ig2(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
		trouver_cases_libres_ig2(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&positionCasesLibres,&positionCasesLibresAttaque);
		do
		{
			choisir_destination_ig2(centreCasePionChoisi,&centreCaseDestination,&numCaseDestination);
			if( !multiAttaque && est_coup_valide_deplacement(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig2(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, positionCasesLibres, positionCasesLibresAttaque, nbrePionJoueur);
				return;
			}
			if(est_coup_valide_attaque(numCasePionChoisi, numCaseDestination, couleurJoueur))
			{
				bouger_pion_choisi_ig2(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, positionCasesLibres, positionCasesLibresAttaque, nbrePionJoueur);
				if(donner_position_cases_libres_attaque(numCaseDestination, couleurJoueur))
				{
					
					// Cette partie doit être revue
					printf("Voulez-vous continuer le tour en attaquant de nouveau ? (o/n)\n"); // Ici, il faut demander au joueur s'il veut attaquer une autre fois
					char choix;
					scanf(" %c", &choix);
					if(choix == 'n')
					{
						printf("OK, tour terminé !\n");
						return;
					}
					else
					{
						numCasePionChoisi.ligne = numCaseDestination.ligne;
						numCasePionChoisi.colonne = numCaseDestination.colonne;
						printf("OK, vous allez pouvoir attaquer de nouveau !\n");
						multiAttaque = 1;
					}
					// Cette partie doit être revue
				}
				else
					return;
			}
			else if( !multiAttaque)
				break;
		}while(1);
	}while(1);
	affiche_all();
}



int main()
{
	BOOL rejouer = true;
	int igChoisi = 0, nbrePionJ1 = 20, nbrePionJ2 = 20;
	int *nbrePionAutreJoueur = &nbrePionJ2;
	COULP couleurJoueur = coul1;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do
	{
		initialiser_plateau();
		afficher_ecran_titre(&igChoisi);
		afficher_ecran_jeu_selon_ig(igChoisi);
		do
		{
			nbrePionAutreJoueur = (couleurJoueur == coul1) ? &nbrePionJ2 : &nbrePionJ1;
			if(igChoisi == 1)
			{
				tour_piece_ig1(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_joueur_ig1(&couleurJoueur);
			}
			else if(igChoisi == 2)
			{
				tour_piece_ig2(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_joueur_ig2(&couleurJoueur);
			}
		}while( !est_fin_jeu_dans_terminal(couleurJoueur, *nbrePionAutreJoueur));
		rejouer = redemander_partie(nbrePionJ1,nbrePionJ2);
	}while(rejouer);
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}
