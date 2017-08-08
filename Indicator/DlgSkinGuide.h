#pragma once
#include "resource.h"
#include "afxwin.h"

#include <string>

// DlgSkinGuide 对话框

class DlgSkinGuide : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSkinGuide)

public:
	DlgSkinGuide(const std::wstring& content, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSkinGuide();

// 对话框数据
	enum { IDD = IDD_DLG_SKIN_GUIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic LTContent_;
	std::wstring	Content_;
	virtual BOOL OnInitDialog();
};
