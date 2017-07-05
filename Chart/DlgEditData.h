#pragma once
#include "afxwin.h"

#include <memory>
#include <vector>
// DlgEditData 对话框

class DlgEditData : public CDialogEx
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

	DECLARE_DYNAMIC(DlgEditData)

public:
	DlgEditData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgEditData();

// 对话框数据
	enum { IDD = IDD_DLG_EDITDATA };

	std::vector<std::tuple<int, int, int>>	GetData() const;

	bool Clear() const;

	void	SetDay( int d );

	std::tuple<int,int>	GetDay() const;


	virtual BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	int		DayBegin_{1};
	int		DayEnd_{ 1 };
	bool	Clear_{};
	std::vector<std::tuple<int, int, int>>	DataList_;

	afx_msg void OnEnChangeTxtSf();
	afx_msg void OnEnChangeTxtYf();
	afx_msg void OnEnChangeTxtHss();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnImport();
	CComboBox CbDataList_;
	afx_msg void OnCbnSelchangeCbDatalist();
};
