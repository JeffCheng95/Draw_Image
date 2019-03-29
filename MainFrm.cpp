
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "WTImage.h"

#include "MainFrm.h"

#include "TopFormView.h"
#include "BottomFormView.h"
#include "SettingDlg.h"
#include "WTImageDoc.h"
#include "MagnifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
extern CBottomFormView *pBottomFormView;		//声明指向CBottom类的指针

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DLINE, &CMainFrame::OnDline)
	ON_COMMAND(ID_DCURVE, &CMainFrame::OnDcurve)
	ON_COMMAND(ID_DRECT, &CMainFrame::OnDrect)
	ON_COMMAND(ID_DROUND, &CMainFrame::OnDround)
	ON_COMMAND(ID_DRRECT, &CMainFrame::OnDrrect)
	ON_COMMAND(ID_DARC, &CMainFrame::OnDarc)
	ON_COMMAND(ID_DELLIP, &CMainFrame::OnDellip)
	ON_COMMAND(ID_DPOLY, &CMainFrame::OnDpoly)
	ON_COMMAND(ID_LINE_WIDTH_SETTING, &CMainFrame::OnLineWidthSetting)
	ON_COMMAND(ID_COLOR, &CMainFrame::OnColor)
	ON_COMMAND(IDM_FONT, &CMainFrame::OnFont)
	ON_COMMAND(ID_VIEW_SHAPETOOL, &CMainFrame::OnViewShapetool)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHAPETOOL, &CMainFrame::OnUpdateViewShapetool)
	ON_COMMAND(ID_VIEW_PENSTYLETOOLBAR, &CMainFrame::OnViewPenstyletoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PENSTYLETOOLBAR, &CMainFrame::OnUpdateViewPenstyletoolbar)
	ON_COMMAND(ID_VIEW_SIZE_TYPE_COLOR, &CMainFrame::OnViewSizeTypeColor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZE_TYPE_COLOR, &CMainFrame::OnUpdateViewSizeTypeColor)
	ON_COMMAND(ID_VIEW_PACKET_TOOLBAR, &CMainFrame::OnViewPacketToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PACKET_TOOLBAR, &CMainFrame::OnUpdateViewPacketToolbar)
	ON_COMMAND(IDM_ADD_TEXT, &CMainFrame::OnAddText)
	ON_COMMAND(IDM_EARSER, &CMainFrame::OnEarser)
	ON_COMMAND(IDM_BRUSH, &CMainFrame::OnBrush)
	ON_COMMAND(IDM_FULL_PAINT, &CMainFrame::OnFullPaint)
	ON_COMMAND(IDM_PAINT_BUCKET, &CMainFrame::OnPaintBucket)
	ON_UPDATE_COMMAND_UI(IDM_FULL_PAINT, &CMainFrame::OnUpdateFullPaint)
	ON_UPDATE_COMMAND_UI(ID_DLINE, &CMainFrame::OnUpdateDline)
	ON_UPDATE_COMMAND_UI(ID_DCURVE, &CMainFrame::OnUpdateDcurve)
	ON_UPDATE_COMMAND_UI(ID_DRECT, &CMainFrame::OnUpdateDrect)
	ON_UPDATE_COMMAND_UI(ID_DRRECT, &CMainFrame::OnUpdateDrrect)
	ON_UPDATE_COMMAND_UI(ID_DARC, &CMainFrame::OnUpdateDarc)
	ON_UPDATE_COMMAND_UI(ID_DROUND, &CMainFrame::OnUpdateDround)
	ON_UPDATE_COMMAND_UI(ID_DELLIP, &CMainFrame::OnUpdateDellip)
	ON_UPDATE_COMMAND_UI(ID_DPOLY, &CMainFrame::OnUpdateDpoly)
	ON_UPDATE_COMMAND_UI(IDM_ADD_TEXT, &CMainFrame::OnUpdateAddText)
	ON_UPDATE_COMMAND_UI(IDM_EARSER, &CMainFrame::OnUpdateEarser)
	ON_UPDATE_COMMAND_UI(IDM_BRUSH, &CMainFrame::OnUpdateBrush)
	ON_UPDATE_COMMAND_UI(IDM_PAINT_BUCKET, &CMainFrame::OnUpdatePaintBucket)
	ON_COMMAND(ID_DSELECT, &CMainFrame::OnDselect)
	ON_COMMAND(IDM_MAGNIFY, &CMainFrame::OnMagnify)
	ON_COMMAND(ID_LIGHTPEN, &CMainFrame::OnLightpen)
	ON_COMMAND(ID_PENCIL, &CMainFrame::OnPencil)
	ON_UPDATE_COMMAND_UI(ID_LIGHTPEN, &CMainFrame::OnUpdateLightpen)
	ON_UPDATE_COMMAND_UI(ID_PENCIL, &CMainFrame::OnUpdatePencil)
	ON_COMMAND(ID_BALLPEN, &CMainFrame::OnBallpen)
	ON_COMMAND(ID_BRUSHPEN, &CMainFrame::OnBrushpen)
	ON_UPDATE_COMMAND_UI(ID_BALLPEN, &CMainFrame::OnUpdateBallpen)
	ON_UPDATE_COMMAND_UI(ID_BRUSHPEN, &CMainFrame::OnUpdateBrushpen)
	ON_COMMAND(ID_UNDO, &CMainFrame::OnUndo)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	//// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_shapeToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_shapeToolBar.LoadToolBar(IDR_SHAPETOOL))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_shapeToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_shapeToolBar);
	

	if (!m_penStyleToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_penStyleToolBar.LoadToolBar(IDR_PENSTYLE))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_penStyleToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_penStyleToolBar);

	if (!m_lineTypeColorToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_lineTypeColorToolBar.LoadToolBar(IDR_SIZE_TYPE_COLOR))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_lineTypeColorToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_lineTypeColorToolBar);

	if (!m_packetToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_packetToolBar.LoadToolBar(IDR_PACKET_TOOLBAR))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_packetToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_packetToolBar);

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	RecalcLayout();		//重新布局，以下代码使多个工具栏停靠在一行。
	CRect rect;
	m_wndToolBar.GetWindowRect(rect);
	rect.OffsetRect(1, 0);//偏移一个位置
	DockControlBar(&m_shapeToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(2, 0);//偏移2个位置
	DockControlBar(&m_penStyleToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(3, 0);//偏移3个位置
	DockControlBar(&m_lineTypeColorToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(4, 0);//偏移4个位置
	DockControlBar(&m_packetToolBar, AFX_IDW_DOCKBAR_TOP, rect);

	//m_wndToolBar.m_pDockBar = NULL;//禁止工具条浮动
	//m_shapeToolBar.m_pDockBar = NULL;//禁止工具条浮动
	//m_penStyleToolBar.m_pDockBar = NULL;//禁止工具条浮动
	//m_lineTypeColorToolBar.m_pDockBar = NULL;//禁止工具条浮动
	//m_packetToolBar.m_pDockBar = NULL;//禁止工具条浮动

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL bFlag = m_splitWnd.CreateStatic(this, 2, 1);
	if (bFlag)
	{
		CSize sz(0, 0);
		m_splitWnd.CreateView(0, 0, RUNTIME_CLASS(CTopFormView), sz, pContext);			//上半部分框用来显示绘图选项，比如线型、线宽、颜色等
		m_splitWnd.CreateView(1, 0, RUNTIME_CLASS(CBottomFormView), sz, pContext);		//下半部分用来绘图 
	}
	return bFlag;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
	//DockControlBar(&m_wndToolBar);

	//DockControlBar(&m_shapeToolBar);

	//DockControlBar(&m_penStyleToolBar);

	//DockControlBar(&m_lineTypeColorToolBar);

	//DockControlBar(&m_packetToolBar);

	RecalcLayout();		//重新布局，以下代码使多个工具栏停靠在一行。
	CRect rect;
	m_wndToolBar.GetWindowRect(rect);
	rect.OffsetRect(256, 0);//偏移一个位置
	DockControlBar(&m_shapeToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(123, 0);//偏移2个位置
	DockControlBar(&m_penStyleToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(102, 0);//偏移3个位置
	DockControlBar(&m_lineTypeColorToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	rect.OffsetRect(77, 0);//偏移4个位置
	DockControlBar(&m_packetToolBar, AFX_IDW_DOCKBAR_TOP, rect);
	//rect.OffsetRect(176, 0);//偏移5个位置
}

void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	int IsSave = MessageBox(_T("是否保存"), _T("Warning"), MB_YESNOCANCEL);
	if (IsSave == IDCANCEL)
	{
		return;
	}
	if (IsSave == IDYES)
	{
		pBottomFormView->OnFileSave();
	}
	if (IsSave == IDNO || pBottomFormView->m_Close)		//为了控制文件保存框中点击取消(此时m_Close置为false)后不会直接退出程序
	{
		CFrameWnd::OnClose();
	}
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

//重载OnCmdMsg 使得分割视图中，每个view能够接收到菜单响应消息
//先调用缺省函数，如果命令没有被处理(缺省的OnCmdMsg返回FALSE)，则获取当前所有视图指针，调用每个视图的OnCmdMsg函数,将命令消息传送给每个视图。
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{	if ( CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) )		
		return TRUE;	
	CWTImageDoc* pDoc = (CWTImageDoc* ) GetActiveDocument ();
	POSITION pos = NULL;	
	if ( pDoc != NULL )	
		pos = pDoc->GetFirstViewPosition ();
	while ( pos != NULL )	
	{		
		CView* pNextView = pDoc->GetNextView ( pos );	
		if ( pNextView != GetActiveView() )		
		{			
			if ( pNextView->OnCmdMsg ( nID, nCode, pExtra, pHandlerInfo ) )		
				return TRUE;	
		}	
	} 	
	return FALSE;
}


void CMainFrame::OnDline()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DLINE;		//图形是线段
}


void CMainFrame::OnDcurve()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DCURVE;		//图形是曲线
}


void CMainFrame::OnDrect()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DRECT;		//图形是矩形
}

void CMainFrame::OnDrrect()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DRRECT;		//图形是圆角矩形
}

