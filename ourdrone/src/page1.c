#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include "onoff.h"
#include "printg.h"
#include "page234.h"
#include "player.h"
//鑿滃崟鏍?
int page1()
{
	int nx , ny, nb, temp, part = 1;
	int mousig[10] = {0};
	int nylist[10] = {0};
	int style[5] = {0, 2, 0, 0, 1};
	float ar1 = 0, br1 = 0; //example
	float signal1;
	bar2d(0, 0, 639, 479, LIGHTGRAY);
	bar3d(0, 0, 100, 480, LIGHTGRAY, 0);
	bar3d(100, 0, 639, 20, LIGHTGRAY, 0);
	bar3d(440, 21, 639, 479, DARKGRAY, 1);
	bar2d(442, 24, 637, 200, BLACK);
	bar2d(442, 24, 472, 54, BLUE);
	bar2d(2, 440, 98, 477, RED);
	button(0, 20, 98, 59, 0);
	button(0, 60, 98, 99, 0);
	button(0, 100, 98, 139, 0);
	button(0, 140, 98, 179, 0);//自定义
	button(442, 24, 472, 54, 0);
	button(2, 440, 98, 477, 0);
	sliderbase(617, 201, nx, ny, 20, 278, 0, 0, 0);
	clrmous(ny, nx);
	printg_cn(28, 160, BLACK, style,"%z", "自定义");
	while(1)
	{
		if(mouse_press(0, 20, 98, 59) == 1)
		{
			button(0, 20, 98, 59, 1);
			part = 1;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 60, 98, 99) == 1)
		{
			button(0, 60, 98, 99, 1);
			part = 2;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 100, 98, 139) == 1)
		{
			button(0, 100, 98, 139, 1);
			part = 3;
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(2, 440, 98, 477) == 1)
		{
			button(2, 440, 98, 477, 1);
			return 0;
		}
		else if (mouse_press(0, 140, 98, 179) == 1)
		{
			button(0, 140, 98, 179, 1);
			part = 4;
		}
		
		
		newmouse(&nx, &ny, &nb);
		temp = slider(617, 201, nx, ny, 20, 278, 0, 0, &signal1);
//switch part
		switch(part)
		{
			case 1:
			bar2d(442, 55, 637, 200, BLACK);
			example(ar1, br1, 540, 110, 20, 10, 1);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, 1);
				return 2;
			}
			ar1 += 0.05;
			br1 += 0.05;
			break;
			case 2:
			bar2d(442, 55, 637, 200, BLACK);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, mousig[3]);
				return 3;
			}
			break;
			case 3:
			bar2d(442, 55, 637, 200, BLACK);
			printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, mousig[3]);
				return 4;
			}
			break;
			case 4:
			//setfillstyle(SOLID_FILL, BLACK);
			//bar(50, 30, 590, 450);
			//play("prj", 1);
			//playtofile("prj");
			//part = 1;
			clrmous(nx, ny);
			return 6;
			break;
		}
		if(temp > 0)
		{
			nylist[0] = temp;
		}
		newmouse(&nx, &ny, &nb);
		delay(20);
	}
	return 0;
}