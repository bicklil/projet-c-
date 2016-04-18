#ifndef TRAITEMENT
	#define TRAITEMENT

	#include <stdio.h>
	#include <stdlib.h>
	#include <opencv2/core/core.hpp>
	#include <opencv2/highgui/highgui_c.h>
	#include <opencv2/imgproc/imgproc_c.h>
	#include <time.h>
	#define RAYON 20 // radius de la bulle
	#define NBCOULEUR 8 // nombre de couleur préparé pour les bulles voir modifiercerlce
	#define DUREEPARTIE 200 // chiffre au pif 
	
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

	
	cercle* ajoutCercle(cercle* premier,cercle* actuel);
	cercle* supprimerCercle(cercle* actuel);
	IplImage* creationImage(IplImage* ptImage,int x,int y , int rayon);
	CvHistogram* calculHistogramme(IplImage* ptImage);
	int cercleToucherTest(IplImage* ptImage,cercle* ptCercle, float precision);
	cercle* cercleToucherPoint(cercle* ptCercle,int* ptScore,paradiff *ptNiveau);
	IplImage* captureImage(CvCapture* capture);
	CvCapture* loadVideo();
	cercle* createCircleRandomp(IplImage* ptImage,cercle* ptPremier);
	cercle*	modifiercercle(cercle* ptCercle, IplImage* ptImage, int* ptScore, paradiff *ptNiveau, float precision);


#endif
