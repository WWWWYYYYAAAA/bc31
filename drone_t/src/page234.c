#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include "printg.h"
#include "TD.h"
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include "page5.h"
#include "fileflow.h"
#include <dir.h>
#include "error.h"
#include "input.h"

#define X0 70
#define Y0 30

extern MX, MY;

// int example(float AR, float BR, int Xoffset,int Zoffset,int Yoffset, int sizeP, int sizeB)
// {
// 		int i, j, size, pic1x=0, pic1y=0;
// 		int state = 0;
// 		float a, b, d;
// 		float tix, tiy, tiz, tin;
// 		int tempx, tempy, tempz, temp;
// 		int k, l, count;
// 		float cube33[27][4];
// 		int cube33out[27][4] ={{0}};
// 		int enableM = 1, enableC = 0, resetM = 0, resetC = 0, flag = 0;
// 		void far * pic1;
// 		count = 0;
// 		for(a=0; a<3; a++)
// 		{
// 			for(b=0; b<3; b++)
// 			{
// 				for(d=0; d<3; d++)
// 				{
// 					cube33[count][0] = a-1;
// 					cube33[count][1] = b-1;
// 					cube33[count][2] = d-1;
// 					cube33[count][3] = count;
// 					count++;
// 				}
// 			}
// 		}
// 		//size = imagesize(0, 0, 150, 150);
// 	//update
// 	{
// 		for(i=0; i<27; i++)
// 			{
// 					move_3d(cube33[i][0]*sizeP, cube33[i][1]*sizeP, cube33[i][2]*sizeP, AR, BR, &cube33out[i][0], &cube33out[i][1], &cube33out[i][2], Xoffset, Yoffset, Zoffset);
// 					cube33out[i][3] = i;
// 			}
// 			for(i=0; i<26; i++)
// 			{
// 				for(j=0; j<26-i; j++)
// 				{
// 					if(cube33out[j][1]>cube33out[j+1][1])
// 					{
// 						tempx = cube33out[j][0];
// 						tempy = cube33out[j][1];
// 						tempz = cube33out[j][2];
// 						temp = cube33out[j][3];
// 						cube33out[j][0] = cube33out[j+1][0];
// 						cube33out[j][1] = cube33out[j+1][1];
// 						cube33out[j][2] = cube33out[j+1][2];
// 						cube33out[j][3] = cube33out[j+1][3];
// 						cube33out[j+1][0] = tempx;
// 						cube33out[j+1][1] = tempy;
// 						cube33out[j+1][2] = tempz;
// 						cube33out[j+1][3] = temp;
// 						tix = cube33[j][0];
// 						tiy = cube33[j][1];
// 						tiz = cube33[j][2];
// 						tin = cube33[j][3];
// ;						cube33[j][0] = cube33[j+1][0];
// 						cube33[j][1] = cube33[j+1][1];
// 						cube33[j][2] = cube33[j+1][2];
// 						cube33[j][3] = cube33[j+1][3];
// 						cube33[j+1][0] = tix;
// 						cube33[j+1][1] = tiy;
// 						cube33[j+1][2] = tiz;
// 						cube33[j+1][3] = tin;
// 					}
// 				}
// 			}
// 			for(i=0; i<27; i++)
// 			{
// 				if(cube33[i][0] > 0 && cube33[i][1] > 0 && cube33[i][2] > 0)
// 					ball(cube33out[i][0], cube33out[i][2], sizeB, RED);
// 				else if(cube33[i][0] > 0 && cube33[i][1] < 0 && cube33[i][2] > 0)
// 					ball(cube33out[i][0], cube33out[i][2], sizeB, YELLOW);
// 				else
// 					ball(cube33out[i][0], cube33out[i][2], sizeB, CYAN);
// 			}
// 			delay(20);
// 	}
// }
// //全屏放映
// int page2()
// {
// 	int nx , ny, nb;
// 	//begine
// 	float AR=0, BR=0;
// 	int Xoffset = 320, Zoffset = 240, Yoffset = 20;
// 	//end
// 	clrmous(ny, nx);
// 	bar2d(0, 0, 639, 479, BLACK);
// 	bar2d(610, 0, 639, 29, RED);
// 	button(610, 0, 639, 29, 0);
// 	bar_3d(0, 0, 609, 29, LIGHTGRAY, 0);
// 	printg(10, 5, 0, "part1/page2");
// 	//begine
		
