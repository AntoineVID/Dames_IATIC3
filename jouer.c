/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include "jouer.h"


PIECE plateau[10][10];


/*
 * ||        ||
 * \/ MODÈLE \/
 */

/* Manipulation du tableau logique */

void effectuer_attaque_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, int *nbrePionJoueur)
{
	NUMCASE milieu;
	milieu.ligne = (depart.ligne + arrivee.ligne) / 2;
	milieu.colonne = (depart.colonne + arrivee.colonne) / 2;
	
	plateau[arrivee.colonne][arrivee.ligne].typeP = plateau[depart.colonne][depart.ligne].typeP;
	plateau[arrivee.colonne][arrivee.ligne].coulP = plateau[depart.colonne][depart.ligne].coulP;
	plateau[milieu.colonne][milieu.ligne].typeP = vide;
	plateau[milieu.colonne][milieu.ligne].coulP = aucune;
	plateau[depart.colonne][depart.ligne].typeP = vide;
	plateau[depart.colonne][depart.ligne].coulP = aucune;
	transformer_pion_en_dame(arrivee);
	*nbrePionJoueur = *nbrePionJoueur - 1;
}

void effectuer_deplacement_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee)
{
	plateau[arrivee.colonne][arrivee.ligne].typeP = plateau[depart.colonne][depart.ligne].typeP;
	plateau[arrivee.colonne][arrivee.ligne].coulP = plateau[depart.colonne][depart.ligne].coulP;
	plateau[depart.colonne][depart.ligne].typeP = vide;
	plateau[depart.colonne][depart.ligne].coulP = aucune;
	transformer_pion_en_dame(arrivee);
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

/*
 * Les deux fonctions suivantes déterminent la position des cases libres autour du pion.
 * La première teste le déplacement et la seconde l'attaque.
 * 
 * En fonction de l'état (case libre ou occupée) de chaque case en diagonale, un nombre leur est attribué.
 * Si une case est occupée, ce nombre vaut 0, si elle est libre, le nombre vaut :
 * 1 pour la case en haut à gauche
 * 2 pour la case en haut à droite                        1   2
 * 4 pour la case en bas à gauche                           X
 * 8 pour la case en bas à droite                         4   8
 * 
 * La valeur de renvoi de chaque fonction est donc un entier appartenant à [0, 15].
 * Il correspond à la somme des quatres nombres donnant les états de chaque case (libre ou occupée)
 */

int donner_position_cases_libres_attaque(NUMCASE depart)
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
			if(depart.colonne > 1 && est_coup_valide_attaque(depart, arrivee))
				cases_libres += 1;
			arrivee.colonne = depart.colonne + 2;
			if(depart.colonne < 8 && est_coup_valide_attaque(depart, arrivee))
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
			if(depart.colonne > 1 && est_coup_valide_attaque(depart, arrivee))
				cases_libres += 4;
			arrivee.colonne = depart.colonne + 2;
			if(depart.colonne < 8 && est_coup_valide_attaque(depart, arrivee))
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

BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination)
{
	PIECE piece = plateau[origine.colonne][origine.ligne];
	int deltaCol = destination.colonne - origine.colonne;
	int deltaLig = destination.ligne - origine.ligne;
	COULP couleurEnnemi = (plateau[origine.colonne][origine.ligne].coulP == coul1) ? coul2 : coul1;
	
	if(plateau[destination.colonne][destination.ligne].coulP == aucune)
	{
		if( ( ( deltaLig == 2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul1) )
			&& ( plateau[destination.colonne - 1][destination.ligne - 1].coulP == couleurEnnemi ) )
		||
		( ( deltaLig == 2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul1) )
			&& ( plateau[destination.colonne + 1][destination.ligne - 1].coulP == couleurEnnemi ) )
		||
		( ( deltaLig == -2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul2) )
			&& ( plateau[destination.colonne - 1][destination.ligne + 1].coulP == couleurEnnemi ) )
		||
		( ( deltaLig == -2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul2) )
			&& ( plateau[destination.colonne + 1][destination.ligne + 1].coulP == couleurEnnemi )))
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

BOOL est_bloque(NUMCASE depart)
{
	return ( !donner_position_cases_libres_deplacement(depart) && !donner_position_cases_libres_attaque(depart) );
}

