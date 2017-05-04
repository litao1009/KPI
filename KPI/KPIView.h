
// KPIView.h : CKPIView 类的接口
//

#pragma once


class CKPIView : public CView
{
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
};

#ifndef _DEBUG  // KPIView.cpp 中的调试版本
inline CKPIDoc* CKPIView::GetDocument() const
   { return reinterpret_cast<CKPIDoc*>(m_pDocument); }
#endif

