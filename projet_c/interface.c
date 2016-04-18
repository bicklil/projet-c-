#include "interface.h"

void clickButton(GtkWidget *ptButton, gpointer data)
{
 	donneePseudo* donneePseudoV = (donneePseudo*)data;
 	const gchar* temp;
    /* Recuperation du texte contenu dans le GtkEntry */
    temp = gtk_entry_get_text(GTK_ENTRY(donneePseudoV->ptEntry));
    sprintf(donneePseudoV->saisie,"%s",temp);
    if (strcmp(donneePseudoV->saisie , "") == 0)
    {
    	sprintf(donneePseudoV->saisie,"%s","Anonymous");
    }
    if (strcmp(donneePseudoV->saisie , "entrez votre pseudo") == 0 )
    {
    	sprintf(donneePseudoV->saisie,"%s","Anonymous");
    }
    gtk_widget_destroy(donneePseudoV->ptWindow);
    donneePseudoV->etat = 0;
}


void quit_prog(GtkWidget *ptWindow , gpointer data)
{
	exit(0);
}

void rien_faire(GtkWidget *ptWindow , gpointer data)
{
	
}


GtkWidget *creationFenetrePrincipal()
/*cree une fenetre GTK*/
{
	GtkWidget *ptWindow;
	ptWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(ptWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(ptWindow), 1080, 600);
    gtk_window_set_title(GTK_WINDOW(ptWindow), "Bubble Epic");
    g_signal_connect(G_OBJECT(ptWindow), "destroy",G_CALLBACK(quit_prog), NULL);
	return ptWindow;
}


GtkWidget *creationFenetreFinPartie()
/*cree une fenetre gtk*/
{
	GtkWidget *ptWindow;
	ptWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(ptWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(ptWindow),300,500);
	gtk_window_set_title(GTK_WINDOW(ptWindow),"Fin de partie");
	g_signal_connect(G_OBJECT(ptWindow), "delete-event",G_CALLBACK(rien_faire),NULL);
	return ptWindow;
}


void AjoutPseudo(GtkWidget *ptWindow,gchar saisie[], int meilleur)
/*remplit la fenetre de fin de score et ajoute un pseudo si rien n'est remplit anonymous par defaut*/
{
	donneePseudo *donneePseudoV;
	GtkWidget *ptZoneTexte;
	GtkWidget *ptVBox;
	GtkWidget *ptButton;
	GtkWidget *ptLabel;
	
	ptVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(ptWindow), ptVBox);
    if (meilleur)
    {
    	ptLabel = gtk_label_new("Bravo vous avez le meilleur score !");
    }
    else
    {
    	ptLabel = gtk_label_new("");
    }
    gtk_box_pack_start(GTK_BOX(ptVBox), ptLabel, TRUE, FALSE, 0);
 
	
	ptZoneTexte = gtk_entry_new_with_max_length(80);
	gtk_entry_set_text(GTK_ENTRY(ptZoneTexte) , "entrez votre pseudo");
	gtk_box_pack_start(GTK_BOX(ptVBox), ptZoneTexte, TRUE, FALSE, 0);
	
	ptButton = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(ptVBox), ptButton, TRUE, FALSE, 0);
	
	donneePseudoV =(donneePseudo*) malloc( sizeof(donneePseudo));
	if (donneePseudoV == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}
	
	donneePseudoV->ptEntry = ptZoneTexte;
	donneePseudoV->ptWindow = ptWindow;
	donneePseudoV->etat = 1;
	
	g_signal_connect(G_OBJECT(ptButton),   "clicked" , G_CALLBACK(clickButton), (donneePseudo *) donneePseudoV);
	gtk_widget_show_all(ptWindow);
	
	
	while (donneePseudoV->etat == 1)
	{
		gtk_main_iteration();
	}
	
	strcpy(saisie, donneePseudoV->saisie);
	free(donneePseudoV);
}


GtkWidget *creationButtonInvisible()
/*cree un bouton radio coche par defaut qui ne sera pas affiche*/
{
	GtkWidget *Button;
	Button = gtk_radio_button_new_with_label(NULL, "selectionnez une difficulte");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Button),TRUE);
	return Button;
}


GtkWidget *creationButtonDependant(const gchar *str1,GtkWidget *ButtonInvisible)
/*cree un bouton radio qui rejoint le groupe de bouton du bouton invisible*/
{
	GtkWidget *Button;
	Button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(ButtonInvisible), str1);
	return Button;
}


