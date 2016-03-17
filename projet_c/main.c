#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <time.h> //pour le random
#define RAYON 10
#define NBCOULEUR 10

typedef struct {int x;
                int y;
                int rayon;
                cvScalar couleur;
                int compteur=0;
                cercle* suivant=NULL;
                cercle* precedent=NULL;}cercle;

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

IplImage* captureImage(cvCapture* capture)
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
    cvCapture* capture = NULL;
    while(!capture)
    {
        capture=cvCreateCameraCapture(); // mettre l'adresse de la video connait pas
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
	int aleaLargeur,aleahauteur;
	cercle *ptcercle;
	hauteur = image->height;
	largeur = image->width;

	aleaLargeur = (rand())%(largeur-RAYON);
	aleahauteur = (rand())%(hauteur-RAYON);

	cvCircle(image, cvPoint ( aleaLargeur, aleahauteur ) ,RAYON,cvScalar( 20, 148, 20,0 ),1,0,0);

	ptcercle->x = aleaLargeur;
	ptcercle->y = aleaHauteur;
	ptcercle->rayon = RAYON;
	ptcercle->couleur = cvScalar( 0x0, 0x0, 0x0,0 );

	return ajoutCercle(premier,ptcercle);

}

void modifColorandsizeCircle(cercle* ptcercle)
  {
      	cvScalar couleur[NBCOULEUR] = (cvScalar( 20, 148, 20,0 ),cvScalar( 179, 255, 49,0 ),
                       cvScalar( 213, 220, 51,0 ),cvScalar( 233, 185, 52,0 ),
                       cvScalar( 246, 149, 51,0 ),cvScalar( 252, 107, 51,0 ),
                       cvScalar( 254, 107, 51,0 ),cvScalar( 254, 50, 49,0 ),
                       cvScalar( 0x0, 0x0, 0x0,0 ),cvScalar( 0x0, 0x0, 0x0,0 ));

        if((ptcercle->compteur%4) == 0) // A METTRE EN TEST AU MOMENT DE L'INCREMENTATION
        {
            ptcercle->couleur = couleur[compteur/4];
        }
       ptcercle->rayon = RAYON-compteur/4;// reduction du cercle
  }

int main(void)
{
	int i = 0;
	cvCapture* ptvideo;
	IplImage* ptImage;
	cercle* premiercercle;

	srand(time(NULL)); // initialisation de rand
	ptvideo = loadVideo;
	premiercercle = NULL;

    cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Image originale", 50, 500);

	while(i < 25)
    {
        ptImage = captureImage(ptvideo);
        premier = createCircleRandomp(ptImage,premier);
        cvShowImage("Image originale", ptImage);
        cvWaitKey(1000);
        i = i+1;
    }

	cvReleaseImage(&ptImage);
	cvReleaseCapture(&capture);

	return 0;
}
