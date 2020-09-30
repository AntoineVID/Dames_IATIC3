/* CORBEIL Alex - VIDAL Antoine IATIC3 */
#include "main.h"

PIECE plateau[10][10];

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
			return 1;
		else
			return 0;
	}
	else
		return 0;
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
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int donner_position_cases_libres_deplacement(NUMCASE depart)
{
	int cases_libres = 0;
	NUMCASE arrivee;

	if(depart.ligne < 9)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		|| ( plateau[depart.colonne][depart.ligne].coulP == coul1 ))
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
		|| ( plateau[depart.colonne][depart.ligne].coulP == coul2 ))
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

int donner_position_cases_libres_attaque(NUMCASE depart, COULP couleurJoueur)
{
	int cases_libres = 0;
	NUMCASE arrivee;
	if(depart.ligne < 8)
	{
		if( ( plateau[depart.colonne][depart.ligne].typeP == dame )
		|| ( plateau[depart.colonne][depart.ligne].coulP == coul1 ))
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
		|| ( plateau[depart.colonne][depart.ligne].coulP == coul2 ))
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

BOOL est_bloque(NUMCASE depart, COULP couleurJoueur)
{
	if( !donner_position_cases_libres_deplacement(depart) && !donner_position_cases_libres_attaque(depart, couleurJoueur))
			return 1;
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
					return 1;
			}
		}
	}
	return 0;
}

int tester_fin_jeu(COULP couleurJoueur, int nbrePionJoueur)
{
	if(est_joueur_bloque(couleurJoueur, nbrePionJoueur))
	{
		return 1;
	}
	if(nbrePionJoueur == 0)
	{
		return 2;
	}
	return 0;
}

void changer_etat_case_tableau_logique(NUMCASE numCase, TYPEP type, COULP coul)
{
	plateau[numCase.colonne][numCase.ligne].typeP = type;
	plateau[numCase.colonne][numCase.ligne].coulP = coul;
}

void effectuer_deplacement_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, COULP couleurJoueur)
{
	changer_etat_case_tableau_logique(arrivee, plateau[depart.colonne][depart.ligne].typeP, couleurJoueur);
	changer_etat_case_tableau_logique(depart, vide, aucune);
	transformer_pion_en_dame(arrivee, couleurJoueur);
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

void jouer_dans_terminal(COULP couleurJoueur, int *nbrePionJoueur)
{
	char choix;
	BOOL multiAttaque = 0;
	NUMCASE depart, arrivee;
	do
	{
		afficher_plateau_dans_terminal();
		printf("Le joueur %d joue. Coordonnées du pion à déplacer :\n", couleurJoueur);
		scanf("%d %d", &depart.colonne, &depart.ligne);
		printf("\n");
		if(plateau[depart.colonne][depart.ligne].coulP != aucune && est_bloque(depart, couleurJoueur))
		{
			printf("Pion bloqué. Veuillez en choisir un autre.\n");
		}
		else if( plateau[depart.colonne][depart.ligne].coulP  == couleurJoueur)
		{
			do
			{
				afficher_plateau_dans_terminal();
				printf("Vous pouvez jouer!\n");
				printf("Le joueur %d joue. Coordonnées de destination :\n", couleurJoueur);
				scanf("%d %d", &arrivee.colonne, &arrivee.ligne);
				if( !multiAttaque && est_coup_valide_deplacement(depart, arrivee))
				{
					effectuer_deplacement_dans_tableau_logique(depart, arrivee, couleurJoueur);					
					return;
				}
				if(est_coup_valide_attaque(depart, arrivee, couleurJoueur))
				{
					effectuer_attaque_dans_tableau_logique(depart, arrivee, couleurJoueur, nbrePionJoueur);
					if(donner_position_cases_libres_attaque(arrivee, couleurJoueur))
					{
						printf("Voulez-vous continuer le tour en attaquant de nouveau ? (o/n)\n");
						scanf(" %c", &choix);
						if(choix == 'n')
						{
							printf("OK, tour terminé !\n");
							return;
						}
						else
						{
							depart.ligne = arrivee.ligne;
							depart.colonne = arrivee.colonne;
							printf("OK, vous allez pouvoir attaque de nouveau !\n");
							multiAttaque = 1;
						}
					}
					else
						return;
				}
				else
				{
					printf("Coup non valide.\n Recommencez.\n");
					if( !multiAttaque)
						break;
				}
			}while(1);
		}
		else
			printf("Ce n'est pas un pion de votre couleur !\n Recommencez le tour.\n");
	}while(1);
}

BOOL est_fin_jeu_dans_terminal(COULP couleurJoueur, int nbrePionJoueur)
{
	if(tester_fin_jeu(couleurJoueur, nbrePionJoueur) == 1)
	{
		printf("Le joueur %d est bloqué. Le joueur %d a gagné !\n", couleurJoueur, (couleurJoueur == coul1) ? coul2 : coul1);
		return 1;
	}
	else if(tester_fin_jeu(couleurJoueur, nbrePionJoueur) == 2)
	{
		printf("Le joueur %d n'a plus de pion. Le joueur %d a gagné !\n", couleurJoueur, (couleurJoueur == coul1) ? coul2 : coul1);
		return 1;
	}
	return 0;
}

/*
 * Fin du test dans le terminal
 */

int main()
{
	int nbrePionJ1 = 20, nbrePionJ2 = 20, nbrePionJoueur;
	COULP couleurJoueur = coul1;
	initialiser_plateau();
	do{
		nbrePionJoueur = (couleurJoueur == coul1) ? nbrePionJ1 : nbrePionJ2;
		jouer_dans_terminal(couleurJoueur, &nbrePionJoueur);
		couleurJoueur = (couleurJoueur == coul1) ? coul2 : coul1;
	}while( !est_fin_jeu_dans_terminal(couleurJoueur, nbrePionJoueur));
	return(0);
}