GtkWidget *creationAffectationTable(GtkWidget *ptImage, GtkWidget *ptWindow, GtkWidget* ptTexte,GtkWidget* ptBouton2, GtkWidget* ptBouton3, GtkWidget* ptBouton4,GtkWidget *ptBoutonS, GtkWidget* ptScore)

/*creation d'une table qui met en place tout les elements sur une grille*/
{
	GtkWidget *ptTable;
	
	ptTable = gtk_table_new(6,10,TRUE);
	gtk_container_add(GTK_CONTAINER(ptWindow), GTK_WIDGET(ptTable));
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptTexte,0,6,0,1);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBoutonS,7,9,0,1);
	//gtk_label_set_text(GTK_LABEL(ptTable),"baby mode");
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton2,7,9,1,2);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton3,7,9,2,3);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton4,7,9,3,4);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptScore,7,9,4,6);
	gtk_table_attach( GTK_TABLE(ptTable), ptImage,1,6,0,6,GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
	gtk_table_set_homogeneous(  GTK_TABLE(ptTable),FALSE );
	return ptTable; 
}


void ajoutScoreCsv(gchar pseudo[],int score,int diff)
{
	time_t timer;
	struct tm *date; 
	FILE *fichier = fopen("score.csv","a");
	if (fichier == NULL)
	{
		printf("FICHIER INVALIDE");
		exit(0);
	}
	
	time(&timer);
	date = gmtime(&timer);
	
	fprintf(fichier,"%d,%d,%s ,%d/%d/%d \n",diff,score,pseudo,date->tm_mday,(date->tm_mon)+1,(date->tm_year)+1900);	
	fclose(fichier);
	//ecriture des score sous le format diff score pseudo date
}


void afficherBestScore(GtkWidget *ptBouton,gpointer data)
{
	GtkWidget *ptWindow;
	GtkWidget *ptTable;
	GtkWidget	*label1,*label2,*label3,*label4,
				*label5,*label6,*label7,*label8,
				*label9,*label10,*label11,*label12,
				*label13,*label14,*label15,*label16;
	char temp[10];
	
	ptWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(ptWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(ptWindow),300,400);
	gtk_window_set_title(GTK_WINDOW(ptWindow),"Meilleurs scores");
	
	struct bestScoreGroupe *bestScoreGrp = (struct bestScoreGroupe *) data;
	
	ptTable = gtk_table_new(4,4,TRUE);
	gtk_container_add(GTK_CONTAINER(ptWindow), GTK_WIDGET(ptTable));
	
	label1 = gtk_label_new("diff");
	gtk_table_attach_defaults (GTK_TABLE(ptTable),label1,0,1,0,1);
	label2 = gtk_label_new("score");
	gtk_table_attach_defaults (GTK_TABLE(ptTable),label2,1,2,0,1);
	label3 = gtk_label_new("pseudonyme");
	gtk_table_attach_defaults (GTK_TABLE(ptTable),label3,2,3,0,1);
	label4 = gtk_label_new("date");
	gtk_table_attach_defaults (GTK_TABLE(ptTable),label4,3,4,0,1);
	
	if (bestScoreGrp->bestDiff1->score == -1)
	{
		label5 = gtk_label_new("Pas de score pour la difficultee 1");
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label5,0,4,1,2);
	}
	else
	{
		label5 = gtk_label_new("diff 1");
		sprintf(temp,"%d",bestScoreGrp->bestDiff1->score);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label5,0,1,1,2);
		label6 = gtk_label_new(temp);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label6,1,2,1,2);
		label7 = gtk_label_new(bestScoreGrp->bestDiff1->pseudo);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label7,2,3,1,2);
		label8 = gtk_label_new(bestScoreGrp->bestDiff1->date);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label8,3,4,1,2);
	}
	if (bestScoreGrp->bestDiff2->score == -1)
	{
		label9 = gtk_label_new("Pas de score pour la difficultee 2");
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label9,0,4,2,3);
	}
	else
	{
		label9 = gtk_label_new("diff 2");
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label9,0,1,2,3);
		sprintf(temp,"%d",bestScoreGrp->bestDiff2->score);
		label10 = gtk_label_new(temp);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label10,1,2,2,3);
		label11 = gtk_label_new(bestScoreGrp->bestDiff2->pseudo);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label11,2,3,2,3);
		label12 = gtk_label_new(bestScoreGrp->bestDiff2->date);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label12,3,4,2,3);
	}
	if (bestScoreGrp->bestDiff3->score == -1)
	{
		label13 = gtk_label_new("Pas de score pour la difficultee 3");
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label13,0,4,3,4);
	}
	else
	{
		label13 = gtk_label_new("diff 3");
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label13,0,1,3,4);
		sprintf(temp,"%d",bestScoreGrp->bestDiff3->score);
		label14 = gtk_label_new(temp);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label14,1,2,3,4);
		label15 = gtk_label_new(bestScoreGrp->bestDiff3->pseudo);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label15,2,3,3,4);
		label16 = gtk_label_new(bestScoreGrp->bestDiff3->date);
		gtk_table_attach_defaults (GTK_TABLE(ptTable),label16,3,4,3,4);	
	}
	
	gtk_widget_show_all(ptWindow);
}


