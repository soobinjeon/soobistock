#pragma pack( push, 1 )

typedef struct _AUTO11_OutBlock1
{
	char      jongcode                      [   6];                                                  // [string    ,    6] 종목코드                                           ※                                                   
	char      sisegubun                     [   1];                                                  // [string    ,    1] 시세급변                                           ※                                                   
	char      updowngubun                   [   1];                                                  // [string    ,    1] 상하한가근접구분                                   ※                                                   
	char      _curjuka						 ;
	char      curjuka                       [   4];													 // [long      ,    4] 현재가                                             ※                                                   
	char      _startjuka                     ;
	char      startjuka                     [   4];													 // [long      ,    4] 시가                                               ※                                                   
	char      _highjuka                      ;														 
	char      highjuka                      [   4];													 // [long      ,    4] 고가                                               ※                                                   
	char      _lowjuka                       ;														 
	char      lowjuka                       [   4];													 // [long      ,    4] 저가                                               ※                                                   
	char      _medohoka                      ;														 
	char      medohoka                      [   4];													 // [long      ,    4] 매도호가                                           ※                                                   
	char      _mesuhoka                      ;														 
	char      mesuhoka                      [   4];													 // [long      ,    4] 매수호가                                           ※                                                   
	char      FILLER1                       [   2];                                                  // [string    ,    2] 4bytes맞추기위해                                   ※                                                   
	char      volume                        [   4];                                                  // [long      ,    4] 누적거래량_주단위                                  ※                                                   
	char      money                         [   4];                                                  // [long      ,    4] 누적거래대금_천단위                                ※                                                   
	char      debirate                      [   4];                                                  // [float     ,    4] 등락률                                             ※                                                   
	char      time                          [   5];                                                  // [string    ,    5] 시간_HH:SS                                         ※                                                   
	char      hightime                      [   5];                                                  // [string    ,    5] 고가시간                                           ※                                                   
	char      lowtime                       [   5];                                                  // [string    ,    5] 저가시간                                           ※                                                   
	char      _debi                          ;
	char      debi                          [   4];													 // [long      ,    4] 전일대비                                           ※                                                   
	char      _nowvol                        ;														 
	char      nowvol                        [   4];													 // [long      ,    4] 직전체결량                                         ※                                                   
	char      sisesec                       [   1];                                                  // [string    ,    1] 시세급변_초                                        ※                                                   
	char      siserate                      [   2];                                                  // [short     ,    2] 시세급변_등락률                                    ※                                                   
	char      nowmoney                      [   4];                                                  // [long      ,    4] 직전거래대금                                       ※                                                   
	char      chejuka                       [   4];                                                  // [long      ,    4] 체결가                                             ※                                                   
	char      _chedebi                       ;
	char      chedebi                       [   4];													 // [long      ,    4] 체결가전일대비                                     ※                                                   
	char      jang                          [   1];                                                  // [string    ,    1] 장구분                                             ※                                                   
	char      updownflag                    [   1];                                                  // [string    ,    1] 상한가근접_구분값                                  ※                                                   
	char      FILLER2                       [   1];                                                  // [string    ,    1] 4bytes맞추기위해                                   ※                                                   
	char      time2                         [   8];                                                  // [string    ,    8] 시간2                                              ※                                                   
	char      chegyulrate                   [   4];                                                  // [float     ,    4] 체결강도                                           ※                                                   
	char      mesusumvolume                 [   4];                                                  // [long      ,    4] 매수체결합                                         ※                                                   
	char      _upjuka                        ;
	char      medosumvolume                 [   4];                                                  // [long      ,    4] 매도체결합                                         ※                                                   
	char      upjuka                        [   4];													 // [long      ,    4] 상한가                                             ※                                                   
	char      _downjuka                      ;
	char      downjuka                      [   4];													 // [long      ,    4] 하한가                                             ※                                                   
	char      FILLER3                       [   2];                                                  // [string    ,    2] 4bytes맞추기위해                                   ※                                                   
	char      befminvol                     [   4];                                                  // [long      ,    4] 전일동시간거래량                                   ※                                                   
	char      befmindebi                    [   4];                                                  // [long      ,    4] 전일동시간대비                                     ※                                                   
	char      startdebirate                 [   4];                                                  // [float     ,    4] 시가등략율                                         ※                                                   
	char      highdebirate                  [   4];                                                  // [float     ,    4] 고가등략율                                         ※                                                   
	char      lowdebirate                   [   4];                                                  // [float     ,    4] 저가등략율                                         ※                                                   
} AUTO11_OutBlock1, *LP_AUTO11_OutBlock1;
#define NAME_AUTO11_OutBlock1     "OutBlock1"

#pragma pack( pop )