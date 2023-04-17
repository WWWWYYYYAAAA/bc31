#ifndef _PAGE5_H_
#define _PAGE5_H_

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

#endif