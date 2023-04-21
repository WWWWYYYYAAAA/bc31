#include "page234.h"

int page234(char *prjdir)
{
	int pause=0, video=0, nx=MX, ny=MY, nb, mx, my, in=1, sr = 2;
    float speed = 1, globalfloat = 0;
    float speedrank[6] = {0.5, 0.75, 1, 1.5, 2, 3};
    //char prjdir[20] = "prj";
    int style[5] = {0, 2, 0, 0, 1};
    int pixnum, i, SP = 0,RO = 0, PO = 0, oldx, oldy, DX = 0, DY = 0;
	int count = 0, globalnum = 0;
	PIX pixlist[LISTSIZE];
	int oldxy[LISTSIZE][2] = {{0, 0}};
	char filename[10]={0};
	float A = 0, B = 0,C=0, percent = 1;
	int X, Y, Z;
    int pausepattern[8] = {295, 438, 305, 445, 295, 452, 295, 438};
    clearpixlist(pixlist, &pixnum, LISTSIZE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, 639, 479);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(598, 0, 639, 342);
    setfillstyle(SOLID_FILL, RED);
    bar(600, 0, 639, 39);
    setfillstyle(SOLID_FILL, BLUE);
    bar(600, 40, 639, 99);
    button(600, 0, 639, 39, 0);
    button(600, 40, 639, 99, 0);//重新打开
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(600, 100, 639, 340);
    printg_cn(612, 120, WHITE, style, "RO");
	printg_cn(612, 160, WHITE, style, "PO");
	printg_cn(612, 200, WHITE, style, "SP");
	printg_cn(612, 240, WHITE, style, "RE");
	printg_cn(616, 280, WHITE, style, "+");
	printg_cn(616, 320, WHITE, style, "-");
	button(600, 100, 639, 139, 0); 	//RO
	button(600, 140, 639, 179, 0); 	//PO
	button(600, 180, 639, 219, 0); 	//SP
	button(600, 220, 639, 259, 0); 	//RE
	button(600, 260, 639, 299, 0); 	//+
	button(600, 300, 639, 340, 0); 	//-
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(80, 405, 520, 410);
    bar(285, 430, 315, 460);
    button(285, 430, 315, 460, 0); //暂停
    setfillstyle(SOLID_FILL, WHITE);
    bar(293, 438, 297, 452);
    bar(303, 438, 307, 452);
    setcolor(WHITE);
    line(330, 450, 480, 450); //倍速
    ball(330, 450, 2, WHITE);
    ball(360, 450, 2, WHITE);
    ball(390, 450, 4, DARKGRAY);//X1
    ball(420, 450, 2, WHITE);
    ball(450, 450, 2, WHITE);
    ball(480, 450, 2, WHITE);
    printg_cn(318,430, WHITE, style, "0.75");
    printg_cn(350,430, WHITE, style, "0.5");
    printg_cn(387,430, WHITE, style, "1");
    printg_cn(410,430, WHITE, style, "1.5");
    printg_cn(447,430, WHITE, style, "2");
    printg_cn(477,430, WHITE, style, "3");
    //setcolor(LIGHTGRAY);
    //rectangle(X0-7, Y0-7, X0+XSIZE+7, Y0+YSIZE+7);
    while (1)
    {
        if(mouse_press(600, 0, 639, 39) == 1)
        {
           button(600, 0, 639, 39, 1);
           delay(200);
           return 1;
        }
        else if(mouse_press(600, 40, 639, 99)==1) //BLUE
        {
            button(600, 40, 639, 99, 1);
            video = 0;
            globalnum = 0;
            globalfloat = 0;
        }
        else if(mouse_press(600, 100, 639, 139) == 1)	//RO
		{
			if(RO == 0)
				RO = 1;
			else if(RO == 1)
				RO = 0;
			//printf("RO %d\n", RO);
			clrmous(nx, ny);
			button(600, 100, 639, 139, 2*RO);
			delay(200);
		}
		else if(mouse_press(600, 140, 639, 179) == 1)	//PO
		{
			if(PO == 0)
				PO = 1;
			else if(PO == 1)
				PO = 0;
			clrmous(nx, ny);
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
			clrmous(nx, ny);
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
			//update = 1;
			percent = 1;
			
		}
		else if(mouse_press(600, 260, 639, 299) == 1)	//+
		{
			button(600, 260, 639, 299, 1);
			percent += 0.05;
		}
		else if(mouse_press(600, 300, 639, 340) == 1)	//-
		{
			button(600, 300, 639, 340, 1);
			percent -= 0.05;
			if(percent<0.05)
			{
				percent = 0.05;
			}
			//update = 1;
		}
        else if(mouse_press(285, 430, 315, 460)==1)
        {//暂停
            button(285, 430, 315, 460, 1);
            delay(100);
            if(pause==0)
            {
                bar_3d(285, 430, 315, 460, LIGHTGRAY, 0);
                setfillstyle(SOLID_FILL, WHITE);
                //setcolor(WHITE);
                //line(295, 438, 305, 445);
                //line(295, 452, 305, 445);
                //line(295, 452, 295, 438);
                //floodfill(300, 445, WHITE);
                //putpixel(300, 445, RED);
                fillpoly(4, pausepattern);
                pause = 1;
            }
            else if(pause == 1)
            {
                bar_3d(285, 430, 315, 460, LIGHTGRAY, 0);
                setfillstyle(SOLID_FILL, WHITE);
                bar(293, 438, 297, 452);
                bar(303, 438, 307, 452);
                pause = 0;
            }
            delay(100);
        }
        else if(mouse_press_sup(80, 400, 520, 420, &mx, &my) == 1)  //进度条
        {
            globalfloat = 1.0 * (mx-80) / 440 * count;
            setfillstyle(SOLID_FILL, BLACK);
            bar(70, 400, 530, 420);
            setfillstyle(SOLID_FILL, LIGHTGRAY);
            bar(80, 405, 520, 410);
            ball(80+440.0*globalfloat/count, 408, 5, DARKGRAY);
        }
        else if(mouse_press_sup(320, 445, 490, 455, &mx, &my) == 1)  //倍速
        {
            clrmous(nx, ny);
            setfillstyle(SOLID_FILL, BLACK);
            bar(320, 440, 490, 460);
            setcolor(WHITE);
            line(330, 450, 480, 450); //倍速
            ball(330, 450, 2, WHITE);
            ball(360, 450, 2, WHITE);
            ball(390, 450, 2, WHITE);//X1
            ball(420, 450, 2, WHITE);
            ball(450, 450, 2, WHITE);
            ball(480, 450, 2, WHITE);
            sr = (mx-330)/30;
            ball(330+sr*30, 450, 4, DARKGRAY);
            speed = speedrank[sr];
        }
        //交互
        if(video == 0)
        {
                video=1;
			    count = getnum(prjdir);
            
        }
        else if(video == 1)
        {   
			if(mouse_press(X0, Y0, X0+XSIZE, Y0+YSIZE))
			{
				clrmous(nx, ny);
			}
            if(pause == 0)
            {
                globalfloat += 1*speed;
                if(mouse_press_sup(80, 400, 520, 420, &mx, &my) == 1)
                {
                    globalfloat = 1.0 * (mx-80) / 440 * count;
                }
                globalnum = (int)globalfloat;
                if(globalnum>count)
                {
                    globalnum = count;
                }
                //进度条
                setfillstyle(SOLID_FILL, BLACK);
                bar(70, 400, 530, 420);
                setfillstyle(SOLID_FILL, LIGHTGRAY);
                bar(80, 405, 520, 410);
                ball(80+440.0*globalnum/count, 408, 5, DARKGRAY);
            }
			if(chdir(prjdir)==0)
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
			//clrmous(nx, ny);
			//setfillstyle(SOLID_FILL, BLACK);
			//bar(X0-5, Y0-5, X0+XSIZE+5, Y0+YSIZE+5); //遮罩
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, percent*0.7);
				if((X>X0&&X<X0+XSIZE)&&(Z>Y0&&Z<Y0+YSIZE))
				{
					if(oldxy[i][0] != X|| oldxy[i][1] != Z)
					{
						setfillstyle(SOLID_FILL, BLACK);
						bar(oldxy[i][0]-2, oldxy[i][1]-2, oldxy[i][0]+2, oldxy[i][1]+2);
						ball_light(X, Z, 2, pixlist[i].color);
					}
					oldxy[i][0] = X;
					oldxy[i][1] = Z;
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			for(i=0; i<pixnum; i++)
			{
				move_3d_p((float)(pixlist[i].x-XSIZE/2), (float)(pixlist[i].y), (float)(pixlist[i].z-YSIZE/2), A, B, &X, &Y, &Z, 0, 0, 0, 1);
				move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, percent*0.7);
				if((X>X0&&X<X0+XSIZE)&&(Z>Y0&&Z<Y0+YSIZE))
				{
						ball_light(X, Z, 2, pixlist[i].color);
				}
				//printf("%d", pixlist[i].x);
				//printf(" %d\n", X);
			}
			//move_3d_p(20, 0, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			// move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			// setcolor(WHITE);
			// line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			// move_3d_p(0, 20, 0, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			// move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			// setcolor(WHITE);
			// line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			// move_3d_p(0, 0, 20, A, B, &X, &Y, &Z, 0, 0, 0, 1);
			// move_3d_yaxis((float)X, (float)Y, (float)Z, C, &X, &Y, &Z, X0+XSIZE/2+DX, 0, Y0+YSIZE/2+DY, 1);
			// setcolor(WHITE);
			// line(X0+XSIZE/2+DX,  Y0+YSIZE/2+DY, X, Z);
			//A+=0.01;
			//B+=0.01;
			//getch();
			//update = 0;
			chdir("..");
			}
			chdir("..");
			}
			if(globalnum == count-1)
			{
				globalnum = 0;
                globalfloat = 0;
			}
        }
        newmouse(&nx, &ny, &nb);
        if(RO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				B -= 0.01*(nx - oldx);
				A += 0.01*(ny - oldy);
			}
		}
		if(PO == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				DX += (nx - oldx);
				DY += (ny - oldy);
			}
		}
		if(SP == 1)
		{
			if(mouse_press(140, 60, 580, 420) == 1)
			{
				C += - 0.01*(ny - oldy);
			}
		}
        oldx = nx;
		oldy = ny;
		delay(7);
    }
    return 1;
}