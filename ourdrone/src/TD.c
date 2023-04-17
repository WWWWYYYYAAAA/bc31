#include <math.h>

//3d渲染
//旋转与偏�?
int move_3d(float xin, float yin, float zin, float A, float B, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset)
{
	float sA = sin(A), cA = cos(A);	//x轴转
	float xA = xin, yA = cA * yin + sA * zin, zA = sA * yin - cA * zin;
	float sB = sin(B), cB = cos(B);	//z轴转
	float xB = cB * xA - sB * yA, yB = sB * xA + cB * yA, zB = zA;
	
	*xout = xB*0.5 + Xoffset;
	*yout = yB*0.5 + Yoffset;
	*zout = zB*0.5 + Zoffset;
	
	return 0;
}

int move_3d_p(float xin, float yin, float zin, float A, float B, int *xout, int *yout, int *zout, int Xoffset, int Yoffset, int Zoffset, float percent)
{
	float sA = -sin(A), cA = -cos(A);	//x轴转
	float xA = xin, yA = cA * yin + sA * zin, zA = sA * yin - cA * zin;
	float sB = sin(B), cB = cos(B);	//z轴转
	float xB = cB * xA - sB * yA, yB = sB * xA + cB * yA, zB = zA;

	*xout = xB*percent + Xoffset;
	*yout = yB*percent + Yoffset;
	*zout = zB*percent + Zoffset;
	
	return 0;
}

//旋转（鼠标接入）
int mou3Dc(int nx, int ny, float *A, float *B, int directX, int directZ,  int enableC, int resetC)
{
	static oldx = 320, oldy = 240;
	if(enableC)
	{
		*A += 0.01 * (ny - oldy)*directZ;
		*B += 0.01 * (nx - oldx)*directX;
	}
	if(resetC)
	{
		*A = 0;
		*B = 0;
	}
	oldx = nx;
	oldy = ny;
	return 0;
}

//平移（鼠标接入）
void mouse_3Dmove(int nx, int ny, int *Xoffset, int *Yoffset, int *Zoffset, int directX, int directY, int directZ, int enableM, int resetM)
{
	static oldx = 320, oldy = 240;
	if(enableM)
	{
			*Zoffset += (ny - oldy)*directZ;
			*Xoffset += (nx - oldx)*directX;
	}
	if(resetM)
	{
		*Zoffset = 240;
		*Xoffset = 320;
	}
	/*
	if(*Xoffset > 640)
	{
		*Xoffset = 640;
	}
	*/
	oldx = nx;
	oldy = ny;
	return 0;
}
