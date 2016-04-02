#include "interface.h"
#include "traitement.h"






/*void callbackButton1(int state, void *pointer){ // fonction pour le choix de la difficulté #voir pour les bloquer quand on est plus dans la partie !

        int *ptChoix = (int*)pointer;
        printf("diff 1\n");
        if (state == 1)
        {*ptChoix = 1;}
}
        
void callbackButton2(int state, void *pointer){

        int *ptChoix = (int*)pointer;
        printf("diff 2\n");
        if (state == 1)
        {*ptChoix = 2;}
}
        
void callbackButton3(int state, void *pointer){

        int *ptChoix = (int*)pointer;
        printf("diff 3\n");
        if (state == 1)
        {*ptChoix = 3;}
}

void callbackButtonExit(int state, void *pointer){

        int *ptExit = (int*)pointer;
        *ptExit = 0;
}*/

void choixNiveaux(paradiff *niveau,int choix) 
{

	switch(choix)
	{
		case 1:
		niveau->difficulte = 50;
		niveau->findevie = 63;
		break;
		case 2:
		niveau->difficulte = 35;
		niveau->findevie =56;
		break ;
		case 3:
		niveau->difficulte = 20;
		niveau->findevie =49 ;
		break ;
		default:
		break ;
	}
}


/*void affichagePreparezVous() // mais pourquoi ca marche pas :'( #latristesse
{
	cvDisplayOverlay("reglage","Attention Preparez vous !",1000);
	cvWaitKey(1000);
	cvDisplayOverlay("reglage","3",1000);
	cvWaitKey(1000);
	cvDisplayOverlay("reglage","2",1000);
	cvWaitKey(1000);
	cvDisplayOverlay("reglage","1",1000);
	cvWaitKey(1000);
	cvDisplayOverlay("reglage","c'est parti !",1000);
}*/


/*void interface(int* precision,int* choix,int*exit) // interface pour choix de difficulté, affichage du score , bouton recommencer,
{
	cvNamedWindow("reglage", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("reglage", 500 , 0);
	
	cvCreateTrackbar("precision","reglage",precision,200,NULL);
	cvCreateButton("difficulte 1",callbackButton1,(void*)choix,CV_RADIOBOX,0); // choix des difficutées
	cvCreateButton("difficulte 2",callbackButton2,(void*)choix,CV_RADIOBOX,0);
	cvCreateButton("difficulte 3",callbackButton3,(void*)choix,CV_RADIOBOX,0);
	
	cvCreateButton("EXIT",callbackButtonExit,(void*)exit,CV_PUSH_BUTTON,0); // bouton qui quit le prog (mettre le callback)
	
	cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL); // mettre dans interface
	cvMoveWindow("Image originale", 0, 0);

	
}*/

/*void affichageFinPartie(int* ptScore){

	cvDisplayOverlay("reglage","votre score est de\n",1000);
	cvWaitKey(1000);
}*/
void supprimeLesCerclesRestant(cercle *ptPremierCercle)
{
	while(ptPremierCercle !=NULL)
	{
		ptPremierCercle = supprimerCercle(ptPremierCercle);
	}
}

void actualisationInterface(GtkWidget *ptImageGtk, IplImage *ptImage,int * ptQualite, int score,GtkWidget *ptScoreGtk)	
{
	char texteScore[80];
	cvSaveImage("/dev/shm/image.png", ptImage, ptQualite);
	gtk_image_set_from_file(GTK_IMAGE(ptImageGtk), "/dev/shm/image.png");
	creationTexteScore(score,texteScore);
	gtk_label_set_text(GTK_LABEL(ptScoreGtk), texteScore	);

}

int main(int argc,char **argv)
{
	GtkWidget *ptTable;
    GtkWidget *ptWindow;
    GtkWidget *ptRadio0;
    GtkWidget *ptRadio1;
    GtkWidget *ptRadio2;
    GtkWidget *ptRadio3;
    GtkWidget *ptImageGtk;
    GtkWidget *ptTexte;
    GtkWidget *ptScoreGtk;
    
	int i = -1;
	int score;
	int * ptScore;
	int choix;
	//int * ptChoix;
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
	
	srand(time(NULL)); // initialisation de rand
	
	choix=0;// choix fixé en brut a mettre avec l'interface
	precision = 0;
	ptVideo = loadVideo();
	ptPremierCercle = NULL;
	ptScore = &score;
	ptNiveau = &niveau;
	//ptChoix = &choix;
	ptQualite=&qualite;
	score =0;
	
	gtk_init(&argc,&argv);
	
	creationTexteScore(score,texteScore);
	
	ptTexte = gtk_label_new("");
    ptScoreGtk = gtk_label_new(texteScore);
	
	ptWindow = creationFenetre();	
	ptRadio0 = creationButtonInvisible();
	ptRadio1 = creationButtonDependant("difficulte 1",ptRadio0);
	ptRadio2 = creationButtonDependant("difficulte 2",ptRadio0);
	ptRadio3 = creationButtonDependant("difficulte 3",ptRadio0);
	ptImageGtk = gtk_image_new_from_file("epic.jpg");
	

    ptTable=creationAffectationTable(ptImageGtk,ptWindow,ptTexte,ptRadio1,ptRadio2,ptRadio3, ptScoreGtk); // affection des widgets a la fenetre gtk
	gtk_widget_show_all(ptWindow);
	choix = choixDifficulte(ptRadio0,ptRadio1,ptRadio2,ptRadio3); 

	while(1) // boucle infinie du programme (mettre l'option quitt)
    {	
   			

		choixNiveaux(ptNiveau,choix); 
		//affichagePreparezVous(); 
		
		while((DUREEPARTIE-i) ){ 
			i++;

		    ptImage = captureImage(ptVideo);
		    if (i%20==0)//(rand()%niveau.difficulte) == 0) // trop aleatoire change a chaque boucle j'aime pas ca ^^
		    {
		  		ptPremierCercle = createCircleRandomp(ptImage,ptPremierCercle);
		  		//printf("%d %p\n",i,ptPremierCercle);
		  		ptInterieurCercle = creationImage(ptImage,ptPremierCercle->x,ptPremierCercle->y , ptPremierCercle->rayon);
		    	ptPremierCercle->histo = calculHistogramme(ptInterieurCercle);
		    	cvReleaseImage(&ptInterieurCercle);  // RELEASE
		    }
		    if(ptPremierCercle != NULL)
		    {
		    		ptPremierCercle = modifiercercle( ptPremierCercle , ptImage , ptScore, ptNiveau , precision) ;

		    }
		    
		    actualisationInterface(ptImageGtk,ptImage,ptQualite,score,ptScoreGtk);	
		    
		    gtk_main_iteration();
		   	cvWaitKey(50);
		}
		
		supprimeLesCerclesRestant(ptPremierCercle);
		ptPremierCercle = NULL;
		affichageDifficulteEntrePartie(ptRadio0, ptRadio1, ptRadio2, ptRadio3, ptImageGtk);
		choix = choixDifficulte(ptRadio0,ptRadio1,ptRadio2,ptRadio3);
		i=0,score=0;
    
	}
	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptVideo);

	return 0;
}
