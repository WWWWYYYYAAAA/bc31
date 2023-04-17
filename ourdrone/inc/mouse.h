#ifndef _mouse_h_
#define _mouse_h_

int mouse_press(int x1, int y1, int x2, int y2);//如果在框中点击，则返�?1；在框中未点击，则返�?2；不在框中则返回0
void mouse(int x, int y, int style);//设计鼠标
int mouseinit(void);//初始�?
void mread(int *,int *,int*);//改坐标不�?
void clrmous(int x,int y);//清除鼠标
void drawmous(int x,int y);//画鼠�?
int newmouse(int *nx,int *ny,int *nbuttons);   //更新鼠标
int mouse_press_sup(int x1, int y1, int x2, int y2, int * mx, int * my);

#endif
