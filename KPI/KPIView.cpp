
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKPIView

IMPLEMENT_DYNCREATE(CKPIView, CView)

BEGIN_MESSAGE_MAP(CKPIView, CView)
END_MESSAGE_MAP()

// CKPIView 构造/析构

CKPIView::CKPIView()
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
	auto ret = CView::PreCreateWindow(cs);

	return ret;
}

// CKPIView 绘制

void CKPIView::OnDraw(CDC* /*pDC*/)
{
	CKPIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	auto t = IsWindow(GetSafeHwnd());

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
#endif //_DEBUG


// CKPIView 消息处理程序
