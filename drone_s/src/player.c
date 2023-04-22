#include "player.h"

int play(char * prjdir)
{
    PIX pixlist1[LISTSIZE], pixlist2[LISTSIZE], nx, ny, nb;
	FRAME STEP[200];
    char fname[10]={0};
    int pixnum1=0, pixnum2=0, pause=0, out=0, i, j, k, filenum=0, frnum=0, vector=1, stp=0;
    int X, Y, Z, X1, Y1, Z1;
    clearpixlist(pixlist1, &pixnum1, LISTSIZE);
    clearpixlist(pixlist2, &pixnum2, LISTSIZE);
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
                        i = STEP[stp-1].cycles;
                        for(j=1; j<41; j++)             //frame
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
                               if((((j*X1 + (40-j)*X)/40)>50&&((j*X1 + (40-j)*X)/40)<590)&&(((j*Z1 + (40-j)*Z)/40)>30&&((j*Z1 + (40-j)*Z)/40)<450))
                                {
                                    ball((j*X1 + (40-j)*X)/40, (j*Z1 + (40-j)*Z)/40, 3, pixlist1[k].color);
                                }
                            }
                            delay(100);
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx*i, DY = STEP[stp].dy*i, DZ = STEP[stp].dz*i;
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
                chdir("..");
                vector = 2;
            }
            else if(vector==2)
            {
                chdir(prjdir);
                if(stream_read(fname, pixlist2, &pixnum2) != -1)
                {
                    if(stp>0&&STEP[stp-1].fileid != STEP[stp].fileid)
                    {
                        i = STEP[stp-1].cycles;
                        for(j=1; j<41; j++) //frame
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
                               if((((j*X1 + (40-j)*X)/40)>50&&((j*X1 + (40-j)*X)/40)<590)&&(((j*Z1 + (40-j)*Z)/40)>30&&((j*Z1 + (40-j)*Z)/40)<450))
                                {
                                    ball((j*X1 + (40-j)*X)/40, (j*Z1 + (40-j)*Z)/40, 3, pixlist2[k].color);
                                }
                            }
                            delay(100);
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx*i, DY = STEP[stp].dy*i, DZ = STEP[stp].dz*i;
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
                chdir("..");
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

int playtofile(char * prjdir)
{
    PIX pixlist1[LISTSIZE], pixlist2[LISTSIZE];
	FRAME STEP[200];
    FILE *fpout;
    char fname[20]={0}, outname[20] = {0};
    int pixnum1=0, pixnum2=0, out=0, i, j, k, filenum=0, frnum=0, vector=1, stp=0;
    int X, Y, Z, X1, Y1, Z1, outnum = 0;
    if(chdir(prjdir)==0)
    {
        mkdir("output");
        chdir("..");
    }
    clearpixlist(pixlist1, &pixnum1, LISTSIZE);
    clearpixlist(pixlist2, &pixnum2, LISTSIZE);
    if(openconf(prjdir, &filenum, &frnum)!= -1&& loadframe(prjdir, STEP, frnum) != -1)
	{
        while (1)
        {
            formatname(STEP[stp].fileid, fname);
            if(vector == 1)
            {
                if(chdir(prjdir)==0)
                {
                if(stream_read(fname, pixlist1, &pixnum1) != -1)
                {
                    if(stp>0&&STEP[stp-1].fileid != STEP[stp].fileid)
                    {   
                        i = STEP[stp-1].cycles;
                        for(j=1; j<41; j++)             //frame
                        {
                            float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                            int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                            if(chdir("output")==0)
                            {
                            outnum++;
                            formatname(outnum, outname);
                            if((fpout = fopen(outname, "w")) == NULL)
                            {
                                error(3);
                                return -1;
                            }
                            fprintf(fpout, "%d\n", pixnum1);
    
                            //setfillstyle(SOLID_FILL, BLACK);
                            //bar(50, 30, 590, 450);
                            for(k=0; k<pixnum1; k++)
                            {
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSIZE/2+DX, DY, YSIZE/2+DZ, STEP[stp-1].percent);
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), 0, 0, &X1, &Y1, &Z1, 0, 0, 0, 1);
                                move_3d_yaxis((float)X1, (float)Y1, (float)Z1, C, &X1, &Y1, &Z1, XSIZE/2, 0, YSIZE/2, STEP[stp].percent);
                               // if((((j*X1 + (40-j)*X)/40)>50&&((j*X1 + (40-j)*X)/40)<590)&&(((j*Z1 + (40-j)*Z)/40)>30&&((j*Z1 + (40-j)*Z)/40)<450))
                                {
                                    //ball((j*X1 + (40-j)*X)/40, (j*Z1 + (40-j)*Z)/40, 3, pixlist1[k].color);
                                    fprintf(fpout, "%d %d %d %d %d\n", (j*X1 + (40-j)*X)/40,  (j*Y1 + (40-j)*Y)/40, (j*Z1 + (40-j)*Z)/40, pixlist1[k].color, pixlist1[k].id);
                                }
                            }
                            fclose(fpout);
                            chdir("..");
                            }
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx*i, DY = STEP[stp].dy*i, DZ = STEP[stp].dz*i;
                        if(chdir("output") == 0)
                        {
                        outnum++;
                        formatname(outnum, outname);
                        //strcat(outname, ".txt");
                        if((fpout = fopen(outname, "w")) == NULL)
                        {
                            error(3);
                            return -1;
                        }
                        fprintf(fpout, "%d\n", pixnum1);
                        
                       // setfillstyle(SOLID_FILL, BLACK);
                        //bar(50, 30, 590, 450);
                        for(k=0; k<pixnum1; k++)
                        {
                            
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
								move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSIZE/2+DX, DY, YSIZE/2+DZ, STEP[stp].percent);
                                //if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    //ball(X, Z, 3, pixlist1[k].color);
                                    fprintf(fpout, "%d %d %d %d %d\n", X, Y, Z, pixlist1[k].color, pixlist1[k].id);
                                }
                               
                            
                        }
                        fclose(fpout);
                        chdir("..");
                        }
                    }
                }
                chdir("..");
                vector = 2;
                }
            }
            else if(vector==2)
            {
                if(chdir(prjdir)==0)
                {
                if(stream_read(fname, pixlist2, &pixnum2) != -1)
                {
                    if(stp>0&&STEP[stp-1].fileid != STEP[stp].fileid)
                    {
                        i = STEP[stp-1].cycles;
                        for(j=1; j<41; j++) //frame
                        {
                            float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                            int DX = STEP[stp].dx, DY = STEP[stp].dy, DZ = STEP[stp].dz;
                            if(chdir("output")==0)
                            {
                            outnum++;
                            formatname(outnum, outname);
                           //strcat(outname, ".txt");
                            if((fpout = fopen(outname, "w")) == NULL)
                            {
                                error(3);
                                return -1;
                            }
                            fprintf(fpout, "%d\n", pixnum2);
                            
                            //setfillstyle(SOLID_FILL, BLACK);
                           // bar(50, 30, 590, 450);
                            for(k=0; k<pixnum2; k++)
                            {
                                move_3d_p((float)(pixlist1[k].x-XSIZE/2), (float)(pixlist1[k].y), (float)(pixlist1[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSIZE/2+DX, DY, YSIZE/2+DZ, STEP[stp-1].percent);
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), 0, 0, &X1, &Y1, &Z1, 0, 0, 0, 1);
                                move_3d_yaxis((float)X1, (float)Y1, (float)Z1, C, &X1, &Y1, &Z1, XSIZE/2, 0, YSIZE/2, STEP[stp].percent);
                                //if((((j*X1 + (40-j)*X)/40)>50&&((j*X1 + (40-j)*X)/40)<590)&&(((j*Z1 + (40-j)*Z)/40)>30&&((j*Z1 + (40-j)*Z)/40)<450))
                                {
                                    //ball((j*X1 + (40-j)*X)/40, (j*Z1 + (40-j)*Z)/40, 3, pixlist2[k].color);
                                    fprintf(fpout, "%d %d %d %d %d\n", (j*X1 + (40-j)*X)/40,  (j*Y1 + (40-j)*Y)/40, (j*Z1 + (40-j)*Z)/40, pixlist2[k].color, pixlist2[k].id);
                                }
                            }
                            fclose(fpout);
                            chdir("..");
                            }
                        }
                    }
                    for(i=0; i<STEP[stp].cycles; i++) //frame
                    {
                        float A = 1.0 * i * STEP[stp].dA, B = 1.0 * i * STEP[stp].dB, C = 1.0 * i * STEP[stp].dC;
                        int DX = STEP[stp].dx*i, DY = STEP[stp].dy*i, DZ = STEP[stp].dz*i;
                        if(chdir("output")==0)
                        {
                        outnum++;
                        formatname(outnum, outname);
                       // strcat(outname, ".txt");
                        if((fpout = fopen(outname, "w")) == NULL)
                        {
                            error(3);
                            return -1;
                        }
                        fprintf(fpout, "%d\n", pixnum2);
                        
                        //setfillstyle(SOLID_FILL, BLACK);
                        //bar(50, 30, 590, 450);
                        for(k=0; k<pixnum2; k++)
                        {
                            
                                move_3d_p((float)(pixlist2[k].x-XSIZE/2), (float)(pixlist2[k].y), (float)(pixlist2[k].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
                                move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XSIZE/2+DX, DY, YSIZE/2+DZ, STEP[stp].percent);
                                //if((X>50&&X<590)&&(Z>30&&Z<450))
                                {
                                    //ball(X, Z, 3, pixlist2[k].color);
                                     fprintf(fpout, "%d %d %d %d %d\n", X, Y, Z, pixlist2[k].color, pixlist2[k].id);
                                }
                            
                        }
                        fclose(fpout);
                        chdir("..");
                        }
                    }
                }
                chdir("..");
                }
                vector = 1;
            }
            stp ++;
            if(stp==frnum)
            {
                FILE * FCO;
                if(chdir(prjdir)==0)
                {
                if(chdir("output")==0)
                {
                if((FCO = fopen("./count.txt", "w")) == NULL)
                {
                    error(3);
                    return -1;
                }
                fprintf(FCO, "%d\n", outnum);
                fclose(FCO);
                chdir("..");
                }
                chdir("..");
                }
                //printf("done");
                break;
            }
            //setfillstyle(SOLID_FILL, BLACK);
            //bar(50, 30, 590, 450);
        }
    }
    
    return 0;
}

