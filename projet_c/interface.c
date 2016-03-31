#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *creationAffectationTable(GtkWidget *pImage, GtkWidget *pWindow, GtkWidget* texte,GtkWidget* bouton2, GtkWidget* bouton3, GtkWidget* bouton4, GtkWidget* score)
{
	GtkWidget *ptTable;
	
	ptTable = gtk_table_new(6,10,TRUE);
	gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(ptTable));
	gtk_table_attach_defaults( GTK_TABLE(ptTable), texte,0,6,0,1);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), bouton2,7,9,1,2);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), bouton3,7,9,2,3);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), bouton4,7,9,3,4);
	gtk_table_attach_defaults( GTK_TABLE(ptTable), score,7,9,4,6);
	gtk_table_attach( GTK_TABLE(ptTable), pImage,1,6,0,6,GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
	return ptTable; 
}




int main(int argc,char **argv)
{
	int choix;
    /* Déclaration du widget */
    GtkWidget *pTable;
    GtkWidget *pWindow;
    GtkWidget *pRadio0;
    GtkWidget *pRadio1;
    GtkWidget *pRadio2;
    GtkWidget *pRadio3;
    GtkWidget *pImage;
    GtkWidget *pTexte;
    GtkWidget *pScore;
    gtk_init(&argc,&argv);
    char *charScore;
    
    pTexte = gtk_label_new("");
    pScore = gtk_label_new("charScore");
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 1080, 600);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Bubble Epic");
    g_signal_connect(G_OBJECT(pWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    /* Création du premier bouton radio */
    pRadio0 = gtk_radio_button_new_with_label(NULL, "selectionnez une difficulte");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pRadio0),TRUE);
    pRadio1 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadio0), "difficulte 1");
    /* Ajout du deuxieme */
    pRadio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio0), "difficulte 2");
    /* Ajout du troisième */
    pRadio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio0), "difficulte 3");
    
	pImage = gtk_image_new_from_file("epic.jpg"	);
    pTable=creationAffectationTable(pImage,pWindow,pTexte,pRadio1,pRadio2,pRadio3, pScore); // affection des widgets a la fenetre gtk
    gtk_table_set_homogeneous(  GTK_TABLE(pTable),FALSE );

    gtk_widget_show_all(pWindow);
        //gtk_events_pending();
    
	while(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(pRadio0))==TRUE){gtk_main_iteration(); }
	/*recupere le bouton select*/
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(pRadio1))==TRUE) choix =1;
   	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(pRadio2))==TRUE) choix =2;
   	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(pRadio3))==TRUE) choix =3;
    
   	gtk_container_remove (GTK_CONTAINER(pTable),pRadio3);
   	gtk_container_remove (GTK_CONTAINER(pTable),pRadio2);
   	gtk_container_remove (GTK_CONTAINER(pTable),pRadio1);
    
    
    while(1){
    gtk_image_set_from_file(GTK_IMAGE(pImage), "/dev/shm/image.png"	);
	    gtk_main_iteration();
	}

    gtk_main();
    /* Démarrage de la boucle événementielle */

    
    return EXIT_SUCCESS; 
}
//http://gtk.developpez.com/cours/gtk2/?page=page_7	
