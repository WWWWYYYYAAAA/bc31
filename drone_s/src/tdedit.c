#include "tdedit.h"


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

int filelink(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, filenum=0, pixnum1=0, i, remake, view = 0;
	int prjflag = 0, frnum = 0;
	PIX pixlist1[LISTSIZE];// pixlist2[LISTSIZE];
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
	
	bar_3d(5, 350, 115, 420, DARKGRAY, 1);
	printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
	printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
	while (1)
	{
		if(mouse_press(2, 35, 118, 74) == 1 && prjflag == 0)	//新建工程
		{
			clrmous(*nx, *ny);
			button(2, 35, 118, 74, 2);
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(prjdir, "dir: ", 130, 455, 20) == 0)
			{
				creatconf(prjdir);
				prjflag = 1;
				filenum = 0;
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 0);
			bar_3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			
		}
		else if(mouse_press(2, 75, 118, 114) == 1 && prjflag == 1) ////添加文件
		{
			char path[20];
			clrmous(*nx, *ny);
			button(2, 75, 118, 114, 2);
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(path, "path: ", 130, 455, 20) == 0)
			{
					clearpixlist(pixlist1, &pixnum1, LISTSIZE);
					if(stream_read(path, pixlist1, &pixnum1) != -1)
					{
						filenum ++;
						//printf("num: %d", filenum);
						updatenum(prjdir, &filenum, &frnum);
						chdir(prjdir);
						formatname(filenum, filename);
						stream_write(filename, pixlist1, pixnum1);
						//printf("%s\n", filename);
						chdir("..");
						view = 1;
						bar_3d(5, 350, 115, 420, DARKGRAY, 1);
						printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
						printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(XOFF, YOFF, XOFF+XSIZE, YOFF+YSIZE);
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
			//bar_3d(140, 60, 580, 420, DARKGRAY, 1);
        }
		else if(mouse_press(2, 115, 118, 154) == 1 && prjflag == 1)
		{
			button(2, 115, 118, 154, 2); //撤销添加
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(XOFF, YOFF, XOFF+XSIZE, YOFF+YSIZE);
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
			bar_3d(5, 350, 115, 420, DARKGRAY, 1);
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
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
						setfillstyle(SOLID_FILL, LIGHTGRAY);
						bar(XOFF, YOFF, XOFF+XSIZE, YOFF+YSIZE);
						for(k=1; k<filenum+1; k++)
						{
							formatname(k, tempname);
							button(BASEX, BASEY+16*(k-1), BASEX+150, BASEY+16*k-1, 0);
							printg_cn(BASEX+5, BASEY+16*(k-1)+4, WHITE, style, tempname);
						}
					}
				}
				
			}
			bar_3d(5, 350, 115, 420, DARKGRAY, 1);
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
			clearpixlist(pixlist1, &pixnum1, LISTSIZE);
			bar_3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
		}
		else if(mouse_press(2, 235, 118, 274)==1)
		{
			char str[20];
			button(2, 235, 118, 274, 2);	//创建流
			while (1)
			{
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(str, "fileid: ", 130, 455, 20) == 0)
				{
					STEP[frnum].fileid = atoi(str);
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dx: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dx = atoi(str);
					}
					else
					{
						STEP[frnum].dx = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dy: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dz = atoi(str);
					}
					else
					{
						STEP[frnum].dz = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dz: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dy = atoi(str);
					}
					else
					{
						STEP[frnum].dy = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dA: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dA = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dA = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dB: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dC = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dC = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "dC: ", 130, 455, 20) == 0)
					{
						STEP[frnum].dB = 1.0 * atoi(str) /180 * 3.14159;
					}
					else
					{
						STEP[frnum].dB = 0;
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(str, "percent: ", 130, 455, 20) == 0)
					{
						STEP[frnum].percent = 1.0 * atoi(str)/100;
					}
					else
					{
						STEP[frnum].percent = 1;
					}
					frnum ++;
					bar_3d(5, 350, 115, 420, DARKGRAY, 1);
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
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			// if(commandin(str, ": ", 130, 455, 20) == 0)
			// {
			// 	STEP[frnum].dz = atoi(str);
			// }
			saveframe(prjdir, STEP, frnum);
			updatenum(prjdir, &filenum, &frnum);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar_3d(5, 350, 115, 420, DARKGRAY, 1);
			printg_cn(10, 360, WHITE, style, "filenum: %d", filenum);
			printg_cn(10, 370, WHITE, style, "frnum: %d", frnum);
			setfillstyle(SOLID_FILL, LIGHTGRAY);
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
					chdir("..");
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
				bar_3d(5, 350, 115, 420, DARKGRAY, 1);
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

