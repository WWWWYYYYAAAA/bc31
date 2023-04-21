#ifndef _PRINTG_h_
#define _PRINTG_h_

#include <graphics.h>
#include <stdarg.h>
#include <string.h>
#include <alloc.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//图形化print
#define ON 1
#define OFF 0

int printg(int x0, int y0, int color, const char *str, ...);
int printg_cn(int x0, int y0, int color, int style[5], const char *str, ...);

#endif
