#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include "xormou.h"

#define OFF	0
#define ON	1

int flag;
/*
出于节约内存的考虑该鼠标库采用异或实现
并将缩减全局变量,以及style
wya 2023.1.22
*/
//初始化鼠标
int mouseinit()
{
	int retcode;
	int xmin,xmax,ymin,ymax,x_max=625,y_max=480;
	int size;
	union REGS regs;
	xmin=2;
	xmax=x_max-1;
	ymin=8;
	ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		return 1;
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}
	flag = OFF;
	return 0;
}

void mouse(int x,int y)
{
			setlinestyle(0,0,1);
			setcolor(WHITE);
			line(x,y,x,y+13);
			line(x+1,y+1,x+1,y+12);
			line(x+2,y+2,x+2,y+11);
			line(x+3,y+3,x+3,y+10);
			line(x+4,y+4,x+4,y+12);
			line(x+5,y+5,x+5,y+9);
			line(x+5,y+11,x+5,y+14);
			line(x+6,y+6,x+6,y+9);
			line(x+6,y+13,x+6,y+15);
			line(x+7,y+7,x+7,y+9);
			line(x+8,y+8,x+8,y+9);
			line(x+9,y+9,x+9,y+9);
			setcolor(DARKGRAY);
			line(x-1,y-1,x-1,y+14);
			line(x-1,y+14,x+3,y+11);
			line(x+3,y+11,x+3,y+12);
			line(x+3,y+12,x+4,y+13);
			line(x+4,y+13,x+4,y+14);
			line(x+4,y+14,x+7,y+17);
			line(x+7,y+17,x+7,y+13);
			line(x+7,y+13,x+6,y+12);
			line(x+6,y+12,x+6,y+11);
			line(x+6,y+11,x+5,y+10);
			line(x+5,y+10,x+11,y+10);
			line(x+11,y+10,x-1,y-2);
}

void mread(int *nx, int *ny, int *nbuttons)  
{
	
	union REGS regs;
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*nx = regs.x.cx;
	*ny = regs.x.dx;
	*nbuttons = regs.x.bx;
}

void newmouse(int *nx, int *ny, int *nbuttons)
{
	int xnow, ynow, buttonsnow;
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	mread(&xnow,&ynow,&buttonsnow);
	*nx = xnow;
	*ny = ynow;
	*nbuttons = buttonsnow;
	if(buttons0 == *nbuttons)
		*nbuttons = 0;    //使得能连续按键
	clrmous(x0,y0);
	drawmous(*nx, *ny);
	
}

void drawmous(int nx, int ny)
{
	if(flag==OFF)
	{
		setwritemode(XOR_PUT);
	    mouse(nx, ny);
		flag = ON;
		setwritemode(COPY_PUT);
	}
}


void clrmous(int nx,int ny)//清除鼠标
{
	if(nx>=0)
	{
		if(flag==ON)
		{
			setwritemode(XOR_PUT); 
			mouse(nx, ny);
			flag = OFF;
			setwritemode(COPY_PUT);
		}
	}
}

//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0
int mouse_press(int x1, int y1, int x2, int y2)
{
	int xn,yn,buttonsn;
	mread(&xn,&yn,&buttonsn);
	//在框中点击，则返回1
	if(xn > x1 
	&&xn < x2
	&&yn > y1
	&&yn < y2)
	{
		if(buttonsn == 1)
			return 1;
		
		//在框中未点击，则返回2
		else if(buttonsn == 0)
			return 2;
		
		//在框中点击右键，则返回3
		else if(buttonsn == 2)
			return 3;
	}
	else
	{
		return 0;
	}
}
