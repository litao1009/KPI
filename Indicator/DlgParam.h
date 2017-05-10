#pragma once
#include "afxwin.h"


// CDlgParam 对话框

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

	int		SF_{};
	int		YF_{};
	int		HSS_{};
	int		Age_{};
	bool	Male_{};

	CEdit TxtHss_;
	CEdit TxtSF_;
	CEdit TxtYF_;
	CButton BtnOK_;
	CComboBox CBSex_;
	CEdit TxtAge_;

public:

	CDlgParam(CWnd* pParent = NULL);   // 标准构造函数

	virtual ~CDlgParam();

// 对话框数据
	enum { IDD = IDD_DLG_PARAM };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:

	int	GetSF() const;

	int	GetYF() const;

	int GetHSS() const;

	int	GetAge() const;

	bool	IsMale() const;

public:
	
	afx_msg void OnEnChangeTxtSf();
	afx_msg void OnEnChangeTxtYf();
	afx_msg void OnEnChangeTxtHss();
	afx_msg void OnEnChangeTxtAge();
	afx_msg void OnCbnSelchangeCbSex();
	
	afx_msg void OnBnClickedBtnImport();
};
