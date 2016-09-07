#pragma once
#define _FUNCTION_H_

#include <windows.h>

#include "data.h"

//���������ͼ����ʵ�ֺ���
class PAINTSHAPE
{
public:
	PAINTSHAPE();
	~PAINTSHAPE();
	void DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //�ۺϰ滭�ߺ���
	void Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //�������κ���
	void Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //�������κ���
	void Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //������Ǻ���
private:
	HDC hDC;
	int BeginX;
	int BeginY;
	int EndX;
	int EndY;
};
