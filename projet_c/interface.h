#ifndef INTERFACE
	#define INTERFACE
	
	#include <gtk/gtk.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "traitement.h"

	
	struct bestScore{
					int diff;
					int score;
					char pseudo[81];
					char date[100];};
					
	typedef struct bestScore bestScore;
	
	struct bestScoreGroupe{
					struct bestScore *bestDiff1;
					struct bestScore *bestDiff2;
					struct bestScore *bestDiff3;};
					
	//typedef struct bestScroreGroupe bestScoreGroupe;
	
	struct donneePseudo{
				GtkWidget *ptEntry;
				gchar saisie[100];
				GtkWidget *ptWindow;
				int etat;};
				
	typedef struct donneePseudo donneePseudo;
	
	int verifieSiBestScore(struct bestScoreGroupe *bestScoreGroupeV,int score,int diff);
	GtkWidget *creationAffectationTable(GtkWidget *ptImage, GtkWidget *ptWindow, GtkWidget* ptTexte,GtkWidget* ptBouton2, GtkWidget* ptBouton3, GtkWidget* ptBouton4,GtkWidget *ptBoutonS, GtkWidget* ptScore);
	GtkWidget *creationFenetrePrincipal();
	GtkWidget *creationFenetreFinPartie();
	GtkWidget *creationButtonInvisible();
	GtkWidget *creationButtonDependant(const gchar *str1,GtkWidget *ButtonInvisible);
	int choixDifficulte(paradiff *niveau, GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptTexte, GtkWidget *ptBoutonS);
	void affichageDifficulteEntrePartie(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptImage, GtkWidget *ptTexte, GtkWidget *ptBoutonS);
	void creationTexteScore(int score,char* scoreTexte);
	void AjoutPseudo(GtkWidget *ptWindow, gchar* saisie, int meilleur);
	void clickButton(GtkWidget *ptButton, gpointer data);
	void ajoutScoreCsv(gchar* pseudo,int score,int diff);
	struct bestScoreGroupe * lireMeilleurScorePremiereFois();
	GtkWidget *creationBoutonScore(GtkWidget *ptWindow,struct bestScoreGroupe *bestScoreGrp);
	void changementBest(struct bestScoreGroupe *bestScoreGroupeV,int score,int choix,gchar* pseudo);
	GtkWidget *creationFenetreInstruction();
	void afficherInstructions(GtkWidget *ptWindow);
	
#endif