BOOL est_joueur_bloque(COULP couleurJoueur, int nbrePionJoueur)
{
	int i, j;
	NUMCASE case_testee;
	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			case_testee.ligne = j;
			case_testee.colonne = i;
			if(plateau[case_testee.colonne][case_testee.ligne].coulP == couleurJoueur && !est_bloque(case_testee))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

TYPEDEFAITE tester_fin_jeu(COULP couleurJoueur, int nbrePionJoueur)
{
	if(nbrePionJoueur == 0)
	{
		return aucunPion;
	}
	if(est_joueur_bloque(couleurJoueur, nbrePionJoueur))
	{
		return pionsBloques;
	}
	return peutJouer;
}

void transformer_pion_en_dame(NUMCASE nc)
{
	if(plateau[nc.colonne][nc.ligne].typeP != dame)
	{
		if( ( nc.ligne == 9 && plateau[nc.colonne][nc.ligne].coulP == coul1)
		||
		( nc.ligne == 0 && plateau[nc.colonne][nc.ligne].coulP == coul2))
		{
			plateau[nc.colonne][nc.ligne].typeP = dame;
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
		couleur=COULEUR_JOUEUR1;
	else if(couleurJoueur == coul2)
		couleur=COULEUR_JOUEUR2;
	
	return couleur;
}

/*		-- Afficher pieces / plateau --		*/

void afficher_pion_ig1(POINT losangeCentre,COULEUR couleur)
{
	POINT sommet,baseDroit,baseGauche;
	
	sommet.x=losangeCentre.x;
	sommet.y=losangeCentre.y+0.5*LONGUEUR_PIECE;
	
	baseDroit.x=losangeCentre.x-0.5*LONGUEUR_PIECE;
	baseDroit.y=losangeCentre.y;
	
	baseGauche.x=losangeCentre.x+0.5*LONGUEUR_PIECE;
	baseGauche.y=losangeCentre.y;
	
	draw_fill_triangle(sommet,baseDroit,baseGauche,couleur);
	
	sommet.x=losangeCentre.x;
	sommet.y=losangeCentre.y-0.5*LONGUEUR_PIECE;
	
	baseDroit.x=losangeCentre.x-0.5*LONGUEUR_PIECE;
	baseDroit.y=losangeCentre.y;
	
	baseGauche.x=losangeCentre.x+0.5*LONGUEUR_PIECE;
	baseGauche.y=losangeCentre.y;
	
	draw_fill_triangle(sommet,baseDroit,baseGauche,couleur);
}

void afficher_dame_ig1(POINT losangeCentre,COULEUR couleur)
{
	POINT sommet,baseDroit,baseGauche;
	
	sommet.x=losangeCentre.x;
	sommet.y=losangeCentre.y+0.3*LONGUEUR_PIECE;
	
	baseDroit.x=losangeCentre.x-0.6*(LONGUEUR_PIECE/2);
	baseDroit.y=losangeCentre.y;
	
	baseGauche.x=losangeCentre.x+0.6*(LONGUEUR_PIECE/2);
	baseGauche.y=losangeCentre.y;
	
	draw_fill_triangle(sommet,baseDroit,baseGauche,COULEUR_DAME);
	
	sommet.x=losangeCentre.x;
	sommet.y=losangeCentre.y-0.3*LONGUEUR_PIECE;
	
	baseDroit.x=losangeCentre.x-0.6*(LONGUEUR_PIECE/2);
	baseDroit.y=losangeCentre.y;
	
	baseGauche.x=losangeCentre.x+0.6*(LONGUEUR_PIECE/2);
	baseGauche.y=losangeCentre.y;
	
	draw_fill_triangle(sommet,baseDroit,baseGauche,COULEUR_DAME);
}

void afficher_case_ig1(POINT centre,COULEUR couleur)
{
	draw_fill_circle(centre,LARG_CASE/2,couleur);
}

void afficher_pion_ig2(POINT centre,COULEUR couleur)
{
	draw_fill_circle(centre,LONGUEUR_PIECE/2,couleur);
}

void afficher_dame_ig2(POINT centre)
{
	draw_fill_circle(centre,LONGUEUR_PIECE/3,COULEUR_DAME);
}

void afficher_case_ig2(POINT bgCase,POINT hdCase,COULEUR couleur)
{
	draw_fill_rectangle(bgCase,hdCase,couleur);
}

void afficher_piece(POINT centre,int ligne,int colonne, CHOIXIG igChoisi)
{
	COULEUR couleur;
	couleur = convertir_joueur_couleur(plateau[colonne][ligne].coulP);
	
	if(igChoisi == ig1)
	{
		afficher_pion_ig1(centre,couleur);
		if(plateau[colonne][ligne].typeP == dame)
		{
			afficher_dame_ig1(centre);
		}
	}
	else
	{
		afficher_pion_ig2(centre,couleur);
		if(plateau[colonne][ligne].typeP == dame)
		{
			afficher_dame_ig2(centre);
		}
	}
}

void afficher_plateau(CHOIXIG igChoisi)
{
	int i=0,j=0;
	POINT centre;
	
	centre.x=LARG_CASE/2; centre.y=LARG_CASE/2;
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) )
			{
				afficher_case_ig1(centre,COULEUR_CASE_JOUEURS);
				
				if(plateau[j][i].coulP != aucune)
				{
					afficher_piece_ig(centre,i,j,igChoisi);
				}
			}
			
			else
			{
				afficher_case_ig1(centre,COULEUR_CASE_VIDE);
			}
		
			centre.x+=LARG_CASE;
		}
		
		centre.x=LARG_CASE/2;
		centre.y+=LARG_CASE;
	}
}

