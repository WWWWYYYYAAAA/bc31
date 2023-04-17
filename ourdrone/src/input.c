#include "printg.h"
#include <graphics.h>
#include <bios.h>
#include <string.h>

int commandin(char * str, char *illu, int x, int y, int length)
{
	int style[5] = {0, 2, 0, 0, 1};
	int key, i=0, len = strlen(illu);
	char ch;
	printg_cn(x, y, WHITE, style, "%s", illu);
	while (1)
	{
		key = bioskey(0);
		ch =  key-(key>>8<<8);
		printf("%d\n", ch);
		if(ch == 13)//enter
		{
			str[i] = 0;
			break;
		}
		else if(ch == 8)
		{
			i--;
			if(i<0)
			{
				i = 0;
				setfillstyle(SOLID_FILL, WHITE);
				bar(x+len*8, y-5, x+len*8+8, y+16);
				delay(50);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(x+len*8, y-5, x+len*8+8, y+16);
			}
			str[i] = 0;
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(x+len*8+i*8, y-5, x+len*8+8+i*8, y+16);
			continue;
		}
		else if(ch == 27)//esc
		{
			return -1;
		}

		if(i>=length-1)
		{
			i = length-1;
			continue;
		}
		//printf("%d", ch);
		printg_cn(x+len*8+i*8, y, WHITE, style, "%c", ch);
		str[i] = ch;
		i++;
		if(i>=20)
		{
			i--;
		}
	}
	return 0;
}

int confirm()
{
	int style[5] = {0, 2, 0, 0, 1};
	int key, i=0;
	char ch, com[10]={0};
	printg_cn(130, 455, WHITE, style, "yes/no: ");
	while (1)
	{
		key = bioskey(0);
		ch =  key-(key>>8<<8);
		if(ch == 13)//enter
		{
			com[i] = 0;
			break;
		}
		else if(ch == 8)//backspace
		{
			i--;
			if(i<0)
			{
				i = 0;
				setfillstyle(SOLID_FILL, WHITE);
				bar(194, 450, 202, 466);
				delay(50);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(194, 450, 202, 466);
			}
			com[i] = 0;
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(194+i*8, 450, 202+i*8, 466);
			continue;
		}
		else if(ch == 27)//esc
		{
			return 0;
		}
		if(i>=9)
		{
			i = 9;
			continue;
		}
		printg_cn(194+i*8, 455, WHITE, style, "%c", ch);
		com[i] = ch;
		i++;
	}
	if(strcmp("yes", com)==0 || strcmp("y", com) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}