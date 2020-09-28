/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include <stdio.h>
#include <stdlib.h>
//~ #include "graphics.h"
#include "main.h"


/* Prototypes */


/* ----- MODELE ----- */

void initialiser_plateau();


/* ----- VUE ----- */

COULEUR convertir_joueur_couleur(COULP couleurJoueur);


/* Afficher pieces / plateau */

//Ig1
void afficher_piece_triangle_haut(POINT ptLosangeCentre,COULEUR couleur);
void afficher_piece_triangle_bas(POINT ptLosangeCentre,COULEUR couleur);
void afficher_piece_dame_triangle_haut(POINT ptLosangeCentre);
void afficher_piece_dame_triangle_bas(POINT ptLosangeCentre);
void afficher_piece_ig1(POINT ptLosangeCentre,PIECE piece);
void afficher_case_ig1(POINT ptCentreCase,COULEUR couleur);
void afficher_plateau_ig1();

//Ig2
void afficher_piece_rond(POINT ptRondCentre,COULEUR couleur);
void afficher_piece_rond_dame(POINT ptRondCentre);
void afficher_piece_ig2(POINT ptRondCentre,PIECE piece);
void afficher_case_ig2(POINT ptbgCase,POINT pthdCase,COULEUR couleur);
void afficher_plateau_ig2();

void afficher_ecran_jeu_selon_ig(int igChoisi);


/* Afficher interface */
void afficher_interface(int igChoisi);
void effacer_tour();


/* Jeu principal */
void changer_tour_joueur_ig1(COULP *couleurJoueur);
void changer_tour_interface_ig1(COULP couleurJoueur);
void changer_tour_joueur_ig2(COULP *couleurJoueur);
void changer_tour_interface_ig2(COULP couleurJoueur);
void tour_piece_ig1(COULP couleur_joueur);
void tour_piece_ig2(COULP couleur_joueur);
void jouer(int igChoisi);


/* Afficher cases libres pion */
POINT recuperer_clic_pos_plateau();
POINT convertir_clic_en_centreCase(POINT clicGauche);
NUMCASE convertir_centreCase_en_numCase(POINT centreCase);
POINT convertir_numCase_en_centreCase(NUMCASE numcase);

int connaitre_cases_libres_pion_j1_ig1(NUMCASE numCasePionChoisi);
int connaitre_cases_libres_pion_j2_ig1(NUMCASE numCasePionChoisi);
int calculer_nb_cases_libres_ig1(PIECE piece,NUMCASE numCasePionChoisi);

void choisir_pion_valide(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi);

void afficher_cases_libres_pion_ig1(POINT centrePionChoisi,COULP couleurJoueur);
void afficher_cases_libres_pion_ig2(POINT centrePionChoisi,COULP couleurJoueur);


/* Ecran titre */
void afficher_titre();
void afficher_exemple_ecran_titre_ig1(POINT ptTitreIg1);
void afficher_ecran_titre_ig1();
void afficher_exemple_ecran_titre_ig2(POINT ptTitreIg2);
void afficher_ecran_titre_ig2();

POINT recuperer_clic_choix_ig();
int choisir_ig(POINT clicChoixIg);
void afficher_ecran_titre(int *ig);


/* Redemander partie */
void afficher_texte_redemander_partie(POINT ptOui,POINT ptNon);
POINT recuperer_clic_redemander_partie(POINT ptOui,POINT ptNon);
BOOL savoir_si_rejouer_partie(POINT ptOui,POINT ptNon,POINT clicRedemanderPartie);
BOOL redemander_partie();


PIECE plateau[10][10];


/* ----- MODELE ----- */


