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
#include "page5.h"
#include "tdedit.h"
#include <dir.h>


extern MX, MY;


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
	button(321, 0, 400, 30, 0);
	button(2, 440, 118, 477, 0);
	printg_cn(10, 15, BLACK, style, "%z", "平面编辑");
	
	printg_cn(90, 15, BLACK, style, "%z", "三维预览");
	printg_cn(170, 15, BLACK, style, "%z", "三维处理");
	printg_cn(250, 15, BLACK, style, "%z", "文件链接");
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
			clrmous(nx, ny);
			button(241, 0, 320, 30, 2);
			sector = 4;
		}
		else if(mouse_press(321, 0, 400, 30) == 1)
		{
			clrmous(nx, ny);
			button(321, 0, 400, 30, 2);
			sector = 5;
		}
		else
		{
			sector = 0;
		}
		if(mouse_press(2, 440, 118, 477) == 1)	//退出
		{
			button(2, 440, 118, 477, 1);
			delay(100);
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
			//clrmous(nx, ny);
			editpic(&nx, &ny, &nb);
			button(1, 0, 80, 30, 0);
		break;
		case 2:
			//clrmous(nx, ny);
			//tdedit(&nx, &ny, &nb);
			tdviwer(&nx, &ny, &nb);
			button(81, 0, 160, 30, 0);
		break;
		case 3:
			//clrmous(nx, ny);
			//tdviwer(&nx, &ny, &nb);
			tdtrans(&nx, &ny, &nb);
			button(161, 0, 240, 30, 0);
		break;
		case 4:
			//文件链接
			filelink(&nx, &ny, &nb);
			button(241, 0, 320, 30, 0);
			
		break;
		case 5:
			button(321, 0, 400, 30, 0);
		break;
		}
		if(temp > 0)
		{
			nylist[0] = temp;
		}
		newmouse(&nx, &ny, &nb);
		//delay(20);
	}
	return 0;
}

