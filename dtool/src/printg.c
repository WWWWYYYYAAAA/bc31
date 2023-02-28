#include <graphics.h>
#include <stdarg.h>
#include <string.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#define ON 1
#define OFF 0
static void do_printg_s(int x0, int y0, int color, const char * str, va_list arg);

int printg(int x0, int y0, int color, const char *str, ...) 
{ 
     va_list arg; 
     va_start(arg, str); 
	 do_printg_s(x0, y0, color, str, arg);
     return 0; 
} 

//s版只可格式化输出 %d

static void do_printg_s(int x0, int y0, int color, const char * str, va_list arg) 
{ 
	char * s, far * p, far * p0;
	int tempint;
	
	p0 = (char far *) farmalloc(sizeof(str)+50);
	if(p0 == NULL)
	{
		printf("do_printg_s farmalloc error.\n");
		return;
	}
	
	s = (char *) malloc(11);
	if(s == NULL)
	{
		printf("do_printg_s malloc error.\n");
		return;
	}
	p = p0;
    for (;*str != '\0'; str++) 
    { 
        if (*str != '%') 
        {
			*p = *str;
			p++;
            continue; 
        }
        str++; 
		switch(*str)
		{
			case 'd':
			case 'D':
				tempint = va_arg(arg, int);
				itoa(tempint, s, 10);
				for(; *s != '\0'; s++)
				{
					*p = *s;
					p++;
				}
				break;
		}
    }
	*p = '\0';
    va_end(arg);
	setcolor(color);
	settextjustify(0, 2);
	settextstyle(0, 0, 1);
	outtextxy(x0, y0, p0);
	free(s);
	free(p0);
}
