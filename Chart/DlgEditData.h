#pragma once
#include "afxwin.h"

#include <memory>
// DlgEditData �Ի���

class DlgEditData : public CDialogEx
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

	DECLARE_DYNAMIC(DlgEditData)

public:
	DlgEditData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgEditData();

// �Ի�������
	enum { IDD = IDD_DLG_EDITDATA };

	int	GetSF() const;

	int	GetYF() const;

	int GetHSS() const;

	bool Clear() const;

	void	SetDay( int d );

	int	GetDay() const;


	virtual BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit TxtHSS_;
	CEdit TxtSF_;
	CEdit TxtYF_;
	CButton BtnOK_;
	CStatic Label_;

	int		SF_{};
	int		YF_{};
	int		HSS_{};
	int		Day_{1};
	bool	Clear_{};

	afx_msg void OnEnChangeTxtSf();
	afx_msg void OnEnChangeTxtYf();
	afx_msg void OnEnChangeTxtHss();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnImport();
};
