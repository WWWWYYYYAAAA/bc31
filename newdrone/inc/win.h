#ifndef _WIN_H_
#define _WIN_H_

class  Win
{
public:
	int x1;
	int y1;
	int x2;
	int y2;
	int color1;
	int color2;
	unsigned long imsize;
	void * imagebuff;
	int lx;
    int ly;
	int count;
    int enable; //操作使能
public:
	Win(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2);
	int update(int ix1, int iy1, int ix2, int iy2, int icolor1, int icolor2);
	int auto_update();
	int clearwin();
	int exit();
};


#endif