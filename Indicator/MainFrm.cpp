
// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() :ImpUPtr_(std::make_unique<Imp>())
{
	// TODO:  在此添加成员初始化代码
	ImpUPtr_->SkinGuideList.emplace_back( 
		L"1 )	不需要特别使用含美白成分的化妆品，注意防晒和晒后修复；\n"
		L"2)	主要选择具有保湿、抗皱功能的化妆品；\n"
		L"3)	推荐夏季使用美白面膜，通常每周使用二次，至少持续使用两个月时间。\n"
		L"4)	推荐品牌：资生堂新透白美肌源动力美白面膜、佰草集(HERBORIST)菁萃原液.银杏净透银杏叶面膜等。\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	皮肤春夏季防晒，晒后需要修复红斑；\n"
		L"2)	常规选择具有保湿、抗皱功能的化妆品，春夏季配合使用含美白成分的化妆品；\n"
		L"3)	春夏季每日晚上使用一次美白乳液，乳液中的美白成分为维生素C、烟酰胺、人参、甘草和银杏萃取物等；每周使用二至三次美白面膜。\n"
		L"4)	推荐品牌：娇韵诗清透润白乳液，雪肌精乳液，FANCL美白祛斑精华面膜、御泥坊美白嫩肤矿物蚕丝面膜。\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	除了选择保湿、抗皱化妆品外，注意防晒，每日常规使用美白化妆品\n"
		L"2)	每日晚上使用一次美白乳液（夏季）或者美白霜（春季、夏季）；\n"
		L"3)	每周使用二至三次美白面膜。\n"
		L"4)	推荐品牌：雅诗兰黛面霜，安利雅姿光感焕白乳霜。乳液和面膜同前。\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	常规使用控油、美白类化妆品；\n"
		L"2)	每日早晚各使用一次控油美白洗面奶，可以选择含有积雪草苷、熊果苷、曲酸、水杨酸、洋甘菊提取物等成分的产品；\n"
		L"3)	每日晚上使用一次美白精华；\n"
		L"4)	每周使用二至三次美白面膜；\n"
		L"5)	夏季户外活动需要使用高PFA值的防晒乳；\n"
		L"6)	推荐品牌：曼秀雷敦美白洁面乳，SK-II净肌护肤洁面乳，雅诗兰黛晶透沁白淡斑精华露，欧莱雅 科研致白三重源白精华液。\n"
		);

	ImpUPtr_->SkinGuideList.emplace_back(
		L"1)	重点使用美白类化妆品；\n"
		L"2)	每日早晚各使用一次美白洗面奶；\n"
		L"3)	洁面后可使用美白化妆水；\n"
		L"4)	每日早上使用美白防护乳液；\n"
		L"5)	每周晚上使用二至三次美白精华；\n"
		L"6)	每周使用二至三次美白面膜；\n"
		L"7)	夏季户外活动需要使用高PFA值的防晒乳；\n"
		L"8)	面部的黄褐斑、老年斑需定期到医院就诊，皮肤科医生指导下使用淡斑产品；\n"
		L"9)	推荐品牌：薇姿理想焕白精华水，SK-II净白清莹露，雪花秀滋晶雪肤美白防护乳霜，兰蔻臻白美颜霜日霜\n" );

	ImpUPtr_->SkinGuideList.emplace_back(
		L"不需要美白护理，常规保湿、防晒即可" );
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
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



void CMainFrame::OnDestroy()
{
	OgreEnv::GetInstance().RemoveAllController();
	ImpUPtr_->OgreWnd_->Destory();

	CFrameWnd::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if ( ImpUPtr_->OgreWnd_ )
	{
		ImpUPtr_->OgreWnd_->Resize(0, 0);
	}
	// TODO:  在此处添加消息处理程序代码
}


void CMainFrame::OnImport()
{
	// TODO:  在此添加命令处理程序代码	
	CFileDialog dlg(TRUE, 0, 0, 6UL, _T("文件 (*.txt)|*.txt||"));
	
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
			MessageBox( _T( "格式错误！" ) );
		}
		evt->Moisture = static_cast<decltype( evt->Moisture )>( std::stoi( what[1].str() ) );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "格式错误！" ) );
		}
		evt->Fat = static_cast<decltype( evt->Fat )>( std::stoi( what[1].str() ) );

		std::getline( ifs, line );
		if ( !std::regex_match( line, what, rg ) )
		{
			MessageBox( _T( "格式错误！" ) );
		}
		evt->Melanin = static_cast<decltype( evt->Melanin )>( std::stoi( what[1].str() ) );

		OgreEnv::GetInstance().PostFrameEventTo3D( evt->ConvertToFrameEvent() );
	}
}


void CMainFrame::OnModifyParam()
{
	// TODO:  在此添加命令处理程序代码
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

	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnSkinGuide()
{
	// TODO:  在此添加命令处理程序代码
	DlgSkinGuide dlg( ImpUPtr_->SkinGuideList[ImpUPtr_->CurSkinGuideIdx] );
	dlg.DoModal();
}