// 	//end
// 	while(1)
// 	{
// 		//遮罩
// 			bar2d(240, 160, 400, 320, BLACK);
// 		newmouse(&nx, &ny, &nb);
// 		//begine
// 		example(AR, BR, Xoffset, Zoffset, Yoffset, 20, 3);
// 		AR+=0.01;
// 		BR+=0.01;
// 		//end
// 		if(mouse_press(610, 0, 639, 29) == 1)
// 		{
// 			button(610, 0, 639, 29, 1);
// 			return 1;
// 		}
// 	}
// }

// int page3()
// {
// 	int nx , ny, nb;
// 	clrmous(ny, nx);
// 	bar2d(0, 0, 639, 479, BLACK);
// 	bar2d(610, 0, 639, 29, RED);
// 	button(610, 0, 639, 29, 0);
// 	bar_3d(0, 0, 609, 29, LIGHTGRAY, 0);
// 	printg(10, 5, 0, "part2/page3");
// 	while(1)
// 	{
// 		newmouse(&nx, &ny, &nb);
// 		if(mouse_press(610, 0, 639, 29) == 1)
// 		{
// 			button(610, 0, 639, 29, 1);
// 			return 1;
// 		}
// 	}
// }

// int page4()
// {
// 	int nx , ny, nb;
// 	clrmous(ny, nx);
// 	bar2d(0, 0, 639, 479, BLACK);
// 	bar2d(610, 0, 639, 29, RED);
// 	button(610, 0, 639, 29, 0);
// 	bar_3d(0, 0, 609, 29, LIGHTGRAY, 0);
// 	printg(10, 5, 0, "part3/page4");
// 	while(1)
// 	{
// 		newmouse(&nx, &ny, &nb);
// 		if(mouse_press(610, 0, 639, 29) == 1)
// 		{
// 			button(610, 0, 639, 29, 1);
// 			return 1;
// 		}
// 	}
// }