void afficher_ecran_jeu(CHOIXIG igChoisi)
{
	fill_screen(noir);
	afficher_plateau(igChoisi);
	afficher_interface(igChoisi);
	affiche_all();
}

/*		-- Afficher Interface --		*/

void afficher_interface(CHOIXIG igChoisi)
{
	POINT texteTour,pionInterface;
	
	texteTour.x=HAUT_FENETRE+20; texteTour.y=HAUT_FENETRE-20;
	pionInterface.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	pionInterface.y=0.85*HAUT_FENETRE;
	
	effacer_tour();
	
	aff_pol("A qui de jouer ?",20,texteTour,blanc);
	
	if(igChoisi==ig1)
	{
		afficher_pion_ig1(pionInterface,COULEUR_JOUEUR1);
	}
	else
	{
		afficher_pion_ig2(tourJoueur,COULEUR_JOUEUR1);
	}
	affiche_all();
}

void effacer_tour()
{
	POINT P1,P2;
	
	P1.x=HAUT_FENETRE+1; P1.y=0.8*HAUT_FENETRE;
	P2.x=LARG_FENETRE; P2.y=0.9*HAUT_FENETRE;
	
	draw_fill_rectangle(P1,P2,noir);
}

/*		-- Choisir pion valide --		*/

POINT recuperer_coords_clic_plateau()
{
	POINT clic;
	
	do{
		clic=wait_clic();
	}while(clic.x>HAUT_FENETRE);
	
	return clic;
}

