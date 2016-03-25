#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <time.h> //pour le random

#define RAYON 20 // radius de la bulle
#define NBCOULEUR 12 // nombre de couleur préparé pour les bulles voir modifiercerlce
#define CHANGEMENT 7
#define DUREEPARTIE 1000 // chiffre au pif 

 struct cercle{ int x;
                int y;
                int rayon;
                CvScalar couleur;
                int compteur;
                CvHistogram* histo;
                struct cercle* suivant;
                struct cercle* precedent;};
typedef struct cercle cercle;

struct parametredifficulte {int difficulte;
							int findevie;};
typedef struct parametredifficulte paradiff;


void callbackButton1(int state, void *pointer){ // fonction pour le choix de la difficulté #voir pour les bloquer quand on est plus dans la partie !

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
}

void choixNiveaux(paradiff *niveau,int choix) 
{

	switch(choix)
	{
		case 1:
		niveau->difficulte = 15;
		niveau->findevie = 63;
		break;
		case 2:
		niveau->difficulte = 10;
		niveau->findevie = 56;
		break ;
		case 3:
		niveau->difficulte = 15;
		niveau->findevie = 49;
		break ;
		default:
		break ;
	}
}

//http://chgi.developpez.com/liste/#LIII-A pour mettre au propre
cercle* ajoutCercle(cercle* premier,cercle* actuel)  // A METTRE AU PROPRE
// on ajoute les nouveux cercles en tete de chaine
{
    if(premier != NULL)
    {
        (premier->precedent) = actuel;
        (actuel->suivant) = premier;
    }
    else
    {
    	(actuel->suivant) = NULL; 
    }
    return actuel;
}


cercle* supprimerCercle(cercle* actuel) // A METTRE AU PROPRE
// supprime le cercle de la chaine et retourne le cercle suivant s'il existe sinon return NULL
{
	cercle* ptsuivant;
    if ((actuel->precedent) == NULL)
    {
    	if ((actuel->suivant) == NULL)
    	{
    		free(actuel);
    		return NULL;
    	}
    	else
    	{
    		ptsuivant = (actuel->suivant);
        	((actuel->suivant)->precedent) = NULL;
        	free(actuel);
        	return ptsuivant;
        }
    }
    if ((actuel->suivant) == NULL)
    {
        ((actuel->precedent)->suivant) = NULL;
        ptsuivant = actuel->precedent;
        free(actuel);
        return ptsuivant;
    }
    ((actuel->suivant)->precedent) = actuel->precedent;
    ((actuel->precedent)->suivant) = actuel->suivant;
    ptsuivant=actuel->suivant;
    free(actuel);
    return ptsuivant;

}


IplImage* creationImage(IplImage* ptImage,int x,int y , int rayon)//A METTRE EN GRIS PLUS SIMPLE
{
	IplImage* ptNewImageGray;
	IplImage* ptNewImage;
	
	CvRect ROI = cvRect((x-rayon),(y-rayon),rayon*2,rayon*2);
 	ptNewImage = cvCreateImage(cvSize(ROI.width,ROI.height), ptImage->depth, 3);
	ptNewImageGray = cvCreateImage(cvGetSize(ptNewImage),IPL_DEPTH_8U,1);
	
	cvSetImageROI(ptImage, ROI); //
	cvCopy(ptImage,ptNewImage,0);
	
	cvResetImageROI(ptImage); // libere le roi
	cvCvtColor(ptNewImage,ptNewImageGray,CV_RGB2GRAY); // met en gris
	
	return ptNewImageGray;
}

CvHistogram* calculHistogramme(IplImage* ptImage)
{	
	int bins = 256;
    int hsize[] = {bins};
	float xranges[] = {0, 256};
    float* ranges[] = {xranges};
	CvHistogram* histo = cvCreateHist(1, hsize, CV_HIST_ARRAY, ranges,1);
	cvCalcHist(&ptImage,histo, 0, NULL );
	return histo;
}	


int cercleToucherTest(IplImage* ptImage,cercle* ptCercle, int precision)
{
	double resultat;
	IplImage* test;
	CvHistogram* histo;
	float precisionf;
	
	precision = precision -100;
	precisionf = (float)precision/100;
	test = creationImage(ptImage,(ptCercle->x),(ptCercle->y),RAYON);
	histo = calculHistogramme(test);
	
	resultat = cvCompareHist(ptCercle->histo,histo,CV_COMP_CORREL);
	
	if (resultat<precisionf)
	{
		printf("TOUCH IN THE FACE\n");
		return 1;
	}
	else
	{
		return 0;
	}
}


