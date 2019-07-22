using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.login
{
    public class LoginInfo
    {
        public string userid { internal set; get; }
        public string passwd { internal set; get; }
        public string cert { internal set; get; }

        public LoginInfo(string uid, string pwd, string ct)
        {
            userid = uid;
            passwd = pwd;
            cert = ct;
        }
    }
}