void modifier_couleur_cases_libres_ig1(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleurCase)
{
	POINT caseLibre;
	
	/* Cases Normales */
	if(casesLibresDep%2>0) //case libre haut gauche
	{
		caseLibre.x=origine.x-LARG_CASE;
		caseLibre.y=origine.y+LARG_CASE;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	if(casesLibresDep%4>1) //case libre haut droite
	{
		caseLibre.x=origine.x+LARG_CASE;
		caseLibre.y=origine.y+LARG_CASE;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	if(casesLibresDep%8>3) //case libre bas gauche
	{
		caseLibre.x=origine.x-LARG_CASE;
		caseLibre.y=origine.y-LARG_CASE;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	if(casesLibresDep%16>7) //case libre bas droite
	{
		caseLibre.x=origine.x+LARG_CASE;
		caseLibre.y=origine.y-LARG_CASE;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	/* Cases Attaque */
	if(casesLibresAtk%2>0) //case libre haut gauche
	{
		caseLibre.x=origine.x-LARG_CASE*2;
		caseLibre.y=origine.y+LARG_CASE*2;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	if(casesLibresAtk%4>1) //case libre haut droite
	{
		caseLibre.x=origine.x+LARG_CASE*2;
		caseLibre.y=origine.y+LARG_CASE*2;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);
	}
	
	if(casesLibresAtk%8>3) //case libre bas gauche
	{
		caseLibre.x=origine.x-LARG_CASE*2;
		caseLibre.y=origine.y-LARG_CASE*2;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);	
	}
	
	if(casesLibresAtk%16>7) //case libre bas droite
	{
		caseLibre.x=origine.x+LARG_CASE*2;
		caseLibre.y=origine.y-LARG_CASE*2;
		draw_fill_circle(caseLibre,LARG_CASE/2,couleurCase);	
	}
}

void modifier_couleur_cases_libres_ig2(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleurCase)
{
	POINT bgCaseLibre,hdCaseLibre;
	
	/* Cases Normales */
	if(casesLibresDep%2>0) //case libre haut droite
	{
		bgCaseLibre.x=origine.x+0.5*LARG_CASE;
		bgCaseLibre.y=origine.y+0.5*LARG_CASE;
		hdCaseLibre.x=origine.x+1.5*LARG_CASE;
		hdCaseLibre.y=origine.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
		
	}
	
	if(casesLibresDep%4>1) //case libre bas droit
	{
		bgCaseLibre.x=origine.x+0.5*LARG_CASE;
		bgCaseLibre.y=origine.y-0.5*LARG_CASE;
		hdCaseLibre.x=origine.x+1.5*LARG_CASE;
		hdCaseLibre.y=origine.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
	
	if(casesLibresDep%8>3) //case libre haut gauche
	{
		bgCaseLibre.x=origine.x-1.5*LARG_CASE;
		bgCaseLibre.y=origine.y+0.5*LARG_CASE;
		hdCaseLibre.x=origine.x-0.5*LARG_CASE;
		hdCaseLibre.y=origine.y+1.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
	
	if(casesLibresDep%16>7) //case libre bas gauche
	{
		bgCaseLibre.x=origine.x-0.5*LARG_CASE;
		bgCaseLibre.y=origine.y-0.5*LARG_CASE;
		hdCaseLibre.x=origine.x-1.5*LARG_CASE;
		hdCaseLibre.y=origine.y-1.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
	
	/* Cases Attaque */
	if(casesLibresAtk%2>0) //case libre haut droite
	{
		bgCaseLibre.x=origine.x+1.5*LARG_CASE;
		bgCaseLibre.y=origine.y+1.5*LARG_CASE;
		hdCaseLibre.x=origine.x+2.5*LARG_CASE;
		hdCaseLibre.y=origine.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
		
	}
	
	if(casesLibresAtk%4>1) //case libre bas droit)
	{
		bgCaseLibre.x=origine.x+1.5*LARG_CASE;
		bgCaseLibre.y=origine.y-1.5*LARG_CASE;
		hdCaseLibre.x=origine.x+2.5*LARG_CASE;
		hdCaseLibre.y=origine.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
	
	if(casesLibresAtk%8>3) //case libre haut gauche
	{
		bgCaseLibre.x=origine.x-2.5*LARG_CASE;
		bgCaseLibre.y=origine.y+1.5*LARG_CASE;
		hdCaseLibre.x=origine.x-1.5*LARG_CASE;
		hdCaseLibre.y=origine.y+2.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
	
	if(casesLibresAtk%16>7) //case libre bas gauche
	{
		bgCaseLibre.x=origine.x-1.5*LARG_CASE;
		bgCaseLibre.y=origine.y-1.5*LARG_CASE;
		hdCaseLibre.x=origine.x-2.5*LARG_CASE;
		hdCaseLibre.y=origine.y-2.5*LARG_CASE;
		
		draw_fill_rectangle(bgCaseLibre,hdCaseLibre,couleurCase);
	}
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

/*		-- Retirer pion pris --		*/

void enlever_pion_qui_subit_attaque(POINT pionChoisi, POINT caseDestination, CHOIXIG igChoisi)
{
	POINT caseLibre;
	
	caseLibre.x = (pionChoisi.x + caseDestination.x) / 2;
	caseLibre.y = (pionChoisi.y + caseDestination.y) / 2;
	if(igChoisi == ig1)
		afficher_case_ig1(caseLibre, COULEUR_CASE_JOUEURS);
	else
		afficher_case_ig2(caseLibre, COULEUR_CASE_JOUEURS);
	
	affiche_all();
}

/*		-- Choix attaque multiple --		*/

void afficher_choix_multi_attaque()
{
	POINT ptMultiAtk1, ptMultiAtk2, ptOui1, ptOui2, ptNon1, ptNon2;
	
	ptMultiAtk1.x = HAUT_FENETRE + 10; ptMultiAtk1.y = HAUT_FENETRE / 4 + 30;
	ptMultiAtk2.x = HAUT_FENETRE + 10; ptMultiAtk2.y = HAUT_FENETRE / 4;
	ptOui1.x = HAUT_FENETRE + 20; ptOui1.y = HAUT_FENETRE / 4 - 30;
	ptOui2.x = HAUT_FENETRE + 60; ptOui2.y = HAUT_FENETRE / 4 - 60;
	ptNon1.x = HAUT_FENETRE + 10 + 100; ptNon1.y = HAUT_FENETRE / 4 - 30;
	ptNon2.x = HAUT_FENETRE + 10 + 140; ptNon2.y = HAUT_FENETRE / 4 - 60;
	
	aff_pol("Attaque possible", 20, ptMultiAtk1, blanc);
	aff_pol("Continuer ?", 20, ptMultiAtk2, blanc);
	aff_pol("Oui", 20, ptOui1, vert);
	draw_rectangle(ptOui1, ptOui2, vert);
	aff_pol("Non", 20, ptNon1, rouge);
	draw_rectangle(ptNon1, ptNon2, rouge);
	affiche_all();
	return;
}

void effacer_choix_multi_attaque()
{
	POINT P1, P2;
	
	P1.x = HAUT_FENETRE + 10; P1.y = HAUT_FENETRE / 4 + 30;
	P2.x = LARG_FENETRE; P2.y = 0;
	
	draw_fill_rectangle(P1, P2, noir);
	affiche_all();
}

BOOL est_acceptee_multi_attaque()
{
	BOOL choix;
	POINT ptOui1, ptOui2, ptNon1, ptNon2;
	
	PouiHD.x = HAUT_FENETRE + 20; PouiHD.y = HAUT_FENETRE / 4 - 30;
	PouiBG.x = HAUT_FENETRE + 60; PouiBG.y = HAUT_FENETRE / 4 - 60;
	PnonHD.x = HAUT_FENETRE + 10 + 100; PnonHD.y = HAUT_FENETRE / 4 - 30;
	PnonBG.x = HAUT_FENETRE + 10 + 140; PnonBG.y = HAUT_FENETRE / 4 - 60;
	
	afficher_choix_multi_attaque();
	choix = recuperer_clic_oui_non(PouiHD, PouiBG, PnonHD, PnonBG);
	effacer_choix_multi_attaque();
	return choix;
}

/*		-- Afficher Ecran Titre --		*/

void afficher_textes_accueil()
{
	POINT texte1, texte2;
	
	texte1.x=LARG_FENETRE/6; texte1.y=HAUT_FENETRE-10;
	texte2.x=130; texte2.y=30;
	
	aff_pol("Projet Dames IATIC3 - CORBEIL Alex / VIDAL Antoine",20,texte1,blanc);
	aff_pol("Cliquer dans le plateau dans lequel vous voulez jouer",20,texte2,blanc);
}

void afficher_exemple_ecran_titre_ig1()
{
	int i,j;
	POINT centreCase, titre;
	
	centreCase.x=100; centreCase.y=150;
	titre.x=LARG_FENETRE/5; titre.y=HAUT_FENETRE-100;
	
	aff_pol("Interface 1",20,titre,blanc);
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) )
			{
				afficher_case_ig1(centreCase,COULEUR_CASE_JOUEURS);
				if(i<2)
					afficher_pion_ig1(centreCase,COULEUR_JOUEUR1);
				
				if(i>2)
					afficher_pion_ig1(centreCase,COULEUR_JOUEUR2);
			}
			
			else
			{
				afficher_case_ig1(centreCase,COULEUR_CASE_VIDE);
			}
		
			centreCase.x+=LARG_CASE;
		}
		
		centreCase.x=100;
		centreCase.y+=LARG_CASE;
	}
	
	affiche_all();
}

void afficher_exemple_ecran_titre_ig2()
{
	int i,j;
	POINT bgCase,hdCase,centreCase, titre;
	
	bgCase.x=440; bgCase.y=120;
	hdCase.x=bgCase.x+LARG_CASE; hdCase.y=bgCase.y+LARG_CASE;
	centreCase.x=440+LARG_CASE/2; centreCase.y=120+LARG_CASE/2;
	titre.x=LARG_FENETRE/1.5; titre.y=HAUT_FENETRE-100;
	
	aff_pol("Interface 2",20,titre,blanc);
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) )
			{
				afficher_case_ig2(bgCase,hdCase,COULEUR_CASE_VIDE);
				
				if(j<2)
				{
					afficher_pion_ig2(centreCase,COULEUR_JOUEUR1);
				}
				
				if(j>2)
				{
					afficher_pion_ig2(centreCase,COULEUR_JOUEUR2);
				}
			}
			
			else
			{
				afficher_case_ig2(bgCase,hdCase,COULEUR_CASE_JOUEURS);
			}
			
			centreCase.x+=LARG_CASE;
			bgCase.x+=LARG_CASE;
			hdCase.x+=LARG_CASE;
		}
		
		centreCase.x=440+LARG_CASE/2;
		centreCase.y+=LARG_CASE;
		bgCase.x=440; bgCase.y+=LARG_CASE;
		hdCase.x=bgCase.x+LARG_CASE; hdCase.y+=LARG_CASE;
	}
	
	affiche_all();
}

void afficher_ecran_titre()
{
	fill_screen(noir);
	afficher_textes_accueil();
	afficher_exemple_ecran_titre_ig1();
	afficher_exemple_ecran_titre_ig2();
	affiche_all();
}

/*		-- Fin Partie --		*/

void afficher_gagnant(int nbrePionJ1,int nbrePionJ2, TYPEDEFAITE finJeu)
{
	POINT ptTexteGagnant;
	
	ptTexteGagnant.x=50; ptTexteGagnant.y=HAUT_FENETRE-50;
	
	if( finJeu == aucunPion)
	{
		aff_pol("Le joueur 1 n'a plus de pion. Le joueur 2 gagne !",20,ptTexteGagnant,blanc);
	}
	
	if( finJeu == aucunPion)
	{
		aff_pol("Le joueur 2 n'a plus de pion. Le joueur 1 gagne !",20,ptTexteGagnant,blanc);
	}
	
	
	if( finJeu == pionsBloques)
	{
		aff_pol("Le joueur 1 est bloque. Le joueur 2 gagne !",20,ptTexteGagnant,blanc);
	}
	
	if( finJeu == pionsBloques)
	{
		aff_pol("Le joueur 2 est bloque. Le joueur 1 gagne !",20,ptTexteGagnant,blanc);
	}
}

BOOL redemander_partie(int nbrePionJ1,int nbrePionJ2)
{
	POINT PouiHG, PouiBD, PnonHG, PnonBD, ptRejouer;

	PouiHG.x=(LARG_FENETRE/3)+150; PouiHG.y=HAUT_FENETRE/2;
	PouiBD.x = PouiHG.x + 40; PouiBD.y = PouiHG.y - 20;
	PnonHG.x=(LARG_FENETRE/3)+250; PnonHG.y=ptOui.y;
	PnonBD.x = PnonHG.x + 40; PnonBD.y = PnonHG.y - 20;
	ptRejouer.x=LARG_FENETRE/3; ptRejouer.y=HAUT_FENETRE/2;
	
	
	fill_screen(noir);
	afficher_gagnant(nbrePionJ1,nbrePionJ2);
	aff_pol("Rejouer ?",20,ptRejouer,blanc);
	aff_pol("Oui",20,ptOui,blanc);
	aff_pol("Non",20,ptNon,blanc);
	affiche_all();
	
	return recuperer_clic_oui_non(PouiHG, PouiBD, PnonHG, PouiBD);
}

/*
 * /\ VUE /\
 * ||     ||
 */

/*
 * ||            ||
 * \/ CONTRÔLEUR \/
 */

void bouger_pion_choisi_ig1(POINT centreCasePionChoisi, POINT centreCaseDestination, NUMCASE numCaseOrig, NUMCASE numCaseDestination, COULP couleurJoueur,int casesLibresDep, int casesLibresAtk, int *nbrePionJoueur)
{
	effacer_cases_libres_choisies_ig1(centreCasePionChoisi, casesLibresDep, casesLibresAtk);
	effacer_piece_case_orig_ig1(centreCasePionChoisi);
	if( est_coup_valide_deplacement(numCaseOrig, numCaseDestination) )
	{
		effectuer_deplacement_dans_tableau_logique(numCaseOrig,numCaseDestination);
	}
	else if( est_coup_valide_attaque(numCaseOrig,numCaseDestination) )
	{
		enlever_pion_qui_subit_attaque_ig1(centreCasePionChoisi, centreCaseDestination);
		effectuer_attaque_dans_tableau_logique(numCaseOrig, numCaseDestination, nbrePionJoueur);
	}
	afficher_piece_ig1(centreCaseDestination,numCaseDestination.ligne,numCaseDestination.colonne);
	affiche_all();
}

void bouger_pion_choisi_ig2(POINT centreCasePionChoisi, POINT centreCaseDestination, NUMCASE numCaseOrig, NUMCASE numCaseDestination, COULP couleurJoueur,int casesLibresDep, int casesLibresAtk, int *nbrePionJoueur)
{
	effacer_cases_libres_choisies_ig2(centreCasePionChoisi, casesLibresDep, casesLibresAtk);
	effacer_piece_case_orig_ig2(centreCasePionChoisi);
	if( est_coup_valide_deplacement(numCaseOrig, numCaseDestination) )
	{
		effectuer_deplacement_dans_tableau_logique(numCaseOrig,numCaseDestination);
	}
	else if( est_coup_valide_attaque(numCaseOrig,numCaseDestination) )
	{
		enlever_pion_qui_subit_attaque_ig2(centreCasePionChoisi, centreCaseDestination);
		effectuer_attaque_dans_tableau_logique(numCaseOrig, numCaseDestination, nbrePionJoueur);
	}
	afficher_piece_ig2(centreCaseDestination,numCaseDestination.ligne,numCaseDestination.colonne);
	affiche_all();
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
		
	}while( est_bloque(*numCasePionChoisi) );
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
		
	}while( est_bloque(*numCasePionChoisi) );
}