cercle* cercleToucherPoint(cercle* ptCercle,int* ptScore,paradiff *ptNiveau) // incremente le compteur de socre en fonction de la duree de vie du cercle
{
	int point_gagner;
	point_gagner = (ptNiveau->findevie)-(ptCercle->compteur);
	*ptScore = *ptScore + point_gagner;
	ptCercle = supprimerCercle(ptCercle);
	return ptCercle;
}


IplImage* captureImage(CvCapture* capture) // recupere une frame du flux de la webcam
{
	IplImage* ptImage = 0; // Pointeur sur une image OpenCV
	ptImage = cvQueryFrame(capture);
	if(ptImage == NULL)
	{
		printf("Impossible d'ouvrir l'image");
		exit(0);
	}
	cvFlip(ptImage, NULL, 1	);// mets la cam dans le bon sens
	return ptImage;
}


CvCapture* loadVideo()// recupere le flux de la webcam
{
    CvCapture* capture = NULL;
    while(capture == NULL)
    {
        capture=cvCaptureFromCAM(0); 
        if (capture == NULL)
        {
            printf("Ouverture du flux vidéo impossible !\n");
        }
    }
    return capture;
}


cercle* createCircleRandomp(IplImage* ptImage,cercle* ptPremier) // cree un cercle aleatoirement sur les bords de la video
{
	int hauteur,largeur;
	int aleaLargeur,aleaHauteur,aleapos;
	cercle *ptCercle;
	
	ptCercle = (cercle*)malloc(sizeof(cercle));
	hauteur = ptImage->height;
	largeur = ptImage->width;
    
    if (ptCercle == NULL)
        {
            printf("Ouverture du flux vidéo impossible !\n");
            exit(0);
        }
    
    aleapos = (rand())%(3);
    switch(aleapos)// mise en position des bulles
    {
    	case 0://gauche
			aleaLargeur = ((rand())%(20))+RAYON;
			aleaHauteur = ((rand())%(hauteur-2*(RAYON)))+RAYON;
			break;
		case 1: //haut
			aleaLargeur = ((rand())%(largeur-2*(RAYON)))+RAYON;
			aleaHauteur = ((rand())%(20))+RAYON;
			break;
		case 2: //bas
			aleaLargeur = largeur-((rand())%(20))-RAYON;
			aleaHauteur = ((rand())%(hauteur-2*(RAYON)))+RAYON;
			break;
	}		
	
	ptCercle->x = aleaLargeur;
	ptCercle->y = aleaHauteur;
	ptCercle->rayon = RAYON;
	ptCercle->couleur = cvScalar( 20, 148, 20,0 );
	ptCercle->compteur = 0;
	ptCercle->precedent = NULL; 
	ajoutCercle(ptPremier,ptCercle);
	
	return ptCercle;
}


