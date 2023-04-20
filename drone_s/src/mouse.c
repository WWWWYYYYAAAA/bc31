#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include "mouse.h"

//only XOR
int flag=0;
int MX, MY;

int mouseinit()//��ʼ��
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
	flag = 0;
	return 0;
}

/*****************************
FUNCTION: mouse
DESCRIPTION: ����ͬ��̬�����
INPUT: x,y
RETURN: ��
******************************/
void mouse(int x,int y, int style)
{
	
	switch(style)
	{
		case 1:                                  //�������
		{
				setcolor(WHITE);
				setlinestyle(0,0,1);
				line(x-1,y+9,x-1,y+8);
				line(x,y+7,x,y+11);
				line(x+1,y+6,x+1,y+13);
				line(x+2,y+8,x+2,y+14);
				line(x+3,y-1,x+3,y+15);
				arc(x+4,y-1,0,180,1);
				line(x+4,y-2,x+4,y+15);
				line(x+5,y-1,x+5,y+16);
				arc(x+6,y+3,0,180,1);
				line(x+6,y+2,x+6,y+16);
				line(x+7,y+3,x+7,y+17);
				arc(x+8,y+5,0,180,1);
				line(x+8,y+4,x+8,y+17);
				line(x+9,y+5,x+9,y+16);
				arc(x+10,y+7,0,180,1);
				line(x+10,y+6,x+10,y+16);
				line(x+11,y+7,x+11,y+13);

				setcolor(DARKGRAY);
				line(x-1,y+9,x-1,y+8);
				line(x-1,y+8,x+1,y+6);
				line(x+1,y+6,x+3,y+10);
				line(x+3,y+10,x+3,y-1);
				arc(x+4,y-1,0,180,1);
				line(x+5,y-1,x+5,y+5);
				arc(x+6,y+3,0,180,1);
				line(x+7,y+3,x+7,y+7);
				arc(x+8,y+5,0,180,1);
				line(x+9,y+5,x+9,y+9);
				arc(x+10,y+7,0,180,1);
				line(x+11,y+7,x+11,y+13);
				arc(x+7,y+13,-90,0,4);
				line(x+7,y+17,x+3,y+15);
				line(x+3,y+15,x+1,y+13);
				line(x+1,y+13,x-1,y+9);
		}
			break;
		case 2:                        //���
		{
			setcolor(DARKGRAY);
			setlinestyle(0,0,1);
			line(x+1,y-1,x+9,y-1);
			line(x+1,y+15,x+9,y+15);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		case 3:                        //ʮ��
		{
			setcolor(WHITE);
			setlinestyle(0,0,1);
			line(x-1,y+7,x+11,y+7);
			line(x+5,y-1,x+5,y+15);
		}
			break;
		default:              //Ĭ�����
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
		break;
	}
}

/***************************************
FUNCTION: mread
DESCRIPTION: ��ȡ�µļĴ�����Ϣ
INPUT: nx,ny,nbuttons
RETURN: ��
****************************************/
void mread(int *nx,int *ny,int *nbuttons)  
{
	union REGS regs;
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*nx = regs.x.cx;
	*ny = regs.x.dx;
	*nbuttons = regs.x.bx;
}

/*******************************************
FUNCTION: newmouse
DESCRIPTION: ���״̬�����仯��������
INPUT: nx,ny,nbuttons
RETURN: ��
********************************************/
int newmouse(int *nx,int *ny,int *nbuttons)
{
	int xn, yn, buttonsn, flag = 0;
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	mread(&xn,&yn,&buttonsn);
	*nbuttons = buttonsn;
	if(*nx != xn && *ny != yn)
	{
		//printf("1");
		*nx = xn;
		*ny = yn;
		if(buttons0 == *nbuttons)
			*nbuttons = 0;    //ʹ������������
		if(xn == x0 && yn == y0 && buttonsn == buttons0)
			return;            //���״̬������ֱ�ӷ���S
		clrmous(x0,y0);        //˵�����״̬�����˸ı�
		flag = 1;
	}
	drawmous(*nx,*ny);
	MX = *nx;
	MY = *ny;
	// int xn,yn,buttonsn;
	// mread(&xn,&yn,&buttonsn);
	// drawmous(xn,yn);
	// MX = xn;
	// MY = yn;
	// delay(5);
	// clrmous(xn,yn); 
	return flag;
}

void clrmous(int nx,int ny)//������
{
	if(nx>=0)
	{
		if(flag==1)
		{
			setwritemode(XOR_PUT); 
			mouse(nx, ny, 0);
			flag=0;
			setwritemode(COPY_PUT);
		}
	}
}

void drawmous(int nx,int ny)
{
	if(flag==0)
	{
		setwritemode(XOR_PUT);
	    mouse(nx, ny, 0);
		flag=1;
		setwritemode(COPY_PUT);
	}
}



//����ڿ��е�����򷵻�1���ڿ���δ������򷵻�2�����ڿ����򷵻�0
int mouse_press(int x1, int y1, int x2, int y2)
{
	int xn,yn,buttonsn;
	mread(&xn,&yn,&buttonsn);
	//�ڿ��е�����򷵻�1
	if(xn > x1 
	&&xn < x2
	&&yn > y1
	&&yn < y2)
	{
		if(buttonsn == 1)
			return 1;
		
		//�ڿ���δ������򷵻�2
		else if(buttonsn == 0)
			return 2;
		
		//�ڿ��е���Ҽ����򷵻�3
		else if(buttonsn == 2)
			return 3;
	}
	else
	{
		return 0;
	}
}

int mouse_press_sup(int x1, int y1, int x2, int y2, int * mx, int * my)
{
	int xn,yn,buttonsn;
	mread(&xn,&yn,&buttonsn);
	*mx = xn;
	*my = yn;
	
	if(xn > x1 
	&&xn < x2
	&&yn > y1
	&&yn < y2)
	{
		if(buttonsn == 1)//�ڿ��е�����򷵻�1
			return 1;
		
		//�ڿ���δ������򷵻�2
		else if(buttonsn == 0)
			return 2;
		
		//�ڿ��е���Ҽ����򷵻�3
		else if(buttonsn == 2)
			return 3;
	}
	else
	{
		return 0;
	}
	return 0;
}