
// YOADLLClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "YOADLLClientDlg.h"
#include "afxdialogex.h"

#include "../../include/MessageDef.h"
#include "BasicTestDlg.h"
#include "StockSiseDlg.h"
#include "StockOrderDlg.h"
#include "StockAccountDlg.h"
#include "TransactionDlg.h"
#include "RealtimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DRAWITEM()
	
END_MESSAGE_MAP()


// CYOADLLClientDlg 대화 상자

CYOADLLClientDlg::CYOADLLClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYOADLLClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pBasicTestDlg		= NULL;
	m_pStockSiseDlg		= NULL;
	m_pStockOrderDlg			= NULL;
	m_pStockAccountDlg	= NULL;
	m_pTransactionDlg	= NULL;
	m_pRealtimeDlg		= NULL;
}

void CYOADLLClientDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_TAB_PANEL, m_ctrlTab);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_cbServer);
}

BEGIN_MESSAGE_MAP(CYOADLLClientDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WMU_RECEIVE_SYSTEM_MESSAGE, OnReceiveSystemMessage)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_LOGIN, OnLoginComplete)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, &CYOADLLClientDlg::OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CYOADLLClientDlg::OnBnClickedButtonLogin)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PANEL, &CYOADLLClientDlg::OnTcnSelchangeTabPanel)
	ON_BN_CLICKED(IDC_BUTTON_GET_ACCOUNTS, &CYOADLLClientDlg::OnBnClickedButtonGetAccounts)
END_MESSAGE_MAP()


void CYOADLLClientDlg::LogMessage(CString strMsg, int nType /* = 0 */, BOOL bTimeStamp /* = TRUE */)
{
	CString strLog;

	if ( TRUE == bTimeStamp )
	{
		CTime date = CTime::GetCurrentTime();

		if ( 0 == nType )
			strLog.Format( _T("[LOG:%d-%02d-%02d %02d:%02d:%02d] %s"), 
							date.GetYear(), date.GetMonth(), date.GetDay(), 
							date.GetHour(), date.GetMinute(), date.GetSecond(),
							strMsg);
		else if ( 1 == nType )
			strLog.Format( _T("[ERR:%d-%02d-%02d %02d:%02d:%02d] %s"), 
			date.GetYear(), date.GetMonth(), date.GetDay(), 
			date.GetHour(), date.GetMinute(), date.GetSecond(),
			strMsg);
	}
	else
	{
		strLog.Format( _T("[ERR_MSG] %s"), strMsg);
	}

	m_lbLog.AddString( strLog );
}

