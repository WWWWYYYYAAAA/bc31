#include <stdio.h>
#include "error.h"
//#include <alloc.h>
//int stream_read(char * path, int (*dronelist)[5])
int stream_read(char * path, int far *dronelist)
{
	int dronenum;
	int far * head;
	FILE * fp;
	if ((fp = fopen(path, "rb")) == NULL)
    {
        error(3);
        return -1;
    }
	fseek(fp, 0, 0);
	head = dronelist;
	fread(&dronenum, 2, 1, fp);
	fread(head, 2, dronenum*5, fp);
	fclose(fp);
	return 0;
}

//int stream_write(char * path, int (*dronelist)[5], int dronenum)
int stream_write(char * path, int far *dronelist, int dronenum)
{
	int i, j;
	FILE * fp;
	int far * head;
	if ((fp = fopen(path, "wb")) == NULL)
    {
		error(3);
        return -1;
    }
	head = dronelist;
	fseek(fp, 0, 0);
	fwrite(&dronenum, 2, 1, fp);
	fwrite(head, 2, dronenum*5, fp);
	fclose(fp);
	return 0;
}