#ifndef _YOACOMMONDEF_H_
#define _YOACOMMONDEF_H_

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	�α�Ÿ���ڵ�
*/
#define		YOALOG_TRAACE									0
#define		YOALOG_ERROR									1
#define		YOALOG_DEBUG									2

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	��ȯ/�����ڵ�
*/
#define 	RESULT_FAIL										-1		// API ���� ��ȯ �ڵ�
#define 	RESULT_SUCCESS									1000	// API ���� ��ȯ �ڵ�
#define 	RESPONSE_LOGIN_FAIL								1		// �α��� ���� �ڵ�
#define 	RESPONSE_LOGIN_SUCCESS							2		// �α��� ���� �ڵ�

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	�����ڵ�
*/
#define		ERROR_MODULE_NOT_FOUND							11		// Yuanta Open API ����� ã�� �� �����ϴ�.
#define		ERROR_FUNCTION_NOT_FOUND						12		// Yuanta Open API �Լ��� ã�� �� �����ϴ�.
#define		ERROR_NOT_INITIAL								13		// Yuanta Open API �ʱ�ȭ ���°� �ƴմϴ�.

#define		ERROR_SYSTEM_START								19
#define		ERROR_SYSTEM_CERT_ERROR							20		// ���������Դϴ�.
#define		ERROR_SYSTEM_MAX_CON							21		// ���������ѵ� �ʰ��Դϴ�.
#define		ERROR_SYSTEM_FORCE_KILL							22		// ��Ʈ��ũ ������ ������ ���� ����Ǿ����ϴ�.
#define		ERROR_SYSTEM_EMERGENCY							23		// �ý��� ��� ��Ȳ�Դϴ�.
#define		ERROR_SYSTEM_INFINIT_CALL						24		// �̻� ȣ��� ������ ����˴ϴ�.
#define		ERROR_SYSTEM_SOCKET_CLOSE						25		// ��Ʈ�� ������ ���������ϴ�.
#define		ERROR_SYSTEM_END								99

#define		ERROR_NOT_LOGINED								101		// �α��� ���°� �ƴմϴ�.
#define		ERROR_ALREADY_LOGINED							102		// �̹� �α��ε� �����Դϴ�.
#define		ERROR_INDEX_OUT_OF_BOUNDS						103		// �ε����� ��������� �Ѿ����ϴ�.
#define		ERROR_TIMEOUT_DATA								104		// Ÿ�Ӿƿ��� �߻��Ͽ����ϴ�.
#define		ERROR_USERINFO_NOT_FOUND						105		// ����� ������ ã�� �� �����ϴ�.
#define		ERROR_ACCOUNT_NOT_FOUND							106		// ���¹�ȣ�� ã�� �� �����ϴ�.
#define		ERROR_ACCOUNT_PASSWORD_INCORRECT				107		// ���� ��й�ȣ�� �߸� �Է��ϼ̽��ϴ�.
#define		ERROR_TYPE_NOT_FOUND							108		// ��û�� Ÿ���� ã�� �� �����ϴ�.

#define		ERROR_CERT_PASSWORD_INCORRECT					110		// �������� ��й�ȣ�� ��ġ���� �ʽ��ϴ�.
#define		ERROR_CERT_NOT_FOUND							111		// ������������ ã�� �� �����ϴ�.
#define		ERROR_CETT_CANCEL_SELECT						112		// ���������� ������ ����߽��ϴ�.
#define		ERROR_NEED_TO_UPDATE							113		// �������� ������Ʈ�� �ʿ��մϴ�.
#define		ERROR_CERT_7_ERROR								114		// �������� 7ȸ �����Դϴ�.
#define		ERROR_ID_PASSWORD_INCORRECT						115		// �α��� ��й�ȣ ��й�ȣ�� ��ġ���� �ʽ��ϴ�.
#define		ERROR_CERT_PASSWORD_SHORT						116		// ���������� ��й�ȣ�� �ּұ��̺��� ª���ϴ�.
#define		ERROR_ID_SHORT									117		// �α��� ���̵� �ּұ��̺��� ª���ϴ�.
#define		ERROR_ID_PASSWORD_SHORT							118		// �α��� ��й�ȣ�� �ּұ��̺��� ª���ϴ�.
#define		ERROR_CERT_DIFF_CERT_SELECT						119		// ���������� DN�� ��ġ���� �ʽ��ϴ�.

#define		ERROR_CERT_OLD									121		// ���� ������ �Դϴ�.
#define		ERROR_CERT_TIME_OVER							122		// ����� ������ �Դϴ�.
#define		ERROR_CERT_STOP									123		// ������ ������ �Դϴ�.
#define		ERROR_CERT_NOTMATCH_SN							124		// SN�� ��ġ���� �ʴ� �������Դϴ�.
#define		ERROR_CERT_ETC									125		// ��Ÿ���� �������Դϴ�.
#define		ERROR_CERT_TIME_OUT								126		// Ÿ������� �߱� ������ �������� Ÿ�Ӿƿ��� �߻��Ͽ����ϴ�. �ٽ� �õ��� �ֽʽÿ�

