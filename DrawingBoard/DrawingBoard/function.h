#pragma once
#define _FUNCTION_H_

#include <windows.h>

#include "data.h"

//该类包含画图函数实现函数
class PAINTSHAPE
{
public:
	PAINTSHAPE();
	~PAINTSHAPE();
	void DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //综合版画线函数
	void Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画三角形函数
	void Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画六边形函数
	void Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画五角星函数
private:
	HDC hDC;
	int BeginX;
	int BeginY;
	int EndX;
	int EndY;
};