int page234(char *prjdir)
{
	int pause=0, video=0, nx=MX, ny=MY, nb, mx, my, in=1, sr = 2;
    float speed = 1, globalfloat = 0;
    float speedrank[6] = {0.5, 0.75, 1, 1.5, 2, 3};
    //char prjdir[20] = "prj";
    int style[5] = {0, 2, 0, 0, 1};
    int pixnum, i, SP = 0,RO = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	int count = 0, globalnum = 0;
	PIX pixlist[LISTSIZE];
	char filename[10]={0};
	float A = 0, B = 0,C=0, percent = 1;
	int X, Y, Z;
    int pausepattern[8] = {295, 438, 305, 445, 295, 452, 295, 438};
    clearpixlist(pixlist, &pixnum, LISTSIZE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, 639, 479);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(598, 0, 639, 342);
    setfillstyle(SOLID_FILL, RED);
    bar(600, 0, 639, 39);
    setfillstyle(SOLID_FILL, BLUE);
    bar(600, 40, 639, 99);
    button(600, 0, 639, 39, 0);
    button(600, 40, 639, 99, 0);//���´�
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(600, 100, 639, 340);
    printg_cn(612, 120, WHITE, style, "RO");
	printg_cn(612, 160, WHITE, style, "PO");
	printg_cn(612, 200, WHITE, style, "SP");
	printg_cn(612, 240, WHITE, style, "RE");
	printg_cn(616, 280, WHITE, style, "+");
	printg_cn(616, 320, WHITE, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//SP
	button(600, 220, 639, 259, 0); 	//RE
	button(600, 260, 639, 299, 0); 	//+
	button(600, 300, 639, 340, 0); 	//-
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(80, 405, 520, 410);
    bar(285, 430, 315, 460);
    button(285, 430, 315, 460, 0); //��ͣ
    setfillstyle(SOLID_FILL, WHITE);
    bar(293, 438, 297, 452);
    bar(303, 438, 307, 452);
    setcolor(WHITE);
    line(330, 450, 480, 450); //����
    ball(330, 450, 2, WHITE);
    ball(360, 450, 2, WHITE);
    ball(390, 450, 4, DARKGRAY);//X1
    ball(420, 450, 2, WHITE);
    ball(450, 450, 2, WHITE);
    ball(480, 450, 2, WHITE);
    printg_cn(318,430, WHITE, style, "0.75");
    printg_cn(350,430, WHITE, style, "0.5");
    printg_cn(387,430, WHITE, style, "1");
    printg_cn(410,430, WHITE, style, "1.5");
    printg_cn(447,430, WHITE, style, "2");
    printg_cn(477,430, WHITE, style, "3");
    //setcolor(LIGHTGRAY);
    //rectangle(X0-7, Y0-7, X0+XSIZE+7, Y0+YSIZE+7);
    while (1)
    {
        if(mouse_press(600, 0, 639, 39) == 1)
        {
           button(600, 0, 639, 39, 1);
           delay(200);
           return 1;
        }
        else if(mouse_press(600, 40, 639, 99)==1) //BLUE
        {
            button(600, 40, 639, 99, 1);
            video = 0;
            globalnum = 0;
            globalfloat = 0;
        }
        else if(mouse_press(600, 100, 639, 139) == 1)	//RO
		{
			if(RO == 0)
				RO = 1;
			else if(RO == 1)
				RO = 0;
			//printf("RO %d\n", RO);
			clrmous(nx, ny);
			button(600, 100, 639, 139, 2*RO);
			delay(200);
		}
		else if(mouse_press(600, 140, 639, 179) == 1)	//PO
		{
			if(PO == 0)
				PO = 1;
			else if(PO == 1)
				PO = 0;
			clrmous(nx, ny);
			button(600, 140, 639, 179, 2*PO);
			delay(200);
		}
		else if(mouse_press(600, 180, 639, 219) == 1)	//SP
		{
			//button(600, 180, 639, 219, 1);
			if(SP == 0)
			{
				SP = 1;
				RO = 0;
				PO = 0;
			}
			else if(SP == 1)
				SP = 0;
			clrmous(nx, ny);
			button(600, 180, 639, 219, 2*SP);
			delay(200);
		}
		else if(mouse_press(600, 220, 639, 259) == 1)	//RE
		{
			button(600, 220, 639, 259, 1);
			DX = 0;
			DY = 0;
			A = 0;
			B = 0;
			C = 0;
			//update = 1;
			percent = 1;
			
		}
		else if(mouse_press(600, 260, 639, 299) == 1)	//+
		{
			button(600, 260, 639, 299, 1);
			percent += 0.05;
		}
		else if(mouse_press(600, 300, 639, 340) == 1)	//-
		{
			button(600, 300, 639, 340, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
			//update = 1;
		}
        else if(mouse_press(285, 430, 315, 460)==1)
        {//��ͣ
            button(285, 430, 315, 460, 1);
            delay(100);
            if(pause==0)
            {
                bar_3d(285, 430, 315, 460, LIGHTGRAY, 0);
                setfillstyle(SOLID_FILL, WHITE);
                //setcolor(WHITE);
                //line(295, 438, 305, 445);
                //line(295, 452, 305, 445);
                //line(295, 452, 295, 438);
                //floodfill(300, 445, WHITE);
                //putpixel(300, 445, RED);
                fillpoly(4, pausepattern);
                pause = 1;
            }
            else if(pause == 1)
            {
                bar_3d(285, 430, 315, 460, LIGHTGRAY, 0);
                setfillstyle(SOLID_FILL, WHITE);
                bar(293, 438, 297, 452);
                bar(303, 438, 307, 452);
                pause = 0;
            }
            delay(100);
        }
        else if(mouse_press_sup(80, 400, 520, 420, &mx, &my) == 1)  //������
        {
            globalfloat = 1.0 * (mx-80) / 440 * count;
            setfillstyle(SOLID_FILL, BLACK);
            bar(70, 400, 530, 420);
            setfillstyle(SOLID_FILL, LIGHTGRAY);
            bar(80, 405, 520, 410);
            ball(80+440.0*globalfloat/count, 408, 5, DARKGRAY);
        }
        else if(mouse_press_sup(320, 445, 490, 455, &mx, &my) == 1)  //����
        {
            clrmous(nx, ny);
            setfillstyle(SOLID_FILL, BLACK);
            bar(320, 440, 490, 460);
            setcolor(WHITE);
            line(330, 450, 480, 450); //����
            ball(330, 450, 2, WHITE);
            ball(360, 450, 2, WHITE);
            ball(390, 450, 2, WHITE);//X1
            ball(420, 450, 2, WHITE);
            ball(450, 450, 2, WHITE);
            ball(480, 450, 2, WHITE);
            sr = (mx-330)/30;
            ball(330+sr*30, 450, 4, DARKGRAY);
            speed = speedrank[sr];
        }
        //����
        if(video == 0)
        {
                video=1;
			    count = getnum(prjdir);
            
        }
        else if(video == 1)
        {   
            if(pause == 0)
            {
                globalfloat += 1*speed;
                if(mouse_press_sup(80, 400, 520, 420, &mx, &my) == 1)
                {
                    globalfloat = 1.0 * (mx-80) / 440 * count;
                }
                globalnum = (int)globalfloat;
                if(globalnum>count)
                {
                    globalnum = count;
                }
                //������
                setfillstyle(SOLID_FILL, BLACK);
                bar(70, 400, 530, 420);
                setfillstyle(SOLID_FILL, LIGHTGRAY);
                bar(80, 405, 520, 410);
                ball(80+440.0*globalnum/count, 408, 5, DARKGRAY);
            }
			if(chdir(prjdir)==0)
			{
			if(chdir("output")==0)
			{
			formatname(globalnum, filename);
			clearpixlist(pixlist, &pixnum, LISTSIZE);
			//strcat(filename, ".txt");
			//stream_read(filename, pixlist, &pixnum);
			//printf("%s\n", filename);
			//printf("%d\n", globalnum);
			//delay(5000);
			//printf("%d\n", pixnum);
			readdronetxt(filename, pixlist, &pixnum);
			clrmous(nx, ny);
			setfillstyle(SOLID_FILL, BLACK);
			bar(X0-5, Y0-5, X0+XSIZE+5, Y0+YSIZE+5);
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, percent);
				if((X>X0&&X<X0+XSIZE)&&(Z>Y0&&Z<Y0+YSIZE))
				{
					ball(X, Z, 3, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			move_3d_p(20, 0, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			move_3d_p(0, 20, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			move_3d_p(0, 0, 20, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			//A+=0.01;
			//B+=0.01;
			//getch();
			//update = 0;
			chdir("..");
			}
			chdir("..");
			}
			if(globalnum == count)
			{
				globalnum = 0;
                globalfloat = 0;
			}
        }
        newmouse(&nx, &ny, &nb);
        if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(nx - oldx);
				A += 0.01*(ny - oldy);
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (nx - oldx);
				DY += (ny - oldy);
			}
		}
		if(SP == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				C += - 0.01*(ny - oldy);
			}
		}
        oldx = nx;
		oldy = ny;
        delay(20);
    }
    return 1;
}