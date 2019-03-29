// BottomFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "WTImage.h"
#include "BottomFormView.h"
#include "MainShape.h"
#include "TopFormView.h"
#include "MainFrm.h"
#include "Graph.h"
#include "SettingDlg.h"
#include "WTImageDoc.h"
#include "MagnifyDlg.h"

// 放大镜功能中用到
#define  MAGNIFIERSIZE				30 //矩形大小
#define  MAGNIFYINGMULTIPLE			4  //放大倍数
#define  OFFSETWIDE					16 //偏离光标热点（宽）
#define  OFFSETHIGH					20 //偏离光标热点（高）


CBottomFormView *pBottomFormView;

// CBottomFormView

IMPLEMENT_DYNCREATE(CBottomFormView, CFormView)

CBottomFormView::CBottomFormView()
	: CFormView(IDD_BOTTOMFORMVIEW)
{
	pBottomFormView = this;
	m_DrawType = 0;
	m_BtisDown = false;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
	m_color = RGB(0, 0, 0);
	m_color_lightpen = RGB(255, 255, 77);
	m_strFontName = "";
	m_pMDC = new CDC();
	m_ptPolyFirst = 0;
	m_ptPolyLast = 0;
	m_PolyCount = 0;
	m_strLine = "";
	m_ptTextOrigin = 0;
	m_flagFullPaint = false;
	m_rectTracker.m_nStyle = CRectTracker::resizeInside | CRectTracker::dottedLine;		//初始化橡皮筋类
	m_listPos = 0;
	m_Close = true;		//默认点关闭时就置位为关
}

CBottomFormView::~CBottomFormView()
{
}

void CBottomFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBottomFormView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_COMMAND(ID_DRAW_SAVE, &CBottomFormView::OnFileSave)
END_MESSAGE_MAP()


// CBottomFormView 诊断

#ifdef _DEBUG
void CBottomFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

#endif //_DEBUG


// CBottomFormView 消息处理程序

void CBottomFormView::OnInitialUpdate()		//视图窗口完全建立后第一个被框架调用的函数
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
}


void CBottomFormView::OnDraw(CDC* pDC)
{
	//TODO: 在此添加专用代码 或 调用基类
	CRect rcBottomView(-1,-1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));		//给下半部分纸界面上色
	pDC->FillRect(&rcBottomView, &CBrush(RGB(255, 255, 255)));

	m_scRollpt = GetScrollPosition();
	
	CClientDC dc(this);		//创建dc
	dc.SetViewportOrg(0, 0);
	dc.BitBlt(0, 0, rcBottomView.Width(), rcBottomView.Height(), m_pMDC, m_scRollpt.x, m_scRollpt.y, SRCCOPY);
}

