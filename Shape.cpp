// Shape.cpp: implementation of the Shape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WTImage.h"
#include "Shape.h"
#include <Math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shape::Shape()
{

}

Shape::~Shape()
{

}

Line::Line()
{
	dlsDrawSort = DlsBresenham;
}

Line::Line(POINT start,POINT end):pStart(start),pEnd(end)
{
	dlsDrawSort = DlsBresenham;
}

Line::Line(const Line& other)
{
	dlsDrawSort = DlsBresenham;
	this->pStart = other.pStart;
	this->pEnd = other.pEnd;

}
bool Line::operator ==(const Line& other)const
{//是否是相同点
	if(this==&other)
		return true;
	else if((this->pStart.x==other.pStart.x)&&(this->pStart.y==other.pStart.y)&&(this->pEnd.x==other.pEnd.x)&&(this->pEnd.y==other.pEnd.y))
	{
		return true;
	}
	else 
	{
		return false;
	}
}


bool Line::operator !=(const Line& other)const
{
	return!(*this==other);
}
void Line::SetStartPoint(POINT tmp)
{
	pStart = tmp;
}

void Line::SetEndPoint(POINT tmp)
{
	pEnd = tmp;
}
void Line::SetDrawLineSort(DRAWLINESORT tmp)
{
	dlsDrawSort = tmp;
}

void Line::Draw(CDC *pDC)
{
	switch(dlsDrawSort)
	{
	case DlsDDA:
		{
			Draw_DDA(pDC);
			break;
		}
	case DlsBresenham:
		{
			Draw_Bresenham(pDC);
			//Draw_DDA(pDC);
			break;
		}
	}
}
void Shape::SetPenColor(long lColor)
{
	m_lPenColor = lColor;
}

void Line::Draw_DDA(CDC *pDC)
{//用DDA算法画直线
	
	int i;
	if(pStart.x==pEnd.x)
	{//X坐标相等，为竖线
		if(pStart.y<=pEnd.y)
		{//每隔一个像素
			for(i=pStart.y;i<=pEnd.y;i++)
				pDC->SetPixel(pStart.x,i,m_lPenColor);
		}
		else
		{
			for(i=pEnd.y;i<=pStart.y;i++)
				pDC->SetPixel(pStart.x,i,m_lPenColor);
		}

		return;
	}

	//为横线
	if(pStart.y==pEnd.y)
	{
		if(pStart.x<=pEnd.x)
		{
			for(i=pStart.x;i<=pEnd.x;i++)
				pDC->SetPixel(i,pStart.y,m_lPenColor);
		}
		else
		{
			for(i=pEnd.x;i<=pStart.x;i++)
				pDC->SetPixel(i,pStart.y,m_lPenColor);
		}

		return;
	}

	//为斜线
	double m=(pEnd.y-pStart.y)*1.0/(pEnd.x-pStart.x);//计算斜率
	double fTemp;

	if(m > -1 && m < 1)
	{//斜率-1<m<1的情况
		if(pStart.x<pEnd.x)
		{
			fTemp=pStart.y-m;
			for(i=pStart.x;i<=pEnd.x;i++)
				pDC->SetPixel(i,fTemp+=m,m_lPenColor);
		}
		else
		{
			fTemp=pEnd.y-m;
			for(i=pEnd.x;i<=pStart.x;i++)
				pDC->SetPixel(i,fTemp+=m,m_lPenColor);
		}
		return;
	}

	if(pStart.y<pEnd.y)
	{
		fTemp=pStart.x-1/m;
		for(i=pStart.y;i<=pEnd.y;i++)
			pDC->SetPixel(fTemp+=1/m,i,m_lPenColor);
	}
	else
	{
		fTemp=pEnd.x-1/m;
		for(i=pEnd.y;i<=pStart.y;i++)
			pDC->SetPixel(fTemp+=1/m,i,m_lPenColor);
	}
}

