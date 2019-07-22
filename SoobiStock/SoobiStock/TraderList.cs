using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock
{
    public enum TraderList
    {
        MAIN = 0,
        YUANTA = 1
        //KIWOOM = 2
    }

    static class TraderListMethods
    {
        public static TraderList GetTraderList(string data)
        {
            string[] names = Enum.GetNames(typeof(TraderList));
            int cnt = 0;
            foreach(string n in names)
            {
                if(data.Equals(n))
                {
                    return (TraderList)cnt;
                }
                cnt++;
            }

            return (TraderList)0;
        }
    }
}
