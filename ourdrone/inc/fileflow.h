#ifndef _FILEFLOW_H_
#define _FILEFLOW_H_

//int stream_read(char * path, int (*dronelist)[5]);
//int stream_write(char * path, int (*dronelist)[5], int dronenum);
//int stream_read(char * path, int far *dronelist);
int stream_read(char * path, int far *dronelist,  int *dronenump);
int stream_write(char * path, int far *dronelist, int dronenum);

#endif