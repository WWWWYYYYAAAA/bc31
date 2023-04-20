#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include "printg.h"
//#include "hz.h"
#include "bmp.h"
//图形化输出

int initialization()
{
	int i;
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 0, 639, 479);
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(WHITE);
	rectangle(160, 300, 480, 320);
	printg(160, 285, 15, "Initializing...");
	for(i=0; i<100; i++)
	{
		setfillstyle(SOLID_FILL, WHITE);
		bar(160, 300, 3.2*i+161, 320);
		delay(1);
	}
	return 0;
}

int page0()
{
	int nx, ny, nb, w, h;
	int style[5] = {0, 2, 0, 0, 1}, style1[5] = {0, 2, 0, 0, 4};
	float scale;
	mouseinit();
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(0, 0, 639, 479);
	bmpinfo("./pic/begin.bmp", &w, &h);
	if((1.0*640/w)>(1.0*480/h))
	{
		scale = 1.0*480/h;
	}
	else
	{
		scale = 1.0*640/w;
	}
	//printf("%f", scale);
	h = h * scale;
	w = w * scale;
	putbmp_zoom(0, 0, "./pic/begin.bmp", scale, scale); //放置背景模板
	bar_3d(180, 300, 460, 360, DARKGRAY, 0);
	button(180, 300, 460, 360, 0);
	bar_3d(180, 380, 460, 440, DARKGRAY, 0);
	button(180, 380, 460, 440, 0);
	bar_3d(600, 440, 639, 479, DARKGRAY, 0);
	//button(600, 440, 639, 479, 0);
	//printg(300, 220, 0, "title");
	/*
	puthz(100, 100, 16, 26, BLACK, "无人机");
	puthz(100, 120, 24, 34, BLACK, "无人机");
	puthz(100, 150, 32, 42, BLACK, "无人机");
	puthz(100, 190, 48, 58, BLACK, "无机人");
	*/
	//printg_cn(168, 203, BLACK, style1, "%z", "建校七十周年无人机灯光秀");
	//printg_cn(165, 200, WHITE, style1, "%z", "建校七十周年无人机灯光秀");
	printg_cn(128, 203, BLACK, style1, "%z", "建校七十周年无人机灯光秀");
	printg_cn(125, 200, WHITE, style1, "%z", "建校七十周年无人机灯光秀");
	printg_cn(255, 330, 15, style, "%z", "无人机灯光秀示例");
	printg_cn(250, 410, 15, style, "%z", "无人机灯光秀编辑器");
	setcolor(BLACK);
	//rectangle(100, 190, 139, 237);
	while(1)
	{
		newmouse(&nx, &ny, &nb);
		if(mouse_press(180, 300, 460, 360) == 1)
		{
			button(180, 300, 460, 360, 1);
			return 1;
		}
		else if(mouse_press(180, 380, 460, 440) == 1)
		{
			button(180, 380, 460, 440, 1);
			return 5;
		}
		else if(mouse_press(600, 440, 639, 479)==1)
		{
			button(600, 440, 639, 479, 1);
			return -2;
		}
		
	}
}