// DlgSwitchItem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgSwitchItem.h"
#include "afxdialogex.h"


// DlgSwitchItem �Ի���

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


// DlgSwitchItem ��Ϣ�������


void DlgSwitchItem::OnCbnSelchangeCbItemlist()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ������ר�õĴ�������
	
	return 0;
}


BOOL DlgSwitchItem::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL DlgSwitchItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CBItems.ResetContent();
	for ( auto index = 1; index <= Count; ++index )
	{
		auto str = L"��" + std::to_wstring(index) + L"������";
		CBItems.AddString(str.c_str());
	}

	CBItems.SetCurSel(Cursel);

	if ( Count == 0 )
	{
		BtnOK.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
