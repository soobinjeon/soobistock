// BasicTestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "BasicTestDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

// CBasicTestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBasicTestDlg, CDialogEx)

CBasicTestDlg::CBasicTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicTestDlg::IDD, pParent)
	, m_strJongCode(_T(""))
{
	m_pMainDlg = NULL;

	m_nReqID_300001 = -1;
}

CBasicTestDlg::~CBasicTestDlg()
{
}

void CBasicTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JONGCODE, m_strJongCode);
	DDX_Control(pDX, IDC_LIST_LOG, m_lbLog);
}


BEGIN_MESSAGE_MAP(CBasicTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CBasicTestDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_REGIST, &CBasicTestDlg::OnBnClickedButtonAutoRegist)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_UNREGIST, &CBasicTestDlg::OnBnClickedButtonAutoUnRegist)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
END_MESSAGE_MAP()


void CBasicTestDlg::LogMessage( CString strMsg )
{
	m_lbLog.InsertString( 0, strMsg );
}

// BasicTestDlg 메시지 처리기입니다.


void CBasicTestDlg::OnBnClickedButtonSearch()
{
	UpdateData();

	TCHAR szJang[10] = {0, };
	// 조회TR(DSO) 셋팅 방법 1 ///////////////////////////////////////////////////////////////////
	g_iYuantaAPI.YOA_GetCodeInfo(MARKET_TYPE_INTERNAL, CODE_INFO_JANG_GUBUN, m_strJongCode, szJang, sizeof(szJang));
	int nResult = g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"),	_T("jang"), szJang );

	// 오류 처리 - 조회TR명, InBlock명, 필드명이 틀린 경우 오류 반환합니다. (오류코드 CommDef.h 참조)
	// ERROR_DSO_NOT_FOUND					202		// DSO를 찾을 수 없습니다.
	// ERROR_BLOCK_NOT_FOUND				203		// 블록을 찾을 수 없습니다.
	// ERROR_FIELD_NOT_FOUND				204		// 필드를 찾을 수 없습니다.
	if ( RESULT_SUCCESS != nResult )
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// 필드값 설정 오류에 대한 메시지를 얻을 수 있습니다.

		AfxMessageBox(msg);
	}

	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("jongcode"),	m_strJongCode );
	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("outflag"),	_T("N") );
	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("tsflag"),	_T("0") );
	//////////////////////////////////////////////////////////////////////////////////////////////


	// 조회TR(DSO) 셋팅 방법 2 ///////////////////////////////////////////////////////////////////
	/*
	g_iYuantaAPI.YOA_SetTRInfo( _T("300001"), _T("InBlock1") );
	g_iYuantaAPI.YOA_SetFieldString( _T("jang"),	 _T("1") );
	g_iYuantaAPI.YOA_SetFieldString( _T("jongcode"), m_strJongCode );
	g_iYuantaAPI.YOA_SetFieldString( _T("outflag"),	 _T("N") );
	g_iYuantaAPI.YOA_SetFieldString( _T("tsflag"),	 _T("0") );
	*/
	//////////////////////////////////////////////////////////////////////////////////////////////

	m_nReqID_300001 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("300001") );

	if ( ERROR_MAX_CODE < m_nReqID_300001 )			// 조회 요청 성공 시, ERROR_MAX_CODE(1000)보다 큰 수의 고유 요청ID 반환합니다.
	{												// 조회응답을 받았을, 구분하는 ID로 사용합니다.
		LogMessage( _T("[300001]주식현재가 조회를 요청하였습니다.") );
	}
	else	// 조회 요청 실패 시, 오류 처리
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( m_nReqID_300001, msg, sizeof(msg) );			// 조회 요청 실패에 대한 메시지를 얻을 수 있습니다.

		LogMessage(msg);
	}
}


