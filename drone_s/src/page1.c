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
	button(0, 140, 98, 179, 0);//�Զ���
	button(442, 24, 472, 54, 0);
	button(2, 440, 98, 477, 0);
	sliderbase(617, 201, nx, ny, 20, 278, 0, 0, 0);
	clrmous(ny, nx);
	printg_cn(20, 40, BLACK, style,"%z", "��һ����");
	printg_cn(20, 80, BLACK, style,"%z", "�ڶ�����");
	printg_cn(20, 120, BLACK, style,"%z", "��������");
	printg_cn(28, 160, BLACK, style,"%z", "�Զ���");
	//int openconf(char * prjdir, int *filenum, int *frnum)

	printg_cn(130, 40, BLACK, style1, "%z %z", "��һ����", "�ع���ʷ");
	//���пƼ���ѧ��֤���й��߽���ҵ�����δ�չ������Ϊ�����й��ߵȽ�����չ����Ӱ��
	//���ڹ��͹�������ʱ�����й�ѧԺ��1953��Ӧ�˶�������1988��ɳ�Ϊ������ƴ�ѧ��
	
//��ԭ��������ѧ��ͬ��ҽ�ƴ�ѧ���人���н���ѧԺ�ͿƼ����ɲ�����ѧԺ��2000��ϲ�����ǧ����������У����пƼ���ѧҲ�����ƿǶ�����
	printg_cn(110, 95, BLACK, style, "    %z", "���пƼ���ѧ��֤���й��߽���ҵ������");
	printg_cn(110, 115, BLACK, style, "%z,%z", "��չ","����Ϊ���й��ߵȽ�����չ����Ӱ��");
	printg_cn(110, 135, BLACK, style, "%z,%z1953%z", "���ڹ��͹�������ʱ","���й�ѧԺ��", "��");
	printg_cn(110, 155, BLACK, style, "%z,%z1988%z", "Ӧ�˶���","��","��ɳ�Ϊ������ƴ�ѧ����");
	printg_cn(110, 175, BLACK, style, "%z,%z,%z", "ԭ��������ѧ","ͬ��ҽ�ƴ�ѧ","�人���н���");
	printg_cn(110, 195, BLACK, style, "%z2000%z,%z", "ѧԺ�ͿƼ����ɲ�����ѧԺ��","��ϲ�", "��");
	printg_cn(110, 215, BLACK, style, "%z,%z", "ǧ�����������","���пƼ���ѧҲ�����ƿǶ�");
	printg_cn(110, 235, BLACK, style, "%z", "����");
	printg_cn(450, 220, WHITE, style, "1.%z", "�������人����");
	printg_cn(450, 240, WHITE, style, "2.%z", "��������ѧ����");
	printg_cn(450, 260, WHITE, style, "3.%z", "ͬ��ҽѧԺ");
	printg_cn(450, 280, WHITE, style, "4.%z", "���пƼ���ѧ�ϲ�");
	//��ʼ��С��
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
			//����С������
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//����С������
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "��һ����", "�ع���ʷ");
			printg_cn(110, 95, BLACK, style, "    %z", "���пƼ���ѧ��֤���й��߽���ҵ������");
			printg_cn(110, 115, BLACK, style, "%z,%z", "��չ","����Ϊ���й��ߵȽ�����չ����Ӱ��");
			printg_cn(110, 135, BLACK, style, "%z,%z1953%z", "���ڹ��͹�������ʱ","���й�ѧԺ��", "��");
			printg_cn(110, 155, BLACK, style, "%z,%z1988%z", "Ӧ�˶���","��","��ɳ�Ϊ������ƴ�ѧ����");
			printg_cn(110, 175, BLACK, style, "%z,%z,%z", "ԭ��������ѧ","ͬ��ҽ�ƴ�ѧ","�人���н���");
			printg_cn(110, 195, BLACK, style, "%z2000%z,%z", "ѧԺ�ͿƼ����ɲ�����ѧԺ��","��ϲ�", "��");
			printg_cn(110, 215, BLACK, style, "%z,%z", "ǧ�����������","���пƼ���ѧҲ�����ƿǶ�");
			printg_cn(110, 235, BLACK, style, "%z", "����");
			printg_cn(450, 220, WHITE, style, "1.%z", "�������人����");
			printg_cn(450, 240, WHITE, style, "2.%z", "��������ѧ����");
			printg_cn(450, 260, WHITE, style, "3.%z", "ͬ��ҽѧԺ");
			printg_cn(450, 280, WHITE, style, "4.%z", "���пƼ���ѧ�ϲ�");
			//printg_cn(110, 135, BLACK, style, "%z", "");
		}
		else if(mouse_press(0, 60, 98, 99) == 1)
		{
			button(0, 60, 98, 99, 1);
			part = 2;
			//����С������
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//����С������
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "�ڶ�����", "���۵���");
			printg_cn(110, 95, BLACK, style, "    %z,%z,%z,%z", "У԰��ľ����","�̲�����","��������","��ɫ");
			printg_cn(110, 115, BLACK, style, "%z,%z", "����","����Ϊ��ɭ��ʽ��ѧ����ѧУ��ѧ����");
			printg_cn(110, 135, BLACK, style, "%z", "֧����ϵ�걸�������������ʩ��ȫ��ѧУ");
			printg_cn(110, 155, BLACK, style, "%z,%z", "ʵʩ���˲���У��ս��","ʦ�������ۺ�ѧУ");
			printg_cn(110, 175, BLACK, style, "%z,%z", "�᳹���衰ѧ��","ѧ����ѧ���Ĵ�ѧ���Ľ���");
			printg_cn(110, 195, BLACK, style, "%z,%z,%z,%z", "˼��","���С�����Ϊ��","�����ǻ�","�������С�");
			printg_cn(110, 215, BLACK, style, "%z,%z", "�İ�ѧ����","��֡�һ����ѧһ�����ơ��Ľ�");
			printg_cn(110, 235, BLACK, style, "%z,%z,%z", "����Ŀ�갴�ա�Ӧ������","����ͻ��","Э����չ");
			printg_cn(110, 255, BLACK, style, "%z,%z,", "���ĿƼ���չ����","�������˸��ǻ����о���");
			printg_cn(110, 275, BLACK, style, "%z", "����������������εĿƼ�������ϵ��");
			printg_cn(450, 220, WHITE, style, "1.%z", "�ϴ���");
			printg_cn(450, 240, WHITE, style, "2.%z", "Уʷ��");
			printg_cn(450, 260, WHITE, style, "3.%z", "ͼ���");
			printg_cn(450, 280, WHITE, style, "4.%z", "���пƼ���ѧУ��");
			printg_cn(450, 300, WHITE, style, "5.%z", "Уѵ");
			printg_cn(450, 320, WHITE, style, "6.AIA%z", "Ժ��");
			printg_cn(450, 340, WHITE, style, "7.70%z", "����У��");
		}
		else if(mouse_press(0, 100, 98, 139) == 1)
		{
			button(0, 100, 98, 139, 1);
			part = 3;
			//����С������
			prjvect = prjlist[part-1];
			filenum = getnum(prjvect);
			filevect = 0;
			swch = 0;
			//����С������
			setfillstyle(SOLID_FILL, LIGHTGRAY);
			bar(105, 40, 435, 470);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(445, 210, 615, 470);
			printg_cn(130, 40, BLACK, style1, "%z %z", "��������", "չ��δ��");
			printg_cn(110, 95, BLACK, style, "   %z,%z,%z,", "��ʮ��ð����","���ǽ�̤ʵ��", "����ǰ��");
			printg_cn(110, 115, BLACK, style, "%z,%z", "���ǽ���δ������ѧԺ", "�������д��¾����");
			printg_cn(110, 135, BLACK, style, "%z,%z", "������Ұ�ĸ߲���˲š�̽�����ܹ���","оƬ");
			printg_cn(110, 155, BLACK, style, "%z,%z,%z,%z", "����","���˽���","���Կ�ѧ��ǰ������","Ϊ���");
			printg_cn(110, 175, BLACK, style, "%z", "��չ�����������������������������һ����");
			printg_cn(110, 195, BLACK, style, "%z,%z", "��ʦ�Ŷ�","������ʻ���ѧ����Χ�ͽ���ƽ̨��");
			printg_cn(110, 215, BLACK, style, "%z,%z", "Я�ֹ���","�߹�ɽˮ��һ�̡�");
			printg_cn(450, 220, WHITE, style, "1.%z", "�ϳɴ����˻�");
			printg_cn(450, 240, WHITE, style, "2.%z", "����ڷ�");
			printg_cn(450, 260, WHITE, style, "3.%z", "���пƼ�����");
			printg_cn(450, 280, WHITE, style, "4.%z", "�Ұ�����");
			printg_cn(450, 300, WHITE, style, "5.%z,", "�빲�͹�ͬ��");
			printg_cn(450, 320, WHITE, style, "  %z", "����ʱ������");
			printg_cn(450, 340, WHITE, style, "6.%z", "�찲�Ż���");
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