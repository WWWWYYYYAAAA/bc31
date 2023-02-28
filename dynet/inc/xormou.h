#ifndef _XORMOU_H_
#define _XORMOU_H_

int mouseinit();
void mouse(int x,int y);
void mread(int *nx, int *ny, int *nbuttons); 
void newmouse(int *nx, int *ny, int *nbuttons);
void drawmous(int nx, int ny);
void clrmous(int nx,int ny);
int mouse_press(int x1, int y1, int x2, int y2);

#endif