
// KPIView.cpp : CKPIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Indicator.h"
#endif

#include "IndicatorDoc.h"
#include "IndicatorView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

class	CIndicatorView::Imp
{
public:
};

// CKPIView

IMPLEMENT_DYNCREATE(CIndicatorView, CView)

BEGIN_MESSAGE_MAP(CIndicatorView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CKPIView ����/����

CIndicatorView::CIndicatorView() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  �ڴ˴���ӹ������

}

CIndicatorView::~CIndicatorView()
{
}

BOOL CIndicatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKPIView ����

void CIndicatorView::OnDraw(CDC* /*pDC*/)
{
	

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKPIView ���

#ifdef _DEBUG
void CIndicatorView::AssertValid() const
{
	CView::AssertValid();
}

void CIndicatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIndicatorDoc* CIndicatorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIndicatorDoc)));
	return (CIndicatorDoc*)m_pDocument;
}

BOOL CIndicatorView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /*= NULL*/)
{
	auto ret = CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	
	GetParentFrame()->SetActiveView(this);

	return ret;
}

#endif //_DEBUG


// CKPIView ��Ϣ�������


BOOL CIndicatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}


void CIndicatorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
}


void CIndicatorView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}
