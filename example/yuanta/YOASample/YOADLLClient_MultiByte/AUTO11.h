#pragma pack( push, 1 )

typedef struct _AUTO11_OutBlock1
{
	char      jongcode                      [   6];                                                  // [string    ,    6] �����ڵ�                                           ��                                                   
	char      sisegubun                     [   1];                                                  // [string    ,    1] �ü��޺�                                           ��                                                   
	char      updowngubun                   [   1];                                                  // [string    ,    1] �����Ѱ���������                                   ��                                                   
	char      _curjuka						 ;
	char      curjuka                       [   4];													 // [long      ,    4] ���簡                                             ��                                                   
	char      _startjuka                     ;
	char      startjuka                     [   4];													 // [long      ,    4] �ð�                                               ��                                                   
	char      _highjuka                      ;														 
	char      highjuka                      [   4];													 // [long      ,    4] ��                                               ��                                                   
	char      _lowjuka                       ;														 
	char      lowjuka                       [   4];													 // [long      ,    4] ����                                               ��                                                   
	char      _medohoka                      ;														 
	char      medohoka                      [   4];													 // [long      ,    4] �ŵ�ȣ��                                           ��                                                   
	char      _mesuhoka                      ;														 
	char      mesuhoka                      [   4];													 // [long      ,    4] �ż�ȣ��                                           ��                                                   
	char      FILLER1                       [   2];                                                  // [string    ,    2] 4bytes���߱�����                                   ��                                                   
	char      volume                        [   4];                                                  // [long      ,    4] �����ŷ���_�ִ���                                  ��                                                   
	char      money                         [   4];                                                  // [long      ,    4] �����ŷ����_õ����                                ��                                                   
	char      debirate                      [   4];                                                  // [float     ,    4] �����                                             ��                                                   
	char      time                          [   5];                                                  // [string    ,    5] �ð�_HH:SS                                         ��                                                   
	char      hightime                      [   5];                                                  // [string    ,    5] ���ð�                                           ��                                                   
	char      lowtime                       [   5];                                                  // [string    ,    5] �����ð�                                           ��                                                   
	char      _debi                          ;
	char      debi                          [   4];													 // [long      ,    4] ���ϴ��                                           ��                                                   
	char      _nowvol                        ;														 
	char      nowvol                        [   4];													 // [long      ,    4] ����ü�ᷮ                                         ��                                                   
	char      sisesec                       [   1];                                                  // [string    ,    1] �ü��޺�_��                                        ��                                                   
	char      siserate                      [   2];                                                  // [short     ,    2] �ü��޺�_�����                                    ��                                                   
	char      nowmoney                      [   4];                                                  // [long      ,    4] �����ŷ����                                       ��                                                   
	char      chejuka                       [   4];                                                  // [long      ,    4] ü�ᰡ                                             ��                                                   
	char      _chedebi                       ;
	char      chedebi                       [   4];													 // [long      ,    4] ü�ᰡ���ϴ��                                     ��                                                   
	char      jang                          [   1];                                                  // [string    ,    1] �屸��                                             ��                                                   
	char      updownflag                    [   1];                                                  // [string    ,    1] ���Ѱ�����_���а�                                  ��                                                   
	char      FILLER2                       [   1];                                                  // [string    ,    1] 4bytes���߱�����                                   ��                                                   
	char      time2                         [   8];                                                  // [string    ,    8] �ð�2                                              ��                                                   
	char      chegyulrate                   [   4];                                                  // [float     ,    4] ü�ᰭ��                                           ��                                                   
	char      mesusumvolume                 [   4];                                                  // [long      ,    4] �ż�ü����                                         ��                                                   
	char      _upjuka                        ;
	char      medosumvolume                 [   4];                                                  // [long      ,    4] �ŵ�ü����                                         ��                                                   
	char      upjuka                        [   4];													 // [long      ,    4] ���Ѱ�                                             ��                                                   
	char      _downjuka                      ;
	char      downjuka                      [   4];													 // [long      ,    4] ���Ѱ�                                             ��                                                   
	char      FILLER3                       [   2];                                                  // [string    ,    2] 4bytes���߱�����                                   ��                                                   
	char      befminvol                     [   4];                                                  // [long      ,    4] ���ϵ��ð��ŷ���                                   ��                                                   
	char      befmindebi                    [   4];                                                  // [long      ,    4] ���ϵ��ð����                                     ��                                                   
	char      startdebirate                 [   4];                                                  // [float     ,    4] �ð����                                         ��                                                   
	char      highdebirate                  [   4];                                                  // [float     ,    4] �����                                         ��                                                   
	char      lowdebirate                   [   4];                                                  // [float     ,    4] �������                                         ��                                                   
} AUTO11_OutBlock1, *LP_AUTO11_OutBlock1;
#define NAME_AUTO11_OutBlock1     "OutBlock1"

#pragma pack( pop )