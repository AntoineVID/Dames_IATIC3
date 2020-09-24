/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "main_bis.h"


void afficher_piece_triangle_haut(POINT ptLosCentre);
void afficher_piece_triangle_bas(POINT ptLosCentre);
void afficher_piece_dame_triangle_haut(POINT ptLosCentre);
void afficher_piece_dame_triangle_bas(POINT ptLosCentre);
void afficher_piece_ig1(POINT ptLosCentre);
void afficher_plateau_ig1();


void afficher_piece_rond(POINT ptRondCentre);
void afficher_piece_rond_dame(POINT ptRondCentre);
void afficher_piece_ig2(POINT ptRondCentre);
void afficher_plateau_ig2();

void afficher_interface();
void efface_tour();


/* Vue */
void afficher_piece_triangle_haut(POINT ptLosCentre)
{
	POINT ptLosHaut,ptLosDroit,ptLosGauche;
	
	ptLosHaut.x=ptLosCentre.x;
	ptLosHaut.y=ptLosCentre.y+0.5*LONGUEUR_PIECE;
	
	ptLosDroit.x=ptLosCentre.x-0.5*LONGUEUR_PIECE;
	ptLosDroit.y=ptLosCentre.y;
	
	ptLosGauche.x=ptLosCentre.x+0.5*LONGUEUR_PIECE;
	ptLosGauche.y=ptLosCentre.y;
	
	draw_fill_triangle(ptLosHaut,ptLosDroit,ptLosGauche,blanc);
}


/* Vue */
void afficher_piece_triangle_bas(POINT ptLosCentre)
{
	POINT ptLosBas,ptLosDroit,ptLosGauche;
	
	ptLosBas.x=ptLosCentre.x;
	ptLosBas.y=ptLosCentre.y-0.5*LONGUEUR_PIECE;
	
	ptLosDroit.x=ptLosCentre.x-0.5*LONGUEUR_PIECE;
	ptLosDroit.y=ptLosCentre.y;
	
	ptLosGauche.x=ptLosCentre.x+0.5*LONGUEUR_PIECE;
	ptLosGauche.y=ptLosCentre.y;
	
	draw_fill_triangle(ptLosBas,ptLosDroit,ptLosGauche,blanc);
}


/* Vue */
void afficher_piece_dame_triangle_haut(POINT ptLosCentre)
{
	POINT ptLosDameHaut,ptLosDameDroit,ptLosDameGauche;
	
	ptLosDameHaut.x=ptLosCentre.x;
	ptLosDameHaut.y=ptLosCentre.y+0.4*LONGUEUR_PIECE;
	
	ptLosDameDroit.x=ptLosCentre.x-0.8*(LONGUEUR_PIECE/2);
	ptLosDameDroit.y=ptLosCentre.y;
	
	ptLosDameGauche.x=ptLosCentre.x+0.8*(LONGUEUR_PIECE/2);
	ptLosDameGauche.y=ptLosCentre.y;
	
	draw_fill_triangle(ptLosDameHaut,ptLosDameDroit,ptLosDameGauche,rouge);
}


/* Vue */
void afficher_piece_dame_triangle_bas(POINT ptLosCentre)
{
	POINT ptLosDameBas,ptLosDameDroit,ptLosDameGauche;
	
	ptLosDameBas.x=ptLosCentre.x;
	ptLosDameBas.y=ptLosCentre.y-0.4*LONGUEUR_PIECE;
	
	ptLosDameDroit.x=ptLosCentre.x-0.8*(LONGUEUR_PIECE/2);
	ptLosDameDroit.y=ptLosCentre.y;
	
	ptLosDameGauche.x=ptLosCentre.x+0.8*(LONGUEUR_PIECE/2);
	ptLosDameGauche.y=ptLosCentre.y;
	
	draw_fill_triangle(ptLosDameBas,ptLosDameDroit,ptLosDameGauche,rouge);
}


/* Vue */
void afficher_piece_ig1(POINT ptLosCentre)
{
	/* if Piece = normal */
	
	afficher_piece_triangle_haut(ptLosCentre);
	afficher_piece_triangle_bas(ptLosCentre);
	
	/* else if Piece = dame */
	
	afficher_piece_dame_triangle_haut(ptLosCentre);
	afficher_piece_dame_triangle_bas(ptLosCentre);
}


