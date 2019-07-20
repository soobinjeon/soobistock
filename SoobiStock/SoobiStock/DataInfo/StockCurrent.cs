using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.DataInfo
{
    class StockCurrent
    {
        public string CodeName { internal set; get; }
        public long CurrentPrice { internal set; get; } //현재가
        public long Diff_Yesterday { internal set; get; } //전일대비
        public float ChangeRate { internal set; get; } //등락율
        public string CompanyName { internal set; get; }
        public string CompanyName_sub { internal set; get; }
        public string Capital_Cate { internal set; get; }
        public string Kospi_cate { internal set; get; }
        public string Credit_Cate { internal set; get; }
        public string Misuinfo { internal set; get; } //미수제한여부
        public long Volume { internal set; get; } //거래량
        public long LastClosingPrice { internal set; get; } //전일종가
        public long LastVolume { internal set; get; }//전일거래량
        public long LastTimeZoneVolume { internal set; get; } //전일동시간대거래량
        public string LastTimeZoneTime { internal set; get; }// 전일동시간대거래량 시간
        public long TranjPrice { internal set; get; } //거래대금
        public long StartPrice { internal set; get; } //시가
        public float StartPriceChangeRate { internal set; get; } //시가 등락률
        public long HighPrice { internal set; get; }
        public float HighPriceChangeRate { internal set; get; }
        public long LowPrice { internal set; get; }
        public float LowPriceChangeRate { internal set; get; }

    }
}