GtkWidget *creationBoutonScore(GtkWidget *ptWindow,struct bestScoreGroupe *bestScoreGrp)
{
	GtkWidget *ptBouton;
	ptBouton = gtk_button_new_with_label("affichez les meilleurs scores");
	g_signal_connect(G_OBJECT(ptBouton),"clicked",G_CALLBACK(afficherBestScore),(struct bestScoreGroupe*)bestScoreGrp);
	return ptBouton;
}


struct bestScoreGroupe *bestScoreDefaut()
{
	bestScore *bestDiff1,*bestDiff2,*bestDiff3;
	struct bestScoreGroupe *bestScoreGrp;
		
	bestDiff1 = (bestScore *) malloc (sizeof(bestScore));
	if (bestDiff1 == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}
	bestDiff2 = (bestScore *) malloc (sizeof(bestScore));
	if (bestDiff2 == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}
	bestDiff3 = (bestScore *) malloc (sizeof(bestScore));
	if (bestDiff3 == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}
		
	bestScoreGrp = (struct bestScoreGroupe *) malloc (sizeof(struct bestScoreGroupe));
	if (bestScoreGrp == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}	
	
	bestDiff1->diff = 1;
	bestDiff1->score = (-1);
	
	bestDiff2->diff = 2;
	bestDiff2->score = (-1);
	
	bestDiff3->diff = 3;
	bestDiff3->score = (-1);
	
	bestScoreGrp->bestDiff1 = bestDiff1;
	bestScoreGrp->bestDiff2 = bestDiff2;
	bestScoreGrp->bestDiff3 = bestDiff3;	
	
	return bestScoreGrp;
}


struct bestScoreGroupe * lireMeilleurScorePremiereFois()
{
	// on cree 4 structure best score , 3 pour les vrais best score de chaque diff et le dernier c'est le temp
	bestScore *bestDiff1,*bestDiff2,*bestDiff3,*bestTemp;
	struct bestScoreGroupe *bestScoreGrp;
	char temp[100];
	FILE *fichier;
	int diff;
	int a,b,c;
	
	bestTemp = (bestScore *) malloc (sizeof(bestScore));
	if (bestTemp == NULL)
	{
		printf("erreur pas de memoire");
		exit(0);
	}
	
	bestScoreGrp = bestScoreDefaut();
	bestDiff1 = bestScoreGrp->bestDiff1;
	bestDiff2 = bestScoreGrp->bestDiff2;
	bestDiff3 = bestScoreGrp->bestDiff3;
	
	
	fichier = fopen("score.csv","r");		
	if (fichier != NULL)
	{
		while ((diff = fgetc(fichier)) != EOF)
		{
			fgetc(fichier);
			
			fscanf(fichier,"%d,%s ,%d/%d/%d\n",&(bestTemp->score),bestTemp->pseudo,&a,&b,&c);
			sprintf(temp,"%d/%d/%d",a,b,c);
			strcpy(bestTemp->date,temp); // il y a un truc qui va pas
			switch(diff)
			{
				case 49 :
				if((bestTemp->score) > (bestDiff1->score))
				{

					bestDiff1->score = bestTemp->score;
					strcpy(bestDiff1->pseudo , bestTemp->pseudo);
					strcpy(bestDiff1->date , bestTemp->date);
				}	
				break;
		
				case 50 :
				if(bestTemp->score > bestDiff2->score)
				{
					bestDiff2->score = bestTemp->score;
					strcpy(bestDiff2->pseudo , bestTemp->pseudo);
					strcpy(bestDiff2->date , bestTemp->date);
				}			
				break;
			
				case 51 :
				if(bestTemp->score > bestDiff3->score)
				{
					bestDiff3->score = bestTemp->score;
					strcpy(bestDiff3->pseudo , bestTemp->pseudo);
					strcpy(bestDiff3->date , bestTemp->date);
				}			
				break;
			
				default :
				printf("tete");
				break;
			}
		
		}
		fclose(fichier);
		bestScoreGrp->bestDiff1 = bestDiff1;
		bestScoreGrp->bestDiff2 = bestDiff2;
		bestScoreGrp->bestDiff3 = bestDiff3;
		free(bestTemp);	
	}

