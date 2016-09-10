/*-------------------------------------------------------------------
功能：绘制指定图形
--------------------------------------------------------------------*/
#include<Windows.h>
#include "Windowsx.h"
#include <tchar.h>
#include<vector>
#include"resource.h"
#include"data.h"
#include"function.h"

using namespace std;

//函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitShape();
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

BOOL IsMove;    //判断是否需要移动图形
BOOL Move;
//BOOL isPaint;   //解决移动过程中黑影问题
int rectshape = 0;

/*-------------------------------------------------------------------
名称：WndProc
功能：消息处理
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSHAPE paint;
	static vector<PAINTDATA> datas;
	vector<PAINTDATA>::const_iterator item;
	vector<PAINTDATA>::iterator deletion;
	static int penStyle = PS_SOLID;
	static PAINTDATA *pCurrentData = NULL;   //指向当前PAINTDATA的指针
	static PAINTDATA *pUpdateData = NULL;    //用于存储被移动后的图形
	HDC hDC;
	PAINTSTRUCT	ps;
	static POINT ptOld, ptNew;
	static RECT rectOld, rectLast, rectMove, rectNew;

	switch (message)
	{
	case WM_COMMAND:                         //点击菜单选择决定要画的图形
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
		if (IsMove)                        //如果“移动菜单”状态为开
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
		        else   //全都都匹配不到还有错误
		        {
		            Move = FALSE;
		        }
			}
		}
		else                        // 如果“移动菜单”状态为闭
		{
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
		}
		break;
	case WM_MOUSEMOVE:    //在鼠标移动过程中动态显示要画的图形
		//如果处于移动状态
		if (Move)
		{
			//鼠标移动画边框
			POINT ptMove;
			ptMove.x = LOWORD(lParam);
			ptMove.y = HIWORD(lParam);
			//用移动过程中的鼠标位置计算图形信息
			rectMove.left = rectOld.left + (ptMove.x - ptOld.x);
			rectMove.top = rectOld.top + (ptMove.y - ptOld.y);
			rectMove.right = rectMove.left + (rectOld.right - rectOld.left);
			rectMove.bottom = rectMove.top + (rectOld.bottom - rectOld.top);

			hDC = GetDC(hWnd);
			//-擦掉上一次的拖动的矩形轨迹
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
原构想：移动图形时，在图形最初的位置用灰色画刷来显示
问题：无法解决图形移动过程中原图形闪烁问题
猜想：移动过程中设置的画刷和 WM_PAINT的画刷冲突
==================================================================
		    //画初始的矩形
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
			//画本次移动的矩形轨迹
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
			//如果处于画图状态
			if (pCurrentData != NULL)
			{
				hDC = GetDC(hWnd);
				SelectObject(hDC, GetStockObject(NULL_BRUSH));
				SetROP2(hDC, R2_NOT);	      //防止重影
											  //根据draw状态判断鼠标移动过程中是否要画图
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
				//实时监听鼠标落点并不断更新
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
		//确定鼠标释放位置
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
			
			//防止移动图形时上一个被移动的图形被擦去
			rectLast.left = 0; rectLast.top = 0; rectLast.right = 0; rectLast.bottom = 0;

			//移动后的坐标加入容器 
			pUpdateData = new PAINTDATA;
			pUpdateData->ptBeginX = rectNew.left;
			pUpdateData->ptBeginY = rectNew.top;
			pUpdateData->ptEndX = rectNew.right;
			pUpdateData->ptEndY = rectNew.bottom;
			pUpdateData->shape = rectshape;
			datas.push_back(*pUpdateData);
			delete(pUpdateData);
			//删除移动前的图形数据
			for (deletion = datas.begin(); deletion != datas.end(); deletion++)
			{
				if ((deletion->ptBeginX == rectOld.left) && (deletion->ptEndY == rectOld.bottom))
				{
					deletion = datas.erase(deletion);
					break;
				}
			}
			//被移动后的图形坐标 
			CopyRect(&rectOld,&rectNew);
			InvalidateRect(hWnd, NULL, TRUE);
			ReleaseDC(hWnd, hDC);
		}
		else 
		{
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
				datas.push_back(*pCurrentData);           //将数据传入vector容器，保存这一个图形
				delete(pCurrentData);        pCurrentData = NULL;
			}
		}
		break;
	case WM_PAINT:                      //缓冲重绘
		BeginPaint(hWnd, &ps);
		//将所有图形重新画一遍  
		for (item = datas.begin(); item != datas.end(); item++)          //迭代器遍历
		{
			hDC = GetDC(hWnd);
			SelectObject(hDC, GetStockObject(NULL_BRUSH));
			//SelectObject(hDC, GetStockObject(BLACK_PEN));
			SetROP2(hDC, R2_BLACK);
			switch (item->shape)    //图形选择
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

//初始化菜单图形状态函数
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