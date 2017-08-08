// DlgSkinGuide.cpp : 实现文件
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgSkinGuide.h"
#include "afxdialogex.h"


// DlgSkinGuide 对话框

IMPLEMENT_DYNAMIC(DlgSkinGuide, CDialogEx)

DlgSkinGuide::DlgSkinGuide( const std::wstring& content, CWnd* pParent /*=NULL*/ )
: CDialogEx(DlgSkinGuide::IDD, pParent), Content_(content)
{

}

DlgSkinGuide::~DlgSkinGuide()
{
}

void DlgSkinGuide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_STATIC_CONTENT, LTContent_ );
}


BEGIN_MESSAGE_MAP(DlgSkinGuide, CDialogEx)
END_MESSAGE_MAP()


// DlgSkinGuide 消息处理程序


BOOL DlgSkinGuide::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	LTContent_.SetWindowTextW( Content_.c_str() );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
