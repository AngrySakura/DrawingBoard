#pragma once
#define _DATE_H_

//ÿ��ͼ�ε����ݽṹ
typedef struct tagData
{
	int ptBeginX, ptBeginY;//���  
	int ptEndX, ptEndY;//�յ�  
	int nEllipseWidth, nEllipseHeight;//��Բ�Ǿ���ʱ��Բ�ĸߺͿ�
	int shape; //ͼ�ε���״
} PAINTDATA;

//���ڱ�ʾ�˵���ͼ��״̬
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