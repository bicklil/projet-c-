#include "traitement.h"

cercle* ajoutCercle(cercle* premier,cercle* actuel) 
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


cercle* supprimerCercle(cercle* actuel) 
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


IplImage* creationImage(IplImage* ptImage,int x,int y , int rayon)
/*recupere la zone de l'image au nieveau du cercle et la transformen en gris*/
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
	
	cvReleaseImage(&ptNewImage);
	
	return ptNewImageGray;
}


CvHistogram* calculHistogramme(IplImage* ptImage)
/*calcul l'histogramme d'une image en gris*/
{	
	int bins = 256;
    int hsize[] = {bins};
	float xranges[] = {0, 256};
    float* ranges[] = {xranges};
	CvHistogram* histo = cvCreateHist(1, hsize, CV_HIST_ARRAY, ranges,1);
	cvCalcHist(&ptImage,histo, 0, NULL );
	return histo;
}	


int cercleToucherTest(IplImage* ptImage,cercle* ptCercle, float precision)
/*compare deux histogramme pour voir si la zone du cercle a ete modifie*/
{
	double resultat;
	IplImage* test;
	CvHistogram* histo;


	test = creationImage(ptImage,(ptCercle->x),(ptCercle->y),RAYON);
	histo = calculHistogramme(test);
	
	cvReleaseImage(&test);
	
	resultat = cvCompareHist(ptCercle->histo,histo,CV_COMP_CORREL);
	
	cvReleaseHist(&histo);  
	
	if (resultat<precision)
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
/*fonction qui ajoute les points des qu'un cercle est touche
l'ajout de point depends de la duree d'existence su cercle*/
{
	int point_gagner;
	point_gagner = (ptNiveau->findevie)-(ptCercle->compteur);
	*ptScore = *ptScore + point_gagner;
	ptCercle = supprimerCercle(ptCercle);
	return ptCercle;
}


IplImage* captureImage(CvCapture* capture) // recupere une frame du flux de la webcam
{
	IplImage* ptImage = 0; 
	ptImage = cvQueryFrame(capture);
	if(ptImage == NULL)
	{
		printf("Impossible d'ouvrir l'image");
		exit(0);
	}
	cvFlip(ptImage, NULL, 1	);// mets l'image dans le bon sens
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


cercle* createCircleRandomp(IplImage* ptImage,cercle* ptPremier)
/*cree un cercle aleatoirement sur les bords de l'image*/
{
	int hauteur,largeur;
	int aleaLargeur,aleaHauteur,aleapos;
	cercle *ptCercle;

	ptCercle = (cercle*)malloc(sizeof(cercle));
	hauteur = ptImage->height;
	largeur = ptImage->width;
    
    if (ptCercle == NULL)
    {
        printf("Erreur memoire\n");
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





cercle*	modifiercercle(cercle* ptCercle, IplImage* ptImage, int* ptScore, paradiff *ptNiveau, float precision) // boucle generale sur les bulles (fin de vie, toucher , moddification)
/*fonction qui modifie tous les cercles existants
elle regarde dans un premier temps si un cercle est touche
si oui on supprime le cercle on ajoute le score et on passe au cercle suivant
sinon on regarde si le cercle est en fin de vie
sinon on regarde si on est au moment ou le cercle doit etre reduit et changer de taille
sinon on ne fait rien sur le cercle*/	
	{
      	CvScalar couleur[NBCOULEUR] = {cvScalar( 20, 148, 20,0 ),cvScalar(43,180,33,0),
      		   cvScalar( 0, 255, 163,0 ), cvScalar( 0, 255, 253,0 ),cvScalar( 0, 167, 255,0 ),
               cvScalar( 0, 103, 255,0 ),cvScalar( 0, 0, 255,0 ),
               cvScalar( 0x0, 0x0, 0x0,0 )};
		int modif = 0;//bool pour savoir si modif


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