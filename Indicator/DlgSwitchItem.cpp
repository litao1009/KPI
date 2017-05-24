// DlgSwitchItem.cpp : 实现文件
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgSwitchItem.h"
#include "afxdialogex.h"


// DlgSwitchItem 对话框

IMPLEMENT_DYNAMIC(DlgSwitchItem, CDialogEx)

DlgSwitchItem::DlgSwitchItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSwitchItem::IDD, pParent)
{

}

DlgSwitchItem::~DlgSwitchItem()
{
}

void DlgSwitchItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_ITEMLIST, CBItems);
	DDX_Control(pDX, IDOK, BtnOK);
}


BEGIN_MESSAGE_MAP(DlgSwitchItem, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CB_ITEMLIST, &DlgSwitchItem::OnCbnSelchangeCbItemlist)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// DlgSwitchItem 消息处理程序


void DlgSwitchItem::OnCbnSelchangeCbItemlist()
{
	// TODO:  在此添加控件通知处理程序代码
	Cursel = CBItems.GetCurSel();
}

void DlgSwitchItem::SetInfo(int count, int idx)
{
	Count = count;
	Cursel = idx;
	
}


int DlgSwitchItem::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ( CDialogEx::OnCreate(lpCreateStruct) == -1 )
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


BOOL DlgSwitchItem::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO:  在此添加专用代码和/或调用基类

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL DlgSwitchItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CBItems.ResetContent();
	for ( auto index = 1; index <= Count; ++index )
	{
		auto str = L"第" + std::to_wstring(index) + L"号样本";
		CBItems.AddString(str.c_str());
	}

	CBItems.SetCurSel(Cursel);

	if ( Count == 0 )
	{
		BtnOK.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
