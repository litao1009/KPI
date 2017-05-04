
// KPIView.h : CKPIView ��Ľӿ�
//

#pragma once

#include <memory>

class CKPIView : public CView
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

protected: // �������л�����

	CKPIView();
	DECLARE_DYNCREATE(CKPIView)

// ����
public:

	CKPIDoc* GetDocument() const;

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
	virtual ~CKPIView();
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
inline CKPIDoc* CKPIView::GetDocument() const
   { return reinterpret_cast<CKPIDoc*>(m_pDocument); }
#endif

