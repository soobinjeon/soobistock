
// YOADLLClient_MultiByteDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "YOADLLClient_MultiByte.h"
#include "YOADLLClient_MultiByteDlg.h"
#include "afxdialogex.h"

#include "../include/MessageDef.h"

#include "DSO300001.h"
#include "AUTO11.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CYOADLLClient_MultiByteDlg ��ȭ ����




CYOADLLClient_MultiByteDlg::CYOADLLClient_MultiByteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYOADLLClient_MultiByteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nReqID_300001 = -1;
	m_bStruct		= FALSE;
}

void CYOADLLClient_MultiByteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_lbLog);
	DDX_Text(pDX, IDC_EDIT_LOGIN_ID, m_strLoginID);
	DDX_Text(pDX, IDC_EDIT_LOGIN_PWD, m_strLoginPwd);
	DDX_Text(pDX, IDC_EDIT_CERT_PWD, m_strCertPwd);
	DDX_Control(pDX, IDC_BUTTON_INITIAL, m_btnInitial);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_BUTTON_LOGOUT, m_btnLogout);
	DDX_Control(pDX, IDC_BUTTON_GET_ACCOUNTS, m_btnGetAcctList);
	DDX_Control(pDX, IDC_LIST_ACCOUNTLIST, m_listAccount);
	DDX_Text(pDX, IDC_EDIT_JONGCODE, m_strJongCode);
	DDX_Control(pDX, IDC_COMBO1, m_cbServer);
}

BEGIN_MESSAGE_MAP(CYOADLLClient_MultiByteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WMU_RECEIVE_SYSTEM_MESSAGE, OnReceiveSystemMessage)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_LOGIN, OnLoginComplete)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_GET_ACCOUNTS, OnBnClickedButtonGetAccounts)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH2, OnBnClickedButtonSearch2)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_REGIST, OnBnClickedButtonAutoRegist)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_UNREGIST, OnBnClickedButtonAutoUnRegist)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CYOADLLClient_MultiByteDlg::OnBnClickedButtonLogout)
END_MESSAGE_MAP()


void CYOADLLClient_MultiByteDlg::LogMessage(CString strMsg, int nType /* = 0 */, BOOL bTimeStamp /* = TRUE */)
{
	CString strLog;

	if ( TRUE == bTimeStamp )
	{
		CTime date = CTime::GetCurrentTime();

		if ( 0 == nType )
			strLog.Format( "[LOG:%d-%02d-%02d %02d:%02d:%02d] %s", 
			date.GetYear(), date.GetMonth(), date.GetDay(), 
			date.GetHour(), date.GetMinute(), date.GetSecond(),
			strMsg);
		else if ( 1 == nType )
			strLog.Format( "[ERR:%d-%02d-%02d %02d:%02d:%02d] %s", 
			date.GetYear(), date.GetMonth(), date.GetDay(), 
			date.GetHour(), date.GetMinute(), date.GetSecond(),
			strMsg);
	}
	else
	{
		strLog.Format( "[ERR_MSG] %s", strMsg);
	}

	m_lbLog.AddString( strLog );
}

CString CYOADLLClient_MultiByteDlg::AccountFormat( TCHAR* pData )
{
	CString strResult( pData );

	int nLen = strResult.GetLength();
	if ( 1 == nLen % 2 )
	{
		strResult.Insert(5, "-");
		strResult.Insert(3, "-");
	}
	else
	{
		strResult.Insert(8, "-");
		strResult.Insert(4, "-");
	}

	return strResult;
}

BOOL CYOADLLClient_MultiByteDlg::CheckAPI()
{
	return CheckInit() && CheckLogin();
}

BOOL CYOADLLClient_MultiByteDlg::CheckInit()
{
	if ( FALSE == g_bInitial )
	{
		LogMessage( "����Ÿ Open API �ʱ�ȭ�� �ʿ��մϴ�.", 1 );
	}

	return g_bInitial;
}

BOOL CYOADLLClient_MultiByteDlg::CheckLogin()
{
	if ( FALSE == g_bLogin )
	{
		LogMessage( "�α����� �ʿ��մϴ�.", 1 );
	}

	return g_bLogin;
}