void CYOADLLClientDlg::InitControl()
{
	m_cbServer.AddString( _T("국내 모의투자") );
	m_cbServer.AddString( _T("국내/해외주식 운영서버") );
	m_cbServer.AddString( _T("해외선물옵션 모의투자") );
	m_cbServer.AddString( _T("해외선물옵션 운영서버") );
	m_cbServer.SetCurSel(0);

	m_listAccount.SetExtendedStyle( m_listAccount.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_listAccount.SetExtendedStyle( m_listAccount.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_listAccount.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_listAccount.InsertColumn(1, _T("계좌번호"), LVCFMT_CENTER, 150);
	m_listAccount.InsertColumn(2, _T("계좌명"), LVCFMT_CENTER, 125);

	m_ctrlTab.InsertItem(0, _T("기본테스트"));
	m_ctrlTab.InsertItem(1, _T("주식현재가"));
	m_ctrlTab.InsertItem(2, _T("주식주문"));
	m_ctrlTab.InsertItem(3, _T("주식계좌"));
	m_ctrlTab.InsertItem(4, _T("조회테스트"));
	m_ctrlTab.InsertItem(5, _T("실시간테스트"));
	

	CRect rcTab;
	m_ctrlTab.GetWindowRect( &rcTab );
	m_ctrlTab.ScreenToClient( &rcTab );

	m_pBasicTestDlg = new CBasicTestDlg;
	m_pBasicTestDlg->Create( IDD_BASICTEST_DIALOG, &m_ctrlTab );
	m_pBasicTestDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pBasicTestDlg->ShowWindow( SW_SHOW );
	m_pBasicTestDlg->SetMainDlg( this );

	m_pStockSiseDlg = new CStockSiseDlg;
	m_pStockSiseDlg->Create( IDD_STOCKSISE_DIALOG, &m_ctrlTab );
	m_pStockSiseDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pStockSiseDlg->ShowWindow( SW_HIDE );
	m_pStockSiseDlg->SetMainDlg( this );

	m_pStockOrderDlg = new CStockOrderDlg;
	m_pStockOrderDlg->Create( IDD_STOCKORDER_DIALOG, &m_ctrlTab );
	m_pStockOrderDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pStockOrderDlg->ShowWindow( SW_HIDE );
	m_pStockOrderDlg->SetMainDlg( this );

	m_pStockAccountDlg = new CStockAccountDlg;
	m_pStockAccountDlg->Create( IDD_STOCKACCOUNT_DIALOG, &m_ctrlTab );
	m_pStockAccountDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pStockAccountDlg->ShowWindow( SW_HIDE );
	m_pStockAccountDlg->SetMainDlg( this );
	
	m_pTransactionDlg = new CTransactionDlg;
	m_pTransactionDlg->Create( IDD_TRANSACTION_DIALOG, &m_ctrlTab );
	m_pTransactionDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pTransactionDlg->ShowWindow( SW_HIDE );
	m_pTransactionDlg->SetMainDlg( this );

	m_pRealtimeDlg = new CRealtimeDlg;
	m_pRealtimeDlg->Create( IDD_REALTIME_DIALOG, &m_ctrlTab );
	m_pRealtimeDlg->MoveWindow( rcTab.left + 10, rcTab.top + 30, rcTab.Width() - 20, rcTab.Height() - 40 );
	m_pRealtimeDlg->ShowWindow( SW_HIDE );
	m_pRealtimeDlg->SetMainDlg( this );
}

CString CYOADLLClientDlg::AccountFormat( TCHAR* pData )
{
	CString strResult( pData );

	int nLen = strResult.GetLength();
	if ( 1 == nLen % 2 )
	{
		strResult.Insert(5, _T("-"));
		strResult.Insert(3, _T("-"));
	}
	else
	{
		strResult.Insert(8, _T("-"));
		strResult.Insert(4, _T("-"));
	}

	return strResult;
}

CString CYOADLLClientDlg::Commify( TCHAR* pData )
{
	CString strResult( pData );

	int nIndex = 1;

	int nCheck = strResult.ReverseFind( '.' );
	int nStart = ( -1 == nCheck ? strResult.GetLength() : nCheck ) - 1;
	int nEnd = 1;
	if ( 0 < strResult.GetLength() )
	{
		if ( !('0' < strResult[0] || '9' < strResult[0]) )
			nEnd = 2;
	}

	for ( int i = nStart; i >= nEnd; i-- )
	{
		if ( 0 == (nIndex % 3) )
		{
			strResult.Insert( i, _T(",") );
			nIndex = 1;
		}
		else
		{
			nIndex++;
		}
	}

	return strResult;
}

CString CYOADLLClientDlg::Commify( long nData )
{
	CString strData;
	strData.Format( _T("%d"), nData );
	return Commify( strData.GetBuffer(0) );
}

CString CYOADLLClientDlg::Commify( double dData )
{
	CString strData;
	strData.Format( _T("%0.2f"), dData );
	return Commify( strData.GetBuffer(0) );
}

BOOL CYOADLLClientDlg::CheckAPI()
{
	return CheckInit() && CheckLogin();
}

BOOL CYOADLLClientDlg::CheckInit()
{
	if ( FALSE == g_bInitial )
	{
		LogMessage( _T("유안타 Open API 초기화가 필요합니다."), 1 );
	}
	
	return g_bInitial;
}

BOOL CYOADLLClientDlg::CheckLogin()
{
	if ( FALSE == g_bLogin )
	{
		LogMessage( _T("로그인이 필요합니다."), 1 );
	}

	return g_bLogin;
}

// CYOADLLClientDlg 메시지 처리기

BOOL CYOADLLClientDlg::PreTranslateMessage(MSG* pMsg)
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

void CYOADLLClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	g_iYuantaAPI.YOA_UnInitial();
		
	if ( NULL != m_pBasicTestDlg )
	{
		m_pBasicTestDlg->DestroyWindow();
		delete m_pBasicTestDlg;
	}

	if ( NULL != m_pStockSiseDlg )
	{
		m_pStockSiseDlg->DestroyWindow();
		delete m_pStockSiseDlg;
	}

	if ( NULL != m_pStockOrderDlg )
	{
		m_pStockOrderDlg->DestroyWindow();
		delete m_pStockOrderDlg;
	}

	if ( NULL != m_pStockAccountDlg )
	{
		m_pStockAccountDlg->DestroyWindow();
		delete m_pStockAccountDlg;
	}

	if ( NULL != m_pTransactionDlg )
	{
		m_pTransactionDlg->DestroyWindow();
		delete m_pTransactionDlg;
	}

	if ( NULL != m_pRealtimeDlg )
	{
		m_pRealtimeDlg->DestroyWindow();
		delete m_pRealtimeDlg;
	}

	//return CDialogEx::DestroyWindow();
	
}


BOOL CYOADLLClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	InitControl();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CYOADLLClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CYOADLLClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CYOADLLClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CYOADLLClientDlg::OnBnClickedButtonInitial()
{

	m_btnInitial.EnableWindow( FALSE );
	
	int nCurSel = m_cbServer.GetCurSel();
	CString strServer = _T("simul.tradar.api.com");
	if ( 1 == nCurSel )
		strServer = _T("real.tradar.api.com");
	else if ( 2 == nCurSel )
		strServer = _T("simul.tradarglobal.api.com");
	else if ( 3 == nCurSel )
		strServer = _T("real.tradarglobal.api.com");

	//if ( RESULT_SUCCESS == g_iYuantaAPI.YOA_Initial( strServer, GetSafeHwnd(), NULL, WMU_STARTMSGID ) )
	if ( RESULT_SUCCESS == g_iYuantaAPI.YOA_Initial( strServer, GetSafeHwnd(), _T("C:\\YuantaAPI"), WMU_STARTMSGID ) )
	{
		if ( 0 == nCurSel || 2 == nCurSel )
			AfxMessageBox( _T("모의투자로 접속합니다.\n모의투자의 계좌비밀번호는 0000입니다.") );

		LogMessage( _T("유안타 Open API가 초기화되었습니다.") );

		g_bInitial = TRUE;
		m_btnLogin.EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_LOGIN_ID )->SetFocus();
	}
	else
	{
		LogMessage( _T("유안타 Open API가 초기화에 실패하였습니다."), 1 );
		m_btnInitial.EnableWindow( TRUE );

		return;
	}
		
}