void CBottomFormView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);		//创建设备描述表
	CBrush D_erase(GetBkColor(dc));		//创建橡皮擦
	CBrush D_Brush(m_color);	//创建刷子
	//CRect cwrect;
	//bool IsInRct = false;
	//CRect Trect;          //定义橡皮筋框的矩形
	//CRect Prect;         //图片矩形框
	//CRect AbsRect;
	//int i = 0;

	SetCapture();
	/*画图图形的需要*/
	m_ptOrigin = point;
	m_ptEnd = point;
	m_ptOld = point;
	if (m_PolyCount == 0)
	{
		m_ptPolyFirst = point;
	}

	/*工具文本插入符的需要*/
	switch (m_DrawType)
	{
	case TTEXTINSERT:
		TEXTMETRIC tm;		//定义文本信息结构体变量
		dc.GetTextMetrics(&tm);		//获得设备描述表中的文本信息
		CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);	//根据字体大小，创建合适的插入符
		ShowCaret();
		SetCaretPos(point);
		m_strLine.Empty();
		m_ptTextOrigin = point;
		break;
	case DERASE:		//橡皮
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth +3), (point.y + m_nLineWidth +3)), &D_erase);
		break;
	case DBRUSH:		//刷子
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		break;
	case DPAINTBUC:		//油漆桶
		dc.SelectObject(&D_Brush);
		dc.ExtFloodFill(point.x, point.y, dc.GetPixel(point.x, point.y), FLOODFILLSURFACE);
		break;
	case DSELECT:
		//GetClientRect(&cwrect); //获取窗体中控件的区域
		////ScreenToClient(&cwrect); //转换为相对区域的CRect  
		//if (point.x > cwrect.left && point.y > cwrect.top && point.x)   //确保按下的坐标在控件区域内   
		//{
		//	if (m_rectTracker.HitTest(point) < 0)     //如果未击中矩形选择框,重新画选择框
		//	{
		//		m_rectTracker.TrackRubberBand(this, point, TRUE);
		//		m_rectTracker.m_rect.NormalizeRect();   //正规化矩形（关于正规化矩形下面有介绍）

		//	}
		//	else           //如果击中矩形选择框
		//	{
		//		m_rectTracker.Track(this, point, TRUE);
		//		m_rectTracker.m_rect.NormalizeRect();   //正规化矩形
		//		
		//	}
		//	Invalidate();   //刷新窗口区域，使得CrectTracker对象重绘到窗口上
		//	m_rectTracker.Draw(&dc);
		//}
		//SendMessage(WM_RBUTTONUP, NULL, NULL);
		break;
	default:
		break;
	}
	
	m_BtisDown = true;		//鼠标已按下

	CFormView::OnLButtonDown(nFlags, point);
}


void CBottomFormView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this); //创建dc
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //创建绘制的画笔
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//创建绘制时填充的画刷
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
	}
	CBrush D_erase(GetBkColor(dc)); //创建橡皮擦
	CBrush D_Brush(m_color);	//创建刷子
	dc.SelectObject(&pen); //将画刷和画笔选入设备描述表中
	dc.SelectObject(pbrush);

	ReleaseCapture();

	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&pen); //将画刷和画笔选入设备描述表中
	m_pMDC->SelectObject(pbrush);
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	if (m_BtisDown != true)
	{
		return;
	}

	switch (m_DrawType)
	{
	case DLINE:		//画线
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);		//擦去上一次的线
		dc.SetROP2(R2_COPYPEN);		//缺省绘图模式，像素为画笔颜色
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);		//绘制固定线
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(m_ptOld);		//在内存中备份
		break;
	case DRECT:		//画矩形
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
		dc.SetROP2(R2_COPYPEN);		//缺省绘图模式，像素为画笔颜色
		dc.Rectangle(CRect(m_ptOrigin, point));
		m_pMDC->Rectangle(CRect(m_ptOrigin, m_ptOld));
		break;
	case DELLI:		//画椭圆
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
		dc.SetROP2(R2_COPYPEN);		//缺省绘图模式，像素为画笔颜色
		dc.Ellipse(CRect(m_ptOrigin, point));
		m_pMDC->Ellipse(CRect(m_ptOrigin, m_ptOld));
		break;
	case DCURVE:	//画曲线
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DRRECT:	//画圆角矩形
		dc.RoundRect(CRect(m_ptOrigin, point), CPoint(15, 15));
		m_ptOld = point;
		break;
	case DARC:
		break;
	case DCIRCLE:	//画圆
		if (((point.x>m_ptOrigin.x) && (point.y>m_ptOrigin.y)) || ((point.x<m_ptOrigin.x) && (point.y<m_ptOrigin.y)))
		{
			point.y = m_ptOrigin.y + (point.x - m_ptOrigin.x);
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		else
		{
			point.y = m_ptOrigin.y - (point.x - m_ptOrigin.x);
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		m_ptOld = point;
		break;
	case DPOLY:		//画多边形
		m_arrayP[m_PolyCount++] = point;
		m_ptPolyLast = point;
		if (m_PolyCount > 1)	//点超过1个时，画折线
		{
			dc.Polyline(m_arrayP, m_PolyCount);
			m_pMDC->Polyline(m_arrayP, m_PolyCount);
		}
		break;
	case DERASE:	//画橡皮
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_erase);
		m_pMDC->FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_erase);
		break;
	case DBRUSH:	//画刷子
		dc.FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		m_pMDC->FillRect(CRect((point.x - m_nLineWidth - 3), (point.y - m_nLineWidth - 3),
			(point.x + m_nLineWidth + 3), (point.y + m_nLineWidth + 3)), &D_Brush);
		break;

	default:
		break;
	}
	/*CDC *m_NodeDC = new CDC;
	m_NodeDC = m_pMDC;
	m_listDC.AddHead(m_NodeDC);*/

	/*CGraph *pGraph = new CGraph(m_DrawType, m_ptOrigin, point);	//估计没什么用
	m_ptrArray.Add(pGraph);*/

	m_BtisDown = false;
	//if (m_DrawType >= DLINE && m_DrawType <= DPOLY)
	//{
		
	//}
	
	//CFormView::OnLButtonUp(nFlags, point);
}