// CYOADLLClient_MultiByteDlg �޽��� ó����

BOOL CYOADLLClient_MultiByteDlg::PreTranslateMessage(MSG* pMsg)
{
	if ( WM_KEYDOWN == pMsg->message )
	{
		if ( VK_RETURN == pMsg->wParam )
		{
			if ( FALSE == g_bInitial )
			{
				OnBnClickedButtonLogin();
			}

			return TRUE;
		}
		else if ( VK_ESCAPE == pMsg->wParam )
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CYOADLLClient_MultiByteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	m_cbServer.AddString( _T("���� ��������") );
	m_cbServer.AddString( _T("����/�ؿ��ֽ� �����") );
	m_cbServer.AddString( _T("�ؿܼ����ɼ� ��������") );
	m_cbServer.AddString( _T("�ؿܼ����ɼ� �����") );
	m_cbServer.SetCurSel(0);

	m_listAccount.SetExtendedStyle( m_listAccount.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_listAccount.SetExtendedStyle( m_listAccount.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_listAccount.InsertColumn(0, "", LVCFMT_RIGHT, 0);
	m_listAccount.InsertColumn(1, "���¹�ȣ", LVCFMT_CENTER, 150);
	m_listAccount.InsertColumn(2, "���¸�", LVCFMT_CENTER, 125);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CYOADLLClient_MultiByteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CYOADLLClient_MultiByteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CYOADLLClient_MultiByteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonInitial()
{

	m_btnInitial.EnableWindow( FALSE );

	int nCurSel = m_cbServer.GetCurSel();
	CString strServer = "simul.tradar.api.com";
	if ( 1 == nCurSel )
		strServer = "real.tradar.api.com";
	else if ( 2 == nCurSel )
		strServer = "simul.tradarglobal.api.com";
	else if ( 3 == nCurSel )
		strServer = "real.tradarglobal.api.com";

	if ( RESULT_SUCCESS == g_iYuantaAPI.YOA_Initial( strServer, GetSafeHwnd(), NULL, WMU_STARTMSGID, FALSE ) )
	{
		if ( 0 == nCurSel || 2 == nCurSel )
			AfxMessageBox( "�������ڷ� �����մϴ�.\n���������� ���º�й�ȣ�� 0000�Դϴ�." );

		LogMessage( "����Ÿ Open API�� �ʱ�ȭ�Ǿ����ϴ�." );

		g_bInitial = TRUE;
		m_cbServer.EnableWindow( FALSE );
		m_btnLogin.EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_LOGIN_ID )->SetFocus();

		//LoadUserInfo();
	}
	else
	{
		LogMessage( "����Ÿ Open API�� �ʱ�ȭ�� �����Ͽ����ϴ�.", 1 );
		m_btnInitial.EnableWindow( TRUE );

		return;
	}

}


void CYOADLLClient_MultiByteDlg::OnBnClickedButtonLogin()
{

	if ( CheckInit() )
	{
		m_btnLogin.EnableWindow( FALSE );

		UpdateData();

		long nResult = g_iYuantaAPI.YOA_Login( GetSafeHwnd(), m_strLoginID, m_strLoginPwd, m_strCertPwd );
		if ( RESULT_SUCCESS == nResult )
		{
			LogMessage( "�α��� ��û�� �Ǿ����ϴ�." );
		}
		else
		{
			LogMessage( "�α��� ��û�� �����Ͽ����ϴ�.", 1 );
			TCHAR msg[2048] = {0,};

			g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );
			LogMessage( msg, 1, FALSE );

			m_btnLogin.EnableWindow( TRUE );
		}
	}

}

LRESULT CYOADLLClient_MultiByteDlg::OnReceiveSystemMessage(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	int nMsgID = wParam;

	TCHAR msg[2048] = {0,};

	g_iYuantaAPI.YOA_GetErrorMessage( nMsgID, msg, sizeof(msg) );
	LogMessage( msg );

	if ( NOTIFY_SYSTEM_NEED_TO_RESTART == nMsgID )
	{
		g_iYuantaAPI.YOA_ReStart();
	}

	return ret;

}

LRESULT CYOADLLClient_MultiByteDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	int nReqID = wParam;

	CString strMsg;
	CString strTrName;

	if ( nReqID == m_nReqID_300001 )
	{
		strTrName = "[300001]�ֽ����簡";
	}	

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:			// ������ �ð� �ȿ� �����κ��� ������ ���� ���, Ÿ�Ӿƿ��� �߻��մϴ�. (�⺻ 10��)
		{
			strMsg.Format( "Timeout %s ��û�� ������ �����ϴ�.", strTrName);
			LogMessage(strMsg);
		}
		break;
	case ERROR_REQUEST_FAIL:			// �������� ��ȸTR(DSO) ó���� ������ �ִ� ��� �߻��մϴ�.
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );	// ó�� �� ������ ���� �޽����� ���� �� �ֽ��ϴ�.
			strMsg.Format( "%s\n%s", strTrName, msg);
			strMsg.TrimRight();
			LogMessage(strMsg);
		}
		break;
	}

	return 0;

}

