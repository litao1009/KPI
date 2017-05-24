#pragma once

#include "resource.h"

#include <vector>
#include <tuple>
#include <string>
#include "afxwin.h"

// DlgSwitchItem 对话框

class DlgSwitchItem : public CDialogEx
{
	int	Cursel{};
	int Count{};
	DECLARE_DYNAMIC(DlgSwitchItem)

public:
	DlgSwitchItem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSwitchItem();

// 对话框数据
	enum { IDD = IDD_DLG_SWITCH_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCbItemlist();

	int	GetCursel() const
	{
		return Cursel;
	}

	void SetInfo(int count, int idx);
	CComboBox CBItems;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	CButton BtnOK;
};
