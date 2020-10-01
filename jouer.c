/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include "jouer.h"


PIECE plateau[10][10];


/*
 * ||        ||
 * \/ MODÈLE \/
 */

/* Manipulation du tableau logique */

void changer_etat_case_tableau_logique(NUMCASE numCase, TYPEP type, COULP coul)
{
	plateau[numCase.colonne][numCase.ligne].typeP = type;
	plateau[numCase.colonne][numCase.ligne].coulP = coul;
}

void effectuer_attaque_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, COULP couleurJoueur, int *nbrePionJoueur)
{
	NUMCASE milieu;
	milieu.ligne = (depart.ligne + arrivee.ligne) / 2;
	milieu.colonne = (depart.colonne + arrivee.colonne) / 2;
	
	changer_etat_case_tableau_logique(arrivee, plateau[depart.colonne][depart.ligne].typeP, couleurJoueur);
	changer_etat_case_tableau_logique(milieu, vide, aucune);
	changer_etat_case_tableau_logique(depart, vide, aucune);
	transformer_pion_en_dame(arrivee, couleurJoueur);
	*nbrePionJoueur = *nbrePionJoueur - 1;
}

void effectuer_deplacement_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, COULP couleurJoueur)
{
	changer_etat_case_tableau_logique(arrivee, plateau[depart.colonne][depart.ligne].typeP, couleurJoueur);
	changer_etat_case_tableau_logique(depart, vide, aucune);
	transformer_pion_en_dame(arrivee, couleurJoueur);
}

void initialiser_plateau()
{
	int i, j;
	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			if( ( !(i % 2) && !(j % 2) && (j < 3) )
			||
			( (i % 2) && (j % 2) && (j < 4) ))
			{
				plateau[i][j].typeP = pion;
				plateau[i][j].coulP = coul1;
			}
			else if( ( !(i % 2) && !(j % 2) && (j > 5) )
			||
			( (i % 2) && (j % 2) && (j > 6) ))
			{
				plateau[i][j].typeP = pion;
				plateau[i][j].coulP = coul2;
			}
			else
			{
				plateau[i][j].typeP = vide;
				plateau[i][j].coulP = aucune;
			}
		}
	}
}

/* Vérification des possibilités d'attaques et de déplacements */

int donner_position_cases_libres_attaque(NUMCASE depart, COULP couleurJoueur)
{
	int cases_libres = 0;
	NUMCASE arrivee;
	if(depart.ligne < 8)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		||
		( plateau[depart.colonne][depart.ligne].coulP == coul1 ))
		{
			arrivee.ligne = depart.ligne + 2;
			arrivee.colonne = depart.colonne - 2;
			if(depart.colonne > 1 && est_coup_valide_attaque(depart, arrivee, couleurJoueur))
				cases_libres += 1;
			arrivee.colonne = depart.colonne + 2;
			if(depart.colonne < 8 && est_coup_valide_attaque(depart, arrivee, couleurJoueur))
				cases_libres += 2;
		}
	}
	if(depart.ligne > 1)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		||
		( plateau[depart.colonne][depart.ligne].coulP == coul2 ))
		{
			arrivee.ligne = depart.ligne - 2;
			arrivee.colonne = depart.colonne - 2;
			if(depart.colonne > 1 && est_coup_valide_attaque(depart, arrivee, couleurJoueur))
				cases_libres += 4;
			arrivee.colonne = depart.colonne + 2;
			if(depart.colonne < 8 && est_coup_valide_attaque(depart, arrivee, couleurJoueur))
				cases_libres += 8;
		}
	}
	return cases_libres;
}

int donner_position_cases_libres_deplacement(NUMCASE depart)
{
	int cases_libres = 0;
	NUMCASE arrivee;

	if(depart.ligne < 9)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		||
		( plateau[depart.colonne][depart.ligne].coulP == coul1 ))
		{
			arrivee.ligne = depart.ligne + 1;
			arrivee.colonne = depart.colonne - 1;
			if(depart.colonne > 0 && est_coup_valide_deplacement(depart, arrivee))
				cases_libres += 1;
			arrivee.colonne = depart.colonne + 1;
			if(depart.colonne < 9 && est_coup_valide_deplacement(depart, arrivee))
				cases_libres += 2;
		}
	}
	if(depart.ligne > 0)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		||
		( plateau[depart.colonne][depart.ligne].coulP == coul2 ))
		{
			arrivee.ligne = depart.ligne - 1;
			arrivee.colonne = depart.colonne - 1;
			if(depart.colonne > 0 && est_coup_valide_deplacement(depart, arrivee))
				cases_libres += 4;
			arrivee.colonne = depart.colonne + 1;
			if(depart.colonne < 9 && est_coup_valide_deplacement(depart, arrivee))
				cases_libres += 8;
		}
	}
	return cases_libres;
}

BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination, COULP couleurJoueur)
{
	PIECE piece = plateau[origine.colonne][origine.ligne];
	int deltaCol = destination.colonne - origine.colonne;
	int deltaLig = destination.ligne - origine.ligne;
	COULP couleurEnnemi = (couleurJoueur == coul1) ? coul2 : coul1;
	
	if(plateau[destination.colonne][destination.ligne].coulP == aucune)
	{
		if( ( deltaLig == 2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul1) && plateau[destination.colonne - 1][destination.ligne - 1].coulP == couleurEnnemi )
		||
		( deltaLig == 2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul1) && plateau[destination.colonne + 1][destination.ligne - 1].coulP == couleurEnnemi )
		||
		( deltaLig == -2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul2) && plateau[destination.colonne - 1][destination.ligne + 1].coulP == couleurEnnemi )
		||
		( deltaLig == -2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul2) && plateau[destination.colonne + 1][destination.ligne + 1].coulP == couleurEnnemi ))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL est_coup_valide_deplacement(NUMCASE origine, NUMCASE destination)
{
	PIECE piece = plateau[origine.colonne][origine.ligne];
	int deltaCol = destination.colonne - origine.colonne;
	int deltaLig = destination.ligne - origine.ligne;

	if(plateau[destination.colonne][destination.ligne].coulP == aucune)
	{
		if( ( deltaLig == 1 && deltaCol == 1 && (piece.typeP == dame || piece.coulP == coul1) )
		||
		( deltaLig == 1 && deltaCol == -1 && (piece.typeP == dame || piece.coulP == coul1) )
		||
		( deltaLig == -1 && deltaCol == 1 && (piece.typeP == dame || piece.coulP == coul2) )
		||
		( deltaLig == -1 && deltaCol == -1 && (piece.typeP == dame || piece.coulP == coul2) ))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

/* Vérification de possibilité de jeu et fin de partie */

BOOL est_bloque(NUMCASE depart, COULP couleurJoueur)
{
	if( !donner_position_cases_libres_deplacement(depart) && !donner_position_cases_libres_attaque(depart, couleurJoueur))
			return TRUE;
	return FALSE;
}

BOOL est_joueur_bloque(COULP couleurJoueur, int nbrePionJoueur)
{
	int nbre_cases_bloquees, i, j;
	NUMCASE case_testee;

	nbre_cases_bloquees = 0;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			case_testee.ligne = j;
			case_testee.colonne = i;
			if(plateau[case_testee.colonne][case_testee.ligne].coulP == couleurJoueur && est_bloque(case_testee, couleurJoueur))
			{
				nbre_cases_bloquees++;
				if(nbre_cases_bloquees == nbrePionJoueur)
					return TRUE;
			}
		}
	}
	return FALSE;
}

int tester_fin_jeu(COULP couleurJoueur, int nbrePionJoueur)
{
	if(nbrePionJoueur == 0)
	{
		return 1;
	}
	if(est_joueur_bloque(couleurJoueur, nbrePionJoueur))
	{
		return 2;
	}
	return 0;
}

void transformer_pion_en_dame(NUMCASE pion, COULP couleurJoueur)
{
	if(plateau[pion.colonne][pion.ligne].typeP != dame)
	{
		if( ( pion.ligne == 9 )
		||
		( pion.ligne == 0 ))
		{
			plateau[pion.colonne][pion.ligne].typeP = dame;
		}
	}
}

/*
 * /\ MODÈLE /\
 * ||        ||
 */

/*
 * ||     ||
 * \/ VUE \/
 */

COULEUR convertir_joueur_couleur(COULP couleurJoueur)
{
	COULEUR couleur=COULEUR_JOUEUR1;
	
	if(couleurJoueur == coul1)
	{
		couleur=COULEUR_JOUEUR1;
	}
	
	else if(couleurJoueur == coul2)
	{
		couleur=COULEUR_JOUEUR2;
	}
	
	return couleur;
}

/*		-- Afficher pieces / plateau --		*/

void afficher_piece_triangle_haut(POINT ptLosangeCentre,COULEUR couleur)
{
	POINT ptLosangeHaut,ptLosangeDroit,ptLosangeGauche;
	
	ptLosangeHaut.x=ptLosangeCentre.x;
	ptLosangeHaut.y=ptLosangeCentre.y+0.5*LONGUEUR_PIECE;
	
	ptLosangeDroit.x=ptLosangeCentre.x-0.5*LONGUEUR_PIECE;
	ptLosangeDroit.y=ptLosangeCentre.y;
	
	ptLosangeGauche.x=ptLosangeCentre.x+0.5*LONGUEUR_PIECE;
	ptLosangeGauche.y=ptLosangeCentre.y;
	
	
	draw_fill_triangle(ptLosangeHaut,ptLosangeDroit,ptLosangeGauche,couleur);
}

