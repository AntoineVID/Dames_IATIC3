/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include "jouer.h"


PIECE plateau[10][10];


/*
 * ||        ||
 * \/ MODÈLE \/
 */

/*		-- Manipulation tableau logique --		*/

void initialiser_tableau()
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

/*		-- Déplacement, attaque et dame --		*/

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

/*		-- Test blocage --		*/

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

void afficher_dame_ig1(POINT losangeCentre)
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

void afficher_case_ig2(POINT centre,COULEUR couleur)
{
	POINT bgCase, hdCase;
	
	bgCase.x = centre.x - LARG_CASE / 2;
	bgCase.y = centre.y - LARG_CASE / 2;
	hdCase.x = centre.x + LARG_CASE / 2;
	hdCase.y = centre.y + LARG_CASE / 2;
	
	draw_fill_rectangle(bgCase,hdCase,couleur);
}

void afficher_piece(POINT centre, CHOIXIG igChoisi)
{
	COULEUR couleur;
	NUMCASE nc;
	nc = convertir_centreCase_en_numCase(centre, igChoisi);
	couleur = convertir_joueur_couleur(plateau[nc.colonne][nc.ligne].coulP);
	
	if(igChoisi == ig1)
	{
		afficher_pion_ig1(centre,couleur);
		if(plateau[nc.colonne][nc.ligne].typeP == dame)
		{
			afficher_dame_ig1(centre);
		}
	}
	else
	{
		afficher_pion_ig2(centre,couleur);
		if(plateau[nc.colonne][nc.ligne].typeP == dame)
		{
			afficher_dame_ig2(centre);
		}
	}
}

void afficher_case(POINT centre, COULEUR couleur, CHOIXIG igChoisi)
{
	if(igChoisi == ig1)
		afficher_case_ig1(centre, couleur);
	else
		afficher_case_ig2(centre, couleur);
}

void afficher_plateau(CHOIXIG igChoisi)
{
	int i,j;
	NUMCASE nc;
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			nc.ligne = i; nc.colonne = j;
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) )
			{
				afficher_case(convertir_numCase_en_centreCase(nc, igChoisi), COULEUR_CASE_JOUEURS, igChoisi);
				if(plateau[nc.colonne][nc.ligne].coulP != aucune)
					afficher_piece(convertir_numCase_en_centreCase(nc, igChoisi), igChoisi);
			}
			else
			{
				afficher_case(convertir_numCase_en_centreCase(nc, igChoisi), COULEUR_CASE_VIDE, igChoisi);
			}
		}
	}
}

void afficher_ecran_jeu(CHOIXIG igChoisi)
{
	fill_screen(noir);
	afficher_plateau(igChoisi);
	affiche_all();
}

/*		-- Afficher Interface --		*/

