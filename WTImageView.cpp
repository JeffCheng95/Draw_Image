
// WTImageView.cpp : CWTImageView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WTImage.h"
#endif

#include "WTImageDoc.h"
#include "WTImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWTImageView

IMPLEMENT_DYNCREATE(CWTImageView, CView)

BEGIN_MESSAGE_MAP(CWTImageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWTImageView 构造/析构

CWTImageView::CWTImageView()
{
	// TODO: 在此处添加构造代码

}

CWTImageView::~CWTImageView()
{
}

BOOL CWTImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CWTImageView 绘制

void CWTImageView::OnDraw(CDC* /*pDC*/)
{
	CWTImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CWTImageView 打印

BOOL CWTImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CWTImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CWTImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CWTImageView 诊断

#ifdef _DEBUG
void CWTImageView::AssertValid() const
{
	CView::AssertValid();
}

void CWTImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWTImageDoc* CWTImageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWTImageDoc)));
	return (CWTImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CWTImageView 消息处理程序
