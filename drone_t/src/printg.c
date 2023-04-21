#include <graphics.h>
#include <stdarg.h>
#include <string.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
//图形化print
#define ON 1
#define OFF 0
int do_printg_s(char far * p0, int x0, int y0, int color, const char * str, va_list arg);
int do_printg_s_cn(char far * p0, int x0, int y0, int color, int style[5], const char * str, va_list arg);
int g_out(int x0, int y0, int color, char far *p0, int style[5]);
void puthzf(int x, int y,int flag,int part,int color, char *s);

int printg(int x0, int y0, int color, const char *str, ...) 
{ 
	char far * p0;
	int flag;
	int style[5] = {0, 2, 0, 0, 1};
	va_list arg; 
	
	va_start(arg, str); 
	
	p0 = (char far *) farmalloc(sizeof(str)+50);
	if(p0 == NULL)
	{
		printf("do_printg_s farmalloc error.\n");
		return -1;
	}
	
	flag = do_printg_s(p0, x0, y0, color, str, arg);
	g_out(x0, y0, color, p0, style);
	free(p0);
    return 0; 
} 

int printg_cn(int x0, int y0, int color, int style[5], const char *str, ...) 
{ 
	char far * p0;
	int flag;
	va_list arg; 
	va_start(arg, str);
	
	p0 = (char far *) farmalloc(sizeof(str)+50);
	if(p0 == NULL)
	{
		printf("do_printg_s farmalloc error.\n");
		return -1;
	}
	
	flag = do_printg_s_cn(p0, x0, y0, color, style, str, arg);
	free(p0);
    return 0; 
} 

//s版只可格式化输出 %d

