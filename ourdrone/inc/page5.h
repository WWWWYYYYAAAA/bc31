#ifndef _PAGE5_H_
#define _PAGE5_H_

int page5();
int editpic(int *nx, int *ny, int *nb);
int picload(char * path);
int tdviwer(int *nx, int *ny, int *nb);
int tdtrans(int *nx, int *ny, int *nb);

typedef struct Pixel
{
    int far x;
    int far y;
    int far z;
    int far color;
    int far id;
}PIX;

#endif