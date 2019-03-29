// Shape.h: interface for the Shape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_)
#define AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum DRAWSORT{dsNULL,dsLine,dsCircle,dsPolyGon,dsQuLine,dsBezier,dsStroke,dsText};//画图类型
enum DRAWLINESORT{DlsNull,DlsDDA,DlsBresenham};//画直线方式:DDA或者Bresenham

/*
*抽象图形类
*/
class Shape  
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw(CDC* pDC)=0;//绘制图形方法,子类具体实现
	void SetPenColor(long lColor);
protected:

	long	m_lPenColor;//画笔颜色
};

/*
*直线类
*/
class Line : public Shape
{
public:
	Line(POINT start,POINT end);
	Line(const Line& other);
	Line();
	~Line();

	void Draw(CDC *pDC);//直线类的绘制方法

	bool operator==(const Line& other)const;
	bool operator!=(const Line& other)const;
	void SetStartPoint(POINT tmp);
	void SetEndPoint(POINT tmp);
	void SetDrawLineSort(DRAWLINESORT tmp);
	POINT GetStartPoint();
	POINT GetEndPoint();
	//void SetPenColor(long lColor);
	friend double Distance(POINT pStart,POINT pEnd);//计算两点间的距离
	
private:
	POINT pStart;//起点
	POINT pEnd;//终点
	//long	m_lPenColor;//画笔颜色
	DRAWLINESORT dlsDrawSort;
	void Draw_DDA(CDC* pDC);
	void Draw_Bresenham(CDC *pDC);

};

/*
* 圆
*/
class Circle : public Shape
{
public:
	Circle(POINT pt,double r):pMid(pt),radis(r){};
	Circle(const Circle& other);
	Circle();
	~Circle(){};
	void Draw(CDC* pDC);
	void SetRadis(double r);
	void SetMidPoint(POINT pt);
	double GetRadis()const;
	void SetPenColor(long lColor);
	friend void CirclePoints(int x,int y,long color,CDC *pDC);
private:
	POINT pMid;//圆心
	double radis;//半径
	long	m_lPenColor;//画笔颜色
};


#endif // !defined(AFX_SHAPE_H__C6FCF805_15B4_4F8A_911B_4D2EBDB86094__INCLUDED_)
