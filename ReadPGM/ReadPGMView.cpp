
// ReadPGMView.cpp : CReadPGMView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CReadPGMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CReadPGMView ����/����

CReadPGMView::CReadPGMView()
{
	// TODO: �ڴ˴���ӹ������

}

CReadPGMView::~CReadPGMView()
{
}

BOOL CReadPGMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CReadPGMView ����

void CReadPGMView::OnDraw(CDC* pDC)
{
	CReadPGMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->m_pImage) return ;
	else pDoc->m_pImage->Draw(pDC->GetSafeHdc(), CRect(0, 0, pDoc->m_pImage->GetWidth(), pDoc->m_pImage->GetHeight()));
}


// CReadPGMView ��ӡ


void CReadPGMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CReadPGMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CReadPGMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CReadPGMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CReadPGMView ���

#ifdef _DEBUG
void CReadPGMView::AssertValid() const
{
	CView::AssertValid();
}

void CReadPGMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReadPGMDoc* CReadPGMView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReadPGMDoc)));
	return (CReadPGMDoc*)m_pDocument;
}
#endif //_DEBUG


// CReadPGMView ��Ϣ�������
