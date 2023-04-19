#include <stdio.h>
#include "error.h"
#include "page5.h"
#include <string.h>
#define NAMELEN 6
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

int formatname(int num, char * name)
{
	int i, j, len;
	sprintf(name, "%d", num);
	len = strlen(name);
	for(i=0; i<len; i++)
	{
		name[i+NAMELEN-len] = name[i];
	}
	for(i=0; i<NAMELEN-len; i++)
	{
		name[i] = '0';
	}
	return 0;
}

int creatconf(char * prjdir)
{
	FILE *fp, *fpb;
	mkdir(prjdir);
	chdir(prjdir);
	if((fp = fopen("./config.txt", "w")) == NULL)
    {
		error(3);
        return -1;
    }
	fclose(fp);
	if((fpb = fopen("./confb", "wb")) == NULL)
    {
		error(3);
        return -1;
    }
	fclose(fpb);
	chdir("../");
	return 0;
}

int openconf(char * prjdir, int *filenum, int *frnum)
{
	FILE *fp;
	chdir(prjdir);
	if((fp = fopen("./confb", "rb")) == NULL)
    {
		error(3);
        return -1;
    }
	fseek(fp, 0, 0);
	fread(filenum, 2, 1, fp);
	fread(frnum, 2, 1, fp);
	fclose(fp);
	chdir("../");
	return 0;
}

int updatenum(char * prjdir, int *filenum, int *frnum)
{
	FILE *fp;
	chdir(prjdir);
	if((fp = fopen("./confb", "wb")) == NULL)
    {
		error(3);
        return -1;
    }
	fseek(fp, 0, 0);
	fwrite(filenum, 2, 1, fp);
	fwrite(frnum, 2, 1, fp);
	fclose(fp);
	chdir("../");
	return 0;
}

int saveframe(char * prjdir, FRAME * framep,int frnum)
{
	int i;
	FILE *fp;
	chdir(prjdir);
	if((fp = fopen("./config.txt", "w")) == NULL)
    {
		error(3);
        return -1;
    }
	for(i=0; i<frnum; i++)
	{
		fprintf(fp, "%d %d %d %d %d %f %f %f %f\n", 
			framep[i].fileid, framep[i].cycles, 
			framep[i].dx, framep[i].dy, framep[i].dz, 
			framep[i].dA, framep[i].dB, framep[i].dC, framep[i].percent);
	}
	fclose(fp);
	chdir("../");
	return 0;
}

int loadframe(char * prjdir, FRAME * framep, int frnum)
{
	int i;
	FILE *fp;
	chdir(prjdir);
	if((fp = fopen("./config.txt", "r")) == NULL)
    {
		error(3);
        return -1;
    }
	for(i=0; i<frnum; i++)
	{
		fscanf(fp, "%d%d%d%d%d%f%f%f%f", 
			&framep[i].fileid, &framep[i].cycles, 
			&framep[i].dx, &framep[i].dy, &framep[i].dz, 
			&framep[i].dA, &framep[i].dB, &framep[i].dC, &framep[i].percent);
	}
	chdir("../");
	return 0;
}