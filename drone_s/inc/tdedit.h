#ifndef _TDEDIT_H_
#define _TDEDIT_H_

#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include <dos.h>
#include <bios.h>
#include "printg.h"
#include "bmp.h"
#include <string.h>
#include "page5.h"
#include "input.h"
#include "alloc.h"
#include "conio.h"
#include "fileflow.h"
#include "error.h"
#include "TD.h"
#include <dir.h>
#include "astruct.h"
#include <stdlib.h>

int XOR_mark(int x1, int y1, int x2, int y2);
int filelink(int *nx, int *ny, int *nb);
int outfinal(int *nx, int *ny, int *nb);
int tdpreviwer(int *nx, int *ny, int *nb, PIX *pixlist, int pixnum);
int tdtrans(int *nx, int *ny, int *nb);

#endif