int outfinal(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 0, update = 1, pixnum, i, SP = 0,RO = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	int count = 0, globalnum = 0;
	PIX pixlist[LISTSIZE];
	char dir[10]={0}, filename[10]={0};
	float A = 0, B = 0,C=0, percent = 1;
	int X, Y, Z;
	printg_cn(45, 55, 0, style, "%Z", "导入"); 
	printg_cn(45, 95, 0, style, "%Z", "关闭");
	button(2, 35, 118, 74, 0); 		//导入
	button(2, 75, 118, 114, 0); 	//清空
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	//bar_3d(140, 60, 580, 420, DARKGRAY, 1);
	setfillstyle(SOLID_FILL, BLACK);
	bar(140, 60, 580, 420);
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
	bar_3d(5, 120, 115, 200, DARKGRAY, 1);
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
			clrmous(*nx, *ny);
			button(2, 35, 118, 74, 2);
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			if(commandin(dir, "path: ", 130, 455, 10) == 0)
			{
				//if(stream_read(path, pixlist, &pixnum)!=-1)
				playtofile(dir);
				count = getnum(dir);
				show = 1;
				//printf("%d\n", count);
			}
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 0);
		}
		else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		{
			button(2, 75, 118, 114, 1);
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm())
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(140, 60, 580, 420);
				bar(121, 440, 639, 479);
				bar_3d(140, 60, 580, 420, DARKGRAY, 1);
				show = 0;
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
			bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
			
			globalnum ++;
			if(chdir(dir)==0)
			{
			if(chdir("output")==0)
			{
			formatname(globalnum, filename);
			clearpixlist(pixlist, &pixnum, LISTSIZE);
			//strcat(filename, ".txt");
			//stream_read(filename, pixlist, &pixnum);
			//printf("%s\n", filename);
			//printf("%d\n", globalnum);
			//delay(5000);
			//printf("%d\n", pixnum);
			readdronetxt(filename, pixlist, &pixnum);
			clrmous(*nx, *ny);
			setfillstyle(SOLID_FILL, BLACK);
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
			//update = 0;
			chdir("..");
			}
			chdir("..");
			}
			if(globalnum == count)
			{
				globalnum = 0;
			}
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
			bar_3d(5, 120, 115, 200, DARKGRAY, 1);
			printg_cn(10, 130, WHITE, style, "dx: %d", DX);
			printg_cn(10, 140, WHITE, style, "dy: %d", DY);
			printg_cn(10, 150, WHITE, style, "A: %d", (int)(A*180/3.14159));
			printg_cn(10, 160, WHITE, style, "B: %d", (int)(C*180/3.14159));
			printg_cn(10, 170, WHITE, style, "C: %d", (int)(B*180/3.14159));
			printg_cn(10, 180, WHITE, style, "percent: %d.%d",(int)(percent/1), ((int)(percent*10))%10);
		}
		oldx = *nx;
		oldy = *ny;
		delay(20);
	}
	return 0;
}

int tdpreviwer(int *nx, int *ny, int *nb, PIX *pixlist, int pixnum)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 1, update = 1, i, RO = 0, SP = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	float A = 0, B = 0, C = 0, percent = 1;
	int X, Y, Z;
	setcolor(LIGHTGRAY);
	rectangle(140-2, 60-2, 580+2, 420+2);
	bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
	bar_3d(5, 40, 115, 120, DARKGRAY, 1);
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
			bar_3d(5, 40, 115, 120, DARKGRAY, 1);
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

int tdtrans(int *nx, int *ny, int *nb)
{
	int style[5] = {0, 2, 0, 0, 1}, show = 0, update = 1, pixnum = 0, i, RO = 0, PO = 0, SP = 0, oldx, oldy, DX = 0, DY = 0;
	PIX pixlist[LISTSIZE];
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
	bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
			
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(121, 440, 639, 479);
			button(2, 35, 118, 74, 1);
		}
		else if(mouse_press(2, 75, 118, 114) == 1)		//clear
		{
			button(2, 75, 118, 114, 1);
			bar_3d(121, 440, 639, 479, DARKGRAY, 1);
			if(confirm())
			{
				setfillstyle(SOLID_FILL, LIGHTGRAY);
				bar(140, 60, 580, 420);
				bar(121, 440, 639, 479);
				bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
			bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strx, "dx: ", 130, 455, 10)==0)
				{
					printf("strz %s\n", strz);
					dx = atoi(strx);
				}
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(stry, "dy: ", 130, 455, 10)==0)
				{
					dz = atoi(stry);
				}
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
				bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(strx, "x: ", 130, 455, 10)==0)
				{
					dx = atoi(strx);
				}
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
				if(commandin(stry, "y: ", 130, 455, 10)==0)
				{
					dz = atoi(stry);
				}
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
				bar_3d(140, 60, 580, 420, DARKGRAY, 1);
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
					
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
				update = 1;
				button(2, 275, 118, 314, 0);
			}
			else if(mouse_press(2, 195, 118, 234) == 1)
			{
				char direction[10], step[10], distance[10];
				int dir=0, stp=1, dst=10, i, j, raw;
				button(2, 195, 118, 234, 2);	//拉伸
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(step, "step: ", 130, 455, 10)==0)
					{
						stp = atoi(step);
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
				bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
					if(commandin(step, "step: ", 130, 455, 20)==0)
					{
						stp = atoi(step);
					}
					bar_3d(121, 440, 639, 479, DARKGRAY, 1);
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
