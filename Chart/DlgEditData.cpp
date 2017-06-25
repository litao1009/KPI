// DlgEditData.cpp : 实现文件
//

#include "stdafx.h"
#include "Chart.h"
#include "DlgEditData.h"
#include "afxdialogex.h"

#include <string>
#include <boost/filesystem.hpp>

class	DlgEditData::Imp
{
public:

	DlgEditData*				ThisPtr_{};

public:

	void	UpdateValue( int s, int y, int h )
	{
		ThisPtr_->SF_ = s;
		ThisPtr_->YF_ = y;
		ThisPtr_->HSS_ = h;

		ThisPtr_->TxtSF_.SetWindowText( std::to_wstring( ThisPtr_->SF_ ).c_str() );
		ThisPtr_->TxtYF_.SetWindowText( std::to_wstring( ThisPtr_->YF_ ).c_str() );
		ThisPtr_->TxtHSS_.SetWindowText( std::to_wstring( ThisPtr_->HSS_ ).c_str() );
	}
};

// DlgEditData 对话框

IMPLEMENT_DYNAMIC(DlgEditData, CDialogEx)

DlgEditData::DlgEditData(CWnd* pParent /*=NULL*/)
: CDialogEx(DlgEditData::IDD, pParent), ImpUPtr_(std::make_unique<Imp>())
{
	ImpUPtr_->ThisPtr_ = this;
}

DlgEditData::~DlgEditData()
{
}

void DlgEditData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_TXT_HSS, TxtHSS_ );
	DDX_Control( pDX, IDC_TXT_SF, TxtSF_ );
	DDX_Control( pDX, IDC_TXT_YF, TxtYF_ );
	DDX_Control( pDX, IDOK, BtnOK_ );
	DDX_Control( pDX, IDC_LABEL_DAY, Label_ );
}


BEGIN_MESSAGE_MAP(DlgEditData, CDialogEx)
	ON_EN_CHANGE( IDC_TXT_SF, &DlgEditData::OnEnChangeTxtSf )
	ON_EN_CHANGE( IDC_TXT_YF, &DlgEditData::OnEnChangeTxtYf )
	ON_EN_CHANGE( IDC_TXT_HSS, &DlgEditData::OnEnChangeTxtHss )
	ON_BN_CLICKED( IDC_BTN_CLEAR, &DlgEditData::OnBnClickedBtnClear )
	ON_BN_CLICKED( IDC_BTN_IMPORT, &DlgEditData::OnBnClickedBtnImport )
END_MESSAGE_MAP()


// DlgEditData 消息处理程序


void DlgEditData::OnEnChangeTxtSf()
{
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


void DlgEditData::OnEnChangeTxtYf()
{
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


void DlgEditData::OnEnChangeTxtHss()
{
	CString str;
	TxtHSS_.GetWindowTextW( str );

	std::wstring wstr = str.GetBuffer();
	str.ReleaseBuffer();

	if ( !wstr.empty() )
	{
		HSS_ = std::stoi( wstr );

		if ( HSS_ > 100 )
		{
			HSS_ = 100;
		}

		TxtHSS_.SetWindowTextW( std::to_wstring( HSS_ ).c_str() );
		TxtHSS_.SetSel( 0, -1 );
		TxtHSS_.SetSel( -1 );
	}
}


void DlgEditData::OnBnClickedBtnClear()
{
	// TODO:  在此添加控件通知处理程序代码
	Clear_ = true;

	CDialogEx::OnOK();
}

int DlgEditData::GetSF() const
{
	return SF_;
}

int DlgEditData::GetYF() const
{
	return YF_;
}

int DlgEditData::GetHSS() const
{
	return HSS_;
}

bool DlgEditData::Clear() const
{
	return Clear_;
}

void DlgEditData::SetDay( int d )
{
	if ( d < 1 )
	{
		d = 1;
	}

	if ( d > 8 )
	{
		d = 8;
	}

	Day_ = d;
}

int DlgEditData::GetDay() const
{
	return Day_;
}

BOOL DlgEditData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Label_.SetWindowTextW( ( L"第" + std::to_wstring( Day_ ) + L"天" ).c_str() );
	ImpUPtr_->UpdateValue( 50, 50, 50 );

	return TRUE;
}

void DlgEditData::OnBnClickedBtnImport()
{
	CFileDialog dlg( TRUE, 0, 0, 6UL, _T( "文件 (*.txt)|*.txt||" ) );

	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		auto fp = dlg.GetPathName();
		std::wstring wstr = fp.GetBuffer();
		fp.ReleaseBuffer();

		try
		{
			boost::filesystem::ifstream ifs( wstr );

			float sf{}, yz{}, hss{};
			ifs >> hss >> yz >> sf;

			ImpUPtr_->UpdateValue( sf, yz, hss );

			GetDlgItem( IDOK )->SetFocus();
		}
		catch ( ... )
		{
			MessageBox( _T( "格式错误！" ) );
		}

	}
}
