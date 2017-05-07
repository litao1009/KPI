
// KPIView.h : CKPIView ��Ľӿ�
//

#pragma once

#include <memory>

class CIndicatorView : public CView
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

protected: // �������л�����

	CIndicatorView();
	DECLARE_DYNCREATE(CIndicatorView)

// ����
public:

	CIndicatorDoc* GetDocument() const;

	// ����
public:

// ��д
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL) override;
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CIndicatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // KPIView.cpp �еĵ��԰汾
inline CIndicatorDoc* CIndicatorView::GetDocument() const
   { return reinterpret_cast<CIndicatorDoc*>(m_pDocument); }
#endif

