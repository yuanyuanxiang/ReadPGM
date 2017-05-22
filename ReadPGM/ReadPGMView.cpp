
// ReadPGMView.cpp : CReadPGMView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ReadPGM.h"
#endif

#include "ReadPGMDoc.h"
#include "ReadPGMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadPGMView

IMPLEMENT_DYNCREATE(CReadPGMView, CView)

BEGIN_MESSAGE_MAP(CReadPGMView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CReadPGMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CReadPGMView 构造/析构

CReadPGMView::CReadPGMView()
{
	// TODO: 在此处添加构造代码

}

CReadPGMView::~CReadPGMView()
{
}

BOOL CReadPGMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CReadPGMView 绘制

void CReadPGMView::OnDraw(CDC* pDC)
{
	CReadPGMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->m_pImage) return ;
	else pDoc->m_pImage->Draw(pDC->GetSafeHdc(), CRect(0, 0, pDoc->m_pImage->GetWidth(), pDoc->m_pImage->GetHeight()));
}


// CReadPGMView 打印


void CReadPGMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CReadPGMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CReadPGMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CReadPGMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CReadPGMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CReadPGMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CReadPGMView 诊断

#ifdef _DEBUG
void CReadPGMView::AssertValid() const
{
	CView::AssertValid();
}

void CReadPGMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReadPGMDoc* CReadPGMView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReadPGMDoc)));
	return (CReadPGMDoc*)m_pDocument;
}
#endif //_DEBUG


// CReadPGMView 消息处理程序
