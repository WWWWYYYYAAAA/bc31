#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include "visual.h"
#include "page0.h"
#include "page1.h"
#include "page5.h"
#include "mouse.h"
#include "page6.h"
#include "page234.h"

void main()
{
	int graphdriver = VGA;
	int	graphmode = VGAHI;
	int page=-1;
	initgraph(&graphdriver, &graphmode, "C:/BORLANDC/BGI");
	cleardevice();
	mouseinit();
	while(1)
	{
		switch(page)
		{
		case -1:
			cleardevice();
			page = initialization();
		break;
		case 0:
			cleardevice();
			page = page0();
		break;
		
		case 1:
			cleardevice();
			page = page1();
		break;
		case 2:
			cleardevice();
			page = page234("prj");
		break;
		case 3:
			cleardevice();
			page = page234("prj");
		break;
		case 4:
			cleardevice();
			page = page234("prj");
		break;
		case 5:
			cleardevice();
			page = page5();
		break;
		case 6:
			cleardevice();
			page = page6();
		break;
		default:
			exit(1);
		}
		/*
		mouse_signal(mousig);
		//button(100, 100, 200, 200, mousig[0]);
		clrmous(nx, ny);
		newmouse(&nx, &ny, &nb);
		temp = slider(617, 201, nx, ny, 20, 278, 0, 0, &signal1);
		if(temp > 0)
		{
			nylist[0] = temp;
		}
		silder_depature(nylist[0], 617, 201, 20, 278, 0, 0);
		newmouse(&nx, &ny, &nb);
		delay(20);
		*/
	}
}
