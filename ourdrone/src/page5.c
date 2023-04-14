#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include <bios.h>
#include "printg.h"
#include "bmp.h"
#include <string.h>
#include "page5.h"
#include "input.h"
#include "alloc.h"
#include "conio.h"
#include "fileflow.h"
#include "error.h"
#include "TD.h"

#define XOFF 140
#define YOFF 60
#define XSIZE 440
#define YSIZE 360
extern MX, MY;
int editpic(int *nx, int *ny, int *nb);
int picload(char * path);
int tdviwer(int *nx, int *ny, int *nb);
int tdedit(int *nx, int *ny, int *nb);
//寮�濮嬬晫闈?
int page5()
{
	int nx , ny, nb, temp, sector = 0;
	int style[5] = {0, 2, 0, 0, 1};
	int mousig[10] = {0};
	int nylist[10] = {0};
	float ar1 = 0, br1 = 0; //example
	float signal1;
	bar2d(0, 0, 639, 479, LIGHTGRAY);
	bar3d(0, 33, 120, 480, LIGHTGRAY, 0);
	
	bar3d(0, 0, 639, 32, LIGHTGRAY, 0);
	bar3d(1, 0, 80, 30, LIGHTGRAY, 0);
	bar3d(81, 0, 160, 30, LIGHTGRAY, 0);
	bar3d(161, 0, 240, 30, LIGHTGRAY, 0);
	bar3d(241, 0, 320, 30, LIGHTGRAY, 0);
	bar2d(2, 440, 118, 477, RED);

	button(1, 0, 80, 30, 0);
	button(81, 0, 160, 30, 0);
	button(161, 0, 240, 30, 0);
	button(241, 0, 320, 30, 0);
	button(2, 440, 118, 477, 0);
	printg_cn(10, 15, BLACK, style, "%z", "平面编辑");
	printg_cn(90, 15, BLACK, style, "%z", "三维编辑");
	printg_cn(170, 15, BLACK, style, "%z", "三维预览");
	setcolor(WHITE);
	rectangle(140-2, 60-2, 580+2, 420+2); //作图区
	clrmous(ny, nx);
	//printg(400, 400, BLACK, "%s", "ssss");
	while(1)
	{
		
		if(mouse_press(1, 0, 80, 30) == 1)
		{
			clrmous(nx, ny);
			button(1, 0, 80, 30, 2);
			sector = 1;
		}
		else if(mouse_press(81, 0, 160, 30) == 1)
		{
			clrmous(nx, ny);
			button(81, 0, 160, 30, 2);
			sector = 2;
		}
		else if(mouse_press(161, 0, 240, 30) == 1)
		{
			clrmous(nx, ny);
			button(161, 0, 240, 30, 2);
			sector = 3;
		}
		else if(mouse_press(241, 0, 320, 30) == 1)
		{
			button(241, 0, 320, 30, 1);
		}
		else
		{
			sector = 0;
		}
		if(mouse_press(2, 440, 118, 477) == 1)
		{
			button(2, 440, 118, 477, 1);
			return 0;
		}
		//refresh area
		
		// else if(mouse_press(0, 0, 639, 40) == 2)
		// {
		// 	button(1, 0, 80, 30, 0);
		// 	button(81, 0, 160, 30, 0);
		// 	button(161, 0, 240, 30, 0);
		// 	button(241, 0, 320, 30, 0);
		// }
		
		

		switch (sector)
		{
		case 1:
			clrmous(nx, ny);
			editpic(&nx, &ny, &nb);
			button(1, 0, 80, 30, 0);
		break;
		case 2:
			clrmous(nx, ny);
			tdedit(&nx, &ny, &nb);
			button(81, 0, 160, 30, 0);
		break;
		case 3:
			clrmous(nx, ny);
			tdviwer(&nx, &ny, &nb);
			button(161, 0, 240, 30, 0);
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

int editpic(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, h, w, edit = 0, pixnum = 0;
	char path[20] = {0};
	PIX pixlist[400];
	void far * balllist[400];
	setcolor(BLACK);
	//rectangle(2, 34, 118, 74);
	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	//rectangle(2, 74, 118, 114);
	printg_cn(45, 95, 0, style, "%Z", "清空");
	printg_cn(30, 135, 0, style, "%Z", "直接编辑");
	printg_cn(45, 175, 0, style, "%z", "保存");
	//putbmp(150, 50, "./pic/hust.bmp");
	//button(600, 440, 639, 479, 0);
	button(2, 440, 118, 477, 0); 	//退出
	button(2, 34, 118, 74, 0); 		//导入
	button(2, 75, 118, 115, 0); 	//清空
	button(2, 116, 118, 156, 0);	//直接编辑
	button(2, 157, 118, 197, 0);	//保存
	newmouse(nx, ny, nb);
	while (1)
	{
		if(mouse_press(2, 440, 118, 477) == 1)
		{
			button(2, 440, 118, 477, 1);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			clrmous(*nx, *ny);
			//bar(600, 440, 639, 479);
			bar(595, 95, 639, 345); 	
			bar(2, 34, 118, 439);//picedit panelclear
			delay(500);
			return 0;
		}
		else if(mouse_press(2, 34, 118, 74) == 1)
		{
			button(2, 34, 118, 74, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(picload(path) == 0)
			{
				putbmp(140, 60, path);
				//printf("w %d h %d", w, h);
				edit = 1;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
		}
		else if(mouse_press(2, 74, 118, 114) == 1)		//clear
		{
			button(2, 74, 118, 114, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm())
			{
				int i;
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(140, 60, 580, 420);
				bar(121, 440, 639, 479);
				setcolor(WHITE);
				rectangle(140-2, 60-2, 580+2, 420+2);
				edit = 0;
				for(i=0; i<pixnum; i++)
				free(balllist[i]);
				pixnum = 0;
			}
			else
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
			}
		}
		else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
        {
			//clrmous(*ny, *nx);
            button(639 - 30,64 - 30, 639, 64, 1);
            error(-1);
			setcolor(WHITE);
			rectangle(140-2, 60-2, 580+2, 420+2); 
			//edit = 1;
        }
		else if(mouse_press(2, 116, 118, 156) == 1)
		{
			button(2, 116, 118, 156, 1);
			edit = 1;
		}
		//edit part
		if(edit == 1)
		{
			int pen = 0;
			int YL, oldx = -1, oldy = -1;
			char str[20] = {0};
			//编辑功能栏
			button(600, 100, 639, 139, 0); 	//功能栏
			printg_cn(612, 120, BLACK, style, "%z", "笔");
			printg_cn(30, 460, WHITE, style, "%z", "退出绘点");
			button(600, 140, 639, 179, 0); 	//功能栏
			button(600, 180, 639, 219, 0); 	//功能栏
			button(600, 220, 639, 259, 0); 	//功能栏
			button(600, 260, 639, 299, 0); 	//功能栏
			button(600, 300, 639, 340, 0); 	//功能栏
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			commandin(str, "z: ", 130, 455, 20);
			YL = atoi(str);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			//printf("%d", ZL);
			bar3d(2, 300, 118, 439, DARKGRAY, 1);//scsreen
			while (1)										//绘制点位
			{
				int backout;
				
				if(mouse_press(600, 100, 639, 139) == 1)//pen
				{
					if(pen ==0)
						pen = 1;
					else
						pen = 0;
					//printf("%d", pen);
					button(600, 100, 639, 139, 2*pen);
					delay(200);
				}
				else if(mouse_press(600, 140, 639, 179) == 1)//功能待定
				{
					button(600, 140, 639, 179, 1);
				}
				else if(mouse_press(600, 180, 639, 219) == 1)
				{
					button(600, 180, 639, 219, 1);
				}
				else if(mouse_press(600, 220, 639, 259) == 1)
				{
					button(600, 220, 639, 259, 1);
				}
				else if(mouse_press(600, 260, 639, 299) == 1)
				{
					button(600, 260, 639, 299, 1);
				}
				else if(mouse_press(600, 300, 639, 340) == 1)
				{
					button(600, 300, 639, 340, 1);
				}
				else if(mouse_press(2, 440, 118, 477) == 1) //退出
				{	
					clrmous(*nx, *ny);
					setfillstyle(SOLID_FILL, RED);
					bar(2, 440, 118, 477);
					button(2, 440, 118, 477, 1);
					delay(500);
					edit = 0;
					break;
				}
				else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
				{
					//clrmous(*ny, *nx);
					button(639 - 30,64 - 30, 639, 64, 1);
					error(-1);
					setcolor(WHITE);
					rectangle(140-2, 60-2, 580+2, 420+2); 
					//edit = 1;
				}
				if(oldx != *nx || oldy != *ny)
				{
					int tempx, tempz;
					//防止出界
					tempx = *nx - XOFF>0? *nx - XOFF: 0;
					tempx = tempx-440 < 0? tempx: 440;
					tempz = *ny - YOFF>0? *ny - YOFF: 0;
					tempz = tempz-360 <0? tempz: 360;
					setfillstyle(SOLID_FILL, DARKGRAY);
					bar(4, 302, 116, 339);
					//140, 60, 580, 420
					printg_cn(10, 310, WHITE, style, "x= %d", tempx);
					printg_cn(10, 330, WHITE, style, "z= %d", YL);
					printg_cn(10, 320, WHITE, style, "y= %d", tempz);
					oldx = *nx;
					oldy = *ny;
				}
				if(pen == 1)
				{
					int xp, yp;
					setcolor(BLACK);
					if(mouse_press_sup(140, 60, 580, 420, &xp, &yp) == 3)
					{
						int col, buffsize, key;
						void far * ballbuff;
						buffsize = imagesize(0, 0, 8, 8);
						ballbuff = farmalloc(buffsize);
						clrmous(*nx, *ny);
						getimage(xp-4, yp-4, xp+4, yp+4, ballbuff);
						ball(xp, yp, 3, CYAN);
						bar3d(121, 440, 639, 479, DARKGRAY, 1);
						printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
						if(commandin(str, "color: ", 130, 455, 20) == 0)
						{
							col = atoi(str);
							ball(xp, yp, 3, col);
							setfillstyle(SOLID_FILL, LIGHTGRAY);
							bar(121, 440, 639, 479);
							pixlist[pixnum].x = xp - XOFF;
							pixlist[pixnum].y = YL;
							pixlist[pixnum].z = yp - YOFF;
							pixlist[pixnum].color = col;
							pixlist[pixnum].id = pixnum;
							setfillstyle(SOLID_FILL, RED);
							bar(80, 340, 88, 348);
							printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[pixnum].x);
							printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[pixnum].z);
							while (1)
							{
								//clrmous(*nx, *ny);
								int flag = 0;
								key = bioskey(0)>>8;
								//printf("%d", key);
								putimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, ballbuff, COPY_PUT);
								switch (key)
								{
								case 1://esc
								case 28://enter
									flag = 1;
								break;
								case 72:
									pixlist[pixnum].z--; //up
								break;
								case 80:
									pixlist[pixnum].z++; //down
								break;
								case 75:
									pixlist[pixnum].x--; //left
								break;
								case 77:
									pixlist[pixnum].x++; //left
								break;
								default:
									break;
								}
								setfillstyle(SOLID_FILL, DARKGRAY);
								bar(4, 350, 116, 370);
								printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[pixnum].x);
								printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[pixnum].z);
								getimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, pixlist[pixnum].x+XOFF+4, pixlist[pixnum].z+YOFF+4, ballbuff);
								ball(pixlist[pixnum].x+140, pixlist[pixnum].z+60, 3, col);
								if(flag == 1)
								{
									setfillstyle(SOLID_FILL, DARKGRAY);
									bar(4, 350, 116, 370);
									break;
								}
							}
							balllist[pixnum] = ballbuff;
							pixnum++;
							setfillstyle(SOLID_FILL, DARKGRAY);
							bar(4, 340, 116, 350);
							printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
						}
						else
						{
							bar(121, 440, 639, 479);
						}
					}
					if(kbhit())		//撤回
					{
						backout = bioskey(0)>>8;
						//printf("%d", backout);
						switch (backout)
						{
						case 59://F1
							if(pixnum>0)
							{
								pixnum--;
								setfillstyle(SOLID_FILL, DARKGRAY);
								bar(4, 340, 116, 350);
								printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
								putimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, balllist[pixnum], COPY_PUT);
								pixlist[pixnum].id = -1;
							}
						break;
						}
					}
				}
				newmouse(nx, ny, nb);
			}
		}
		if(mouse_press(2, 157, 118, 197) == 1)
		{
			int i;
			if(pixnum > 0) // save the file
			{
				char savepath[30];
				button(2, 157, 118, 197, 1);
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				commandin(savepath, "path: ", 130, 455, 30);
				stream_write(savepath, &(pixlist[0].x), pixnum);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				stream_read(savepath, &(pixlist[0].x), &pixnum);
				//printf("ss %d", pixnum);
			}
			else
			{
				error(2);
			}
			for(i=0; i<pixnum; i++)
				free(balllist[i]);
			pixnum = 0;
		}
		newmouse(nx, ny, nb);
	}
	
}

