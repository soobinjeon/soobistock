using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock
{
    public class LogMessage
    {
        TraderList tlist;
        public static string SYSTEM_MESSAGE = "System Message";
        public static string SBSTOCK_SYSTEM_MESSAGE = "SBStock System Message";
        public static string TRADER_MESSAGE = "Trader Message";
        public LogMessage(TraderList t)
        {
            tlist = t;
        }

        public void LOG_MESSAGE(string s_type, string message)
        {
            LOG_MESSAGE(s_type, message, -1);
        }

        public void LOG_MESSAGE(string s_type, string message, int mID)
        {
            Console.WriteLine("({0}:{1} - {2}) : {3}",tlist.ToString(), s_type, mID, message);
        }
    }
}
