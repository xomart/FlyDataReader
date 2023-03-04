//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#pragma hdrstop

#include "MForm.h"
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma pack (push, 1)
using namespace std;
const int rr = 500;

enum SK_TYPE { _SK_ASK1975 = 0, _SK_GSK     = 1, _SK_GSKZ  = 2, _SK_ASKTES = 6, 
			   _SK_ASKTE   = 7, _SK_OSK1975 = 8, _SK_OSKTE = 9, _SK_OSKTES = 10, 
			   _SK_ASK2000 =11, _SK_OSK2000 =12, _SK_RLN   = 101};

//------------------------------------------------------------------------------- 
// Возможные события, наступление которых отслеживавет модель движения
//------------------------------------------------------------------------------- 
enum ModEventName{
	ModEvent_EMPTY = 0,				// Признак отсутствия события ---> отсутствия расчёта параметров	 
	ModEvent_INIT = 1,				// Инициализация МД
	ModEvent_STEP = 2,				// Выполнен один шаг интегрирования	 
	ModEvent_BKSTEP = 3,			// Отшагивание в пределах витка для уточнения чего либо

	ModEvent_DUON = 4,				// 	 
	ModEvent_DUSTEPON = 5,			// 	 
	ModEvent_DUOFF = 6,				// 	 

	ModEvent_VITVU = 7,				// Восходящий узел витка	 
	ModEvent_VITNU = 8,				// Нисходящий узел витка
	ModEvent_HMIN = 9,				// Минимальная высота
	ModEvent_HMAX = 10,				// Максимальная высота
	ModEvent_RMIN = 11,				// Минимальный радиус
	ModEvent_RMAX = 12,				// Максимальный радиус
	ModEvent_SHADOWBEG = 13,		// Начало тени
	ModEvent_SHADOWEND = 14,		// Конец тени

	ModEvent_ONBREAKTIME = 15,		// Достигнут предельный момент времени заданный параметром notFurtherTime в функции GoStepA
	ModEvent_ONTIME = 16,			// Выполнено прогнозирование до витка
	ModEvent_ONVIT = 17,			// Выполнено прогнозирование до заданного момента времени
	ModEvent_ONARG = 18,			// Выполнено прогнозирование до заданного аргумента широты

	ModEvent_ZRVBEG = 100,			// Начало ЗРВ
	ModEvent_ZRVEND = 101,			// Конец ЗРВ
	ModEvent_ZRVPARAM = 102			// Момент прохождения параметра ЗРВ
};


AnsiString dig;
struct TIME {
	short  h;       // Часы         (0 - 23)
	short  m;       // Минуты       (0 - 59)
	short  s;       // Секунды      (0 - 59)
	double d;       // Доли секунды (  < 1 )
};

TForm1 *Form1;
double xmin, xmax, ymin, ymax;

static TIniFile *FNUfile; // Файл НУ
static TIniFile *NUfile;  //  to view

AnsiString USOFileName = ExtractFileDir(Application->ExeName);

struct TOEl
{
double a; // Большая полуось в ДТКМ
double e; // эксцентриситет
double i; // Наклонение
//double  //
};

AnsiString foldername;

struct TNU{
 double pos[3];
 double vel[3];
};

struct TFlyData
{
int DD;
int MM;
int YY;
TIME t;
double X;
double Y;
double Z;
double Vx;
double Vy;
double Vz;
double dolgota; // Долгота
double shirota; // Широта
double h;       // Высота
double n;       // Наклонение
double period;  // Период
double R;
long v;         // Виток для 2000
};

struct TFlyData peoplej[rr];

int kadr;

void scenary_status(bool sc_act, AnsiString ScName){
 if(sc_act){
       Form1->scenary_st->Caption=ScName;
        } else Form1->scenary_st->Caption="Нет";
}

void loadresult(string fname) {   //v4
	fstream f;
	f.open((char*)&fname, fstream::out);
	if (f) {
		f.read((char*)&peoplej, sizeof(TFlyData));
	}
	f.close();
}

void ListFiles(AnsiString path, TStrings*  List)
{
// Эта процедура выводит список файлов и  вызывает
// саму себя для всех  каталогов
TSearchRec sr;
if (FindFirst(path+"*.*",  faAnyFile, sr) == 0)
{
     do
     {
         if (sr.Attr &  faDirectory)
          {
              if (sr.Name!=".")
              if  (sr.Name!="..")
              {
                  ListFiles(path+sr.Name+"\\",List);// Рекурсивный  вызов
              }
          }
          else
          {
           AnsiString  Ext=ExtractFileExt(sr.Name).UpperCase();
           if  (Ext==".ini") {
           List->Add(path+sr.Name);
           Form1->ScenaryTV->Items->AddChild(Form1->ScenaryTV->Items->GetFirstNode(),sr.Name);
           }
          }
     }
     while  (FindNext(sr) ==  0);
     FindClose(sr);
}
    Application->ProcessMessages();
}


