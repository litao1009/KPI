// DlgSkinGuide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Indicator.h"
#include "DlgSkinGuide.h"
#include "afxdialogex.h"


// DlgSkinGuide �Ի���

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


// DlgSkinGuide ��Ϣ�������


BOOL DlgSkinGuide::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	LTContent_.SetWindowTextW( Content_.c_str() );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
