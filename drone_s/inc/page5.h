#ifndef _PAGE5_H_
#define _PAGE5_H_

#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include <bios.h>
#include "printg.h"
#include "bmp.h"
#include <string.h>
#include "input.h"
#include "alloc.h"
#include "conio.h"
#include "fileflow.h"
#include "error.h"
#include "TD.h"
#include "tdedit.h"
#include <dir.h>
#include "player.h"
#include "astruct.h"

#define XOFF 140
#define YOFF 60
#define XSIZE 440
#define YSIZE 360
#define LISTSIZE 600
#define BASEX 150
#define BASEY 70

extern MX, MY;


int page5();
int editpic(int *nx, int *ny, int *nb);
int picload(char * path); //ÆúÓÃ
int tdviwer(int *nx, int *ny, int *nb);
int clearpixlist(PIX * pixlist, int * pixnum, int num);

#endif