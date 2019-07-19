using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.DataInfo
{
    public class Account
    {
        public string accountID { internal set; get; }
        public string accountName { internal set; get; }
        public string accountNickName { internal set; get; }
        public string accountType { internal set; get; }
        public Account(string accid, string accname, string accNick, string acctype)
        {
            accountID = accid;
            accountName = accname;
            accountNickName = accNick;
            accountType = acctype;
        }
    }
}
