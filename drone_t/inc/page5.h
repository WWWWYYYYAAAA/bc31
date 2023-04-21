#ifndef _PAGE5_H_
#define _PAGE5_H_

#define XOFF 140
#define YOFF 60
#define XSIZE 440
#define YSIZE 360
#define LISTSIZE 600
#define BASEX 150
#define BASEY 70
typedef struct Pixel
{
    int far x;
    int far y;
    int far z;
    int far color;
    int far id;
}PIX;

typedef struct Frame
{
    int far fileid;
    int far cycles;
    int far dx;
    int far dy;
    int far dz;
    float far dA;
    float far dB;
    float far dC;
    float far percent;

}FRAME;


int page5();
int editpic(int *nx, int *ny, int *nb);
int picload(char * path); //����
int tdviwer(int *nx, int *ny, int *nb);
int clearpixlist(PIX * pixlist, int * pixnum, int num);

#endif