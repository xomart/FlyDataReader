//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#pragma hdrstop

#include "MForm.h"
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma pack (push, 1)
using namespace std;
struct TIME {
	short  h;       // Часы         (0 - 23)
	short  m;       // Минуты       (0 - 59)
	short  s;       // Секунды      (0 - 59)
	double d;       // Доли секунды (  < 1 )
};

TForm1 *Form1;
double xmin, xmax, ymin, ymax;

static TIniFile *FNUfile; // Файл НУ

AnsiString USOFileName = ExtractFileDir(Application->ExeName);

struct TFlyData
{
int DD;
int MM;
int YY;
double t[4];
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
double period;
//TIME t;
int v;
};

struct TFlyData peoplej[200];

int kadr;

struct Contact {
    char number[11];
    char adress[50];
    char sname[50];
};

void loadfileg(){
  std::ifstream fin("input.dot", std::ios::in | std::ios::binary);
    // здесь будем хранить считанные структуры
    std::vector<Contact> vec;
    // временная переменная
    Contact temp;
    // пока есть что читать, цикл продолжается
    while (fin.read((char*)&temp, sizeof(Contact))) {
        // запихиваем в конец вектора считанную структуру
        vec.push_back(temp);
    };
    // не забудем закрыть файл
    fin.close();
}

void scenary_status(bool sc_act, AnsiString ScName){
 if(sc_act){
       Form1->scenary_st->Caption=ScName;
        } else Form1->scenary_st->Caption="Нет";
}

void loadfromf(AnsiString filename,AnsiString out){
char line[1024];
ifstream F("filenamefff.txt");
while(F.getline(line, sizeof(line), '\n'))
    {    //-------------------------
        Form1->Memo1->Lines->Append(line);
        //-------------------------       
        int l = strlen(line);
        //ShowMessage(l);
     }
}

void loadresult(string fname) {   //v4
	fstream f;
	f.open((char*)&fname, fstream::out);
	if (f) {
		f.read((char*)&peoplej, sizeof(TFlyData));
	}
	f.close();
}



void addbf73(int NU){
        Form1->bf73m->Clear();
  Form1->bf73m->Lines->Add("\nБАЛЛИСТИЧЕСКИЕ ФОРМЫ        Дата 13.02.1956     Время 12:32:12\n");
  Form1->bf73m->Lines->Add("***************************************************************");
  Form1->bf73m->Lines->Add("\n");
  Form1->bf73m->Lines->Add(" Форма 73     НУ-"+IntToStr(NU)+"      N Обьекта");

}

// Debug
char * filename = "result.dat";

//struct person
//{
//    char name[20];
//    int age;
//};

int save(char * filename, struct TFlyData *p);
int load(char * filename);
int ke;

// DEBUG END

void additem(TFlyData *S){
TDateTime mDT;
AnsiString St1 = S->t.h+":"+S->t.m;//+":"+S->t.s+".";
//+":"+S->NN;
//AnsiString St2 = ":"+S->SS;
//St += ":"+S->SS+"."+S->ZZZ;
//mDT = StrToTime(S->HH+":"+S->NN+":"+S->SS);  +":"+S->SS+"."+S->ZZZ
//mDT = StrToDateTime();
 TListItem *M;
M = Form1->resultlv->Items->Add();
M->Caption = IntToStr(kadr);
M->SubItems->Add(St1);
M->SubItems->Add(FloatToStr(S->X));
M->SubItems->Add(FloatToStr(S->Y));
M->SubItems->Add(FloatToStr(S->Z));
M->SubItems->Add(FloatToStr(S->Vx));
M->SubItems->Add(FloatToStr(S->Vy));
M->SubItems->Add(FloatToStr(S->Vz));
M->SubItems->Add(FloatToStr(S->dolgota));
M->SubItems->Add(FloatToStr(S->shirota));
M->SubItems->Add(FloatToStr(S->h));
M->SubItems->Add(FloatToStr(S->n));
M->SubItems->Add(FloatToStr(S->v));
}

char razdelitel[]=" ,./;:";
int n; // Колличество элементов массива
//TFlyData* FDMas = new TFlyData[n];  // Рабочий дин. массив

void AddXY(double X, double Y){
 Form1->TC->Series[0]->AddXY(X,Y,"", clWhite);
}

void AddXYh(double X, double Y){
 Form1->Hgr->Series[0]->AddXY(X,Y,"", clBlue);
}