LRESULT CYOADLLClient_MultiByteDlg::OnLoginComplete(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	if ( RESPONSE_LOGIN_SUCCESS == wParam )
	{
		LogMessage( "�α����� �Ϸ�Ǿ����ϴ�." );
		m_btnLogout.EnableWindow( TRUE );
		m_btnGetAcctList.EnableWindow( TRUE );

		g_bLogin = TRUE;

	}
	else if ( RESPONSE_LOGIN_FAIL == wParam )
	{
		if ( ERROR_TIMEOUT_DATA == lParam )
		{
			LogMessage( "�α����� �����Ͽ����ϴ�.", 1 );
			LogMessage( "�����κ��� �α��� ������ �����ϴ�. �ٽ� �õ��Ͽ� �ֽʽÿ�.", 1, FALSE );
		}
		else
		{
			LogMessage( "�α����� �����Ͽ����ϴ�.", 1 );

			TCHAR msg[2048] = {0,};

			g_iYuantaAPI.YOA_GetErrorMessage( lParam, msg, sizeof(msg) );
			LogMessage( msg, 1, FALSE );
		}

		m_btnLogin.EnableWindow( TRUE );
		m_btnLogout.EnableWindow( FALSE );
		m_btnGetAcctList.EnableWindow( FALSE );
	}

	return ret;

}

