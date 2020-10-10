/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#ifndef JOUER_H
#define JOUER_H

#include "graphics.h"

#define LARG_FENETRE 800
#define HAUT_FENETRE 600

#define LARG_CASE (HAUT_FENETRE/10)
#define LONGUEUR_PIECE ((2.0/3.0)*LARG_CASE)

#define COULEUR_JOUEUR1 blanc
#define COULEUR_JOUEUR2 gris
#define COULEUR_DAME rouge
#define COULEUR_CASE_LIBRE jaune
#define COULEUR_CASE_JOUEURS saddlebrown
#define COULEUR_CASE_VIDE burlywood

typedef enum CHOIXIG{
	ig1 = 1, ig2 = 2
} CHOIXIG;

typedef enum TYPEDEFAITE{
	peutJouer, aucunPion, pionsBloques
} TYPEDEFAITE;

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


/*
 * ||        ||
 * \/ MODÈLE \/
 */

/* Manipulations tableau logique */
void initialiser_tableau();
void effectuer_attaque_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, int *nbrePionJoueur);
void effectuer_deplacement_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee);

/* Déplacement, attaque et dame */
int donner_position_cases_libres_attaque(NUMCASE depart);
int donner_position_cases_libres_deplacement(NUMCASE depart);
BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination);
BOOL est_coup_valide_deplacement(NUMCASE origine, NUMCASE destination);
void transformer_pion_en_dame(NUMCASE pion);

/* Test blocage */
BOOL est_bloque(NUMCASE depart);
BOOL est_joueur_bloque(COULP couleurJoueur, int nbrePionJoueur);
TYPEDEFAITE tester_fin_jeu(COULP couleurJoueur, int nbrePionJoueur);

/*
 * /\ MODÈLE /\
 * ||        ||
 */

/*
 * ||     ||
 * \/ VUE \/
 */

COULEUR convertir_joueur_couleur(COULP couleurJoueur);

/* Afficher pieces / plateau */
void afficher_pion_ig1(POINT losangeCentre,COULEUR couleur);
void afficher_dame_ig1(POINT losangeCentre);
void afficher_case_ig1(POINT centre,COULEUR couleur);

void afficher_pion_ig2(POINT centre,COULEUR couleur);
void afficher_dame_ig2(POINT centre);
void afficher_case_ig2(POINT centre,COULEUR couleur);

void afficher_piece(POINT centre, CHOIXIG igChoisi);
void afficher_case(POINT centre, COULEUR couleur, CHOIXIG igChoisi);
void afficher_plateau(CHOIXIG igChoisi);

/* Afficher interface */
void afficher_interface(CHOIXIG igChoisi, COULEUR couleur);
void effacer_tour();

/* Choisir pion valide */
POINT recuperer_coords_clic_plateau();
void modifier_couleur_cases_libres_ig1(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleurCase);
void modifier_couleur_cases_libres_ig2(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleurCase);
void modifier_couleur_cases_libres(POINT origine, int casesLibresDep, int casesLibresAtk, COULEUR couleur, CHOIXIG igChoisi);

/* Choisir destination */
void afficher_texte_choix_destination();
void effacer_texte_choix_destination();

/* Retirer pion pris */
void enlever_pion_qui_subit_attaque(POINT caseOrig, POINT caseDest, CHOIXIG igChoisi);

/* Choix attaque multiple */
void afficher_choix_multi_attaque();
void effacer_choix_multi_attaque();
BOOL est_acceptee_multi_attaque();

/* Ecran titre */
void afficher_textes_accueil();
void afficher_exemple_ecran_titre_ig1();
void afficher_exemple_ecran_titre_ig2();
void afficher_ecran_titre();

/* Fin Partie */
void afficher_gagnant(COULP couleurJoueur, TYPEDEFAITE finJeu);
void afficher_texte_redemander_partie(POINT ptOui,POINT ptNon);
BOOL redemander_partie(COULP couleurJoueur, TYPEDEFAITE finJeu);

/*
 * /\ VUE /\
 * ||     ||
 */

/*
 * ||            ||
 * \/ CONTRÔLEUR \/
 */

NUMCASE convertir_clic_en_numCase(POINT clic, CHOIXIG igChoisi);
POINT convertir_numCase_en_centreCase(NUMCASE numcase, CHOIXIG igChoisi);
NUMCASE convertir_centreCase_en_numCase(POINT centre, CHOIXIG igChoisi);
BOOL recuperer_clic_oui_non(POINT oui1, POINT oui2, POINT non1, POINT non2);
void trouver_cases_libres(NUMCASE numCaseOrig, int *casesLibresDep, int *casesLibresAtk, BOOL est_multiAtk, CHOIXIG igChoisi);

/*
 * /\ CONTRÔLEUR /\
 * ||            ||
 */
 
#endif // JOUER_H