int editpic(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, h, w, edit = 0, buffsize, pixnum = 0;
	char path[20] = {0}, picpath[20] = {0};
	PIX pixlist[400];
	void far * ballbuff;
	float scale = 1;
	void far * balllist[400];
	buffsize = imagesize(0, 0, 8, 8);
	setcolor(BLACK);
	//rectangle(2, 34, 118, 74);
	printg_cn(30, 55, 0, style, "%Z", "导入图片"); 
	//rectangle(2, 74, 118, 114);
	printg_cn(45, 95, 0, style, "%Z", "清空");
	printg_cn(30, 135, 0, style, "%Z", "直接编辑");
	printg_cn(45, 175, 0, style, "%z", "保存");
	printg_cn(45, 215, 0, style, "%z", "导入");
	//putbmp(150, 50, "./pic/hust.bmp");
	//button(600, 440, 639, 479, 0);
	button(2, 440, 118, 477, 0); 	//退出
	button(2, 35, 118, 74, 0); 		//导入图片
	button(2, 75, 118, 114, 0); 	//清空
	button(2, 115, 118, 154, 0);	//直接编辑
	button(2, 155, 118, 194, 0);	//保存
	button(2, 195, 118, 234, 0);	//导入
	newmouse(nx, ny, nb);
	while (1)
	{
		if(mouse_press(2, 440, 118, 477) == 1) //退出
		{
			button(600, 100, 639, 139, 0);
			button(600, 140, 639, 179, 0);
			button(600, 180, 639, 219, 0);
			button(2, 440, 118, 477, 1);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			clrmous(*nx, *ny);
			//bar(600, 440, 639, 479);
			bar(595, 95, 639, 345); 	
			bar(2, 34, 118, 439);//picedit panelclear
			delay(500);
			return 0;
		}
		else if(mouse_press(2, 35, 118, 74) == 1) //导入图片
		{
			clrmous(*nx, *ny);
			button(2, 35, 118, 74, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				strcpy(picpath, path);
				bmpinfo(path, &w, &h);
				if((1.0*XSIZE/w)>(1.0*YSIZE/h))
				{
					scale = 1.0*YSIZE/h;
				}
				else
				{
					scale = 1.0*XSIZE/w;
				}
				//printf("%f", scale);
				h = h * scale;
				w = w * scale;
				putbmp_zoom(140+(XSIZE-w)/2, 60+(YSIZE-h)/2, path, scale, scale); //放置背景模板
				//printf("w %d h %d", w, h);
				edit = 1;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 0);
		}
		else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		{
			button(2, 75, 118, 114, 1);
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
				for(i=0; i<400; i++)
				{
					if(balllist[i] != NULL)
					{
						free(balllist[i]);
					}
					pixlist[i].x = 0;
					pixlist[i].y = 0;
					pixlist[i].z = 0; 
					pixlist[i].color = 0; 
					pixlist[i].id = -1; 
				}
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
		else if(mouse_press(2, 115, 118, 154) == 1)	//直接编辑
		{
			button(2, 115, 118, 154, 1);
			edit = 1;
		}
		else if(mouse_press(2, 195, 118, 234) == 1)
		{
			int k;
			clrmous(*nx, *ny);
			button(2, 195, 118, 234, 2);					//导入
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				if(stream_read(path, pixlist, &pixnum)!=-1)
					edit = 1;
			}
			for(k = 0; k<pixnum; k++)
			{
				ballbuff = farmalloc(buffsize);
				clrmous(*nx, *ny);
				getimage(pixlist[k].x-4+XOFF, pixlist[k].z-4+YOFF, pixlist[k].x+4+XOFF, pixlist[k].z+4+YOFF, ballbuff);
				balllist[k] = ballbuff;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 195, 118, 234, 0);
		}

		//edit part
		if(edit == 1)
		{
			int pen = 0, xyz = 0, del = 0, pix = 0;
			int YL=0, oldx = -1, oldy = -1, k;
			char str[20] = {0};
			printg_cn(30, 460, WHITE, style, "%z", "退出绘点");
			//编辑功能栏
			button(600, 100, 639, 139, 0); 	//笔
			printg_cn(612, 120, BLACK, style, "%z", "笔");
			button(600, 140, 639, 179, 0); 	//xyz
			printg_cn(608, 160, BLACK, style, "XYZ");
			button(600, 180, 639, 219, 0); 	//del
            printg_cn(608, 200, BLACK, style, "DEL");
			button(600, 220, 639, 259, 0); 	//PIXIDVIEW
			printg_cn(608, 240, BLACK, style, "PIX");
			button(600, 260, 639, 299, 0); 	//preview
			printg_cn(608, 280, BLACK, style, "PRV");
			button(600, 300, 639, 340, 0); 	//功能栏
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			commandin(str, "z: ", 130, 455, 20);
			YL = atoi(str);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			//printf("%d", ZL);
			bar3d(2, 300, 118, 439, DARKGRAY, 1);//scsreen
			if(pixnum>0)
			{
				for(k=0; k<pixnum; k++)
				{
					//printf("12\n");
					ballbuff = farmalloc(buffsize);
					getimage(pixlist[k].x+XOFF-4, pixlist[k].z+YOFF-4, pixlist[k].x+XOFF+4, pixlist[k].z+YOFF+4, ballbuff);
					if((pixlist[k].x+140>145&&pixlist[k].x+140<575)&&(pixlist[k].z+60>65&&pixlist[k].z+60<415))
					{
						ball(pixlist[k].x+140, pixlist[k].z+60, 3, pixlist[k].color);
					}
					//printf("%d %d %d\n", pixlist[k].x, pixlist[k].y, pixlist[k].z);
				}
			}

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
				else if(mouse_press(600, 140, 639, 179) == 1)   //xyz 直接坐标绘制点
				{
					if(xyz ==0)
					{
                        pen = 0;
                        xyz = 1;
						del = 0;
                    }
					else
						xyz = 0;
                    clrmous(*nx, *ny);
					button(600, 100, 639, 139, 2*pen);
					button(600, 140, 639, 179, 2*xyz);
					button(600, 180, 639, 219, 2*del);
					delay(200);
				}
				else if(mouse_press(600, 180, 639, 219) == 1) 	//del 删除特定点
				{
					button(600, 180, 639, 219, 1);
					if(del ==0)
					{
                        pen = 0;
                        xyz = 0;
						del = 1;
                    }
					else
						del = 0;
					clrmous(*nx, *ny);
					//printf("del %d\n", del);
					button(600, 100, 639, 139, 2*pen);
					button(600, 140, 639, 179, 2*xyz);
					button(600, 180, 639, 219, 2*del);
					delay(200);
				}
				else if(mouse_press(600, 220, 639, 259) == 1) //pixview
				{
					if(pix == 0)
					{
                    	pix = 1;
                    }
					else
					{
						pix = 0;
					}
					//printf("%d", pix);
					clrmous(*nx, *ny);
					button(600, 220, 639, 259, 2*pix);
					delay(200);
					
				}
				else if(mouse_press(600, 260, 639, 299) == 1)	//preview
				{
					{
						button(600, 260, 639, 299, 1);
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(595, 100, 639, 345);	//遮住原来的功能栏
						bar(2, 34, 118, 477);		//遮住原来的操作栏
						setfillstyle(SOLID_FILL, RED);
						bar(2, 440, 118, 477);
						button(2 , 440, 118, 477, 1);
						printg_cn(30, 460, WHITE, style, "%z", "退出预览");
					}	
					tdpreviwer(nx, ny, nb, pixlist, pixnum);
					//还原
					{
						int s;
						setfillstyle(SOLID_FILL, RED);
						bar(2, 440, 118, 477);
						printg_cn(30, 460, WHITE, style, "%z", "退出绘点");
						//编辑功能栏
						button(600, 100, 639, 139, 0); 	//笔
						printg_cn(612, 120, BLACK, style, "%z", "笔");
						button(600, 140, 639, 179, 0); 	//xyz
						printg_cn(608, 160, BLACK, style, "XYZ");
						button(600, 180, 639, 219, 0); 	//del
						printg_cn(608, 200, BLACK, style, "DEL");
						button(600, 220, 639, 259, 0); 	//PIXIDVIEW
						printg_cn(608, 240, BLACK, style, "PIX");
						button(600, 260, 639, 299, 0); 	//preview
						printg_cn(608, 280, BLACK, style, "PRV");
						button(600, 300, 639, 340, 0); 	//功能栏
						bar3d(121, 440, 639, 479, DARKGRAY, 1);
						// commandin(str, "z: ", 130, 455, 20);
						// YL = atoi(str);
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(121, 440, 639, 479);
						//printf("%d", ZL);
						bar3d(2, 300, 118, 439, DARKGRAY, 1);//scsreen
						setcolor(BLACK);
						//rectangle(2, 34, 118, 74);
						printg_cn(30, 55, 0, style, "%Z", "导入图片"); 
						//rectangle(2, 74, 118, 114);
						printg_cn(45, 95, 0, style, "%Z", "清空");
						printg_cn(30, 135, 0, style, "%Z", "直接编辑");
						printg_cn(45, 175, 0, style, "%z", "保存");
						printg_cn(45, 215, 0, style, "%z", "导入");
						//putbmp(150, 50, "./pic/hust.bmp");
						//button(600, 440, 639, 479, 0);
						button(2, 440, 118, 477, 0); 	//退出
						button(2, 35, 118, 74, 0); 		//导入
						button(2, 75, 118, 114, 0); 	//清空
						button(2, 115, 118, 154, 0);	//直接编辑
						button(2, 155, 118, 194, 0);	//保存
						button(2, 195, 118, 234, 0);	//导入
						//printf("%d", pixnum);
						if(picpath[0]!=0)
						{
							putbmp_zoom(140+(XSIZE-w)/2, 60+(YSIZE-h)/2, picpath, scale, scale); //放置背景模板
						}
						
						for(s=0; s<pixnum; s++)
						{
							ball(pixlist[s].x+XOFF, pixlist[s].z+YOFF, 3, pixlist[s].color);
						}
					}
				}
				else if(mouse_press(600, 300, 639, 340) == 1)
				{
					button(600, 300, 639, 340, 1);
				}
				else if(mouse_press(2, 440, 118, 477) == 1) //退出
				{	
					button(600, 100, 639, 139, 0);
					button(600, 140, 639, 179, 0);
					button(600, 180, 639, 219, 0);
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
				else if(mouse_press(2, 75, 118, 114) == 1)		//clear
				{
					button(2, 75, 118, 114, 1);
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
						for(i=0; i<400; i++)
						{
							if(balllist[i] != NULL)
							{
								free(balllist[i]);
							}
							pixlist[i].x = 0;
							pixlist[i].y = 0;
							pixlist[i].z = 0; 
							pixlist[i].color = 0; 
							pixlist[i].id = -1; 
						}
						pixnum = 0;
					}
					else
					{
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(121, 440, 639, 479);
					}
				}
				else if(mouse_press(2, 195, 118, 234) == 1)
				{
					int k;
					int pixn = 0;
					clrmous(*nx, *ny);
					button(2, 195, 118, 234, 2);					//导入
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					//printf("%d %d\n", pixnum, pixn);
					if(commandin(path, "path: ", 130, 455, 20) == 0)
					{
						if(stream_read(path, pixlist+pixnum, &pixn)!=-1)
							edit = 1;
					}
					//printf("%d %d\n", pixnum, pixn);
					clrmous(*nx, *ny);
					for(k = pixnum; k<pixnum+pixn; k++)
					{
						ballbuff = farmalloc(buffsize);
						getimage(pixlist[k].x-4+XOFF, pixlist[k].z-4+YOFF, pixlist[k].x+4+XOFF, pixlist[k].z+4+YOFF, ballbuff);
						pixlist[k].id +=pixnum;
						balllist[k] = ballbuff;
					}

					pixnum = pixnum + pixn;
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(121, 440, 639, 479);
					for(k=0; k<pixnum; k++)
					{
						ball(pixlist[k].x+XOFF, pixlist[k].z+YOFF, 3, pixlist[k].color);
					}
					button(2, 195, 118, 234, 0);	
				}
				else if(mouse_press(2, 155, 118, 194) == 1)
				{
					int i;
					if(pixnum > 0) // save the file
					{
						char savepath[30];
						clrmous(*nx, *ny);
						button(2, 155, 118, 194, 2);
						bar3d(121, 440, 639, 479, DARKGRAY, 1);
						// for(i=0; i<pixnum; i++)
						// {
						// 	printf("%d\t", pixlist[i].id);
						// }
						commandin(savepath, "path: ", 130, 455, 30);
						stream_write(savepath, pixlist, pixnum);
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(121, 440, 639, 479);
						//stream_read(savepath, &(pixlist[0].x), &pixnum);
						//printf("ss %d", pixnum);
						button(2, 155, 118, 194, 0);
					}
					else
					{
						error(2);
					}
					//for(i=0; i<pixnum; i++)
						//free(balllist[i]);
					//pixnum = 0;
				}
				else if(mouse_press(2, 35, 118, 74) == 1) //导入图片
				{
					int k;
					clrmous(*nx, *ny);
					button(2, 35, 118, 74, 2);
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(path, "path: ", 130, 455, 20) == 0)
					{
						strcpy(picpath, path);
						bmpinfo(path, &w, &h);
						if((1.0*XSIZE/w)>(1.0*YSIZE/h))
						{
							scale = 1.0*YSIZE/h;
						}
						else
						{
							scale = 1.0*XSIZE/w;
						}
						//printf("%f", scale);
						h = h * scale;
						w = w * scale;
						putbmp_zoom(140+(XSIZE-w)/2, 60+(YSIZE-h)/2, path, scale, scale); //放置背景模板
						//printf("w %d h %d", w, h);
						edit = 1;
				 	}
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(121, 440, 639, 479);
					for(k=0; k<pixnum; k++)
					{
						ball(pixlist[k].x+XOFF, pixlist[k].z+YOFF, 3, pixlist[k].color);
					}
					button(2, 35, 118, 74, 0);
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

				if(pix == 1) 				//pixlistview
				{
					int i, flag=0;
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					while (1)
					{
						if(kbhit())		//退出pixview
						{
							char key;
							key = bioskey(0)>>8;
							//printf("%d", key);
							if(key == 1)//esc
							{
								pix = 0;
								button(600, 220, 639, 259, 2*pix);
								setfillstyle(SOLID_FILL, LIGHTGRAY);
								bar(121, 440, 639, 479);
								break;
							}
						}
						else if(mouse_press(600, 220, 639, 259) == 1) //pixview
						{
							pix = 0;
							//printf("%d", pix);
							clrmous(*nx, *ny);
							button(600, 220, 639, 259, 2*pix);
							setfillstyle(SOLID_FILL, LIGHTGRAY);
							bar(121, 440, 639, 479);
							delay(200);
							break;
						}
						if(pixnum>0&& flag==1)
						{
							for(i=0; i<pixnum; i++)
							{
								if(mouse_press(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF) == 2)
								{
									bar3d(121, 440, 639, 479, DARKGRAY, 1);
									printg_cn(130, 455,WHITE, style, "x %d; y %d; z %d; color: %d; pixid: %d", pixlist[i].x, pixlist[i].z, pixlist[i].y, pixlist[i].color, pixlist[i].id);
									break;
								}
							}
						}
						if(mouse_press(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF) == 1)
						{
							//编辑
							int xp, yp;
							XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF);
							{
								int col, key, zp;
								//ballbuff = farmalloc(buffsize);
								clrmous(*nx, *ny);
								bar3d(121, 440, 639, 479, DARKGRAY, 1);
								//printg_cn(10, 340, WHITE, style, "point= %d", i);
								if(commandin(str, "color: ", 130, 455, 20) == 0)
								{
									char* str1[10], str2[10], str3[10];
									col = atoi(str);
									if(col==-1)
									{
										col = pixlist[i].color;
									}
									bar3d(121, 440, 639, 479, DARKGRAY, 1);
									if(commandin(str1, "xp: ", 130, 455, 10) == 0)
									{
										xp = atoi(str1);
									}
									else
									{
										xp = pixlist[i].x;
									}
									bar3d(121, 440, 639, 479, DARKGRAY, 1);
									if(commandin(str2, "yp: ", 130, 455, 10) == 0)
									{
										yp = atoi(str2);
									}
									else
									{
										yp = pixlist[i].z;
									}
									bar3d(121, 440, 639, 479, DARKGRAY, 1);
									if(commandin(str3, "zp: ", 130, 455, 10) == 0)
									{
										zp = atoi(str3);
									}
									else
									{
										zp = pixlist[i].y;
									}
									bar3d(121, 440, 639, 479, DARKGRAY, 1);
									{
										XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF); //off
										//printf("delay");
										//delay(5000);
										putimage(pixlist[i].x+XOFF-4, pixlist[i].z+YOFF-4, balllist[i], COPY_PUT);
										getimage(xp-4+XOFF, yp-4+YOFF, xp+4+XOFF, yp+4+YOFF, balllist[i]);
										//ball(xp, yp, 3, CYAN);
										ball(xp+XOFF, yp+YOFF, 3, col);
										pixlist[i].x = xp;
										pixlist[i].y = zp;
										pixlist[i].z = yp;
										pixlist[i].color = col;
										
										XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF); // on
										// setwritemode(XOR_PUT); 
										// 	for(j=0; j<11; j++)
										// 	{
										// 		line(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF+j, pixlist[i].x+5+XOFF, pixlist[i].z-5+YOFF+j);
										// 	}
										// 	setwritemode(COPY_PUT); 
										setfillstyle(SOLID_FILL, LIGHTGRAY);
										bar(121, 440, 639, 479);
										
										//pixlist[i].id = i;
										setfillstyle(SOLID_FILL, RED);
										bar(100, 340, 108, 348);
										printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[i].x);
										printg_cn(10, 370, WHITE, style, "zp= %d", pixlist[i].y);
										printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[i].z);
										//printf("key");
										while (1)
										{
											int flag = 0;
											clrmous(*nx, *ny);
											//printf("key");
											key = bioskey(0)>>8;
											//printf("%d", key);
											XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF); //off
											putimage(pixlist[i].x+XOFF-4, pixlist[i].z+YOFF-4, balllist[i], COPY_PUT);
											switch (key)
											{
												case 1://esc
												case 28://enter
													flag = 1;
												break;
												case 72:
													pixlist[i].z--; //up
												break;
												case 80:
													pixlist[i].z++; //down
												break;
												case 75:
													pixlist[i].x--; //left
												break;
												case 77:
													pixlist[i].x++; //left
												break;
												case 12://-
													pixlist[i].y--; //down
												break;
												case 13://-
													pixlist[i].y++; //up
												break;
												default:
													break;
											}
											setfillstyle(SOLID_FILL, DARKGRAY);
											bar(4, 350, 116, 380);
											printg_cn(10, 350, WHITE, style, "xp= %d", pixlist[i].x);
											printg_cn(10, 370, WHITE, style, "zp= %d", pixlist[i].y);
											printg_cn(10, 360, WHITE, style, "yp= %d", pixlist[i].z);
											//XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF); 
											getimage(pixlist[i].x+XOFF-4, pixlist[i].z+YOFF-4, pixlist[i].x+XOFF+4, pixlist[i].z+YOFF+4, balllist[i]);
											ball(pixlist[i].x+140, pixlist[i].z+60, 3, col);
											XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF); //on
											if(flag == 1)
											{
												setfillstyle(SOLID_FILL, DARKGRAY);
												bar(4, 350, 116, 380);
												XOR_mark(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF, pixlist[i].x+5+XOFF, pixlist[i].z+5+YOFF);	//off
												break;
											}
										}
										//balllist[i] = ballbuff;
										setfillstyle(SOLID_FILL, DARKGRAY);
										bar(4, 340, 116, 350);
										//printg_cn(10, 340, WHITE, style, "point= %d", i);
									}
								
								}
								else
								{
									int j;
									setfillstyle(SOLID_FILL, LIGHTGRAY);
									bar(121, 440, 639, 479);
									//setwritemode(XOR_PUT); 
									// for(j=0; j<11; j++)
									// {
									// 	line(pixlist[i].x-5+XOFF, pixlist[i].z-5+YOFF+j, pixlist[i].x+5+XOFF, pixlist[i].z-5+YOFF+j);
									// }
									// setwritemode(COPY_PUT); 
								}
							}

							// if(kbhit())		//撤回
							// {
							// 	backout = bioskey(0)>>8;
							// 	//printf("%d", backout);
							// 	switch (backout)
							// 	{
							// 	case 59://F1
							// 		if(i>0)
							// 		{
							// 			i--;
							// 			setfillstyle(SOLID_FILL, DARKGRAY);
							// 			bar(4, 340, 116, 350);
							// 			printg_cn(10, 340, WHITE, style, "point= %d", i);
							// 			putimage(pixlist[i].x+XOFF-4, pixlist[i].z+YOFF-4, balllist[i], COPY_PUT);
							// 			pixlist[i].id = -1;
							// 		}
							// 	break;
							// 	}
							// }
							bar3d(121, 440, 639, 479, DARKGRAY, 1);
						}
						flag = newmouse(nx, ny, nb);
					}
				}
				if(pen == 1)
				{
					int xp, yp;
					setcolor(BLACK);
					if(mouse_press_sup(140, 60, 580, 420, &xp, &yp) == 3)
					{
						int col, key;
						
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
							bar(100, 340, 108, 348);
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
							putimage(xp-4, yp-4, ballbuff, COPY_PUT);
							free(ballbuff);
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
				else if(xyz == 1) //xyz_edit
                {
                    int xp, yp;
					setcolor(BLACK);
					if(mouse_press_sup(140, 60, 580, 420, &xp, &yp) == 3)
					{
						int col, key, zp;
						ballbuff = farmalloc(buffsize);
						clrmous(*nx, *ny);
						bar3d(121, 440, 639, 479, DARKGRAY, 1);
						printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
						if(commandin(str, "color: ", 130, 455, 20) == 0)
						{
                            char* str1[10], str2[10], str3[10];
							col = atoi(str);
							bar3d(121, 440, 639, 479, DARKGRAY, 1);
                            commandin(str1, "xp: ", 130, 455, 10);
                            bar3d(121, 440, 639, 479, DARKGRAY, 1);
                            commandin(str2, "yp: ", 130, 455, 10);
                            bar3d(121, 440, 639, 479, DARKGRAY, 1);
                            commandin(str3, "zp: ", 130, 455, 10);
                            bar3d(121, 440, 639, 479, DARKGRAY, 1);
							{
								xp = atoi(str1);
                                yp = atoi(str2);
                                zp = atoi(str3);
                                getimage(xp-4+XOFF, yp-4+YOFF, xp+4+XOFF, yp+4+YOFF, ballbuff);
						        //ball(xp, yp, 3, CYAN);
								ball(xp+XOFF, yp+YOFF, 3, col);
								setfillstyle(SOLID_FILL, LIGHTGRAY);
								bar(121, 440, 639, 479);
								pixlist[pixnum].x = xp;
								pixlist[pixnum].y = zp;
								pixlist[pixnum].z = yp;
								pixlist[pixnum].color = col;
								pixlist[pixnum].id = pixnum;
								setfillstyle(SOLID_FILL, RED);
								bar(100, 340, 108, 348);
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
				else if(del == 1)		//删除指定点
				{
					int pixid;
					clrmous(*nx, *ny);
					//printf("qw");
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "pixid: ", 130, 455, 20) == 0)
					{
						pixid = atoi(str);
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(121, 440, 639, 479);
						if(pixid < pixnum && pixid >= 0)
						{
							
							setwritemode(XOR_PUT); 
							XOR_mark(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF, pixlist[pixid].x+5+XOFF, pixlist[pixid].z+5+YOFF);
							bar3d(121, 440, 639, 479, DARKGRAY, 1);
							if(confirm() == 1)
							{
								int j;
								XOR_mark(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF, pixlist[pixid].x+5+XOFF, pixlist[pixid].z+5+YOFF);
								
								putimage(pixlist[pixid].x+XOFF-4, pixlist[pixid].z+YOFF-4, balllist[pixid], COPY_PUT);
								free(balllist[pixid]);
								pixnum--;
								for(j=pixid; j<pixnum; j++)
								{
									pixlist[j] = pixlist[j+1];
								}
								
								// for(i=pixid; i<pixnum; i++)
								// {
								// 	balllist[i] = balllist[i+1];
								// }
								bar(4, 340, 116, 350);
								printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
							}
							else
							{
								XOR_mark(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF, pixlist[pixid].x+5+XOFF, pixlist[pixid].z+5+YOFF);
							}
							
						}
						
						// if(pixnum>0)
						// {
						// 	pixnum--;
						// 	setfillstyle(SOLID_FILL, DARKGRAY);
						// 	bar(4, 340, 116, 350);
						// 	printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
						// 	putimage(pixlist[pixnum].x+XOFF-4, pixlist[pixnum].z+YOFF-4, balllist[pixnum], COPY_PUT);
						// 	pixlist[pixnum].id = -1;
						// }
					}
					else
					{
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(121, 440, 639, 479);
						del = 0;
						button(600, 180, 639, 219, 2*del);
					}
					
				}
				newmouse(nx, ny, nb);
			}
		}
		
		if(mouse_press(2, 155, 118, 194) == 1)
		{
			int i;
			if(pixnum > 0) // save the file
			{
				char savepath[30];
				clrmous(*nx, *ny);
				button(2, 155, 118, 194, 2);
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				commandin(savepath, "path: ", 130, 455, 30);
				stream_write(savepath, pixlist, pixnum);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				//stream_read(savepath, pixlist, &pixnum);
				//printf("ss %d", pixnum);
				button(2, 155, 118, 194, 0);
			}
			else
			{
				error(2);
			}
			//for(i=0; i<pixnum; i++)
				//free(balllist[i]);
			//pixnum = 0;
		}
		newmouse(nx, ny, nb);
	}
	
}