LRESULT CYOADLLClient_MultiByteDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{

	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strTRID( pRecvData->szTrCode );

	if ( wParam == m_nReqID_300001 )
	{
		if ( FALSE == m_bStruct )
		{
			char data[1024] = {0,};

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetTRFieldString( "300001", "OutBlock1", "jongname", data, sizeof(data) );
			GetDlgItem( IDC_BT_JONGNAME )->SetWindowText( data );

			g_iYuantaAPI.YOA_GetTRFieldString( "300001", "OutBlock1", "curjuka", data, sizeof(data) );
			GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

			g_iYuantaAPI.YOA_SetTRInfo( "300001", "OutBlock1" );

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "debi", data, sizeof(data) );
			GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "debirate", data, sizeof(data) );
			GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "volume", data, sizeof(data) );
			GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );

			g_iYuantaAPI.YOA_SetTRInfo( "300001", "OutBlock2" );
			int nCnt = g_iYuantaAPI.YOA_GetRowCount( "300001", "OutBlock2" );

			if ( 0 < nCnt )
			{
				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "highjuka", data, sizeof(data), 0 );
				GetDlgItem( IDC_BT_OUTBLOCK2_01 )->SetWindowText( data );

				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "highjukaday", data, sizeof(data), 0 );
				GetDlgItem( IDC_BT_OUTBLOCK2_02 )->SetWindowText( data );
			}

			if ( 2 < nCnt )
			{
				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "lowjuka", data, sizeof(data), 2 );
				GetDlgItem( IDC_BT_OUTBLOCK2_03 )->SetWindowText( data );

				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "lowjukaday", data, sizeof(data), 2 );
				GetDlgItem( IDC_BT_OUTBLOCK2_04 )->SetWindowText( data );
			}

			g_iYuantaAPI.YOA_SetTRInfo( "300001", "OutBlock3" );
			nCnt = g_iYuantaAPI.YOA_GetRowCount( "300001", "OutBlock3" );

			if ( 0 < nCnt )
			{
				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "medovol", data, sizeof(data), 0 );
				GetDlgItem( IDC_BT_OUTBLOCK3_01 )->SetWindowText( data );

				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "mesuvol", data, sizeof(data), 0 );
				GetDlgItem( IDC_BT_OUTBLOCK3_02 )->SetWindowText( data );
			}

			if ( 2 < nCnt )
			{
				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "medovol", data, sizeof(data), 4 );
				GetDlgItem( IDC_BT_OUTBLOCK3_03 )->SetWindowText( data );

				memset( data, 0x00, sizeof(data) );
				g_iYuantaAPI.YOA_GetFieldString( "mesuvol", data, sizeof(data), 4 );
				GetDlgItem( IDC_BT_OUTBLOCK3_04 )->SetWindowText( data );
			}

			g_iYuantaAPI.YOA_SetTRInfo( "300001", "OutBlock4" );
			
			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "stockgubun", data, sizeof(data), 0 );
			GetDlgItem( IDC_BT_OUTBLOCK4_01 )->SetWindowText( data );

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "flowstocks", data, sizeof(data), 0 );
			GetDlgItem( IDC_BT_OUTBLOCK4_02 )->SetWindowText( data );

			memset( data, 0x00, sizeof(data) );
			g_iYuantaAPI.YOA_GetFieldString( "loanvolume", data, sizeof(data), 0 );
			GetDlgItem( IDC_BT_OUTBLOCK4_03 )->SetWindowText( data );
		}
		else
		{
			if ( NULL != pRecvData->lpData )
			{
				LP_DSO300001_OutBlock1 pOutBlock1 = (LP_DSO300001_OutBlock1)pRecvData->lpData;
				
				long curJuka = g_iYuantaAPI.GetPacketLong( pOutBlock1->curjuka, sizeof(pOutBlock1->curjuka), TYPE_LONG );
					
				GetDlgItem( IDC_BT_JONGNAME )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->jongname, sizeof(pOutBlock1->jongname), TYPE_STRING ) 
				);

				GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->curjuka, sizeof(pOutBlock1->curjuka), TYPE_LONG ) 
				);

				GetDlgItem( IDC_BT_DEBI )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->debi, sizeof(pOutBlock1->debi), TYPE_LONG ) 
				);

				GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->debirate, sizeof(pOutBlock1->debirate), TYPE_FLOAT ) 
				);

				GetDlgItem( IDC_BT_VOLUME )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->volume, sizeof(pOutBlock1->volume), TYPE_LONG ) 
				);
				
				// OutBlock2
				int nCount = g_iYuantaAPI.GetPacketWord( pRecvData->lpData + sizeof(DSO300001_OutBlock1), sizeof(WORD), TYPE_LONG );
				
				LP_DSO300001_OutBlock2 pOutBlock2_0 = (LP_DSO300001_OutBlock2)(pRecvData->lpData + sizeof(DSO300001_OutBlock1) + sizeof(WORD));
				CString strHighjuka = g_iYuantaAPI.GetPacketString( pOutBlock2_0->highjuka, sizeof(pOutBlock2_0->highjuka), TYPE_LONG );
				CString strHighjukaday = g_iYuantaAPI.GetPacketString( pOutBlock2_0->highjukaday, sizeof(pOutBlock2_0->highjukaday), TYPE_STRING );
				long nLowjuka = g_iYuantaAPI.GetPacketLong( pOutBlock2_0->lowjuka, sizeof(pOutBlock2_0->lowjuka), TYPE_LONG );
				CString strLowjukaday = g_iYuantaAPI.GetPacketString( pOutBlock2_0->lowjukaday, sizeof(pOutBlock2_0->lowjukaday), TYPE_STRING );
				
				LP_DSO300001_OutBlock2 pOutBlock2_1 = (LP_DSO300001_OutBlock2)((char*)pOutBlock2_0 + sizeof(DSO300001_OutBlock2));
				long nHighjuka_1 = g_iYuantaAPI.GetPacketLong( pOutBlock2_1->highjuka, sizeof(pOutBlock2_1->highjuka), TYPE_LONG );
				CString strHighjukaday_1 = g_iYuantaAPI.GetPacketString( pOutBlock2_1->highjukaday, sizeof(pOutBlock2_1->highjukaday), TYPE_STRING );
				long nLowjuka_1 = g_iYuantaAPI.GetPacketLong( pOutBlock2_1->lowjuka, sizeof(pOutBlock2_1->lowjuka), TYPE_LONG );
				CString strLowjukaday_1 = g_iYuantaAPI.GetPacketString( pOutBlock2_1->lowjukaday, sizeof(pOutBlock2_1->lowjukaday), TYPE_STRING );

				LP_DSO300001_OutBlock2 pOutBlock2_2 = (LP_DSO300001_OutBlock2)((char*)pOutBlock2_1 + sizeof(DSO300001_OutBlock2));
				long nHighjuka_2 = g_iYuantaAPI.GetPacketLong( pOutBlock2_2->highjuka, sizeof(pOutBlock2_2->highjuka), TYPE_LONG );
				CString strHighjukaday_2 = g_iYuantaAPI.GetPacketString( pOutBlock2_2->highjukaday, sizeof(pOutBlock2_2->highjukaday), TYPE_STRING );
				CString strLowjuka_2 = g_iYuantaAPI.GetPacketString( pOutBlock2_2->lowjuka, sizeof(pOutBlock2_2->lowjuka), TYPE_LONG );
				CString strLowjukaday_2 = g_iYuantaAPI.GetPacketString( pOutBlock2_2->lowjukaday, sizeof(pOutBlock2_2->lowjukaday), TYPE_STRING );

				GetDlgItem( IDC_BT_OUTBLOCK2_01 )->SetWindowText( strHighjuka );
				GetDlgItem( IDC_BT_OUTBLOCK2_02 )->SetWindowText( strHighjukaday );
				GetDlgItem( IDC_BT_OUTBLOCK2_03 )->SetWindowText( strLowjuka_2 );
				GetDlgItem( IDC_BT_OUTBLOCK2_04 )->SetWindowText( strLowjukaday_2 );

				// OutBlock3
				nCount = g_iYuantaAPI.GetPacketWord( (char*)pOutBlock2_2 + sizeof(DSO300001_OutBlock2), sizeof(WORD), TYPE_LONG );

				LP_DSO300001_OutBlock3 pOutBlock3_0 = (LP_DSO300001_OutBlock3)((char*)pOutBlock2_2 + sizeof(DSO300001_OutBlock2) + sizeof(WORD));
				CString strMedovol = g_iYuantaAPI.GetPacketString( pOutBlock3_0->medovol, sizeof(pOutBlock3_0->medovol), TYPE_LONG );
				CString strMesuvol = g_iYuantaAPI.GetPacketString( pOutBlock3_0->mesuvol, sizeof(pOutBlock3_0->mesuvol), TYPE_LONG );

				LP_DSO300001_OutBlock3 pOutBlock3_1 = (LP_DSO300001_OutBlock3)((char*)pOutBlock3_0 + sizeof(DSO300001_OutBlock3));
				long nMesuvol_1 = g_iYuantaAPI.GetPacketLong( pOutBlock3_1->mesuvol, sizeof(pOutBlock3_1->mesuvol), TYPE_LONG );

				LP_DSO300001_OutBlock3 pOutBlock3_2 = (LP_DSO300001_OutBlock3)((char*)pOutBlock3_1 + sizeof(DSO300001_OutBlock3));
				long nMesuvol_2 = g_iYuantaAPI.GetPacketLong( pOutBlock3_2->mesuvol, sizeof(pOutBlock3_2->mesuvol), TYPE_LONG );

				LP_DSO300001_OutBlock3 pOutBlock3_3 = (LP_DSO300001_OutBlock3)((char*)pOutBlock3_2 + sizeof(DSO300001_OutBlock3));
				long nMesuvol_3 = g_iYuantaAPI.GetPacketLong( pOutBlock3_3->mesuvol, sizeof(pOutBlock3_3->mesuvol), TYPE_LONG );

				LP_DSO300001_OutBlock3 pOutBlock3_4 = (LP_DSO300001_OutBlock3)((char*)pOutBlock3_3 + sizeof(DSO300001_OutBlock3));
				CString strMedovol_4 = g_iYuantaAPI.GetPacketString( pOutBlock3_4->medovol, sizeof(pOutBlock3_4->medovol), TYPE_LONG );
				CString strMesuvol_4 = g_iYuantaAPI.GetPacketString( pOutBlock3_4->mesuvol, sizeof(pOutBlock3_4->mesuvol), TYPE_LONG );

				GetDlgItem( IDC_BT_OUTBLOCK3_01 )->SetWindowText( strMedovol );
				GetDlgItem( IDC_BT_OUTBLOCK3_02 )->SetWindowText( strMesuvol );
				GetDlgItem( IDC_BT_OUTBLOCK3_03 )->SetWindowText( strMedovol_4 );
				GetDlgItem( IDC_BT_OUTBLOCK3_04 )->SetWindowText( strMesuvol_4 );

				// OutBlock4
				LP_DSO300001_OutBlock4 pOutBlock4 = (LP_DSO300001_OutBlock4)((char*)pOutBlock3_4 + sizeof(DSO300001_OutBlock3));
				CString strStockgubun = g_iYuantaAPI.GetPacketString( pOutBlock4->stockgubun, sizeof(pOutBlock4->stockgubun), TYPE_STRING );
				CString strFlowstocks = g_iYuantaAPI.GetPacketString( pOutBlock4->flowstocks, sizeof(pOutBlock4->flowstocks), TYPE_LONG );
				CString strLoanvolume = g_iYuantaAPI.GetPacketDBLString( pOutBlock4->loanvolume, sizeof(pOutBlock4->loanvolume), TYPE_DOUBLE, 2 );
				
				GetDlgItem( IDC_BT_OUTBLOCK4_01 )->SetWindowText( strStockgubun );
				GetDlgItem( IDC_BT_OUTBLOCK4_02 )->SetWindowText( strFlowstocks );
				GetDlgItem( IDC_BT_OUTBLOCK4_03 )->SetWindowText( strLoanvolume );
			}
		}

		LogMessage( "[300001]�ֽ����簡 ������ �����Ͽ����ϴ�." );
	}

	return 0;

}

