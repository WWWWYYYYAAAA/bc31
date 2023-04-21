#ifndef _FILEFLOW_H_
#define _FILEFLOW_H_

#include <stdio.h>
#include "error.h"
#include "page5.h"
#include <string.h>
#include <dir.h>
#include "astruct.h"
#define NAMELEN 6

// typedef struct Frame
// {
//     int far fileid;
//     int far cycles;
//     int far dx;
//     int far dy;
//     int far dz;
//     float far dA;
//     float far dB;
//     float far dC;
//     float far percent;

// }FRAME;

//int stream_read(char * path, int (*dronelist)[5]);
//int stream_write(char * path, int (*dronelist)[5], int dronenum);
//int stream_read(char * path, int far *dronelist);
int stream_read(char * path, PIX *pixlist,  int *dronenump);
int stream_write(char * path, PIX *pixlist, int dronenum);
int formatname(int num, char * name);
int openconf(char * prjdir, int *filenum, int *frnum);
int updatenum(char * prjdir, int *filenum, int *frnum);
int saveframe(char * prjdir, FRAME * framep,int frnum);
int loadframe(char * prjdir, FRAME * framep, int frnum);
int getnum(char * prjdir);
int readdronetxt(char * path, PIX *pixlist, int * pixnum);
//int getfilenum(char * prjdir, int *filenum);

#endif