int picload(char * path)
{
	int style[5] = {0, 2, 0, 0, 1};
	int key, i=0;
	char ch;
	while (1)
	{
		key = bioskey(0);
		ch =  key-(key>>8<<8);
		if(ch == 13)
		{
			path[i] = 0;
			break;
		}
		else if(ch == 8)
		{
			i--;
			if(i<0)
			{
				i = 0;
				setfillstyle(SOLID_FILL, WHITE);
				bar(130, 450, 138, 466);
				delay(50);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(130, 450, 138, 466);
			}
			path[i] = 0;
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(130+i*8, 450, 138+i*8, 466);
			continue;
		}
		else if(ch == 27)
		{
			return -1;
		}
		//printf("%d", ch);
		if(i>=19)
		{
			i = 19;
			continue;
		}
		printg_cn(130+i*8, 455, WHITE, style, "%c", ch);
		path[i] = ch;
		i++;
	}
	return 0;
}


int tdviwer(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 0, pixnum, i, RO = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	PIX pixlist[400];
	float A = 0, B = 0, percent = 1;
	int X, Y, Z;
	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	printg_cn(45, 95, 0, style, "%Z", "清空");
	button(2, 34, 118, 74, 0); 		//导入
	button(2, 75, 118, 115, 0); 	//清空
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	bar3d(140, 60, 580, 420, DARKGRAY, 1);
	printg_cn(612, 120, BLACK, style, "RO");
	printg_cn(612, 160, BLACK, style, "PO");
	printg_cn(612, 200, BLACK, style, "RE");
	printg_cn(616, 240, BLACK, style, "+");
	printg_cn(616, 280, BLACK, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//RE
	button(600, 220, 639, 259, 0); 	//+
	button(600, 260, 639, 299, 0); 	//-
	button(600, 300, 639, 340, 0); 	//功能栏
	while (1)
	{
		if(mouse_press(2, 440, 118, 477) == 1)//退出
		{
			button(2, 440, 118, 477, 1);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			clrmous(*nx, *ny);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(140-2, 60-2, 580+2, 420+2);
			bar(595, 95, 639, 345); 	//功能栏
			setcolor(WHITE);
			rectangle(140-2, 60-2, 580+2, 420+2);
			//bar(600, 440, 639, 479);
			bar(2, 34, 118, 439);//picedit panelclear
			delay(500);
			return 0;
		}
		else if(mouse_press(2, 34, 118, 74) == 1) //导入
		{
			char path[20];
			button(2, 34, 118, 74, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				if(stream_read(path, &(pixlist[0].x), &pixnum)!=-1)
					show = 1;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
		}
		else if(mouse_press(2, 74, 118, 114) == 1)		//clear
		{
			button(2, 74, 118, 114, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm())
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(140, 60, 580, 420);
				bar(121, 440, 639, 479);
				bar3d(140, 60, 580, 420, DARKGRAY, 1);
			}
			else
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
			}
		}
		else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
        {
			//clrmous(*ny, *nx);
            button(639 - 30,64 - 30, 639, 64, 1);
            error(-1);
			//setcolor(WHITE);
			//rectangle(140-2, 60-2, 580+2, 420+2); 
			//edit = 1;
			bar3d(140, 60, 580, 420, DARKGRAY, 1);
        }
		if(mouse_press(600, 100, 639, 139) == 1)	//RO
		{
			if(RO == 0)
				RO = 1;
			else if(RO == 1)
				RO = 0;
			//printf("RO %d\n", RO);
			clrmous(*nx, *ny);
			button(600, 100, 639, 139, 2*RO);
			delay(200);
		}
		else if(mouse_press(600, 140, 639, 179) == 1)	//PO
		{
			if(PO == 0)
				PO = 1;
			else if(PO == 1)
				PO = 0;
				clrmous(*nx, *ny);
			button(600, 140, 639, 179, 2*PO);
			delay(200);
		}
		else if(mouse_press(600, 180, 639, 219) == 1)	//RE
		{
			button(600, 180, 639, 219, 1);
			DX = 0;
			DY = 0;
			A = 0;
			B = 0;
		}
		else if(mouse_press(600, 220, 639, 259) == 1)
		{
			button(600, 220, 639, 259, 1);
			percent += 0.05;

		}
		else if(mouse_press(600, 260, 639, 299) == 1)
		{
			button(600, 260, 639, 299, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
		}
		else if(mouse_press(600, 300, 639, 340) == 1)
		{
			button(600, 300, 639, 340, 1);
		}
		if(show == 1)
		{
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				if((X>145&&X<575)&&(Z>65&&Z<415))
				{
					ball(X, Z, 3, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
				delay(5);
			}
			//A+=0.01;
			//B+=0.01;
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(140, 60, 580, 420);
			//getch();
		}
		newmouse(nx, ny, nb);
		if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(*nx - oldx);
				A += 0.01*(*ny - oldy);
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (*nx - oldx);
				DY += (*ny - oldy);
			}
		}
		oldx = *nx;
		oldy = *ny;
	}
	return 0;
}