void CYOADLLClientDlg::OnBnClickedButtonLogin()
{

	if ( CheckInit() )
	{
		m_btnLogin.EnableWindow( FALSE );

		UpdateData();

		long nResult = g_iYuantaAPI.YOA_Login( GetSafeHwnd(), m_strLoginID, m_strLoginPwd, m_strCertPwd );
		if ( RESULT_SUCCESS == nResult )
		{
			LogMessage( _T("로그인 요청이 되었습니다.") );
		}
		else
		{
			LogMessage( _T("로그인 요청이 실패하였습니다."), 1 );
			TCHAR msg[2048] = {0,};

			g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );
			LogMessage( msg, 1, FALSE );

			m_btnLogin.EnableWindow( TRUE );
		}
	}

}

LRESULT CYOADLLClientDlg::OnReceiveSystemMessage(WPARAM wParam, LPARAM lParam)
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

LRESULT CYOADLLClientDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	int nReqID = wParam;

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:
		break;
	}

	return ret;

}

LRESULT CYOADLLClientDlg::OnLoginComplete(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;
	
	if ( RESPONSE_LOGIN_SUCCESS == wParam )
	{
		LogMessage( _T("로그인이 완료되었습니다.") );
		m_btnLogout.EnableWindow( TRUE );
		m_btnGetAcctList.EnableWindow( TRUE );

		g_bLogin = TRUE;
	
	}
	else if ( RESPONSE_LOGIN_FAIL == wParam )
	{
		if ( ERROR_TIMEOUT_DATA == lParam )
		{
			LogMessage( _T("로그인이 실패하였습니다."), 1 );
			LogMessage( _T("서버로부터 로그인 응답이 없습니다. 다시 시도하여 주십시오."), 1, FALSE );
		}
		else
		{
			LogMessage( _T("로그인이 실패하였습니다."), 1 );

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

LRESULT CYOADLLClientDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	int nReqID = wParam;

	CString strValue;
	if ( m_mapReqID.Lookup( nReqID, strValue ) )
	{
		
	}

	return ret;

}

void CYOADLLClientDlg::OnTcnSelchangeTabPanel(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_ctrlTab.GetCurSel();

	m_pBasicTestDlg->ShowWindow( SW_HIDE );
	m_pStockSiseDlg->ShowWindow( SW_HIDE );
	m_pStockOrderDlg->ShowWindow( SW_HIDE );
	m_pStockAccountDlg->ShowWindow( SW_HIDE );
	m_pTransactionDlg->ShowWindow( SW_HIDE );
	m_pRealtimeDlg->ShowWindow( SW_HIDE );
	

	if ( 0 == nCurSel )
		m_pBasicTestDlg->ShowWindow( SW_SHOW );
	else if ( 1 == nCurSel )
		m_pStockSiseDlg->ShowWindow( SW_SHOW );
	else if ( 2 == nCurSel )
	{
		
		if ( 0 == m_listAccount.GetItemCount() )
		{
			if ( IDOK == AfxMessageBox( _T("계좌정보가 없습니다.\n계좌가져오기를 하시겠습니까?"), MB_OKCANCEL ) )
			{
				OnBnClickedButtonGetAccounts();
			}
		}
		
		m_pStockOrderDlg->ShowWindow( SW_SHOW );
	}
	else if ( 3 == nCurSel )
	{
		
		if ( 0 == m_listAccount.GetItemCount() )
		{
			if ( IDOK == AfxMessageBox( _T("계좌정보가 없습니다.\n계좌가져오기를 하시겠습니까?"), MB_OKCANCEL ) )
			{
				OnBnClickedButtonGetAccounts();
			}
		}
		
		m_pStockAccountDlg->ShowWindow( SW_SHOW );
	}
	else if ( 4 == nCurSel )
		m_pTransactionDlg->ShowWindow( SW_SHOW );
	else if ( 5 == nCurSel )
		m_pRealtimeDlg->ShowWindow( SW_SHOW );

	*pResult = 0;
}


void CYOADLLClientDlg::OnBnClickedButtonGetAccounts()
{
	
	if ( CheckAPI() )
	{
		m_listAccount.DeleteAllItems();
		if ( NULL != m_pStockOrderDlg )
		{
			m_pStockOrderDlg->InitAccount();
		}

		if ( NULL != m_pStockAccountDlg )
		{
			m_pStockAccountDlg->InitAccount();
		}

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

					if ( NULL != m_pStockOrderDlg )
					{
						m_pStockOrderDlg->AddAccount( account, acctInfo );
					}

					if ( NULL != m_pStockAccountDlg )
					{
						m_pStockAccountDlg->AddAccount( account, acctInfo );
					}
				}
			}
		}

		if ( 0 == nCnt )
		{
			LogMessage( _T("계좌정보가 없습니다.") );
		}
	}

}


