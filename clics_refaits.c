void afficher_ecran_jeu_selon_ig(BOOL igChoisi);
void afficher_interface(BOOL igChoisi);
BOOL choisir_ig();
void afficher_ecran_titre(BOOL *igChoisi);
BOOL savoir_si_rejouer_partie(POINT ptOui,POINT ptNon);
BOOL redemander_partie(int nbrePionJ1,int nbrePionJ2);


void afficher_ecran_jeu_selon_ig(BOOL igChoisi)
{
	fill_screen(noir);
	
	if (igChoisi==1)
		afficher_plateau_ig1();
	else
		afficher_plateau_ig2();
	
	afficher_interface(igChoisi);
	affiche_all();
}


void afficher_interface(BOOL igChoisi)
{
	POINT ptTexteTour,ptTourJoueur;
	
	ptTexteTour.x=HAUT_FENETRE+20;ptTexteTour.y=HAUT_FENETRE-20;

	ptTourJoueur.x=HAUT_FENETRE+(LARG_FENETRE-HAUT_FENETRE)/2;
	ptTourJoueur.y=0.85*HAUT_FENETRE;
	

	aff_pol("A qui de jouer ?",20,ptTexteTour,blanc);

	
	if(igChoisi==TRUE)
	{
		afficher_piece_triangle_haut(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
		afficher_piece_triangle_bas(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
	}
	
	else if(igChoisi==FALSE)
	{
		afficher_piece_rond(ptTourJoueur,COULEUR_JOUEUR1); //coul1 car le joueur 1 commence
	}
	
	affiche_all();
}



BOOL choisir_ig()
{
	POINT clicChoixIg;
	
	do{
		clicChoixIg = wait_clic();
		if( (clicChoixIg.x>70) && (clicChoixIg.x<370) && (clicChoixIg.y<420) && (clicChoixIg.y>120) )
			return TRUE;
		else if( (clicChoixIg.x>440) && (clicChoixIg.x<740) && (clicChoixIg.y<420) && (clicChoixIg.y>120) )
			return FALSE;
	}while(1);
}


void afficher_ecran_titre(BOOL *igChoisi)
{
	fill_screen(noir);
	afficher_titre();
	afficher_ecran_titre_ig1();
	afficher_ecran_titre_ig2();
	
	affiche_all();
	*igChoisi=choisir_ig();
}


BOOL savoir_si_rejouer_partie(POINT ptOui,POINT ptNon)
{
	POINT clicRejouer;	
	do{
		clicRejouer = wait_clic();
		if( (clicRejouer.x>ptOui.x) && (clicRejouer.x<ptOui.x+40) && (clicRejouer.y>ptOui.y-20) && (clicRejouer.y<ptOui.y) )
			return TRUE;
		if( (clicRejouer.x>ptNon.x) && (clicRejouer.x<ptNon.x+40) && (clicRejouer.y>ptNon.y-20) && (clicRejouer.y<ptNon.y) )
			return FALSE;
	}while(1);
}

BOOL redemander_partie(int nbrePionJ1,int nbrePionJ2)
{
	POINT ptOui,ptNon;
	BOOL rejouer=FALSE;

	ptOui.x=(LARG_FENETRE/3)+150;ptOui.y=HAUT_FENETRE/2;
	ptNon.x=(LARG_FENETRE/3)+250;ptNon.y=ptOui.y;
	
	fill_screen(noir);
	afficher_gagnant(nbrePionJ1,nbrePionJ2);
	afficher_texte_redemander_partie(ptOui,ptNon);
	rejouer=savoir_si_rejouer_partie(ptOui,ptNon);
	
	return rejouer;
}


int main()
{
	BOOL rejouer = TRUE,igChoisi = TRUE;
	int nbrePionJ1, nbrePionJ2;
	int *nbrePionAutreJoueur;
	COULP couleurJoueur = coul1;
	
	init_graphics(LARG_FENETRE,HAUT_FENETRE);
	affiche_auto_off();
	
	do
	{
		igChoisi = TRUE;
		nbrePionJ1 = 20, nbrePionJ2 = 20;
		nbrePionAutreJoueur = &nbrePionJ2;
		couleurJoueur = coul1;
		
		initialiser_plateau();
		afficher_ecran_titre(&igChoisi);
		afficher_ecran_jeu_selon_ig(igChoisi);
		do
		{
			nbrePionAutreJoueur = (couleurJoueur == coul1) ? &nbrePionJ2 : &nbrePionJ1;
			if(igChoisi == TRUE)
			{
				tour_piece_ig1(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_joueur_ig1(&couleurJoueur);
			}
			else if(igChoisi == FALSE)
			{
				tour_piece_ig2(couleurJoueur, nbrePionAutreJoueur);
				changer_tour_joueur_ig2(&couleurJoueur);
			}
		}while( !tester_fin_jeu(couleurJoueur, *nbrePionAutreJoueur));
		rejouer = redemander_partie(nbrePionJ1,nbrePionJ2);
	}while(rejouer);
	
	fill_screen(noir);
	affiche_all();
	wait_escape();
	return 0;
}

