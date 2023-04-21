#ifndef _PAGE234_H_
#define _PAGE234_H_

#include <graphics.h>
#include "mouse.h"
#include <visual.h>
#include "printg.h"
#include "TD.h"
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include "page5.h"
#include "fileflow.h"
#include <dir.h>
#include "error.h"
#include "input.h"
#include "astruct.h"

#define X0 70
#define Y0 30

extern MX, MY;

//int page2();
//int page3();
//int page4();
//int example(float AR, float BR, int Xoffset,int Zoffset,int Yoffset, int sizeP, int sizeB);
int page234(char *prjdir);

#endif