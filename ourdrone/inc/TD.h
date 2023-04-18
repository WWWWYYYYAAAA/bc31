#ifndef _TD_H_
#define _TD_H_

int mou3Dc(int nx, int ny, float *A, float *B, int directX, int directZ,  int enableC, int resetC);
int mouse_3Dmove(int nx, int ny, int *Xoffset, int *Yoffset, int *Zoffset, int directX, int directY, int directZ, int enableM, int resetM);
int move_3d(float xin, float yin, float zin, float A, float B, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset);
int move_3d_p(float xin, float yin, float zin, float A, float B, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset, float percent);
int move_3d_yaxis(float xin, float yin, float zin, float C, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset, float percent);

#endif