int picload(char * path)	//弃用
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
	int style[5] = {0, 2, 0, 0, 1}, show = 0, update = 1, pixnum, i, SP = 0,RO = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	PIX pixlist[400];
	float A = 0, B = 0,C=0, percent = 1;
	int X, Y, Z;
	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	printg_cn(45, 95, 0, style, "%Z", "清空");
	button(2, 35, 118, 74, 0); 		//导入
	button(2, 75, 118, 114, 0); 	//清空
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	bar3d(140, 60, 580, 420, DARKGRAY, 1);
	printg_cn(612, 120, BLACK, style, "RO");
	printg_cn(612, 160, BLACK, style, "PO");
	printg_cn(612, 200, BLACK, style, "SP");
	printg_cn(612, 240, BLACK, style, "RE");
	printg_cn(616, 280, BLACK, style, "+");
	printg_cn(616, 320, BLACK, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//SP
	button(600, 220, 639, 259, 0); 	//RE
	button(600, 260, 639, 299, 0); 	//+
	button(600, 300, 639, 340, 0); 	//-
	bar3d(5, 120, 115, 200, DARKGRAY, 1);
	printg_cn(10, 130, WHITE, style, "dx: %d", DX);
	printg_cn(10, 140, WHITE, style, "dy: %d", DY);
	printg_cn(10, 150, WHITE, style, "A: %d", (int)(A*180/3.14159));
	printg_cn(10, 160, WHITE, style, "B: %d", (int)(C*180/3.14159));
	printg_cn(10, 170, WHITE, style, "C: %d", (int)(B*180/3.14159));
	printg_cn(10, 180, WHITE, style, "percent: %d.%d",(int)(percent/1), ((int)(percent*10))%10);
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
		else if(mouse_press(2, 35, 118, 74) == 1) //导入
		{
			char path[20];
			clrmous(*nx, *ny);
			button(2, 35, 118, 74, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				if(stream_read(path, pixlist, &pixnum)!=-1)
					show = 1;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 0);
		}
		else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		{
			button(2, 75, 118, 114, 1);
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
			clrmous(*nx, *ny);
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
			update = 1;
			percent = 1;
			
		}
		else if(mouse_press(600, 260, 639, 299) == 1)	//+
		{
			button(600, 260, 639, 299, 1);
			percent += 0.05;
			update = 1;
			
		}
		else if(mouse_press(600, 300, 639, 340) == 1)	//-
		{
			button(600, 300, 639, 340, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
			update = 1;
		}
		
		if(show == 1&& update == 1)
		{
			clrmous(*nx, *ny);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(140, 60, 580, 420);
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				if((X>145&&X<575)&&(Z>65&&Z<415))
				{
					ball(X, Z, 3, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			move_3d_p(20, 0, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 20, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 0, 20, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			//A+=0.01;
			//B+=0.01;
			//getch();
			update = 0;
		}
		newmouse(nx, ny, nb);
		//delay(10);
		if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(*nx - oldx);
				A += 0.01*(*ny - oldy);
				update = 1;
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (*nx - oldx);
				DY += (*ny - oldy);
				update = 1;
			}
		}
		if(SP == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				C += - 0.01*(*ny - oldy);
				update = 1;
			}
		}
		if(oldx != *nx||oldy != *ny)
		{
			bar3d(5, 120, 115, 200, DARKGRAY, 1);
			printg_cn(10, 130, WHITE, style, "dx: %d", DX);
			printg_cn(10, 140, WHITE, style, "dy: %d", DY);
			printg_cn(10, 150, WHITE, style, "A: %d", (int)(A*180/3.14159));
			printg_cn(10, 160, WHITE, style, "B: %d", (int)(C*180/3.14159));
			printg_cn(10, 170, WHITE, style, "C: %d", (int)(B*180/3.14159));
			printg_cn(10, 180, WHITE, style, "percent: %d.%d",(int)(percent/1), ((int)(percent*10))%10);
		}
		oldx = *nx;
		oldy = *ny;
		
	}
	return 0;
}

