#ifndef _VISUAL_H_
#define _VISUAL_H_

#include <graphics.h>
#include <dos.h>
#include "printg.h"
#include "mouse.h"
#include "page5.h"
#include "astruct.h"

extern int MX, MY;


void ball(int x, int y, int r, int color);
int button(int x1, int y1, int x2, int y2, int state);
void bar2d(int x1, int y1, int x2, int y2, int color);
void sliderbase(int x0, int y0, int nx, int ny, int wid, int len, int direct, int style, int mode);
int slider(int x0, int y0, int nx, int ny, int wid, int len, int direct, int style, float *signal);
void silder_depature(int nynum, int x0, int y0, int wid, int len, int direct, int style);
void bar_3d(int x1, int y1, int x2, int y2, int color, int style);
void ball_light(int x, int y, int r, int color);
void ball_base(int x, int y, int r, int color);

#endif