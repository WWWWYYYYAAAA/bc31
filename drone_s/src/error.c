#include <graphics.h>
#include "printg.h"
#include "mouse.h"
#include "visual.h"
#define ERRORX 121
#define ERRORY 34
#define YEND 64
#define XEND 639

int error(int signal)
{
    int style[5] = {0, 2, 0, 0, 1};
    static int flag = 0;
    if(signal == -1)
    {
        //setwritemode(COPY_PUT);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(ERRORX, ERRORY-1, XEND, YEND+1);
        flag = 0;
        return -1;
    }
    else if(signal == 0)
    {
        return flag;
    }
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(ERRORX, ERRORY, XEND, YEND);
    setfillstyle(SOLID_FILL, RED);
    bar(XEND - 30,YEND - 30, XEND, YEND);
    button(XEND - 30,YEND - 30, XEND, YEND, 0);
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    line(XEND - 30+8, YEND - 30+8, XEND-8, YEND-8);
    line(XEND-8, YEND - 30+8, XEND - 30+8, YEND-8);
    setlinestyle(0, 0, 1);
    switch (signal)
    {
    case 1:
        printg_cn(ERRORX+10, ERRORY+10, WHITE, style, ".bmp is not open, wrong path or wrong file type.");
        flag = 1;
    break;
    case 2:
        printg_cn(ERRORX+10, ERRORY+10, WHITE, style, "Workspace is empty.");
        flag = 2;
    break;
    case 3:
        printg_cn(ERRORX+10, ERRORY+10, WHITE, style, "file is not open, wrong path or wrong file type.");
        flag = 3;
    break;
    }
    return 0;
}