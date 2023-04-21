#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdlib.h>
#include <stdio.h>
#include "TD.h"
#include "visual.h"
#include "page5.h"
#include "fileflow.h"
#include "mouse.h"
#include <dir.h>
#include <graphics.h>
#include "error.h"
#include <string.h>
#include "astruct.h"

#define XSCREEN1 100
#define XSCREEN2 540
#define YSCREEN1 60
#define YSCREEN2 420

int play(char * prjdir);
int playtofile(char * prjdir);

#endif