void Line::Draw_Bresenham(CDC *pDC)
{//用Bresenham算法画直线

	int i;

	if(pStart.x==pEnd.x)
	{
		//为竖线
		if(pStart.y<=pEnd.y)
		{
			for(i=pStart.y;i<=pEnd.y;i++)
				pDC->SetPixel(pStart.x,i,m_lPenColor);
		}
		else
		{
			for(i=pEnd.y;i<=pStart.y;i++)
				pDC->SetPixel(pStart.x,i,m_lPenColor);
		}

		return;
	}

	//为横线
	if(pStart.y==pEnd.y)
	{
		if(pStart.x<=pEnd.x)
		{
			for(i=pStart.x;i<=pEnd.x;i++)
				pDC->SetPixel(i,pStart.y,m_lPenColor);
		}
		else
		{
			for(i=pEnd.x;i<=pStart.x;i++)
				pDC->SetPixel(i,pStart.y,m_lPenColor);
		}

		return;
	}

	//为斜线
	double m=(pEnd.y-pStart.y)*1.0/(pEnd.x-pStart.x);
	double p;

	p=2*m-1;
	if(m>0 && m<=1)
	{
		if(pStart.x<pEnd.x)
		{
			while(pStart.x<=pEnd.x)
			{
				pDC->SetPixel(pStart.x++,pStart.y,m_lPenColor);
				if(p>=0)
				{
					p+=2*m-2;
					pStart.y++;
				}
				else
					p+=2*m;
			}
		}
		else
		{
			while(pEnd.x<=pStart.x)
			{
				pDC->SetPixel(pEnd.x++,pEnd.y,m_lPenColor);
				if(p>=0)
				{
					p+=2*m-2;
					pEnd.y++;
				}
				else
					p+=2*m;
			}
		}

		return;
	}

	p=-2*m-1;
	if(m<0 && m>=-1)
	{
		if(pStart.x<pEnd.x)
		{
			while(pStart.x<=pEnd.x)
			{
				pDC->SetPixel(pStart.x++,pStart.y,m_lPenColor);
				if(p>=0)
				{
					p+=-2*m-2;
					pStart.y--;
				}
				else
					p+=-2*m;
			}
		}
		else
		{
			while(pEnd.x<=pStart.x)
			{
				pDC->SetPixel(pEnd.x++,pEnd.y,m_lPenColor);
				if(p>=0)
				{
					p+=-2*m-2;
					pEnd.y--;
				}
				else
					p+=-2*m;
			}
		}

		return;
	}

	p=2/m-1;
	if(m>1)
	{
		if(pStart.y<pEnd.y)
		{
			while(pStart.y<=pEnd.y)
			{
				pDC->SetPixel(pStart.x,pStart.y++,m_lPenColor);
				if(p>=0)
				{
					p+=2/m-2;
					pStart.x++;
				}
				else
					p+=2/m;
			}
		}
		else
		{
			while(pEnd.y<=pStart.y)
			{
				pDC->SetPixel(pEnd.x,pEnd.y++,m_lPenColor);
				if(p>=0)
				{
					p+=2/m-2;
					pEnd.x++;
				}
				else
					p+=2/m;
			}
		}

		return;
	}

	p=-2/m-1;
	if(pStart.y<pEnd.y)
	{
		while(pStart.y<=pEnd.y)
		{
			pDC->SetPixel(pStart.x,pStart.y++,m_lPenColor);
			if(p>=0)
			{
				p+=-2/m-2;
				pStart.x--;
			}
			else
				p+=-2/m;
		}
	}
	else
	{
		while(pEnd.y<=pStart.y)
		{
			pDC->SetPixel(pEnd.x,pEnd.y++,m_lPenColor);
			if(p>=0)
			{
				p+=-2/m-2;
				pEnd.x--;
			}
			else
				p+=-2/m;
		}
	}
}

POINT Line::GetStartPoint()
{
	return pStart;
}

POINT Line::GetEndPoint()
{
	return pEnd;
}

Line::~Line()
{
}

double Distance(POINT pStart,POINT pEnd)
{
	double deltX = pEnd.x-pStart.x;
	double deltY = pEnd.y-pEnd.y;
	return sqrt(deltX*deltX+deltY*deltY);
}
Circle::Circle()
{

}

Circle::Circle(const Circle& other)
{
	this->pMid = other.pMid;
	this->radis = other.radis;
}

void Circle::Draw(CDC *pDC)
{//中点算法画圆
	int x,y;
	double p;

	pDC->SetViewportOrg(pMid);

	x=0;
	y=radis;
	p=1.25-radis;
	while(x<=y+1)
	{
		CirclePoints(x,y,m_lPenColor,pDC);
		
		x++;
		if(p>=0)
		{
			y--;
			p+=2.0*(x-y)+5;
		}
		else
			p+=2*x+3;
	}

	pDC->SetViewportOrg(0,0);
}

void CirclePoints(int x,int y,long color,CDC *pDC)
{
		//第1象限
		pDC->SetPixel(x,y,color);
		pDC->SetPixel(y,x,color);
		//第2象限
		pDC->SetPixel(-x,y,color);
		pDC->SetPixel(-y,x,color);
		//第3象限
		pDC->SetPixel(-y,-x,color);
		pDC->SetPixel(-x,-y,color);
		//第4象限
		pDC->SetPixel(x,-y,color);
		pDC->SetPixel(y,-x,color);
}

double Circle::GetRadis()const
{
	return this->radis;
}

void Circle::SetPenColor(long lColor)
{
	m_lPenColor = lColor;
}

void Circle::SetMidPoint(POINT pt)
{
	pMid = pt;
}

void Circle::SetRadis(double r)
{
	radis = r;
}