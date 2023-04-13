#ifndef _ONOFF_H_
#define _ONOFF_H_

int mouse_signal(int * mousig);
class Mouse_move
{
public:
    int x0;
    int y0;
    int dx;
    int dy;
public:
    Mouse_move(int x, int y);
    int update(int x1, int y1);

};

#endif