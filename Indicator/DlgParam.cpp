// DlgParam.cpp : 实现文件
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgParam.h"
#include "afxdialogex.h"

#include <string>

// CDlgParam 对话框

IMPLEMENT_DYNAMIC(CDlgParam, CDialogEx)

CDlgParam::CDlgParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgParam::IDD, pParent)
{

}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TXT_HSS, TxtHss_ );
	DDX_Control( pDX, IDC_TXT_SF, TxtSF_ );
	DDX_Control( pDX, IDC_TXT_YF, TxtYF_ );
	DDX_Control( pDX, IDOK, BtnOK_ );
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
	ON_EN_CHANGE( IDC_TXT_SF, &CDlgParam::OnEnChangeTxtSf )
	ON_EN_UPDATE( IDC_TXT_SF, &CDlgParam::OnEnUpdateTxtSf )
	ON_EN_CHANGE( IDC_TXT_YF, &CDlgParam::OnEnChangeTxtYf )
	ON_EN_CHANGE( IDC_TXT_HSS, &CDlgParam::OnEnChangeTxtHss )
END_MESSAGE_MAP()


// CDlgParam 消息处理程序


int CDlgParam::GetSF() const
{
	return SF_;
}

int CDlgParam::GetYF() const
{
	return YF_;
}

int CDlgParam::GetHSS() const
{
	return HSS_;
}

void CDlgParam::OnEnChangeTxtSf()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	TxtSF_.GetWindowTextW( str );

	std::wstring wstr = str.GetBuffer();
	str.ReleaseBuffer();

	if ( !wstr.empty() )
	{
		SF_ = std::stoi( wstr );

		if ( SF_ > 100 )
		{
			SF_ = 100;
		}

		TxtSF_.SetWindowTextW( std::to_wstring( SF_ ).c_str() );
		TxtSF_.SetSel( 0, -1 );
		TxtSF_.SetSel( -1 );
	}
}

void CDlgParam::OnEnChangeTxtYf()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	TxtYF_.GetWindowTextW( str );

	std::wstring wstr = str.GetBuffer();
	str.ReleaseBuffer();

	if ( !wstr.empty() )
	{
		YF_ = std::stoi( wstr );

		if ( YF_ > 100 )
		{
			YF_ = 100;
		}

		TxtYF_.SetWindowTextW( std::to_wstring( YF_ ).c_str() );
		TxtYF_.SetSel( 0, -1 );
		TxtYF_.SetSel( -1 );
	}
}


void CDlgParam::OnEnChangeTxtHss()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString str;
	TxtHss_.GetWindowTextW( str );

	std::wstring wstr = str.GetBuffer();
	str.ReleaseBuffer();

	if ( !wstr.empty() )
	{
		HSS_ = std::stoi( wstr );

		if ( HSS_ > 100 )
		{
			HSS_ = 100;
		}

		TxtHss_.SetWindowTextW( std::to_wstring( HSS_ ).c_str() );
		TxtHss_.SetSel( 0, -1 );
		TxtHss_.SetSel( -1 );
	}
}



void CDlgParam::OnEnUpdateTxtSf()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TxtSF_.SetWindowTextW( _T( "50" ) );
	TxtYF_.SetWindowTextW( _T( "50" ) );
	TxtHss_.SetWindowTextW( _T( "50" ) );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}