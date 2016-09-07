#define _FUNCTION_H_

#include <windows.h>
#include"function.h"

//综合画直线函数
void PAINTSHAPE:: DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	MoveToEx(hDC, BeginX, BeginY, NULL);
	LineTo(hDC, EndX, EndY);
}

//画三角形函数
void PAINTSHAPE::Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//画底边
	MoveToEx(hDC, BeginX, EndY, NULL);
	LineTo(hDC, EndX, EndY);
	//画左斜边
	MoveToEx(hDC, BeginX, EndY, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, BeginY);
	//画右斜边
	MoveToEx(hDC, EndX, EndY, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, BeginY);
}

//画六边形函数
void PAINTSHAPE::Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//逆时针将六点连线画出六边形
	MoveToEx(hDC, (3 * BeginX + EndX) / 4, BeginY, NULL);
	LineTo(hDC, BeginX, (BeginY + EndY) / 2);

	MoveToEx(hDC, BeginX, (BeginY + EndY) / 2, NULL);
	LineTo(hDC, (3 * BeginX + EndX) / 4, EndY);

	MoveToEx(hDC, (3 * BeginX + EndX) / 4, EndY, NULL);
	LineTo(hDC, (BeginX + 3 * EndX) / 4, EndY);

	MoveToEx(hDC, (BeginX + 3 * EndX) / 4, EndY, NULL);
	LineTo(hDC, EndX, (BeginY + EndY) / 2);

	MoveToEx(hDC, EndX, (BeginY + EndY) / 2, NULL);
	LineTo(hDC, (BeginX + 3 * EndX) / 4, BeginY);

	MoveToEx(hDC, (BeginX + 3 * EndX) / 4, BeginY, NULL);
	LineTo(hDC, (3 * BeginX + EndX) / 4, BeginY);
}

//画五角星函数
void PAINTSHAPE::Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//逆时针依次画出十条边
	MoveToEx(hDC, (BeginX + EndX) / 2, BeginY, NULL);
	LineTo(hDC, (3 * BeginX + 2 * EndX) / 5, (3 * BeginY + 2 * EndY) / 5);

	MoveToEx(hDC, (3 * BeginX + 2 * EndX) / 5, (3 * BeginY + 2 * EndY) / 5, NULL);
	LineTo(hDC, BeginX, (3 * BeginY + 2 * EndY) / 5);

	MoveToEx(hDC, BeginX, (3 * BeginY + 2 * EndY) / 5, NULL);
	LineTo(hDC, (7 * BeginX + 3 * EndX) / 10, (2 * BeginY + 3 * EndY) / 5);

	MoveToEx(hDC, (7 * BeginX + 3 * EndX) / 10, (2 * BeginY + 3 * EndY) / 5, NULL);
	LineTo(hDC, (4 * BeginX + EndX) / 5, EndY);

	MoveToEx(hDC, (4 * BeginX + EndX) / 5, EndY, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, (3 * BeginY + 7 * EndY) / 10);

	MoveToEx(hDC, (BeginX + EndX) / 2, (3 * BeginY + 7 * EndY) / 10, NULL);
	LineTo(hDC, (BeginX + 4 * EndX) / 5, EndY);

	MoveToEx(hDC, (BeginX + 4 * EndX) / 5, EndY, NULL);
	LineTo(hDC, (3 * BeginX + 7 * EndX) / 10, (2 * BeginY + 3 * EndY) / 5);

	MoveToEx(hDC, (3 * BeginX + 7 * EndX) / 10, (2 * BeginY + 3 * EndY) / 5, NULL);
	LineTo(hDC, EndX, (3 * BeginY + 2 * EndY) / 5);

	MoveToEx(hDC, EndX, (3 * BeginY + 2 * EndY) / 5, NULL);
	LineTo(hDC, (2 * BeginX + 3 * EndX) / 5, (3 * BeginY + 2 * EndY) / 5);

	MoveToEx(hDC, (2 * BeginX + 3 * EndX) / 5, (3 * BeginY + 2 * EndY) / 5, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, BeginY);
}

PAINTSHAPE::PAINTSHAPE()
{
}

PAINTSHAPE::~PAINTSHAPE()
{
}