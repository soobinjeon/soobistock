using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.DataInfo
{
    class StockPrice
    {
        public Code codes { set; get; }
        public string CompanyName { set; get; } //회사명
        public string CompanyName_sub { set; get; }
        public string CodeName { set; get; } //종코드
        public long CurrentPrice { set; get; } //현재가
        public float ChangeRate { set; get; } //등락율
        public long StartPrice { set; get; } //시가
        public long HighPrice { set; get; }
        public long LowPrice { set; get; }
        public long SellPrice { set; get; }
        public long BuyPrice { set; get; }
        public string HighTime { set; get; }
        public string LowTime { set; get; }
        public long MaxPrice { set; get; }
        public long MinPrice { set; get; }
        public long Diff_Yesterday { set; get; } //전일대비
        public long Volume { set; get; } //거래량 (주)
        public long Money { set; get; } //누적거래대금
        public float StartPriceChangeRate { set; get; } //시가 등락률
        public float HighPriceChangeRate { set; get; } //고가 등락율
        public float LowPriceChangeRate { set; get; } //저가 등락율
    }
}
