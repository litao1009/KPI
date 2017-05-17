
// ChartView.cpp : CChartView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Chart.h"
#endif

#include "ChartDoc.h"
#include "ChartView.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

class	CChartView::Imp
{
public:
};

// CChartView

IMPLEMENT_DYNCREATE(CChartView, CView)

BEGIN_MESSAGE_MAP(CChartView, CView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CChartView ����/����

CChartView::CChartView():ImpUPtr_( std::make_unique<Imp>() )
{
	// TODO:  �ڴ˴���ӹ������

}

CChartView::~CChartView()
{
}

BOOL CChartView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChartView ����

void CChartView::OnDraw(CDC* /*pDC*/)
{
	
}


// CChartView ���

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CView::AssertValid();
}

void CChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChartDoc* CChartView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChartDoc)));
	return (CChartDoc*)m_pDocument;
}

BOOL CChartView::Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /*= NULL */ )
{
	auto ret = CView::Create( lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext );

	GetParentFrame()->SetActiveView( this );

	return ret;
}

#endif //_DEBUG


// CChartView ��Ϣ�������


BOOL CChartView::OnEraseBkgnd( CDC* pDC )
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}