void CBasicTestDlg::OnBnClickedButtonAutoRegist()
{
	UpdateData();

	g_iYuantaAPI.YOA_SetTRFieldString( _T("11"), _T("InBlock1"), _T("jongcode"), m_strJongCode );
	int nResult = g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), _T("11") );

	if ( ERROR_MAX_CODE < nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( TRUE );

		LogMessage( _T("[11]주식 실시간체결이 등록 되었습니다.") );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// 실시간 등록 실패에 대한 메시지를 얻을 수 있습니다.

		LogMessage(msg);
	}
}

void CBasicTestDlg::OnBnClickedButtonAutoUnRegist()
{
	int nResult = g_iYuantaAPI.YOA_UnregistAuto( GetSafeHwnd(), _T("11") );

	if ( RESULT_SUCCESS == nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( FALSE );

		LogMessage( _T("[11]주식 실시간체결이 해지 되었습니다.") );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// 실시간 해지 실패에 대한 메시지를 얻을 수 있습니다.

		LogMessage(msg);
	}
}

LRESULT CBasicTestDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	int nReqID = wParam;

	CString strMsg;
	CString strTrName;

	if ( nReqID == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");
	}	

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:			// 설정된 시간 안에 서버로부터 응답이 없는 경우, 타임아웃이 발생합니다. (기본 10초)
		{
			strMsg.Format( _T("Timeout %s 요청의 응답이 없습니다."), strTrName);
			LogMessage(strMsg);
		}
		break;
	case ERROR_REQUEST_FAIL:			// 서버에서 조회TR(DSO) 처리중 오류가 있는 경우 발생합니다.
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );	// 처리 중 오류에 대한 메시지를 얻을 수 있습니다.
			strMsg.Format( _T("%s\n%s"), strTrName, msg);
			strMsg.TrimRight();
			LogMessage(strMsg);
		}
		break;
	}
	
	return 0;

}

LRESULT CBasicTestDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	//CString strTRID( (LPCTSTR)(LPCSTR)lParam );
	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;

	CString strTrName = _T("");

	if ( wParam == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");

		TCHAR data[1024] = {0,};

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("jongname"), data, sizeof(data) );
		GetDlgItem( IDC_BT_JONGNAME )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("curjuka"), data, sizeof(data) );
		GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

		g_iYuantaAPI.YOA_SetTRInfo( _T("300001"), _T("OutBlock1") );
		g_iYuantaAPI.YOA_GetFieldString( _T("debi"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetFieldString( _T("debirate"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetFieldString( _T("volume"), data, sizeof(data) );
		GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );

		LogMessage( _T("[300001]주식현재가 응답을 수신하였습니다.") );
	}
	else if ( wParam == m_nReqID_160001 )
	{
		TCHAR data[1024] = {0,};

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("160001"), _T("OutBlock1"), _T("org_no"), data, sizeof(data) );
	}

	return 0;

}

LRESULT CBasicTestDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	
	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );
	
	if ( 0 == strAutoID.Compare( _T("11") ) )
	{
		long nData = 0;
		TCHAR data[1024] = {0,};

		//g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("curjuka"), &nData );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("curjuka"), data, sizeof(data) );
		GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("debi"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("debirate"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
		GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );
	}
	else if ( 0 == strAutoID.Compare( _T("71") ) )
	{
		byte gubun48 = 0;
		g_iYuantaAPI.YOA_GetTRFieldByte( _T("71"), _T("OutBlock1"), _T("gubun48"), &gubun48 );

		TCHAR data[1024] = {0,};
		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("custseq"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("origno"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("ordno"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("jumunno"), data, sizeof(data) );

		__int64 cheprcise = 0;
		int nResult = g_iYuantaAPI.YOA_GetTRFieldLong64( _T("71"), _T("OutBlock1"), _T("jumunuv"), &cheprcise );

		if ( ERROR_MAX_CODE < nResult )
		{										

		}
		else	// 조회 요청 실패 시, 오류 처리
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );

			LogMessage(msg);
		}
	}

	return 0;

}
