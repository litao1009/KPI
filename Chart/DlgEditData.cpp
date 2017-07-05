// DlgEditData.cpp : 实现文件
//

#include "stdafx.h"
#include "Chart.h"
#include "DlgEditData.h"
#include "afxdialogex.h"

#include <string>
#include <regex>
#include <boost/filesystem.hpp>

class	DlgEditData::Imp
{
public:

	DlgEditData*				ThisPtr_{};
	int							CurSel_{};

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
	DDX_Control( pDX, IDC_CB_DATALIST, CbDataList_ );
}


BEGIN_MESSAGE_MAP(DlgEditData, CDialogEx)
	ON_EN_CHANGE( IDC_TXT_SF, &DlgEditData::OnEnChangeTxtSf )
	ON_EN_CHANGE( IDC_TXT_YF, &DlgEditData::OnEnChangeTxtYf )
	ON_EN_CHANGE( IDC_TXT_HSS, &DlgEditData::OnEnChangeTxtHss )
	ON_BN_CLICKED( IDC_BTN_CLEAR, &DlgEditData::OnBnClickedBtnClear )
	ON_BN_CLICKED( IDC_BTN_IMPORT, &DlgEditData::OnBnClickedBtnImport )
	ON_CBN_SELCHANGE( IDC_CB_DATALIST, &DlgEditData::OnCbnSelchangeCbDatalist )
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

std::vector<std::tuple<int, int, int>> DlgEditData::GetData() const
{
	if ( !DataList_.empty() )
	{
		return DataList_;
	}
	else
	{
		decltype( DataList_ ) tmp;
		tmp.emplace_back( std::make_tuple( HSS_, YF_, SF_ ) );
		return tmp;
	}
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

	DayBegin_ = d;
	DayEnd_ = d;
}

std::tuple<int,int> DlgEditData::GetDay() const
{
	return std::make_tuple( DayBegin_, DayEnd_ );
}

BOOL DlgEditData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CbDataList_.EnableWindow( FALSE );
	Label_.SetWindowTextW( ( L"第" + std::to_wstring( DayBegin_ ) + L"天" ).c_str() );
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

		std::string line;
		try
		{
			boost::filesystem::ifstream ifs( wstr );

			std::getline( ifs, line );
			std::getline( ifs, line );

			std::regex rg( R"(\s*(\d+)\s+(\d+)\s+(\d+)\s*)" );
			std::smatch what;

			decltype( DataList_ ) importList;

			while ( ifs )
			{
				line.clear();
				std::getline( ifs, line );

				if ( !std::regex_match( line, what, rg ) )
				{
					continue;
				}

				auto hss = std::stoi( what[1].str() );
				auto yz = std::stoi( what[2].str() );
				auto sf = std::stoi( what[3].str() );

				importList.emplace_back( hss, yz, sf );

				if ( DayBegin_ + importList.size() - 1 >= 8 )
				{
					break;
				}
			}

			if ( importList.empty() )
			{
				throw "empty";
			}

			DataList_ = importList;

			DayEnd_ = DayBegin_ + DataList_.size() - 1;
			ImpUPtr_->CurSel_ = 0;
			CbDataList_.ResetContent();

			if ( DataList_.size() > 1 )
			{
				for ( auto index = 0; index < DataList_.size(); ++index )
				{
					auto str = L"第" + std::to_wstring( DayBegin_ + index ) + L"天";
					CbDataList_.AddString( str.c_str() );
				}

				CbDataList_.EnableWindow( TRUE );
				CbDataList_.SetCurSel( ImpUPtr_->CurSel_ );
				Label_.SetWindowTextW( ( L"第" + std::to_wstring( DayBegin_ ) + L"~" + std::to_wstring(DayEnd_) + L"天" ).c_str() );
			}
			else
			{
				CbDataList_.EnableWindow( FALSE );
				Label_.SetWindowTextW( ( L"第" + std::to_wstring( DayBegin_ ) + L"天" ).c_str() );
			}

			int sf{}, yz{}, hss{};
			std::tie( hss, yz, sf ) = DataList_[ImpUPtr_->CurSel_];
			ImpUPtr_->UpdateValue( sf, yz, hss );

			GetDlgItem( IDOK )->SetFocus();
		}
		catch ( ... )
		{
			MessageBox( _T( "格式错误！" ) );
		}

	}
}


void DlgEditData::OnCbnSelchangeCbDatalist()
{
	ImpUPtr_->CurSel_ = CbDataList_.GetCurSel();

	int sf{}, yz{}, hss{};
	std::tie( hss, yz, sf ) = DataList_[ImpUPtr_->CurSel_];
	ImpUPtr_->UpdateValue( sf, yz, hss );
}
