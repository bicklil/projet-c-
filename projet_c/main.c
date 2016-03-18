#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <time.h> //pour le random

#define RAYON 10
#define NBCOULEUR 10
#define CHANGEMENT 4 // changement du rayon et de la couleur


 struct cercle{int x;
                int y;
                int rayon;
                CvScalar couleur;
                int compteur;
                struct cercle* suivant;
                struct cercle* precedent;};
                
typedef struct cercle cercle;

cercle* ajoutCercle(cercle* premier,cercle* actuel)
// on ajoute les nouveux cercles en tete de chaine
{
    if(premier != NULL)
    {
        premier->precedent = actuel;
    }
    actuel->suivant = premier;
    return actuel;
}

cercle* supprimerCercle(cercle* actuel,cercle* premier)
// supprime le cercle de la chaine
{
    if (actuel->precedent == NULL)
    {
        (actuel->suivant)->precedent = NULL;
        premier = actuel->suivant;
        return premier;
    }
    if (actuel->suivant == NULL)
    {
        (actuel->precedent)->suivant = NULL;
        free(actuel);
        return premier;
    }
    (actuel->suivant)->precedent = actuel->precedent;
    (actuel->precedent)->suivant = actuel->suivant;
    return premier;

}

IplImage* captureImage(CvCapture* capture)
{
	IplImage* ptImage = 0; // Pointeur sur une image OpenCV
	ptImage = cvQueryFrame(capture);
	if(!ptImage)
	{
		printf("Impossible d'ouvrir l'image");
		exit(0);
	}
	return ptImage;
}

CvCapture* loadVideo()
{
    CvCapture* capture = NULL;
    while(!capture)
    {
        capture=cvCaptureFromCAM(0); // mettre l'adresse de la video connait pas
        if (!capture)
        {
            printf("Ouverture du flux vidéo impossible !\n");
        }
    }
    return capture;
}
cercle* createCircleRandomp(IplImage* image,cercle* premier)
{
	int hauteur,largeur;
	int aleaLargeur,aleaHauteur;
	cercle *ptcercle;
	ptcercle = (cercle*)malloc(sizeof(cercle));
	hauteur = image->height;
	largeur = image->width;
    if (!ptcercle)
        {
            printf("Ouverture du flux vidéo impossible !\n");
            exit(0);
        }

	aleaLargeur = (rand())%(largeur-RAYON);
	aleaHauteur = (rand())%(hauteur-RAYON);

	cvCircle(image, cvPoint ( aleaLargeur , aleaHauteur ) ,RAYON,cvScalar( 20, 148, 20,0 ),1,0,0);

	ptcercle->x = aleaLargeur;
	ptcercle->y = aleaHauteur;
	ptcercle->rayon = RAYON;
	ptcercle->couleur = cvScalar( 0x0, 0x0, 0x0,0 );

	return ajoutCercle(premier,ptcercle);

}

void modifColorandsizeCircle(cercle* ptcercle)
  {
      	CvScalar couleur[NBCOULEUR] = {cvScalar( 20, 148, 20,0 ),cvScalar( 179, 255, 49,0 ),
                       cvScalar( 213, 220, 51,0 ),cvScalar( 233, 185, 52,0 ),
                       cvScalar( 246, 149, 51,0 ),cvScalar( 252, 107, 51,0 ),
                       cvScalar( 254, 107, 51,0 ),cvScalar( 254, 50, 49,0 ),
                       cvScalar( 0x0, 0x0, 0x0,0 ),cvScalar( 0x0, 0x0, 0x0,0 )};

        if((ptcercle->compteur%CHANGEMENT) == 0) // A METTRE EN TEST AU MOMENT DE L'INCREMENTATION
        {
            ptcercle->couleur = couleur[ptcercle->compteur/CHANGEMENT];
        }
       ptcercle->rayon = RAYON-ptcercle->compteur/CHANGEMENT;// reduction du cercle
  }
  
cercle* affichercercle(cercle* ptcercle, IplImage* ptImage)
	{
		cvCircle(ptImage, cvPoint ( ptcercle->x , ptcercle->y ) ,RAYON,cvScalar( 20, 148, 20,0 ),1,0,0);
		cvShowImage("Image originale", ptImage);
		return ptcercle->suivant;
	}

int main(void)
{
	int i = 0;
	CvCapture* ptvideo;
	IplImage* ptImage;
	cercle* premiercercle,*actuel;

	srand(time(NULL)); // initialisation de rand

	ptvideo = loadVideo();
	premiercercle = NULL;

    cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Image originale", 0, 0);

	while(1)
    {
        ptImage = captureImage(ptvideo);
        cvShowImage("Image originale", ptImage);
        //test
        
        if (!(i%5))
        {
      		premiercercle = createCircleRandomp(ptImage,premiercercle);
        }
        actuel=premiercercle;
        while(actuel->suivant!=NULL)
        {
        	actuel=affichercercle(actuel,ptImage);
        }
         i++;
         cvWaitKey(24);
    }

	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptvideo);

	return 0;
}
