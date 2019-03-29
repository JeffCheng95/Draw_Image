// MagnifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WTImage.h"
#include "MagnifyDlg.h"
#include "afxdialogex.h"


// CMagnifyDlg 对话框

IMPLEMENT_DYNAMIC(CMagnifyDlg, CDialogEx)

CMagnifyDlg::CMagnifyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MAGNIFY, pParent)
{
	m_fMultiple = 2;
	bcatch = true;
}

CMagnifyDlg::~CMagnifyDlg()
{
}

void CMagnifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

int CMagnifyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 35, NULL);
	return 0;
}


BEGIN_MESSAGE_MAP(CMagnifyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMagnifyDlg 消息处理程序

void CMagnifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
						   // TODO: 在此处添加消息处理程序代码
						   // 不为绘图消息调用 CDialogEx::OnPaint()
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	GetClientRect(m_rect);
	int cx = m_rect.Width();
	int cy = m_rect.Height();
	int nCx = GetSystemMetrics(SM_CXSCREEN);
	int nCy = GetSystemMetrics(SM_CYSCREEN);
	static bool first = true;
	if (first)
	{
		::SetWindowPos(m_hWnd, HWND_TOPMOST, nCx/2 - cx/2, nCy/2 - cy/2, 0, 0, SWP_NOSIZE);
		first = false;
	}

	if (IsWindowVisible())
	{
		POINT pt;
		::GetCursorPos(&pt);
		HDC hDesktopDC = ::GetDC(NULL);
		HDC hDC = ::GetDC(m_hWnd);


		CRect ImgRect;
		CRect DlgRect = m_rect;
		int bs = 2 * m_fMultiple;
		ImgRect.left = int(pt.x - (float)m_rect.Width() / 2 / m_fMultiple);
		ImgRect.top = int(pt.y - (float)m_rect.Height() / 2 / m_fMultiple);
		ImgRect.right = int(pt.x + (float)m_rect.Width() / 2 / m_fMultiple);
		ImgRect.bottom = int(pt.y + (float)m_rect.Height() / 2 / m_fMultiple);
		//处理不可见部分
		if (ImgRect.left<0)
		{
			ImgRect.left = 0;
		}
		if (ImgRect.top<0)
		{
			ImgRect.top = 0;
		}
		if (ImgRect.right>nCx)
		{
			ImgRect.right = nCx;
		}
		if (ImgRect.bottom>nCy)
		{
			ImgRect.bottom = nCy;
		}
		if (DlgRect.left<0)
		{
			DlgRect.left = 0;
		}
		if (DlgRect.top<0)
		{
			DlgRect.top = 0;
		}
		if (DlgRect.right>nCx)
		{
			DlgRect.right = nCx;
		}
		if (DlgRect.bottom>nCy)
		{
			DlgRect.bottom = nCy;
		}
		::SetStretchBltMode(hDC, COLORONCOLOR);
		::StretchBlt(hDC, DlgRect.left, DlgRect.top, DlgRect.Width(), DlgRect.Height(),
			hDesktopDC, ImgRect.left, ImgRect.top, ImgRect.Width(), ImgRect.Height(), SRCCOPY);
		::ReleaseDC(m_hWnd, hDesktopDC);
		::ReleaseDC(m_hWnd, hDC);
	}
}


HCURSOR CMagnifyDlg::OnQueryDragIcon()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return static_cast<HCURSOR>(m_hIcon);
}


void CMagnifyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}