void afficher_piece_triangle_bas(POINT ptLosangeCentre,COULEUR couleur)
{
	POINT ptLosangeBas,ptLosangeDroit,ptLosangeGauche;
	
	ptLosangeBas.x=ptLosangeCentre.x;
	ptLosangeBas.y=ptLosangeCentre.y-0.5*LONGUEUR_PIECE;
	
	ptLosangeDroit.x=ptLosangeCentre.x-0.5*LONGUEUR_PIECE;
	ptLosangeDroit.y=ptLosangeCentre.y;
	
	ptLosangeGauche.x=ptLosangeCentre.x+0.5*LONGUEUR_PIECE;
	ptLosangeGauche.y=ptLosangeCentre.y;
	
	draw_fill_triangle(ptLosangeBas,ptLosangeDroit,ptLosangeGauche,couleur);
}

void afficher_piece_dame_triangle_haut(POINT ptLosangeCentre)
{
	POINT ptLosangeDameHaut,ptLosangeDameDroit,ptLosangeDameGauche;
	
	ptLosangeDameHaut.x=ptLosangeCentre.x;
	ptLosangeDameHaut.y=ptLosangeCentre.y+0.3*LONGUEUR_PIECE;
	
	ptLosangeDameDroit.x=ptLosangeCentre.x-0.6*(LONGUEUR_PIECE/2);
	ptLosangeDameDroit.y=ptLosangeCentre.y;
	
	ptLosangeDameGauche.x=ptLosangeCentre.x+0.6*(LONGUEUR_PIECE/2);
	ptLosangeDameGauche.y=ptLosangeCentre.y;
	
	draw_fill_triangle(ptLosangeDameHaut,ptLosangeDameDroit,ptLosangeDameGauche,COULEUR_DAME);
}

void afficher_piece_dame_triangle_bas(POINT ptLosangeCentre)
{
	POINT ptLosangeDameBas,ptLosangeDameDroit,ptLosangeDameGauche;
	
	ptLosangeDameBas.x=ptLosangeCentre.x;
	ptLosangeDameBas.y=ptLosangeCentre.y-0.3*LONGUEUR_PIECE;
	
	ptLosangeDameDroit.x=ptLosangeCentre.x-0.6*(LONGUEUR_PIECE/2);
	ptLosangeDameDroit.y=ptLosangeCentre.y;
	
	ptLosangeDameGauche.x=ptLosangeCentre.x+0.6*(LONGUEUR_PIECE/2);
	ptLosangeDameGauche.y=ptLosangeCentre.y;
	
	draw_fill_triangle(ptLosangeDameBas,ptLosangeDameDroit,ptLosangeDameGauche,COULEUR_DAME);
}

void afficher_piece_ig1(POINT ptLosangeCentre,int ligne,int colonne)
{
	COULEUR couleur;
	couleur = convertir_joueur_couleur(plateau[colonne][ligne].coulP);
	
	if( (plateau[colonne][ligne].typeP == pion) || (plateau[colonne][ligne].typeP == dame) )
	{
		afficher_piece_triangle_haut(ptLosangeCentre,couleur);
		afficher_piece_triangle_bas(ptLosangeCentre,couleur);
	}
		
	if(plateau[colonne][ligne].typeP == dame)
	{
		afficher_piece_dame_triangle_haut(ptLosangeCentre);
		afficher_piece_dame_triangle_bas(ptLosangeCentre);
	}
}

void afficher_case_ig1(POINT ptCentreCase,COULEUR couleur)
{
	draw_fill_circle(ptCentreCase,LARG_CASE/2,couleur);
}

void afficher_plateau_ig1()
{
	int i=0,j=0;
	POINT ptCentreCase;
	
	ptCentreCase.x=LARG_CASE/2;ptCentreCase.y=LARG_CASE/2;
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				afficher_case_ig1(ptCentreCase,COULEUR_CASE_JOUEURS);
				
				if(plateau[j][i].coulP != aucune)
				{
					afficher_piece_ig1(ptCentreCase,i,j);
				}
			}
			
			else
			{
				afficher_case_ig1(ptCentreCase,COULEUR_CASE_VIDE);
			}
		
			ptCentreCase.x+=LARG_CASE;
		}
		
		ptCentreCase.x=LARG_CASE/2;
		ptCentreCase.y+=LARG_CASE;
	}
	
}

void afficher_piece_rond(POINT ptRondCentre,COULEUR couleur)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/2,couleur);
}

void afficher_piece_rond_dame(POINT ptRondCentre)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/3,COULEUR_DAME);
}

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

void afficher_case_ig2(POINT ptbgCase,POINT pthdCase,COULEUR couleur)
{
	draw_fill_rectangle(ptbgCase,pthdCase,couleur);
}

