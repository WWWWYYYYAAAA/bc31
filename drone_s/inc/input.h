#ifndef _INPUT_H_
#define _INPUT_H_

int commandin(char * str, char *illu, int x, int y, int length);
int confirm();

/*
Ê¹ÓÃÊ¾Àý
bar_3d(121, 440, 639, 479, DARKGRAY, 1);
if(commandin(str, "color: ", 130, 455, 20) == 0)
...
setfillstyle(SOLID_FILL, LIGHTGRAY);
bar(121, 440, 639, 479);
*/

#endif