int do_printg_s(char far * p0, int x0, int y0, int color, const char * str, va_list arg) 
{ 
	char * s, far * p, tempch;
	int tempint;
	
	s = (char *) malloc(11);
	if(s == NULL)
	{
		printf("do_printg_s malloc error.\n");
		return -1;
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

			case 'c':
			case 'C':
				tempch = va_arg(arg, char);
				*p = tempch;
				p++;
			break;

			case 'S':
			case 's':
				s = va_arg(arg, char *);
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
	//printf(p0);
	free(s);
	return 0;
}
//style[5] #0 horiz, #1 vert, #2 font, #3 direction, #4 size
int g_out(int x0, int y0, int color, char far *p0, int style[5])
{
	setcolor(color);
	/*
	settextjustify(0, 2);
	settextstyle(0, 0, 1);
	*/
	settextjustify(style[0], style[1]);
	settextstyle(style[2], style[3], style[4]);
	outtextxy(x0, y0, p0);
}

void puthzf(int x, int y,int flag,int part,int color, char *s)
{
	FILE *hzk_p=NULL;                                       //定义汉字库文件指�?
	unsigned char quma,weima;                 //定义汉字的区码和位码
	unsigned long offset;                          //定义汉字在字库中的偏移量
	int i,j,pos;

	
	switch(flag)    //不同的flag对应不同的汉字库，实现了汉字的大小可根据需要改�?
	{
		case 0 :
		case 16 :
		{
			char mat[32];   //16*16的汉字需�?32个字节的数组来存�?
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZ16","rb");            //绝对相对路径
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对�?
				settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//黑体笔划输出，水平输出，24*24点阵
				outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      //求出区码
					weima=s[1]-0xa0;                     //求出位码
					offset=(94*(quma-1)+(weima-1))*32L;   //求出要显示的汉字在字库文件中的偏�?
					fseek(hzk_p,offset,SEEK_SET);         //重定位文件指�?
					fread (mat,32,1,hzk_p);            //读出该汉字的具体点阵数据,1为要读入的项�?

					for(i=0;i<16;i++)
					{
						pos=2*i;       //16*16矩阵中有每一行有两外字节
						
						for(j=0;j<8;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>j)&mat[pos])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						y++;
					}
					/*====================================================
						以上是一个汉字显示完
					====================================================*/
					x+=part;        //给x 一个偏移量part
					s+=2;           //汉字里存放的是内码，2个字节，所以要�?2

				}
				x=x0;y0+=flag+10; //一行汉字显示完�?,重新从左侧开始输出汉字，给y一个偏移量
			}
		break;
		}
		case 1:
		case 24 :
		{
			char mat[72];   //24*24矩阵�?72个字节来存储
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\Hzk24k","rb");
			if (hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对�?
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//黑体笔划输出，水平输出，24*24点阵
				outtextxy(10,10,"Can't open hzk24 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while(x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      //求出区码
					weima=s[1]-0xa0;                     //求出位码
					offset=(94*(quma-1)+(weima-1))*72L;
					fseek(hzk_p,offset,SEEK_SET);
					fread (mat,72,1,hzk_p);
					for (i=0;i<24;i++)
					{
						pos=3*i;   //矩阵中每一行有三个字节
						
						for(j=0;j<8;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>j)&mat[pos])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						y++;

					}
					x+=part;
					s+=2;
				}
				x=x0;y0+=flag+10;
			}
		break;
		}
		case 2:
		case 32 :
		{
			char mat[128];   //32*32的汉字需�?128个字节的数组来存�?
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZK32S","rb");
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对�?
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//黑体笔划输出，水平输出，24*24点阵						
				outtextxy(10,10,"Can't open hzk32 file!Press any key to quit...");
				 getch();
				 exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      //求出区码
					weima=s[1]-0xa0;                     //求出位码
					offset=(94*(quma-1)+(weima-1))*128L;
					fseek(hzk_p,offset,SEEK_SET);
					fread (mat,128,1,hzk_p);
					for(i=0;i<32;i++)
					{
						pos=4*i;       //32*32矩阵中有每一行有两外字节
						for(j=0;j<8;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>j)&mat[pos])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=24;j<32;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-24))&mat[pos+3])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						y++;


					}
						//以上是一个汉字显示完
					x+=part;    //给x 一个偏移量part
					s+=2;          //汉字里存放的是内码，2个字节，所以要�?2

				}
				x=x0;y0+=flag+10;   //一行汉字显示完后，给y一个偏移量
			}
		break;
		}
		case 3:
		case 48:
		{
			char mat[288];   //48*48的汉字需�?288个字节的数组来存�?
			int y0=y;
			int x0=x;
			 hzk_p = fopen(".\\HZK\\Hzk48k","rb");
			 if(hzk_p==NULL)
			 {
				settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对�?
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//黑体笔划输出，水平输出，24*24点阵
				outtextxy(10,10,"Can't open hzk48 file!Press any key to quit...");
				 getch();
				 exit(1);

			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      //求出区码
					weima=s[1]-0xa0;                     //求出位码
					offset=(94*(quma-1)+(weima-1))*288L;   //求出要显示的汉字在字库文件中的偏�?
					fseek(hzk_p,offset,SEEK_SET);         //重定位文件指�?
					fread (mat,288,1,hzk_p);            //读出该汉字的具体点阵数据,1为要读入的项�?

					for(i=0;i<48;i++)
					{
						pos=6*i;
							for(j=0;j<8;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>j)&mat[pos])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=24;j<32;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-24))&mat[pos+3])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=32;j<40;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-32))&mat[pos+4])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);

							}
						}
						for(j=40;j<48;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-40))&mat[pos+5])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);

							}
						}
						y++;
					}
						//以上是一个汉字显示完
					x+=part;    //给x 一个偏移量part
					s+=2;          //汉字里存放的是内码，2个字节，所以要�?2

				}
				x=x0;y0+=flag+10;   //一行汉字显示完后，给y一个偏移量
			}
		break;
		}
		default:
		{
			char mat[32];   //16*16的汉字需�?32个字节的数组来存�?
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZ16","rb");            //绝对相对路径
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对�?
				settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//黑体笔划输出，水平输出，24*24点阵
				outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      //求出区码
					weima=s[1]-0xa0;                     //求出位码
					offset=(94*(quma-1)+(weima-1))*32L;   //求出要显示的汉字在字库文件中的偏�?
					fseek(hzk_p,offset,SEEK_SET);         //重定位文件指�?
					fread (mat,32,1,hzk_p);            //读出该汉字的具体点阵数据,1为要读入的项�?

					for(i=0;i<16;i++)
					{
						pos=2*i;       //16*16矩阵中有每一行有两外字节
						
						for(j=0;j<8;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>j)&mat[pos])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   //j%8只能�?0�?8之间循环，j/8�?0�?1之间循环
							{
								putpixel(x+j,y,color);
							}
						}
						y++;
					}
					/*====================================================
						以上是一个汉字显示完
					====================================================*/
					x+=part;        //给x 一个偏移量part
					s+=2;           //汉字里存放的是内码，2个字节，所以要�?2

				}
				x=x0;y0+=flag+10; //一行汉字显示完�?,重新从左侧开始输出汉字，给y一个偏移量
			}
		break;
		}
		break;
	}

	fclose(hzk_p);
}