void initialiser_plateau()
{
	int i, j;
	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			if( ( !(i % 2) && !(j % 2) && (j < 4) )
			||
			( (i % 2) && (j % 2) && (j < 4) ))
			{
				plateau[i][j].typeP = pion;
				plateau[i][j].coulP = coul1;
			}
			else if( ( !(i % 2) && !(j % 2) && (j > 5) )
			||
			( (i % 2) && (j % 2) && (j > 5) ))
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


/* ----- VUE ----- */


/* Vue */
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


/* Vue */
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


/* Vue */
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


/* Vue */
void afficher_piece_dame_triangle_haut(POINT ptLosangeCentre)
{
	POINT ptLosangeDameHaut,ptLosangeDameDroit,ptLosangeDameGauche;
	
	ptLosangeDameHaut.x=ptLosangeCentre.x;
	ptLosangeDameHaut.y=ptLosangeCentre.y+0.4*LONGUEUR_PIECE;
	
	ptLosangeDameDroit.x=ptLosangeCentre.x-0.8*(LONGUEUR_PIECE/2);
	ptLosangeDameDroit.y=ptLosangeCentre.y;
	
	ptLosangeDameGauche.x=ptLosangeCentre.x+0.8*(LONGUEUR_PIECE/2);
	ptLosangeDameGauche.y=ptLosangeCentre.y;
	
	draw_fill_triangle(ptLosangeDameHaut,ptLosangeDameDroit,ptLosangeDameGauche,COULEUR_DAME);
}


/* Vue */
void afficher_piece_dame_triangle_bas(POINT ptLosangeCentre)
{
	POINT ptLosangeDameBas,ptLosangeDameDroit,ptLosangeDameGauche;
	
	ptLosangeDameBas.x=ptLosangeCentre.x;
	ptLosangeDameBas.y=ptLosangeCentre.y-0.4*LONGUEUR_PIECE;
	
	ptLosangeDameDroit.x=ptLosangeCentre.x-0.8*(LONGUEUR_PIECE/2);
	ptLosangeDameDroit.y=ptLosangeCentre.y;
	
	ptLosangeDameGauche.x=ptLosangeCentre.x+0.8*(LONGUEUR_PIECE/2);
	ptLosangeDameGauche.y=ptLosangeCentre.y;
	
	draw_fill_triangle(ptLosangeDameBas,ptLosangeDameDroit,ptLosangeDameGauche,COULEUR_DAME);
}


/* Vue */
void afficher_piece_ig1(POINT ptLosangeCentre,PIECE piece)
{
	COULEUR couleur;
	couleur = convertir_joueur_couleur(piece.coulP);
	
	if(piece.typeP == pion)
	{
		afficher_piece_triangle_haut(ptLosangeCentre,couleur);
		afficher_piece_triangle_bas(ptLosangeCentre,couleur);
	}
		
	else if(piece.typeP == dame)
	{
		afficher_piece_dame_triangle_haut(ptLosangeCentre);
		afficher_piece_dame_triangle_bas(ptLosangeCentre);
	}
}


/* Vue */
void afficher_case_ig1(POINT ptCentreCase,COULEUR couleur)
{
	draw_fill_circle(ptCentreCase,LARG_CASE/2,couleur);
}


/* Vue */
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
					afficher_piece_ig1(ptCentreCase,plateau[j][i]);
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


/* Vue */
void afficher_piece_rond(POINT ptRondCentre,COULEUR couleur)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/2,couleur);
}


/* Vue */
void afficher_piece_rond_dame(POINT ptRondCentre)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/2.5,COULEUR_DAME);
}


/* Vue */
void afficher_piece_ig2(POINT ptRondCentre,PIECE piece)
{
	COULEUR couleur;
	couleur = convertir_joueur_couleur(piece.coulP);
	
	if(piece.typeP == pion)
	{
		afficher_piece_rond(ptRondCentre,couleur);
	}
	
	else if(piece.typeP == dame)
	{	
		afficher_piece_rond_dame(ptRondCentre);
	}
}


/* Vue */
void afficher_case_ig2(POINT ptbgCase,POINT pthdCase,COULEUR couleur)
{
	draw_fill_rectangle(ptbgCase,pthdCase,couleur);
}


/* Vue */
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
					afficher_piece_ig2(ptCentreCase,plateau[j][i]); //MAUVAIS CAR SE BASE SUR LE PLATEAU DE IG1
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


/* Vue */
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


/* Vue */
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


/* Vue */
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


/* Vue */
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


/* Vue */
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


/* Vue */
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


/* Vue */
void changer_tour_interface_ig2(COULP couleurJoueur)
{
	COULEUR couleur;
	POINT ptTourJoueur;
	
	ptTourJoueur.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptTourJoueur.y=0.85*HAUT_FENETRE;

	couleur=convertir_joueur_couleur(couleurJoueur);
	afficher_piece_rond(ptTourJoueur,couleur);
}


