using SoobiStock.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.login
{
    public class LoginIO
    {
        Dictionary<TraderList, LoginInfo> logins;
        string cryptKey = "soobisoobaRyan";
        AES Crypt;

        string fileName = @"loginfo.dat";
        public LoginIO()
        {
            logins = new Dictionary<TraderList, LoginInfo>();
            Crypt = new AES(cryptKey);
            LoadLoginInfo();
        }

        public LoginInfo getLoginInfo(TraderList tl)
        {
            LoginInfo linfo = null;
            if(logins.TryGetValue(tl, out linfo))
            {
                return linfo;
            }
            else
            {
                return new LoginInfo("null", "null", "null");
            }
        }

        void LoadLoginInfo()
        {
            List<string> data = getReadLoginInfo();
            
            if(data.Count < 3)
            {
                return;
            }

            for(int i = 0; i < data.Count; i+=4)
            {
                logins.Add(TraderListMethods.GetTraderList(Crypt.Decrypt(data[i])), new LoginInfo(Crypt.Decrypt(data[i+1])
                    , Crypt.Decrypt(data[i + 2])
                    , Crypt.Decrypt(data[i + 3])));
            }

            foreach(LoginInfo linfo in logins.Values)
            {
                Console.WriteLine("Login Info : " + linfo.userid + ", " + linfo.passwd + ", " + linfo.cert);
            }
        }

        List<string> getReadLoginInfo()
        {
            List<string> data = new List<string>();
            char[] c = null;
            int counter = 0;
            System.IO.StreamReader file = new System.IO.StreamReader(fileName);

            while (file.Peek() >= 0)
            {
                c = new char[24];
                file.Read(c, 0, c.Length);
                data.Add(new string(c));
            }
            file.Close();
            return data;
        }

        public void InputLoginInfo(Dictionary<TraderList, LoginInfo> loginfo)
        {
            System.IO.StreamWriter file = new System.IO.StreamWriter(fileName);

            foreach(TraderList tl in loginfo.Keys)
            {
                LoginInfo li = loginfo[tl];

                file.Write(Crypt.Encrypt(tl.ToString()));
                file.Write(Crypt.Encrypt(li.userid));
                file.Write(Crypt.Encrypt(li.passwd));
                file.Write(Crypt.Encrypt(li.cert));
            }

            file.Close();
        }
    }
}