/* Vue */
void afficher_plateau_ig1()
{
	int i=0,j=0;
	POINT ptCentreCase;
	ptCentreCase.x=LARG_CASE/2;ptCentreCase.y=LARG_CASE/2;
	
	for(i=0;i<NB_CASES;i++)
	{
		for(j=0;j<NB_CASES;j++)
		{		
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				draw_fill_circle(ptCentreCase,LARG_CASE/2,burlywood);
			}
			
			else
			{
				draw_fill_circle(ptCentreCase,LARG_CASE/2,saddlebrown);
			}
		
			ptCentreCase.x+=LARG_CASE;
		}
		
		ptCentreCase.x=LARG_CASE/2;
		ptCentreCase.y+=LARG_CASE;
	}
	
}

/* Vue */
void afficher_piece_rond(POINT ptRondCentre)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/2,blanc);
}


/* Vue */
void afficher_piece_rond_dame(POINT ptRondCentre)
{
	draw_fill_circle(ptRondCentre,LONGUEUR_PIECE/2.5,rouge);
}


/* Vue */
void afficher_piece_ig2(POINT ptRondCentre)
{
	
	/* if Piece = normal */
	
	afficher_piece_rond(ptRondCentre);
	
	/* if Piece = dame */
	
	afficher_piece_rond_dame(ptRondCentre);
}


/* Vue */
void afficher_plateau_ig2()
{
	int i=0,j=0;
	POINT ptbgCase,pthdCase;
	ptbgCase.x=0;ptbgCase.y=0;
	pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y=ptbgCase.y+LARG_CASE;

	for(i=0;i<NB_CASES;i++)
	{
		for(j=0;j<NB_CASES;j++)
		{		
			if ( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{draw_fill_rectangle(ptbgCase,pthdCase,burlywood);}
			
			else
			{draw_fill_rectangle(ptbgCase,pthdCase,saddlebrown);}
		
			ptbgCase.x+=LARG_CASE;
			pthdCase.x+=LARG_CASE;
		}
		
		ptbgCase.x=0;ptbgCase.y+=LARG_CASE;
		pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y+=LARG_CASE;
	}
}


/* Vue */
void afficher_interface()
{
	POINT ptTour,ptNbrP1,ptNbrP2;
	
	ptTour.x=HAUT_FENETRE+20;ptTour.y=HAUT_FENETRE-20;
	ptNbrP1.x=HAUT_FENETRE+5;ptNbrP1.y=0.66*HAUT_FENETRE;
	ptNbrP2.x=HAUT_FENETRE+5;ptNbrP2.y=0.33*HAUT_FENETRE;
	
	aff_pol("A qui de jouer ?",20,ptTour,blanc);
	aff_pol("Nombre de pions 1",20,ptNbrP1,blanc);
	aff_pol("Nombre de pions 2",20,ptNbrP2,blanc);
}


/* Vue*/
void efface_tour()
{
	POINT ptbgIndiqTour,pthdIndiqTour;
	
	ptbgIndiqTour.x=HAUT_FENETRE+1;
	ptbgIndiqTour.y=0.8*HAUT_FENETRE;
	pthdIndiqTour.x=LARG_FENETRE;
	pthdIndiqTour.y=0.9*HAUT_FENETRE;
	
	draw_fill_rectangle(ptbgIndiqTour,pthdIndiqTour,noir);
}



int main(void)
{
	POINT ptCentrePiece,ptIndiqTour;

	ptCentrePiece.x=LARG_CASE+LARG_CASE/2;ptCentrePiece.y=LARG_CASE/2;
	
	ptIndiqTour.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptIndiqTour.y=0.85*HAUT_FENETRE;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	afficher_plateau_ig1();
	afficher_piece_ig1(ptCentrePiece);
	//~ afficher_piece_ig2(ptCentrePiece);
	
	afficher_interface();
	afficher_piece_ig1(ptIndiqTour);
	//~ efface_tour();
	
	affiche_all();
	wait_escape();
	return 0;
}
