
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Indicator.h"

#include "MainFrm.h"

#include "DlgParam.h"
#include "DlgSwitchItem.h"
#include "DlgSkinGuide.h"

#include "Frame/OgreEnv.h"
#include "Frame/OgreWndWrapper.h"
#include "Controller/IndicatorController.h"
#include "FrameEvent/IndicatorEvt.h"

#include <fstream>
#include <regex>
#include <vector>
#include <tuple>
#include <string>

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

// CMainFrame

class	CMainFrame::Imp
{
public:

	OgreWndWrapperUPtr						OgreWnd_;
	std::vector<std::tuple<int, int, int>>	itemList;
	int										CurIndex{};
	IndicatorEvt::SPtr						Evt = std::make_shared<IndicatorEvt>();
	std::vector<std::wstring>				SkinGuideList;
	int										CurSkinGuideIdx{};

public:

	void	PostEvt()
	{
		if ( Evt->Melanin <= 9 )
		{
			CurSkinGuideIdx = 0;
		}
		else if ( Evt->Melanin <= 14 )
		{
			CurSkinGuideIdx = 1;
		}
		else if ( Evt->Melanin <= 22 )
		{
			CurSkinGuideIdx = 2;
		}
		else if ( Evt->Melanin <= 30 )
		{
			CurSkinGuideIdx = 3;
		}
		else if ( Evt->Melanin <= 40 )
		{
			CurSkinGuideIdx = 4;
		}
		else
		{
			CurSkinGuideIdx = 5;
		}

		OgreEnv::GetInstance().PostFrameEventTo3D( Evt->ConvertToFrameEvent() );
	}
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND( ID_IMPORT, &CMainFrame::OnImport )
	ON_COMMAND( ID_MODIFY_PARAM, &CMainFrame::OnModifyParam )
	ON_COMMAND(ID_SWITCH_ITEM, &CMainFrame::OnSwitchItem)
	ON_COMMAND( ID_SKIN_GUIDE, &CMainFrame::OnSkinGuide )
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	ImpUPtr_->SkinGuideList.emplace_back( 
		L"1 )	����Ҫ�ر�ʹ�ú����׳ɷֵĻ�ױƷ��ע���ɹ��ɹ���޸���\n"
		L"2)	��Ҫѡ����б�ʪ�����幦�ܵĻ�ױƷ��\n"
		L"3)	�Ƽ��ļ�ʹ��������Ĥ��ͨ��ÿ��ʹ�ö��Σ����ٳ���ʹ��������ʱ�䡣\n"
		L"4)	�Ƽ�Ʒ�ƣ���������͸������Դ����������Ĥ���۲ݼ�(HERBORIST)ݼ��ԭҺ.���Ӿ�͸����Ҷ��Ĥ�ȡ�\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	Ƥ�����ļ���ɹ��ɹ����Ҫ�޸���ߣ�\n"
		L"2)	����ѡ����б�ʪ�����幦�ܵĻ�ױƷ�����ļ����ʹ�ú����׳ɷֵĻ�ױƷ��\n"
		L"3)	���ļ�ÿ������ʹ��һ��������Һ����Һ�е����׳ɷ�Ϊά����C�����������˲Ρ��ʲݺ�������ȡ��ȣ�ÿ��ʹ�ö�������������Ĥ��\n"
		L"4)	�Ƽ�Ʒ�ƣ�����ʫ��͸�����Һ��ѩ������Һ��FANCL������߾�����Ĥ�����෻�����۷������˿��Ĥ��\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	����ѡ��ʪ�����廯ױƷ�⣬ע���ɹ��ÿ�ճ���ʹ�����׻�ױƷ\n"
		L"2)	ÿ������ʹ��һ��������Һ���ļ�����������˪���������ļ�����\n"
		L"3)	ÿ��ʹ�ö�������������Ĥ��\n"
		L"4)	�Ƽ�Ʒ�ƣ���ʫ������˪���������˹�л�����˪����Һ����Ĥͬǰ��\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	����ʹ�ÿ��͡������໯ױƷ��\n"
		L"2)	ÿ�������ʹ��һ�ο�������ϴ���̣�����ѡ���л�ѩ���ա��ܹ��ա����ᡢˮ���ᡢ��ʾ���ȡ��ȳɷֵĲ�Ʒ��\n"
		L"3)	ÿ������ʹ��һ�����׾�����\n"
		L"4)	ÿ��ʹ�ö�������������Ĥ��\n"
		L"5)	�ļ�������Ҫʹ�ø�PFAֵ�ķ�ɹ�飻\n"
		L"6)	�Ƽ�Ʒ�ƣ������׶����׽����飬SK-II�������������飬��ʫ���쾧͸�߰׵��߾���¶��ŷ���� �����°�����Դ�׾���Һ��\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	�ص�ʹ�������໯ױƷ��\n"
		L"2)	ÿ�������ʹ��һ������ϴ���̣�\n"
		L"3)	������ʹ�����׻�ױˮ��\n"
		L"4)	ÿ������ʹ�����׷�����Һ��\n"
		L"5)	ÿ������ʹ�ö����������׾�����\n"
		L"6)	ÿ��ʹ�ö�������������Ĥ��\n"
		L"7)	�ļ�������Ҫʹ�ø�PFAֵ�ķ�ɹ�飻\n"
		L"8)	�沿�Ļƺְߡ�������趨�ڵ�ҽԺ���Ƥ����ҽ��ָ����ʹ�õ��߲�Ʒ��\n"
		L"9)	�Ƽ�Ʒ�ƣ�ޱ��������׾���ˮ��SK-II������Ө¶��ѩ�����̾�ѩ�����׷�����˪����ޢ�������˪��˪\n" );