void ReadData(){
 //for (int i = n - 1 ; i >= 0; i--) {
    //cout << dinamich_array[i] << " ";  // ??????? ???????? ???? ?????
 // }
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
	} else Form1->Label50->Caption="VAR 3 - No File";
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
int load(char * filename)
{
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;

    // выделяем память для количества данных
    int *pti = (int *)malloc(m);
 
    if ((fp = fopen(filename, "r")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    // считываем количество структур
    c = (char *)pti;
    while (m>0)
    {
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    //получаем число элементов
    n = *pti;
    ke = n;
 
    // выделяем память для считанного массива структур
    struct TFlyData * ptr = (struct TFlyData *) malloc(n * sizeof(struct TFlyData));
    c = (char *)ptr;
    // после записи считываем посимвольно из файла
    while ((i= getc(fp))!=EOF)
    {
        *c = i;
        c++;
    }
    // перебор загруженных элементов и вывод на консоль
    printf("\n%d people in the file stored\n\n", n);
for (int k = 0; k<n; k++)
{
    kadr++;
    AddXY((ptr + k)->dolgota,(ptr + k)->shirota);
    //Form1->ListBox1->Items->Add("Долгота - "+FloatToStr((ptr + k)->dolgota) );
    additem((ptr + k));
}
    Form1->Label1->Caption=IntToStr(n);
    free(pti);
    free(ptr);
    fclose(fp);
    return 0;
}

void TestA(){
//gfd
}

void DataToChart(){

//for (int k = 0; k<ke; k++)
//{
//    AddXY(TFLyData.
//}    reinterpret_cast<char*>
}

void loadload(AnsiString filename){ // V1
int SI = Form1->showiter->Text.ToInt();
ifstream fin;
    fin.open(filename.c_str(), std::ios::binary);    //    std::ios::binary ios::binary | ios::trunc
    if(fin.is_open()){
    fin.read(reinterpret_cast<char*>(peoplej), SI * sizeof(TFlyData));
    fin.close();  for (int k = 0; k<SI; k++)
{
    kadr++;
    AddXY(peoplej[k].dolgota,peoplej[k].shirota);
    AddXYh(peoplej[k].h,k);
    additem(&peoplej[k]);
} }

}

void load2(AnsiString filename){  // Финальный вариант
ifstream fin;
    fin.open(filename.c_str(), std::ios::binary);
    if(fin.is_open()){
    fin.read((char *)peoplej, 200*sizeof(TFlyData));
    fin.close();
    for (int k = 0; k<200; k++)
{
    kadr++;
    AddXY(peoplej[k].dolgota,peoplej[k].shirota);
    additem(&peoplej[k]);
} }

}

void newload(string filename){ // V2
  FILE* f;
  f = fopen(filename.c_str(), "wb");
  fread(peoplej, sizeof(peoplej[0]), 200, f);
  fclose(f);
  /*
    FILE * f = fopen("filename","wb");
fwrite(MasStruct,sizeof(MasStruct[0]),10,f);
fclose(f);
  */
  for (int k = 0; k<200; k++)
{
    kadr++;
    AddXY(peoplej[k].dolgota,peoplej[k].shirota);
    additem(&peoplej[k]);
}
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
temp_d = (360 - StrToFloat(Edit6->Text))*-1;

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

TC->BottomAxis->SetMinMax(0,360);
TC->LeftAxis->SetMinMax(-90,90);
Hgr->LeftAxis->SetMinMax(100,500);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
//load(filename);
load(Edit19->Text.c_str());
//Label1->Caption=person
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    //struct TFlyData people[] = { 104, 51, 194, 122, 48, 3195, 137, 43, 196 };
    //int nt = sizeof(people) / sizeof(people[0]);

    //save(filename, people, nt);
    //Label1->Caption=IntToStr(nt);
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
FNUfile->WriteString("DateTime","StartDate",DateToStr(StartDatePicker->Date));
FNUfile->WriteString("DateTime","StartTime",TimeToStr(StartTimePicker->Time));
FNUfile->WriteString("DateTime","EndDate",DateToStr(EndDatePicker->Date));
FNUfile->WriteString("DateTime","EndTime",TimeToStr(EndTimePicker->Time));
FNUfile->WriteString("SK","SKNum",skn->ItemIndex);
FNUfile->WriteString("KA","Mass",mass->Text);
FNUfile->WriteString("KA","Fuel",fuel->Text);
FNUfile->WriteString("KA","Sb",sb->Text);
FNUfile->WriteString("KA","Sd",sd->Text);
FNUfile->WriteString("Misc","Vitok",vitok->Text);
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


void __fastcall TForm1::Button10Click(TObject *Sender)
{
addbf73(54);
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

void __fastcall TForm1::loadrClick(TObject *Sender)
{
loadload("gfds");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
//resultlv->ItemFocused->~TListItem()
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
if (loadg->Execute())
{
loadload(loadg->FileName);
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
if (loadg->Execute())
{
newload(loadg->FileName.c_str());
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
if (loadg->Execute())
{
load(loadg->FileName.c_str());
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
panr->Caption=IntToStr(Rc);
}
//---------------------------------------------------------------------------

