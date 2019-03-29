#pragma once



// CTopFormView 窗体视图

class CTopFormView : public CFormView
{
	DECLARE_DYNCREATE(CTopFormView)

protected:
	CTopFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTopFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOPFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
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

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void InitListCtrl();
private:
	CListCtrl     m_listCtrl;
	CImageList    m_imageList;
	short         m_imageW;
	short         m_imageH;
	HANDLE        m_handle;                        //循环插入图片线程的句柄
	GdiplusStartupInput   m_gdiplusStartupInput;   //只需要在程序运行最开始初始化一次
	ULONG_PTR             m_gdiplusToken;          //只需要在程序运行最开始初始化一次
private:
	bool  insertImageItem(TCHAR* path);
public:
	void UpdateImageList();
	afx_msg void OnShowpic();
};





