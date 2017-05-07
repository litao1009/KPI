#pragma once
#include "afxwin.h"


// CDlgParam 对话框

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

	int	SF_{};
	int	YF_{};
	int	HSS_{};

public:
	CDlgParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParam();

// 对话框数据
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	int	GetSF() const;

	int	GetYF() const;

	int GetHSS() const;

public:
	CEdit TxtHss_;
	CEdit TxtSF_;
	CEdit TxtYF_;
	afx_msg void OnEnChangeTxtSf();
	afx_msg void OnEnUpdateTxtSf();
	virtual BOOL OnInitDialog();
	CButton BtnOK_;
	afx_msg void OnEnChangeTxtYf();
	afx_msg void OnEnChangeTxtHss();
};
