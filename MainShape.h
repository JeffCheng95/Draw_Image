#pragma once
class CMainShape
{
public:
	CMainShape();
	~CMainShape();

public:		//公用成员变量
	CPoint m_ptOrigin;		//起始点坐标
	CPoint m_ptEnd;			//终点坐标
	int m_DrawType;			//绘制图形类型
};

class CLine : public CMainShape
{

};

class CRectangle : public CMainShape
{

};

class CEllipse : public CMainShape
{

};