LRESULT CYOADLLClient_MultiByteDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{

	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );

	if ( 0 == strAutoID.Compare( "11" ) )
	{
		if ( FALSE == m_bStruct )
		{
			long nData = 0;
			TCHAR data[1024] = {0,};

			//g_iYuantaAPI.YOA_GetTRFieldLong( "11", "OutBlock1", "curjuka", &nData );
			g_iYuantaAPI.YOA_GetTRFieldString( "11", "OutBlock1", "curjuka", data, sizeof(data) );
			GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

			g_iYuantaAPI.YOA_GetTRFieldString( "11", "OutBlock1", "debi", data, sizeof(data) );
			GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

			g_iYuantaAPI.YOA_GetTRFieldString( "11", "OutBlock1", "debirate", data, sizeof(data) );
			GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

			g_iYuantaAPI.YOA_GetTRFieldString( "11", "OutBlock1", "volume", data, sizeof(data) );
			GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );
		}
		else
		{
			if ( NULL != pRecvData->lpData )
			{
				LP_AUTO11_OutBlock1 pOutBlock1 = (LP_AUTO11_OutBlock1)pRecvData->lpData;

				long curJuka = g_iYuantaAPI.GetPacketLong( pOutBlock1->curjuka, sizeof(pOutBlock1->curjuka), TYPE_LONG );

				GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->curjuka, sizeof(pOutBlock1->curjuka), TYPE_LONG ) 
					);

				GetDlgItem( IDC_BT_DEBI )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->debi, sizeof(pOutBlock1->debi), TYPE_LONG ) 
					);

				GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->debirate, sizeof(pOutBlock1->debirate), TYPE_FLOAT ) 
					);

				GetDlgItem( IDC_BT_VOLUME )->SetWindowText( 
					g_iYuantaAPI.GetPacketString( pOutBlock1->volume, sizeof(pOutBlock1->volume), TYPE_LONG ) 
					);

			}
		}
	}

	return 0;

}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonGetAccounts()
{

	if ( CheckAPI() )
	{
		m_listAccount.DeleteAllItems();
		
		TCHAR account[64];
		TCHAR acctInfo[1024];

		int nCnt = g_iYuantaAPI.YOA_GetAccountCount( );
		for ( int i = 0; i < nCnt; i++ )
		{
			memset( account, 0x00, sizeof(account) );

			if ( RESULT_SUCCESS == g_iYuantaAPI.YOA_GetAccount( i, account, sizeof(account) ) )
			{
				m_listAccount.InsertItem( i, _T("account") );
				m_listAccount.SetItemText( i, 1, AccountFormat(account) );

				memset( acctInfo, 0x00, sizeof(acctInfo) );
				if ( g_iYuantaAPI.YOA_GetAccountInfo( ACCOUNT_INFO_NAME, account, acctInfo, sizeof(acctInfo) ) )
				{
					m_listAccount.SetItemText( i, 2, acctInfo );
				}
			}
		}

		if ( 0 == nCnt )
		{
			LogMessage( "���������� �����ϴ�." );
		}
	}

}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonSearch()
{
	UpdateData();

	m_bStruct = FALSE;

	g_iYuantaAPI.YOA_SetConfig( CONFIG_STRUCT_MODE, 0 );
	g_iYuantaAPI.YOA_SetConfig( CONFIG_REALDATA_BYPASS_MODE, 0 );
	
	TCHAR szJang[101] = {0, };
	// ��ȸTR(DSO) ���� ��� 1 ///////////////////////////////////////////////////////////////////
	g_iYuantaAPI.YOA_GetCodeInfo(MARKET_TYPE_INTERNAL, CODE_INFO_JANG_GUBUN, m_strJongCode, szJang, sizeof(szJang));
	int nResult = g_iYuantaAPI.YOA_SetTRFieldString( "300001", "InBlock1",	"jang", szJang );

	// ���� ó�� - ��ȸTR��, InBlock��, �ʵ���� Ʋ�� ��� ���� ��ȯ�մϴ�. (�����ڵ� CommDef.h ����)
	// ERROR_DSO_NOT_FOUND					202		// DSO�� ã�� �� �����ϴ�.
	// ERROR_BLOCK_NOT_FOUND				203		// ����� ã�� �� �����ϴ�.
	// ERROR_FIELD_NOT_FOUND				204		// �ʵ带 ã�� �� �����ϴ�.
	if ( RESULT_SUCCESS != nResult )
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ʵ尪 ���� ������ ���� �޽����� ���� �� �ֽ��ϴ�.

		AfxMessageBox(msg);
	}

	g_iYuantaAPI.YOA_SetTRFieldString( "300001", "InBlock1", "jongcode",	m_strJongCode );
	g_iYuantaAPI.YOA_SetTRFieldString( "300001", "InBlock1", "outflag",	"N" );
	g_iYuantaAPI.YOA_SetTRFieldString( "300001", "InBlock1", "tsflag",	"0" );
	//////////////////////////////////////////////////////////////////////////////////////////////


	// ��ȸTR(DSO) ���� ��� 2 ///////////////////////////////////////////////////////////////////
	/*
	g_iYuantaAPI.YOA_SetTRInfo( "300001", "InBlock1" );
	g_iYuantaAPI.YOA_SetFieldString( "jang",		"1" );
	g_iYuantaAPI.YOA_SetFieldString( "jongcode",	m_strJongCode );
	g_iYuantaAPI.YOA_SetFieldString( "outflag",	"N" );
	g_iYuantaAPI.YOA_SetFieldString( "tsflag",	"0" );
	*/
	//////////////////////////////////////////////////////////////////////////////////////////////

	m_nReqID_300001 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), "300001" );

	if ( ERROR_MAX_CODE < m_nReqID_300001 )			// ��ȸ ��û ���� ��, ERROR_MAX_CODE(1000)���� ū ���� ���� ��ûID ��ȯ�մϴ�.
	{												// ��ȸ������ �޾���, �����ϴ� ID�� ����մϴ�.
		LogMessage( "[300001]�ֽ����簡 ��ȸ�� ��û�Ͽ����ϴ�." );
	}
	else	// ��ȸ ��û ���� ��, ���� ó��
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( m_nReqID_300001, msg, sizeof(msg) );			// ��ȸ ��û ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonSearch2()
{
	UpdateData();

	m_bStruct = TRUE;
	
	g_iYuantaAPI.YOA_SetConfig( CONFIG_STRUCT_MODE, 1 );
	g_iYuantaAPI.YOA_SetConfig( CONFIG_REALDATA_BYPASS_MODE, 1 );

	DSO300001_InBlock1 inBlock1;
	FillMemory( &inBlock1, sizeof(inBlock1), 0x00 );
	/*
	byte jang = 1;
	char outflag = 'N';
	char tsflag = '0';
	
	CopyMemory( &inBlock1.jang, &jang, sizeof(inBlock1.jang) );
	CopyMemory( &inBlock1.jongcode, m_strJongCode.GetBuffer(0), sizeof(inBlock1.jongcode) );
	CopyMemory( &inBlock1.outflag, &outflag, sizeof(inBlock1.outflag) );
	CopyMemory( &inBlock1.tsflag, &tsflag, sizeof(inBlock1.tsflag) );
	*/

	//g_iYuantaAPI.SetPacketByte( inBlock1.jang, sizeof(inBlock1.jongcode), TYPE_BYTE, jang );
	g_iYuantaAPI.SetPacketString( inBlock1.jang, sizeof(inBlock1.jang), TYPE_BYTE, "1" );
	g_iYuantaAPI.SetPacketString( inBlock1.jongcode, sizeof(inBlock1.jongcode), TYPE_STRING, m_strJongCode );
	g_iYuantaAPI.SetPacketString( inBlock1.outflag, sizeof(inBlock1.outflag), TYPE_STRING, "N" );
	g_iYuantaAPI.SetPacketString( inBlock1.outflag, sizeof(inBlock1.outflag), TYPE_STRING, "0" );

	m_nReqID_300001 = g_iYuantaAPI.YOA_RequestData( GetSafeHwnd(), "300001", (void*)&inBlock1, sizeof(inBlock1) );

	if ( ERROR_MAX_CODE < m_nReqID_300001 )			// ��ȸ ��û ���� ��, ERROR_MAX_CODE(1000)���� ū ���� ���� ��ûID ��ȯ�մϴ�.
	{												// ��ȸ������ �޾���, �����ϴ� ID�� ����մϴ�.
		LogMessage( "[300001]�ֽ����簡 ��ȸ�� ��û�Ͽ����ϴ�." );
	}
	else	// ��ȸ ��û ���� ��, ���� ó��
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( m_nReqID_300001, msg, sizeof(msg) );			// ��ȸ ��û ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonAutoRegist()
{
	UpdateData();

	g_iYuantaAPI.YOA_SetTRFieldString( "11", "InBlock1", "jongcode", m_strJongCode );
	int nResult = g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), "11" );

	if ( ERROR_MAX_CODE < nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( TRUE );

		LogMessage( "[11]�ֽ� �ǽð�ü���� ��� �Ǿ����ϴ�." );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ǽð� ��� ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

void CYOADLLClient_MultiByteDlg::OnBnClickedButtonAutoUnRegist()
{
	int nResult = g_iYuantaAPI.YOA_UnregistAuto( GetSafeHwnd(), "11" );

	if ( RESULT_SUCCESS == nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( FALSE );

		LogMessage( "[11]�ֽ� �ǽð�ü���� ���� �Ǿ����ϴ�." );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ǽð� ���� ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

void CYOADLLClient_MultiByteDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	g_iYuantaAPI.YOA_UnInitial();
}



void CYOADLLClient_MultiByteDlg::OnBnClickedButtonLogout()
{
	g_iYuantaAPI.YOA_UnInitial();
	OnOK();
}
