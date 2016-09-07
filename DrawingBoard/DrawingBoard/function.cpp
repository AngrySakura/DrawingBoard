#define _FUNCTION_H_

#include <windows.h>
#include"function.h"

//�ۺϻ�ֱ�ߺ���
void PAINTSHAPE:: DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	MoveToEx(hDC, BeginX, BeginY, NULL);
	LineTo(hDC, EndX, EndY);
}

//�������κ���
void PAINTSHAPE::Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//���ױ�
	MoveToEx(hDC, BeginX, EndY, NULL);
	LineTo(hDC, EndX, EndY);
	//����б��
	MoveToEx(hDC, BeginX, EndY, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, BeginY);
	//����б��
	MoveToEx(hDC, EndX, EndY, NULL);
	LineTo(hDC, (BeginX + EndX) / 2, BeginY);
}

//�������κ���
void PAINTSHAPE::Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//��ʱ�뽫�������߻���������
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

//������Ǻ���
void PAINTSHAPE::Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	//��ʱ�����λ���ʮ����
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