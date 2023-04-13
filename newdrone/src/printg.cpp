#include <graphics.h>
#include <stdarg.h>
#include <string.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include "printg.h"

#define ON 1
#define OFF 0
int do_printg_s(char far * p0, int x0, int y0, int color, const char * str, va_list arg);
int do_printg_s_cn(char far * p0, int x0, int y0, int color, int style[5], const char * str, va_list arg);
int g_out(int x0, int y0, int color, char far *p0, int style[5]);
//void puthzf(int x, int y,int flag,int part,int color, char *s);

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

//s板只可格式化输出 %d 整型 cn兼容中文

int do_printg_s(char far * p0, int x0, int y0, int color, const char * str, va_list arg) 
{ 
	char * s, far * p;
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
	FILE *hzk_p=NULL;                       
	unsigned char quma,weima;               
	unsigned long offset;                      
	int i,j,pos;

	
	switch(flag)   
	{
		case 0 :
		case 16 :
		{
			char mat[32];  
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZ16","rb");            
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          
				settextstyle(GOTHIC_FONT,HORIZ_DIR,1);				
				outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      
					weima=s[1]-0xa0;                   
					offset=(94*(quma-1)+(weima-1))*32L;  
					fseek(hzk_p,offset,SEEK_SET);         
					fread (mat,32,1,hzk_p);            

					for(i=0;i<16;i++)
					{
						pos=2*i;       
						
						for(j=0;j<8;j++)    
						{
							if(((0x80>>j)&mat[pos])!=NULL)   
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)   
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)  
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
		case 1:
		case 24 :
		{
			char mat[72];   
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\Hzk24k","rb");
			if (hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);	
				outtextxy(10,10,"Can't open hzk24 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while(x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      
					weima=s[1]-0xa0;                     
					offset=(94*(quma-1)+(weima-1))*72L;
					fseek(hzk_p,offset,SEEK_SET);
					fread (mat,72,1,hzk_p);
					for (i=0;i<24;i++)
					{
						pos=3*i;   
						
						for(j=0;j<8;j++)   
						{
							if(((0x80>>j)&mat[pos])!=NULL)   
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)   
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)   
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
			char mat[128];   
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZK32S","rb");
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);										
				outtextxy(10,10,"Can't open hzk32 file!Press any key to quit...");
				 getch();
				 exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                     
					weima=s[1]-0xa0;                     
					offset=(94*(quma-1)+(weima-1))*128L;
					fseek(hzk_p,offset,SEEK_SET);
					fread (mat,128,1,hzk_p);
					for(i=0;i<32;i++)
					{
						pos=4*i;       
						for(j=0;j<8;j++)    
						{
							if(((0x80>>j)&mat[pos])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++) 
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL) 
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)    
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=24;j<32;j++)    
						{
							if(((0x80>>(j-24))&mat[pos+3])!=NULL)  
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
		case 3:
		case 48:
		{
			char mat[288];   
			int y0=y;
			int x0=x;
			 hzk_p = fopen(".\\HZK\\Hzk48k","rb");
			 if(hzk_p==NULL)
			 {
				settextjustify(LEFT_TEXT,TOP_TEXT);          
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					
				outtextxy(10,10,"Can't open hzk48 file!Press any key to quit...");
				 getch();
				 exit(1);

			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      
					weima=s[1]-0xa0;                     
					offset=(94*(quma-1)+(weima-1))*288L;   
					fseek(hzk_p,offset,SEEK_SET);       
					fread (mat,288,1,hzk_p);           

					for(i=0;i<48;i++)
					{
						pos=6*i;
							for(j=0;j<8;j++)   
						{
							if(((0x80>>j)&mat[pos])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)    
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)   
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=16;j<24;j++)    
						{
							if(((0x80>>(j-16))&mat[pos+2])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=24;j<32;j++)    
						{
							if(((0x80>>(j-24))&mat[pos+3])!=NULL)   
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=32;j<40;j++)    
						{
							if(((0x80>>(j-32))&mat[pos+4])!=NULL)   
							{
								putpixel(x+j,y,color);

							}
						}
						for(j=40;j<48;j++)    
						{
							if(((0x80>>(j-40))&mat[pos+5])!=NULL)   
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
		default:
		{
			char mat[32];   
			int y0=y;
			int x0=x;
			hzk_p = fopen(".\\HZK\\HZ16","rb");           
			if(hzk_p==NULL)
			{
				settextjustify(LEFT_TEXT,TOP_TEXT);          
				settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					
				outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
				getch();
				exit(1);
			}
			while(*s!=NULL)
			{
				while (x<640-flag && (*s!=NULL))
				{
					y=y0;
					quma=s[0]-0xa0;                      
					weima=s[1]-0xa0;                     
					offset=(94*(quma-1)+(weima-1))*32L;   
					fseek(hzk_p,offset,SEEK_SET);        
					fread (mat,32,1,hzk_p);            

					for(i=0;i<16;i++)
					{
						pos=2*i;      
						
						for(j=0;j<8;j++)   
						{
							if(((0x80>>j)&mat[pos])!=NULL)  
							{
								putpixel(x+j,y,color);
							}
						}
						for(j=8;j<16;j++)   
						{
							if(((0x80>>(j-8))&mat[pos+1])!=NULL)  
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
		break;
	}

	fclose(hzk_p);
}


int do_printg_s_cn(char far * p0, int x0, int y0, int color, int style[5], const char * str, va_list arg) 
{ 
	char * s, far * p;
	int tempint;
	int i = 0, hzsize = style[4]<<3;
	char charstr[3] = {0}, * tempcn;
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
		}
    }
	*p = '\0';
    va_end(arg);
	//printf(p0);
	free(s);
	return 0;
}