/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#ifndef JOUER_H
#define JOUER_H

#include "graphics.h"

#define LARG_FENETRE 800
#define HAUT_FENETRE 600

#define LARG_CASE HAUT_FENETRE/10
#define LONGUEUR_PIECE (2.0/3.0)*LARG_CASE

#define COULEUR_JOUEUR1 blanc
#define COULEUR_JOUEUR2 gris
#define COULEUR_DAME rouge
#define COULEUR_CASE_LIBRE jaune
#define COULEUR_CASE_JOUEURS saddlebrown
#define COULEUR_CASE_VIDE burlywood


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

/* Manipulation du tableau logique */

void changer_etat_case_tableau_logique(NUMCASE numCase, TYPEP type, COULP coul);

void effectuer_attaque_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, COULP couleurJoueur, int *nbrePionJoueur);

void effectuer_deplacement_dans_tableau_logique(NUMCASE depart, NUMCASE arrivee, COULP couleurJoueur);

void initialiser_plateau();

/* Vérification des possibilités d'attaques et de déplacements */

int donner_position_cases_libres_attaque(NUMCASE depart, COULP couleurJoueur);

int donner_position_cases_libres_deplacement(NUMCASE depart);

BOOL est_coup_valide_attaque(NUMCASE origine, NUMCASE destination, COULP couleurJoueur);

BOOL est_coup_valide_deplacement(NUMCASE origine, NUMCASE destination);

/* Vérification de possibilité de jeu et fin de partie */

BOOL est_bloque(NUMCASE depart, COULP couleurJoueur);

BOOL est_joueur_bloque(COULP couleurJoueur, int nbrePionJoueur);

int tester_fin_jeu(COULP couleurJoueur, int nbrePionJoueur);

void transformer_pion_en_dame(NUMCASE pion, COULP couleurJoueur);

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

//Ig1
void afficher_piece_triangle_haut(POINT ptLosangeCentre,COULEUR couleur);
void afficher_piece_triangle_bas(POINT ptLosangeCentre,COULEUR couleur);
void afficher_piece_dame_triangle_haut(POINT ptLosangeCentre);
void afficher_piece_dame_triangle_bas(POINT ptLosangeCentre);
void afficher_piece_ig1(POINT ptLosangeCentre,int ligne,int colonne);
void afficher_case_ig1(POINT ptCentreCase,COULEUR couleur);
void afficher_plateau_ig1();

//Ig2
void afficher_piece_rond(POINT ptRondCentre,COULEUR couleur);
void afficher_piece_rond_dame(POINT ptRondCentre);
void afficher_piece_ig2(POINT ptRondCentre,int ligne,int colonne);
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

/* Choisir pion valide */
POINT recuperer_clic_pos_plateau();
POINT convertir_clic_en_centreCase(POINT clicGauche);
void afficher_cases_libres_ig1(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);
void effacer_cases_libres_choisies_ig1(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);
void afficher_cases_libres_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);
void effacer_cases_libres_choisies_ig2(POINT centrePionChoisi,int positionCasesLibres,int positionCasesLibresAttaque);

/* Choisir destination */
void afficher_texte_choix_destination();
void effacer_texte_choix_destination();
void choisir_destination_ig1(POINT centreCasePionChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination);
void choisir_destination_ig2(POINT centreCasePionChoisi,POINT *centreCaseDestination,NUMCASE *numCaseDestination);

/* Bouger Pion */
void effacer_piece_case_orig_ig1(POINT centreCasePionChoisi);
void enlever_pion_qui_subit_attaque_ig1(POINT centreCasePionChoisi, POINT centreCaseDestination);
void effacer_piece_case_orig_ig2(POINT centreCasePionChoisi);
void enlever_pion_qui_subit_attaque_ig2(POINT centreCasePionChoisi, POINT centreCaseDestination);

/* Choix attaque multiple */

void afficher_choix_multi_attaque(POINT ptMultiAtk1, POINT ptMultiAtk2, POINT ptOui1, POINT ptOui2, POINT ptNon1, POINT ptNon2);
void effacer_choix_multi_attaque(POINT P1);
BOOL recuper_choix_multi_attaque(POINT ptOui1, POINT ptOui2, POINT ptNon1, POINT ptNon2);
BOOL est_acceptee_multi_attaque();

/* Ecran titre */
void afficher_titre();
void afficher_choisir_interface();
void afficher_exemple_ecran_titre_ig1(POINT ptTitreIg1);
void afficher_ecran_titre_ig1();
void afficher_exemple_ecran_titre_ig2(POINT ptTitreIg2);
void afficher_ecran_titre_ig2();
POINT recuperer_clic_choix_ig();
void afficher_ecran_titre(int *ig);

/* Afficher Fin Partie */
void afficher_gagnant(int nbrePionJ1,int nbrePionJ2);

/* Redemander partie */
void afficher_texte_redemander_partie(POINT ptOui,POINT ptNon);
POINT recuperer_clic_redemander_partie(POINT ptOui,POINT ptNon);
BOOL redemander_partie();

/*
 * /\ VUE /\
 * ||     ||
 */

/*
 * ||            ||
 * \/ CONTRÔLEUR \/
 */

void bouger_pion_choisi_ig1(POINT centreCasePionChoisi,POINT centreCaseDestination,NUMCASE numCaseOrig,NUMCASE numCaseDestination,COULP couleurJoueur,int positionCasesLibres,int positionCasesLibresAttaque, int *nbrePionJoueur);
void bouger_pion_choisi_ig2(POINT centreCasePionChoisi,POINT centreCaseDestination,NUMCASE numCaseOrig,NUMCASE numCaseDestination,COULP couleurJoueur,int positionCasesLibres,int positionCasesLibresAttaque, int *nbrePionJoueur);
int choisir_ig(POINT clicChoixIg);
void choisir_pion_valide_ig1(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi);
void choisir_pion_valide_ig2(COULP couleurPionValide,POINT *centreCasePionChoisi,NUMCASE *numCasePionChoisi);
NUMCASE convertir_centreCase_en_numCase(POINT centreCase);
POINT convertir_numCase_en_centreCase(NUMCASE numcase);
NUMCASE convertir_numCase_ig1_vers_ig2(NUMCASE numCaseIg1);
NUMCASE convertir_numCase_ig2_vers_ig1(NUMCASE numCaseIg2);
BOOL savoir_si_rejouer_partie(POINT ptOui,POINT ptNon,POINT clicRedemanderPartie);
void trouver_cases_libres_ig1(POINT centrePionChoisi,NUMCASE numCasePionchoisi,COULP couleurJoueur,int *positionCasesLibres,int *positionCasesLibresAttaque, BOOL est_multiAttaque);
void trouver_cases_libres_ig2(POINT centrePionChoisi,NUMCASE numCasePionchoisi,COULP couleurJoueur,int *positionCasesLibres,int *positionCasesLibresAttaque, BOOL est_multiAttaque);
void tour_piece_ig1(COULP couleurJoueur, int *nbrePionJoueur);
void tour_piece_ig2(COULP couleurJoueur, int *nbrePionJoueur);

/*
 * /\ CONTRÔLEUR /\
 * ||            ||
 */
 
#endif // JOUER_H