POINT convertir_numCase_en_centreCase_ig1(NUMCASE numcase)
{
	POINT centreCase;
	
	centreCase.x=(numcase.colonne*LARG_CASE)+(LARG_CASE/2);
	centreCase.y=(numcase.ligne*LARG_CASE)+(LARG_CASE/2);
	
	return centreCase;
}

POINT convertir_numCase_en_centreCase_ig2(NUMCASE numcase)
{
	POINT centreCase;
	
	centreCase.x=(numCaseIg1.ligne*LARG_CASE)+(LARG_CASE/2);
	centreCase.y=(9-numCaseIg1.colonne*LARG_CASE)+(LARG_CASE/2);
	
	return centreCase;
}

BOOL recuperer_clic_oui_non(POINT ouiHG, POINT ouiBD, POINT nonHG, POINT nonBD)
{
	POINT clic;
	
	do
	{
		clic = wait_clic();
		if((clic.x > ouiHG.x) && (clic.x < ouiBD.x) && (clic.y < ouiHG.y) && (clic.y > ouiBD.y))
			return TRUE;
		else if((clic.x > nonHG.x) && (clic.x < nonBD.x) && (clic.y < nonHG.y) && (clic.y > nonBD.y))
			return FALSE;
	}while(1);
}

void trouver_cases_libres(NUMCASE numCaseOrig, int *casesLibresDep, int *casesLibresAtk, BOOL est_multiAtk, CHOIXIG igChoisi)
{
	if( !est_multiAtk)
		*casesLibresDep = donner_position_cases_libres_deplacement(numCaseOrig);
	else
		*casesLibresDep = 0;
	*casesLibresAtk = donner_position_cases_libres_attaque(numCaseOrig);
	if(igChoisi == ig1)
		afficher_cases_libres_ig1(convertir_numCase_en_centreCase_ig1(numCaseOrig), *casesLibresDep, *casesLibresAtk);
	else
		afficher_cases_libres_ig2(convertir_numCase_en_centreCase_ig2(numCaseOrig), *casesLibresDep, *casesLibresAtk);
}

