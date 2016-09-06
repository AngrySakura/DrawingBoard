/*-------------------------------------------------------------------
功能：绘制指定图形
--------------------------------------------------------------------*/
#include<Windows.h>
#include<vector>
#include"resource.h"

using namespace std;

//函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //综合版画线函数
void Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画三角形函数
void Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画六边形函数
void Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY);  //画五角星函数

																	  //全局变量
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

//每个图形的数据结构
typedef struct tagData
{
	int ptBeginX, ptBeginY;//起点  
	int ptEndX, ptEndY;//终点  
	int nEllipseWidth, nEllipseHeight;//画圆角矩形时椭圆的高和宽
	BOOL shape; //图形的形状
} PAINTDATA;

/*-------------------------------------------------------------------
名称：WinMain
功能：窗口
-------------------------------------------------------------------*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE PreInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;   //定义窗口句柄
	MSG msg;   //储存消息的变量
	WNDCLASS wc;   //定义窗口类型变量

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
	//创建窗口
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
	//显示更新
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
名称：WndProc
功能：消息处理
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static vector<PAINTDATA> datas;
	vector<PAINTDATA>::const_iterator item;
	static int penStyle = PS_SOLID;
	static PAINTDATA *pCurrentData = NULL;//指向当前PAINTDATA的指针
	HDC hDC;
	PAINTSTRUCT	ps;

	switch (message)
	{
	case WM_COMMAND:    //点击菜单选择决定要画的图形
		switch (wParam)
		{
		case ID_LINE:
			fSizeLine = TRUE;
			fSizeRectangle = FALSE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = FALSE;
			fSizeSexangle = FALSE;
			fSizePentagram = FALSE;
			break;
		case ID_RECTANGLE:
			fSizeLine = FALSE;
			fSizeRectangle = TRUE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = FALSE;
			fSizeSexangle = FALSE;
			fSizePentagram = FALSE;
			break;
		case ID_ELLIPSE:
			fSizeLine = FALSE;
			fSizeRectangle = FALSE;
			fSizeEllipse = TRUE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = FALSE;
			fSizeSexangle = FALSE;
			fSizePentagram = FALSE;
			break;
		case ID_ROUNDRECT:
			fSizeLine = FALSE;
			fSizeRectangle = FALSE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = TRUE;
			fSizeTriangle = FALSE;
			fSizeSexangle = FALSE;
			fSizePentagram = FALSE;
			break;
		case ID_TRIANGLE:
			fSizeLine = FALSE;
			fSizeRectangle = FALSE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = TRUE;
			fSizeSexangle = FALSE;
			fSizePentagram = FALSE;
			break;
		case ID_SEXANGLE:
			fSizeLine = FALSE;
			fSizeRectangle = FALSE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = FALSE;
			fSizeSexangle = TRUE;
			fSizePentagram = FALSE;
			break;
		case ID_PENTAGRAM:
			fSizeLine = FALSE;
			fSizeRectangle = FALSE;
			fSizeEllipse = FALSE;
			fSizeRoundRect = FALSE;
			fSizeTriangle = FALSE;
			fSizeSexangle = FALSE;
			fSizePentagram = TRUE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		pCurrentData = new PAINTDATA;                 //获取起始位置的坐标并初始化数据
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
	case WM_MOUSEMOVE:                                //在鼠标移动过程中动态显示要画的图形,
		if (pCurrentData != NULL)
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			SetROP2(hDC, R2_NOT);	      //防止重影
			if (fDrawLine)
			{
				DrawLine(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
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
				Triangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			if (fDrawSexangle)
			{
				Sexangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			if (fDrawPentagram)
			{
				Pentagram(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			pCurrentData->ptEndX = LOWORD(lParam);
			pCurrentData->ptEndY = HIWORD(lParam);
			if (fDrawLine)
			{
				DrawLine(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
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
				Triangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			if (fDrawSexangle)
			{
				Sexangle(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			if (fDrawPentagram)
			{
				Pentagram(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
			}
			ReleaseDC(hWnd, hDC);
		}
		break;
	case WM_LBUTTONUP:
		if (pCurrentData != NULL)                    //鼠标左键松开时关闭相应图形的权限
		{
			switch (pCurrentData->shape)          //图形选择
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
			datas.push_back(*pCurrentData);           //保存这一个图形
		}
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		//将所有图形重新画一遍  
		for (item = datas.begin(); item != datas.end(); item++)
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			SetROP2(hDC, R2_BLACK);
			switch (item->shape)    //图形选择
			{
			case 1:
				DrawLine(hDC, pCurrentData->ptBeginX, pCurrentData->ptBeginY, pCurrentData->ptEndX, pCurrentData->ptEndY);
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
				Triangle(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 6:
				Sexangle(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
				break;
			case 7:
				Pentagram(hDC, item->ptBeginX, item->ptBeginY, item->ptEndX, item->ptEndY);
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

void DrawLine(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
{
	MoveToEx(hDC, BeginX, BeginY, NULL);
	LineTo(hDC, EndX, EndY);
}

//画三角形函数
void Triangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
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
void Sexangle(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
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
void Pentagram(HDC hDC, int BeginX, int BeginY, int EndX, int EndY)
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
