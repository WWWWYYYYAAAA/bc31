#include <stdlib.h>
#include <stdio.h>
#include "TD.h"
#include "visual.h"
#include "page5.h"
#include "fileflow.h"
#include "mouse.h"
#include <dir.h>
#include <graphics.h>

#define XSCREEN1 100
#define XSCREEN2 540
#define YSCREEN1 60
#define YSCREEN2 420

int play(char * prjdir, int step)
{
    PIX pixlist1[400], pixlist2[400], nx, ny, nb;
	FRAME STEP[200];
    char fname[10]={0};
    int pixnum1=0, pixnum2=0, pause=0, out=0, i, j, k, filenum=0, frnum=0, vector=1, stp=0;
    int X, Y, Z, X1, Y1, Z1;
    clearpixlist(pixlist1, &pixnum1, 400);
    clearpixlist(pixlist2, &pixnum2, 400);
    if(openconf(prjdir, &filenum, &frnum)!= -1&& loadframe(prjdir, STEP, frnum) != -1)
	{
        while (1)
        {
            newmouse(&nx, &ny, &nb);
            formatname(STEP[stp].fileid, fname);
            if(vector == 1)
            {
                chdir(prjdir);
                if(stream_read(fname, pixlist1, &pixnum1) != -1)
                {
                    if(stp>0&&STEP[stp-1].fileid != STEP[stp].fileid)
                    {   
                        i = STEP[step-1].cycles;
                        for(j=1; j<21; j++)             //frame
                        {
                            float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                            int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(50, 30, 590, 450);
                            newmouse(&nx, &ny, &nb);
                            for(k=0; k<pixnum1; k++)
                            {
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSCREEN1+XSIZE/2+DX, DY, YSCREEN1+YSIZE/2+DZ, STEP[stp-1].percent);
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), 0, 0, &X1, &Y1, &Z1, 0, 0, 0, 1);
                                move_3d_yaxis((float)X1, (float)Y1, (float)Z1, C, &X1, &Y1, &Z1, XSCREEN1+XSIZE/2, 0, YSCREEN1+YSIZE/2, STEP[stp].percent);
                                if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    ball((j*X1 + (20-j)*X)/20, (j*Z1 + (20-j)*Z)/20, 3, pixlist1[k].color);
                                }
                            }
                            delay(100);
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(50, 30, 590, 450);
                        newmouse(&nx, &ny, &nb);
                        for(k=0; k<pixnum1; k++)
                        {
                            
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
								move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSCREEN1+XSIZE/2+DX, DY, YSCREEN1+YSIZE/2+DZ, STEP[stp].percent);
                                if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    ball(X, Z, 3, pixlist1[k].color);
                                }
                               
                            
                        }
                        delay(30);
                    }
                }
                chdir("../");
                vector = 2;
            }
            else if(vector==2)
            {
                chdir(prjdir);
                if(stream_read(fname, pixlist2, &pixnum2) != -1)
                {
                    if(stp>0&&STEP[stp-1].fileid != STEP[stp].fileid)
                    {
                        i = STEP[step-1].cycles;
                        for(j=1; j<21; j++) //frame
                        {
                            float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                            int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(50, 30, 590, 450);
                            newmouse(&nx, &ny, &nb);
                            for(k=0; k<pixnum2; k++)
                            {
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSCREEN1+XSIZE/2+DX, DY, YSCREEN1+YSIZE/2+DZ, STEP[stp-1].percent);
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), 0, 0, &X1, &Y1, &Z1, 0, 0, 0, 1);
                                move_3d_yaxis((float)X1, (float)Y1, (float)Z1, C, &X1, &Y1, &Z1, XSCREEN1+XSIZE/2, 0, YSCREEN1+YSIZE/2, STEP[stp].percent);
                                if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    ball((j*X1 + (20-j)*X)/20, (j*Z1 + (20-j)*Z)/20, 3, pixlist2[k].color);
                                }
                            }
                            delay(100);
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(50, 30, 590, 450);
                        newmouse(&nx, &ny, &nb);
                        for(k=0; k<pixnum2; k++)
                        {
                            
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSCREEN1+XSIZE/2+DX, DY, YSCREEN1+YSIZE/2+DZ, STEP[stp].percent);
                                if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    ball(X, Z, 3, pixlist2[k].color);
                                }
                            
                        }
                        delay(30);
                    }
                }
                chdir("../");
                vector = 1;
            }
            stp ++;
            if(stp==frnum)
            {
                stp = 0;
            }
            delay(30);
            setfillstyle(SOLID_FILL, BLACK);
            bar(50, 30, 590, 450);
        }
    }
    
    return 0;
}
