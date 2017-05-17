
// Chart.h : Chart 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CChartApp:
// 有关此类的实现，请参阅 Chart.cpp
//

class CChartApp : public CWinApp
{
public:
	CChartApp();


	virtual int ExitInstance() override;

	virtual BOOL OnIdle( LONG lCount ) override;

	virtual BOOL IsIdleMessage( MSG* pMsg ) override;

	virtual BOOL PumpMessage() override;

	// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChartApp theApp;
