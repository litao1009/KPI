
// KPIView.cpp : CKPIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "KPI.h"
#endif

#include "KPIDoc.h"
#include "KPIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKPIView

IMPLEMENT_DYNCREATE(CKPIView, CView)

BEGIN_MESSAGE_MAP(CKPIView, CView)
END_MESSAGE_MAP()

// CKPIView ����/����

CKPIView::CKPIView()
{
	// TODO:  �ڴ˴���ӹ������

}

CKPIView::~CKPIView()
{
}

BOOL CKPIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	auto ret = CView::PreCreateWindow(cs);

	return ret;
}

// CKPIView ����

void CKPIView::OnDraw(CDC* /*pDC*/)
{
	CKPIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto t = IsWindow(GetSafeHwnd());

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKPIView ���

#ifdef _DEBUG
void CKPIView::AssertValid() const
{
	CView::AssertValid();
}

void CKPIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKPIDoc* CKPIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKPIDoc)));
	return (CKPIDoc*)m_pDocument;
}
#endif //_DEBUG


// CKPIView ��Ϣ�������
