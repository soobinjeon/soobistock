#pragma pack( push, 1 )

typedef struct _DSO300001_InBlock1
{
	char      jang                          [   1];    // [byte      ,    1] �峻�ܱ���                                         ��                                                   
	char      jongcode                      [   6];    // [varstring ,    6] �����ڵ�                                           ��                                                   
	char      outflag                       [   1];    // [varstring ,    1] ���ϰ�����_Y_N                                     ��                                                   
	char      tsflag                        [   1];    // [varstring ,    1] �ŷ�������_���_���                               ��                                                   
} DSO300001_InBlock1, *LP_DSO300001_InBlock1;
#define NAME_DSO300001_InBlock1     "InBlock1"

typedef struct _DSO300001_OutBlock1
{
	char      jongname                      [  20];                                                  // [varstring ,   20] �����̸�                                           ��                                                   
	char      _curjuka;	   
	char      curjuka						[   4];													 // [long      ,    4] ���簡                                             ��                                                   
	char      _deb;        
	char      debi							[   4];													 // [long      ,    4] ���ϴ��                                           ��                                                   
	char      debirate                      [   4];                                                  // [float     ,    4] �����                                             ��                                                   
	char      upname                        [  20];                                                  // [varstring ,   20] �����̸�                                           ��                                                   
	char      buname                        [  20];                                                  // [varstring ,   20] ���̸�                                             ��                                                   
	char      cap                           [   4];                                                  // [varstring ,    4] �ں��ݱ���                                         ��                                                   
	char      kospi                         [   8];                                                  // [varstring ,    8] �ڽ��Ǳ���                                         ��                                                   
	char      credit                        [  26];                                                  // [varstring ,   26] �ſ뱸��                                           ��                                                   
	char      misuinfo                      [  15];                                                  // [varstring ,   15] �̼����ѿ���                                       ��                                                   
	char      volume                        [   4];                                                  // [long      ,    4] �ŷ���                                             ��                                                   
	char      prevlastjuka                  [   4];                                                  // [long      ,    4] ��������                                           ��                                                   
	char      prevvolume                    [   4];                                                  // [long      ,    4] ���ϰŷ���                                         ��                                                   
	char      befminvol                     [   4];                                                  // [long      ,    4] ���ϵ��ð���ŷ���                                 ��                                                   
	char      beftime                       [   5];                                                  // [varstring ,    5] ���ϵ��ð���ŷ����ð�                             ��                                                   
	char      money                         [   4];                                                  // [long      ,    4] �ŷ����                                           ��                                                   
	char      _startjuka;   
	char	  startjuka						[   4];													 // [long      ,    4] �ð�                                               ��                                                   
	char      startdebirate                 [   4];                                                  // [float     ,    4] �ð������                                         ��                                                   
	char      _highjuka;    
	char      highjuka						[   4];													 // [long      ,    4] ��                                               ��                                                   
	char      highdebirate                  [   4];                                                  // [float     ,    4] �������                                         ��                                                   
	char      _lowjuka;		
	char      lowjuka						[   4];													 // [long      ,    4] ����                                               ��                                                   
	char      lowdebirate                   [   4];                                                  // [float     ,    4] ���������                                         ��                                                   
	char      hightime                      [   5];                                                  // [varstring ,    5] ���ð�                                           ��                                                   
	char      lowtime                       [   5];                                                  // [varstring ,    5] �����ð�                                           ��                                                   
	char      _upjuka;		
	char      upjuka						[   4];													 // [long      ,    4] ���Ѱ�                                             ��                                                   
	char      _downjuka;	
	char      downjuka						[   4];													 // [long      ,    4] ���Ѱ�                                             ��                                                   
	char      _medohoka;	
	char      medohoka						[   4];													 // [long      ,    4] �ŵ�ȣ��                                           ��                                                   
	char      _mesuhoka;	
	char      mesuhoka						[   4];													 // [long      ,    4] �ż�ȣ��                                           ��                                                   
	char      facejuka                      [   4];                                                  // [long      ,    4] �׸鰡                                             ��                                                   
	char      standardjuka                  [   4];                                                  // [long      ,    4] ���ذ�                                             ��                                                   
	char      kwunbae                       [  15];                                                  // [varstring ,   15] �ǹ������                                         ��                                                   
	char      replacejuka                   [   4];                                                  // [long      ,    4] ��밡                                             ��                                                   
	char      forevol                       [   4];                                                  // [long      ,    4] �ܱ��κ�����                                       ��                                                   
	char      forerate                      [   4];                                                  // [float     ,    4] �ܱ��κ�����                                       ��                                                   
	char      foretoday                     [   4];                                                  // [long      ,    4] �ܱ�����������                                     ��                                                   
	char      forebefore                    [   4];                                                  // [long      ,    4] �ܱ�����������                                     ��                                                   
	char      closemonth                    [   4];                                                  // [long      ,    4] ����                                             ��                                                   
	char      cntstocks                     [   4];                                                  // [long      ,    4] �����ֽļ�                                         ��                                                   
	char      capmoney                      [   4];                                                  // [long      ,    4] �ں���                                             ��                                                   
	char      per                           [   4];                                                  // [float     ,    4] PER                                                ��                                                   
	char      closememe                     [  12];                                                  // [varstring ,   12] �����Ÿſ���                                       ��                                                   
	char      memesu                        [   4];                                                  // [long      ,    4] �Ÿż�������                                       ��                                                   
	char      rentrestrate                  [   4];                                                  // [float     ,    4] �����ܰ���                                         ��                                                   
	char      creditrestrate                [   4];                                                  // [float     ,    4] �����ܰ���                                         ��                                                   
	char      securities                    [   3];                                                  // [varstring ,    3] ����ּ���                                         ��                                                   
	char      registerday                   [  10];                                                  // [varstring ,   10] �����                                             ��                                                   
	char      monrate                       [   4];                                                  // [float     ,    4] ȸ����                                             ��                                                   
} DSO300001_OutBlock1, *LP_DSO300001_OutBlock1;
#define NAME_DSO300001_OutBlock1     "OutBlock1"

