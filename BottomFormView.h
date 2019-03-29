#pragma once


// CBottomFormView 窗体视图

class CBottomFormView : public CFormView
{
	DECLARE_DYNCREATE(CBottomFormView)

protected:
	CBottomFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBottomFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOTTOMFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:		//私有成员变量
	CPtrArray m_ptrArray;
	


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnDraw(CDC* pDC);		//重写OnDraw()函数
	virtual void OnInitialUpdate();

protected:		//控件相关成员变量

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileSave();

public:		//公用成员变量
	enum DTYPE		//画图形类型
	{
		DLINE,		//画线
		DCURVE,		//画曲线
		DRECT,		//画矩形
		DRRECT,		//画圆角矩形
		DARC,		//画圆弧
		DELLI,		//画椭圆
		DCIRCLE,	//画圆
		DPOLY,		//画多边形
		TTEXTINSERT,	//文本插入符
		DERASE,		//画图的橡皮擦
		DBRUSH,		//画图的刷子
		DPAINTBUC,		//画图的油漆桶
		DSELECT,	//选择框
		DMAGNIFY,	//放大镜
		DLIGHTPEN,	//荧光笔
		DPENCIL,	//铅笔
		DBALLPEN,	//圆珠笔
		DBRUSHPEN,	//毛笔
	};

	int m_DrawType;		//画图形类型
	CPoint m_ptOrigin;		//起始点坐标
	CPoint m_ptEnd;			//终点坐标
	CPoint m_ptOld;			//上一次的旧点
	bool m_BtisDown;		//按键是否按下
	CDC *m_pMDC;			//存于内存中的设备环境对象（DC对象）
	UINT m_nLineWidth;		// 线宽的设置
	int  m_nLineStyle;		//线型：实线、虚线、点线
	COLORREF m_color;		//选择的颜色
	COLORREF m_color_lightpen;	//荧光笔的颜色
	CFont m_font;			//选择的字体
	CString m_strFontName;	//显示选择的字体
	CPoint m_ptPolyFirst;	//折线图中的第一个点
	CPoint m_ptPolyLast;	//折线图中最后点
	CPoint m_arrayP[255];	//存储折线图中所有点
	int m_PolyCount;		//折线的点的计数
	CString m_strLine;		//插入字符时的字符串
	CPoint m_ptTextOrigin;
	bool m_flagFullPaint;	//颜色填充按钮的按下抬起状态标识
	CRectTracker m_rectTracker;		//橡皮筋类对象
	CList<CDC*, CDC*&> m_listDC;		//位图存入链表
	int m_listPos;		//链表的位置
	CPoint m_scRollpt;		//滚动条（视图位移点）
	bool m_Close;		//是否要关闭文件

};




