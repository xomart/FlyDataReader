//---------------------------------------------------------------------------

#ifndef MFormH
#define MFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TChart *TC;
        TLineSeries *Series1;
        TButton *Button4;
        TGroupBox *GroupBox4;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit5;
        TEdit *Edit6;
        TButton *Button3;
        TLabel *Label1;
        TLabel *Label2;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TEdit *svx;
        TEdit *svy;
        TLabel *Label4;
        TEdit *svz;
        TLabel *Label7;
        TGroupBox *GroupBox3;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *svvx;
        TEdit *svvy;
        TEdit *svvz;
        TButton *SaveNU;
        TGroupBox *GroupBox5;
        TSaveDialog *Save;
        TComboBox *skn;
        TGroupBox *GroupBox6;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *vitok;
        TGroupBox *GroupBox7;
        TGroupBox *GroupBox8;
        TCheckBox *lsf;
        TLabel *Label13;
        TEdit *lsfn;
        TLabel *Label14;
        TCheckBox *sun;
        TCheckBox *moon;
        TGroupBox *GroupBox9;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TComboBox *ComboBox2;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *Edit3;
        TLabel *Label17;
        TEdit *Edit4;
        TLabel *Label18;
        TComboBox *ComboBox3;
        TLabel *Label19;
        TComboBox *ComboBox4;
        TGroupBox *GroupBox10;
        TEdit *Edit7;
        TLabel *Label20;
        TGroupBox *GroupBox11;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TLabel *Label21;
        TEdit *Edit8;
        TTabSheet *TabSheet4;
        TCheckBox *CheckBox12;
        TLabel *Label22;
        TEdit *mass;
        TLabel *Label23;
        TLabel *Label24;
        TEdit *fuel;
        TLabel *Label25;
        TLabel *Label26;
        TEdit *sb;
        TLabel *Label27;
        TEdit *sd;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox12;
        TLabel *Label28;
        TEdit *Edit1;
        TLabel *Label29;
        TLabel *Label30;
        TEdit *Edit2;
        TLabel *Label31;
        TLabel *Label32;
        TEdit *Edit9;
        TLabel *Label33;
        TLabel *Label34;
        TEdit *Edit10;
        TLabel *Label35;
        TEdit *Edit11;
        TLabel *Label36;
        TTabSheet *TabSheet6;
        TChart *Orbit;
        TLineSeries *Series2;
        TGroupBox *GroupBox13;
        TLabel *Label38;
        TLabel *Label39;
        TEdit *Edit12;
        TEdit *Edit13;
        TButton *Button6;
        TGroupBox *GroupBox14;
        TLabel *Label40;
        TLabel *Label41;
        TEdit *Edit14;
        TEdit *Edit15;
        TButton *Button7;
        TGroupBox *GroupBox15;
        TLabel *Label42;
        TLabel *Label43;
        TEdit *Edit16;
        TEdit *Edit17;
        TButton *Button8;
        TGroupBox *GroupBox16;
        TDateTimePicker *StartDatePicker;
        TGroupBox *GroupBox17;
        TDateTimePicker *EndDatePicker;
        TEdit *Edit18;
        TLabel *Label44;
        TLabel *Label45;
        TTabSheet *TabSheet7;
        TTreeView *ScenaryTV;
        TLabel *Label46;
        TGroupBox *GroupBox18;
        TPageControl *PageControl2;
        TTabSheet *TabSheet8;
        TLabel *Label47;
        TLabel *scenary_st;
        TPageControl *PageControl3;
        TTabSheet *TabSheet9;
        TListView *resultlv;
        TTabSheet *TabSheet10;
        TPopupMenu *PopupMenu1;
        TMenuItem *N1;
        TPageControl *PageControl4;
        TTabSheet *TabSheet11;
        TMemo *bf73m;
        TTabSheet *TabSheet12;
        TCheckBox *CheckBox1;
        TOpenDialog *loadg;
        TGroupBox *GroupBox19;
        TRadioButton *sm_ini;
        TRadioButton *sm_uof;
        TTabSheet *TabSheet13;
        TPageControl *PageControl5;
        TTabSheet *TabSheet14;
        TGroupBox *GroupBox20;
        TGroupBox *GroupBox21;
        TCheckBox *CheckBox2;
        TGroupBox *GroupBox22;
        TButton *Button1;
        TGroupBox *GroupBox23;
        TLabel *Label48;
        TLabel *Label52;
        TLabel *Label53;
        TLabel *Label54;
        TLabel *Label55;
        TLabel *Label56;
        TLabel *Label57;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label60;
        TLabel *Label61;
        TLabel *Label62;
        TListBox *ListBox1;
        TButton *Button14;
        TButton *Button9;
        TChart *Hgr;
        TPanel *startb;
        TPanel *panr;
        TLabel *Label51;
        TLabel *Label63;
        TLabel *Label64;
        TEdit *Edit20;
        TLabel *Label65;
        TEdit *showiter;
        TLineSeries *Series3;
        TGroupBox *GroupBox24;
        TRadioButton *d4;
        TRadioButton *d6;
        TRadioButton *d8;
        TEdit *nhh;
        TEdit *nnn;
        TEdit *nss;
        TEdit *nzzz;
        TLabel *Label50;
        TLabel *Label66;
        TLabel *Label67;
        TEdit *khh;
        TLabel *Label68;
        TEdit *knn;
        TLabel *Label69;
        TEdit *kss;
        TLabel *Label70;
        TEdit *kzzz;
        TTimer *lt;
        TEdit *Edit19;
        TLabel *Label37;
        TLabel *Label49;
        TLabel *version;
        TLabel *Label71;
        TLabel *Label72;
        TGroupBox *GroupBox25;
        TButton *Button2;
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SaveNUClick(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall startbClick(TObject *Sender);
        void __fastcall d4Click(TObject *Sender);
        void __fastcall d6Click(TObject *Sender);
        void __fastcall d8Click(TObject *Sender);
        void __fastcall ltTimer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