void CMainFrame::OnDarc()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DARC;		//图形是圆弧
}

void CMainFrame::OnDround()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DCIRCLE;		//图形是圆形
}

void CMainFrame::OnDellip()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DELLI;		//图形是椭圆
}

void CMainFrame::OnDpoly()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DPOLY;		//图形是多边形
}

void CMainFrame::OnLineWidthSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;
	dlg.m_nLineWidth = pBottomFormView->m_nLineWidth;
	dlg.m_nLineStyle = pBottomFormView->m_nLineStyle;
	if (IDOK == dlg.DoModal())
	{
		pBottomFormView->m_nLineWidth = dlg.m_nLineWidth;
		pBottomFormView->m_nLineStyle = dlg.m_nLineStyle;
	}

}

void CMainFrame::OnColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult = pBottomFormView->m_color;
	if (IDOK == dlg.DoModal())
	{
		pBottomFormView->m_color = dlg.m_cc.rgbResult;
	}

}

void CMainFrame::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		if (pBottomFormView->m_font.m_hObject)
		{
			pBottomFormView->m_font.DeleteObject();
		}
		pBottomFormView->m_font.CreateFontIndirectW(dlg.m_cf.lpLogFont);	//用所选字体初始化m_font对象
		pBottomFormView->m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;	//保存字体名
	}
}