void afficher_plateau_ig2()
{
	int i=0,j=0;
	POINT ptbgCase,pthdCase,ptCentreCase;
	
	ptCentreCase.x=LARG_CASE/2;ptCentreCase.y=LARG_CASE/2;

	ptbgCase.x=0;ptbgCase.y=0;
	pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y=ptbgCase.y+LARG_CASE;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_JOUEURS);
				
				if(plateau[j][i].coulP != aucune)
				{
					afficher_piece_ig2(ptCentreCase,i,j); //MAUVAIS CAR SE BASE SUR LE PLATEAU DE IG1
				}
			}
			
			else
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_VIDE);
			}
		
			ptCentreCase.x+=LARG_CASE;
			ptbgCase.x+=LARG_CASE;
			pthdCase.x+=LARG_CASE;
		}
		
		ptCentreCase.x=LARG_CASE/2;
		ptCentreCase.y+=LARG_CASE;
		ptbgCase.x=0;ptbgCase.y+=LARG_CASE;
		pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y+=LARG_CASE;
	}
	affiche_all();
}

void afficher_ecran_jeu_selon_ig(int igChoisi)
{
	fill_screen(noir);
	
	if (igChoisi==1)
	{afficher_plateau_ig1();}
	
	else if (igChoisi==2)
	{afficher_plateau_ig2();}
	
	afficher_interface(igChoisi);
	affiche_all();
}

/*		-- Afficher Interface --		*/

void afficher_interface(int igChoisi)
{
	POINT ptTexteTour,ptTourJoueur/*,ptNbrP1,ptNbrP2,ptAnnuler*/;
	
	ptTexteTour.x=HAUT_FENETRE+20;ptTexteTour.y=HAUT_FENETRE-20;

	ptTourJoueur.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptTourJoueur.y=0.85*HAUT_FENETRE;
	

	aff_pol("A qui de jouer ?",20,ptTexteTour,blanc);



	//~ ptNbrP1.x=HAUT_FENETRE+5;ptNbrP1.y=0.66*HAUT_FENETRE;
	//~ ptNbrP2.x=HAUT_FENETRE+5;ptNbrP2.y=0.33*HAUT_FENETRE;	
	//~ aff_pol("Nombre de pions 1",20,ptNbrP1,blanc);
	//~ aff_pol("Nombre de pions 2",20,ptNbrP2,blanc);
	//~ ptAnnuler.x=HAUT_FENETRE+30;ptAnnuler.y=50;
	//~ aff_pol("Annuler coup",20,ptAnnuler,blanc); //N'afficher que si plusieurs prises

	
	if(igChoisi==1)
	{
		afficher_piece_triangle_haut(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
		afficher_piece_triangle_bas(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
	}
	
	else if(igChoisi==2)
	{
		afficher_piece_rond(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
	}
	
	affiche_all();
}

void effacer_tour()
{
	POINT ptbgIndiqTour,pthdIndiqTour;
	
	ptbgIndiqTour.x=HAUT_FENETRE+1;
	ptbgIndiqTour.y=0.8*HAUT_FENETRE;
	pthdIndiqTour.x=LARG_FENETRE;
	pthdIndiqTour.y=0.9*HAUT_FENETRE;
	
	draw_fill_rectangle(ptbgIndiqTour,pthdIndiqTour,noir);
}

/*		-- Jeu principal --		*/

void changer_tour_joueur_ig1(COULP *couleurJoueur)
{	
	if(*couleurJoueur == coul1)
	{*couleurJoueur=coul2;}
	
	else if(*couleurJoueur == coul2)
	{*couleurJoueur=coul1;}
	
	effacer_tour();
	changer_tour_interface_ig1(*couleurJoueur);
	
	affiche_all();
}

void changer_tour_interface_ig1(COULP couleurJoueur)
{
	COULEUR couleur;
	POINT ptTourJoueur;
	
	ptTourJoueur.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptTourJoueur.y=0.85*HAUT_FENETRE;

	couleur=convertir_joueur_couleur(couleurJoueur);
	afficher_piece_triangle_haut(ptTourJoueur,couleur);
	afficher_piece_triangle_bas(ptTourJoueur,couleur);
}

void changer_tour_joueur_ig2(COULP *couleurJoueur)
{
	if(*couleurJoueur == coul1)
	{*couleurJoueur=coul2;}
	
	else if(*couleurJoueur == coul2)
	{*couleurJoueur=coul1;}
	
	effacer_tour();
	changer_tour_interface_ig2(*couleurJoueur);
	
	affiche_all();
}

void changer_tour_interface_ig2(COULP couleurJoueur)
{
	COULEUR couleur;
	POINT ptTourJoueur;
	
	ptTourJoueur.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptTourJoueur.y=0.85*HAUT_FENETRE;

	couleur=convertir_joueur_couleur(couleurJoueur);
	afficher_piece_rond(ptTourJoueur,couleur);
}

/*		-- Afficher cases libres pion --		*/

POINT recuperer_clic_pos_plateau()
{
	POINT clicPionChoisi;
	
	do{
		clicPionChoisi=wait_clic();
	}while( (clicPionChoisi.x<0) || (clicPionChoisi.x>HAUT_FENETRE) || (clicPionChoisi.y<0) || (clicPionChoisi.y>HAUT_FENETRE) ); //LARG_FENETRE = HAUT_FENETRE
	
	return clicPionChoisi;
}

POINT convertir_clic_en_centreCase(POINT clicPionChoisi)
{
	POINT centreCase;
	
	centreCase.x=0;centreCase.y=0;

	centreCase.x=(clicPionChoisi.x) / (LARG_CASE) * (LARG_CASE) + (LARG_CASE/2); //On divise puis multiplie pour avoir un multiple de LARG_CASE
	centreCase.y=(clicPionChoisi.y) / (LARG_CASE) * (LARG_CASE) + (LARG_CASE/2); //On divise puis multiplie pour avoir un multiple de LARG_CASE
	
	return centreCase;
}

void afficher_cases_libres_ig1(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque)
{
	POINT centreCaseLibre;
	
	/* Cases Normales */
	if(positionCasesLibres%2>0) //rond haut gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibres%4>1) //rond haut droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibres%8>3) //rond bas gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);	
	}
	
	if(positionCasesLibres%16>7) //rond bas droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);	
	}
	
	
	/* Cases Attaque */
	if(positionCasesLibresAttaque%2>0) //rond haut gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibresAttaque%4>1) //rond haut droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
	
	if(positionCasesLibresAttaque%8>3) //rond bas gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);	
	}
	
	if(positionCasesLibresAttaque%16>7) //rond bas droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_LIBRE);	
	}
	
	affiche_all();
}