int tdedit(int *nx, int *ny, int *nb)
{int style[5] = {0, 2, 0, 0, 1}, h, w, edit = 0, pixnum = 0;
	char path[20] = {0};
	PIX pixlist[400];
	void far * balllist[400];
	setcolor(BLACK);
	//rectangle(2, 34, 118, 74);
	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	//rectangle(2, 74, 118, 114);
	printg_cn(45, 95, 0, style, "%Z", "清空");
	printg_cn(30, 135, 0, style, "%Z", "直接编辑");
	printg_cn(45, 175, 0, style, "%z", "保存");
	//putbmp(150, 50, "./pic/hust.bmp");
	//button(600, 440, 639, 479, 0);
	button(2, 440, 118, 477, 0); 	//退出
	button(2, 34, 118, 74, 0); 		//导入
	button(2, 75, 118, 115, 0); 	//清空
	button(2, 116, 118, 156, 0);	//直接编辑
	button(2, 157, 118, 197, 0);	//保存
	newmouse(nx, ny, nb);
	while (1)
	{
		if(mouse_press(2, 440, 118, 477) == 1)
		{
			button(2, 440, 118, 477, 1);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			clrmous(*nx, *ny);
			//bar(600, 440, 639, 479);
			bar(595, 95, 639, 345); 	
			bar(2, 34, 118, 439);//picedit panelclear
			delay(500);
			return 0;
		}
		else if(mouse_press(2, 34, 118, 74) == 1)
		{
			button(2, 34, 118, 74, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(picload(path) == 0)
			{
				putbmp(140, 60, path);
				//printf("w %d h %d", w, h);
				edit = 1;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
		}
		else if(mouse_press(2, 74, 118, 114) == 1)		//clear
		{
			button(2, 74, 118, 114, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm())
			{
				int i;
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(140, 60, 580, 420);
				bar(121, 440, 639, 479);
				setcolor(WHITE);
				rectangle(140-2, 60-2, 580+2, 420+2);
				edit = 0;
				for(i=0; i<pixnum; i++)
					free(balllist[i]);
				pixnum = 0;
			}
			else
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
			}
		}
		else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
        {
			//clrmous(*ny, *nx);
            button(639 - 30,64 - 30, 639, 64, 1);
            error(-1);
			setcolor(WHITE);
			rectangle(140-2, 60-2, 580+2, 420+2); 
			//edit = 1;
        }
		else if(mouse_press(2, 116, 118, 156) == 1)
		{
			button(2, 116, 118, 156, 1);
			edit = 1;
		}
		//edit part
		if(edit == 1)
		{
			int pen = 0;
			int YL, oldx = -1, oldy = -1;
			char str[20] = {0};
			//编辑功能栏
			button(600, 100, 639, 139, 0); 	//功能栏
			printg_cn(612, 120, BLACK, style, "%z", "笔");
			printg_cn(30, 460, WHITE, style, "%z", "退出绘点");
			button(600, 140, 639, 179, 0); 	//功能栏
			button(600, 180, 639, 219, 0); 	//功能栏
			button(600, 220, 639, 259, 0); 	//功能栏
			button(600, 260, 639, 299, 0); 	//功能栏
			button(600, 300, 639, 340, 0); 	//功能栏
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			// commandin(str, "z: ", 130, 455, 20);
			// YL = atoi(str);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			//printf("%d", ZL);
			bar3d(2, 300, 118, 439, DARKGRAY, 1);//scsreen
			while (1)										//绘制点位
			{
				int backout;
				
				if(mouse_press(600, 100, 639, 139) == 1)//pen
				{
					if(pen ==0)
						pen = 1;
					else
						pen = 0;
					//printf("%d", pen);
					button(600, 100, 639, 139, 2*pen);
					delay(200);
				}
				else if(mouse_press(600, 140, 639, 179) == 1)//功能待定
				{
					button(600, 140, 639, 179, 1);
				}
				else if(mouse_press(600, 180, 639, 219) == 1)
				{
					button(600, 180, 639, 219, 1);
				}
				else if(mouse_press(600, 220, 639, 259) == 1)
				{
					button(600, 220, 639, 259, 1);
				}
				else if(mouse_press(600, 260, 639, 299) == 1)
				{
					button(600, 260, 639, 299, 1);
				}
				else if(mouse_press(600, 300, 639, 340) == 1)
				{
					button(600, 300, 639, 340, 1);
				}
				else if(mouse_press(2, 440, 118, 477) == 1) //退出
				{	
					clrmous(*nx, *ny);
					setfillstyle(SOLID_FILL, RED);
					bar(2, 440, 118, 477);
					button(2, 440, 118, 477, 1);
					delay(500);
					edit = 0;
					break;
				}
				else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
				{
					//clrmous(*ny, *nx);
					button(639 - 30,64 - 30, 639, 64, 1);
					error(-1);
					setcolor(WHITE);
					rectangle(140-2, 60-2, 580+2, 420+2); 
					//edit = 1;
				}
				if(oldx != *nx || oldy != *ny)
				{
					int tempx, tempz, tempy=0;
					//防止出界
					tempx = *nx - XOFF>0? *nx - XOFF: 0;
					tempx = tempx-440 < 0? tempx: 440;
					tempz = *ny - YOFF>0? *ny - YOFF: 0;
					tempz = tempz-360 <0? tempz: 360;
					setfillstyle(SOLID_FILL, DARKGRAY);
					bar(4, 302, 116, 339);
					//140, 60, 580, 420
					printg_cn(10, 310, WHITE, style, "x= %d", tempx);
					printg_cn(10, 330, WHITE, style, "z= %d", tempy);
					printg_cn(10, 320, WHITE, style, "y= %d", tempz);
					oldx = *nx;
					oldy = *ny;
				}
				if(pen == 1)
				{
					int xp, yp;
					setcolor(BLACK);
					if(mouse_press_sup(140, 60, 580, 420, &xp, &yp) == 3)
					{
						int col, buffsize, key, zp;
						void far * ballbuff;
						buffsize = imagesize(0, 0, 8, 8);
						ballbuff = farmalloc(buffsize);
						clrmous(*nx, *ny);
						getimage(xp-4, yp-4, xp+4, yp+4, ballbuff);
						ball(xp, yp, 3, CYAN);
						bar3d(121, 440, 639, 479, DARKGRAY, 1);
						printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
						if(commandin(str, "color: ", 130, 455, 20) == 0)
						{

							col = atoi(str);
							bar3d(121, 440, 639, 479, DARKGRAY, 1);
							if(commandin(str, "zp: ", 130, 455, 20) == 0)
							{
								zp = atoi(str);
								ball(xp, yp, 3, col);
								setfillstyle(SOLID_FILL, LIGHTGRAY);
								bar(121, 440, 639, 479);
								pixlist[pixnum].x = xp - XOFF;
								pixlist[pixnum].y = zp;
								pixlist[pixnum].z = yp - YOFF;
								pixlist[pixnum].color = col;
								pixlist[pixnum].id = pixnum;
								setfillstyle(SOLID_FILL, RED);
								bar(80, 340, 88, 348);
								printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[pixnum].x);
								printg_cn(10, 370, WHITE, style, "zp= %d", pixlist[pixnum].y);
								printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[pixnum].z);
								while (1)
								{
									//clrmous(*nx, *ny);
									int flag = 0;
									key = bioskey(0)>>8;
									//printf("%d", key);
									putimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, ballbuff, COPY_PUT);
									switch (key)
									{
									case 1://esc
									case 28://enter
										flag = 1;
									break;
									case 72:
										pixlist[pixnum].z--; //up
									break;
									case 80:
										pixlist[pixnum].z++; //down
									break;
									case 75:
										pixlist[pixnum].x--; //left
									break;
									case 77:
										pixlist[pixnum].x++; //left
									break;
									case 12://-
										pixlist[pixnum].y--; //down
									break;
									case 13://-
										pixlist[pixnum].y++; //up
									break;
									default:
										break;
									}
									setfillstyle(SOLID_FILL, DARKGRAY);
									bar(4, 350, 116, 380);
									printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[pixnum].x);
									printg_cn(10, 370, WHITE, style, "zp= %d", pixlist[pixnum].y);
									printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[pixnum].z);
									getimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, pixlist[pixnum].x+XOFF+4, pixlist[pixnum].z+YOFF+4, ballbuff);
									ball(pixlist[pixnum].x+140, pixlist[pixnum].z+60, 3, col);
									if(flag == 1)
									{
										setfillstyle(SOLID_FILL, DARKGRAY);
										bar(4, 350, 116, 380);
										break;
									}
								}
								balllist[pixnum] = ballbuff;
								pixnum++;
								setfillstyle(SOLID_FILL, DARKGRAY);
								bar(4, 340, 116, 350);
								printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
							}
							
						}
						else
						{
							bar(121, 440, 639, 479);
						}
					}
					if(kbhit())		//撤回
					{
						backout = bioskey(0)>>8;
						//printf("%d", backout);
						switch (backout)
						{
						case 59://F1
							if(pixnum>0)
							{
								pixnum--;
								setfillstyle(SOLID_FILL, DARKGRAY);
								bar(4, 340, 116, 350);
								printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
								putimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, balllist[pixnum], COPY_PUT);
								pixlist[pixnum].id = -1;
							}
						break;
						}
					}
				}
				newmouse(nx, ny, nb);
			}
		}
		if(mouse_press(2, 157, 118, 197) == 1)
		{
			int i;
			if(pixnum > 0) // save the file
			{
				char savepath[30];
				button(2, 157, 118, 197, 1);
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				commandin(savepath, "path: ", 130, 455, 30);
				stream_write(savepath, &(pixlist[0].x), pixnum);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				stream_read(savepath, &(pixlist[0].x), &pixnum);
				//printf("ss %d", pixnum);
			}
			else
			{
				error(2);
			}
			for(i=0; i<pixnum; i++)
				free(balllist[i]);
			pixnum = 0;
		}
		newmouse(nx, ny, nb);
	}
	
}