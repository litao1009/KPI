// DlgParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgParam.h"
#include "afxdialogex.h"


#include <boost/format.hpp>
#include <boost/filesystem/fstream.hpp>

// CDlgParam �Ի���

class	CDlgParam::Imp
{
public:

	std::vector<std::tuple<int, int, int>>	itemList;
	CDlgParam*								ThisPtr_{};
	int										Cursel{};

public:

	void	UpdateValue(int s, int y, int h)
	{
		ThisPtr_->SF_ = s;
		ThisPtr_->YF_ = y;
		ThisPtr_->HSS_ = h;

		ThisPtr_->TxtSF_.SetWindowText(std::to_wstring(ThisPtr_->SF_).c_str());
		ThisPtr_->TxtYF_.SetWindowText(std::to_wstring(ThisPtr_->YF_).c_str());
		ThisPtr_->TxtHss_.SetWindowText(std::to_wstring(ThisPtr_->HSS_).c_str());
	}
};

IMPLEMENT_DYNAMIC(CDlgParam, CDialogEx)

CDlgParam::CDlgParam(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgParam::IDD, pParent), ImpUPtr_(std::make_unique<Imp>())
{
	ImpUPtr_->ThisPtr_ = this;
}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXT_HSS, TxtHss_);
	DDX_Control(pDX, IDC_TXT_SF, TxtSF_);
	DDX_Control(pDX, IDC_TXT_YF, TxtYF_);
	DDX_Control(pDX, IDOK, BtnOK_);
	DDX_Control(pDX, IDC_CB_SEX, CBSex_);
	DDX_Control(pDX, IDC_TXT_AGE, TxtAge_);
	DDX_Control(pDX, IDC_CB_IMPORT_ITEM, CBItem_);
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
	ON_EN_CHANGE( IDC_TXT_SF, &CDlgParam::OnEnChangeTxtSf )
	ON_EN_CHANGE( IDC_TXT_YF, &CDlgParam::OnEnChangeTxtYf )
	ON_EN_CHANGE( IDC_TXT_HSS, &CDlgParam::OnEnChangeTxtHss )
	ON_EN_CHANGE( IDC_TXT_AGE, &CDlgParam::OnEnChangeTxtAge )
	ON_CBN_SELCHANGE( IDC_CB_SEX, &CDlgParam::OnCbnSelchangeCbSex )
	ON_BN_CLICKED( IDC_BTN_IMPORT, &CDlgParam::OnBnClickedBtnImport )
	ON_CBN_SELCHANGE(IDC_CB_IMPORT_ITEM, &CDlgParam::OnCbnSelchangeCbImportItem)
END_MESSAGE_MAP()


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CBItem_.EnableWindow(FALSE);

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

std::vector<std::tuple<int, int, int>> CDlgParam::GetItemList() const
{
	return ImpUPtr_->itemList;
}

int CDlgParam::GetCursel() const
{
	return ImpUPtr_->Cursel;
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

void CDlgParam::OnBnClickedBtnImport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg( TRUE, 0, 0, 6UL, _T( "�ļ� (*.txt)|*.txt||" ) );

	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		auto fp = dlg.GetPathName();
		std::wstring wstr = fp.GetBuffer();
		fp.ReleaseBuffer();

		try
		{
			boost::filesystem::ifstream ifs( wstr );

			std::string line;

			static std::string tagStr = "��ɫ��----------��֬----------ˮ��";

			auto foundTag = false;
			while ( true )
			{
				line.clear();
				std::getline(ifs, line);

				if ( line == tagStr )
				{
					foundTag = true;
					break;
				}
			}

			if ( !foundTag )
			{
				throw "";
			}

			float sf{}, yz{}, hss{};

			ImpUPtr_->itemList.clear();

			while ( ifs )
			{
				ifs >> hss >> yz >> sf;

				sf = std::fabs(sf);
				yz = std::fabs(yz);
				hss = std::fabs(hss);

				ImpUPtr_->itemList.emplace_back((int)sf, (int)yz, (int)hss);
			}

			if ( ImpUPtr_->itemList.empty() )
			{
				throw "";
			}

			auto firstVal = ImpUPtr_->itemList.front();
			ImpUPtr_->UpdateValue(std::get<0>(firstVal), std::get<1>(firstVal), std::get<2>(firstVal));

			CBItem_.ResetContent();
			for ( auto index = 0; index < ImpUPtr_->itemList.size(); ++index )
			{
				auto str = L"��" + std::to_wstring(index + 1) + L"������";
				CBItem_.AddString(str.c_str());
			}

			CBItem_.EnableWindow(TRUE);
			CBItem_.SetCurSel(0);

			GetDlgItem( IDOK )->SetFocus();
		}
		catch ( ... )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		
	}
}


void CDlgParam::OnCbnSelchangeCbImportItem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	auto curIndex = CBItem_.GetCurSel();
	auto curVal = ImpUPtr_->itemList[curIndex];
	ImpUPtr_->Cursel = curIndex;
	ImpUPtr_->UpdateValue(std::get<0>(curVal), std::get<1>(curVal), std::get<2>(curVal));
}
