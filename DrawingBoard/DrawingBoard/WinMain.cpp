/*-------------------------------------------------------------------
���ܣ�����ָ��ͼ��
--------------------------------------------------------------------*/
#include<Windows.h>
#include "Windowsx.h"
#include <tchar.h>
#include<vector>
#include"resource.h"
#include"data.h"
#include"function.h"

using namespace std;

//��������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitShape();
																	  //ȫ�ֱ���
BOOL fSizeLine;
BOOL fDrawLine;
BOOL fSizeRectangle;
BOOL fDrawRectangle;
BOOL fSizeEllipse;
BOOL fDrawEllipse;
BOOL fSizeRoundRect;
BOOL fDrawRoundRect;
BOOL fSizeTriangle;
BOOL fDrawTriangle;
BOOL fSizeSexangle;
BOOL fDrawSexangle;
BOOL fSizePentagram;
BOOL fDrawPentagram;

BOOL IsMove;    //�ж��Ƿ���Ҫ�ƶ�ͼ��
BOOL Move;
//BOOL isPaint;   //����ƶ������к�Ӱ����
int rectshape = 0;

/*-------------------------------------------------------------------
���ƣ�WndProc
���ܣ���Ϣ����
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSHAPE paint;
	static vector<PAINTDATA> datas;
	vector<PAINTDATA>::const_iterator item;
	vector<PAINTDATA>::iterator deletion;
	static int penStyle = PS_SOLID;
	static PAINTDATA *pCurrentData = NULL;   //ָ��ǰPAINTDATA��ָ��
	static PAINTDATA *pUpdateData = NULL;    //���ڴ洢���ƶ����ͼ��
	HDC hDC;
	PAINTSTRUCT	ps;
	static POINT ptOld, ptNew;
	static RECT rectOld, rectLast, rectMove, rectNew;

	switch (message)
	{
	case WM_COMMAND:                         //����˵�ѡ�����Ҫ����ͼ��
		switch (wParam)
		{
		case ID_LINE:
			InitShape();
			fSizeLine = TRUE;
			IsMove = FALSE;
			break;
		case ID_RECTANGLE:
			InitShape();
			fSizeRectangle = TRUE;
			IsMove = FALSE;
			break;
		case ID_ELLIPSE:
			InitShape();
			fSizeEllipse = TRUE;
			IsMove = FALSE;
			break;
		case ID_ROUNDRECT:
			InitShape();
			fSizeRoundRect = TRUE;
			IsMove = FALSE;
			break;
		case ID_TRIANGLE:
			InitShape();
			fSizeTriangle = TRUE;
			IsMove = FALSE;
			break;
		case ID_SEXANGLE:
			InitShape();
			fSizeSexangle = TRUE;
			IsMove = FALSE;
			break;
		case ID_PENTAGRAM:
			InitShape();
			fSizePentagram = TRUE;
			IsMove = FALSE;
			break;
		case ID_MOVE:
			InitShape();
			IsMove = TRUE;
	/*		if (movecount % 2 == 0)        
			{
				IsMove = TRUE;
				movecount++;
			}
			else
			{
				IsMove = FALSE;
				movecount++;
			}*/
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		if (IsMove)                        //������ƶ��˵���״̬Ϊ��
		{
			ptOld.x = LOWORD(lParam);
			ptOld.y = HIWORD(lParam);
			for (item = datas.begin(); item != datas.end(); item++)
			{
				rectOld.left = item->ptBeginX;
				rectOld.top = item->ptBeginY;
				rectOld.right = item->ptEndX;
				rectOld.bottom = item->ptEndY;
				rectshape = item->shape;
	            if (PtInRect(&rectOld,ptOld))
		        {
		            Move = TRUE;
		            break;
		        }
		        else   //ȫ����ƥ�䲻�����д���
		        {
		            Move = FALSE;
		        }
			}
		}
		else                        // ������ƶ��˵���״̬Ϊ��
		{
			pCurrentData = new PAINTDATA;                 //��ȡ��ʼλ�õ����겢��ʼ������
			pCurrentData->ptBeginX = pCurrentData->ptEndX = LOWORD(lParam);
			pCurrentData->ptBeginY = pCurrentData->ptEndY = HIWORD(lParam);
			pCurrentData->nEllipseHeight = pCurrentData->nEllipseWidth = 30;
			if (fSizeLine)
			{
				fDrawLine = TRUE;
				pCurrentData->shape = 1;
			}
			if (fSizeRectangle)
			{
				fDrawRectangle = TRUE;
				pCurrentData->shape = 2;
			}
			if (fSizeEllipse)
			{
				fDrawEllipse = TRUE;
				pCurrentData->shape = 3;
			}
			if (fSizeRoundRect)
			{
				fDrawRoundRect = TRUE;
				pCurrentData->shape = 4;
			}
			if (fSizeTriangle)
			{
				fDrawTriangle = TRUE;
				pCurrentData->shape = 5;
			}
			if (fSizeSexangle)
			{
				fDrawSexangle = TRUE;
				pCurrentData->shape = 6;
			}
			if (fSizePentagram)
			{
				fDrawPentagram = TRUE;
				pCurrentData->shape = 7;
			}
		}
		break;
	case WM_MOUSEMOVE:    //������ƶ������ж�̬��ʾҪ����ͼ��
		//��������ƶ�״̬
		if (Move)
		{
			//����ƶ����߿�
			POINT ptMove;
			ptMove.x = LOWORD(lParam);
			ptMove.y = HIWORD(lParam);
			//���ƶ������е����λ�ü���ͼ����Ϣ
			rectMove.left = rectOld.left + (ptMove.x - ptOld.x);
			rectMove.top = rectOld.top + (ptMove.y - ptOld.y);
			rectMove.right = rectMove.left + (rectOld.right - rectOld.left);
			rectMove.bottom = rectMove.top + (rectOld.bottom - rectOld.top);

			hDC = GetDC(hWnd);
			//-������һ�ε��϶��ľ��ι켣
			SelectObject(hDC, GetStockObject(WHITE_PEN));
			SelectObject(hDC, GetStockObject(WHITE_BRUSH));
			//Rectangle(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
			switch (rectshape)
			{
			case 1:
				paint.DrawLine(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			case 2:
				Rectangle(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			case 3:
				Ellipse(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			case 4:
				RoundRect(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom, 30, 30);
				break;
			case 5:
				paint.Triangle(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			case 6:
				paint.Sexangle(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			case 7:
				paint.Pentagram(hDC, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
				break;
			}
/*==================================================================
ԭ���룺�ƶ�ͼ��ʱ����ͼ�������λ���û�ɫ��ˢ����ʾ
���⣺�޷����ͼ���ƶ�������ԭͼ����˸����
���룺�ƶ����������õĻ�ˢ�� WM_PAINT�Ļ�ˢ��ͻ
==================================================================
		    //����ʼ�ľ���
			SelectObject(hDC, GetStockObject(NULL_PEN));
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			//Rectangle(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
			switch (rectshape)
			{
			case 1:
				paint.DrawLine(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			case 2:
				Rectangle(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			case 3:
				Ellipse(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			case 4:
				RoundRect(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom, 30, 30);
				break;
			case 5:
				paint.Triangle(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			case 6:
				paint.Sexangle(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			case 7:
				paint.Pentagram(hDC, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
				break;
			}
*/		
			//�������ƶ��ľ��ι켣
			SelectObject(hDC, GetStockObject(BLACK_PEN));
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			//Rectangle(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
			switch (rectshape)
			{
			case 1:
				paint.DrawLine(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			case 2:
				Rectangle(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			case 3:
				Ellipse(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			case 4:
				RoundRect(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom, 30, 30);
				break;
			case 5:
				paint.Triangle(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			case 6:
				paint.Sexangle(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			case 7:
				paint.Pentagram(hDC, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
				break;
			}
			CopyRect(&rectLast, &rectMove);
		}
		else
		{
			//������ڻ�ͼ״̬
			if (pCurrentData != NULL)
			{
				hDC = GetDC(hWnd);
				SelectObject(hDC, GetStockObject(NULL_BRUSH));
				SetROP2(hDC, R2_NOT);	      //��ֹ��Ӱ
											  //����draw״̬�ж�����ƶ��������Ƿ�Ҫ��ͼ
				if (fDrawLine)
				{
					paint.DrawLine(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawRectangle)
				{
					Rectangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawEllipse)
				{
					Ellipse(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawRoundRect)
				{
					RoundRect(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY, pCurrentData->nEllipseWidth, pCurrentData->nEllipseHeight);
				}
				if (fDrawTriangle)
				{
					paint.Triangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawSexangle)
				{
					paint.Sexangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawPentagram)
				{
					paint.Pentagram(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				//ʵʱ���������㲢���ϸ���
				pCurrentData->ptEndX = LOWORD(lParam);
				pCurrentData->ptEndY = HIWORD(lParam);
				if (fDrawLine)
				{
					paint.DrawLine(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawRectangle)
				{
					Rectangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawEllipse)
				{
					Ellipse(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawRoundRect)
				{
					RoundRect(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY, pCurrentData->nEllipseWidth, pCurrentData->nEllipseHeight);
				}
				if (fDrawTriangle)
				{
					paint.Triangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawSexangle)
				{
					paint.Sexangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				if (fDrawPentagram)
				{
					paint.Pentagram(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
				}
				ReleaseDC(hWnd, hDC);
			}
		}
		break;
	case WM_LBUTTONUP:
		//ȷ������ͷ�λ��
		if (Move)
		{
			hDC = GetDC(hWnd);
			Move = FALSE;
			ptNew.x = LOWORD(lParam);
			ptNew.y = HIWORD(lParam);
			rectNew.left = rectOld.left + (ptNew.x - ptOld.x);
			rectNew.top = rectOld.top + (ptNew.y - ptOld.y);
			rectNew.right = rectNew.left + (rectOld.right - rectOld.left);
			rectNew.bottom = rectNew.top + (rectOld.bottom - rectOld.top);
			
			//��ֹ�ƶ�ͼ��ʱ��һ�����ƶ���ͼ�α���ȥ
			rectLast.left = 0; rectLast.top = 0; rectLast.right = 0; rectLast.bottom = 0;

			//�ƶ��������������� 
			pUpdateData = new PAINTDATA;
			pUpdateData->ptBeginX = rectNew.left;
			pUpdateData->ptBeginY = rectNew.top;
			pUpdateData->ptEndX = rectNew.right;
			pUpdateData->ptEndY = rectNew.bottom;
			pUpdateData->shape = rectshape;
			datas.push_back(*pUpdateData);
			delete(pUpdateData);
			//ɾ���ƶ�ǰ��ͼ������
			for (deletion = datas.begin(); deletion != datas.end(); deletion++)
			{
				if ((deletion->ptBeginX == rectOld.left) && (deletion->ptEndY == rectOld.bottom))
				{
					deletion = datas.erase(deletion);
					break;
				}
			}
			//���ƶ����ͼ������ 
			CopyRect(&rectOld,&rectNew);
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hDC);
		}
		else 
		{
			if (pCurrentData != NULL)                    //�������ɿ�ʱ�ر���Ӧͼ�ε�Ȩ��
			{
				switch (pCurrentData->shape)          //ͼ��ѡ��
				{
				case 1:
					fDrawLine = FALSE;
					break;
				case 2:
					fDrawRectangle = FALSE;
					break;
				case 3:
					fDrawEllipse = FALSE;
					break;
				case 4:
					fDrawRoundRect = FALSE;
					break;
				case 5:
					fDrawTriangle = FALSE;
					break;
				case 6:
					fDrawSexangle = FALSE;
					break;
				case 7:
					fDrawPentagram = FALSE;
					break;
				}
				pCurrentData->ptEndX = LOWORD(lParam);
				pCurrentData->ptEndY = HIWORD(lParam);
				InvalidateRect(hWnd, NULL, true);
				datas.push_back(*pCurrentData);           //�����ݴ���vector������������һ��ͼ��
				delete(pCurrentData);        pCurrentData = NULL;
			}
		}
		break;
	case WM_PAINT:                      //�����ػ�
		BeginPaint(hWnd, &ps);
		//������ͼ�����»�һ��  
		for (item = datas.begin(); item != datas.end(); item++)          //����������
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			//SelectObject(hDC, GetStockObject(BLACK_PEN));
			SetROP2(hDC, R2_BLACK);
			switch (item->shape)    //ͼ��ѡ��
			{
			case 1:
				paint.DrawLine(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 2:
				Rectangle(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 3:
				Ellipse(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 4:
				RoundRect(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY, item->nEllipseWidth, item->nEllipseHeight);
				break;
			case 5:
				paint.Triangle(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 6:
				paint.Sexangle(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 7:
				paint.Pentagram(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			}
			ReleaseDC(hWnd, hDC);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*-------------------------------------------------------------------
���ƣ�WinMain
���ܣ�����
-------------------------------------------------------------------*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE PreInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;   //���崰�ھ��
	MSG msg;   //������Ϣ�ı���
	WNDCLASS wc;   //���崰�����ͱ���

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = L"SHAPE";

	if (!RegisterClass(&wc))
	{
		return (FALSE);
	}
	//��������
	hWnd = CreateWindow(
		L"SHAPE",
		L"DrawingBoard",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		return (FALSE);
	}
	//��ʾ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
	UNREFERENCED_PARAMETER(lpCmdLine);
}

//��ʼ���˵�ͼ��״̬����
void InitShape()
{
	fSizeLine = FALSE;
	fSizeRectangle = FALSE;
	fSizeEllipse = FALSE;
	fSizeRoundRect = FALSE;
	fSizeTriangle = FALSE;
	fSizeSexangle = FALSE;
	fSizePentagram = FALSE;
}