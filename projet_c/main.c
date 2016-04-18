#include "interface.h"
#include "traitement.h"
#include <unistd.h>


void supprimeLesCerclesRestant(cercle *ptPremierCercle)
/*supprime tout les cercles en memoire*/
{
	while(ptPremierCercle != NULL)
	{
		ptPremierCercle = supprimerCercle(ptPremierCercle);
	}
}

void actualisationInterface(GtkWidget *ptImageGtk, IplImage *ptImage,int * ptQualite, int score,GtkWidget *ptScoreGtk)	
/*actualise toute l'interface non fixe durant la partie*/
{
	char texteScore[80];

	cvSaveImage("/dev/shm/image.png", ptImage, ptQualite);
	gtk_image_set_from_file(GTK_IMAGE(ptImageGtk), "/dev/shm/image.png");
	creationTexteScore(score,texteScore);
	gtk_label_set_text(GTK_LABEL(ptScoreGtk), texteScore);

}

void waitFor (unsigned int secs) {
/*permet de faire une pause de x sec*/
    time_t retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}

void preparezVous(GtkWidget *ptTexte) //marche pas sauf le hide
{
	gtk_label_set_text(GTK_LABEL(ptTexte), "Attention la partie commence dans : 3"	);
	waitFor(1);
	gtk_label_set_text(GTK_LABEL(ptTexte), "Attention la partie commence dans : 2"	);
	waitFor(1);
	gtk_label_set_text(GTK_LABEL(ptTexte), "Attention la partie commence dans : 1"	);
	waitFor(1);
	gtk_label_set_text(GTK_LABEL(ptTexte), "c'est parti !"	);
	waitFor(1);
	gtk_widget_hide(ptTexte);
}

int main(int argc,char **argv)
{
    GtkWidget *ptWindow;
    GtkWidget *ptRadio0;
    GtkWidget *ptRadio1;
    GtkWidget *ptRadio2;
    GtkWidget *ptRadio3;
    GtkWidget *ptImageGtk;
    GtkWidget *ptTexte;
    GtkWidget *ptScoreGtk;
    GtkWidget *ptWindowEnd;
    GtkWidget *ptBoutonS;
    
    struct bestScoreGroupe * bestScoreGrp;
    
	int i = -1;
	int score;
	int * ptScore;
	int choix;
	paradiff niveau; // struct contenant les parametres du niveau choisit
	paradiff* ptNiveau;
	CvCapture* ptVideo;
	IplImage* ptImage;
	IplImage* ptInterieurCercle;
	cercle* ptPremierCercle;
	float precision;
	int qualite = 3;
	int *ptQualite;
	char texteScore[80];
	gchar saisie[100] ;
	int meilleur;
	
	srand(time(NULL)); // initialisation de rand
	
	choix = 0;
	precision = 0;
	ptVideo = loadVideo();
	ptPremierCercle = NULL;
	ptScore = &score;
	ptNiveau = &niveau;
	ptQualite = &qualite;
	score = 0;
	bestScoreGrp = lireMeilleurScorePremiereFois() ;
	
	gtk_init(&argc,&argv);
	
	creationTexteScore(score,texteScore);
	
	ptTexte = gtk_label_new("Bienvenue sur EPIC BUBBLE");
    ptScoreGtk = gtk_label_new(texteScore);
	
	ptWindow = creationFenetrePrincipal();	
	ptRadio0 = creationButtonInvisible();
	ptRadio1 = creationButtonDependant("baby mode",ptRadio0);
	ptRadio2 = creationButtonDependant("normal",ptRadio0);
	ptRadio3 = creationButtonDependant("Insanity",ptRadio0);
	ptBoutonS = creationBoutonScore(ptWindow,bestScoreGrp);
	ptImageGtk = gtk_image_new_from_file("epic.jpg");
	
    creationAffectationTable(ptImageGtk,ptWindow,ptTexte,ptRadio1,ptRadio2,ptRadio3,ptBoutonS, ptScoreGtk); // affection des widgets a la fenetre gtk
	gtk_widget_show_all(ptWindow);
	
	choix = choixDifficulte(ptNiveau, ptRadio0,ptRadio1,ptRadio2,ptRadio3,ptTexte,ptBoutonS);
	
	while(1) // boucle infinie du programme si on ferme la fenetre le programme est quitte
    {	
   			
		//preparezVous(ptTexte); // MARCHE PAS FULL BUG FULL PAS ACTUALISATION
		
		while((DUREEPARTIE-i) ){ 
			i++;

		    ptImage = captureImage(ptVideo);
		    if (i%ptNiveau->difficulte==0)
		    {
		  		ptPremierCercle = createCircleRandomp(ptImage,ptPremierCercle);
		  		ptInterieurCercle = creationImage(ptImage,ptPremierCercle->x,ptPremierCercle->y , ptPremierCercle->rayon);
		    	ptPremierCercle->histo = calculHistogramme(ptInterieurCercle);
		    	cvReleaseImage(&ptInterieurCercle);  
		    }
		    if(ptPremierCercle != NULL)
		    {
		    		ptPremierCercle = modifiercercle( ptPremierCercle , ptImage , ptScore, ptNiveau , precision) ;

		    }
		    
		    actualisationInterface(ptImageGtk,ptImage,ptQualite,score,ptScoreGtk);	
		    
		    gtk_main_iteration();
		   	cvWaitKey(1);
		}
		ptWindowEnd = creationFenetreFinPartie();
		meilleur = verifieSiBestScore(bestScoreGrp,score,choix);
		AjoutPseudo(ptWindowEnd,saisie,meilleur);
		ajoutScoreCsv(saisie,score,choix);
		changementBest(bestScoreGrp,score,choix,saisie);

		supprimeLesCerclesRestant(ptPremierCercle);
		ptPremierCercle = NULL;
		affichageDifficulteEntrePartie(ptRadio0, ptRadio1, ptRadio2, ptRadio3, ptImageGtk,ptTexte,ptBoutonS);
		choix = choixDifficulte(ptNiveau, ptRadio0,ptRadio1,ptRadio2,ptRadio3,ptTexte,ptBoutonS);
		i = 0;
		score = 0;
    
	}
	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptVideo);
	free(bestScoreGrp);

	return 0;
}
