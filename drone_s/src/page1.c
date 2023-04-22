#include "page1.h"

int page1()
{
	int nx , ny, nb, temp, part = 1, i, swch=0;
	int mousig[10] = {0};
	int nylist[10] = {0};
	int style[5] = {0, 2, 0, 0, 1}, filenum=0, filevect=0, dronenum=0;
	int style1[5] = {0, 2, 0, 0, 3};
	int style2[5] = {0, 2, 0, 0, 2};
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

	printg_cn(130, 40, BLACK, style1, "%z %z", "第一部分", "回顾历史");
	//华中科技大学见证了中国高教事业的两次大发展，被誉为“新中国高等教育发展的缩影。
	//早在共和国曙光初亮时，华中工学院于1953年应运而生，于1988年成长为华中理科大学。
	
//而原华中理工大学、同济医科大学、武汉城市建设学院和科技部干部管理学院于2000年合并，在千禧年的新生中，华中科技大学也终于破壳而出。
	printg_cn(110, 95, BLACK, style, "    %z", "华中科技大学见证了中国高教事业的两次");
	printg_cn(110, 115, BLACK, style, "%z,%z", "大发展","被誉为新中国高等教育发展的缩影。");
	printg_cn(110, 135, BLACK, style, "%z,%z1953%z", "早在共和国曙光初亮时","华中工学院于", "年");
	printg_cn(110, 155, BLACK, style, "%z,%z1988%z", "应运而生","于","年成长为华中理科大学。而");
	printg_cn(110, 175, BLACK, style, "%z,%z,%z", "原华中理工大学","同济医科大学","武汉城市建设");
	printg_cn(110, 195, BLACK, style, "%z2000%z,%z", "学院和科技部干部管理学院于","年合并", "并");
	printg_cn(110, 215, BLACK, style, "%z,%z", "千禧年的新生中","华中科技大学也终于破壳而");
	printg_cn(110, 235, BLACK, style, "%z", "出。");
	printg_cn(450, 220, WHITE, style, "1.%z", "华工于武汉诞生");
	printg_cn(450, 240, WHITE, style, "2.%z", "华中理工大学诞生");
	printg_cn(450, 260, WHITE, style, "3.%z", "同济医学院");
	printg_cn(450, 280, WHITE, style, "4.%z", "华中科技大学合并");
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
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "第一部分", "回顾历史");
			printg_cn(110, 95, BLACK, style, "    %z", "华中科技大学见证了中国高教事业的两次");
			printg_cn(110, 115, BLACK, style, "%z,%z", "大发展","被誉为新中国高等教育发展的缩影。");
			printg_cn(110, 135, BLACK, style, "%z,%z1953%z", "早在共和国曙光初亮时","华中工学院于", "年");
			printg_cn(110, 155, BLACK, style, "%z,%z1988%z", "应运而生","于","年成长为华中理科大学。而");
			printg_cn(110, 175, BLACK, style, "%z,%z,%z", "原华中理工大学","同济医科大学","武汉城市建设");
			printg_cn(110, 195, BLACK, style, "%z2000%z,%z", "学院和科技部干部管理学院于","年合并", "并");
			printg_cn(110, 215, BLACK, style, "%z,%z", "千禧年的新生中","华中科技大学也终于破壳而");
			printg_cn(110, 235, BLACK, style, "%z", "出。");
			printg_cn(450, 220, WHITE, style, "1.%z", "华工于武汉诞生");
			printg_cn(450, 240, WHITE, style, "2.%z", "华中理工大学诞生");
			printg_cn(450, 260, WHITE, style, "3.%z", "同济医学院");
			printg_cn(450, 280, WHITE, style, "4.%z", "华中科技大学合并");
			//printg_cn(110, 135, BLACK, style, "%z", "");
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
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "第二部分", "着眼当下");
			printg_cn(110, 95, BLACK, style, "    %z,%z,%z,%z", "校园树木葱茏","碧草如茵","环境优雅","景色");
			printg_cn(110, 115, BLACK, style, "%z,%z", "秀丽","被誉为“森林式大学”。学校教学科研");
			printg_cn(110, 135, BLACK, style, "%z", "支撑体系完备，各项公共服务设施齐全。学校");
			printg_cn(110, 155, BLACK, style, "%z,%z", "实施“人才兴校”战略","师资力量雄厚。学校");
			printg_cn(110, 175, BLACK, style, "%z,%z", "贯彻建设“学生","学者与学术的大学”的教育");
			printg_cn(110, 195, BLACK, style, "%z,%z,%z,%z", "思想","秉承“育人为本","创新是魂","责任以行”");
			printg_cn(110, 215, BLACK, style, "%z,%z", "的办学理念","坚持“一流教学一流本科”的建");
			printg_cn(110, 235, BLACK, style, "%z,%z,%z", "建设目标按照“应用领先","基础突破","协调发展");
			printg_cn(110, 255, BLACK, style, "%z,%z,", "”的科技发展方略","构建起了覆盖基础研究层");
			printg_cn(110, 275, BLACK, style, "%z", "技术开发层三个层次的科技创新体系。");
			printg_cn(450, 220, WHITE, style, "1.%z", "南大门");
			printg_cn(450, 240, WHITE, style, "2.%z", "校史馆");
			printg_cn(450, 260, WHITE, style, "3.%z", "图书馆");
			printg_cn(450, 280, WHITE, style, "4.%z", "华中科技大学校徽");
			printg_cn(450, 300, WHITE, style, "5.%z", "校训");
			printg_cn(450, 320, WHITE, style, "6.AIA%z", "院徽");
			printg_cn(450, 340, WHITE, style, "7.70%z", "周年校庆");
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
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "第三部分", "展望未来");
			printg_cn(110, 95, BLACK, style, "   %z,%z,%z,", "数十年冒雨冲风","我们脚踏实地", "砥砺前行");
			printg_cn(110, 115, BLACK, style, "%z,%z", "我们建立未来技术学院", "培养具有创新精神和");
			printg_cn(110, 135, BLACK, style, "%z,%z", "国际视野的高层次人才。探索智能工厂","芯片");
			printg_cn(110, 155, BLACK, style, "%z,%z,%z,%z", "制造","无人建造","大脑科学等前沿领域","为社会");
			printg_cn(110, 175, BLACK, style, "%z", "发展和人类进步贡献力量。引进和培养一流的");
			printg_cn(110, 195, BLACK, style, "%z,%z", "教师团队","打造国际化的学术氛围和交流平台。");
			printg_cn(110, 215, BLACK, style, "%z,%z", "携手共进","走过山水又一程。");
			printg_cn(450, 220, WHITE, style, "1.%z", "合成大无人机");
			printg_cn(450, 240, WHITE, style, "2.%z", "火箭腾飞");
			printg_cn(450, 260, WHITE, style, "3.%z", "华中科技大星");
			printg_cn(450, 280, WHITE, style, "4.%z", "我爱华科");
			printg_cn(450, 300, WHITE, style, "5.%z,", "与共和国同行");
			printg_cn(450, 320, WHITE, style, "  %z", "与新时代共进");
			printg_cn(450, 340, WHITE, style, "6.%z", "天安门欢庆");
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
		if(mouse_press(442, 24, 637, 220))
		{
			clrmous(nx, ny);
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
						if((((dronelist[i].x)*SCALE+XLS)>440)&& 
						   (((dronelist[i].x)*SCALE+XLS)<639)&&
						   (((dronelist[i].z)*SCALE+YLS)>40)&&
						   (((dronelist[i].z)*SCALE+YLS)<190))
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