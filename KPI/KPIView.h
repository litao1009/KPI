
// KPIView.h : CKPIView 类的接口
//

#pragma once

#include <memory>

class CKPIView : public CView
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

protected: // 仅从序列化创建

	CKPIView();
	DECLARE_DYNCREATE(CKPIView)

// 特性
public:

	CKPIDoc* GetDocument() const;

	// 操作
public:

// 重写
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL) override;
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CKPIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // KPIView.cpp 中的调试版本
inline CKPIDoc* CKPIView::GetDocument() const
   { return reinterpret_cast<CKPIDoc*>(m_pDocument); }
#endif