void CMainFrame::OnAddText()
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = TTEXTINSERT;	//文本插入符
}

void CMainFrame::OnEarser()		//橡皮擦
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DERASE;
}

void CMainFrame::OnBrush()		//刷子
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DBRUSH;
}

void CMainFrame::OnLightpen()		//荧光笔
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DLIGHTPEN;
}

void CMainFrame::OnPencil()		//铅笔
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DPENCIL;
}

void CMainFrame::OnBallpen()	//圆珠笔
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DBALLPEN;
}


void CMainFrame::OnBrushpen()	//毛笔
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DBRUSHPEN;
}



void CMainFrame::OnPaintBucket()	//油漆桶
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DPAINTBUC;
}

void CMainFrame::OnFullPaint()		//颜色填充
{
	// TODO: 在此添加命令处理程序代码
	if (pBottomFormView->m_flagFullPaint == false)
	{
		pBottomFormView->m_flagFullPaint = true;		//按钮按下状态，表明是填充状态
	}
	else
	{
		pBottomFormView->m_flagFullPaint = false;
	}
}


void CMainFrame::OnDselect()	//选择框
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DSELECT;
}

void CMainFrame::OnMagnify()	//放大镜
{
	// TODO: 在此添加命令处理程序代码
	pBottomFormView->m_DrawType = DMAGNIFY;
	CMagnifyDlg magDlg;
	magDlg.DoModal();
	//CWnd *pChWnd = new CWnd;
	//pChWnd->CreateEx(0,//WS_EX_TOPMOST,
	//	AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
	//	(LPCTSTR)"Magnify",
	//	WS_POPUP,//|WS_BORDER,//WS_OVERLAPPEDWINDOW,
	//	0, 0, 300, 180,
	//	m_splitWnd,
	//	NULL,
	//	NULL);
	//pChWnd->CenterWindow();
	//pChWnd->ShowWindow(SW_SHOW);
}





