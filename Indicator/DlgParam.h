#pragma once
#include "afxwin.h"


// CDlgParam �Ի���

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

	int	SF_{};
	int	YF_{};
	int	HSS_{};

public:
	CDlgParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParam();

// �Ի�������
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