int tdtrans(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 0, update = 1, pixnum = 0, i, RO = 0, PO = 0, SP = 0, oldx, oldy, DX = 0, DY = 0;
	PIX pixlist[400];
	float A = 0, B = 0, C = 0, percent = 1;
	int X, Y, Z;
	button(2, 440, 118, 477, 0); 	//退出

	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	printg_cn(45, 95, 0, style, "%Z", "清空");
	button(2, 35, 118, 74, 0); 		//导入
	button(2, 75, 118, 114, 0); 	//清空
	//
	printg_cn(45, 135, 0, style, "%Z", "位置");
	printg_cn(45, 175, 0, style, "%z", "角度");
	printg_cn(45, 215, 0, style, "%z", "拉伸");
	printg_cn(45, 255, 0, style, "%z", "旋转");
	printg_cn(45, 295, 0, style, "%z", "保存");
	printg_cn(45, 335, 0, style, "%z", "刷新");
	//putbmp(150, 50, "./pic/hust.bmp");
	//button(600, 440, 639, 479, 0);
	button(2, 115, 118, 154, 0);	//位置
	button(2, 155, 118, 194, 0);	//角度
	button(2, 195, 118, 234, 0);	//拉伸
	button(2, 235, 118, 274, 0);	//旋转
	//button(2, 275, 118, 314, 0);	//合并
	button(2, 315, 118, 355, 0);	//刷新
	button(2, 275, 118, 314, 0);
	//
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	bar3d(140, 60, 580, 420, DARKGRAY, 1);
	printg_cn(612, 120, BLACK, style, "RO");
	printg_cn(612, 160, BLACK, style, "PO");
	printg_cn(612, 200, BLACK, style, "SP");
	printg_cn(612, 240, BLACK, style, "RE");
	printg_cn(616, 280, BLACK, style, "+");
	printg_cn(616, 320, BLACK, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//SP
	button(600, 220, 639, 259, 0); 	//RE
	button(600, 260, 639, 299, 0); 	//+
	button(600, 300, 639, 340, 0); 	//-
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
		else if(mouse_press(2, 35, 118, 74) == 1) //导入
		{
			char path[20];
			int k, pixn;
			button(2, 35, 118, 74, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				if(stream_read(path, pixlist+pixnum, &pixn)!=-1)
					show = 1;
			}
			for(k = pixnum; k<pixnum+pixn; k++)
			{
				pixlist[k].id += pixnum;
			}
			pixnum += pixn;
			/*
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
				if(stream_read(path, pixlist+pixnum, &pixn)!=-1)
					edit = 1;
			}
			//printf("%d %d\n", pixnum, pixn);
			for(k = pixnum; k<pixnum+pixn; k++)
			{
				ballbuff = farmalloc(buffsize);
				clrmous(*nx, *ny);
				getimage(pixlist[k].x-4+XOFF, pixlist[k].z-4+YOFF, pixlist[k].x+4+XOFF, pixlist[k].z+4+YOFF, ballbuff);
				pixlist[k].id +=pixnum;
				balllist[k] = ballbuff;
			}
			*/
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 1);
		}
		else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		{
			button(2, 75, 118, 114, 1);
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
			button(2, 35, 118, 74, 1);
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
			update = 1;
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
			clrmous(*nx, *ny);
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
			update = 1;
			percent = 1;
			
		}
		else if(mouse_press(600, 260, 639, 299) == 1)	//+
		{
			button(600, 260, 639, 299, 1);
			percent += 0.05;
			update = 1;
			
		}
		else if(mouse_press(600, 300, 639, 340) == 1)	//-
		{
			button(600, 300, 639, 340, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
			update = 1;
		}
		
		if(show == 1)
		{
			if(mouse_press(2, 115, 118, 154) == 1)
			{
				char strx[10], stry[10], strz[10];
				int dx=0, dy=0, dz=0;
				button(2, 115, 118, 154, 2);	//位置
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strx, "dx: ", 130, 455, 10)==0)
				{
					printf("strz %s\n", strz);
					dx = atoi(strx);
				}
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(stry, "dy: ", 130, 455, 10)==0)
				{
					dz = atoi(stry);
				}
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strz, "dz: ", 130, 455, 10)==0)
				{
					
					dy = atoi(strz);
				}
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				for(i=0; i<pixnum; i++)
				{
					pixlist[i].x += dx;
					pixlist[i].y += dy;
					pixlist[i].z += dz;
				}
				bar3d(140, 60, 580, 420, DARKGRAY, 1);
				// for(i=0; i<pixnum; i++)
				// {
				// 	move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				// 	move_3d_yaxis((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				// 	if((X>145&&X<575)&&(Z>65&&Z<415))
				// 	{
				// 		ball(X, Z, 3, pixlist[i].color);
				// 	}
				// 	//printf("%d", pixlist[i].x);
				// 	//printf(" %d\n", X);
				// }
				update = 1;
				button(2, 115, 118, 154, 0);	//位置
			}
			else if(mouse_press(2, 155, 118, 194)==1)
			{
				
				char strx[10]={0}, stry[10]={0}, strz[10]={0};
				int dx=0, dy=0, dz=0;
				float xf, yf, zf;
				button(2, 155, 118, 194, 2);	//角度
				//printf("sss");
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strx, "x: ", 130, 455, 10)==0)
				{
					dx = atoi(strx);
				}
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(stry, "y: ", 130, 455, 10)==0)
				{
					dz = atoi(stry);
				}
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strz, "z: ", 130, 455, 10)==0)
				{
					dy = atoi(strz);
				}
				//printf("%d, %d, %d\n", dx, dy, dz);
				xf = 1.0 * dx /180 * 3.14159;
				yf = 1.0 * dy /180 * 3.14159;
				zf = 1.0 * dz /180 * 3.14159;
				//printf("%f, %f, %f\n", xf, yf, zf);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				for(i=0; i<pixnum; i++)
				{
					move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), xf, zf, &X, &Y, &Z, 0, 0, 0, 1);
					move_3d_yaxis((float)X, (float)Y, (float)Z, yf, &X, &Y, &Z, XSIZE/2, 0, YSIZE/2, 1);
					pixlist[i].x = X;
					pixlist[i].y = Y;
					pixlist[i].z = Z;
				}
				bar3d(140, 60, 580, 420, DARKGRAY, 1);
				// for(i=0; i<pixnum; i++)
				// {
				// 	move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				// 	move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				// 	if((X>145&&X<575)&&(Z>65&&Z<415))
				// 	{
				// 		ball(X, Z, 3, pixlist[i].color);
				// 	}
				// 	//printf("%d", pixlist[i].x);
				// 	//printf(" %d\n", X);
				// }
				update = 1;
				button(2, 155, 118, 194, 0);	//角度
				
			}
			else if(mouse_press(2, 275, 118, 314)==1)
			{
				int i;
				button(2, 275, 118, 314, 2);
				//button(2, 315, 118, 355, 2);	//保存
				if(pixnum > 0) // save the file
				{
					char savepath[30];
					clrmous(*nx, *ny);
					
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					// for(i=0; i<pixnum; i++)
					// {
					// 	printf("%d\t", pixlist[i].id);
					// }
					commandin(savepath, "path: ", 130, 455, 30);
					stream_write(savepath, pixlist, pixnum);
					setfillstyle(SOLID_FILL, LIGHTGRAY);
					bar(121, 440, 639, 479);
					//stream_read(savepath, &(pixlist[0].x), &pixnum);
					//printf("ss %d", pixnum);
				}
				else
				{
					error(2);
				}
				//for(i=0; i<pixnum; i++)
					//free(balllist[i]);
				//pixnum = 0;
				//button(2, 315, 118, 355, 0);	//保存
				update = 1;
				button(2, 275, 118, 314, 0);
			}
			else if(mouse_press(2, 195, 118, 234) == 1)
			{
				char direction[10], step[10], distance[10];
				int dir=0, stp=1, dst=10, i, j, raw;
				button(2, 195, 118, 234, 2);	//拉伸
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(direction, "x/y/z: ", 130, 455, 10)==0)
				{
					if(strcmp("x", direction) == 0)
					{
						dir = 1;
					} 
					else if(strcmp("y", direction) == 0)
					{
						dir = 3;
					}
					else if(strcmp("z", direction) == 0)
					{
						dir = 2;
					}
				}
				if (dir!=0)
				{
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(step, "step: ", 130, 455, 10)==0)
					{
						stp = atoi(step);
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(distance, "distance: ", 130, 455, 10)==0)
					{
						dst = atoi(distance);
					}
				
					raw = pixnum;
					switch (dir)
					{
					case 1:
						for(i=1; i<stp+1; i++)
						{
							for(j=0; j<raw; j++)
							{
								pixlist[j+i*raw].x = pixlist[j].x + dst*i;
								pixlist[j+i*raw].y = pixlist[j].y;
								pixlist[j+i*raw].z = pixlist[j].z;
								pixlist[j+i*raw].color = pixlist[j].color;
								pixlist[j+i*raw].id = pixlist[j].id + raw*i;
							}
						}
					break;
					case 2:
						for(i=1; i<stp+1; i++)
						{
							for(j=0; j<raw; j++)
							{
								pixlist[j+i*raw].x = pixlist[j].x;
								pixlist[j+i*raw].y = pixlist[j].y+ dst*i;
								pixlist[j+i*raw].z = pixlist[j].z;
								pixlist[j+i*raw].color = pixlist[j].color;
								pixlist[j+i*raw].id = pixlist[j].id + raw*i;
							}
						}
					break;
					case 3:
						for(i=1; i<stp+1; i++)
						{
							for(j=0; j<raw; j++)
							{
								pixlist[j+i*raw].x = pixlist[j].x;
								pixlist[j+i*raw].y = pixlist[j].y;
								pixlist[j+i*raw].z = pixlist[j].z+ dst*i;
								pixlist[j+i*raw].color = pixlist[j].color;
								pixlist[j+i*raw].id = pixlist[j].id + raw*i;
							}
						}
					break;
					}
					pixnum = pixnum * (stp+1);
				}
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				update = 1;
				button(2, 195, 118, 234, 0);	//拉伸
			}
			else if(mouse_press(2, 235, 118, 274) == 1)
			{
				char direction[10], step[10], angle[10];
				int dir=0, stp=1, ang=10, i, j, raw;
				float anglef;
				button(2, 235, 118, 274, 2);
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(direction, "x/y/z: ", 130, 455, 20)==0)
				{
					if(strcmp("x", direction) == 0)
					{
						dir = 1;
					} 
					else if(strcmp("y", direction) == 0)
					{
						dir = 3;
					}
					else if(strcmp("z", direction) == 0)
					{
						dir = 2;
					}
				}
				if (dir!=0)
				{
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(step, "step: ", 130, 455, 20)==0)
					{
						stp = atoi(step);
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(angle, "angle: ", 130, 455, 20)==0)
					{
						ang = atoi(angle);
					}
					anglef = 1.0 * ang /180 * 3.14159;
				
				raw = pixnum;
				//printf("%d %f\n", ang, anglef);
				switch (dir)
				{
				case 1:
					for(i=1; i<stp+1; i++)
					{
						for(j=0; j<raw; j++)
						{
							move_3d_p((float)(pixlist[j].x-XSIZE/2), (float)(pixlist[j].y), (float)(pixlist[j].z-YSIZE/2), anglef*i, 0, &X, &Y, &Z, 0, 0, 0, 1);
							move_3d_yaxis((float)X, (float)Y, (float)Z, 0, &X, &Y, &Z, XSIZE/2, 0, YSIZE/2, 1);
							pixlist[j+i*raw].x = X;
							pixlist[j+i*raw].y = Y;
							pixlist[j+i*raw].z = Z;
							pixlist[j+i*raw].color = pixlist[j].color;
							pixlist[j+i*raw].id = pixlist[j].id + raw*i;
						}
					}
				break;
				case 2:
					for(i=1; i<stp+1; i++)
					{
						for(j=0; j<raw; j++)
						{
							move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), 0, 0, &X, &Y, &Z, 0, 0, 0, 1);
							move_3d_yaxis((float)X, (float)Y, (float)Z, anglef*i, &X, &Y, &Z, XSIZE/2, 0, YSIZE/2, 1);
							pixlist[j+i*raw].x = X;
							pixlist[j+i*raw].y = Y;
							pixlist[j+i*raw].z = Z;
							pixlist[j+i*raw].color = pixlist[j].color;
							pixlist[j+i*raw].id = pixlist[j].id + raw*i;
						}
					}
				break;
				case 3:
					
					for(i=1; i<stp+1; i++)
					{
						for(j=0; j<raw; j++)
						{
							move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), 0, anglef*i, &X, &Y, &Z, 0, 0, 0, 1);
							move_3d_yaxis((float)X, (float)Y, (float)Z, 0, &X, &Y, &Z, XSIZE/2, 0, YSIZE/2, 1);
							pixlist[j+i*raw].x = X;
							pixlist[j+i*raw].y = Y;
							pixlist[j+i*raw].z = Z;
							pixlist[j+i*raw].color = pixlist[j].color;
							pixlist[j+i*raw].id = pixlist[j].id + raw*i;
						}
					}
				break;
				}
				pixnum = pixnum * (stp+1);
			}
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				update = 1;
				button(2, 235, 118, 274, 1);
			}
			if(mouse_press(2, 315, 118, 355)==1)
			{
				button(2, 315, 118, 355, 1);	//刷新
				update = 1;
			}
		}


		if(show == 1&& update == 1)
		{
			clrmous(*nx, *ny);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(140, 60, 580, 420);
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				if((X>145&&X<575)&&(Z>65&&Z<415))
				{
					ball(X, Z, 3, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			//显示坐标轴
			move_3d_p(20, 0, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 20, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 0, 20, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			//A+=0.01;
			//B+=0.01;
			//C+=0.01;
			//getch();
			update = 0;
		}
		newmouse(nx, ny, nb);
		//delay(10);
		if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(*nx - oldx);
				A += 0.01*(*ny - oldy);
				update = 1;
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (*nx - oldx);
				DY += (*ny - oldy);
				update = 1;
			}
		}
		if(SP == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				C += - 0.01*(*ny - oldy);
				update = 1;
			}
		}
		oldx = *nx;
		oldy = *ny;
		
	}
	return 0;
}

