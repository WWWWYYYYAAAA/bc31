#ifndef _BMP_H_
#define _BMP_H_

#include <stdio.h>
#include <graphics.h>
#include "error.h"

int putbmp(int x, int y, char *s);
int putbmpsup(int x, int y, int *w, int *h, char *s);
int bmpinfo(char *path, int *w, int *h);
int putbmp_zoom(int x, int y, char *s, float scalex, float scaley);

#endif