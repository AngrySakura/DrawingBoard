#pragma once
#define _DATE_H_

//每个图形的数据结构
typedef struct tagData
{
	int ptBeginX, ptBeginY;//起点  
	int ptEndX, ptEndY;//终点  
	int nEllipseWidth, nEllipseHeight;//画圆角矩形时椭圆的高和宽
	int shape; //图形的形状
} PAINTDATA;

//用于表示菜单的图形状态
typedef struct tagSize
{
	BOOL fSizeLine;
	BOOL fSizeRectangle;
	BOOL fSizeEllipse;
	BOOL fSizeRoundRect;
	BOOL fSizeTriangle;
	BOOL fSizeSexangle;
	BOOL fSizePentagram;
}PAINTSIZE;