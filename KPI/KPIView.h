
// KPIView.h : CKPIView ��Ľӿ�
//

#pragma once


class CKPIView : public CView
{
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
};

#ifndef _DEBUG  // KPIView.cpp �еĵ��԰汾
inline CKPIDoc* CKPIView::GetDocument() const
   { return reinterpret_cast<CKPIDoc*>(m_pDocument); }
#endif

