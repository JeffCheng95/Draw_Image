// TopFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "WTImage.h"
#include "TopFormView.h"
#include "BottomFormView.h"
#include <windows.h>

extern CBottomFormView *pBottomFormView;		//声明指向CBottom类的指针

DWORD WINAPI GetImageThread(LPVOID lpParam);

// CTopFormView

IMPLEMENT_DYNCREATE(CTopFormView, CFormView)

CTopFormView::CTopFormView()
	: CFormView(IDD_TOPFORMVIEW)
{
	m_imageW = 120;
	m_imageH = 90;
}

CTopFormView::~CTopFormView()
{
}

void CTopFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTopFormView, CFormView)
	ON_COMMAND(ID_SHOWPIC, &CTopFormView::OnShowpic)
END_MESSAGE_MAP()


// CTopFormView 诊断

#ifdef _DEBUG
void CTopFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopFormView 消息处理程序

int CTopFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect;
	GetClientRect(&rect);
	//动态创建listctrl控件 LVS_AUTOARRANGE设置后图标可随窗口大小的变化自动排列
	m_listCtrl.Create(LVS_SINGLESEL | LVS_ICON | WS_CHILD | WS_VISIBLE | LVS_SINGLESEL | LVS_AUTOARRANGE, CRect(rect), this, IDD_TOPFORMVIEW);
	InitListCtrl();
	return 0;
}

void CTopFormView::InitListCtrl()//ListCtrl与imagelist的初始化
{

	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);  //初始化GDI+
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置当前的列表视图控件扩展的样式
	m_listCtrl.SetIconSpacing(CSize(140, 130));     //设置图片间距
													//设置缩略图大小，宽120 高90
	m_imageW = 120;
	m_imageH = 90;
	m_imageList.Create(m_imageW, m_imageH, ILC_COLORDDB | ILC_COLOR32, 1, 1);     //wide of picture is 120,height is 90
	m_listCtrl.SetImageList(&m_imageList, LVSIL_NORMAL);     //CImageList associates CListCtrl//LVSIL_NORMAL:大图标方式进行图像列表，LVSIL_SMALL为小图标，LVSIL_STATE 以图像状态进行图像列表
															 //UpdateImageList();
}

void CTopFormView::OnShowpic()
{
	// TODO: 在此添加命令处理程序代码
	DWORD  dwID;
	//CreateThread在主线程的基础上创建一个新线程。否则图片无法实时显示
	m_handle = CreateThread(NULL, 0, GetImageThread, this, 0, &dwID);
}


DWORD WINAPI GetImageThread(LPVOID lpParam)
{
	CTopFormView *pPicListDlg = (CTopFormView*)lpParam;
	pPicListDlg->UpdateImageList();
	return 1;
}
void CTopFormView::UpdateImageList()
{
	CString imagename;
	int a = 1, i = 0;
	//while(a<=7)
	while (i<3)
	{
		a = i % 7 + 1;//用于循环输出图像，为方便输出，此处在image文件下存的图片都是1.jpg,2.jpg一直到7.jpg的名称
		imagename.Format(_T("D:\\%d.jpg"), a);
		TCHAR* imagename_t = new TCHAR[50];
		imagename_t = imagename.GetBuffer(imagename.GetLength());//cstring convert to tchar*
		imagename.ReleaseBuffer();
		insertImageItem(imagename_t);
		Sleep(300);
		i++;
	}
}
bool  CTopFormView::insertImageItem(TCHAR* path)
{
	Bitmap bmp(path);                     //传入图片路径

	int sourceWidth = m_imageW;           //获得图片宽度,这个120和创建的120保持相同。
	int sourceHeight = bmp.GetHeight();   //获得图片宽度     
	if (sourceHeight>m_imageH)             //和m_ImageList.Create(120…)有很大关系，如果小于设
	{
		sourceHeight = m_imageH;           //定的宽度，图片将无法显示
	}


	Bitmap* pThumbnail = static_cast<Bitmap*>(bmp.GetThumbnailImage(sourceWidth, sourceHeight, NULL, NULL)); //设定缩略图的大小
	HBITMAP hBmp = NULL;
	pThumbnail->GetHBITMAP(Color(255, 255, 255), &hBmp);
	CBitmap *pImage = CBitmap::FromHandle(hBmp);         //转换成CBitmap格式位图
	if (hBmp == NULL)
	{
		AfxMessageBox(L"载入为空");
	}
	/*CBitmap *pImage = new CBitmap;
	pImage->Attach(hBmp);*/


	TCHAR drive[MAX_PATH] = _T("");
	TCHAR dir[MAX_PATH] = _T("");
	TCHAR fname[MAX_PATH] = _T("");
	TCHAR ext[MAX_PATH] = _T("");

	_wsplitpath_s(path, drive, dir, fname, ext);
	drive[MAX_PATH - 1] = '\0';
	dir[MAX_PATH - 1] = '\0';
	fname[MAX_PATH - 1] = '\0';
	ext[MAX_PATH - 1] = '\0';
	CString itemName(fname);
	itemName.Append(ext);

	int index = m_imageList.Add(pImage, RGB(255, 255, 255));
	m_listCtrl.InsertItem(index, itemName, index);               // itemName名字会显示在图片下
	return true;
}




