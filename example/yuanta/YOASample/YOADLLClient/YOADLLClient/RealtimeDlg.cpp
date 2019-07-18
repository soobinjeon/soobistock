// RealtimeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "RealtimeDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

// CRealtimeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRealtimeDlg, CDialog)

CRealtimeDlg::CRealtimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealtimeDlg::IDD, pParent)
{
	m_strAutoID = _T("11");
	m_strInBlockName = _T("InBlock1");
	m_strOutBlockName = _T("OutBlock1");

	m_pMainDlg = NULL;
}

CRealtimeDlg::~CRealtimeDlg()
{
}

void CRealtimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AUTO_IN_BLOCKNAME, m_strInBlockName);
	DDX_Text(pDX, IDC_EDIT_AUTO_IN_FIELDNAME, m_strInFieldName);
	DDX_Text(pDX, IDC_EDIT_AUTO_IN_FIELDVALUE, m_strInFieldValue);
	DDX_Text(pDX, IDC_EDIT_AUTO_OUT_BLOCKNAME, m_strOutBlockName);
	DDX_Text(pDX, IDC_EDIT_AUTO_OUT_FIELDNAME, m_strOutFieldName);
	DDX_Text(pDX, IDC_EDIT_IN_AUTONO, m_strAutoID);
	DDX_Control(pDX, IDC_LIST_AUTO_INBLOCK, m_ctrlInBlocks);
	DDX_Control(pDX, IDC_LIST_AUTO_OUTBLOCK, m_ctrlOutBlocks);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlLog);
}


BEGIN_MESSAGE_MAP(CRealtimeDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_INIT, &CRealtimeDlg::OnBnClickedButtonAutoInit)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_REGIST, &CRealtimeDlg::OnBnClickedButtonAutoRegist)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_UNREGIST, &CRealtimeDlg::OnBnClickedButtonAutoUnregist)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_IN_ADD, &CRealtimeDlg::OnBnClickedButtonAutoInAdd)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_IN_DEL, &CRealtimeDlg::OnBnClickedButtonAutoInDel)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_OUT_ADD, &CRealtimeDlg::OnBnClickedButtonAutoOutAdd)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_OUT_DEL, &CRealtimeDlg::OnBnClickedButtonAutoOutDel)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
END_MESSAGE_MAP()