void tour_piece_ig1(COULP couleurJoueur, int *nbrePionJoueur)
{
	int casesLibresDep = 0, casesLibresAtk = 0;
	POINT centreCasePionChoisi, centreCaseDestination;
	NUMCASE numCasePionChoisi, numCaseDestination;
	BOOL est_multiAtk = FALSE;
	do
	{
		effacer_cases_libres_choisies_ig1(centreCasePionChoisi,casesLibresDep,casesLibresAtk);
		choisir_pion_valide_ig1(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
		trouver_cases_libres_ig1(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&casesLibresDep,&casesLibresAtk, est_multiAtk);
		do
		{
			choisir_destination_ig1(centreCasePionChoisi,&centreCaseDestination,&numCaseDestination);
			if( !est_multiAtk && est_coup_valide_deplacement(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig1(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, casesLibresDep, casesLibresAtk, nbrePionJoueur);
				return;
			}
			if(est_coup_valide_attaque(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig1(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, casesLibresDep, casesLibresAtk, nbrePionJoueur);
				if(donner_position_cases_libres_attaque(numCaseDestination))
				{
					if(est_acceptee_multi_attaque())
					{
						est_multiAtk = TRUE;
						numCasePionChoisi.ligne = numCaseDestination.ligne;
						numCasePionChoisi.colonne = numCaseDestination.colonne;
						centreCasePionChoisi = convertir_numCase_en_centreCase(numCasePionChoisi);
						trouver_cases_libres_ig1(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&casesLibresDep,&casesLibresAtk, est_multiAtk);
					}
					else
						return;
				}
				else
					return;
			}
			else if( !est_multiAtk)
				break;
		}while(1);
	}while(1);
}

void tour_piece_ig2(COULP couleurJoueur, int *nbrePionJoueur)
{
	int casesLibresDep = 0, casesLibresAtk = 0;
	POINT centreCasePionChoisi, centreCaseDestination;
	NUMCASE numCasePionChoisi, numCaseDestination;
	BOOL est_multiAtk = FALSE;
	do
	{
		effacer_cases_libres_choisies_ig2(centreCasePionChoisi,casesLibresDep,casesLibresAtk);
		choisir_pion_valide_ig2(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
		trouver_cases_libres_ig2(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&casesLibresDep,&casesLibresAtk, est_multiAtk);
		do
		{
			choisir_destination_ig2(centreCasePionChoisi,&centreCaseDestination,&numCaseDestination);
			if( !est_multiAtk && est_coup_valide_deplacement(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig2(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, casesLibresDep, casesLibresAtk, nbrePionJoueur);
				return;
			}
			if(est_coup_valide_attaque(numCasePionChoisi, numCaseDestination))
			{
				bouger_pion_choisi_ig2(centreCasePionChoisi, centreCaseDestination, numCasePionChoisi, numCaseDestination, couleurJoueur, casesLibresDep, casesLibresAtk, nbrePionJoueur);
				if(donner_position_cases_libres_attaque(numCaseDestination))
				{
					if(est_acceptee_multi_attaque())
					{
						est_multiAtk = TRUE;
						numCasePionChoisi.ligne = numCaseDestination.ligne;
						numCasePionChoisi.colonne = numCaseDestination.colonne;
						centreCasePionChoisi = convertir_numCase_en_centreCase(numCasePionChoisi);
						trouver_cases_libres_ig2(centreCasePionChoisi,numCasePionChoisi,couleurJoueur,&casesLibresDep,&casesLibresAtk, est_multiAtk);
					}
					else
						return;
				}
				else
					return;
			}
			else if( !est_multiAtk)
				break;
		}while(1);
	}while(1);
}

/*
 * /\ CONTRÔLEUR /\
 * ||            ||
 */

int main()
{
	int nbrePionJ1, nbrePionJ2;
	int *nbrePionAutreJoueur;
	BOOL rejouer = TRUE;
	COULP couleurJoueur = coul1;
	CHOIXIG igChoisi;
	TYPEDEFAITE finJeu = peutJouer;
	POINT PouiBG, PouiHD, PnonBG, PouiHD;
	PouiHG.x = 70; PouiHG.y = 420;
	PouiBD.x = 370; PouiBD.y = 120;
	PnonHG.x = 440; PnonHG.y = 420;
	PouiBD.x = 740; PouiBD.y = 120;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do
	{
		igChoisi = ig1;
		nbrePionJ1 = 20, nbrePionJ2 = 20;
		nbrePionAutreJoueur = &nbrePionJ2;
		couleurJoueur = coul1;
		
		initialiser_plateau();
		afficher_ecran_titre();
		igChoisi = (recuperer_clic_oui_non(PouiHG, PouiBD, PnonHG, PouiBD)) ? ig1 : ig2;
		afficher_ecran_jeu_selon_ig(igChoisi);
		do
		{
			nbrePionAutreJoueur = (couleurJoueur == coul1) ? &nbrePionJ2 : &nbrePionJ1;
			if(igChoisi == ig1)
			{
				tour_piece_ig1(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_interface(*couleurJoueur, igChoisi);
			}
			else
			{
				tour_piece_ig2(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_interface(*couleurJoueur, igChoisi);
			}
			couleurJoueur = (couleurJoueur == coul1) ? coul2 : coul1;
			finJeu = tester_fin_jeu(couleurJoueur, *nbrePionAutreJoueur;
		}while( !finJeu));
		rejouer = redemander_partie(nbrePionJ1,nbrePionJ2, finJeu);
	}while(rejouer);
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}
