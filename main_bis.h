/* CORBEIL Alex - VIDAL Antoine IATIC3 */

#ifndef MAIN_H
#define MAIN_H

//~ #include "graphics.h"

#define LARG_FENETRE 800
#define HAUT_FENETRE 600

#define LARG_CASE 0.1*HAUT_FENETRE
#define LONGUEUR_PIECE (2.0/3.0)*LARG_CASE
#define NB_CASES 10

typedef enum{
	coulj1,coulj2
}COULP;

typedef enum{
	vide,pion,dame
}TYPEP;

typedef struct{
	TYPEP typep;
	COULP coulp;
}PIECE;



#endif