#define		ERROR_REQUEST_FAIL								201		// DSO ��û�� �����Ͽ����ϴ�.
#define		ERROR_DSO_NOT_FOUND								202		// DSO�� ã�� �� �����ϴ�.
#define		ERROR_BLOCK_NOT_FOUND							203		// ����� ã�� �� �����ϴ�..
#define		ERROR_FIELD_NOT_FOUND							204		// �ʵ带 ã�� �� �����ϴ�.
#define		ERROR_REQUEST_NOT_FOUND							205		// ��û ������ ã�� �� �����ϴ�.
#define		ERROR_ATTR_NOT_FOUND							206		// �ʵ��� �Ӽ��� ã�� �� �����ϴ�.
#define		ERROR_REGIST_FAIL								207		// AUTO ����� �����Ͽ����ϴ�.
#define		ERROR_AUTO_NOT_FOUND							208		// AUTO�� ã�� �� �����ϴ�.
#define		ERROR_KEY_NOT_FOUND								209		// ��û�� Ű�� ã�� �� �����ϴ�.
#define		ERROR_VALUE_NOT_FOUND							210		// ��û�� ���� ã�� �� �����ϴ�.
#define		ERROR_REQUEST_SEC_LIMIT_OVER					211		// ��û ī��Ʈ 5�ʴ� ������ �ʰ��Ͽ����ϴ�.
#define		ERROR_REQUEST_MIN_LIMIT_OVER					212		// ��û ī��Ʈ �д� ������ �ʰ��Ͽ����ϴ�.
#define		ERROR_REQUEST_HOUR_LIMIT_OVER					213		// ��û ī��Ʈ �ð��� ������ �ʰ��Ͽ����ϴ�.

#define		ERROR_MAX_CODE									RESULT_SUCCESS

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	�ý��� �뺸 �ڵ�
*/
#define		NOTIFY_SYSTEM_NEED_TO_RESTART					26		// ��� ���濡 ���� ����� �ʿ�
#define		NOTIFY_SYSTEM_LOGIN_START						27		// �α����� �����մϴ�.
#define		NOTIFY_SYSTEM_LOGIN_REQ_USERINFO				28		// ����� ������ ��û�մϴ�.
#define		NOTIFY_SYSTEM_LOGIN_RCV_USERINFO				29		// ����� ������ �����߽��ϴ�.
#define		NOTIFY_SYSTEM_LOGIN_FILE_DWN_START				30		// ���� �ٿ�ε带 �����մϴ�.
#define		NOTIFY_SYSTEM_LOGIN_FILE_DWN_END				31		// ���� �ٿ�ε尡 �Ϸ�Ǿ����ϴ�.
#define		NOTIFY_SYSTEM_TRAY_APP_CHECK					32		// Ʈ���� App üũ
#define		NOTIFY_SYSTEM_INFO_DUP_CONNECT					33		// ��������
#define		NOTIFY_SYSTEM_INFO_DETECT_CLOSET				34		// ���� ���� ����, �翬�� �õ����Դϴ�.
#define		NOTIFY_SYSTEM_INFO_RECONNECT					35		// �翬��Ǿ����ϴ�.

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	���������ڵ�
*/
#define		ACCOUNT_INFO_NAME								1		// ���¸�
#define		ACCOUNT_INFO_NICKNAME							2		// ���º���
#define		ACCOUNT_INFO_TYPE								3		// ��ǰ����

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	���������ڵ�
*/
#define		MARKET_TYPE_INTERNAL							0		// ����(�ֽ�,�����ɼ�)
#define		MARKET_TYPE_GLOBAL_STOCK						1		// �ؿ��ֽ�
#define		MARKET_TYPE_GLOBAL_DERIVATIVE					2		// �ؿܼ����ɼ�
#define		MARKET_TYPE_INTERNAL_STOCK						3		// ���� �ֽ�
#define		MARKET_TYPE_INTERNAL_KOSPIFUTURE				4		// ���� ����
#define		MARKET_TYPE_INTERNAL_KOSPIOPTION				5		// ���� �ɼ�
#define		MARKET_TYPE_GLOBAL_FUTURE						6		// �ؿܼ���
#define		MARKET_TYPE_GLOBAL_OPTION						7		// �ؿܿɼ�

#define		CODE_INFO_CODE									0		// �ڵ�
#define		CODE_INFO_STANDARD_CODE							1		// ǥ���ڵ�
#define		CODE_INFO_NAME									2		// �ѱ� �����
#define		CODE_INFO_ENG_NAME								3		// ���� �����
#define		CODE_INFO_JANG_GUBUN							4		// �屸��

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	ȯ�漳���ڵ�
*/
#define		CONFIG_STRUCT_MODE								0		// ��ȸ �� �ǽð� TR���� struct ����� ���� ������ ������ ��ȯ�ǵ��� ����
#define		CONFIG_REALDATA_BYPASS_MODE						1		// �ǽð� struct ����, Key-Value ����ó�� 

//-------------------------------------------------------------------------------------------------------------------
/**	@brief	�޽���
*/
// �޽����� ID���� Connect�ÿ� ������ nStartMsgID�� ���Ͽ� ���
#define 	CMD_YOA_FAIL									-1		// API Call ����
#define 	CMD_YOA_SUCCESS									1		// API Call ����
#define 	CMD_SYSTEM_MESSAGE								2		// System Message
#define 	CMD_LOGIN										3		// �����κ��� �α��� ��� �޾����� �߻�
#define 	CMD_LOGOUT										4		// �����κ��� �α׾ƿ� ��� �޾����� �߻�
#define 	CMD_RECEIVE_ERROR								5		// �����κ��� ������ �޾��� �� �߻�
#define 	CMD_RECEIVE_DATA								6		// Request�� ��û�� �����͸� �޾��� �� �߻�
#define 	CMD_RECEIVE_REAL_DATA							7		// RegistAuto�� ����� �ǽð��� �޾��� �� �߻�

#endif // _YOACOMMONDEF_H_
