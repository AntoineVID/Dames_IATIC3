void afficher_plateau_ig2();

void afficher_cases_libres_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);
void effacer_cases_libres_choisies_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);

void choisir_destination_ig2(POINT centreCasePionChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination);
void effacer_piece_case_orig_ig2(POINT centreCasePionChoisi);
void enlever_pion_qui_subit_attaque_ig2(POINT centreCasePionChoisi,int positionCasesLibresAttaque);

void afficher_exemple_ecran_titre_ig1(POINT ptTitreIg1);
void afficher_exemple_ecran_titre_ig2(POINT ptTitreIg2);
void afficher_choisir_interface();
POINT recuperer_clic_choix_ig();

void choisir_pion_valide_ig1(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi); //SUPPRIMER choisir_pion_valide (sans ig à la fin)
void choisir_pion_valide_ig2(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi); //SUPPRIMER choisir_pion_valide (sans ig à la fin)

NUMCASE convertir_numCase_ig1_vers_ig2(NUMCASE numCaseIg1); //Ajouté
NUMCASE convertir_numCase_ig2_vers_ig1(NUMCASE numCaseIg2); //Ajouté

void trouver_cases_libres_ig2(POINT centrePionChoisi,NUMCASE numCasePionchoisi,COULP couleurJoueur,int *positionCasesLibres,int *positionCasesLibresAttaque);


void afficher_piece_ig2(POINT ptRondCentre,int ligne,int colonne)
{
	COULEUR couleur;
	couleur = convertir_joueur_couleur(plateau[colonne][ligne].coulP);
	if( (plateau[colonne][ligne].typeP == pion) || (plateau[colonne][ligne].typeP == dame) )
	{
		afficher_piece_rond(ptRondCentre,couleur);
	}
		
	if(plateau[colonne][ligne].typeP == dame)
	{
		afficher_piece_rond_dame(ptRondCentre);
	}
	
}

void afficher_cases_libres_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque)
{
	POINT centrebgCaseLibre,centrehdCaseLibre;
	
	/* Cases Normales */
	if(positionCasesLibres%2>0) //rond haut droite (à la base haut gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
		
	}
	
	if(positionCasesLibres%4>1) //rond bas droit (à la base haut droit)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibres%8>3) //rond haut gauche (à la base bas gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-0.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibres%16>7) //rond bas gauche ( à la base bas droite)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	/* Cases Attaque */
	if(positionCasesLibresAttaque%2>0) //rond haut droite (à la base haut gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
		
	}
	
	if(positionCasesLibresAttaque%4>1) //rond bas droit (à la base haut droit)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibresAttaque%8>3) //rond haut gauche (à la base bas gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-2.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibresAttaque%16>7) //rond bas gauche ( à la base bas droite)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_LIBRE);
	}
	
	affiche_all();
}

void effacer_cases_libres_choisies_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque)
{
	POINT centrebgCaseLibre,centrehdCaseLibre;
	
	/* Cases Normales */
	if(positionCasesLibres%2>0) //rond haut droite (à la base haut gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibres%4>1) //rond bas droit (à la base haut droit)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibres%8>3) //rond haut gauche (à la base bas gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-0.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibres%16>7) //rond bas gauche ( à la base bas droite)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-0.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-0.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	/* Cases Attaque */
	if(positionCasesLibresAttaque%2>0) //rond haut droite (à la base haut gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}

	if(positionCasesLibresAttaque%4>1) //rond bas droit (à la base haut droit)
	{
		centrebgCaseLibre.x=centrePionChoisi.x+1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x+2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibresAttaque%8>3) //rond haut gauche (à la base bas gauche)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-2.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y+1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibresAttaque%16>7) //rond bas gauche ( à la base bas droite)
	{
		centrebgCaseLibre.x=centrePionChoisi.x-1.5*LARG_CASE;
		centrebgCaseLibre.y=centrePionChoisi.y-1.5*LARG_CASE;
		centrehdCaseLibre.x=centrePionChoisi.x-2.5*LARG_CASE;
		centrehdCaseLibre.y=centrePionChoisi.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(centrebgCaseLibre,centrehdCaseLibre,COULEUR_CASE_JOUEURS);
	}
		affiche_all();
}

void choisir_destination_ig2(POINT centreCasePionChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination)
{
	POINT clicCaseDestination;
	
	afficher_texte_choix_destination();
	clicCaseDestination=recuperer_clic_pos_plateau();
	effacer_texte_choix_destination();

	*centreCaseDestination=convertir_clic_en_centreCase(clicCaseDestination);
	*numCaseDestination=convertir_centreCase_en_numCase(*centreCaseDestination);
	*numCaseDestination=convertir_numCase_ig2_vers_ig1(*numCaseDestination);
}

void effacer_piece_case_orig_ig2(POINT centreCasePionChoisi)
{
	draw_fill_circle(centreCasePionChoisi,LONGUEUR_PIECE/2,COULEUR_CASE_JOUEURS);
}

