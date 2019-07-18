#pragma pack( push, 1 )

typedef struct _DSO300001_InBlock1
{
	char      jang                          [   1];    // [byte      ,    1] 장내외구분                                         ※                                                   
	char      jongcode                      [   6];    // [varstring ,    6] 종목코드                                           ※                                                   
	char      outflag                       [   1];    // [varstring ,    1] 단일가여부_Y_N                                     ※                                                   
	char      tsflag                        [   1];    // [varstring ,    1] 거래원수량_대금_평균                               ※                                                   
} DSO300001_InBlock1, *LP_DSO300001_InBlock1;
#define NAME_DSO300001_InBlock1     "InBlock1"

typedef struct _DSO300001_OutBlock1
{
	char      jongname                      [  20];                                                  // [varstring ,   20] 종목이름                                           ※                                                   
	char      _curjuka;	   
	char      curjuka						[   4];													 // [long      ,    4] 현재가                                             ※                                                   
	char      _deb;        
	char      debi							[   4];													 // [long      ,    4] 전일대비                                           ※                                                   
	char      debirate                      [   4];                                                  // [float     ,    4] 등락율                                             ※                                                   
	char      upname                        [  20];                                                  // [varstring ,   20] 업종이름                                           ※                                                   
	char      buname                        [  20];                                                  // [varstring ,   20] 부이름                                             ※                                                   
	char      cap                           [   4];                                                  // [varstring ,    4] 자본금구분                                         ※                                                   
	char      kospi                         [   8];                                                  // [varstring ,    8] 코스피구분                                         ※                                                   
	char      credit                        [  26];                                                  // [varstring ,   26] 신용구분                                           ※                                                   
	char      misuinfo                      [  15];                                                  // [varstring ,   15] 미수제한여부                                       ※                                                   
	char      volume                        [   4];                                                  // [long      ,    4] 거래량                                             ※                                                   
	char      prevlastjuka                  [   4];                                                  // [long      ,    4] 전일종가                                           ※                                                   
	char      prevvolume                    [   4];                                                  // [long      ,    4] 전일거래량                                         ※                                                   
	char      befminvol                     [   4];                                                  // [long      ,    4] 전일동시간대거래량                                 ※                                                   
	char      beftime                       [   5];                                                  // [varstring ,    5] 전일동시간대거래량시간                             ※                                                   
	char      money                         [   4];                                                  // [long      ,    4] 거래대금                                           ※                                                   
	char      _startjuka;   
	char	  startjuka						[   4];													 // [long      ,    4] 시가                                               ※                                                   
	char      startdebirate                 [   4];                                                  // [float     ,    4] 시가등락율                                         ※                                                   
	char      _highjuka;    
	char      highjuka						[   4];													 // [long      ,    4] 고가                                               ※                                                   
	char      highdebirate                  [   4];                                                  // [float     ,    4] 고가등락율                                         ※                                                   
	char      _lowjuka;		
	char      lowjuka						[   4];													 // [long      ,    4] 저가                                               ※                                                   
	char      lowdebirate                   [   4];                                                  // [float     ,    4] 저가등락율                                         ※                                                   
	char      hightime                      [   5];                                                  // [varstring ,    5] 고가시간                                           ※                                                   
	char      lowtime                       [   5];                                                  // [varstring ,    5] 저가시간                                           ※                                                   
	char      _upjuka;		
	char      upjuka						[   4];													 // [long      ,    4] 상한가                                             ※                                                   
	char      _downjuka;	
	char      downjuka						[   4];													 // [long      ,    4] 하한가                                             ※                                                   
	char      _medohoka;	
	char      medohoka						[   4];													 // [long      ,    4] 매도호가                                           ※                                                   
	char      _mesuhoka;	
	char      mesuhoka						[   4];													 // [long      ,    4] 매수호가                                           ※                                                   
	char      facejuka                      [   4];                                                  // [long      ,    4] 액면가                                             ※                                                   
	char      standardjuka                  [   4];                                                  // [long      ,    4] 기준가                                             ※                                                   
	char      kwunbae                       [  15];                                                  // [varstring ,   15] 권배락구분                                         ※                                                   
	char      replacejuka                   [   4];                                                  // [long      ,    4] 대용가                                             ※                                                   
	char      forevol                       [   4];                                                  // [long      ,    4] 외국인보유량                                       ※                                                   
	char      forerate                      [   4];                                                  // [float     ,    4] 외국인보유율                                       ※                                                   
	char      foretoday                     [   4];                                                  // [long      ,    4] 외국인증감당일                                     ※                                                   
	char      forebefore                    [   4];                                                  // [long      ,    4] 외국인증감전일                                     ※                                                   
	char      closemonth                    [   4];                                                  // [long      ,    4] 결산월                                             ※                                                   
	char      cntstocks                     [   4];                                                  // [long      ,    4] 상장주식수                                         ※                                                   
	char      capmoney                      [   4];                                                  // [long      ,    4] 자본금                                             ※                                                   
	char      per                           [   4];                                                  // [float     ,    4] PER                                                ※                                                   
	char      closememe                     [  12];                                                  // [varstring ,   12] 정리매매여부                                       ※                                                   
	char      memesu                        [   4];                                                  // [long      ,    4] 매매수량단위                                       ※                                                   
	char      rentrestrate                  [   4];                                                  // [float     ,    4] 대주잔고율                                         ※                                                   
	char      creditrestrate                [   4];                                                  // [float     ,    4] 융자잔고율                                         ※                                                   
	char      securities                    [   3];                                                  // [varstring ,    3] 등록주선사                                         ※                                                   
	char      registerday                   [  10];                                                  // [varstring ,   10] 등록일                                             ※                                                   
	char      monrate                       [   4];                                                  // [float     ,    4] 회전율                                             ※                                                   
} DSO300001_OutBlock1, *LP_DSO300001_OutBlock1;
#define NAME_DSO300001_OutBlock1     "OutBlock1"

