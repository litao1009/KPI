
// KPIView.cpp : CKPIView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CKPIView 构造/析构

CIndicatorView::CIndicatorView() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  在此处添加构造代码

}

CIndicatorView::~CIndicatorView()
{
}

BOOL CIndicatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKPIView 绘制

void CIndicatorView::OnDraw(CDC* /*pDC*/)
{
	

	// TODO:  在此处为本机数据添加绘制代码
}


// CKPIView 诊断

#ifdef _DEBUG
void CIndicatorView::AssertValid() const
{
	CView::AssertValid();
}

void CIndicatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIndicatorDoc* CIndicatorView::GetDocument() const // 非调试版本是内联的
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


// CKPIView 消息处理程序


BOOL CIndicatorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


void CIndicatorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


void CIndicatorView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}
