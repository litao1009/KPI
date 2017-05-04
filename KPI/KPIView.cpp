
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

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

class	CKPIView::Imp
{
public:
};

// CKPIView

IMPLEMENT_DYNCREATE(CKPIView, CView)

BEGIN_MESSAGE_MAP(CKPIView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CKPIView ����/����

CKPIView::CKPIView() :ImpUPtr_(std::make_unique<Imp>())
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

	return CView::PreCreateWindow(cs);
}

// CKPIView ����

void CKPIView::OnDraw(CDC* /*pDC*/)
{
	

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

BOOL CKPIView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /*= NULL*/)
{
	auto ret = CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	
	GetParentFrame()->SetActiveView(this);

	return ret;
}

#endif //_DEBUG


// CKPIView ��Ϣ�������


BOOL CKPIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}


void CKPIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}


void CKPIView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}