cercle*	modifiercercle(cercle* ptCercle, IplImage* ptImage, int* ptScore, paradiff *ptNiveau, int precision) // boucle generale sur les bulles (fin de vie, toucher , moddification)
	{
      	CvScalar couleur[NBCOULEUR] = {cvScalar( 20, 148, 20,0 ),cvScalar( 179, 255, 49,0 ),
               cvScalar( 213, 220, 51,0 ),cvScalar( 233, 185, 52,0 ),
               cvScalar( 246, 149, 51,0 ),cvScalar( 252, 107, 51,0 ),
               cvScalar( 254, 107, 51,0 ),cvScalar( 254, 50, 49,0 ),
               cvScalar( 0x0, 0x0, 0x0,0 ),cvScalar( 0x0, 0x0, 0x0,0 )};//couleur a revoir ca vva du vert au bleu ...
		int modif = 0;
		cercle* ptPremierCercle = ptCercle;
		while(ptCercle != NULL)
		{	
			modif = 0;
			(ptCercle->compteur)++;
			if (cercleToucherTest(ptImage,ptCercle,precision)==1) // test si on a toucher le cerlce
			{
				if (ptPremierCercle == ptCercle)
		    		{
						ptCercle=cercleToucherPoint(ptCercle,ptScore,ptNiveau);
		   				ptPremierCercle = ptCercle;
		   			}
				else
					{
						ptCercle=cercleToucherPoint(ptCercle,ptScore,ptNiveau);
					}
				modif=1;	
			}
		    if ((modif == 0) )//destruction du mailllon
		    {
		    	if(ptCercle!=NULL)
		    	{
		    		if((ptCercle->compteur) == ptNiveau->findevie)
		    		{
		    			printf("DEADPOOL\n");
		    			if (ptPremierCercle == ptCercle)
		    			{
		    				ptCercle = supprimerCercle(ptCercle);
		    				ptPremierCercle = ptCercle;
		    			}
						else
						{
							ptCercle = supprimerCercle(ptCercle);
						}	 		    			
		    		}
		    		else
		    		{
		    			if(((ptCercle->compteur)%CHANGEMENT) == 0 )//modification du maillon
		 			   {
							ptCercle->couleur = couleur[(ptCercle->compteur)/CHANGEMENT];
							ptCercle->rayon = RAYON-(ptCercle->compteur)/(CHANGEMENT/2);
							cvCircle(ptImage, cvPoint ( (ptCercle->x) , (ptCercle->y) ) ,(ptCercle->rayon),(ptCercle->couleur),-1,1,0);
							cvShowImage("Image originale", ptImage);
							if(ptCercle->suivant == NULL)
							{
								return ptPremierCercle;
							}
							else
							{
								ptCercle = (ptCercle->suivant);	
		    				}
		    			}
		    			else
						{
							cvCircle(ptImage, cvPoint ( ptCercle->x , ptCercle->y ) ,ptCercle->rayon,ptCercle->couleur,-1,0,0);
							cvShowImage("Image originale", ptImage);
							ptCercle = ptCercle->suivant;	    
		    			}

					}
				}
				else
				{
					return NULL;
				}
			}
		}
		return ptPremierCercle;
	}
	

void affichagePreparezVous() // mais pourquoi ca marche pas :'( #latristesse
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
}


void interface(int* precision,int* choix,int*exit) // interface pour choix de difficulté, affichage du score , bouton recommencer,
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

	
}

void affichageFinPartie(int* ptScore){

	cvDisplayOverlay("reglage","votre score est de\n",1000);
}


int main(void)
{
	int i = -1;
	int score;
	int * ptScore;
	int choix;
	int * ptChoix;
	int exit;
	int* ptExit;
	paradiff niveau; // struct contenant les parametres du niveau choisit
	paradiff* ptNiveau;
	CvCapture* ptVideo;
	IplImage* ptImage;
	IplImage* ptInterieurCercle;
	cercle* ptPremierCercle;
	int* ptPrecision;
	int precision;
	
	srand(time(NULL)); // initialisation de rand
	
	exit=1;
	choix=0;
	precision = 100; // correspond à 0
	ptVideo = loadVideo();
	ptPremierCercle = NULL;
	ptScore = &score;
	ptNiveau = &niveau;
	ptPrecision = &precision;
	ptChoix = &choix;
	ptExit=&exit;
	score =0;

	while(exit) // boucle infinie du programme (mettre l'option quitt)
    {	
   			
		interface(ptPrecision,ptChoix,ptExit);
		while(choix == 0){cvWaitKey(10);} // boutton pas check
		choixNiveaux(ptNiveau,choix); 
		affichagePreparezVous(); 
		
		while(DUREEPARTIE-i ){ // il faut rajouter un ou logique avec l'exit
			i++;
		    ptImage = captureImage(ptVideo);
		    if ((rand()%niveau.difficulte) == 0) // trop aleatoire change a chaque boucle j'aime pas ca ^^
		    {
		  		ptPremierCercle = createCircleRandomp(ptImage,ptPremierCercle);
		  		//printf("%d %p\n",i,ptPremierCercle);
		  		ptInterieurCercle = creationImage(ptImage,ptPremierCercle->x,ptPremierCercle->y , ptPremierCercle->rayon);
		    	ptPremierCercle->histo = calculHistogramme(ptInterieurCercle);
		    }
		    if(ptPremierCercle != NULL)
		    {
		    		ptPremierCercle = modifiercercle( ptPremierCercle , ptImage , ptScore, ptNiveau , precision) ;
		    }
		    cvWaitKey(1);
		}
		affichageFinPartie(ptScore);
    
	}
	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptVideo);

	return 0;
}