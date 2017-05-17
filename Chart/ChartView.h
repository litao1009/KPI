
// ChartView.h : CChartView 类的接口
//

#pragma once

#include <memory>

class CChartView : public CView
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

protected: // 仅从序列化创建
	CChartView();
	DECLARE_DYNCREATE(CChartView)

// 特性
public:
	CChartDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL ) override;
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
};

#ifndef _DEBUG  // ChartView.cpp 中的调试版本
inline CChartDoc* CChartView::GetDocument() const
   { return reinterpret_cast<CChartDoc*>(m_pDocument); }
#endif

