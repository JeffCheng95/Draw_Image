#pragma once


// CMagnifyDlg 对话框

class CMagnifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMagnifyDlg)

public:
	CMagnifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMagnifyDlg();
	afx_msg void OnPaint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MAGNIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
public:
	CRect m_rect;
	int m_fMultiple;
	bool bcatch;

	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
