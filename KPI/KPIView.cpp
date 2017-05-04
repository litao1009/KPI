
// KPIView.cpp : CKPIView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CKPIView 构造/析构

CKPIView::CKPIView() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  在此处添加构造代码

}

CKPIView::~CKPIView()
{
}

BOOL CKPIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKPIView 绘制

void CKPIView::OnDraw(CDC* /*pDC*/)
{
	

	// TODO:  在此处为本机数据添加绘制代码
}


// CKPIView 诊断

#ifdef _DEBUG
void CKPIView::AssertValid() const
{
	CView::AssertValid();
}

void CKPIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKPIDoc* CKPIView::GetDocument() const // 非调试版本是内联的
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


// CKPIView 消息处理程序


BOOL CKPIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


void CKPIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


void CKPIView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}
