namespace MiniTimePeriodVolume
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnAuto = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.cbType = new System.Windows.Forms.ComboBox();
            this.cbDayType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbVolume = new System.Windows.Forms.TextBox();
            this.btnRequest = new System.Windows.Forms.Button();
            this.cbInterval = new System.Windows.Forms.ComboBox();
            this.lblName = new System.Windows.Forms.Label();
            this.tbCode = new System.Windows.Forms.TextBox();
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lvData = new System.Windows.Forms.ListView();
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader7 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader8 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader9 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader10 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lblLog = new System.Windows.Forms.Label();
            this.btnNext = new System.Windows.Forms.Button();
            this.columnHeader11 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnNext);
            this.groupBox1.Controls.Add(this.btnAuto);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cbType);
            this.groupBox1.Controls.Add(this.cbDayType);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.tbVolume);
            this.groupBox1.Controls.Add(this.btnRequest);
            this.groupBox1.Controls.Add(this.cbInterval);
            this.groupBox1.Controls.Add(this.lblName);
            this.groupBox1.Controls.Add(this.tbCode);
            this.groupBox1.Location = new System.Drawing.Point(12, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(388, 77);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            // 
            // btnAuto
            // 
            this.btnAuto.Enabled = false;
            this.btnAuto.Location = new System.Drawing.Point(333, 45);
            this.btnAuto.Name = "btnAuto";
            this.btnAuto.Size = new System.Drawing.Size(49, 22);
            this.btnAuto.TabIndex = 11;
            this.btnAuto.Text = "실시간";
            this.btnAuto.UseVisualStyleBackColor = true;
            this.btnAuto.Click += new System.EventHandler(this.btnAuto_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(120, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "체결량";
            // 
            // cbType
            // 
            this.cbType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbType.Enabled = false;
            this.cbType.FormattingEnabled = true;
            this.cbType.Items.AddRange(new object[] {
            "이상",
            "이하"});
            this.cbType.Location = new System.Drawing.Point(278, 46);
            this.cbType.Name = "cbType";
            this.cbType.Size = new System.Drawing.Size(49, 20);
            this.cbType.TabIndex = 9;
            // 
            // cbDayType
            // 
            this.cbDayType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDayType.Enabled = false;
            this.cbDayType.FormattingEnabled = true;
            this.cbDayType.Items.AddRange(new object[] {
            "당일",
            "전일"});
            this.cbDayType.Location = new System.Drawing.Point(11, 46);
            this.cbDayType.Name = "cbDayType";
            this.cbDayType.Size = new System.Drawing.Size(47, 20);
            this.cbDayType.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(253, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(17, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "주";
            // 
            // tbVolume
            // 
            this.tbVolume.Enabled = false;
            this.tbVolume.Location = new System.Drawing.Point(169, 46);
            this.tbVolume.Name = "tbVolume";
            this.tbVolume.Size = new System.Drawing.Size(79, 21);
            this.tbVolume.TabIndex = 6;
            this.tbVolume.Text = "0";
            this.tbVolume.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // btnRequest
            // 
            this.btnRequest.Enabled = false;
            this.btnRequest.Location = new System.Drawing.Point(278, 16);
            this.btnRequest.Name = "btnRequest";
            this.btnRequest.Size = new System.Drawing.Size(49, 22);
            this.btnRequest.TabIndex = 3;
            this.btnRequest.Text = "조회";
            this.btnRequest.UseVisualStyleBackColor = true;
            this.btnRequest.Click += new System.EventHandler(this.btnRequest_Click);
            // 
            // cbInterval
            // 
            this.cbInterval.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbInterval.Enabled = false;
            this.cbInterval.FormattingEnabled = true;
            this.cbInterval.Items.AddRange(new object[] {
            "체결",
            "1분",
            "5분",
            "10분"});
            this.cbInterval.Location = new System.Drawing.Point(62, 46);
            this.cbInterval.Name = "cbInterval";
            this.cbInterval.Size = new System.Drawing.Size(49, 20);
            this.cbInterval.TabIndex = 2;
            // 
            // lblName
            // 
            this.lblName.BackColor = System.Drawing.Color.White;
            this.lblName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblName.Enabled = false;
            this.lblName.Location = new System.Drawing.Point(117, 17);
            this.lblName.Name = "lblName";
            this.lblName.Padding = new System.Windows.Forms.Padding(3, 3, 0, 0);
            this.lblName.Size = new System.Drawing.Size(155, 20);
            this.lblName.TabIndex = 1;
            // 
            // tbCode
            // 
            this.tbCode.Enabled = false;
            this.tbCode.Location = new System.Drawing.Point(11, 17);
            this.tbCode.Name = "tbCode";
            this.tbCode.Size = new System.Drawing.Size(100, 21);
            this.tbCode.TabIndex = 0;
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5});
            this.listView1.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listView1.Location = new System.Drawing.Point(12, 88);
            this.listView1.Name = "listView1";
            this.listView1.Scrollable = false;
            this.listView1.Size = new System.Drawing.Size(388, 26);
            this.listView1.TabIndex = 1;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Index";
            this.columnHeader1.Width = 0;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "시간";
            this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader2.Width = 81;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "현재가";
            this.columnHeader3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader3.Width = 100;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "대비";
            this.columnHeader4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader4.Width = 110;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "체결량";
            this.columnHeader5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader5.Width = 94;
            // 
            // lvData
            // 
            this.lvData.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader6,
            this.columnHeader7,
            this.columnHeader8,
            this.columnHeader9,
            this.columnHeader10,
            this.columnHeader11});
            this.lvData.Font = new System.Drawing.Font("굴림", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lvData.FullRowSelect = true;
            this.lvData.GridLines = true;
            this.lvData.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.lvData.Location = new System.Drawing.Point(12, 113);
            this.lvData.Name = "lvData";
            this.lvData.Size = new System.Drawing.Size(388, 303);
            this.lvData.TabIndex = 2;
            this.lvData.UseCompatibleStateImageBehavior = false;
            this.lvData.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Width = 0;
            // 
            // columnHeader7
            // 
            this.columnHeader7.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader7.Width = 80;
            // 
            // columnHeader8
            // 
            this.columnHeader8.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader8.Width = 100;
            // 
            // columnHeader9
            // 
            this.columnHeader9.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader9.Width = 25;
            // 
            // columnHeader10
            // 
            this.columnHeader10.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader10.Width = 85;
            // 
            // lblLog
            // 
            this.lblLog.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lblLog.Location = new System.Drawing.Point(12, 426);
            this.lblLog.Name = "lblLog";
            this.lblLog.Padding = new System.Windows.Forms.Padding(0, 5, 0, 0);
            this.lblLog.Size = new System.Drawing.Size(388, 23);
            this.lblLog.TabIndex = 3;
            // 
            // btnNext
            // 
            this.btnNext.Enabled = false;
            this.btnNext.Location = new System.Drawing.Point(333, 16);
            this.btnNext.Name = "btnNext";
            this.btnNext.Size = new System.Drawing.Size(49, 22);
            this.btnNext.TabIndex = 12;
            this.btnNext.Text = "다음";
            this.btnNext.UseVisualStyleBackColor = true;
            this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
            // 
            // columnHeader11
            // 
            this.columnHeader11.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader11.Width = 76;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(411, 460);
            this.Controls.Add(this.lblLog);
            this.Controls.Add(this.lvData);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.groupBox1);
            this.Name = "MainForm";
            this.Text = "미니시간대별체결량";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
            this.Shown += new System.EventHandler(this.MainForm_Shown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbType;
        private System.Windows.Forms.ComboBox cbDayType;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbVolume;
        private System.Windows.Forms.Button btnRequest;
        private System.Windows.Forms.ComboBox cbInterval;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.TextBox tbCode;
        private System.Windows.Forms.Button btnAuto;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ListView lvData;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
        private System.Windows.Forms.ColumnHeader columnHeader9;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.Label lblLog;
        private System.Windows.Forms.Button btnNext;
        private System.Windows.Forms.ColumnHeader columnHeader11;
    }
}

