/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#include "main.h"
#include "graphics.h"
#include <stdio.h>

void initialiser_plateau();
BOOL est_coup_valide_deplacement(NUMCASE origine, NUMCASE destination);
BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination, COULP couleurJoueur);


PIECE plateau[10][10];

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

BOOL est_coup_valide_deplacement(NUMCASE origine, NUMCASE destination)
{
	PIECE piece = plateau[origine.ligne][origine.colonne];
	int deltaLig = destination.ligne - origine.ligne;
	int deltaCol = destination.colonne - origine.colonne;

	if(plateau[destination.ligne][destination.colonne].coulP == aucune)
	{
		if( ( deltaLig == 1 && deltaCol == 1 && (piece.typeP == dame || piece.coulP == coul1) )
		||
		( deltaLig == -1 && deltaCol == 1 && (piece.typeP == dame || piece.coulP == coul1) )
		||
		( deltaLig == 1 && deltaCol == -1 && (piece.typeP == dame || piece.coulP == coul2) )
		||
		( deltaLig == -1 && deltaCol == -1 && (piece.typeP == dame || piece.coulP == coul2) ))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination, COULP couleurJoueur)
{
	PIECE piece = plateau[origine.ligne][origine.colonne];
	int deltaLig = destination.ligne - origine.ligne;
	int deltaCol = destination.colonne - origine.colonne;
	COULP couleurEnnemi = (couleurJoueur == coul1) ? coul2 : coul1;
	
	if(plateau[destination.ligne][destination.colonne].coulP == aucune)
	{
		if( ( deltaLig == 2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul1) && plateau[destination.ligne - 1][destination.colonne - 1].coulP == couleurEnnemi )
		||
		( deltaLig == -2 && deltaCol == 2 && (piece.typeP == dame || piece.coulP == coul1) && plateau[destination.ligne + 1][destination.colonne - 1].coulP == couleurEnnemi )
		||
		( deltaLig == 2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul2) && plateau[destination.ligne - 1][destination.colonne + 1].coulP == couleurEnnemi )
		||
		( deltaLig == -2 && deltaCol == -2 && (piece.typeP == dame || piece.coulP == coul2) && plateau[destination.ligne + 1][destination.colonne + 1].coulP == couleurEnnemi ))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

void transformer_pion_en_dame(int coordX, int coordY, COULP couleurJoueur)
{
	if(plateau[coordX][coordY].typeP != dame)
	{
		if( ( couleurJoueur == coul1 && coordY == 9 )
		||
		( coordY == 0 ))
		{
			plateau[coordX][coordY].typeP = dame;
		}
	}
}

/*
 * Pour tester dans le terminal
 */

void afficher_etat_case_dans_terminal(int x, int y)
{
	if(plateau[x][y].coulP == aucune)
	{
		printf(" ");
	}
	else if(plateau[x][y].typeP == pion)
	{
		if(plateau[x][y].coulP == coul1)
			printf("a");
		else
			printf("b");
	}
	else
	{
		if(plateau[x][y].coulP == coul1)
			printf("A");
		else
			printf("B");
	}

}

void afficher_plateau_dans_terminal()
{
	int i, j;

	printf("   0 1 2 3 4 5 6 7 8 9\n");
	for(j = 9; j >= 0; j--)
	{
		printf("%d |", j);
		for(i = 0; i < 10; i++)
		{
			afficher_etat_case_dans_terminal(i, j);
			printf("|");
		}
		printf(" %d\n", j);
	}
	printf("   0 1 2 3 4 5 6 7 8 9\n");
}

void jouer_dans_terminal(COULP couleurJoueur)
{
	NUMCASE clic1, clic2;
	do
	{
		printf("Le joueur %d joue. Coordonnées du pion à déplacer :\n", couleurJoueur);
		scanf("%d %d", &clic1.ligne, &clic1.colonne);
		printf("La case %d %d est : ", clic1.ligne, clic1.colonne);
		afficher_etat_case_dans_terminal(clic1.ligne, clic1.colonne);
		printf("\n");
		if( plateau[clic1.ligne][clic1.colonne].coulP  == couleurJoueur)
		{
			printf("Vous pouvez jouer!\n");
			printf("Le joueur %d joue. Coordonnées de destination :\n", couleurJoueur);
			scanf("%d %d", &clic2.ligne, &clic2.colonne);
			if(est_coup_valide_deplacement(clic1, clic2))
			{
				plateau[clic1.ligne][clic1.colonne].coulP = aucune;
				plateau[clic2.ligne][clic2.colonne].typeP = plateau[clic1.ligne][clic1.colonne].typeP;
				plateau[clic2.ligne][clic2.colonne].coulP = couleurJoueur;
				transformer_pion_en_dame(clic2.ligne, clic2.colonne, couleurJoueur);
				break;
			}
			if(est_coup_valide_attaque(clic1, clic2, couleurJoueur))
			{
				plateau[clic1.ligne][clic1.colonne].coulP = aucune;
				plateau[(clic1.ligne + clic2.ligne) / 2][(clic1.colonne + clic2.colonne) / 2].coulP = aucune;
				plateau[clic2.ligne][clic2.colonne].typeP = plateau[clic1.ligne][clic1.colonne].typeP;
				plateau[clic2.ligne][clic2.colonne].coulP = couleurJoueur;
				transformer_pion_en_dame(clic2.ligne, clic2.colonne, couleurJoueur);
				break;
			}
			else
			{
				printf("Coup non valide.\n Recommencez le tour.\n");
			}
		}
		else
		{
			printf("Ce n'est pas un pion de votre couleur !\n Recommencez le tour.\n");
		}
	}while(1);
}

/*
 * Fin du test dans le terminal
 */

int main()
{
	COULP couleurJoueur = coul1;
	//init_graphics(LARG_FENETRE, HAUT_FENETRE);
	//affiche_auto_off();	
	//wait_escape();
	initialiser_plateau();
	while(1)
	{
		afficher_plateau_dans_terminal();
		jouer_dans_terminal(couleurJoueur);
		couleurJoueur = (couleurJoueur == coul1) ? coul2 : coul1;
	}
	return(0);
}