void CRealtimeDlg::InitControl()
{
	m_ctrlInBlocks.SetExtendedStyle( m_ctrlInBlocks.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInBlocks.SetExtendedStyle( m_ctrlInBlocks.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_ctrlInBlocks.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlInBlocks.InsertColumn(1, _T("블록명"), LVCFMT_CENTER,	95);
	m_ctrlInBlocks.InsertColumn(2, _T("필드명"), LVCFMT_CENTER,	120);
	m_ctrlInBlocks.InsertColumn(3, _T("필드값"), LVCFMT_CENTER,	120);

	m_ctrlOutBlocks.SetExtendedStyle( m_ctrlOutBlocks.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlOutBlocks.SetExtendedStyle( m_ctrlOutBlocks.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_ctrlOutBlocks.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlOutBlocks.InsertColumn(1, _T("블록명"), LVCFMT_CENTER,	95);
	m_ctrlOutBlocks.InsertColumn(2, _T("필드명"), LVCFMT_CENTER,	120);
	m_ctrlOutBlocks.InsertColumn(3, _T("필드값"), LVCFMT_CENTER,	120);
}

void CRealtimeDlg::SetSample()
{
	m_ctrlInBlocks.InsertItem( 0, _T("Block") );
	m_ctrlInBlocks.SetItemText( 0, 0, _T("InBlock1") );
	m_ctrlInBlocks.SetItemText( 0, 1, _T("InBlock1") );

	m_ctrlInBlocks.InsertItem( 1, _T("Field") );
	m_ctrlInBlocks.SetItemText( 1, 0, _T("InBlock1") );
	m_ctrlInBlocks.SetItemText( 1, 2, _T("jongcode") );
	m_ctrlInBlocks.SetItemText( 1, 3, _T("005930") );

	m_ctrlOutBlocks.InsertItem( 0, _T("Block") );
	m_ctrlOutBlocks.SetItemText( 0, 0, _T("OutBlock1") );
	m_ctrlOutBlocks.SetItemText( 0, 1, _T("OutBlock1") );

	m_ctrlOutBlocks.InsertItem( 1, _T("Field") );
	m_ctrlOutBlocks.SetItemText( 1, 0, _T("OutBlock1") );
	m_ctrlOutBlocks.SetItemText( 1, 2, _T("jongcode") );

	m_ctrlOutBlocks.InsertItem( 2, _T("Field") );
	m_ctrlOutBlocks.SetItemText( 2, 0, _T("OutBlock1") );
	m_ctrlOutBlocks.SetItemText( 2, 2, _T("curjuka") );
}

BOOL CRealtimeDlg::CheckAPI()
{
	if ( NULL == m_pMainDlg )
		return FALSE;

	return m_pMainDlg->CheckAPI();
}

// CRealtimeDlg 메시지 처리기입니다.

BOOL CRealtimeDlg::PreTranslateMessage(MSG* pMsg)
{
	if ( WM_KEYDOWN == pMsg->message )
	{
		if ( VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam )
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CRealtimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();
	SetSample();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT CRealtimeDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
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

LRESULT CRealtimeDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );

	CString strLog;
	CTime date = CTime::GetCurrentTime();

	strLog.Format( _T("[%d-%02d-%02d %02d:%02d:%02d] 실시간[%s] 수신"), 
		date.GetYear(), date.GetMonth(), date.GetDay(), 
		date.GetHour(), date.GetMinute(), date.GetSecond(), strAutoID);

	m_ctrlLog.InsertString( 0, strLog );

	if ( 100 < m_ctrlLog.GetCount() )
	{
		for ( int i = 100; i < 50; i-- )
			m_ctrlLog.DeleteString( i );
	}

	if ( strAutoID == m_strAutoID )
	{
		TCHAR data[1024];

		CString strTemp;
		CString strBlock;
		CString strField;
		CString strValue;
		CString strIndex;
		int nIndex;

		int nRowCnt = m_ctrlOutBlocks.GetItemCount();
		for ( int nRow = 0; nRow < nRowCnt; nRow++ )
		{
			strTemp = m_ctrlOutBlocks.GetItemText(nRow, 1);

			if ( !strTemp.IsEmpty() )
			{
				strBlock = strTemp;
			}
			else
			{
				memset( data, 0x00, sizeof(data) );
				strField = m_ctrlOutBlocks.GetItemText(nRow, 2);
				nIndex = _ttoi( m_ctrlOutBlocks.GetItemText(nRow, 4) );

				g_iYuantaAPI.YOA_GetTRFieldString( m_strAutoID, strBlock, strField, data, sizeof(data), nIndex );

				m_ctrlOutBlocks.SetItemText( nRow, 3, data );
			}
		}
	}

	return ret;
}

void CRealtimeDlg::OnBnClickedButtonAutoInit()
{
	m_ctrlInBlocks.DeleteAllItems();
	m_ctrlOutBlocks.DeleteAllItems();

	m_strAutoID			= _T("");
	m_strInBlockName	= _T("InBlock1");
	m_strInFieldName	= _T("");
	m_strInFieldValue	= _T("");
	m_strOutBlockName	= _T("OutBlock1");
	m_strOutFieldName	= _T("");

	UpdateData(FALSE);
}

void CRealtimeDlg::OnBnClickedButtonAutoRegist()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();
		
		CString strTemp;
		CString strBlock;
		CString strField;
		CString strValue;

		int nRowCnt = m_ctrlInBlocks.GetItemCount();
		for ( int nRow = 0; nRow < nRowCnt; nRow++ )
		{
			strTemp = m_ctrlInBlocks.GetItemText(nRow, 1);

			if ( !strTemp.IsEmpty() )
			{
				strBlock = strTemp;
			}
			else
			{
				strField = m_ctrlInBlocks.GetItemText(nRow, 2);
				strValue = m_ctrlInBlocks.GetItemText(nRow, 3);

				if ( FALSE == g_iYuantaAPI.YOA_SetTRFieldString( m_strAutoID, strBlock, strField, strValue, 0 ) )
				{
					TCHAR msg[1024] = {0,};

					int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
					g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

					CString strErrorMsg;
					strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

					m_pMainDlg->LogMessage( _T("[") + strField + _T("] 필드 값 설정중 오류가 발생하였습니다."), 1 );
					m_pMainDlg->LogMessage( strErrorMsg );

					return;
				}
			}
		}
		
		if ( 0 < nRowCnt )
		{
			if ( g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), m_strAutoID ) )
			{
				m_pMainDlg->LogMessage( _T("AUTO[") + m_strAutoID + _T("]가 정상 등록되었습니다.") );
			}
			else
			{
				TCHAR msg[1024] = {0,};

				int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

				m_pMainDlg->LogMessage( _T("[") + m_strAutoID + _T("] AUTO 등록중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg );
			}
		}
		
	}
}

void CRealtimeDlg::OnBnClickedButtonAutoUnregist()
{
	if ( TRUE == CheckAPI() )
	{
		if ( g_iYuantaAPI.YOA_UnregistAutoWithWindow( GetSafeHwnd() ) )
		{
			m_pMainDlg->LogMessage( _T("실시간테스트에서 등록한 모든 AUTO가 정상 해지되었습니다.") );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			m_pMainDlg->LogMessage( _T("실시간테스트에서 등록한 AUTO 해지중 오류가 발생하였습니다."), 1 );
			m_pMainDlg->LogMessage( strErrorMsg );
		}
	}
}

void CRealtimeDlg::OnBnClickedButtonAutoInAdd()
{
	UpdateData();

	BOOL bFindBlock = FALSE;
	CString strTemp;

	int nRowCnt = m_ctrlInBlocks.GetItemCount();
	for ( int nRow = 0; nRow < nRowCnt; nRow++ )
	{
		strTemp = m_ctrlInBlocks.GetItemText(nRow, 0);

		if ( strTemp == m_strInBlockName )
		{
			bFindBlock = TRUE;
		}
		else
		{
			if ( TRUE == bFindBlock )
			{
				m_ctrlInBlocks.InsertItem( nRow, _T("Field") );
				m_ctrlInBlocks.SetItemText( nRow, 0, m_strInBlockName );
				m_ctrlInBlocks.SetItemText( nRow, 2, m_strInFieldName );
				m_ctrlInBlocks.SetItemText( nRow, 3, m_strInFieldValue );

				break;
			}
		}
	}

	int nRow = nRowCnt;

	if ( FALSE == bFindBlock )
	{
		m_ctrlInBlocks.InsertItem( nRow, _T("Block") );
		m_ctrlInBlocks.SetItemText( nRow, 0, m_strOutBlockName );
		m_ctrlInBlocks.SetItemText( nRow, 1, m_strOutBlockName );

		nRow++;
		m_ctrlInBlocks.InsertItem( nRow, _T("Field") );
		m_ctrlInBlocks.SetItemText( nRow, 0, m_strOutBlockName );
		m_ctrlInBlocks.SetItemText( nRow, 2, m_strOutFieldName );
		m_ctrlInBlocks.SetItemText( nRow, 3, m_strInFieldValue );
	}
	else if ( TRUE == bFindBlock )
	{
		m_ctrlInBlocks.InsertItem( nRow, _T("Field") );
		m_ctrlInBlocks.SetItemText( nRow, 0, m_strInBlockName );
		m_ctrlInBlocks.SetItemText( nRow, 2, m_strInFieldName );
		m_ctrlInBlocks.SetItemText( nRow, 3, m_strInFieldValue );
	}
}


void CRealtimeDlg::OnBnClickedButtonAutoInDel()
{
	int nSelRow = m_ctrlInBlocks.GetSelectionMark();

	CString strTemp = m_ctrlInBlocks.GetItemText( nSelRow, 1 );

	if ( -1 == strTemp.Find(_T("InBlock"), 0) )
	{
		m_ctrlInBlocks.DeleteItem( nSelRow );
	}
	else
	{
		CString strBlockName = strTemp;

		int nRowCnt = m_ctrlInBlocks.GetItemCount();
		for ( int nRow = nRowCnt- 1; nRow >= 0; nRow-- )
		{
			strTemp = m_ctrlInBlocks.GetItemText(nRow, 0);

			if ( strBlockName == strTemp )
			{
				m_ctrlInBlocks.DeleteItem( nRow );
			}
		}
	}
}


void CRealtimeDlg::OnBnClickedButtonAutoOutAdd()
{
	UpdateData();

	BOOL bFindBlock = FALSE;
	CString strTemp;

	int nRowCnt = m_ctrlOutBlocks.GetItemCount();
	for ( int nRow = 0; nRow < nRowCnt; nRow++ )
	{
		strTemp = m_ctrlOutBlocks.GetItemText(nRow, 0);

		if ( strTemp == m_strOutBlockName )
		{
			bFindBlock = TRUE;
		}
		else
		{
			if ( TRUE == bFindBlock )
			{
				m_ctrlOutBlocks.InsertItem( nRow, _T("Field") );
				m_ctrlOutBlocks.SetItemText( nRow, 0, m_strOutBlockName );
				m_ctrlOutBlocks.SetItemText( nRow, 2, m_strOutFieldName );

				break;
			}
		}
	}

	int nRow = nRowCnt;

	if ( FALSE == bFindBlock )
	{
		m_ctrlOutBlocks.InsertItem( nRow, _T("Block") );
		m_ctrlOutBlocks.SetItemText( nRow, 0, m_strOutBlockName );
		m_ctrlOutBlocks.SetItemText( nRow, 1, m_strOutBlockName );

		nRow++;
		m_ctrlOutBlocks.InsertItem( nRow, _T("Field") );
		m_ctrlOutBlocks.SetItemText( nRow, 0, m_strOutBlockName );
		m_ctrlOutBlocks.SetItemText( nRow, 2, m_strOutFieldName );
	}
	else if ( TRUE == bFindBlock )
	{
		m_ctrlOutBlocks.InsertItem( nRow, _T("Field") );
		m_ctrlOutBlocks.SetItemText( nRow, 0, m_strOutBlockName );
		m_ctrlOutBlocks.SetItemText( nRow, 2, m_strOutFieldName );
	}
}


void CRealtimeDlg::OnBnClickedButtonAutoOutDel()
{
	int nSelRow = m_ctrlOutBlocks.GetSelectionMark();

	CString strTemp = m_ctrlOutBlocks.GetItemText( nSelRow, 1 );

	if ( -1 == strTemp.Find(_T("OutBlock"), 0) )
	{
		m_ctrlOutBlocks.DeleteItem( nSelRow );
	}
	else
	{
		CString strBlockName = strTemp;

		int nRowCnt = m_ctrlOutBlocks.GetItemCount();
		for ( int nRow = nRowCnt- 1; nRow >= 0; nRow-- )
		{
			strTemp = m_ctrlOutBlocks.GetItemText(nRow, 0);

			if ( strBlockName == strTemp )
			{
				m_ctrlOutBlocks.DeleteItem( nRow );
			}
		}
	}
}