void CBottomFormView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	if (pStatus)						//状态栏输出当前鼠标指针的位置
	{
		str.Format(_T("X=%d,Y=%d"), point.x, point.y);
		pStatus->SetWindowTextW(str);
	}

	CClientDC dc(this); //创建dc
	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //创建绘制的画笔
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//创建绘制时填充的画刷
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
	}
	dc.SelectObject(&pen); //将画刷和画笔选入设备描述表中
	CBrush *POldBrush = dc.SelectObject(pbrush);

	CPen D_erase(1, 2*m_nLineWidth+6, GetBkColor(dc)); //创建橡皮擦

	CPen D_Brush(1, 2 * m_nLineWidth + 6, m_color); //创建刷子

	CPen D_LightPen(1, m_nLineWidth + 8, m_color_lightpen/*RGB(255,255,77)*/);	//创建荧光笔
	int OldROP = 0;		//旧的混合模式

	CPen D_BallPen(1, m_nLineWidth + 3, m_color);	//创建圆珠笔

	//CPoint mag_pt(0, 0);
	//GetCursorPos(&mag_pt);//鼠标当前的屏幕位置实现放大器跟随鼠标移动
	//ScreenToClient(&mag_pt);
	//CPoint ptLeftTop(mag_pt.x + OFFSETWIDE, mag_pt.y + OFFSETHIGH);
	//CRect mag_rt;
	//GetClientRect(&mag_rt);
	//CBitmap m_pBitmap;
	//m_pBitmap.CreateCompatibleBitmap(&dc, mag_rt.Width(), mag_rt.Height());
	//CBitmap *pOldBitmap;
	//CPen mag_pen;
	//CPen *mag_pOldPen;
	//int mag_nWidth;

	if (m_BtisDown != true)
	{
		return;
	}

	switch (m_DrawType)
	{
	case DLINE:
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);		//擦去上一次的线
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);		//绘制当前的临时线
		m_ptOld = point;
		break;
	case DRECT:
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
		dc.Rectangle(CRect(m_ptOrigin, point));
		m_ptOld = point;
		break;
	case DELLI:
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
		dc.Ellipse(CRect(m_ptOrigin, point));
		m_ptOld = point;
		break;
	case DCURVE:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DRRECT:
		dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
		dc.RoundRect(CRect(m_ptOrigin, m_ptOld), CPoint(15, 15));
		dc.RoundRect(CRect(m_ptOrigin, point), CPoint(15, 15));
		m_ptOld = point;
		break;
	case DARC:
		break;
	case DCIRCLE:
		if (((point.x>m_ptOrigin.x) && (point.y>m_ptOrigin.y)) || ((point.x<m_ptOrigin.x) && (point.y<m_ptOrigin.y)))
		{
			point.y = m_ptOrigin.y + (point.x - m_ptOrigin.x);
			dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
			dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		else
		{
			point.y = m_ptOrigin.y - (point.x - m_ptOrigin.x);
			dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
			dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
			dc.Ellipse(CRect(m_ptOrigin, point));
		}
		m_ptOld = point;
		break;
	case DPOLY:
		if (m_PolyCount != 0)
		{
			dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);		//这块可能有些问题，闪烁，换成m_ptOld后会多出一条线
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);		//绘制当前的临时线
		}
		else
		{
			dc.SetROP2(R2_NOTXORPEN);		//逆转当前屏幕颜色来画线的绘图方式
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld);		//擦去上一次的线
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);		//绘制当前的临时线
		}
		m_ptOld = point;
		break;
	case DERASE:		//橡皮擦
		dc.SelectObject(&D_erase);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		break;
	case DBRUSH:
		dc.SelectObject(&D_Brush);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		break;
	case DLIGHTPEN:
		OldROP = dc.SetROP2(R2_MASKPEN);
		dc.SelectObject(&D_LightPen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_pMDC->MoveTo(m_ptOrigin);
		m_pMDC->LineTo(point);
		m_ptOrigin = point;
		dc.SetROP2(OldROP);
		break;
	case DPENCIL:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
		break;
	case DBALLPEN:		//圆珠笔
		dc.SelectObject(&D_BallPen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin = point;
	case DMAGNIFY:

		//CXTPWnd *pWnd = new CXTPWnd;
		//m_pMainWnd = pWnd;
		//pWnd->XCreate();
		//return TRUE;

		//ptLeftTop = mag_rt.TopLeft();
		//dc.CreateCompatibleDC(m_pMDC);
		//pOldBitmap = dc.SelectObject(&m_pBitmap);//m_pBitmap保存的当前桌面的位图没有进行阿尔法合成的可以看第一章里有如何获取的或者也可以改成你想要的位图	
		//m_pMDC->StretchBlt(ptLeftTop.x, ptLeftTop.y, MAGNIFIERSIZE * MAGNIFYINGMULTIPLE, MAGNIFIERSIZE * MAGNIFYINGMULTIPLE, &dc,	                 
		//	(mag_pt.x  - MAGNIFIERSIZE / 2), (mag_pt.y  - MAGNIFIERSIZE / 2),	                 
		//	MAGNIFIERSIZE,MAGNIFIERSIZE, SRCCOPY);//拉伸图片达到放大的效果
		//mag_nWidth = MAGNIFIERSIZE * MAGNIFYINGMULTIPLE;	//画中间的十字Begin	
		//
		//mag_pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		//mag_pOldPen = m_pMDC->SelectObject(&mag_pen);
		//m_pMDC->MoveTo(ptLeftTop.x, ptLeftTop.y + mag_nWidth / 2);
		//m_pMDC->LineTo(ptLeftTop.x + mag_nWidth, ptLeftTop.y + mag_nWidth / 2);
		//m_pMDC->MoveTo(ptLeftTop.x + mag_nWidth / 2, ptLeftTop.y);
		//m_pMDC->LineTo(ptLeftTop.x + mag_nWidth / 2, ptLeftTop.y + mag_nWidth);
		//m_pMDC->SelectObject(mag_pOldPen);	//画中间的十字End 	//画边框Begin
		//m_pMDC->SelectStockObject(NULL_BRUSH);
		//m_pMDC->Rectangle(ptLeftTop.x, ptLeftTop.y, ptLeftTop.x + mag_nWidth, ptLeftTop.y + mag_nWidth);	//画边框End 		
		//
		//dc.SelectObject(pOldBitmap);	
		//dc.DeleteDC();

	default:
		break;
	}
	
	CFormView::OnMouseMove(nFlags, point);
}

