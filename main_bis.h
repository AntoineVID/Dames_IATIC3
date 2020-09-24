#ifndef MAIN_H
#define MAIN_H

#define LONGUEUR_PIECE 40

typedef enum{
	VIDE,PION,DAME
}TYPEP;

typedef enum{
	NOIR,BLANC
}COULP;

typedef struct{
	TYPEP typeP;
	COULP coulP;
}PIECE;


void afficher_piece_ig1(POINT sommetTri);
void afficher_pion_triangle_haut(POINT ptSommetTri);
void afficher_pion_triangle_bas(POINT ptSommetTri);
void affichier_dame_triangle_haut(POINT ptSommetTri);
void affichier_dame_triangle_bas(POINT ptSommetTri);


void afficher_piece_ig2(POINT ptCentrePion);
void afficher_pion_rond(POINT ptCentrePion);
void afficher_pion_rond(POINT ptCentrePion);




#endif
