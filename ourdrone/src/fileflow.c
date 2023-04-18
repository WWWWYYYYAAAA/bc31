#include <stdio.h>
#include "error.h"
#include "page5.h"

//#include <alloc.h>
//int stream_read(char * path, int (*dronelist)[5])
int stream_read(char * path, PIX *pixlist,  int *dronenump)
{
	int dronenum, k;
	int far * head;
	FILE * fp;
	if ((fp = fopen(path, "rb")) == NULL)
    {
        error(3);
        return -1;
    }
	fseek(fp, 0, 0);
	
	fread(dronenump, 2, 1, fp);
	for(k=0; k<*dronenump; k++)
	{
		fread((pixlist+k), 10, 1, fp);
	}
	//printf("num: %d", *dronenump);
	fclose(fp);
	return 0;
}

//int stream_write(char * path, int (*dronelist)[5], int dronenum)
int stream_write(char * path, PIX *pixlist, int dronenum)
{
	int k;
	FILE * fp;
	int far * head;
	if ((fp = fopen(path, "wb")) == NULL)
    {
		error(3);
        return -1;
    }
	//head = dronelist;
	fseek(fp, 0, 0);
	fwrite(&dronenum, 2, 1, fp);

	for(k=0; k<dronenum; k++)
	{
		fwrite((pixlist+k), 10, 1, fp);
	}
	//fwrite(head, 2, dronenum*5, fp);
	fclose(fp);
	return 0;
}