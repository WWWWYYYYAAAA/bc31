#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <alloc.h>
#include <math.h>
#include "mouse.h"
#include "printg.h"

#define XC 320
#define YC 240
#define DRONEX 64
#define DRONEY 64

void move_3d(float xin, float yin, float zin, float A, float B, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset)
{
	float sA = sin(A), cA = cos(A);	//x轴转
	float xA = xin, yA = cA * yin - sA * zin, zA = sA * yin + cA * zin;
	float sB = sin(B), cB = cos(B);	//z轴转
	float xB = cB * xA - sB * yA, yB = sB * xA + cB * yA, zB = zA;
	
	*xout = xB + Xoffset;
	*yout = yB + Yoffset;
	*zout = zB + Zoffset;
}





void main()
{
	char far *drone, *droneY;
	float A = 0, B = 0;
	float i, j;
	int xo, yo, zo;
	float AR=0, BR=0;
	float xL, yL, zL, LR, mLR = 0;// LR:light rank
	float R1 = 11, R2 = 21, si, ci, sj, cj, sA, cA, sB, cB, xi, yi, zi;
	int nx = -1, ny = -1, nbuttons, k, l;
	float cube[8][3] = {{10, 10, 10}, {-10, 10, 10}, {-10, -10, 10}, {10, -10, 10}, {10, 10, -10}, {-10, 10, -10}, {-10, -10, -10}, {10, -10, -10}};
	int cubeout[8][3] ={{0}};
	int graphdriver = VGA;
    int	graphmode = VGAHI;
	char c;
	printf("This is a test on 2023.1.19.\n");
	getch();
    initgraph(&graphdriver, &graphmode, "C://BORLANDC//BGI");
	while(1)
	{
		mouseinit();
		clrmous(nx, ny);
		setcolor(0);
		setfillstyle(SOLID_FILL, 0);
		bar(0, 0, 640, 480);
		setcolor(4);
		setfillstyle(SOLID_FILL, 4);
		bar(610, 10, 630, 30);
		//newmouse(&nx, &ny, &nbuttons);
		while(1)
		{
			//newmouse(&nx, &ny, &nbuttons);
			//setcolor(4);
			//setfillstyle(SOLID_FILL, 4);
			//bar(100, 20, 200, 50);
			//printg(105, 25, 1, "%d %d %d", nx, ny, nbuttons);
			
			//the donut
		
			{
				/*
				setcolor(0);
				setfillstyle(SOLID_FILL, 0);
				bar(250, 250, 400, 400);
				*/
				for(i=0; i<8; i++)
				{
					move_3d(cube[i][0]*4, cube[i][1]*4, cube[i][2]*4, AR, BR, &cubeout[i][0], &cubeout[i][1], &cubeout[i][2], 300, 20, 300);
				}
				setcolor(WHITE);
				setlinestyle(0,0,1);
				line(cubeout[0][0],cubeout[0][2],cubeout[1][0],cubeout[1][2]);
				line(cubeout[0][0],cubeout[0][2],cubeout[3][0],cubeout[3][2]);
				line(cubeout[0][0],cubeout[0][2],cubeout[4][0],cubeout[4][2]);
				line(cubeout[2][0],cubeout[2][2],cubeout[1][0],cubeout[1][2]);
				line(cubeout[2][0],cubeout[2][2],cubeout[3][0],cubeout[3][2]);
				line(cubeout[2][0],cubeout[2][2],cubeout[6][0],cubeout[6][2]);
				line(cubeout[5][0],cubeout[5][2],cubeout[4][0],cubeout[4][2]);
				line(cubeout[5][0],cubeout[5][2],cubeout[6][0],cubeout[6][2]);
				line(cubeout[5][0],cubeout[5][2],cubeout[1][0],cubeout[1][2]);
				line(cubeout[7][0],cubeout[7][2],cubeout[4][0],cubeout[4][2]);
				line(cubeout[7][0],cubeout[7][2],cubeout[6][0],cubeout[6][2]);
				line(cubeout[7][0],cubeout[7][2],cubeout[3][0],cubeout[3][2]);
				AR += 0.1;
				BR += 0.1;
			}
			delay(30);
			free(drone);
			free(droneY);
			//delay(20);
			setcolor(0);
			setfillstyle(SOLID_FILL, 0);
			bar(0, 0, 640, 480);
			newmouse(&nx, &ny, &nbuttons);
			setcolor(4);
			setfillstyle(SOLID_FILL, 4);
			bar(610, 10, 630, 30);
			if(mouse_press(610, 10, 630, 30) == 1)
			{
				clrmous(nx, ny);
				restorecrtmode();
				//free_mousbuff()
				break;
			}
			
			if(kbhit())
			{
				if(getch() == 'q')
				{
					clrmous(nx, ny);
					restorecrtmode();
					//free_mousbuff()
					break;
				}
			}
		}
		printf("the graph is closed.\n");
		printf("mLR: %f\n", mLR);
		c = getch();
		if(c == 'q')
		{
			closegraph();
			break;
		}
		else
		{
			setgraphmode(getgraphmode());
		}
	}
	delay(100);
}