int tdpreviwer(int *nx, int *ny, int *nb, PIX *pixlist, int pixnum)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 1, update = 1, i, RO = 0, SP = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	float A = 0, B = 0, C = 0, percent = 1;
	int X, Y, Z;
	//printg_cn(45, 55, 0, style, "%Z", "导入"); 
	//printg_cn(45, 95, 0, style, "%Z", "清空");
	//button(2, 35, 118, 74, 0); 		//导入
	//button(2, 75, 118, 114, 0); 	//清空
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	bar3d(140, 60, 580, 420, DARKGRAY, 1);
	printg_cn(612, 120, BLACK, style, "RO");
	printg_cn(612, 160, BLACK, style, "PO");
	printg_cn(612, 200, BLACK, style, "SP");
	printg_cn(612, 240, BLACK, style, "RE");
	printg_cn(616, 280, BLACK, style, "+");
	printg_cn(616, 320, BLACK, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//SP
	button(600, 220, 639, 259, 0); 	//RE
	button(600, 260, 639, 299, 0); 	//+
	button(600, 300, 639, 340, 0); 	//-
	//printf("%d", pixlist[0].color);
	bar3d(5, 40, 115, 120, DARKGRAY, 1);
	printg_cn(10, 50, WHITE, style, "dx: %d", DX);
	printg_cn(10, 60, WHITE, style, "dy: %d", DY);
	printg_cn(10, 70, WHITE, style, "A: %d", (int)(A*180/3.14159));
	printg_cn(10, 80, WHITE, style, "B: %d", (int)(C*180/3.14159));
	printg_cn(10, 90, WHITE, style, "C: %d", (int)(B*180/3.14159));
	printg_cn(10, 100, WHITE, style, "percent: %d.%d",(int)(percent/1), ((int)(percent*10))%10);
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
		//else if(mouse_press(2, 35, 118, 74) == 1) //导入
		// {
		// 	char path[20];
		// 	button(2, 35, 118, 74, 1);
		// 	bar3d(121, 440, 639, 479, DARKGRAY, 1);
		// 	if(commandin(path, "path: ", 130, 455, 20) == 0)
		// 	{
		// 		if(stream_read(path, &(pixlist[0].x), &pixnum)!=-1)
		// 			show = 1;
		// 	}
		// 	setfillstyle(SOLID_FILL, LIGHTGRAY);
		// 	bar(121, 440, 639, 479);
		// }
		// else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		// {
		// 	button(2, 75, 118, 114, 1);
		// 	bar3d(121, 440, 639, 479, DARKGRAY, 1);
		// 	if(confirm())
		// 	{
		// 		setfillstyle(SOLID_FILL, LIGHTGRAY);
		// 		bar(140, 60, 580, 420);
		// 		bar(121, 440, 639, 479);
		// 		bar3d(140, 60, 580, 420, DARKGRAY, 1);
		// 	}
		// 	else
		// 	{
		// 		setfillstyle(SOLID_FILL, LIGHTGRAY);
		// 		bar(121, 440, 639, 479);
		// 	}
		// }
		// else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
        // {
		// 	//clrmous(*ny, *nx);
        //     button(639 - 30,64 - 30, 639, 64, 1);
        //     error(-1);
		// 	//setcolor(WHITE);
		// 	//rectangle(140-2, 60-2, 580+2, 420+2); 
		// 	//edit = 1;
		// 	bar3d(140, 60, 580, 420, DARKGRAY, 1);
        // }
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
			clrmous(*nx, *ny);
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
			update = 1;
			percent = 1;
			
		}
		else if(mouse_press(600, 260, 639, 299) == 1)	//+
		{
			button(600, 260, 639, 299, 1);
			percent += 0.05;
			update = 1;
			
		}
		else if(mouse_press(600, 300, 639, 340) == 1)	//-
		{
			button(600, 300, 639, 340, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
			update = 1;
		}
		
		if(show == 1&& update == 1)
		{
			clrmous(*nx, *ny);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(140, 60, 580, 420);
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, percent);
				if((X>145&&X<575)&&(Z>65&&Z<415))
				{
					ball(X, Z, 3, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			move_3d_p(20, 0, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 20, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			move_3d_p(0, 0, 20, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, XOFF+XSIZE/2+DX, 0, YOFF+YSIZE/2+DY, 1);
			setcolor(WHITE);
			line(XOFF+XSIZE/2+DX,  YOFF+YSIZE/2+DY, X, Z);
			//A+=0.01;
			//B+=0.01;
			//getch();
			update = 0;
		}
		newmouse(nx, ny, nb);
		//delay(10);
		if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(*nx - oldx);
				A += 0.01*(*ny - oldy);
				update = 1;
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (*nx - oldx);
				DY += (*ny - oldy);
				update = 1;
			}
		}
		if(SP == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				C += - 0.01*(*ny - oldy);
				update = 1;
			}
		}
		if(oldx != *nx||oldy != *ny)
		{
			bar3d(5, 40, 115, 120, DARKGRAY, 1);
			printg_cn(10, 50, WHITE, style, "dx: %d", DX);
			printg_cn(10, 60, WHITE, style, "dy: %d", DY);
			printg_cn(10, 70, WHITE, style, "A: %d", (int)(A*180/3.14159));
			printg_cn(10, 80, WHITE, style, "B: %d", (int)(C*180/3.14159));
			printg_cn(10, 90, WHITE, style, "C: %d", (int)(B*180/3.14159));
			printg_cn(10, 100, WHITE, style, "percent: %d.%d",(int)(percent/1), ((int)(percent*10))%10);
		}
		oldx = *nx;
		oldy = *ny;
		
	}
	return 0;
}

