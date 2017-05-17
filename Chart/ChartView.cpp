
// ChartView.cpp : CChartView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CChartView 构造/析构

CChartView::CChartView():ImpUPtr_( std::make_unique<Imp>() )
{
	// TODO:  在此处添加构造代码

}

CChartView::~CChartView()
{
}

BOOL CChartView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChartView 绘制

void CChartView::OnDraw(CDC* /*pDC*/)
{
	
}


// CChartView 诊断

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CView::AssertValid();
}

void CChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChartDoc* CChartView::GetDocument() const // 非调试版本是内联的
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


// CChartView 消息处理程序


BOOL CChartView::OnEraseBkgnd( CDC* pDC )
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