void CBottomFormView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this); //创建dc
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //创建绘制的画笔
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//创建绘制时填充的画刷
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
	}
	dc.SelectObject(&pen); //将画刷和画笔选入设备描述表中
	dc.SelectObject(pbrush);
	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&pen);		//将画刷和画笔选入内存中
	m_pMDC->SelectObject(pbrush);
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	switch (m_DrawType)
	{
	case DPOLY:
		if (m_PolyCount != 0)
		{
			dc.MoveTo(m_ptPolyLast);
			dc.LineTo(point);
			dc.MoveTo(point);
			dc.LineTo(m_ptPolyFirst);
			m_pMDC->MoveTo(m_ptPolyLast);
			m_pMDC->LineTo(point);
			m_pMDC->MoveTo(point);
			m_pMDC->LineTo(m_ptPolyFirst);
			m_PolyCount = 0;
		}
		break;
	default:
		break;
	}

	CFormView::OnRButtonUp(nFlags, point);
}


void CBottomFormView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)		//输入字符
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_color); //创建绘制的画笔
	CBrush *pbrush = new CBrush();
	if (m_flagFullPaint == true)
	{
		pbrush->CreateSolidBrush(m_color);		//创建绘制时填充的画刷
	}
	else
	{
		pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
	}

	if (!m_pMDC->m_hDC)
	{
		m_pMDC->CreateCompatibleDC(&dc);
		m_pMDC->SetViewportOrg(-m_scRollpt);
	}
	CRect rect;
	CBitmap bitmap;
	GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pMDC->SelectObject(&bitmap);
	m_pMDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	CFont *pOldFont = dc.SelectObject(&m_font);
	m_pMDC->SelectObject(&m_font);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	dc.SetTextColor(m_color);
	m_pMDC->SetTextColor(m_color);
	if (0x0d == nChar)			//回车键为0x0d
	{
		m_strLine.Empty();
		m_ptTextOrigin.y += tm.tmHeight;
		/*m_strLine += "\r\n";*/
	}
	else if(0x08 == nChar)		//退格键为0x08
	{
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());	//将要删除的字符颜色设置为画板背景色,返回原来的色
		dc.TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);
		m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);		//返回指定值的靠左侧字符串
		dc.SetTextColor(clr);	
	}
	else
	{
		m_strLine += (char)nChar;
	}

	CSize sz = dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptTextOrigin.x + sz.cx;
	pt.y = m_ptTextOrigin.y;
	SetCaretPos(pt);
	dc.TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);
	m_pMDC->TextOutW(m_ptTextOrigin.x, m_ptTextOrigin.y, m_strLine);

	dc.SelectObject(pOldFont);

	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

