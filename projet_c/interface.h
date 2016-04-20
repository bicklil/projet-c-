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
	
	GtkWidget *creationAffectationTable(GtkWidget *ptImage, GtkWidget *ptWindow, GtkWidget* ptTexte,GtkWidget* ptBouton2, GtkWidget* ptBouton3, GtkWidget* ptBouton4,GtkWidget *ptBoutonS, GtkWidget* ptScore);
	GtkWidget *creationFenetrePrincipal();
	GtkWidget *creationFenetreFinPartie();
	GtkWidget *creationButtonInvisible();
	GtkWidget *creationBoutonScore(GtkWidget *ptWindow,struct bestScoreGroupe *bestScoreGrp);
	GtkWidget *creationButtonDependant(const gchar *str1,GtkWidget *ButtonInvisible);
	GtkWidget *creationFenetreInstruction();
	void creationTexteScore(int score,char* scoreTexte);

	int choixDifficulte(paradiff *niveau, GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptTexte, GtkWidget *ptBoutonS);
	void affichageDifficulteEntrePartie(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptImage, GtkWidget *ptTexte, GtkWidget *ptBoutonS);
	void afficherInstructions(GtkWidget *ptWindow);

	void AjoutPseudo(GtkWidget *ptWindow, gchar* saisie, int meilleur);
	void ajoutScoreCsv(gchar* pseudo,int score,int diff);
	
	struct bestScoreGroupe * lireMeilleurScorePremiereFois();
	void changementBest(struct bestScoreGroupe *bestScoreGroupeV,int score,int choix,gchar* pseudo);
	int verifieSiBestScore(struct bestScoreGroupe *bestScoreGroupeV,int score,int diff);
	
#endif