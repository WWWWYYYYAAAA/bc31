#ifndef _TDEDIT_H_
#define _TDEDIT_H_


int XOR_mark(int x1, int y1, int x2, int y2);
int filelink(int *nx, int *ny, int *nb);
int outfinal(int *nx, int *ny, int *nb);
int tdpreviwer(int *nx, int *ny, int *nb, PIX *pixlist, int pixnum);
int tdtrans(int *nx, int *ny, int *nb);

#endif