void effacer_cases_libres_choisies_ig1(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque)
{
	POINT centreCaseLibre;
	
	/* Cases Normales */
	if(positionCasesLibres%2>0) //rond haut gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibres%4>1) //rond haut droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibres%8>3) //rond bas gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);	
	}
	
	if(positionCasesLibres%16>7) //rond bas droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);	
	}
	
	/* Cases Attaque */
	if(positionCasesLibresAttaque%2>0) //rond haut gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibresAttaque%4>1) //rond haut droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y+LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);
	}
	
	if(positionCasesLibresAttaque%8>3) //rond bas gauche
	{
		centreCaseLibre.x=centrePionChoisi.x-LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);	
	}
	
	if(positionCasesLibresAttaque%16>7) //rond bas droite
	{
		centreCaseLibre.x=centrePionChoisi.x+LARG_CASE*2;
		centreCaseLibre.y=centrePionChoisi.y-LARG_CASE*2;
		draw_fill_circle(centreCaseLibre,LARG_CASE/2,COULEUR_CASE_JOUEURS);	
	}

	affiche_all();
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

/*		-- Choisir destination --		*/

void afficher_texte_choix_destination()
{
	POINT ptTexteDestination;
	
	ptTexteDestination.x=HAUT_FENETRE+15; ptTexteDestination.y=HAUT_FENETRE-200;
	
	aff_pol("Choix destination",20,ptTexteDestination,blanc);
	affiche_all();
}

void effacer_texte_choix_destination()
{
	POINT ptbdTexteDestination,pthgTexteDestination;
	
	ptbdTexteDestination.x=HAUT_FENETRE+1; ptbdTexteDestination.y=HAUT_FENETRE-220;
	pthgTexteDestination.x=LARG_FENETRE; ptbdTexteDestination.y=HAUT_FENETRE-200;
		
	draw_fill_rectangle(ptbdTexteDestination,pthgTexteDestination,noir);
	affiche_all();
}

