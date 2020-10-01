void afficher_plateau_ig2()
{
	int i=0,j=0;
	POINT ptbgCase,pthdCase,ptCentreCase;
	NUMCASE numCaseIg1={0,0},numCaseIg2={0,0};

	ptbgCase.x=0;ptbgCase.y=0;
	pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y=ptbgCase.y+LARG_CASE;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if( ((i%2) && (j%2)) || (!(i%2) && !(j%2)) ) //Si les coordonnées sont toutes les 2 paires ou toutes les 2 impaires
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_VIDE);
			}
			
			else
			{
				afficher_case_ig2(ptbgCase,pthdCase,COULEUR_CASE_JOUEURS);
			}
			ptbgCase.x+=LARG_CASE;
			pthdCase.x+=LARG_CASE;
		}
		ptbgCase.x=0;ptbgCase.y+=LARG_CASE;
		pthdCase.x=ptbgCase.x+LARG_CASE;pthdCase.y+=LARG_CASE;
	}
	
	
	
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(plateau[j][i].coulP != aucune)
			{
				numCaseIg1.ligne=i;numCaseIg1.colonne=j;
				numCaseIg2=convertir_numCase_ig1_vers_ig2(numCaseIg1);
				ptCentreCase=convertir_numCase_en_centreCase(numCaseIg2);
				
				afficher_piece_ig2(ptCentreCase,i,j);	
			}
		}
	}
	
	affiche_all();
}
