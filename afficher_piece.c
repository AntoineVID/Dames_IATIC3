#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "main_bis.h"


/* Vue */
void afficher_pion_triangle_haut(POINT ptSommetTriHaut)
{
	POINT ptDroitPion,ptGauchePion;
	
	ptDroitPion.x=ptSommetTriHaut.x-0.5*LONGUEUR_PIECE;
	ptDroitPion.y=ptSommetTriHaut.y-0.5*LONGUEUR_PIECE;
	
	ptGauchePion.x=ptSommetTriHaut.x+0.5*LONGUEUR_PIECE;
	ptGauchePion.y=ptDroitPion.y;
	
	draw_fill_triangle(ptSommetTriHaut,ptDroitPion,ptGauchePion,blanc);
}


/* Vue */
void afficher_pion_triangle_bas(POINT ptSommetTriBas)
{
	POINT ptDroitPion,ptGauchePion;
	
	ptDroitPion.x=ptSommetTriBas.x-0.5*LONGUEUR_PIECE;
	ptDroitPion.y=ptSommetTriBas.y+0.5*LONGUEUR_PIECE;
	
	ptGauchePion.x=ptSommetTriBas.x+0.5*LONGUEUR_PIECE;
	ptGauchePion.y=ptDroitPion.y;
	
	draw_fill_triangle(ptSommetTriBas,ptDroitPion,ptGauchePion,blanc);
}


/* Vue */
void afficher_dame_triangle_haut(POINT ptSommetTriHaut)
{
	POINT ptSommetDame,ptDroitDame,ptGaucheDame;
	
	ptSommetDame.x=ptSommetTriHaut.x;
	ptSommetDame.y=ptSommetTriHaut.y-0.2*(LONGUEUR_PIECE/2);
	
	ptDroitDame.x=ptSommetTriHaut.x-0.8*(LONGUEUR_PIECE/2);
	ptDroitDame.y=ptSommetTriHaut.y-0.5*LONGUEUR_PIECE;
	
	ptGaucheDame.x=ptSommetTriHaut.x+0.8*(LONGUEUR_PIECE/2);
	ptGaucheDame.y=ptDroitDame.y;
	
	draw_fill_triangle(ptSommetDame,ptDroitDame,ptGaucheDame,rouge);
}


/* Vue */
void afficher_dame_triangle_bas(POINT ptSommetTriBas)
{
	POINT ptSommetDame,ptDroitDame,ptGaucheDame;
	
	ptSommetDame.x=ptSommetTriBas.x;
	ptSommetDame.y=ptSommetTriBas.y+0.2*(LONGUEUR_PIECE/2);
	
	ptDroitDame.x=ptSommetTriBas.x-0.8*(LONGUEUR_PIECE/2);
	ptDroitDame.y=ptSommetTriBas.y+0.5*LONGUEUR_PIECE;
	
	ptGaucheDame.x=ptSommetTriBas.x+0.8*(LONGUEUR_PIECE/2);
	ptGaucheDame.y=ptDroitDame.y;

	draw_fill_triangle(ptSommetDame,ptDroitDame,ptGaucheDame,rouge);
}


/* Vue */
void afficher_piece_ig1(POINT ptSommetTriHaut)
{
	POINT ptSommetTriBas;
	
	ptSommetTriBas.x=ptSommetTriHaut.x;
	ptSommetTriBas.y=ptSommetTriHaut.y-LONGUEUR_PIECE;
	
	/* if pion = normal */
	
	afficher_pion_triangle_haut(ptSommetTriHaut);
	afficher_pion_triangle_bas(ptSommetTriBas);
	
	/* else if pion = dame */
	
	afficher_dame_triangle_haut(ptSommetTriHaut);
	afficher_dame_triangle_bas(ptSommetTriBas);
}


/* Vue */

void afficher_pion_rond(POINT ptCentrePion)
{
	draw_fill_circle(ptCentrePion,LONGUEUR_PIECE/2,blanc);
}

/* Vue */
void afficher_pion_rond_dame(POINT ptCentrePion)
{
	draw_fill_circle(ptCentrePion,LONGUEUR_PIECE/2.5,rouge);
}

/* Vue */
void afficher_piece_ig2(POINT ptCentrePion)
{
	
	/* if pion = normal */
	
	afficher_pion_rond(ptCentrePion);
	
	/* if pion = dame */
	
	afficher_pion_rond_dame(ptCentrePion);
}


int main(void)
{
	POINT ptSommetTriHaut,ptCentrePion;
	
	ptSommetTriHaut.x=100;ptSommetTriHaut.y=200;
	ptCentrePion.x=400;ptCentrePion.y=300;
	
	init_graphics(800,600);
	affiche_auto_off();
	
	afficher_piece_ig1(ptSommetTriHaut);
	afficher_piece_ig2(ptCentrePion);
	
	affiche_all();
	wait_escape();
	return 0;
}