void CYOADLLClientDlg::LoadUserInfo()
{
	TCHAR pszCurDirectory[1204];
	memset(pszCurDirectory, 0x00, sizeof(pszCurDirectory));
	DWORD dwRet = ::GetModuleFileName(NULL, pszCurDirectory, sizeof(pszCurDirectory)/*1024*/);
	CString path = pszCurDirectory;
	int iFind = path.ReverseFind('\\');

	if (iFind < 0)
	{
		return;
	}

	path = path.Mid(0, iFind + 1);
	path += _T("\\testlogin.ini");


	TCHAR temp[1024];
	memset(temp, 0x00, sizeof(temp));
	GetPrivateProfileString(_T("TEST_INFO"), _T("ID"), _T(""), temp, sizeof(temp), path);
	m_strLoginID = temp;

	memset(temp, 0x00, sizeof(temp));
	GetPrivateProfileString(_T("TEST_INFO"), _T("PWD"), _T(""), temp, sizeof(temp), path);
	m_strLoginPwd = temp;

	memset(temp, 0x00, sizeof(temp));
	GetPrivateProfileString(_T("TEST_INFO"), _T("CERT_PWD"), _T(""), temp, sizeof(temp), path);
	m_strCertPwd = temp;
	m_strCertPwd.Remove('2');
	
	UpdateData(FALSE);

	if ( 0 < m_strLoginID.GetLength() && 0 < m_strLoginPwd.GetLength() && 0 < m_strCertPwd.GetLength() )
		OnBnClickedButtonLogin();
}