int filelink(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, filenum=0, pixnum1=0, i, remake, view = 0;
	int prjflag = 0, frnum = 0;
	PIX pixlist1[400];// pixlist2[400];
	FRAME STEP[200];

	char prjdir[30]={0}, filename[10]={0};
	float A = 0, B = 0, C = 0, percent = 1;
	int X, Y, Z;
	printg_cn(30, 55, 0, style, "%Z", "新建工程"); 
	printg_cn(30, 95, 0, style, "%Z", "添加文件"); 
	printg_cn(30, 135, 0, style, "%Z", "撤销添加");
	printg_cn(30, 175, 0, style, "%Z", "导入工程");
	printg_cn(30, 215, 0, style, "%Z", "关闭工程");
	printg_cn(38, 255, 0, style, "%Z", "创建流");
	printg_cn(38, 295, 0, style, "%Z", "保存流");
	button(2, 35, 118, 74, 0);		//新建工程
	button(2, 75, 118, 114, 0);		//添加文件
	button(2, 115, 118, 154, 0); 	//撤回
	button(2, 155, 118, 194, 0); 	//导入工程
	button(2, 195, 118, 234, 0);	//关闭工程
	button(2, 235, 118, 274, 0);	//创建流
	button(2, 275, 118, 314, 0);	//保存流
	
	bar3d(5, 350, 115, 420, DARKGRAY, 1);
	printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
	printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
	while (1)
	{
		if(mouse_press(2, 35, 118, 74) == 1 && prjflag == 0)	//新建工程
		{
			clrmous(*nx, *ny);
			button(2, 35, 118, 74, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(prjdir, "dir: ", 130, 455, 20) == 0)
			{
				creatconf(prjdir);
				prjflag = 1;
				filenum = 0;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 0);
			bar3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			
		}
		else if(mouse_press(2, 75, 118, 114) == 1 && prjflag == 1) ////添加文件
		{
			char path[20];
			clrmous(*nx, *ny);
			button(2, 75, 118, 114, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
					clearpixlist(pixlist1, &pixnum1, 400);
					if(stream_read(path, pixlist1, &pixnum1) != -1)
					{
						filenum ++;
						//printf("num: %d", filenum);
						updatenum(prjdir, &filenum, &frnum);
						chdir(prjdir);
						formatname(filenum, filename);
						stream_write(filename, pixlist1, pixnum1);
						//printf("%s\n", filename);
						chdir("../");
						view = 1;
						bar3d(5, 350, 115, 420, DARKGRAY, 1);
						printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
						printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
						if(filenum > 0)
						{
							int k;
							char tempname[20] = {0};
							for(k=0; k<filenum; k++)
							{
								formatname(k, tempname);
								button(BASEX, BASEY+16*(k-1), BASEX+200, BASEY+16*k-1, 0);
								printg_cn(BASEX+5, BASEY+16*(k-1)+4, WHITE, style, tempname);
							}
						}
					}
				
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 75, 118, 114, 0);
		}
		else if(mouse_press(639 - 30,64 - 30, 639, 64) == 1 && error(0))	//error
        {
			//clrmous(*ny, *nx);
            button(639 - 30,64 - 30, 639, 64, 1);
            error(-1);
			//setcolor(WHITE);
			rectangle(140-2, 60-2, 580+2, 420+2); 
			//edit = 1;
			//bar3d(140, 60, 580, 420, DARKGRAY, 1);
        }
		else if(mouse_press(2, 115, 118, 154) == 1 && prjflag == 1)
		{
			button(2, 115, 118, 154, 2); //撤销添加
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm()==1)
			{
				formatname(filenum, filename);
				remove(filename);
				if(filenum>0)
				{
					filenum --;
					if(filenum > 0)
					{
						int k;
						char tempname[20] = {0};
						for(k=1; k<filenum+1; k++)
						{
							formatname(k, tempname);
							button(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1, 0);
							printg_cn(BASEX+5, BASEY+16*(k-1)+4, WHITE, style, tempname);
						}
					}
				}
				updatenum(prjdir, &filenum, &frnum);
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 115, 118, 154, 0);
			bar3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
		}
		else if(mouse_press(2, 440, 118, 477) == 1)//退出
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
		else if(mouse_press(2, 155, 118, 194) == 1 && prjflag == 0)
		{
			//导入工程
			int i;
			clrmous(*nx, *ny);
			button(2, 155, 118, 194, 2);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(prjdir, "dir: ", 130, 455, 20) == 0)
			{
				//creatconf(prjdir);
				if(openconf(prjdir, &filenum, &frnum)!= -1&& loadframe(prjdir, STEP, frnum) != -1)
				{
					// for(i=0; i<frnum; i++)
					// {
					// 	printf("%d %d %d %d %d %f %f %f %f\n",
					// 		STEP[i].fileid, STEP[i].cycles, 
					// 		STEP[i].dx, STEP[i].dy, STEP[i].dz, 
					// 		STEP[i].dA, STEP[i].dB, STEP[i].dC, STEP[i].percent);
					// }
					prjflag = 1;
					//printf("num %d", filenum);
					if(filenum > 0)
					{
						int k;
						char tempname[20] = {0};
						for(k=1; k<filenum+1; k++)
						{
							formatname(k, tempname);
							button(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1, 0);
							printg_cn(BASEX+5, BASEY+16*(k-1)+4, WHITE, style, tempname);
						}
					}
				}
				
			}
			bar3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 155, 118, 194, 0);
		}
		else if(mouse_press(2, 195, 118, 234)==1)
		{
			button(2, 195, 118, 234, 1);	//关闭工程
			prjflag = 0;
			filenum = 0;
			pixnum1 = 0;
			clearpixlist(pixlist1, &pixnum1, 400);
			bar3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
		}
		else if(mouse_press(2, 235, 118, 274)==1)
		{
			char str[20];
			button(2, 235, 118, 274, 2);	//创建流
			while (1)
			{
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(str, "fileid: ", 130, 455, 20) == 0)
				{
					STEP[frnum].fileid = atoi(str);
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "cycles: ", 130, 455, 20) == 0)
					{
						STEP[frnum].cycles = atoi(str);
						if(STEP[frnum].cycles<=0)
						{
							STEP[frnum].cycles = 1;
						}
					}
					else
					{
						STEP[frnum].cycles = 1;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dx: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dx = atoi(str);
					}
					else
					{
						STEP[frnum].dx = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dy: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dz = atoi(str);
					}
					else
					{
						STEP[frnum].dz = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dz: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dy = atoi(str);
					}
					else
					{
						STEP[frnum].dy = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dA: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dA = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dA = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dB: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dC = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dC = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dC: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dB = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dB = 0;
					}
					bar3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "percent: ", 130, 455, 20) == 0)
					{
						STEP[frnum].percent = 1.0 * atoi(str)/100;
					}
					else
					{
						STEP[frnum].percent = 1;
					}
					frnum ++;
					bar3d(5, 350, 115, 420, DARKGRAY, 1);
					printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
					printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
				}
				else
				{
					break;
				}
			}
			
			button(2, 235, 118, 274, 0);	//创建流
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
		}
		else if(mouse_press(2, 275, 118, 314)==1)
		{
			char str[20];
			button(2, 275, 118, 314, 2);	//保存流
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			// if(commandin(str, ": ", 130, 455, 20) == 0)
			// {
			// 	STEP[frnum].dz = atoi(str);
			// }
			saveframe(prjdir, STEP, frnum);
			updatenum(prjdir, &filenum, &frnum);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
			bar(121, 440, 639, 479);
			button(2, 275, 118, 314, 0);	//保存流
		}
		if(filenum > 0)
		{
			int k;
			char tempname[20] = {0};
			for(k=1; k<filenum+1; k++)
			{
				formatname(k, tempname);
				if(mouse_press(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1) == 1)
				{
					button(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1, 1);
					chdir(prjdir);
					if(stream_read(tempname, pixlist1, &pixnum1) != -1)
					{
						view = 1;
					}
					chdir("../");
				}
			}
		}
		if(view == 1)
		{
			{
				button(600, 260, 639, 299, 1);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				//bar(595, 100, 639, 345);	//遮住原来的功能栏
				bar(2, 34, 118, 477);		//遮住原来的操作栏
				setfillstyle(SOLID_FILL, RED);
				bar(2, 440, 118, 477);
				button(2 , 440, 118, 477, 1);
				printg_cn(30, 460, WHITE, style, "%z", "退出预览");
			}
			tdpreviwer(nx, ny, nb, pixlist1, pixnum1);
			{
				printg_cn(30, 55, 0, style, "%Z", "新建工程"); 
				printg_cn(30, 95, 0, style, "%Z", "添加文件"); 
				printg_cn(30, 135, 0, style, "%Z", "撤销添加");
				printg_cn(30, 175, 0, style, "%Z", "导入工程");
				printg_cn(30, 215, 0, style, "%Z", "关闭工程");
				printg_cn(38, 255, 0, style, "%Z", "创建流");
				printg_cn(38, 295, 0, style, "%Z", "保存流");
				button(2, 35, 118, 74, 0);		//新建工程
				button(2, 75, 118, 114, 0);		//添加文件
				button(2, 115, 118, 154, 0); 	//撤回
				button(2, 155, 118, 194, 0); 	//导入工程
				button(2, 195, 118, 234, 0);	//关闭工程
				button(2, 235, 118, 274, 0);	//创建流
				button(2, 275, 118, 314, 0);	//保存流
				bar3d(5, 350, 115, 420, DARKGRAY, 1);
				printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
				printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
				if(filenum > 0)
				{
					int k;
					char tempname[20] = {0};
					for(k=1; k<filenum+1; k++)
					{
						formatname(k, tempname);
						button(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1, 0);
						printg_cn(BASEX+5, BASEY+16*(k-1)+4, WHITE, style, tempname);
					}
				}
			}
			view = 0;
		}
		newmouse(nx, ny, nb);
	}
	return 0;
}

int clearpixlist(PIX * pixlist, int * pixnum, int num)
{
	int i;
	for(i=0; i<num; i++)
	{
		pixlist[i].x = XSIZE/2;
		pixlist[i].y = 0;
		pixlist[i].z = YSIZE/2;
		pixlist[i].color = 0;
		pixlist[i].id = -1;
	}
	*pixnum = 0;
	return 0;
}
