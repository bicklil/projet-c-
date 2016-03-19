#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <time.h> //pour le random

#define RAYON 20
#define NBCOULEUR 12
#define CHANGEMENT 7 // changement du rayon et de la couleur
#define FINDEVIE 49

 struct cercle{int x;
                int y;
                int rayon;
                CvScalar couleur;
                int compteur;
                struct cercle* suivant;
                struct cercle* precedent;};
                
typedef struct cercle cercle;

void choixNiveaux() // mettre les variables de difficultés en parametre en pointeur (changement,fin de vie,...)
{
	int choix;
	printf("CHOIX DU NIVEAU :\n     - 1-FACILE\n     - 2-INTERMEDIARE\n     - 3-DIFFICILE\n");
	scanf("%d",&choix);
	switch(choix)
	{
		case 1:
		break;
		case 2:
		break ;
		case 3:
		break ;
		default:
		break ;
	}
}


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
// supprime le cercle de la chaine
{
	cercle* ptsuivant;
    if ((actuel->precedent) == NULL)
    {
    	if ((actuel->suivant) == NULL)
    	{
    		return NULL;
    	}
    	else
    	{
    		ptsuivant = (actuel->suivant);
        	((actuel->suivant)->precedent) = NULL;
        	actuel = actuel->suivant;
        	free(actuel);
        	return ptsuivant;
        }
    }
    if ((actuel->suivant) == NULL)
    {
        ((actuel->precedent)->suivant) = NULL;
        free(actuel);
        return actuel->precedent;
    }
    ((actuel->suivant)->precedent) = actuel->precedent;
    ((actuel->precedent)->suivant) = actuel->suivant;
    free(actuel);
    return ptsuivant;

}

IplImage* captureImage(CvCapture* capture)
{
	IplImage* ptImage = 0; // Pointeur sur une image OpenCV
	ptImage = cvQueryFrame(capture);
	if(ptImage==NULL)
	{
		printf("Impossible d'ouvrir l'image");
		exit(0);
	}
	return ptImage;
}

CvCapture* loadVideo()
{
    CvCapture* capture = NULL;
    while(capture==NULL)
    {
        capture=cvCaptureFromCAM(0); // mettre l'adresse de la video connait pas
        if (capture==NULL)
        {
            printf("Ouverture du flux vidéo impossible !\n");
        }
    }
    return capture;
}
cercle* createCircleRandomp(IplImage* image,cercle* premier)
{
	int hauteur,largeur;
	int aleaLargeur,aleaHauteur,aleapos;
	cercle *ptcercle;
	
	ptcercle = (cercle*)malloc(sizeof(cercle));
	hauteur = image->height;
	largeur = image->width;
    
    if (ptcercle==NULL)
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
	
	ptcercle->x = aleaLargeur;
	ptcercle->y = aleaHauteur;
	ptcercle->rayon = RAYON;
	ptcercle->couleur = cvScalar( 20, 148, 20,0 );
	ptcercle->compteur = 0;
	ajoutCercle(premier,ptcercle);
	
	return ptcercle;

}

cercle*	modifiercercle(cercle* ptcercle, IplImage* ptImage)
	{
      	CvScalar couleur[NBCOULEUR] = {cvScalar( 20, 148, 20,0 ),cvScalar( 179, 255, 49,0 ),
               cvScalar( 213, 220, 51,0 ),cvScalar( 233, 185, 52,0 ),
               cvScalar( 246, 149, 51,0 ),cvScalar( 252, 107, 51,0 ),
               cvScalar( 254, 107, 51,0 ),cvScalar( 254, 50, 49,0 ),
               cvScalar( 0x0, 0x0, 0x0,0 ),cvScalar( 0x0, 0x0, 0x0,0 )};//couleur a revoir ca vva du vert au bleu ...
		int modif=0;
		cercle* premiercercle=ptcercle;
		while(ptcercle!=NULL)
		{	
			modif=0;
			(ptcercle->compteur)++;
		    if ((ptcercle->compteur)==FINDEVIE)//destruction du mailllon
		    {
		    	if (premiercercle==ptcercle)
		    	{
		    		ptcercle=supprimerCercle(ptcercle);
		    		premiercercle=ptcercle;
		    	}
				else
				{
					ptcercle=supprimerCercle(ptcercle);
				}
		    	modif=1;
		    }
		    if((((ptcercle->compteur)%CHANGEMENT)==0)&&(modif==0))//modification du maillon
		    {
				ptcercle->couleur = couleur[(ptcercle->compteur)/CHANGEMENT];
				ptcercle->rayon = RAYON-(ptcercle->compteur)/(CHANGEMENT/2);
				cvCircle(ptImage, cvPoint ( (ptcercle->x) , (ptcercle->y) ) ,(ptcercle->rayon),(ptcercle->couleur),-1,1,0);
				cvShowImage("Image originale", ptImage);
				if(ptcercle->suivant==NULL)
				{
					return premiercercle;
				}
				else
				{
					ptcercle=(ptcercle->suivant);
					modif=1;	
		    	}
		    }
		    if(modif==0);//incrementation du maillon 
		    {
				cvCircle(ptImage, cvPoint ( ptcercle->x , ptcercle->y ) ,ptcercle->rayon,ptcercle->couleur,-1,0,0);
				cvShowImage("Image originale", ptImage);
				ptcercle=ptcercle->suivant;	    
		    }

		}
		return premiercercle;
	}
	
int cercleToucher(cercle* ptcercle,int* score)
{
	int point_gagner;
	point_gagner=FINDEVIE-(ptcercle->compteur);
	*score=*score + point_gagner;
	ptcercle=supprimerCercle(ptcercle);
	return ptcercle;
}

int main(void)
{
	int i = -1;
	//int score;
	CvCapture* ptvideo;
	IplImage* ptImage;
	cercle* premiercercle;

	srand(time(NULL)); // initialisation de rand

	ptvideo = loadVideo();
	premiercercle = NULL;

    cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Image originale", 0, 0);
	
	choixNiveaux();

	while(1)
    {
    	i++;
        ptImage = captureImage(ptvideo);
        cvShowImage("Image originale", ptImage);        
        if ((i%6)==0)
        {
      		premiercercle = createCircleRandomp(ptImage,premiercercle);
      		printf("%d %p\n",i,premiercercle);
        }
        premiercercle = modifiercercle( premiercercle , ptImage ) ;
        
        cvWaitKey(24);
    }

	cvReleaseImage(&ptImage);
	cvReleaseCapture(&ptvideo);

	return 0;
}