	return bestScoreGrp;
}


void changementBest(struct bestScoreGroupe *bestScoreGroupeV,int score,int choix,gchar pseudo[])
{
	time_t timer;
	struct tm *date;
	time(&timer);
	date = gmtime(&timer); 
	
	switch (choix)
	{
		case 1 :
			bestScoreGroupeV->bestDiff1->score = score;
			strcpy(bestScoreGroupeV->bestDiff1->pseudo,pseudo);
			sprintf(bestScoreGroupeV->bestDiff1->date,"%d/%d/%d",date->tm_mday,(date->tm_mon)+1,(date->tm_year)+1900);		
			break;
		case 2 :
			bestScoreGroupeV->bestDiff2->score = score;
			strcpy(bestScoreGroupeV->bestDiff2->pseudo,pseudo);
			sprintf(bestScoreGroupeV->bestDiff2->date,"%d/%d/%d",date->tm_mday,(date->tm_mon)+1,(date->tm_year)+1900);	
			break;
		case 3 :
			bestScoreGroupeV->bestDiff3->score = score;
			strcpy(bestScoreGroupeV->bestDiff3->pseudo,pseudo);
			sprintf(bestScoreGroupeV->bestDiff3->date,"%d/%d/%d",date->tm_mday,(date->tm_mon)+1,(date->tm_year)+1900);	
			break;
		default :
		break;
	}
}


int verifieSiBestScore(struct bestScoreGroupe *bestScoreGroupeV,int  score,int diff)
{
	switch(diff)
	{
		case 1 :
			if(bestScoreGroupeV->bestDiff1->score < score)
			return 1;
			break;
		case 2 :
			if(bestScoreGroupeV->bestDiff2->score < score)
			return 1;
			break;
		case 3 :
			if(bestScoreGroupeV->bestDiff3->score < score)
			return 1;
			break;
		default :
			break;
	}
	return 0;	
}


int choixDifficulte(paradiff *niveau, GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptTexte, GtkWidget *ptBoutonS)
/*attends qu'une difficulte soit selectionné puis fait dispariatre les bouton*/
{
	int choix;
	while(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio0))==TRUE){gtk_main_iteration(); }
	/*recupere le bouton select*/
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio1))==TRUE)
	{
		choix = 1;
		niveau->difficulte = 8;
		niveau->findevie = 35;
	}
   if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio2))==TRUE)
   {
  	 	choix = 2;
   		niveau->difficulte = 3;
		niveau->findevie = 35;
   }
   if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio3))==TRUE)
   {
   		choix = 3;
   		niveau->difficulte = 1;
		niveau->findevie = 21;
   }
    
   gtk_widget_hide  (ptRadio3);
   gtk_widget_hide  (ptRadio2);
   gtk_widget_hide  (ptRadio1);
   gtk_widget_hide  (ptBoutonS);
   gtk_widget_hide  (ptTexte);
   return choix;
}


void affichageDifficulteEntrePartie(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptImage, GtkWidget *ptTexte, GtkWidget *ptBoutonS)
/*reaffiche les boutons de difficulte apres que la partie soit finie afon d'en refaire une autre*/
{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ptRadio0),TRUE);
		gtk_image_set_from_file(GTK_IMAGE(ptImage), "epic.jpg");
		gtk_widget_show(ptRadio1);
		gtk_widget_show(ptRadio2);
		gtk_widget_show(ptBoutonS);
		gtk_widget_show(ptRadio3);
		gtk_label_set_text(GTK_LABEL(ptTexte),"Voulez vous recommencez ? Si oui choissisez à nouveau une difficultée");
		gtk_widget_show(ptTexte);
			
}


void creationTexteScore(int score,char* scoreTexte) // cree un texte avec le score
{
 	sprintf(scoreTexte,"Votre score est de : %d", score);
}
