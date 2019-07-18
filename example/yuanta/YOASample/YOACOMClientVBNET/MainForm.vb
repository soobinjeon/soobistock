Public Class MainForm
    Dim WithEvents yuantaAPI As New YuantaCOMLib.YuantaAPI
    Dim ReqID As Integer
    Dim AutoReqID As Integer

    Private Sub yuantaAPI_Login(nResult As Integer, bstrMsg As String) Handles yuantaAPI.Login
        If CommDef.RESPONSE_LOGIN_SUCCESS = nResult Then
            BtnLogin.Enabled = False
            BtnLogout.Enabled = True
            BtnAccount.Enabled = True
            BtnSearch.Enabled = True
            BtnRegist.Enabled = True

            LBMainLog.Items.Add("로그인이 완료되었습니다.")
        Else
            BtnLogin.Enabled = True
            BtnLogout.Enabled = False

            LBMainLog.Items.Add("로그인이 실패하였습니다.")

            If CommDef.ERROR_TIMEOUT_DATA = nResult Then
                LBMainLog.Items.Add("서버로부터 로그인 응답이 없습니다. 다시 시도하여 주십시오.")
            Else
                LBMainLog.Items.Add(yuantaAPI.YOA_GetErrorMessage(nResult))
            End If
        End If
    End Sub

    Private Sub yuantaAPI_ReceiveData(nReqID As Integer, bstrDSOID As String) Handles yuantaAPI.ReceiveData
        If ReqID = nReqID Then
            LBLog.Items.Add("[300001]주식현재가 조회응답을 수신하였습니다.")
            yuantaAPI.YOA_SetTRInfo("300001", "OutBlock1")
            TBName.Text = yuantaAPI.YOA_GetFieldString("jongname", 0)
            TBCurJuka.Text = yuantaAPI.YOA_GetFieldString("curjuka", 0)
            TBDebi.Text = yuantaAPI.YOA_GetFieldString("debi", 0)
            TBDebiRate.Text = yuantaAPI.YOA_GetFieldString("debirate", 0)
            TBVolume.Text = yuantaAPI.YOA_GetFieldString("volume", 0)
        End If
    End Sub

    Private Sub yuantaAPI_ReceiveRealData(nReqID As Integer, bstrAutoID As String) Handles yuantaAPI.ReceiveRealData
        If AutoReqID = nReqID Then
            LBLog.Items.Add("[11]주식 실시간체결을 수신하였습니다.")
            yuantaAPI.YOA_SetTRInfo("11", "OutBlock1")
            TBCurJuka.Text = yuantaAPI.YOA_GetFieldString("curjuka", 0)
            TBDebi.Text = yuantaAPI.YOA_GetFieldString("debi", 0)
            TBDebiRate.Text = yuantaAPI.YOA_GetFieldString("debirate", 0)
            TBVolume.Text = yuantaAPI.YOA_GetFieldString("volume", 0)
        End If
    End Sub

    Private Sub yuantaAPI_ReceiveError(nReqID As Integer, nErrCode As Integer, bstrErrMsg As String) Handles yuantaAPI.ReceiveError
        LBMainLog.Items.Add(bstrErrMsg)
    End Sub

    Private Sub yuantaAPI_ReceiveSystemMessage(nID As Integer, bstrMsg As String) Handles yuantaAPI.ReceiveSystemMessage
        LBMainLog.Items.Add(bstrMsg)
        
        If CommDef.NOTIFY_SYSTEM_NEED_TO_RESTART = nID Then
            yuantaAPI.YOA_ReStart()
        End If
    End Sub

    Private Sub BtnInit_Click(sender As System.Object, e As System.EventArgs) Handles BtnInit.Click
        'Dim strURL = "real.tradarglobal.api.com"
        'Dim strURL = "simul.tradarglobal.api.com"
        'Dim strURL = "real.tradar.api.com"
        Dim strURL = "simul.tradar.api.com"
        Dim nResult = yuantaAPI.YOA_Initial(strURL, "")
        If CommDef.RESULT_SUCCESS = nResult Then
            If strURL = "simul.tradar.api.com" Or strURL = "simul.tradarglobal.api.com" Then
                MsgBox("모의투자로 접속합니다." & Chr(13) & Chr(10) & "모의투자의 계좌비밀번호는 0000입니다.")
            End If

            LBMainLog.Items.Add("유안타 Open API가 초기화되었습니다.")
            BtnInit.Enabled = False
            BtnLogin.Enabled = True
        Else
            LBMainLog.Items.Add("유안타 Open API가 초기화에 실패하였습니다.")
        End If
    End Sub

    Private Sub BtnLogin_Click(sender As System.Object, e As System.EventArgs) Handles BtnLogin.Click
        Dim nResult = yuantaAPI.YOA_Login(TBUserID.Text, TBUserPWD.Text, TBCertPWD.Text)
        If CommDef.RESULT_SUCCESS = nResult Then
            LBMainLog.Items.Add("로그인 요청이 되었습니다.")
            BtnLogin.Enabled = False
        Else
            LBMainLog.Items.Add("로그인 요청이 실패하였습니다.")
            LBMainLog.Items.Add(yuantaAPI.YOA_GetErrorMessage(nResult))
            BtnLogin.Enabled = True
            BtnLogout.Enabled = False
        End If
    End Sub

    Private Sub BtnLogout_Click(sender As System.Object, e As System.EventArgs) Handles BtnLogout.Click
        yuantaAPI.YOA_UnInitial()
        Close()
    End Sub

    Private Sub MainForm_FormClosed(sender As Object, e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        yuantaAPI.YOA_UnInitial()
    End Sub

    Private Sub BtnAccount_Click(sender As System.Object, e As System.EventArgs) Handles BtnAccount.Click
        Dim strAccount As String
        Dim nCount = yuantaAPI.YOA_GetAccountCount() - 1
        Dim i As Integer
        For i = 0 To nCount
            LVAccount.Items.Add(i + 1)
            strAccount = yuantaAPI.YOA_GetAccount(i)
            LVAccount.Items.Item(i).SubItems.Add(strAccount)
            LVAccount.Items.Item(i).SubItems.Add(yuantaAPI.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NAME, strAccount))
        Next
    End Sub

    Private Sub BtnSearch_Click(sender As System.Object, e As System.EventArgs) Handles BtnSearch.Click
        Dim strJang = yuantaAPI.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL, CommDef.CODE_INFO_JANG_GUBUN, TBCode.Text)

        yuantaAPI.YOA_SetTRInfo("300001", "InBlock1")

        yuantaAPI.YOA_SetFieldString("jang", strJang, 0)
        yuantaAPI.YOA_SetFieldString("jongcode", TBCode.Text, 0)
        yuantaAPI.YOA_SetFieldString("outflag", "N", 0)
        yuantaAPI.YOA_SetFieldString("tsflag", "0", 0)

        ReqID = yuantaAPI.YOA_Request("300001", True, -1)
        If CommDef.ERROR_MAX_CODE < ReqID Then
            LBLog.Items.Add("[300001]주식현재가 조회를 요청하였습니다.")
        Else
            LBLog.Items.Add("[300001]주식현재가 조회 요청이 실패하였습니다.")
            LBLog.Items.Add(yuantaAPI.YOA_GetErrorMessage(ReqID))
        End If
    End Sub

    Private Sub BtnRegist_Click(sender As System.Object, e As System.EventArgs) Handles BtnRegist.Click
        yuantaAPI.YOA_SetTRFieldString("11", "InBlock1", "jongcode", TBCode.Text, 0)

        AutoReqID = yuantaAPI.YOA_RegistAuto("11")
        If CommDef.ERROR_MAX_CODE < AutoReqID Then
            BtnRegist.Enabled = False
            BtnUnRegist.Enabled = True

            LBLog.Items.Add("[11]주식 실시간체결 Auto가 등록 되었습니다.")
        Else
            BtnRegist.Enabled = True
            BtnUnRegist.Enabled = False

            LBLog.Items.Add("[11]주식 실시간체결 Auto 등록 요청이 실패하였습니다.")
            LBLog.Items.Add(yuantaAPI.YOA_GetErrorMessage(AutoReqID))
        End If
    End Sub

    Private Sub BtnUnRegist_Click(sender As System.Object, e As System.EventArgs) Handles BtnUnRegist.Click
        AutoReqID = yuantaAPI.YOA_UnRegistAutoWithReqID(AutoReqID)
        If CommDef.RESULT_SUCCESS = AutoReqID Then
            LBLog.Items.Add("[11]주식 실시간체결 Auto가 해지 되었습니다.")
        Else
            LBLog.Items.Add("[11]주식 실시간체결 Auto 해지 요청이 실패하였습니다.")
        End If
    End Sub
End Class
