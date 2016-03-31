
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
		niveau->findevie = 77;
		break;
		case 2:
		niveau->difficulte = 35;
		niveau->findevie =63;
		break ;
		case 3:
		niveau->difficulte = 20;
		niveau->findevie =56 ;
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


int main(void)
{
	int i = -1;
	int score;
	int * ptScore;
	int choix;
	int * ptChoix;
	paradiff niveau; // struct contenant les parametres du niveau choisit
	paradiff* ptNiveau;
	CvCapture* ptVideo;
	IplImage* ptImage;
	IplImage* ptInterieurCercle;
	cercle* ptPremierCercle;
	float precision;
	
	srand(time(NULL)); // initialisation de rand
	
	choix=3;// choix fixé en brut a mettre avec l'interface
	precision = 0;
	ptVideo = loadVideo();
	ptPremierCercle = NULL;
	ptScore = &score;
	ptNiveau = &niveau;
	ptChoix = &choix;
	score =0;
	
		//interface(ptPrecision,ptChoix,ptExit);
		while(choix == 0){cvWaitKey(10);} // boutton pas check

	while(1) // boucle infinie du programme (mettre l'option quitt)
    {	
   			

		choixNiveaux(ptNiveau,choix); 
		//affichagePreparezVous(); 
		
		while((DUREEPARTIE-i) ){ 
			i++;

		    ptImage = captureImage(ptVideo);
		    if (i%200000)//(rand()%niveau.difficulte) == 0) // trop aleatoire change a chaque boucle j'aime pas ca ^^
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
		    cvWaitKey(50);
		}
    
	}
	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptVideo);

	return 0;
}