void choisir_destination_ig1(POINT centreCasePionChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination)
{
	POINT clicCaseDestination;
	
	afficher_texte_choix_destination();
	clicCaseDestination=recuperer_clic_pos_plateau();
	effacer_texte_choix_destination();

	*centreCaseDestination=convertir_clic_en_centreCase(clicCaseDestination);
	*numCaseDestination=convertir_centreCase_en_numCase(*centreCaseDestination);
	
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

/*		-- Bouger Pion --		*/

void effacer_piece_case_orig_ig1(POINT centreCasePionChoisi)
{
	draw_fill_circle(centreCasePionChoisi,LARG_CASE/2,COULEUR_CASE_JOUEURS);
}

void enlever_pion_qui_subit_attaque_ig1(POINT centrePionChoisi, POINT centreCaseDestination)
{
	POINT centreCaseLibre;
	
	centreCaseLibre.x = (centrePionChoisi.x + centreCaseDestination.x) / 2;
	centreCaseLibre.y = (centrePionChoisi.y + centreCaseDestination.y) / 2;
	draw_fill_circle(centreCaseLibre, LARG_CASE/2, COULEUR_CASE_JOUEURS);
	
	affiche_all();
}

void effacer_piece_case_orig_ig2(POINT centreCasePionChoisi)
{
	draw_fill_circle(centreCasePionChoisi,LONGUEUR_PIECE/2,COULEUR_CASE_JOUEURS);
}

/*		-- Choix attaque multiple --		*/

void afficher_choix_multi_attaque(POINT ptMultiAtk1, POINT ptMultiAtk2, POINT ptOui1, POINT ptOui2, POINT ptNon1, POINT ptNon2)
{
	aff_pol("Attaque possible", 20, ptMultiAtk1, blanc);
	aff_pol("Continuer ?", 20, ptMultiAtk2, blanc);
	aff_pol("Oui", 20, ptOui1, vert);
	draw_rectangle(ptOui1, ptOui2, vert);
	aff_pol("Non", 20, ptNon1, rouge);
	draw_rectangle(ptNon1, ptNon2, rouge);
	affiche_all();
	return;
}

void effacer_choix_multi_attaque(POINT P1)
{
	POINT P2;
	
	P2.x = LARG_FENETRE; P2.y = 0;
	draw_fill_rectangle(P1, P2, noir);
	affiche_all();
}

BOOL recuper_choix_multi_attaque(POINT ptOui1, POINT ptOui2, POINT ptNon1, POINT ptNon2)
{
	POINT clicMultiAtk;
	
	do
	{
		clicMultiAtk = wait_clic();
		if((clicMultiAtk.x > ptOui1.x) && (clicMultiAtk.x < ptOui2.x) && (clicMultiAtk.y < ptOui1.y) && (clicMultiAtk.y > ptOui2.y))
			return 1;
		else if((clicMultiAtk.x > ptNon1.x) && (clicMultiAtk.x < ptNon2.x) && (clicMultiAtk.y < ptNon1.y) && (clicMultiAtk.y > ptNon2.y))
			return 0;
	}while(1);
}

BOOL est_acceptee_multi_attaque()
{
	BOOL choix;
	POINT ptMultiAtk1, ptMultiAtk2, ptOui1, ptOui2, ptNon1, ptNon2;
	
	ptMultiAtk1.x = HAUT_FENETRE + 10; ptMultiAtk1.y = HAUT_FENETRE / 4 + 30;
	ptMultiAtk2.x = HAUT_FENETRE + 10; ptMultiAtk2.y = HAUT_FENETRE / 4;
	ptOui1.x = HAUT_FENETRE + 20; ptOui1.y = HAUT_FENETRE / 4 - 30;
	ptOui2.x = HAUT_FENETRE + 60; ptOui2.y = HAUT_FENETRE / 4 - 60;
	ptNon1.x = HAUT_FENETRE + 10 + 100; ptNon1.y = HAUT_FENETRE / 4 - 30;
	ptNon2.x = HAUT_FENETRE + 10 + 140; ptNon2.y = HAUT_FENETRE / 4 - 60;
	
	afficher_choix_multi_attaque(ptMultiAtk1, ptMultiAtk2, ptOui1, ptOui2, ptNon1, ptNon2);
	choix = recuper_choix_multi_attaque(ptOui1, ptOui2, ptNon1, ptNon2);
	effacer_choix_multi_attaque(ptMultiAtk1);
	return choix;
}

/*		-- Afficher Ecran Titre --		*/

void afficher_titre()
{
	POINT ptTitre;
	
	ptTitre.x=LARG_FENETRE/6;ptTitre.y=HAUT_FENETRE-10; // /6 pour centrer le texte
	
	aff_pol("Projet Dames IATIC3 - CORBEIL Alex / VIDAL Antoine",20,ptTitre,blanc);
}

void afficher_choisir_interface()
{
	POINT ptTexteChoisirInterface;
	
	ptTexteChoisirInterface.x=130;
	ptTexteChoisirInterface.y=30;
	
	aff_pol("Cliquer dans le plateau dans lequel vous voulez jouer",20,ptTexteChoisirInterface,blanc);
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

void afficher_ecran_titre_ig1()
{
	POINT ptTitreIg1;
	
	ptTitreIg1.x=LARG_FENETRE/5;ptTitreIg1.y=HAUT_FENETRE-100;
	
	aff_pol("Interface 1",20,ptTitreIg1,blanc);
	afficher_exemple_ecran_titre_ig1(ptTitreIg1);
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

void afficher_ecran_titre_ig2()
{
	POINT ptTitreIg2;
	
	ptTitreIg2.x=LARG_FENETRE/1.5;ptTitreIg2.y=HAUT_FENETRE-100;
			
	aff_pol("Interface 2",20,ptTitreIg2,blanc);
	afficher_exemple_ecran_titre_ig2(ptTitreIg2);
	affiche_all();
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

void afficher_ecran_titre(int *ig)
{
	POINT clicChoixIg;
	
	fill_screen(noir);
	afficher_titre();
	afficher_ecran_titre_ig1();
	afficher_ecran_titre_ig2();
	
	affiche_all();
	clicChoixIg=recuperer_clic_choix_ig();
	*ig=choisir_ig(clicChoixIg);
	
}

/*		-- Afficher Redemander Partie --		*/

void afficher_texte_redemander_partie(POINT ptOui,POINT ptNon)
{
	POINT ptRejouer;
	
	ptRejouer.x=LARG_FENETRE/3;ptRejouer.y=HAUT_FENETRE/2;

	fill_screen(noir);
	
	/*afficher_gagnant();*/
	
	aff_pol("Rejouer ?",20,ptRejouer,blanc);
	aff_pol("Oui",20,ptOui,blanc);
	aff_pol("Non",20,ptNon,blanc);
	affiche_all();
}

POINT recuperer_clic_redemander_partie(POINT ptOui,POINT ptNon)
{
	POINT clicRedemanderPartie;
	
	do{
		clicRedemanderPartie=wait_clic();
	}while( ((clicRedemanderPartie.x<ptOui.x) && (clicRedemanderPartie.x>ptOui.x+50) && (clicRedemanderPartie.y<ptOui.y) && (clicRedemanderPartie.y>ptOui.y+50)) ||
			((clicRedemanderPartie.x<ptNon.x) && (clicRedemanderPartie.x>ptNon.x+50) && (clicRedemanderPartie.y<ptNon.y) && (clicRedemanderPartie.y>ptNon.y+50)) );
	
	return clicRedemanderPartie;
}

BOOL redemander_partie()
{
	POINT ptOui,ptNon,clicRedemanderPartie;
	BOOL rejouer=false;

	ptOui.x=(LARG_FENETRE/3)+150;ptOui.y=HAUT_FENETRE/2;
	ptNon.x=(LARG_FENETRE/3)+250;ptNon.y=ptOui.y;
	
	fill_screen(noir);
	afficher_texte_redemander_partie(ptOui,ptNon);
	clicRedemanderPartie=recuperer_clic_redemander_partie(ptOui,ptNon);
	rejouer=savoir_si_rejouer_partie(ptOui,ptNon,clicRedemanderPartie);
	
	return rejouer;
}

/*
 * /\ VUE /\
 * ||     ||
 */

/*
 * ||            ||
 * \/ CONTRÔLEUR \/
 */

void bouger_pion_choisi_ig1(POINT centreCasePionChoisi, POINT centreCaseDestination, NUMCASE numCaseOrig, NUMCASE numCaseDestination, COULP couleurJoueur,int positionCasesLibres, int positionCasesLibresAttaque, int *nbrePionJoueur)
{
	effacer_cases_libres_choisies_ig1(centreCasePionChoisi, positionCasesLibres, positionCasesLibresAttaque);
	effacer_piece_case_orig_ig1(centreCasePionChoisi);
	if( est_coup_valide_deplacement(numCaseOrig, numCaseDestination) )
	{
		effectuer_deplacement_dans_tableau_logique(numCaseOrig,numCaseDestination,couleurJoueur);
	}
	else if( est_coup_valide_attaque(numCaseOrig,numCaseDestination,couleurJoueur) )
	{
		enlever_pion_qui_subit_attaque_ig1(centreCasePionChoisi, centreCaseDestination);
		effectuer_attaque_dans_tableau_logique(numCaseOrig, numCaseDestination, couleurJoueur, nbrePionJoueur);
	}
	afficher_piece_ig1(centreCaseDestination,numCaseDestination.ligne,numCaseDestination.colonne);
	affiche_all();
}

int choisir_ig(POINT clicChoixIg)
{
	int ig=0;
	
	if(clicChoixIg.x<LARG_FENETRE/2)
	{ig=1;}
	
	else if(clicChoixIg.x>LARG_FENETRE/2)
	{ig=2;}
	
	return ig;
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

NUMCASE convertir_centreCase_en_numCase(POINT centreCase)
{
	NUMCASE numcase;
	
	numcase.ligne=(centreCase.y)/(LARG_CASE);
	numcase.colonne=(centreCase.x)/(LARG_CASE);
	
	return numcase;
}

POINT convertir_numCase_en_centreCase(NUMCASE numcase)
{
	POINT centreCase;
	
	centreCase.x=(numcase.colonne*LARG_CASE)+(LARG_CASE/2);
	centreCase.y=(numcase.ligne*LARG_CASE)+(LARG_CASE/2);
	
	return centreCase;
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

BOOL savoir_si_rejouer_partie(POINT ptOui,POINT ptNon,POINT clicRedemanderPartie)
{
	BOOL rejouer=true;
	
	if( (clicRedemanderPartie.x>=ptOui.x) && (clicRedemanderPartie.x<=ptOui.x+40) && (clicRedemanderPartie.y>=ptOui.y-20) && (clicRedemanderPartie.y<=ptOui.y) ) //40=longueur_texte 20=hauteur_texte
	{
		rejouer=true;
	}
	
	else if( (clicRedemanderPartie.x>=ptNon.x) && (clicRedemanderPartie.x<=ptNon.x+40) && (clicRedemanderPartie.y>=ptNon.y-20) && (clicRedemanderPartie.y<=ptNon.y) ) //40=longueur_texte 20=hauteur_texte
	{
		rejouer=false;
	}
	
	return rejouer;
}

void trouver_cases_libres_ig1(POINT centrePionChoisi, NUMCASE numCasePionChoisi, COULP couleurJoueur, int *positionCasesLibres, int *positionCasesLibresAttaque, BOOL est_multiAttaque)
{
	if( !est_multiAttaque)
		*positionCasesLibres = donner_position_cases_libres_deplacement(numCasePionChoisi);
	else
		*positionCasesLibres = 0;
	*positionCasesLibresAttaque = donner_position_cases_libres_attaque(numCasePionChoisi,couleurJoueur);
	
	afficher_cases_libres_ig1(centrePionChoisi, *positionCasesLibres, *positionCasesLibresAttaque);
}

void trouver_cases_libres_ig2(POINT centrePionChoisi,NUMCASE numCasePionChoisi,COULP couleurJoueur,int *positionCasesLibres,int *positionCasesLibresAttaque)
{
	*positionCasesLibres=donner_position_cases_libres_deplacement(numCasePionChoisi);
	*positionCasesLibresAttaque=donner_position_cases_libres_attaque(numCasePionChoisi,couleurJoueur);
	
	afficher_cases_libres_ig2(centrePionChoisi,*positionCasesLibres,*positionCasesLibresAttaque);
}

void tour_piece_ig1(COULP couleurJoueur, int *nbrePionJoueur)
{
	int positionCasesLibres = 0, positionCasesLibresAttaque = 0;
	POINT centreCasePionChoisi, centreCaseDestination;
	NUMCASE numCasePionChoisi, numCaseDestination;
	BOOL est_multiAttaque = FALSE;
	do
	{
		effacer_cases_libres_choisies_ig1(centreCasePionChoisi,positionCasesLibres,positionCasesLibresAttaque);
		choisir_pion_valide_ig1(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
		trouver_cases_libres_ig1(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&positionCasesLibres,&positionCasesLibresAttaque, est_multiAttaque);
		do
		{
			choisir_destination_ig1(centreCasePionChoisi,&centreCaseDestination,&numCaseDestination);
			if( !est_multiAttaque && est_coup_valide_deplacement(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig1(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, positionCasesLibres, positionCasesLibresAttaque, nbrePionJoueur);
				return;
			}
			if(est_coup_valide_attaque(numCasePionChoisi, numCaseDestination, couleurJoueur))
			{
				bouger_pion_choisi_ig1(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, positionCasesLibres, positionCasesLibresAttaque, nbrePionJoueur);
				if(donner_position_cases_libres_attaque(numCaseDestination, couleurJoueur))
				{
					if(est_acceptee_multi_attaque())
					{
						numCasePionChoisi.ligne = numCaseDestination.ligne;
						numCasePionChoisi.colonne = numCaseDestination.colonne;
						est_multiAttaque = TRUE;
						centreCasePionChoisi = convertir_numCase_en_centreCase(numCasePionChoisi);
						trouver_cases_libres_ig1(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&positionCasesLibres,&positionCasesLibresAttaque, est_multiAttaque);
					}
					else
						return;
				}
				else
					return;
			}
			else if( !est_multiAttaque)
				break;
		}while(1);
	}while(1);
}

/*
 * /\ CONTRÔLEUR /\
 * ||            ||
 */

BOOL est_fin_jeu_dans_terminal(COULP couleurJoueur, int nbrePionJoueur)
{
	if(tester_fin_jeu(couleurJoueur, nbrePionJoueur) == 1)
	{
		printf("Le joueur %d n'a plus de pion. Le joueur %d a gagné !\n", couleurJoueur, (couleurJoueur == coul1) ? coul2 : coul1);
		return 1;
	}
	else if(tester_fin_jeu(couleurJoueur, nbrePionJoueur) == 2)
	{
		printf("Le joueur %d est bloqué. Le joueur %d a gagné !\n", couleurJoueur, (couleurJoueur == coul1) ? coul2 : coul1);
		return 1;
	}
	return 0;
}

int main()
{
	BOOL rejouer = true;
	int igChoisi, nbrePionJ1, nbrePionJ2;
	int *nbrePionAutreJoueur;
	COULP couleurJoueur = coul1;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do
	{
		igChoisi = 0;
		nbrePionJ1 = 20, nbrePionJ2 = 20;
		nbrePionAutreJoueur = &nbrePionJ2;
		couleurJoueur = coul1;
		
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
				//~ tour_piece_ig2(couleurJoueur);
				//~ changer_tour_joueur_ig2(&couleurJoueur);
			}
		}while( !est_fin_jeu_dans_terminal(couleurJoueur, *nbrePionAutreJoueur));
		rejouer = redemander_partie();
	}while(rejouer);
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}

