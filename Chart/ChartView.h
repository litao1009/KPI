
// ChartView.h : CChartView ��Ľӿ�
//

#pragma once

#include <memory>

class CChartView : public CView
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

protected: // �������л�����
	CChartView();
	DECLARE_DYNCREATE(CChartView)

// ����
public:
	CChartDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL ) override;
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
};

#ifndef _DEBUG  // ChartView.cpp �еĵ��԰汾
inline CChartDoc* CChartView::GetDocument() const
   { return reinterpret_cast<CChartDoc*>(m_pDocument); }
#endif