void afficher_interface(CHOIXIG igChoisi, COULEUR couleur)
{
	POINT texteTour,pionInterface;
	
	texteTour.x=HAUT_FENETRE+20; texteTour.y=HAUT_FENETRE-20;
	pionInterface.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	pionInterface.y=0.85*HAUT_FENETRE;
	
	effacer_tour();
	
	aff_pol("A qui de jouer ?",20,texteTour,blanc);
	
	if(igChoisi==ig1)
	{
		afficher_pion_ig1(pionInterface,couleur);
	}
	else
	{
		afficher_pion_ig2(pionInterface,couleur);
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

void modifier_couleur_cases_libres(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleur, CHOIXIG igChoisi)
{
	if(igChoisi == ig1)
		modifier_couleur_cases_libres_ig1(origine, casesLibresDep, casesLibresAtk, couleur);
	else
		modifier_couleur_cases_libres_ig2(origine, casesLibresDep, casesLibresAtk, couleur);
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

/*		-- Retirer pion pris --		*/

void enlever_pion_qui_subit_attaque(POINT caseOrig, POINT caseDest, CHOIXIG igChoisi)
{
	POINT caseMilieu;
	
	caseMilieu.x = (caseOrig.x + caseDest.x) / 2;
	caseMilieu.y = (caseOrig.y + caseDest.y) / 2;
	if(igChoisi == ig1)
		afficher_case_ig1(caseMilieu, COULEUR_CASE_JOUEURS);
	else
		afficher_case_ig2(caseMilieu, COULEUR_CASE_JOUEURS);
	
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
	POINT PouiHD, PouiBG, PnonHD, PnonBG;
	
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
	POINT centreCase, titre;
	
	centreCase.x=440+LARG_CASE/2; centreCase.y=120+LARG_CASE/2;
	titre.x=LARG_FENETRE/1.5; titre.y=HAUT_FENETRE-100;
	
	aff_pol("Interface 2",20,titre,blanc);
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) )
			{
				afficher_case_ig2(centreCase,COULEUR_CASE_VIDE);
				
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
				afficher_case_ig2(centreCase,COULEUR_CASE_JOUEURS);
			}
			
			centreCase.x+=LARG_CASE;
		}
		
		centreCase.x=440+LARG_CASE/2;
		centreCase.y+=LARG_CASE;
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

void afficher_gagnant(COULP couleurJoueur, TYPEDEFAITE finJeu)
{
	POINT ptTextePlusPion, ptTexteBloque;
	
	ptTextePlusPion.x=30; ptTextePlusPion.y=HAUT_FENETRE-50;
	ptTexteBloque.x=75; ptTexteBloque.y=HAUT_FENETRE-50;
	
	if(couleurJoueur == coul1 && finJeu == aucunPion)
	{
		aff_pol("Le joueur 1 n'a plus de pion. Le joueur 2 gagne !",30,ptTextePlusPion,crimson);
	}
	
	if(couleurJoueur == coul2 && finJeu == aucunPion)
	{
		aff_pol("Le joueur 2 n'a plus de pion. Le joueur 1 gagne !",30,ptTextePlusPion,crimson);
	}
	
	
	if(couleurJoueur == coul1 && finJeu == pionsBloques)
	{
		aff_pol("Le joueur 1 est bloque. Le joueur 2 gagne !",30,ptTexteBloque,crimson);
	}
	
	if(couleurJoueur == coul2 && finJeu == pionsBloques)
	{
		aff_pol("Le joueur 2 est bloque. Le joueur 1 gagne !",30,ptTexteBloque,crimson);
	}
}

BOOL redemander_partie(COULP couleurJoueur, TYPEDEFAITE finJeu)
{
	POINT ptRejouer, PouiHG, PouiBD, PnonHG, PnonBD;
	
	ptRejouer.x=LARG_FENETRE/4; ptRejouer.y=HAUT_FENETRE/2;
	PouiHG.x=(LARG_FENETRE/3)+150; PouiHG.y=HAUT_FENETRE/2;
	PouiBD.x = PouiHG.x + 60; PouiBD.y = PouiHG.y - 45;
	PnonHG.x=(LARG_FENETRE/3)+250; PnonHG.y=PouiHG.y;
	PnonBD.x = PnonHG.x + 60; PnonBD.y = PnonHG.y - 45;
	
	
	fill_screen(noir);
	afficher_gagnant(couleurJoueur, finJeu);
	aff_pol("Rejouer ?",40,ptRejouer,blanc);
	aff_pol("Oui",40,PouiHG,vertclair);
	aff_pol("Non",40,PnonHG,darkred);
	affiche_all();
	
	return recuperer_clic_oui_non(PouiHG, PouiBD, PnonHG, PnonBD);
}

/*
 * /\ VUE /\
 * ||     ||
 */

/*
 * ||            ||
 * \/ CONTRÔLEUR \/
 */

NUMCASE convertir_clic_en_numCase(POINT clic, CHOIXIG igChoisi)
{
	NUMCASE nc;
	
	if(igChoisi == ig1)
	{
		nc.ligne = clic.y / LARG_CASE;
		nc.colonne = clic.x / LARG_CASE;
	}
	else
	{
		nc.ligne = clic.x / LARG_CASE;
		nc.colonne = 9 - ( clic.y / LARG_CASE );
	}
	
	return nc;
}

POINT convertir_numCase_en_centreCase(NUMCASE numcase, CHOIXIG igChoisi)
{
	POINT centreCase;
	
	if(igChoisi == ig1)
	{
		centreCase.x=(numcase.colonne*LARG_CASE)+(LARG_CASE/2);
		centreCase.y=(numcase.ligne*LARG_CASE)+(LARG_CASE/2);
	}
	else
	{
		centreCase.x=(numcase.ligne * LARG_CASE) + (LARG_CASE/2);
		centreCase.y=( (9 - numcase.colonne) * LARG_CASE) + (LARG_CASE/2);
	}
	
	return centreCase;
}

NUMCASE convertir_centreCase_en_numCase(POINT centre, CHOIXIG igChoisi)
{
	NUMCASE numcase;
	
	if(igChoisi == ig1)
	{
		numcase.ligne=(centre.y)/(LARG_CASE);
		numcase.colonne=(centre.x)/(LARG_CASE);
	}
	else
	{
		numcase.ligne=(centre.x)/(LARG_CASE);
		numcase.colonne= 9 - (centre.y)/(LARG_CASE);
	}
	
		return numcase;
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
}

/*
 * /\ CONTRÔLEUR /\
 * ||            ||
 */

int main()
{
	int nbrePionJ1, nbrePionJ2, casesLibresDep, casesLibresAtk;
	int *nbrePionAutreJoueur;
	BOOL est_multiAtk, estTourTermine;
	COULP couleurJoueur;
	CHOIXIG igChoisi;
	TYPEDEFAITE finJeu;
	POINT PouiHG, PouiBD, PnonHG, PnonBD, clic;
	NUMCASE numCaseOrig, numCaseDest;
	
	PouiHG.x = 70; PouiHG.y = 420;
	PouiBD.x = 370; PouiBD.y = 120;
	PnonHG.x = 440; PnonHG.y = 420;
	PnonBD.x = 740; PnonBD.y = 120;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do
	{
		nbrePionJ1 = 20, nbrePionJ2 = 20;
		couleurJoueur = coul1;
		
		initialiser_tableau();
		afficher_ecran_titre();
		igChoisi = (recuperer_clic_oui_non(PouiHG, PouiBD, PnonHG, PnonBD)) ? ig1 : ig2;
		afficher_ecran_jeu(igChoisi);
		
		do
		{
			nbrePionAutreJoueur = (couleurJoueur == coul1) ? &nbrePionJ2 : &nbrePionJ1;
			casesLibresDep = 0;
			casesLibresAtk = 0;
			
			afficher_interface(igChoisi, convertir_joueur_couleur(couleurJoueur));
			
			do
			{
				est_multiAtk = FALSE;
				estTourTermine = FALSE;
				
				do{
					clic = recuperer_coords_clic_plateau();
					numCaseOrig = convertir_clic_en_numCase(clic, igChoisi);
				}while( ( plateau[numCaseOrig.colonne][numCaseOrig.ligne].coulP != couleurJoueur )
					|| ( est_bloque(numCaseOrig) ));
				trouver_cases_libres(numCaseOrig, &casesLibresDep, &casesLibresAtk, est_multiAtk, igChoisi);
				modifier_couleur_cases_libres(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), casesLibresDep, casesLibresAtk, COULEUR_CASE_LIBRE, igChoisi);
				do
				{
					afficher_texte_choix_destination();
					clic = recuperer_coords_clic_plateau();
					numCaseDest = convertir_clic_en_numCase(clic, igChoisi);
					effacer_texte_choix_destination();
					modifier_couleur_cases_libres(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), casesLibresDep, casesLibresAtk, COULEUR_CASE_JOUEURS, igChoisi);
					
					if( !est_multiAtk && est_coup_valide_deplacement(numCaseOrig, numCaseDest))
					{
						effectuer_deplacement_dans_tableau_logique(numCaseOrig,numCaseDest);
						estTourTermine = TRUE;
						
						afficher_case(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), COULEUR_CASE_JOUEURS, igChoisi);
						afficher_piece(convertir_numCase_en_centreCase(numCaseDest,igChoisi), igChoisi);
						affiche_all();
						
						break;
					}
					else if(est_coup_valide_attaque(numCaseOrig, numCaseDest))
					{
						effectuer_attaque_dans_tableau_logique(numCaseOrig, numCaseDest, nbrePionAutreJoueur);
						
						afficher_case(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), COULEUR_CASE_JOUEURS, igChoisi);
						afficher_piece(convertir_numCase_en_centreCase(numCaseDest,igChoisi), igChoisi);
						enlever_pion_qui_subit_attaque(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), convertir_numCase_en_centreCase(numCaseDest, igChoisi), igChoisi);
						
						if(donner_position_cases_libres_attaque(numCaseDest))
						{
							if(est_acceptee_multi_attaque())
							{
								est_multiAtk = TRUE;
								numCaseOrig.ligne = numCaseDest.ligne;
								numCaseOrig.colonne = numCaseDest.colonne;
								trouver_cases_libres(numCaseOrig, &casesLibresDep, &casesLibresAtk, est_multiAtk, igChoisi);
							}
							else
							{
								estTourTermine = TRUE;
								break;
							}
						}
						else
						{
							estTourTermine = TRUE;
							break;
						}
					}
					else if( !est_multiAtk)
						break;
				if(est_multiAtk)
					modifier_couleur_cases_libres(convertir_numCase_en_centreCase(numCaseOrig, igChoisi), casesLibresDep, casesLibresAtk, COULEUR_CASE_LIBRE, igChoisi);
				}while(1);
			}while( !estTourTermine);
			couleurJoueur = (couleurJoueur == coul1) ? coul2 : coul1;
			finJeu = tester_fin_jeu(couleurJoueur, *nbrePionAutreJoueur);
		}while( !finJeu);
		
	}while( redemander_partie(couleurJoueur, finJeu) );
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}
