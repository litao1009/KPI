#pragma once
#include "resource.h"
#include "afxwin.h"

#include <string>

// DlgSkinGuide �Ի���

class DlgSkinGuide : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSkinGuide)

public:
	DlgSkinGuide(const std::wstring& content, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSkinGuide();

// �Ի�������
	enum { IDD = IDD_DLG_SKIN_GUIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic LTContent_;
	std::wstring	Content_;
	virtual BOOL OnInitDialog();
};
