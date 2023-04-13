#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include "onoff.h"
#include "printg.h"
#include "TD.h"
#include <dos.h>
#include <stdlib.h>

int example(float AR, float BR, int Xoffset,int Zoffset,int Yoffset, int sizeP, int sizeB)
{
		int i, j, size, pic1x=0, pic1y=0;
		int state = 0;
		float a, b, d;
		float tix, tiy, tiz, tin;
		int tempx, tempy, tempz, temp;
		int k, l, count;
		float cube33[27][4];
		int cube33out[27][4] ={{0}};
		int enableM = 1, enableC = 0, resetM = 0, resetC = 0, flag = 0;
		void far * pic1;
		count = 0;
		for(a=0; a<3; a++)
		{
			for(b=0; b<3; b++)
			{
				for(d=0; d<3; d++)
				{
					cube33[count][0] = a-1;
					cube33[count][1] = b-1;
					cube33[count][2] = d-1;
					cube33[count][3] = count;
					count++;
				}
			}
		}
		//size = imagesize(0, 0, 150, 150);
	//update
	{
		for(i=0; i<27; i++)
			{
					move_3d(cube33[i][0]*sizeP, cube33[i][1]*sizeP, cube33[i][2]*sizeP, AR, BR, &cube33out[i][0], &cube33out[i][1], &cube33out[i][2], Xoffset, Yoffset, Zoffset);
					cube33out[i][3] = i;
			}
			for(i=0; i<26; i++)
			{
				for(j=0; j<26-i; j++)
				{
					if(cube33out[j][1]>cube33out[j+1][1])
					{
						tempx = cube33out[j][0];
						tempy = cube33out[j][1];
						tempz = cube33out[j][2];
						temp = cube33out[j][3];
						cube33out[j][0] = cube33out[j+1][0];
						cube33out[j][1] = cube33out[j+1][1];
						cube33out[j][2] = cube33out[j+1][2];
						cube33out[j][3] = cube33out[j+1][3];
						cube33out[j+1][0] = tempx;
						cube33out[j+1][1] = tempy;
						cube33out[j+1][2] = tempz;
						cube33out[j+1][3] = temp;
						tix = cube33[j][0];
						tiy = cube33[j][1];
						tiz = cube33[j][2];
						tin = cube33[j][3];
;						cube33[j][0] = cube33[j+1][0];
						cube33[j][1] = cube33[j+1][1];
						cube33[j][2] = cube33[j+1][2];
						cube33[j][3] = cube33[j+1][3];
						cube33[j+1][0] = tix;
						cube33[j+1][1] = tiy;
						cube33[j+1][2] = tiz;
						cube33[j+1][3] = tin;
					}
				}
			}
			for(i=0; i<27; i++)
			{
				if(cube33[i][0] > 0 && cube33[i][1] > 0 && cube33[i][2] > 0)
					ball(cube33out[i][0], cube33out[i][2], sizeB, RED);
				else if(cube33[i][0] > 0 && cube33[i][1] < 0 && cube33[i][2] > 0)
					ball(cube33out[i][0], cube33out[i][2], sizeB, YELLOW);
				else
					ball(cube33out[i][0], cube33out[i][2], sizeB, CYAN);
			}
			delay(20);
	}
}
//全屏放映
int page2()
{
	int nx , ny, nb;
	//begine
	float AR=0, BR=0;
	int Xoffset = 320, Zoffset = 240, Yoffset = 20;
	//end
	clrmous(ny, nx);
	bar2d(0, 0, 639, 479, BLACK);
	bar2d(610, 0, 639, 29, RED);
	button(610, 0, 639, 29, 0);
	bar3d(0, 0, 609, 29, LIGHTGRAY, 0);
	printg(10, 5, 0, "part1/page2");
	//begine
		
	//end
	while(1)
	{
		//遮罩
			bar2d(240, 160, 400, 320, BLACK);
		newmouse(&nx, &ny, &nb);
		//begine
		example(AR, BR, Xoffset, Zoffset, Yoffset, 20, 3);
		AR+=0.01;
		BR+=0.01;
		//end
		if(mouse_press(610, 0, 639, 29) == 1)
		{
			button(610, 0, 639, 29, 1);
			return 1;
		}
	}
}

int page3()
{
	int nx , ny, nb;
	clrmous(ny, nx);
	bar2d(0, 0, 639, 479, BLACK);
	bar2d(610, 0, 639, 29, RED);
	button(610, 0, 639, 29, 0);
	bar3d(0, 0, 609, 29, LIGHTGRAY, 0);
	printg(10, 5, 0, "part2/page3");
	while(1)
	{
		newmouse(&nx, &ny, &nb);
		if(mouse_press(610, 0, 639, 29) == 1)
		{
			button(610, 0, 639, 29, 1);
			return 1;
		}
	}
}

int page4()
{
	int nx , ny, nb;
	clrmous(ny, nx);
	bar2d(0, 0, 639, 479, BLACK);
	bar2d(610, 0, 639, 29, RED);
	button(610, 0, 639, 29, 0);
	bar3d(0, 0, 609, 29, LIGHTGRAY, 0);
	printg(10, 5, 0, "part3/page4");
	while(1)
	{
		newmouse(&nx, &ny, &nb);
		if(mouse_press(610, 0, 639, 29) == 1)
		{
			button(610, 0, 639, 29, 1);
			return 1;
		}
	}
}