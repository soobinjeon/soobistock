using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.DataInfo
{
    class StockCurrent : StockPrice
    {
        public string Capital_Cate { set; get; } //자본금 구분
        public string Kospi_cate { set; get; } //코스피구분
        public string Credit_Cate { set; get; } //신용구분
        public string Misuinfo { set; get; } //미수제한여부
        public long LastClosingPrice { set; get; } //전일종가
        public long LastVolume { set; get; }//전일거래량
        public long LastTimeZoneVolume { set; get; } //전일동시간대거래량
        public string LastTimeZoneTime { set; get; }// 전일동시간대거래량 시간
        public long ParPrice { set; get; } //액면가
        public long StandardPrice { set; get; } //기준가
        public string Kwunbae { set; get; } //권배락 구분
        public long ReplacePrice { set; get; } //대용가
        public long ForeignVolume { set; get; } //외국인 보유량
        public float ForeignRate { set; get; } //외국인 보유율
        public long ForeignDay { set; get; } //외국인 증감ㄷ당일
        public long ForeignBefore { set; get; } // 외국인 중감 전일
        public long CloseMonth { set; get; } //결산월
        public long CntStocks { set; get; } //상장주식수
        public long CapMoney { set; get; } //자본금구분
        public float PER { set; get; } //PER
        public string CloseMeme { set; get; } //정리매매여부
        public long Memesu { set; get; } //매매수라단위
        public float RentRestrate { set; get; } //대주잔고율
        public float CreatRestrate { set; get; } //융자잔고율
        public string Securities { set; get; } //등록주선사
        public string Registerday { set; get; } //등록일
        public float MoneyRate { set; get; } //회전율


    }
}
