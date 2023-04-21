#ifndef _ASTRUCT_H_
#define _ASTRUCT_H_

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

#endif