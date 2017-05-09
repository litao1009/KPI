// DlgParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgParam.h"
#include "afxdialogex.h"

#include <string>

// CDlgParam �Ի���

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
	DDX_Control( pDX, IDC_CB_SEX, CBSex_ );
	DDX_Control( pDX, IDC_TXT_AGE, TxtAge_ );
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
	ON_EN_CHANGE( IDC_TXT_SF, &CDlgParam::OnEnChangeTxtSf )
	ON_EN_CHANGE( IDC_TXT_YF, &CDlgParam::OnEnChangeTxtYf )
	ON_EN_CHANGE( IDC_TXT_HSS, &CDlgParam::OnEnChangeTxtHss )
	ON_EN_CHANGE( IDC_TXT_AGE, &CDlgParam::OnEnChangeTxtAge )
	ON_CBN_SELCHANGE( IDC_CB_SEX, &CDlgParam::OnCbnSelchangeCbSex )
END_MESSAGE_MAP()


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TxtSF_.SetWindowTextW( _T( "50" ) );
	TxtYF_.SetWindowTextW( _T( "50" ) );
	TxtHss_.SetWindowTextW( _T( "50" ) );
	TxtAge_.SetWindowTextW( _T( "20" ) );
	CBSex_.SetCurSel( 0 );
	
	OnEnChangeTxtSf();
	OnEnChangeTxtYf();
	OnEnChangeTxtHss();
	OnEnChangeTxtAge();
	OnCbnSelchangeCbSex();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


// CDlgParam ��Ϣ�������


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

int CDlgParam::GetAge() const
{
	return Age_;
}

bool CDlgParam::IsMale() const
{
	return Male_;
}

void CDlgParam::OnEnChangeTxtSf()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

void CDlgParam::OnEnChangeTxtAge()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	TxtAge_.GetWindowTextW( str );

	std::wstring wstr = str.GetBuffer();
	str.ReleaseBuffer();

	if ( !wstr.empty() )
	{
		Age_ = std::stoi( wstr );

		if ( Age_ > 100 )
		{
			Age_ = 100;
		}

		TxtAge_.SetWindowTextW(std::to_wstring(Age_).c_str());
		TxtAge_.SetSel( 0, -1 );
		TxtAge_.SetSel( -1 );
	}
}


void CDlgParam::OnCbnSelchangeCbSex()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Male_ = CBSex_.GetCurSel() == 0;
}