void CBottomFormView::OnFileSave()		//保存文件
{
	// TODO: 在此添加命令处理程序代码
	m_Close = true;	//表示要关闭
	CClientDC dc(this);
	CRect rect;
	BOOL  showMsgTag;                  //是否要弹出”图像保存成功对话框"     
	GetClientRect(&rect);                  //获取画布大小    
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.Width(), rect.Height());       //创建兼容位图  

	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式    
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);  //将位图选入DC，并保存返回值   

	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);        //将屏幕DC的图像复制到内存DC中    

	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像     

	showMsgTag = TRUE;
	CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png | 其他格式*.*) | *.* || ");  

	CFileDialog dlg(FALSE, _T("bmp"), _T("test.bmp"), NULL, strFilter);

	if (dlg.DoModal() != IDOK)
	{
		m_Close = false;		//表示不关闭
		return;
	}
	CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个  

	CString strExtension;

	strFileName = dlg.m_ofn.lpstrFile;

	if (dlg.m_ofn.nFileExtension = 0)               //扩展名项目为0    
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
			case 1:
				strExtension = "bmp"; break;
			case 2:
				strExtension = "jpg"; break;
			case 3:
				strExtension = "gif"; break;
			case 4:
				strExtension = "png"; break;
			default:
				break;
		}
		strFileName = strFileName + "." + strExtension;
	}
	HRESULT hResult = image.Save(strFileName);     //保存图像    
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"), strFileName);
	}
	else
	{
		if (showMsgTag)
			MessageBox(_T("文件保存成功！"), strFileName);
	}
	image.Detach();
	SelectObject(hdc, hOldMap);
}