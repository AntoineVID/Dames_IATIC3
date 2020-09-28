/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#ifndef MAIN_H
#define MAIN_H

#include "graphics.h"

#define LARG_FENETRE 800
#define HAUT_FENETRE 600

#define LARG_CASE HAUT_FENETRE/10
#define LONGUEUR_PIECE (2.0/3.0)*LARG_CASE
#define NB_CASES 10

#define COULEUR_JOUEUR1 blanc
#define COULEUR_JOUEUR2 gris
#define COULEUR_DAME rouge
#define COULEUR_CASE_LIBRE jaune



typedef enum TYPEP{
	vide, pion, dame
} TYPEP; 

typedef enum COULP{
	aucune, coul1, coul2
} COULP;

typedef struct PIECE{
	TYPEP typeP;
	COULP coulP;
} PIECE;

typedef struct NUMCASE{
	int ligne;
	int colonne;
} NUMCASE;



#endif