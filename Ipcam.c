#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
//#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_TTF.h> 


IplImage*  binaire (IplImage* img)
{
    uchar *data;
    data     = (uchar *)img->imageData;
    int i;
    int s;
    s = 127;
    //printf(" --> 3 : Entrez votre seuil\n");
  // scanf("%d", &s); 
    // Parcours de TOUS les pixels.
    /*img = cvLoadImage("img",0);
      if(!img)
      {
        printf("Impossible d'ouvrir l'image");
        exit(0);
      }
      cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
      cvMoveWindow("Image originale", 50, 500);
      cvShowImage("Image originale", img);*/
    //IplImage *imgnvg = cvCreateImage(cvGetSize(img), img->depth, 1);
    //Mat gray;
    //cvtColor( img, img, CV_BGR2GRAY);
    for(i = 0; i< ((img->height * img->width)*3); i++)
    {
      // On binarise les pixels.
      if(data[i] <= s) {
          data[i] = 0;
      }
      if(data[i] > s) {
          data[i] = 255;
      }
    }
 return img;
}	
     
//void invert (IplImage* img)
//{
  //assert (img->depth == IPL_DEPTH_8U && img->nChannels == 1);
  // TODO 
  //return img;
//}

/*IplImage*  comparateur (IplImage* img1,IplImage* img5,IplImage* img6)
{
    uchar *data,*data5,*data6;
    data     = (uchar *)img1->imageData;
    data5     = (uchar *)img5->imageData;
    data6     = (uchar *)img6->imageData;
    int i;
    for(i = 0; i< img1->height * img1->width; i++)
    {
      // On compare les pixels.
      if(data[i] == data5[i]) {
          data6[i] = 0;
      }
      if(data[i] != data5[i]) {
          data6[i] = 255;
      }
    }
  return img6;
}*/
     
int main(){
//CvCapture *camera =  cvCaptureFromFile("http://50.73.56.89/mjpg/video.mjpg"); // changer l'IP ICI
CvCapture *camera =  cvCaptureFromCAM(0);
if (camera==NULL) {
    printf("Impossible de récupérer le flux\n");
    exit(0);
}

cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
//cvMoveWindow("Camera", 100, 100);
while (cvWaitKey(100)!=atoi("q")){
    //IplImage *img=cvQueryFrame(camera);
    ///cvShowImage("Camera",img);
    //cvWaitKey(200);
    IplImage *img2=cvQueryFrame(camera);
    //IplImage *img3=cvQueryFrame(camera);
    //img2 = 
    //invert (img2);
    //IplImage *hvs;
    // Create the hsv image
    //hsv = cvCloneImage(img2);
    //cvCvtColor(img2, hsv, CV_BGR2HSV);
    SDL_SaveBMP (img2, "sortie.jpg"); 
    cvcvtColor(img2, img2, CV_RGB2GRAY);
    //binaire (img2);
    //comparateur (img,img2,img3);
    //cvShowImage("test3", img3);
    //cvShowImage("test1", img);
    cvShowImage("Camera", img2);
}
cvReleaseCapture(&camera);
return 0;
}

