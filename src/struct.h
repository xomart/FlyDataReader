enum ModEventName{
	ModEvent_EMPTY = 0,				// ������� ���������� ������� ---> ���������� ������� ����������	 
	ModEvent_INIT = 1,				// ������������� ��
	ModEvent_STEP = 2,				// �������� ���� ��� ��������������	 
	ModEvent_BKSTEP = 3,			// ����������� � �������� ����� ��� ��������� ���� ����

	ModEvent_DUON = 4,				// 	 
	ModEvent_DUSTEPON = 5,			// 	 
	ModEvent_DUOFF = 6,				// 	 

	ModEvent_VITVU = 7,				// ���������� ���� �����	 
	ModEvent_VITNU = 8,				// ���������� ���� �����
	ModEvent_HMIN = 9,				// ����������� ������
	ModEvent_HMAX = 10,				// ������������ ������
	ModEvent_RMIN = 11,				// ����������� ������
	ModEvent_RMAX = 12,				// ������������ ������
	ModEvent_SHADOWBEG = 13,		// ������ ����
	ModEvent_SHADOWEND = 14,		// ����� ����

	ModEvent_ONBREAKTIME = 15,		// ��������� ���������� ������ ������� �������� ���������� notFurtherTime � ������� GoStepA
	ModEvent_ONTIME = 16,			// ��������� ��������������� �� �����
	ModEvent_ONVIT = 17,			// ��������� ��������������� �� ��������� ������� �������
	ModEvent_ONARG = 18,			// ��������� ��������������� �� ��������� ��������� ������

	ModEvent_ZRVBEG = 100,			// ������ ���
	ModEvent_ZRVEND = 101,			// ����� ���
	ModEvent_ZRVPARAM = 102			// ������ ����������� ��������� ���
};

//-------------------------------------------------------------------------------
// �������������� ������� 
typedef struct ZMOD_EVENT {
ModEventName	ID ;		// ��� �������
double			ta ;		// ����� �������, ������� � ���   
double			Value ;		// �������� �������������� �������, ��� ����������� 
double			Value2 ;	// ������� �� ����� ������ ==> ����� ������� ��������
double			Value3 ;	//
double			Value4 ;	//
long			Value5 ;	//
} _ZMOD_EVENT ;				//

struct DATE
{
	int  d ;        // ����� (1 - 31)
	int  m ;        // ����� (1 - 12)
	int  g ;        // ���   (1900 - 9999)
};

struct FLYTIME_API TIME {
	short  h;       // ����         (0 - 23)
	short  m;       // ������       (0 - 59)
	short  s;       // �������      (0 - 59)
	double d;       // ���� ������� (  < 1 )
};

typedef struct ZSC_SI {
	ZMOD_EVENT E ;				// ������� ��� �������� �������� ������ ������ ���������� ��������
								// �������� ������ �����, ��������� ���, ����������� �����, ����������� ������ � �.�....
	long Vit75 ;				// ����� ��� ��� 1975, 2000 �����, 
	long Vit00 ;				// ������� � ������� ������� �����
	long VitTE ;
	long VitTES ;

	// ��������� ������� � ��, ��/���, ���
	double GSK[6] ;		// ���������� � �������� � ���
	double ASKTES[6] ;	// ���������� � �������� � ��� ������� ����� �������
	double ASKTE[6] ;	// ���������� � �������� � ��� ������� ��������
	double ASK1975[6] ;	// ���������� � �������� � ��� ����� 1975 ����
	double ASK2000[6] ;	// ���������� � �������� � ��� ����� 2000 ����
	double OSK1975[6] ;	// ������������ �������� ������ ������������ �������� ����� 1975 �.
	double OSKTE[6] ;	// ������������ �������� ������ ������������ �������� ������� �������� �����
	double OSKTES[6] ;	// ������������ �������� ������ ������������ �������� ������� ������� �����
	double OSK2000[6] ;	// ������������ �������� ������ ������������ �������� ����� 2000 �.
	double THBLFR[9] ;	// 0 - ������ ���. � ��������, 1 - ������ � ��, 2 - B, 3 - L, 
						// 4 - fi � ��������, 5 - R � ��,
						// 6 - ����������� �� ������ ��/���, 7 - ����������� �� ������� ��/���.
						// 8 - ���������� ��������������� ����� �����

	bool   isOSK1975bpl ;	// �������� ������� ������������ ��������� ��� ��������������
	bool   isOSK2000bpl ;	// ������� ��������� � �������� � ��������� ������
	bool   isOSKTEbpl ;
	bool   isOSKTESbpl ;

	double OSK1975bpl[6] ;	// ������������ �������� ������ ��� �������������� 
	double OSKTEbpl[6] ;	// ������� ��������� � �������� � ��������� ������
	double OSKTESbpl[6] ;
	double OSK2000bpl[6] ;

	// ������������� ��������� ������� ���������������� ���������
	double ExternalEq[EXTEQ_MAXCOUNT] ; // �������� ������� ����������
	int    ExternalEqCount ;// ����������� ������� ���������
	bool   ExternalEqOn ;	// ������� ���������� ������� ��������� ("��������� ��������")

	double SA[25] ;			// �������������� ������������ ("���� ������"). ��� ���� � ��������

	double   m ;			// ������� ����� ��, ��
	double   tmss ;			// ������� ������� ��������� �����, ���
	double   ta ;			// ����� �������, �� ����� �� ������� �������� ������ ������ ����������
	DATE     Data;			// ���� ���������������� (���� ����� � ���)
	TIME     Time ;			// ����� � ����� ������� � �������� (���������� ���������)
	//TheTimes T ;			// �� ��� ����� � ������� ;
} _ZSC_SI ;
 