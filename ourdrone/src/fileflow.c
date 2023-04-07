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
	fread(head, 2, dronenum*5, fp);
	fclose(fp);
	return 0;
}

int stream_write(char * path, int (*dronelist)[5], int dronenum)
{
	int i, j;
	FILE * fp;
	int * head;
	if ((fp = fopen(path, "wb")) == NULL)
    {
        printf("not open");
        return -1;
    }
	printf("stream_write\n");
	for(i=0; i<2; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("%d	", dronelist[i][j]);
		}
		printf("\n");
	}
	head = &dronelist[0][0];
	fseek(fp, 0, 0);
	fwrite(&dronenum, 2, 1, fp);
	fwrite(head, 2, dronenum*5, fp);
	fclose(fp);
	return 0;
}