void CMainFrame::OnViewShapetool()
{
	// TODO: 在此添加命令处理程序代码
	if (m_shapeToolBar.IsWindowVisible())
	{
		m_shapeToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_shapeToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_shapeToolBar);
}


void CMainFrame::OnUpdateViewShapetool(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_shapeToolBar.IsWindowVisible());
}


void CMainFrame::OnViewPenstyletoolbar()
{
	// TODO: 在此添加命令处理程序代码
	if (m_penStyleToolBar.IsWindowVisible())
	{
		m_penStyleToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_penStyleToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_penStyleToolBar);
}


void CMainFrame::OnUpdateViewPenstyletoolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_penStyleToolBar.IsWindowVisible());
}


void CMainFrame::OnViewSizeTypeColor()		//设置线型线宽颜色的工具栏，在视图中选择显示或不显示
{
	// TODO: 在此添加命令处理程序代码
	if (m_lineTypeColorToolBar.IsWindowVisible())
	{
		m_lineTypeColorToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_lineTypeColorToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_lineTypeColorToolBar);
}


void CMainFrame::OnUpdateViewSizeTypeColor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_lineTypeColorToolBar.IsWindowVisible());
}

void CMainFrame::OnViewPacketToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if (m_packetToolBar.IsWindowVisible())
	{
		m_packetToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_packetToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_packetToolBar);
}

void CMainFrame::OnUpdateViewPacketToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_packetToolBar.IsWindowVisible());
}


void CMainFrame::OnUpdateFullPaint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DRECT || pBottomFormView->m_DrawType == DELLI ||
		pBottomFormView->m_DrawType == DRRECT || pBottomFormView->m_DrawType == DCIRCLE ||
		pBottomFormView->m_DrawType == DPOLY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}

	if (pBottomFormView->m_flagFullPaint == false)		//按钮按下抬起状态
	{
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(TRUE);
	}
}


void CMainFrame::OnUpdateDline(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DLINE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateDcurve(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DCURVE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDrect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DRECT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDrrect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DRRECT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDarc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DARC)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDround(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DCIRCLE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDellip(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DELLI)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateDpoly(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DPOLY)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateAddText(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == TTEXTINSERT)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateEarser(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DERASE)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBrush(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DBRUSH)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdatePaintBucket(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DPAINTBUC)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateLightpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DLIGHTPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdatePencil(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DPENCIL)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBallpen(CCmdUI *pCmdUI)	//圆珠笔的按下抬起状态
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DBALLPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateBrushpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (pBottomFormView->m_DrawType == DBRUSHPEN)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}



void CMainFrame::OnUndo()
{
	// TODO: 在此添加命令处理程序代码
	
	if (pBottomFormView->m_listPos != 0)
	{
		pBottomFormView->m_pMDC = pBottomFormView->m_listDC.GetAt(pBottomFormView->m_listDC.FindIndex(2));
		pBottomFormView->m_listPos++;
	}
	Invalidate();
}
