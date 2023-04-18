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



int XOR_mark(int x1, int y1, int x2, int y2)
{
	int j, h;
	h = y2 - y1 + 1;
	setcolor(WHITE);
	setwritemode(XOR_PUT); 
	for(j=0; j<h; j++)
	{
	 	line(x1, y1 + j, x2, y1 + j);
	}
	setwritemode(COPY_PUT); 
	return 0;
}

int tdedit(int *nx, int *ny, int *nb)
{
	
	int style[5] = {0, 2, 0, 0, 1}, h, w, edit = 0, buffsize, pixnum = 0;
	char path[20] = {0};
	PIX pixlist[200];
	float scale = 1;
	void far * balllist[200];
	void far * ballbuff;
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
	button(2, 35, 118, 74, 0); 		//导入
	button(2, 75, 118, 114, 0); 	//清空
	button(2, 115, 118, 154, 0);	//直接编辑
	button(2, 155, 118, 194, 0);	//保存
	button(2, 195, 118, 234, 0);	//导入
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
		else if(mouse_press(2, 35, 118, 74) == 1)
		{
			button(2, 35, 118, 74, 1);
			bar3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
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
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
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
		else if(mouse_press(2, 115, 118, 154) == 1)
		{
			button(2, 115, 118, 154, 1);
			edit = 1;
		}
		else if(mouse_press(2, 195, 118, 234) == 1)
		{
			int k;
			button(2, 195, 118, 234, 1);					//导入
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
		}
		//edit part
		if(edit == 1)
		{
			int pen = 0, xyz = 0, del = 0, pix = 0;
			int YL, oldx = -1, oldy = -1, k;
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
			// commandin(str, "z: ", 130, 455, 20);
			// YL = atoi(str);
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
                    {
                        pen = 1;
                        xyz = 0;
						del = 0;
                    }
					else
						pen = 0;
					clrmous(*nx, *ny);
                   	button(600, 100, 639, 139, 2*pen);
					button(600, 140, 639, 179, 2*xyz);
					button(600, 180, 639, 219, 2*del);
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
						int col, key, zp;
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
							setfillstyle(SOLID_FILL, LIGHTGRAY);
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
							int j;
							setwritemode(XOR_PUT); 
							for(j=0; j<11; j++)
							{
								line(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF+j, pixlist[pixid].x+5+XOFF, pixlist[pixid].z-5+YOFF+j);
							}
							setwritemode(COPY_PUT); 
							bar3d(121, 440, 639, 479, DARKGRAY, 1);
							if(confirm() == 1)
							{
								int i;
								setwritemode(XOR_PUT); 
								for(i=0; i<11; i++)
								{
									line(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF+i, pixlist[pixid].x+5+XOFF, pixlist[pixid].z-5+YOFF+i);
								}
								setwritemode(COPY_PUT); 
								putimage(pixlist[pixid].x+XOFF-4, pixlist[pixid].z+YOFF-4, balllist[pixid], COPY_PUT);
								pixnum--;
								for(i=pixid; i<pixnum; i++)
								{
									pixlist[i] = pixlist[i+1];
								}
								free(balllist[pixid]);
								for(i=pixid; i<pixnum; i++)
								{
									balllist[i] = balllist[i+1];
								}
								bar(4, 340, 116, 350);
								printg_cn(10, 340, WHITE, style, "point= %d", pixnum);
							}
							else
							{
								int i;
								setwritemode(XOR_PUT); 
								for(i=0; i<11; i++)
								{
									line(pixlist[pixid].x-5+XOFF, pixlist[pixid].z-5+YOFF+i, pixlist[pixid].x+5+XOFF, pixlist[pixid].z-5+YOFF+i);
								}
								setwritemode(COPY_PUT); 
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
				button(2, 155, 118, 194, 1);
				bar3d(121, 440, 639, 479, DARKGRAY, 1);
				commandin(savepath, "path: ", 130, 455, 30);
				stream_write(savepath, pixlist, pixnum);
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(121, 440, 639, 479);
				stream_read(savepath, pixlist, &pixnum);
				//printf("ss %d", pixnum);
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