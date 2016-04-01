#ifndef INTERFACE
	#define INTERFACE
	
	#include <gtk/gtk.h>
	

	GtkWidget *creationAffectationTable(GtkWidget *ptImage, GtkWidget *ptWindow, GtkWidget* ptTexte,GtkWidget* ptBouton2, GtkWidget* ptBouton3, GtkWidget* ptBouton4, GtkWidget* ptScore);
	GtkWidget *creationFenetre();
	GtkWidget *creationButtonInvisible();
	GtkWidget *creationButtonDependant(const gchar *str1,GtkWidget *ButtonInvisible);
	int choixDifficulte(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3);

#endif