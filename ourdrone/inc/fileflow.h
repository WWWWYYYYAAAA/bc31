#ifndef _FILEFLOW_H_
#define _FILEFLOW_H_

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

#endif