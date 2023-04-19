#ifndef _PAGE5_H_
#define _PAGE5_H_

#define XOFF 140
#define YOFF 60
#define XSIZE 440
#define YSIZE 360
typedef struct Pixel
{
    int far x;
    int far y;
    int far z;
    int far color;
    int far id;
}PIX;

int page5();
int editpic(int *nx, int *ny, int *nb);
int picload(char * path); //ÆúÓÃ
int tdviwer(int *nx, int *ny, int *nb);
int tdtrans(int *nx, int *ny, int *nb);
int tdpreviwer(int *nx, int *ny, int *nb, PIX *pixlist, int pixnum);
int filelink(int *nx, int *ny, int *nb);
int clearpixlist(PIX * pixlist, int * pixnum, int num);

#endif