	ImpUPtr_->SkinGuideList.emplace_back(
		L"����Ҫ���׻������汣ʪ����ɹ����" );
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	auto cf = GetActiveView();
	

	auto curHwnd = reinterpret_cast<int>( cf->GetSafeHwnd() );
	RECT rect;
	cf->GetClientRect(&rect);
	ImpUPtr_->OgreWnd_ = OgreEnv::GetInstance().CreateRenderWindow(curHwnd, rect.right - rect.left, rect.bottom - rect.top);

	auto ctrller = std::make_shared<IndicatorController>(ImpUPtr_->OgreWnd_->GetRenderWindow());
	OgreEnv::GetInstance().AddController(ctrller);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	auto height = 740;
	cs.cx = height * 2 + 20;
	cs.cy = height + 62;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_THICKFRAME;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnDestroy()
{
	OgreEnv::GetInstance().RemoveAllController();
	ImpUPtr_->OgreWnd_->Destory();

	CFrameWnd::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if ( ImpUPtr_->OgreWnd_ )
	{
		ImpUPtr_->OgreWnd_->Resize(0, 0);
	}
	// TODO:  �ڴ˴������Ϣ����������
}


void CMainFrame::OnImport()
{
	// TODO:  �ڴ���������������	
	CFileDialog dlg(TRUE, 0, 0, 6UL, _T("�ļ� (*.txt)|*.txt||"));
	
	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		auto fp = dlg.GetPathName();
		std::wstring wstr = fp.GetBuffer();
		fp.ReleaseBuffer();

		std::ifstream ifs( wstr );
		std::string line;

		std::regex rg( R"((\d+))" );
		std::smatch what;

		auto evt = std::make_shared<IndicatorEvt>();

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Moisture = static_cast<decltype( evt->Moisture )>( std::stoi( what[1].str() ) );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Fat = static_cast<decltype( evt->Fat )>( std::stoi( what[1].str() ) );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "��ʽ����" ) );
		}
		evt->Melanin = static_cast<decltype( evt->Melanin )>( std::stoi( what[1].str() ) );

		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}
}


void CMainFrame::OnModifyParam()
{
	// TODO:  �ڴ���������������
	{
		auto evt = std::make_shared<ClearEvt>();
		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}

	CDlgParam dlg;
	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		ImpUPtr_->itemList = dlg.GetItemList();
		ImpUPtr_->CurIndex = dlg.GetCursel();
		ImpUPtr_->Evt->Fat = static_cast<decltype( ImpUPtr_->Evt->Fat )>( dlg.GetYF() );
		ImpUPtr_->Evt->Moisture = static_cast<decltype( ImpUPtr_->Evt->Moisture )>( dlg.GetSF() );
		ImpUPtr_->Evt->Melanin = static_cast<decltype( ImpUPtr_->Evt->Melanin )>( dlg.GetHSS() );
		ImpUPtr_->Evt->Male = dlg.IsMale();
		ImpUPtr_->Evt->Age = dlg.GetAge();
		ImpUPtr_->Evt->DisplayType = dlg.GetDisplayType();

		ImpUPtr_->PostEvt();
	}
}


void CMainFrame::OnSwitchItem()
{
	DlgSwitchItem dlg;

	dlg.SetInfo(ImpUPtr_->itemList.size(), ImpUPtr_->CurIndex);
	auto ret = dlg.DoModal();
	if ( ret == 1 )
	{
		ImpUPtr_->CurIndex = dlg.GetCursel();
		auto curVal = ImpUPtr_->itemList[ImpUPtr_->CurIndex];

		ImpUPtr_->Evt->Moisture = static_cast<decltype( ImpUPtr_->Evt->Moisture )>( std::get<0>( curVal ) );
		ImpUPtr_->Evt->Fat = static_cast<decltype( ImpUPtr_->Evt->Fat )>( std::get<1>( curVal ) );
		ImpUPtr_->Evt->Melanin = static_cast<decltype( ImpUPtr_->Evt->Melanin )>( std::get<2>( curVal ) );

		ImpUPtr_->PostEvt();
	}

	// TODO:  �ڴ���������������
}


void CMainFrame::OnSkinGuide()
{
	// TODO:  �ڴ���������������
	DlgSkinGuide dlg( ImpUPtr_->SkinGuideList[ImpUPtr_->CurSkinGuideIdx] );
	dlg.DoModal();
}
