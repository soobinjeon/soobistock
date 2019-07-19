using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.DataInfo
{
    public class Code
    {
        public string CodeID { internal set; get; }
        public string Standard_codeID { internal set; get; }
        public string Name { internal set; get; }
        public string Name_ENG { internal set; get; }
        public MarketType Market_Type { internal set; get; }

        public Code(string cid, string scid, string name, string nameeng, string mtype)
        {
            CodeID = cid;
            Standard_codeID = scid;
            Name = name;
            Name_ENG = nameeng;
            InsertMarketType(mtype);
        }

        private void InsertMarketType(string mtype)
        {
            if (mtype.Equals("1"))
            {
                Market_Type = MarketType.KOSDAQ;
            }else if(mtype.Equals("0"))
            {
                Market_Type = MarketType.KOSPI;
            }
            else
            {
                Market_Type = MarketType.NONE;
            }

        }
    }
}