void addbf73(int NU){
        Form1->bf73m->Clear();
  Form1->bf73m->Lines->Add("\nБАЛЛИСТИЧЕСКИЕ ФОРМЫ        Дата 13.02.1956     Время 12:32:12\n");
  Form1->bf73m->Lines->Add("***************************************************************");
  Form1->bf73m->Lines->Add("\n");
  Form1->bf73m->Lines->Add(" Форма 73     НУ-"+IntToStr(NU)+"      N Обьекта");
  Form1->bf73m->Lines->Add("\n");

}

// Debug
char * filename = "result.dat";

int save(char * filename, struct TFlyData *p);
int load(char * filename);
int ke;

// DEBUG END
AnsiString rett(double t){
  //      M
  double m = t/60;
  double s = t-(m*60);
 return FloatToStr(m)+"."+FloatToStr(s);
}


void additem(TFlyData *S){
TDateTime mDT;
AnsiString timex[3];
if(S->t.h<10)timex[0] = "0"+IntToStr(S->t.h); else timex[0] = IntToStr(S->t.h);
if(S->t.m<10)timex[1] = "0"+IntToStr(S->t.m); else timex[1] = IntToStr(S->t.m);
if(S->t.s<10)timex[2] = "0"+IntToStr(S->t.s); else timex[2] = IntToStr(S->t.s);
AnsiString St1 = timex[0]+":"+timex[1]+":"+timex[2]+FormatFloat(".000",S->t.d);
 TListItem *M;
M = Form1->resultlv->Items->Add();
M->Caption = IntToStr(kadr);
M->SubItems->Add(St1);
M->SubItems->Add(FormatFloat("0"+dig,S->X));          // Положение
M->SubItems->Add(FormatFloat("0"+dig,S->Y));
M->SubItems->Add(FormatFloat("0"+dig,S->Z));
M->SubItems->Add(FormatFloat("0"+dig,S->Vx));         // Скорости
M->SubItems->Add(FormatFloat("0"+dig,S->Vy));
M->SubItems->Add(FormatFloat("0"+dig,S->Vz));
M->SubItems->Add(FormatFloat("0.000",S->dolgota));    // Долгота
M->SubItems->Add(FormatFloat("0.000",S->shirota));    // Широта
M->SubItems->Add(FormatFloat("000.000",S->h));          // Высота
M->SubItems->Add(FormatFloat("0000.0000",S->R));          // Высота
int m = S->period/60;
M->SubItems->Add(IntToStr(m)+"."+FormatFloat("00.",S->period-(m*60)));     // Наклонение
M->SubItems->Add(FloatToStr(S->v));          // Виток
}

char razdelitel[]=" ,./;:";
int n; // Колличество элементов массива
//TFlyData* FDMas = new TFlyData[n];  // Рабочий дин. массив

void AddXY(double X, double Y){
//if(X>179) Form1->TC->Series[0]->AddXY(X-360,Y,"", clWhite); else
//Form1->TC->Series[0]->AddXY(X,Y,"", clWhite);
double lon_new = fmod((X+180),360)-180;
Form1->TC->Series[0]->AddXY(lon_new,Y,"", clWhite);
}

void AddXYh(double X, double Y){
 Form1->Hgr->Series[0]->AddXY(X,Y,"", clBlue);
}

void Nresult(){
 	fstream f;
	f.open((char*)Form1->Edit20->Text.c_str(), fstream::out);
	if (f) {
         for (int k = 0; k<200; k++)
{
    kadr++;
    AddXY(peoplej[k].dolgota,peoplej[k].shirota);
    //Form1->ListBox1->Items->Add("Долгота - "+FloatToStr((ptr + k)->dolgota) );
    additem(peoplej);
}
		f.read((char*)&peoplej, sizeof(peoplej) );
	} //else Form1->Label50->Caption="VAR 3 - No File";
	f.close();
}