int do_printg_s_cn(char far * p0, int x0, int y0, int color, int style[5], const char * str, va_list arg) 
{ 
	char * s, far * p, tempch;
	int tempint;
	int i = 0, hzsize = style[4]<<3;
	char charstr[3] = {0}, * tempcn;
	setcolor(color);
	s = (char *) malloc(11);
	if(s == NULL)
	{
		printf("do_printg_s malloc error.\n");
		return -1;
	}
	switch(hzsize)
	{
	case 16:
	break;
	case 24:
	break;
	case 32:
	break;
	case 48:
	break;
	default:
		hzsize = 16;
	break;
	}
	p = p0;
    for (;*str != '\0'; str++) 
    { 
        if (*str != '%') 
        {
			*p = *str;
			charstr[0] = *p;
			charstr[1] = 0;
			settextjustify(style[0], style[1]);
			settextstyle(style[2], style[3], style[4]);
			outtextxy(x0+i, y0, charstr);
			i+=style[4]*8;
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
					charstr[0] = *p;
					charstr[1] = 0;
					settextjustify(style[0], style[1]);
					settextstyle(style[2], style[3], style[4]);
					outtextxy(x0+i, y0, charstr);
					i+=style[4]*8;
					p++;
				}
				break;
			case 'Z':
			case 'z':
				tempcn = va_arg(arg, char *);
				for(; *tempcn != '\0'; tempcn+=2)
				{
					*p = *tempcn;
					*(p+1) = *(tempcn+1);
					charstr[0] = *(tempcn);
					charstr[1] = *(tempcn+1);
					puthzf(x0+i, y0+((style[4]<<3)-hzsize), hzsize, hzsize, color, charstr);
					i+=hzsize;
					p+=2;
				}
				break;

			case 'c':
			case 'C':
				tempch = va_arg(arg, char);
				*p = tempch;
				charstr[0] = *p;
				charstr[1] = 0;
				settextjustify(style[0], style[1]);
				settextstyle(style[2], style[3], style[4]);
				outtextxy(x0+i, y0, charstr);
				i+=style[4]*8;
				p++;
			break;

			case 'S':
			case 's':
				s = va_arg(arg, char *);
				for(; *s != '\0'; s++)
				{
					*p = *s;
					charstr[0] = *p;
					charstr[1] = 0;
					settextjustify(style[0], style[1]);
					settextstyle(style[2], style[3], style[4]);
					outtextxy(x0+i, y0, charstr);
					p++;
					i+=style[4]*8;
				}
			break;
		}
    }
	*p = '\0';
    va_end(arg);
	//printf(p0);
	free(s);
	return 0;
}