#include <stdio.h>

//#include <alloc.h>
int stream_read(char * path, int (*dronelist)[5])
{
	int dronenum;
	int * head;
	FILE * fp;
	if ((fp = fopen(path, "rb")) == NULL)
    {
        printf("not open");
        return -1;
    }
	fseek(fp, 0, 0);
	head = &dronelist[0][0];
	fread(&dronenum, 2, 1, fp);
	fread(head, 2, dronenum*4, fp);
	fclose(fp);
	return 0;
}

int stream_write(char * path, int (*dronelist)[5], int dronenum)
{
	FILE * fp;
	int * head;
	if ((fp = fopen(path, "rb")) == NULL)
    {
        printf("not open");
        return -1;
    }
	head = &dronelist[0][0];
	fseek(fp, 0, 0);
	fwrite(&dronenum, 2, 1, fp);
	fread(head, 2, dronenum*4, fp);
	fclose(fp);
	return 0;
}
