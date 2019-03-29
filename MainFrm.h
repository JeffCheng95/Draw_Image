
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);//分割视图响应菜单消息

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	

public:
	CStatusBar        m_wndStatusBar;
	CToolBar          m_wndToolBar;
	CToolBar          m_shapeToolBar;		//绘制图形的工具栏
	CToolBar          m_penStyleToolBar;	//使用的笔型
	CToolBar		  m_lineTypeColorToolBar;	//线规格和颜色
	CToolBar		  m_packetToolBar;		//使用的工具包工具栏，如放大镜等
	CSplitterWnd      m_splitWnd;

	enum SBID { prompt, xName, xVal, yName, yVal };
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

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDline();
	afx_msg void OnDcurve();
	afx_msg void OnDrect();
	afx_msg void OnDround();
	afx_msg void OnDrrect();
	afx_msg void OnDarc();
	afx_msg void OnDellip();
	afx_msg void OnDpoly();
	afx_msg void OnLineWidthSetting();
	afx_msg void OnColor();
	afx_msg void OnFont();
	afx_msg void OnViewShapetool();
	afx_msg void OnUpdateViewShapetool(CCmdUI *pCmdUI);
	afx_msg void OnViewPenstyletoolbar();
	afx_msg void OnUpdateViewPenstyletoolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewSizeTypeColor();
	afx_msg void OnUpdateViewSizeTypeColor(CCmdUI *pCmdUI);
	afx_msg void OnViewPacketToolbar();
	afx_msg void OnUpdateViewPacketToolbar(CCmdUI *pCmdUI);
	afx_msg void OnAddText();
	afx_msg void OnEarser();
	afx_msg void OnBrush();
	afx_msg void OnFullPaint();
	afx_msg void OnPaintBucket();
	afx_msg void OnUpdateFullPaint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDcurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrrect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDarc(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDround(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDellip(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDpoly(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAddText(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEarser(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrush(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaintBucket(CCmdUI *pCmdUI);
	afx_msg void OnDselect();
	afx_msg void OnMagnify();
	afx_msg void OnLightpen();
	afx_msg void OnPencil();
	afx_msg void OnUpdateLightpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePencil(CCmdUI *pCmdUI);
	afx_msg void OnBallpen();
	afx_msg void OnBrushpen();
	afx_msg void OnUpdateBallpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushpen(CCmdUI *pCmdUI);


	afx_msg void OnUndo();
	afx_msg void OnPaint();
	afx_msg void OnClose();
};




