#include "interface.h"

GtkWidget *creationFenetre()
{
	GtkWidget *ptWindow;
	ptWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(ptWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(ptWindow), 1080, 600);
    gtk_window_set_title(GTK_WINDOW(ptWindow), "Bubble Epic");
    g_signal_connect(G_OBJECT(ptWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	return ptWindow;
}

GtkWidget *creationButtonInvisible()
{
	GtkWidget *Button;
	Button = gtk_radio_button_new_with_label(NULL, "selectionnez une difficulte");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Button),TRUE);
	return Button;
}

GtkWidget *creationButtonDependant(const gchar *str1,GtkWidget *ButtonInvisible)
{
	GtkWidget *Button;
	Button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(ButtonInvisible), str1);
	return Button;
}

GtkWidget *creationAffectationTable(GtkWidget *ptImage, GtkWidget *ptWindow, GtkWidget* ptTexte,GtkWidget* ptBouton2, GtkWidget* ptBouton3, GtkWidget* ptBouton4, GtkWidget* ptScore)
{
	GtkWidget *ptTable;
	
	ptTable = gtk_table_new(6,10,TRUE);
	gtk_container_add(GTK_CONTAINER(ptWindow), GTK_WIDGET(ptTable));
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptTexte,0,6,0,1);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton2,7,9,1,2);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton3,7,9,2,3);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptBouton4,7,9,3,4);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), ptScore,7,9,4,6);
	gtk_table_attach( GTK_TABLE(ptTable), ptImage,1,6,0,6,GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
	gtk_table_set_homogeneous(  GTK_TABLE(ptTable),FALSE );
	return ptTable; 
}



int choixDifficulte(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3)
{
	int choix;
	while(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio0))==TRUE){gtk_main_iteration(); }
	/*recupere le bouton select*/
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio1))==TRUE) choix =1;
   	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio2))==TRUE) choix =2;
   	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(ptRadio3))==TRUE) choix =3;
    
    gtk_widget_hide  (ptRadio3);
   	gtk_widget_hide  (ptRadio2);
   	gtk_widget_hide  (ptRadio1);
   	return choix;
}

void affichageDifficulteEntrePartie(GtkWidget *ptRadio0, GtkWidget *ptRadio1, GtkWidget *ptRadio2, GtkWidget *ptRadio3, GtkWidget *ptImage)
{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ptRadio0),TRUE);
		gtk_image_set_from_file(GTK_IMAGE(ptImage), "epic.jpg");
		printf("test");
		gtk_widget_show(ptRadio1);
		gtk_widget_show(ptRadio2);
		gtk_widget_show(ptRadio3);
		//gtk_main_iteration();
		
}

/*int main(int argc,char **argv)
{
	int choix;
     Déclaration des widgets 
    GtkWidget *pTable;
    GtkWidget *ptWindow;
    GtkWidget *ptRadio0;
    GtkWidget *ptRadio1;
    GtkWidget *ptRadio2;
    GtkWidget *ptRadio3;
    GtkWidget *ptImage;
    GtkWidget *ptTexte;
    GtkWidget *ptScore;
    
    gtk_init(&argc,&argv);
    char *charScore;
    
    ptTexte = gtk_label_new("");
    ptScore = gtk_label_new("charScore");
	
	creationFenetre(ptWindow);	
    ptTable=creationAffectationTable(ptImage,ptWindow,ptTexte,ptRadio1,ptRadio2,ptRadio3, ptScore); // affection des widgets a la fenetre gtk
	initialisationDifficulté(ptImage,ptRadio0,ptRadio1,ptRadio2,ptRadio3);
    
    gtk_widget_show_all(ptWindow);
        
    choix = choixDifficulté(ptRadio0,ptRadio1,ptRadio2,ptRadio3); 
    
    while(1)
    {
		actualisationImage(ptImage);	
		gtk_main_iteration();
	}

    gtk_main();
    Démarrage de la boucle événementielle 

    
    return EXIT_SUCCESS; 
}*/