int save(char * filename, struct TFlyData * st, int n)
{
    FILE * fp;
    char *c;
 
    // число записываемых байтов
    int size = n * sizeof(struct TFlyData);
     
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    // записываем количество структур
    c = (char *)&n;
    for (int i = 0; i<sizeof(int); i++)
    {
        putc(*c++, fp);
    }
 
    // посимвольно записываем в файл все структуры
    c = (char *)st;
    for (int i = 0; i < size; i++)
    {
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}
 
// загрузка из файла массива структур

void loadload(AnsiString filename){ // V1   WORKING
int ST = Form1->showiter->Text.ToInt();
int SI = Form1->Edit19->Text.ToInt();
ifstream fin;
    fin.open(filename.c_str(), std::ios::binary);    //    std::ios::binary ios::binary | ios::trunc
    if(fin.is_open()){
    fin.read(reinterpret_cast<char*>(peoplej), SI * sizeof(TFlyData));
    fin.close();  for (int k = ST; k<SI; k++)
{
    kadr++;
    AddXY(peoplej[k].dolgota,peoplej[k].shirota);   // Fligt Trace
    AddXYh(k,peoplej[k].R);                         // H
    additem(&peoplej[k]);
} }

}

void ScanNU(AnsiString Path)
{
Form1->ListBox2->Clear();
TSearchRec tsch_r;
    if(FindFirst(Path + "*.ini", faAnyFile, tsch_r) == 0)
    {
        do
        {   //--------------------------------
            Form1->ListBox2->Items->Add(tsch_r.Name);
        }   //--------------------------------
        while(FindNext(tsch_r) == 0);
    }
 
    FindClose(tsch_r);
}

void loadini(AnsiString fname){
NUfile = new TIniFile(fname);
Form1->s_vsx->Caption = NUfile->ReadString("StateVector","X",0);
Form1->s_vsy->Caption = NUfile->ReadString("StateVector","Y",0);
Form1->s_vsz->Caption = NUfile->ReadString("StateVector","Z",0);
Form1->s_vsvx->Caption = NUfile->ReadString("StateVector","Vx",0);
Form1->s_vsvy->Caption = NUfile->ReadString("StateVector","Vy",0);
Form1->s_vsvz->Caption = NUfile->ReadString("StateVector","VZ",0);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
double temp_d;
temp_d = StrToFloat(Edit6->Text);
if(temp_d>180)
//temp_d = (360 - StrToFloat(Edit6->Text))*-1;

TC->Series[0]->AddXY(temp_d,StrToFloat(Edit5->Text),"", clWhite);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
TC->Series[0]->Clear();
resultlv->Clear();
kadr=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
dig=".0000";
TC->BottomAxis->SetMinMax(-180,180);
TC->LeftAxis->SetMinMax(-90,90);
//Hgr->LeftAxis->SetMinMax(100,500);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveNUClick(TObject *Sender)
{
AnsiString NuFileName;
Save->InitialDir=ExtractFileDir(Application->ExeName);
if(Save->Execute()){
FNUfile = new TIniFile(Save->FileName);
if(sm_ini->Checked){
FNUfile->WriteString("StateVector","X",svx->Text);
FNUfile->WriteString("StateVector","Y",svy->Text);
FNUfile->WriteString("StateVector","Z",svz->Text);
FNUfile->WriteString("StateVector","Vx",svvx->Text);
FNUfile->WriteString("StateVector","Vy",svvy->Text);
FNUfile->WriteString("StateVector","Vz",svvz->Text);
FNUfile->WriteString("DateTime","SD_D",DateToStr(StartDatePicker->Date).SubString(0,2));
FNUfile->WriteString("DateTime","SD_M",DateToStr(StartDatePicker->Date).SubString(4,2));
FNUfile->WriteString("DateTime","SD_Y",DateToStr(StartDatePicker->Date).SubString(7,4));
FNUfile->WriteString("DateTime","ST_H",nhh->Text);
FNUfile->WriteString("DateTime","ST_M",nnn->Text);
FNUfile->WriteString("DateTime","ST_S",nss->Text);
FNUfile->WriteString("DateTime","ST_Z","0."+nzzz->Text);
FNUfile->WriteString("DateTime","ED_D",DateToStr(EndDatePicker->Date).SubString(0,2));
FNUfile->WriteString("DateTime","ED_M",DateToStr(EndDatePicker->Date).SubString(4,2));
FNUfile->WriteString("DateTime","ED_Y",DateToStr(EndDatePicker->Date).SubString(7,4));
FNUfile->WriteString("DateTime","ET_H",khh->Text);
FNUfile->WriteString("DateTime","ET_M",knn->Text);
FNUfile->WriteString("DateTime","ET_S",kss->Text);
FNUfile->WriteString("DateTime","ET_Z","0."+kzzz->Text);
FNUfile->WriteString("SK","SKNum",skn->ItemIndex);
FNUfile->WriteString("KA","Mass",mass->Text);
FNUfile->WriteString("KA","Fuel",fuel->Text);
FNUfile->WriteString("KA","Sb",sb->Text);
FNUfile->WriteString("KA","Sd",sd->Text);
FNUfile->WriteString("Misc","Vitok",vitok->Text);
FNUfile->WriteString("Misc","SK",skn->ItemIndex);
FNUfile->WriteString("Misc","Step",istep->Text);
if(lsf->Checked){
FNUfile->WriteString("LSF","Num",lsfn->Text);
if(sun->Checked)FNUfile->WriteString("LSF","Sun","1");
else FNUfile->WriteString("LSF","Sun","0");
if(moon->Checked)FNUfile->WriteString("LSF","Moon","1");
else FNUfile->WriteString("LSF","Moon","0");
}
} else
if(sm_uof->Checked) {

}

}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
Orbit->BottomAxis->SetMinMax(StrToInt(Edit12->Text),StrToInt(Edit13->Text));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
Orbit->LeftAxis->SetMinMax(StrToInt(Edit15->Text),StrToInt(Edit14->Text));        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
Orbit->Series[0]->AddXY(StrToFloat(Edit17->Text),StrToFloat(Edit16->Text),"", clRed);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
//Form2->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button11Click(TObject *Sender)
{
loadresult("test.dat");
for (int i = 0; i < 200; i++){
   additem(peoplej);
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N1Click(TObject *Sender)
{
//resultlv->ItemFocused->~TListItem()
PageControl1->TabIndex=4;
addbf73(54);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
TC->Series[0]->Clear();
Hgr->Series[0]->Clear();
resultlv->Clear();
kadr=0;
if (loadg->Execute())
{
loadload(loadg->FileName);
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
if (loadg->Execute())
{
loadresult(loadg->FileName.c_str());
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::startbClick(TObject *Sender)
{
int Rc;
Rc = WinExec("Fly.exe", SW_SHOWMINNOACTIVE);
TC->Series[0]->Clear();
Hgr->Series[0]->Clear();
resultlv->Clear();
kadr=0;
//if (loadg->Execute())
//{
lt->Enabled=1;
//}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d4Click(TObject *Sender)
{
dig=".0000";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d6Click(TObject *Sender)
{
dig=".000000";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::d8Click(TObject *Sender)
{
dig=".00000000";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ltTimer(TObject *Sender)
{
loadload("out.dat");
lt->Enabled=0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
loadload("out.dat");        
}
//---------------------------------------------------------------------------
HANDLE hProc = NULL;
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcess(NULL, "Fly.exe", NULL, NULL, false, 0, NULL, NULL, &si, &pi))
    {
        ShowMessage("Ошибка запуска");
    }
    else
    {
        hProc = pi.hProcess;
        Tmr_1->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Tmr_1Timer(TObject *Sender)
{
   DWORD exitCode;
    GetExitCodeProcess(hProc, &exitCode);
 
    if (exitCode != STILL_ACTIVE)
    {
        Tmr_1->Enabled = false;
        loadload("out.dat");
    }        
}
//---------------------------------------------------------------------------
AnsiString fna;
void __fastcall TForm1::ScenaryTVMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button == mbLeft) {
        // проверяем, что мы кликнули именно по строке узла
        if (ScenaryTV->GetHitTestInfoAt(X, Y).Contains(htOnItem)) {
            TTreeNode *NodeClicked = ScenaryTV->GetNodeAt(X, Y);
            if (NodeClicked) {
                const AnsiString sNodeText = NodeClicked->Text;
                groupl->Caption = sNodeText;// работаем с полученным текстом узла
                ScanNU(GetCurrentDir()+"\\scenary\\"+sNodeText+"\\");
                foldername = GetCurrentDir()+"\\scenary\\"+sNodeText+"\\";
                fna = "\\scenary\\"+sNodeText+"\\";
            }
        }
    }
}
//---------------------------------------------------------------------------
AnsiString fnmm;
void __fastcall TForm1::ListBox2Click(TObject *Sender)
{
scenary_st->Caption=ListBox2->Items->Strings[ListBox2->ItemIndex];
loadini(foldername+ListBox2->Items->Strings[ListBox2->ItemIndex]);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Panel1Click(TObject *Sender)
{
TC->Series[0]->Clear();
Hgr->Series[0]->Clear();
resultlv->Clear();
kadr=0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    AnsiString fnname = fna+ListBox2->Items->Strings[ListBox2->ItemIndex];
    //Label62->Caption = fnname.Delete(1,1);
    AnsiString s_templ = "Fly.exe "+fnname.Delete(1,1);
    AnsiString ttuuyy = "Fly.exe testa.ini";
    if (!CreateProcess(NULL, s_templ.c_str(), NULL, NULL, false, 0, NULL, NULL, &si, &pi))
    {
        ShowMessage("Ошибка запуска");
    }
    else
    {
        hProc = pi.hProcess;
        Tmr_1->Enabled = true;
    }        
}
//---------------------------------------------------------------------------



