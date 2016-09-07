/*-------------------------------------------------------------------
���ܣ�����ָ��ͼ��
--------------------------------------------------------------------*/
#include<Windows.h>
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
		L"SHAPE",
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

/*-------------------------------------------------------------------
���ƣ�WndProc
���ܣ���Ϣ����
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSHAPE paint;
	static vector<PAINTDATA> datas;
	vector<PAINTDATA>::const_iterator item;
	static int penStyle = PS_SOLID;
	static PAINTDATA *pCurrentData = NULL;//ָ��ǰPAINTDATA��ָ��
	HDC hDC;
	PAINTSTRUCT	ps;

	switch (message)
	{
	case WM_COMMAND:    //����˵�ѡ�����Ҫ����ͼ��
		switch (wParam)
		{
		case ID_LINE:
			InitShape();
			fSizeLine = TRUE;
			break;
		case ID_RECTANGLE:
			InitShape();
			fSizeRectangle = TRUE;
			break;
		case ID_ELLIPSE:
			InitShape();
			fSizeEllipse = TRUE;
			break;
		case ID_ROUNDRECT:
			InitShape();
			fSizeRoundRect = TRUE;
			break;
		case ID_TRIANGLE:
			InitShape();
			fSizeTriangle = TRUE;
			break;
		case ID_SEXANGLE:
			InitShape();
			fSizeSexangle = TRUE;
			break;
		case ID_PENTAGRAM:
			InitShape();
			fSizePentagram = TRUE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
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
		break;
	case WM_MOUSEMOVE:                                //������ƶ������ж�̬��ʾҪ����ͼ��,
		if (pCurrentData != NULL)
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			SetROP2(hDC, R2_NOT);	      //��ֹ��Ӱ
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
		break;
	case WM_LBUTTONUP:
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
			datas.push_back(*pCurrentData);           //������һ��ͼ��
		}
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		//������ͼ�����»�һ��  
		for (item = datas.begin(); item != datas.end(); item++)
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
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