/* Vue */
void tour_piece_ig1(COULP couleurJoueur)
{
	POINT centreCasePionChoisi;
	NUMCASE numCasePionChoisi;
	
	//~ do{
		choisir_pion_valide(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
		afficher_cases_libres_pion_ig1(centreCasePionChoisi,couleurJoueur);
	//~ }while(/*est_coup_valide_deplacement(numCasePionChoisi,numCaseDestination) == false*/);
	
	/* BOUGER PION */
	
	affiche_all();
}


/* Vue */
void tour_piece_ig2(COULP couleurJoueur)
{
	POINT centreCasePionChoisi;
	NUMCASE numCasePionChoisi;
	
	choisir_pion_valide(couleurJoueur,&centreCasePionChoisi,&numCasePionChoisi);
	afficher_cases_libres_pion_ig2(centreCasePionChoisi,couleurJoueur);
	
	/* BOUGER PION */
	
	affiche_all();
}


/* Controleur? */
void jouer(int igChoisi)
{
	COULP couleurJoueur=coul1;
	
	do{
		if(igChoisi==1)
		{
			tour_piece_ig1(couleurJoueur);
			changer_tour_joueur_ig1(&couleurJoueur);
			tour_piece_ig1(couleurJoueur);
			changer_tour_joueur_ig1(&couleurJoueur);
		}
		
		else if(igChoisi==2)
		{
			tour_piece_ig2(couleurJoueur);
			changer_tour_joueur_ig2(&couleurJoueur);
			tour_piece_ig2(couleurJoueur);
			changer_tour_joueur_ig2(&couleurJoueur);
		}
	}while(1); //personne n'a perdu
}


/*		-- Afficher cases libres pion --		*/


/* Vue */
POINT recuperer_clic_pos_plateau()
{
	POINT clicPionChoisi;
	
	do{
		clicPionChoisi=wait_clic();
	}while( (clicPionChoisi.x<0) || (clicPionChoisi.x>HAUT_FENETRE) || (clicPionChoisi.y<0) || (clicPionChoisi.y>HAUT_FENETRE) ); //LARG_FENETRE = HAUT_FENETRE
	
	return clicPionChoisi;
}


/* Vue */
POINT convertir_clic_en_centreCase(POINT clicPionChoisi)
{
	POINT centreCase;
	
	centreCase.x=0;centreCase.y=0;

	centreCase.x=(clicPionChoisi.x) / (LARG_CASE) * (LARG_CASE) + (LARG_CASE/2); //On divise puis multiplie pour avoir un multiple de LARG_CASE
	centreCase.y=(clicPionChoisi.y) / (LARG_CASE) * (LARG_CASE) + (LARG_CASE/2); //On divise puis multiplie pour avoir un multiple de LARG_CASE
	
	return centreCase;
}


/* Controleur */
NUMCASE convertir_centreCase_en_numCase(POINT centreCase)
{
	NUMCASE numcase;
		
	numcase.ligne=(centreCase.x)/(LARG_CASE);
	numcase.colonne=(centreCase.y)/(LARG_CASE);
	
	return numcase;
}


/* Controleur */
POINT convertir_numCase_en_centreCase(NUMCASE numcase)
{
	POINT centreCase;
	
	centreCase.x=(numcase.ligne*LARG_CASE)+(LARG_CASE/2);
	centreCase.y=(numcase.colonne*LARG_CASE)+(LARG_CASE/2);
	
	return centreCase;
}


/* Controleur */
int connaitre_cases_libres_pion_j1_ig1(NUMCASE numCasePionChoisi)
{
	int nbCasesLibres=0;
	
	/* Pas besoin de vérifier les bords des y (côté haut et bas du plateau) puisque le pion ne peut pas se déplacer en arrière et s'il atteint le bout il devient une dame */
	
	if(numCasePionChoisi.ligne>0)
	{
		if(plateau[(numCasePionChoisi.ligne)-1][(numCasePionChoisi.colonne)+1].coulP == aucune)
		{nbCasesLibres++;}
	}
	
	if(numCasePionChoisi.ligne<9)
	{
		if(plateau[(numCasePionChoisi.ligne)+1][(numCasePionChoisi.colonne)+1].coulP == aucune)
		{nbCasesLibres++;}
	}
	
	return nbCasesLibres;
}


/* Controleur */
int connaitre_cases_libres_pion_j2_ig1(NUMCASE numCasePionChoisi)
{
	int nbCasesLibres=0;
	
	/* Pas besoin de vérifier les bords des y (côté haut et bas du plateau) puisque le pion ne peut pas se déplacer en arrière et s'il atteint le bout il devient une dame */
	
	if(numCasePionChoisi.ligne>0)
	{
		if(plateau[(numCasePionChoisi.ligne)-1][(numCasePionChoisi.colonne)-1].coulP == aucune)
		{nbCasesLibres++;}
	}
	
	if(numCasePionChoisi.ligne<9)
	{
		if(plateau[(numCasePionChoisi.ligne)+1][(numCasePionChoisi.colonne)-1].coulP == aucune)
		{nbCasesLibres++;}
	}
	
	return nbCasesLibres;
}


/* Controleur */
int calculer_nb_cases_libres_ig1(PIECE piece,NUMCASE numCasePionChoisi)
{
	int nbCasesLibres=0;
	
	if(piece.typeP == pion)
	{
		if(piece.coulP == coul1)
		{
			nbCasesLibres+=connaitre_cases_libres_pion_j1_ig1(numCasePionChoisi);
		}
		
		else if(piece.coulP == coul2)
		{
			nbCasesLibres+=connaitre_cases_libres_pion_j2_ig1(numCasePionChoisi);
		}
	}
	
	else if(piece.typeP == dame)
	{
		/* sera fait plus tard quand on aura implémenté les dames */
	}
	
	
	if(nbCasesLibres==0)
	{printf("Pas de cases libres. Choisir un autre pion\n");} //A METTRE EN COMMENTAIRE QUAND LE JEU SERA FINI
	
	return nbCasesLibres;
}


/* Controleur */
void choisir_pion_valide(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi)
{
	COULP couleurPionChoisi;
	POINT clicPionChoisi;
	int nbCasesLibres=0;
	
	do{
		do{
			clicPionChoisi=recuperer_clic_pos_plateau();
			*centreCasePionChoisi=convertir_clic_en_centreCase(clicPionChoisi);
			*numCasePionChoisi=convertir_centreCase_en_numCase(*centreCasePionChoisi);
			couleurPionChoisi=plateau[numCasePionChoisi->ligne][numCasePionChoisi->colonne].coulP;
		}while(couleurPionChoisi!=couleurPionValide);
		
		//~ printf("numcasepionchoisi x %d numcasepionchoisi y %d\n",numCasePionChoisi->ligne,numCasePionChoisi->colonne);
		
		/* if ig1 */
		nbCasesLibres=calculer_nb_cases_libres_ig1(plateau[numCasePionChoisi->ligne][numCasePionChoisi->colonne],*numCasePionChoisi); //prend en compte si c'est pion ou dame
		
		/* FAIRE CALCUL NBCASESLIBRES POUR IG2 */
		
		printf("nbCasesLibres %d\n",nbCasesLibres); //A METTRE EN COMMENTAIRE QUAND LE JEU SERA FINI
	}while(nbCasesLibres==0);
}


/* Vue */
void afficher_cases_libres_pion_ig1(POINT centrePionChoisi,COULP couleurJoueur)
{
	POINT centreCaseLibre1,centreCaseLibre2;
	
	if(couleurJoueur==coul1)
	{
		centreCaseLibre1.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre1.y=centrePionChoisi.y+LARG_CASE;
		
		centreCaseLibre2.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre2.y=centrePionChoisi.y+LARG_CASE;
	}
	
	else if(couleurJoueur==coul2)
	{
		centreCaseLibre1.x=centrePionChoisi.x+LARG_CASE;
		centreCaseLibre1.y=centrePionChoisi.y-LARG_CASE;
		
		centreCaseLibre2.x=centrePionChoisi.x-LARG_CASE;
		centreCaseLibre2.y=centrePionChoisi.y-LARG_CASE;
	}
	
	if(centrePionChoisi.x<(HAUT_FENETRE-LARG_CASE)) //Eviter dessiner sur bord droit
	{
		draw_fill_circle(centreCaseLibre1,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
	
	if(centrePionChoisi.x>LARG_CASE) //Eviter dessiner sur bord gauche
	{
		draw_fill_circle(centreCaseLibre2,LARG_CASE/2,COULEUR_CASE_LIBRE);
	}
}


/* Vue */
void afficher_cases_libres_pion_ig2(POINT centrePionChoisi,COULP couleurJoueur)
{
	POINT caseLibrebg1,caseLibrehd1,caseLibrebg2,caseLibrehd2;
	
	if(couleurJoueur==coul1)
	{
		caseLibrebg1.x=centrePionChoisi.x+LARG_CASE/2;
		caseLibrebg1.y=centrePionChoisi.y+LARG_CASE/2;
		caseLibrehd1.x=(centrePionChoisi.x+1.5*LARG_CASE)-1;
		caseLibrehd1.y=(centrePionChoisi.y+1.5*LARG_CASE)-1;

		caseLibrehd2.x=centrePionChoisi.x+LARG_CASE/2;
		caseLibrehd2.y=centrePionChoisi.y-1.5*LARG_CASE;
		caseLibrebg2.x=(centrePionChoisi.x+1.5*LARG_CASE)-1;
		caseLibrebg2.y=(centrePionChoisi.y-LARG_CASE/2)-1;
	}
	
	else if(couleurJoueur==coul2)
	{
		caseLibrebg1.x=centrePionChoisi.x-1.5*LARG_CASE;
		caseLibrebg1.y=centrePionChoisi.y+LARG_CASE/2;
		caseLibrehd1.x=(centrePionChoisi.x-LARG_CASE/2)-1;
		caseLibrehd1.y=(centrePionChoisi.y+1.5*LARG_CASE)-1;

		caseLibrehd2.x=centrePionChoisi.x-1.5*LARG_CASE;
		caseLibrehd2.y=centrePionChoisi.y-1.5*LARG_CASE;
		caseLibrebg2.x=(centrePionChoisi.x-LARG_CASE/2)-1;
		caseLibrebg2.y=(centrePionChoisi.y-LARG_CASE/2)-1;
	}
	
	if(centrePionChoisi.y<(HAUT_FENETRE-LARG_CASE)) //Eviter dessiner sur bord haut
	{
		draw_fill_rectangle(caseLibrebg1,caseLibrehd1,COULEUR_CASE_LIBRE);
	}
	
	if(centrePionChoisi.y>LARG_CASE) //Eviter dessiner sur bord bas
	{
		draw_fill_rectangle(caseLibrebg2,caseLibrehd2,COULEUR_CASE_LIBRE);
	}
}

/*
void choisir_destination_valide_ig1(POINT centreCaseChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination)
{
	COULP couleurCaseDestination;
	POINT clicCaseDestination;
	
	do{
		clicCaseDestination=recuperer_clic_pos_plateau();
		*centreCaseDestination=convertir_clic_en_centreCase(clicCaseDestination);
		*numCaseDestination=convertir_centreCase_en_numCase(*centreCasePionChoisi);
		couleurCaseDestination=plateau[numCaseDestination->ligne][numCaseDestination->colonne].coulP;
	}while(plateau[numCaseDestination.ligne][numCaseDestination.colonne].coulp != aucune);
	
}
*/
/*		-- Afficher Ecran Titre --		*/


/* Vue */
void afficher_titre()
{
	POINT ptTitre;
	
	ptTitre.x=LARG_FENETRE/6;ptTitre.y=HAUT_FENETRE-10; // /6 pour centrer le texte
	
	aff_pol("Projet Dames IATIC3 - CORBEIL Alex / VIDAL Antoine",20,ptTitre,blanc);
}


/* Vue */
void afficher_exemple_ecran_titre_ig1(POINT ptTitreIg1)
{
	POINT ptCaseTitreJ1,ptCaseTitreJ2;
	
	ptCaseTitreJ1.x=ptTitreIg1.x;ptCaseTitreJ1.y=ptTitreIg1.y-100;
	ptCaseTitreJ2.x=ptCaseTitreJ1.x+2*LARG_CASE;ptCaseTitreJ2.y=ptCaseTitreJ1.y;
	
	afficher_case_ig1(ptCaseTitreJ1,COULEUR_CASE_JOUEURS);
	afficher_piece_triangle_haut(ptCaseTitreJ1,COULEUR_JOUEUR1);
	afficher_piece_triangle_bas(ptCaseTitreJ1,COULEUR_JOUEUR1);
	
	afficher_case_ig1(ptCaseTitreJ2,COULEUR_CASE_VIDE);
	afficher_piece_triangle_haut(ptCaseTitreJ2,COULEUR_JOUEUR2);
	afficher_piece_triangle_bas(ptCaseTitreJ2,COULEUR_JOUEUR2);
}

/* Vue */
void afficher_ecran_titre_ig1()
{
	POINT ptTitreIg1;
	
	ptTitreIg1.x=LARG_FENETRE/5;ptTitreIg1.y=HAUT_FENETRE-100;
	
	aff_pol("Interface 1",20,ptTitreIg1,blanc);
	afficher_exemple_ecran_titre_ig1(ptTitreIg1);
	affiche_all();
}


/* Vue */
void afficher_exemple_ecran_titre_ig2(POINT ptTitreIg2)
{
	POINT ptCasebgJ1,ptCasehdJ1,ptCasebgJ2,ptCasehdJ2,ptCentreCaseJ1,ptCentreCaseJ2;

	ptCasebgJ1.x=ptTitreIg2.x-35;ptCasebgJ1.y=ptTitreIg2.y-125; // 35 et 125 pour "centrer"
	ptCasehdJ1.x=ptCasebgJ1.x+LARG_CASE;ptCasehdJ1.y=ptCasebgJ1.y+LARG_CASE;
	
	ptCasebgJ2.x=ptCasebgJ1.x+2*LARG_CASE;ptCasebgJ2.y=ptCasebgJ1.y;
	ptCasehdJ2.x=ptCasebgJ2.x+LARG_CASE;ptCasehdJ2.y=ptCasebgJ2.y+LARG_CASE;
	
	ptCentreCaseJ1.x=ptCasebgJ1.x+LARG_CASE/2;ptCentreCaseJ1.y=ptCasebgJ1.y+LARG_CASE/2;
	ptCentreCaseJ2.x=ptCasebgJ2.x+LARG_CASE/2;ptCentreCaseJ2.y=ptCasebgJ2.y+LARG_CASE/2;


	afficher_case_ig2(ptCasebgJ1,ptCasehdJ1,COULEUR_CASE_JOUEURS);
	afficher_piece_rond(ptCentreCaseJ1,COULEUR_JOUEUR1);
	
	afficher_case_ig2(ptCasebgJ2,ptCasehdJ2,COULEUR_CASE_VIDE);
	afficher_piece_rond(ptCentreCaseJ2,COULEUR_JOUEUR2);
}


/* Vue */
void afficher_ecran_titre_ig2()
{
	POINT ptTitreIg2;
	
	ptTitreIg2.x=LARG_FENETRE/1.5;ptTitreIg2.y=HAUT_FENETRE-100;
			
	aff_pol("Interface 2",20,ptTitreIg2,blanc);
	afficher_exemple_ecran_titre_ig2(ptTitreIg2);
	affiche_all();
}


/* Vue */
POINT recuperer_clic_choix_ig()
{
	POINT clicChoixIg={0,0};
	
	do{
		clicChoixIg=wait_clic();
	}while( (clicChoixIg.y>HAUT_FENETRE-50) ); //A changer pour que le clic soit bien dans le cadre de l'interface
	
	return clicChoixIg;
}


/* Controleur */
int choisir_ig(POINT clicChoixIg)
{
	int ig=0;
	
	if(clicChoixIg.x<LARG_FENETRE/2)
	{ig=1;}
	
	else if(clicChoixIg.x>LARG_FENETRE/2)
	{ig=2;}
	
	return ig;
}


/* Vue */
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


/* Vue */
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


/* Vue */
POINT recuperer_clic_redemander_partie(POINT ptOui,POINT ptNon)
{
	POINT clicRedemanderPartie;
	
	do{
		clicRedemanderPartie=wait_clic();
	}while( ((clicRedemanderPartie.x<ptOui.x) && (clicRedemanderPartie.x>ptOui.x+50) && (clicRedemanderPartie.y<ptOui.y) && (clicRedemanderPartie.y>ptOui.y+50)) ||
			((clicRedemanderPartie.x<ptNon.x) && (clicRedemanderPartie.x>ptNon.x+50) && (clicRedemanderPartie.y<ptNon.y) && (clicRedemanderPartie.y>ptNon.y+50)) );
	
	return clicRedemanderPartie;
}


/* Controleur */
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


/* Vue */
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


int main(void)
{
	BOOL rejouer=true;
	int igChoisi=0;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do{
		initialiser_plateau();
		afficher_ecran_titre(&igChoisi);
		afficher_ecran_jeu_selon_ig(igChoisi);
		jouer(igChoisi);
		
		
		
		/* fin de partie */
		
		/* afficher_gagnant();*/
		rejouer=redemander_partie();
		
	}while(rejouer==true);
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}