void afficher_exemple_ecran_titre_ig1(POINT ptTitreIg1)
{
	int i=0,j=0;
	POINT ptCentreCase;
	
	ptCentreCase.x=100;ptCentreCase.y=150;
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				afficher_case_ig1(ptCentreCase,COULEUR_CASE_JOUEURS);
				
				if(i<2)
				{
					afficher_piece_triangle_haut(ptCentreCase,COULEUR_JOUEUR1);
					afficher_piece_triangle_bas(ptCentreCase,COULEUR_JOUEUR1);
				}
				
				if(i>2)
				{
					afficher_piece_triangle_haut(ptCentreCase,COULEUR_JOUEUR2);
					afficher_piece_triangle_bas(ptCentreCase,COULEUR_JOUEUR2);	
				}
			}
			
			else
			{
				afficher_case_ig1(ptCentreCase,COULEUR_CASE_VIDE);
			}
		
			ptCentreCase.x+=LARG_CASE;
		}
		
		ptCentreCase.x=100;
		ptCentreCase.y+=LARG_CASE;
	}
	
	affiche_all();
}

void afficher_exemple_ecran_titre_ig2(POINT ptTitreIg2)
{
	int i=0,j=0;
	POINT ptbgCase,pthdCase,ptCentreCase;

	ptbgCase.x=440;ptbgCase.y=120;
	pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y=ptbgCase.y+LARG_CASE;
	ptCentreCase.x=440+LARG_CASE/2;ptCentreCase.y=120+LARG_CASE/2;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_VIDE);
				
				if(j<2)
				{
					afficher_piece_rond(ptCentreCase,COULEUR_JOUEUR1);
				}
				
				if(j>2)
				{
					afficher_piece_rond(ptCentreCase,COULEUR_JOUEUR2);
				}
			}
			
			else
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_JOUEURS);
			}
			
			ptCentreCase.x+=LARG_CASE;

			ptbgCase.x+=LARG_CASE;
			pthdCase.x+=LARG_CASE;
		}
		
		ptCentreCase.x=440+LARG_CASE/2;
		ptCentreCase.y+=LARG_CASE;
		
		ptbgCase.x=440;ptbgCase.y+=LARG_CASE;
		pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y+=LARG_CASE;
	}
	
	affiche_all();
}

void afficher_choisir_interface()
{
	POINT ptTexteChoisirInterface;
	
	ptTexteChoisirInterface.x=130;
	ptTexteChoisirInterface.y=30;
	
	aff_pol("Cliquer dans le plateau dans lequel vous voulez jouer",20,ptTexteChoisirInterface,blanc);
}

POINT recuperer_clic_choix_ig()
{
	POINT clicChoixIg={0,0};
	
	do{
		clicChoixIg=wait_clic();
	}while(
				( (clicChoixIg.x>370) &&   (clicChoixIg.x<420) )
			||	( (clicChoixIg.y<120) ||   (clicChoixIg.y>420) )
			||  ( (clicChoixIg.x<70)  && ( (clicChoixIg.y>120) || (clicChoixIg.y<420) ) )
			||  ( (clicChoixIg.x>740) && ( (clicChoixIg.y>120) || (clicChoixIg.y<420) ) )
		  );

	return clicChoixIg;
}

void choisir_pion_valide_ig1(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi)
{
	COULP couleurPionChoisi;
	POINT clicPionChoisi;
	
	do{
		
		do{
			clicPionChoisi=recuperer_clic_pos_plateau();
			*centreCasePionChoisi=convertir_clic_en_centreCase(clicPionChoisi);
			*numCasePionChoisi=convertir_centreCase_en_numCase(*centreCasePionChoisi);
			couleurPionChoisi=plateau[numCasePionChoisi->colonne][numCasePionChoisi->ligne].coulP;
		}while(couleurPionChoisi!=couleurPionValide);
		
	}while( est_bloque(*numCasePionChoisi,couleurPionChoisi) );
}

void choisir_pion_valide_ig2(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi)
{
	COULP couleurPionChoisi;
	POINT clicPionChoisi;
	
	do{
		
		do{
			clicPionChoisi=recuperer_clic_pos_plateau();
			*centreCasePionChoisi=convertir_clic_en_centreCase(clicPionChoisi);
			*numCasePionChoisi=convertir_centreCase_en_numCase(*centreCasePionChoisi);
			*numCasePionChoisi=convertir_numCase_ig2_vers_ig1(*numCasePionChoisi);
			couleurPionChoisi=plateau[numCasePionChoisi->colonne][numCasePionChoisi->ligne].coulP;
		}while(couleurPionChoisi!=couleurPionValide);
		
	}while( est_bloque(*numCasePionChoisi,couleurPionChoisi) );
}

NUMCASE convertir_numCase_ig1_vers_ig2(NUMCASE numCaseIg1)
{
	NUMCASE numCaseIg2;

	numCaseIg2.ligne=9-numCaseIg1.colonne; // -9 ici car ligne et colonne sont inversées
	numCaseIg2.colonne=numCaseIg1.ligne;

	return numCaseIg2;
}

NUMCASE convertir_numCase_ig2_vers_ig1(NUMCASE numCaseIg2)
{
	NUMCASE numCaseIg1;

	numCaseIg1.ligne=numCaseIg2.colonne;
	numCaseIg1.colonne=9-numCaseIg2.ligne; // -9 ici car ligne et colonne sont inversées

	return numCaseIg1;
}

void trouver_cases_libres_ig2(POINT centrePionChoisi,NUMCASE numCasePionChoisi,COULP couleurJoueur,int *positionCasesLibres,int *positionCasesLibresAttaque)
{
	*positionCasesLibres=donner_position_cases_libres_deplacement(numCasePionChoisi);
	*positionCasesLibresAttaque=donner_position_cases_libres_attaque(numCasePionChoisi,couleurJoueur);
	
	afficher_cases_libres_ig2(centrePionChoisi,*positionCasesLibres,*positionCasesLibresAttaque);
}

