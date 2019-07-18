<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainForm
    Inherits System.Windows.Forms.Form

    'Form은 Dispose를 재정의하여 구성 요소 목록을 정리합니다.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows Form 디자이너에 필요합니다.
    Private components As System.ComponentModel.IContainer

    '참고: 다음 프로시저는 Windows Form 디자이너에 필요합니다.
    '수정하려면 Windows Form 디자이너를 사용하십시오.  
    '코드 편집기를 사용하여 수정하지 마십시오.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.PictureBox2 = New System.Windows.Forms.PictureBox()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.LBLog = New System.Windows.Forms.ListBox()
        Me.TBVolume = New System.Windows.Forms.TextBox()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.TBDebiRate = New System.Windows.Forms.TextBox()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.TBDebi = New System.Windows.Forms.TextBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.TBCurJuka = New System.Windows.Forms.TextBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.TBName = New System.Windows.Forms.TextBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.BtnUnRegist = New System.Windows.Forms.Button()
        Me.BtnRegist = New System.Windows.Forms.Button()
        Me.BtnSearch = New System.Windows.Forms.Button()
        Me.TBCode = New System.Windows.Forms.TextBox()
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.BtnLogout = New System.Windows.Forms.Button()
        Me.BtnLogin = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.LBMainLog = New System.Windows.Forms.ListBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.TBCertPWD = New System.Windows.Forms.TextBox()
        Me.TBUserPWD = New System.Windows.Forms.TextBox()
        Me.ColumnHeader3 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.TBUserID = New System.Windows.Forms.TextBox()
        Me.ColumnHeader2 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.BtnAccount = New System.Windows.Forms.Button()
        Me.ColumnHeader1 = CType(New System.Windows.Forms.ColumnHeader(), System.Windows.Forms.ColumnHeader)
        Me.LVAccount = New System.Windows.Forms.ListView()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.BtnInit = New System.Windows.Forms.Button()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        CType(Me.PictureBox2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox3.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'PictureBox2
        '
        Me.PictureBox2.Image = Global.YOACOMClientVBNET.My.Resources.Resources.logo2
        Me.PictureBox2.Location = New System.Drawing.Point(14, 241)
        Me.PictureBox2.Name = "PictureBox2"
        Me.PictureBox2.Size = New System.Drawing.Size(411, 239)
        Me.PictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox2.TabIndex = 17
        Me.PictureBox2.TabStop = False
        '
        'PictureBox1
        '
        Me.PictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None
        Me.PictureBox1.Image = Global.YOACOMClientVBNET.My.Resources.Resources.logo1
        Me.PictureBox1.Location = New System.Drawing.Point(14, 198)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(411, 43)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 16
        Me.PictureBox1.TabStop = False
        '
        'LBLog
        '
        Me.LBLog.FormattingEnabled = True
        Me.LBLog.ItemHeight = 12
        Me.LBLog.Location = New System.Drawing.Point(189, 63)
        Me.LBLog.Name = "LBLog"
        Me.LBLog.Size = New System.Drawing.Size(236, 124)
        Me.LBLog.TabIndex = 15
        '
        'TBVolume
        '
        Me.TBVolume.Location = New System.Drawing.Point(71, 167)
        Me.TBVolume.Name = "TBVolume"
        Me.TBVolume.Size = New System.Drawing.Size(106, 21)
        Me.TBVolume.TabIndex = 14
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(12, 172)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(41, 12)
        Me.Label8.TabIndex = 13
        Me.Label8.Text = "거래량"
        '
        'TBDebiRate
        '
        Me.TBDebiRate.Location = New System.Drawing.Point(71, 141)
        Me.TBDebiRate.Name = "TBDebiRate"
        Me.TBDebiRate.Size = New System.Drawing.Size(106, 21)
        Me.TBDebiRate.TabIndex = 12
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(12, 146)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(41, 12)
        Me.Label9.TabIndex = 11
        Me.Label9.Text = "등락률"
        '
        'TBDebi
        '
        Me.TBDebi.Location = New System.Drawing.Point(71, 115)
        Me.TBDebi.Name = "TBDebi"
        Me.TBDebi.Size = New System.Drawing.Size(106, 21)
        Me.TBDebi.TabIndex = 10
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(12, 120)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(53, 12)
        Me.Label7.TabIndex = 9
        Me.Label7.Text = "전일대비"
        '
        'TBCurJuka
        '
        Me.TBCurJuka.Location = New System.Drawing.Point(71, 89)
        Me.TBCurJuka.Name = "TBCurJuka"
        Me.TBCurJuka.Size = New System.Drawing.Size(106, 21)
        Me.TBCurJuka.TabIndex = 8
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(12, 94)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(41, 12)
        Me.Label6.TabIndex = 7
        Me.Label6.Text = "현재가"
        '
        'TBName
        '
        Me.TBName.Location = New System.Drawing.Point(71, 63)
        Me.TBName.Name = "TBName"
        Me.TBName.Size = New System.Drawing.Size(106, 21)
        Me.TBName.TabIndex = 6
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(12, 68)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(41, 12)
        Me.Label5.TabIndex = 5
        Me.Label5.Text = "종목명"
        '
        'BtnUnRegist
        '
        Me.BtnUnRegist.Enabled = False
        Me.BtnUnRegist.Location = New System.Drawing.Point(350, 18)
        Me.BtnUnRegist.Name = "BtnUnRegist"
        Me.BtnUnRegist.Size = New System.Drawing.Size(75, 23)
        Me.BtnUnRegist.TabIndex = 4
        Me.BtnUnRegist.Text = "실시간해지"
        Me.BtnUnRegist.UseVisualStyleBackColor = True
        '
        'BtnRegist
        '
        Me.BtnRegist.Enabled = False
        Me.BtnRegist.Location = New System.Drawing.Point(271, 18)
        Me.BtnRegist.Name = "BtnRegist"
        Me.BtnRegist.Size = New System.Drawing.Size(75, 23)
        Me.BtnRegist.TabIndex = 3
        Me.BtnRegist.Text = "실시간등록"
        Me.BtnRegist.UseVisualStyleBackColor = True
        '
        'BtnSearch
        '
        Me.BtnSearch.Enabled = False
        Me.BtnSearch.Location = New System.Drawing.Point(189, 18)
        Me.BtnSearch.Name = "BtnSearch"
        Me.BtnSearch.Size = New System.Drawing.Size(75, 23)
        Me.BtnSearch.TabIndex = 2
        Me.BtnSearch.Text = "조회"
        Me.BtnSearch.UseVisualStyleBackColor = True
        '
        'TBCode
        '
        Me.TBCode.Location = New System.Drawing.Point(99, 20)
        Me.TBCode.Name = "TBCode"
        Me.TBCode.Size = New System.Drawing.Size(78, 21)
        Me.TBCode.TabIndex = 1
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.PictureBox2)
        Me.GroupBox3.Controls.Add(Me.PictureBox1)
        Me.GroupBox3.Controls.Add(Me.LBLog)
        Me.GroupBox3.Controls.Add(Me.TBVolume)
        Me.GroupBox3.Controls.Add(Me.Label8)
        Me.GroupBox3.Controls.Add(Me.TBDebiRate)
        Me.GroupBox3.Controls.Add(Me.Label9)
        Me.GroupBox3.Controls.Add(Me.TBDebi)
        Me.GroupBox3.Controls.Add(Me.Label7)
        Me.GroupBox3.Controls.Add(Me.TBCurJuka)
        Me.GroupBox3.Controls.Add(Me.Label6)
        Me.GroupBox3.Controls.Add(Me.TBName)
        Me.GroupBox3.Controls.Add(Me.Label5)
        Me.GroupBox3.Controls.Add(Me.BtnUnRegist)
        Me.GroupBox3.Controls.Add(Me.BtnRegist)
        Me.GroupBox3.Controls.Add(Me.BtnSearch)
        Me.GroupBox3.Controls.Add(Me.TBCode)
        Me.GroupBox3.Controls.Add(Me.Label4)
        Me.GroupBox3.Location = New System.Drawing.Point(546, 12)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(438, 486)
        Me.GroupBox3.TabIndex = 7
        Me.GroupBox3.TabStop = False
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(12, 25)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(81, 12)
        Me.Label4.TabIndex = 0
        Me.Label4.Text = "주식 종목코드"
        '
        'BtnLogout
        '
        Me.BtnLogout.Enabled = False
        Me.BtnLogout.Location = New System.Drawing.Point(141, 142)
        Me.BtnLogout.Name = "BtnLogout"
        Me.BtnLogout.Size = New System.Drawing.Size(108, 23)
        Me.BtnLogout.TabIndex = 8
        Me.BtnLogout.Text = "로그아웃"
        Me.BtnLogout.UseVisualStyleBackColor = True
        '
        'BtnLogin
        '
        Me.BtnLogin.Enabled = False
        Me.BtnLogin.Location = New System.Drawing.Point(16, 142)
        Me.BtnLogin.Name = "BtnLogin"
        Me.BtnLogin.Size = New System.Drawing.Size(108, 23)
        Me.BtnLogin.TabIndex = 7
        Me.BtnLogin.Text = "로그인"
        Me.BtnLogin.UseVisualStyleBackColor = True
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(27, 117)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(53, 12)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "인증비번"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(27, 63)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(41, 12)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "아이디"
        '
        'LBMainLog
        '
        Me.LBMainLog.FormattingEnabled = True
        Me.LBMainLog.ItemHeight = 12
        Me.LBMainLog.Location = New System.Drawing.Point(14, 195)
        Me.LBMainLog.Name = "LBMainLog"
        Me.LBMainLog.Size = New System.Drawing.Size(526, 304)
        Me.LBMainLog.TabIndex = 6
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(27, 90)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(53, 12)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "비밀번호"
        '
        'TBCertPWD
        '
        Me.TBCertPWD.Location = New System.Drawing.Point(103, 112)
        Me.TBCertPWD.Name = "TBCertPWD"
        Me.TBCertPWD.PasswordChar = Global.Microsoft.VisualBasic.ChrW(9679)
        Me.TBCertPWD.Size = New System.Drawing.Size(135, 21)
        Me.TBCertPWD.TabIndex = 3
        '
        'TBUserPWD
        '
        Me.TBUserPWD.Location = New System.Drawing.Point(103, 85)
        Me.TBUserPWD.Name = "TBUserPWD"
        Me.TBUserPWD.PasswordChar = Global.Microsoft.VisualBasic.ChrW(9679)
        Me.TBUserPWD.Size = New System.Drawing.Size(135, 21)
        Me.TBUserPWD.TabIndex = 2
        '
        'ColumnHeader3
        '
        Me.ColumnHeader3.Text = "계좌명"
        Me.ColumnHeader3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        Me.ColumnHeader3.Width = 90
        '
        'TBUserID
        '
        Me.TBUserID.Location = New System.Drawing.Point(103, 58)
        Me.TBUserID.Name = "TBUserID"
        Me.TBUserID.Size = New System.Drawing.Size(135, 21)
        Me.TBUserID.TabIndex = 1
        '
        'ColumnHeader2
        '
        Me.ColumnHeader2.Text = "계좌번호"
        Me.ColumnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        Me.ColumnHeader2.Width = 95
        '
        'BtnAccount
        '
        Me.BtnAccount.Enabled = False
        Me.BtnAccount.Location = New System.Drawing.Point(6, 20)
        Me.BtnAccount.Name = "BtnAccount"
        Me.BtnAccount.Size = New System.Drawing.Size(114, 23)
        Me.BtnAccount.TabIndex = 1
        Me.BtnAccount.Text = "계좌가져오기"
        Me.BtnAccount.UseVisualStyleBackColor = True
        '
        'ColumnHeader1
        '
        Me.ColumnHeader1.Text = "No"
        Me.ColumnHeader1.Width = 35
        '
        'LVAccount
        '
        Me.LVAccount.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.ColumnHeader1, Me.ColumnHeader2, Me.ColumnHeader3})
        Me.LVAccount.FullRowSelect = True
        Me.LVAccount.GridLines = True
        Me.LVAccount.Location = New System.Drawing.Point(6, 58)
        Me.LVAccount.Name = "LVAccount"
        Me.LVAccount.Size = New System.Drawing.Size(244, 107)
        Me.LVAccount.TabIndex = 0
        Me.LVAccount.UseCompatibleStateImageBehavior = False
        Me.LVAccount.View = System.Windows.Forms.View.Details
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.LVAccount)
        Me.GroupBox2.Controls.Add(Me.BtnAccount)
        Me.GroupBox2.Location = New System.Drawing.Point(284, 12)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(256, 177)
        Me.GroupBox2.TabIndex = 5
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = " 계좌 "
        '
        'BtnInit
        '
        Me.BtnInit.Location = New System.Drawing.Point(16, 20)
        Me.BtnInit.Name = "BtnInit"
        Me.BtnInit.Size = New System.Drawing.Size(233, 23)
        Me.BtnInit.TabIndex = 0
        Me.BtnInit.Text = "YuantaAPI 모듈 초기화"
        Me.BtnInit.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.BtnLogout)
        Me.GroupBox1.Controls.Add(Me.BtnLogin)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.TBCertPWD)
        Me.GroupBox1.Controls.Add(Me.TBUserPWD)
        Me.GroupBox1.Controls.Add(Me.TBUserID)
        Me.GroupBox1.Controls.Add(Me.BtnInit)
        Me.GroupBox1.Location = New System.Drawing.Point(13, 12)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(265, 177)
        Me.GroupBox1.TabIndex = 4
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = " 로그인 "
        '
        'MainForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(997, 511)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.LBMainLog)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Name = "MainForm"
        Me.Text = "유안타 오픈 API 클라이언트(COM용)"
        CType(Me.PictureBox2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents PictureBox2 As System.Windows.Forms.PictureBox
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents LBLog As System.Windows.Forms.ListBox
    Friend WithEvents TBVolume As System.Windows.Forms.TextBox
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents TBDebiRate As System.Windows.Forms.TextBox
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents TBDebi As System.Windows.Forms.TextBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents TBCurJuka As System.Windows.Forms.TextBox
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents TBName As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents BtnUnRegist As System.Windows.Forms.Button
    Friend WithEvents BtnRegist As System.Windows.Forms.Button
    Friend WithEvents BtnSearch As System.Windows.Forms.Button
    Friend WithEvents TBCode As System.Windows.Forms.TextBox
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents BtnLogout As System.Windows.Forms.Button
    Friend WithEvents BtnLogin As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents LBMainLog As System.Windows.Forms.ListBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents TBCertPWD As System.Windows.Forms.TextBox
    Friend WithEvents TBUserPWD As System.Windows.Forms.TextBox
    Friend WithEvents ColumnHeader3 As System.Windows.Forms.ColumnHeader
    Friend WithEvents TBUserID As System.Windows.Forms.TextBox
    Friend WithEvents ColumnHeader2 As System.Windows.Forms.ColumnHeader
    Friend WithEvents BtnAccount As System.Windows.Forms.Button
    Friend WithEvents ColumnHeader1 As System.Windows.Forms.ColumnHeader
    Friend WithEvents LVAccount As System.Windows.Forms.ListView
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents BtnInit As System.Windows.Forms.Button
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox

End Class