typedef struct _DSO300001_OutBlock2
{
	char      highjuka                      [   4];    // [long      ,    4] 최고가                                             ※                                                   
	char      highjukaday                   [   7];    // [varstring ,    7] 최고가일                                           ※                                                   
	char      lowjuka                       [   4];    // [long      ,    4] 최저가                                             ※                                                   
	char      lowjukaday                    [   7];    // [varstring ,    7] 최저가일                                           ※                                                   
} DSO300001_OutBlock2, *LP_DSO300001_OutBlock2;
#define NAME_DSO300001_OutBlock2     "OutBlock2"

typedef struct _DSO300001_OutBlock3
{
	char      medocomno                     [   3];    // [varstring ,    3] 매도회원사                                         ※                                                   
	char      medovol                       [   4];    // [long      ,    4] 매도수량                                           ※                                                   
	char      mesucomno                     [   3];    // [varstring ,    3] 매수회원사                                         ※                                                   
	char      mesuvol                       [   4];    // [long      ,    4] 매수수량                                           ※                                                   
} DSO300001_OutBlock3, *LP_DSO300001_OutBlock3;
#define NAME_DSO300001_OutBlock3     "OutBlock3"

typedef struct _DSO300001_OutBlock4
{
	char      _ecncurjuka                    ;
	char      ecncurjuka                    [   4];													 // [long      ,    4] 현재가                                             ※                                                   
	char      _ecndebi                       ;
	char      ecndebi                       [   4];													 // [long      ,    4] 대비                                               ※                                                   
	char      ecnrate                       [   4];                                                  // [float     ,    4] 등락율                                             ※                                                   
	char      ecnvolume                     [   4];                                                  // [long      ,    4] 거래량                                             ※                                                   
	char      ecnmoney                      [   4];                                                  // [long      ,    4] 대금(천원)                                         ※                                                   
	char      _ecnstartjuka                  ;
	char      ecnstartjuka                  [   4];													 // [long      ,    4] 시가                                               ※                                                   
	char      _ecnhighjuka                   ;
	char      ecnhighjuka                   [   4];													 // [long      ,    4] 고가                                               ※                                                   
	char      _ecnlowjuka                    ;
	char      ecnlowjuka                    [   4];													 // [long      ,    4] 저가                                               ※                                                   
	char      foretoday2                    [   8];                                                  // [double    ,    8] 외국인증감당일                                     ※                                                   
	char      forebefore2                   [   8];                                                  // [double    ,    8] 외국인증감전일                                     ※                                                   
	char      res2                          [   4];                                                  // [long      ,    4] 2차저항                                            ※                                                   
	char      res1                          [   4];                                                  // [long      ,    4] 1차저항                                            ※                                                   
	char      pivot                         [   4];                                                  // [long      ,    4] 피봇                                               ※                                                   
	char      sup1                          [   4];                                                  // [long      ,    4] 1차지지                                            ※                                                   
	char      sup2                          [   4];                                                  // [long      ,    4] 2차지지                                            ※                                                   
	char      stockgubun                    [  29];                                                  // [varstring ,   29] 자사주구분                                         ※                                                   
	char      stockvolume                   [   4];                                                  // [long      ,    4] 자사주신청량                                       ※                                                   
	char      stockchevol                   [   4];                                                  // [long      ,    4] 자사주체결량                                       ※                                                   
	char      supdate                       [   4];                                                  // [long      ,    4] 제공일                                             ※                                                   
	char      flowstocks                    [   4];                                                  // [long      ,    4] 유동수량                                           ※                                                   
	char      lporder                       [  10];                                                  // [varstring ,   10] lp주문가능여부                                     ※                                                   
	char      spread                        [   4];                                                  // [float     ,    4] 스프레스                                           ※                                                   
	char      minhokamulti                  [   4];                                                  // [long      ,    4] 최소호가수량배수                                   ※                                                   
	char      lpcode1                       [   3];                                                  // [varstring ,    3] lp1                                                ※                                                   
	char      lpcode2                       [   3];                                                  // [varstring ,    3] lp2                                                ※                                                   
	char      lpcode3                       [   3];                                                  // [varstring ,    3] lp3                                                ※                                                   
	char      lpcode4                       [   3];                                                  // [varstring ,    3] lp4                                                ※                                                   
	char      lpcode5                       [   3];                                                  // [varstring ,    3] lp5                                                ※                                                   
	char      roundstock                    [  20];                                                  // [varstring ,   20] 우회상장여부                                       ※                                                   
	char      sellvolume                    [   4];                                                  // [long      ,    4] 공매도수량                                         ※                                                   
	char      sellmoney                     [   4];                                                  // [long      ,    4] 공매도대금                                         ※                                                   
	char      borrow                        [   6];                                                  // [varstring ,    6] 대차가능여부                                       ※                                                   
	char      presell                       [   6];                                                  // [varstring ,    6] 공매도불가여부                                     ※                                                   
	char      pbr                           [   4];                                                  // [float     ,    4] PBR                                                ※                                                   
	char      eps                           [   4];                                                  // [long      ,    4] EPS                                                ※                                                   
	char      bps                           [   4];                                                  // [long      ,    4] BPS                                                ※                                                   
	char      upcode                        [   4];                                                  // [long      ,    4] 업종코드                                           ※                                                   
	char      loanvolume                    [   8];                                                  // [double    ,    8] 대차잔고                                           ※                                                   
	char      progsunmesu                   [   4];                                                  // [long      ,    4] 프로그램순매수수량                                 ※                                                   
	char      currencycode                  [   3];                                                  // [varstring ,    3] 화폐단위                                           ※                                                   
	char      roa                           [   4];                                                  // [float     ,    4] ROA                                                ※                                                   
	char      roe                           [   4];                                                  // [float     ,    4] ROE                                                ※                                                   
	char      progchasunmesu                [   4];                                                  // [long      ,    4] 차익프로그램순매수_수량                            ※                                                   
	char      progbisunmesu                 [   4];                                                  // [long      ,    4] 비차익프로그램순매수_수량                          ※                                                   
	char      sellbefvolume                 [   8];                                                  // [double    ,    8] 전일공매도수                                       ※                                                   
} DSO300001_OutBlock4, *LP_DSO300001_OutBlock4;
#define NAME_DSO300001_OutBlock4     "OutBlock4"

#pragma pack( pop )