#include "page1.h"

int page1()
{
	int nx , ny, nb, temp, part = 1, i, swch=0;
	int mousig[10] = {0};
	int nylist[10] = {0};
	int style[5] = {0, 2, 0, 0, 1}, filenum=0, filevect=0, dronenum=0;
	char prjlist[3][20] = {"EPRJ1", "EPRJ2", "EPRJ3"};
	char * prjvect, name[20] = {0};
	float signal1;
	PIX dronelist[LISTSIZE];
	bar2d(0, 0, 639, 479, LIGHTGRAY);
	bar_3d(0, 0, 100, 480, LIGHTGRAY, 0);
	bar_3d(100, 0, 639, 20, LIGHTGRAY, 0);
	bar_3d(440, 21, 639, 479, DARKGRAY, 1);
	bar2d(442, 24, 637, 200, BLACK);//little screen
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
	printg_cn(20, 40, BLACK, style,"%z", "第一部分");
	printg_cn(20, 80, BLACK, style,"%z", "第二部分");
	printg_cn(20, 120, BLACK, style,"%z", "第三部分");
	printg_cn(28, 160, BLACK, style,"%z", "自定义");
	//int openconf(char * prjdir, int *filenum, int *frnum)

	//初始化小窗
	prjvect = prjlist[part-1];
	filenum = getnum(prjvect);
	if(swch++%BLANK==0)
		filevect ++;
	if(chdir(prjvect)==0)
	{
		if(chdir("output")==0)
		{
		formatname(filevect, name);
		readdronetxt(name, dronelist, &dronenum);
		for(i=0; i<dronenum; i++)
		{
			ball_base((dronelist[i].x)*SCALE+XLS, (dronelist[i].z)*SCALE+YLS, 1, dronelist[i].color);
		}
		chdir("..");
		}
		chdir("..");
	}
	while(1)
	{
		if(mouse_press(0, 20, 98, 59) == 1)
		{
			button(0, 20, 98, 59, 1);
			part = 1;
			//更新小窗向量
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//更新小窗向量
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 60, 98, 99) == 1)
		{
			button(0, 60, 98, 99, 1);
			part = 2;
			//更新小窗向量
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//更新小窗向量
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(130, 40, 180, 60);
		}
		else if(mouse_press(0, 100, 98, 139) == 1)
		{
			button(0, 100, 98, 139, 1);
			part = 3;
			//更新小窗向量
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//更新小窗向量
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
		if(part>=1 && part<=3)
		{
			if(swch++%BLANK==0)
			{
				filevect += 50;
				swch = 1;
			if(filevect >= filenum)
			{
				filevect = 1;
			}
			if(chdir(prjvect)==0)
			{
				if(chdir("output")==0)
				{
					formatname(filevect, name);
					//stream_read(name, dronelist, &dronenum);
					readdronetxt(name, dronelist, &dronenum);
					bar2d(442, 55, 637, 200, BLACK);
					for(i=0; i<dronenum; i++)
					{
						ball_base((dronelist[i].x)*SCALE+XLS, (dronelist[i].z)*SCALE+YLS, 1, dronelist[i].color);
					}
					chdir("..");
				}
				//printf("%s\n", name);
				chdir("..");
			}
			}
			if(filevect >= filenum)
			{
				filevect = 1;
			}
		}
		newmouse(&nx, &ny, &nb);
		temp = slider(617, 201, nx, ny, 20, 278, 0, 0, &signal1);
//switch part
		switch(part)
		{
			case 1:
			// //bar2d(442, 55, 637, 200, BLACK);
			// printg(130, 40, 0, "part %d", part);
			// if(mouse_press(442, 24, 472, 54) == 1)
			// {
			// 	button(442, 24, 472, 54, 1);
			// 	return 2;
			// }
			// break;
			case 2:
			// //bar2d(442, 55, 637, 200, BLACK);
			// printg(130, 40, 0, "part %d", part);
			// if(mouse_press(442, 24, 472, 54) == 1)
			// {
			// 	button(442, 24, 472, 54, mousig[3]);
			// 	return 3;
			// }
			// break;
			case 3:
			//bar2d(442, 55, 637, 200, BLACK);
			//printg(130, 40, 0, "part %d", part);
			if(mouse_press(442, 24, 472, 54) == 1)
			{
				button(442, 24, 472, 54, mousig[3]);
				clrmous(nx, ny);
				return part+1;
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