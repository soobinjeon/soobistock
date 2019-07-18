using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using YuantaCOMLib;

namespace MiniTimePeriodVolume
{
    public partial class LoginDlg : Form
    {
        public MainForm mainForm;
        public IYuantaAPI iYuantaAPI;

        public LoginDlg()
        {
            InitializeComponent();

            cbServer.SelectedIndex = 0;
        }

        private void cbServer_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (0 == cbServer.SelectedIndex || 2 == cbServer.SelectedIndex)
                tbCertPW.Enabled = false;
            else
                tbCertPW.Enabled = true;
        }
    }
}