typedef struct _DSO300001_OutBlock2
{
	char      highjuka                      [   4];    // [long      ,    4] �ְ�                                             ��                                                   
	char      highjukaday                   [   7];    // [varstring ,    7] �ְ���                                           ��                                                   
	char      lowjuka                       [   4];    // [long      ,    4] ������                                             ��                                                   
	char      lowjukaday                    [   7];    // [varstring ,    7] ��������                                           ��                                                   
} DSO300001_OutBlock2, *LP_DSO300001_OutBlock2;
#define NAME_DSO300001_OutBlock2     "OutBlock2"

typedef struct _DSO300001_OutBlock3
{
	char      medocomno                     [   3];    // [varstring ,    3] �ŵ�ȸ����                                         ��                                                   
	char      medovol                       [   4];    // [long      ,    4] �ŵ�����                                           ��                                                   
	char      mesucomno                     [   3];    // [varstring ,    3] �ż�ȸ����                                         ��                                                   
	char      mesuvol                       [   4];    // [long      ,    4] �ż�����                                           ��                                                   
} DSO300001_OutBlock3, *LP_DSO300001_OutBlock3;
#define NAME_DSO300001_OutBlock3     "OutBlock3"

typedef struct _DSO300001_OutBlock4
{
	char      _ecncurjuka                    ;
	char      ecncurjuka                    [   4];													 // [long      ,    4] ���簡                                             ��                                                   
	char      _ecndebi                       ;
	char      ecndebi                       [   4];													 // [long      ,    4] ���                                               ��                                                   
	char      ecnrate                       [   4];                                                  // [float     ,    4] �����                                             ��                                                   
	char      ecnvolume                     [   4];                                                  // [long      ,    4] �ŷ���                                             ��                                                   
	char      ecnmoney                      [   4];                                                  // [long      ,    4] ���(õ��)                                         ��                                                   
	char      _ecnstartjuka                  ;
	char      ecnstartjuka                  [   4];													 // [long      ,    4] �ð�                                               ��                                                   
	char      _ecnhighjuka                   ;
	char      ecnhighjuka                   [   4];													 // [long      ,    4] ��                                               ��                                                   
	char      _ecnlowjuka                    ;
	char      ecnlowjuka                    [   4];													 // [long      ,    4] ����                                               ��                                                   
	char      foretoday2                    [   8];                                                  // [double    ,    8] �ܱ�����������                                     ��                                                   
	char      forebefore2                   [   8];                                                  // [double    ,    8] �ܱ�����������                                     ��                                                   
	char      res2                          [   4];                                                  // [long      ,    4] 2������                                            ��                                                   
	char      res1                          [   4];                                                  // [long      ,    4] 1������                                            ��                                                   
	char      pivot                         [   4];                                                  // [long      ,    4] �Ǻ�                                               ��                                                   
	char      sup1                          [   4];                                                  // [long      ,    4] 1������                                            ��                                                   
	char      sup2                          [   4];                                                  // [long      ,    4] 2������                                            ��                                                   
	char      stockgubun                    [  29];                                                  // [varstring ,   29] �ڻ��ֱ���                                         ��                                                   
	char      stockvolume                   [   4];                                                  // [long      ,    4] �ڻ��ֽ�û��                                       ��                                                   
	char      stockchevol                   [   4];                                                  // [long      ,    4] �ڻ���ü�ᷮ                                       ��                                                   
	char      supdate                       [   4];                                                  // [long      ,    4] ������                                             ��                                                   
	char      flowstocks                    [   4];                                                  // [long      ,    4] ��������                                           ��                                                   
	char      lporder                       [  10];                                                  // [varstring ,   10] lp�ֹ����ɿ���                                     ��                                                   
	char      spread                        [   4];                                                  // [float     ,    4] ��������                                           ��                                                   
	char      minhokamulti                  [   4];                                                  // [long      ,    4] �ּ�ȣ���������                                   ��                                                   
	char      lpcode1                       [   3];                                                  // [varstring ,    3] lp1                                                ��                                                   
	char      lpcode2                       [   3];                                                  // [varstring ,    3] lp2                                                ��                                                   
	char      lpcode3                       [   3];                                                  // [varstring ,    3] lp3                                                ��                                                   
	char      lpcode4                       [   3];                                                  // [varstring ,    3] lp4                                                ��                                                   
	char      lpcode5                       [   3];                                                  // [varstring ,    3] lp5                                                ��                                                   
	char      roundstock                    [  20];                                                  // [varstring ,   20] ��ȸ���忩��                                       ��                                                   
	char      sellvolume                    [   4];                                                  // [long      ,    4] ���ŵ�����                                         ��                                                   
	char      sellmoney                     [   4];                                                  // [long      ,    4] ���ŵ����                                         ��                                                   
	char      borrow                        [   6];                                                  // [varstring ,    6] �������ɿ���                                       ��                                                   
	char      presell                       [   6];                                                  // [varstring ,    6] ���ŵ��Ұ�����                                     ��                                                   
	char      pbr                           [   4];                                                  // [float     ,    4] PBR                                                ��                                                   
	char      eps                           [   4];                                                  // [long      ,    4] EPS                                                ��                                                   
	char      bps                           [   4];                                                  // [long      ,    4] BPS                                                ��                                                   
	char      upcode                        [   4];                                                  // [long      ,    4] �����ڵ�                                           ��                                                   
	char      loanvolume                    [   8];                                                  // [double    ,    8] �����ܰ�                                           ��                                                   
	char      progsunmesu                   [   4];                                                  // [long      ,    4] ���α׷����ż�����                                 ��                                                   
	char      currencycode                  [   3];                                                  // [varstring ,    3] ȭ�����                                           ��                                                   
	char      roa                           [   4];                                                  // [float     ,    4] ROA                                                ��                                                   
	char      roe                           [   4];                                                  // [float     ,    4] ROE                                                ��                                                   
	char      progchasunmesu                [   4];                                                  // [long      ,    4] �������α׷����ż�_����                            ��                                                   
	char      progbisunmesu                 [   4];                                                  // [long      ,    4] ���������α׷����ż�_����                          ��                                                   
	char      sellbefvolume                 [   8];                                                  // [double    ,    8] ���ϰ��ŵ���                                       ��                                                   
} DSO300001_OutBlock4, *LP_DSO300001_OutBlock4;
#define NAME_DSO300001_OutBlock4     "OutBlock4"

#pragma pack( pop )