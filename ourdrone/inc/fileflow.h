#ifndef _FILEFLOW_H_
#define _FILEFLOW_H_

int stream_read(char * path, int (*dronelist)[5]);
int stream_write(char * path, int (*dronelist)[5], int dronenum);

#endif