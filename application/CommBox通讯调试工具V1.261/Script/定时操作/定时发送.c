#include "windows.h"
int edt1;
int cbHex;
int cbx1;
int tmr1;
int btn0,btn1,btn2;
void OnClose(int *sender)
{
    HideVclWin();
    CloseVclWin();
    ////PrintToCommWin("over");

}
void OnStart(void *sender)
{
    char s[200];
    GetProperty(cbx1,"text",s,20);
    int inv=atoi(s);
    printf("%d",inv);
    SetProperty(tmr1,"interval",inv);
    SetProperty(tmr1,"enabled",1);
    SetProperty(btn1,"enabled",0);
    SetProperty(btn2,"enabled",1);

    //myForm.btnStart.Enabled=false;
    //myForm.btnStop.Enabled=true;
}
void OnStop()
{
    SetProperty(tmr1,"enabled",0);
    SetProperty(btn1,"enabled",1);
    SetProperty(btn2,"enabled",0);

}
void OnTimer()
{
    char s[200];
    int ck;
    PrintToCommWin("abc");
    ck=GetProperty(cbHex,"checked",s,4);
    printf("checked:%s",s);
    GetProperty(edt1,"text",s,200);
    if(ck==1)
        SendHexString(s);
    else
        SendString(s);
}


void main()
{
    ClearOutputWin();   //��������������
    ClearCommWin();
    CloseInputWin();
    CloseCodeWin();//
    HideLeftTools();
    HideRightTools();
    HideOutputWin();
    ClearVclControls();
    int p=GetGuiWin();

    btn0=CreateComponentEx(p,"button","caption","�ر�",     "left",230,"top",70,"width",100,"height",30,"onclick",OnClose,NULL);//������ť
    btn1=CreateComponentEx(p,"button","caption","��ʼ����", "left",10,"top",70,"width",100,"height",30,"onclick",OnStart,NULL);//������ť
    btn2=CreateComponentEx(p,"button","caption","ֹͣ����", "left",120,"top",70,"width",100,"height",30,"onclick",OnStop,NULL);//������ť
    int lbl1=CreateComponentEx(p,"label", "caption","��������:","left",10,"top",8,"width",90,"height",20,NULL);//������ť
    edt1=CreateComponentEx(p,"edit",  "text",   "123456",   "left",70,"top",5,"width",260,"height",20,NULL);//������ť
    cbHex=CreateComponentEx(p,"checkbox","caption","ʮ�����Ʒ���","left",10,"top",35,"width",100,"height",20,NULL);//������ť
    int lbl2=CreateComponentEx(p,"label", "caption","���ͼ��:","left",145,"top",37,"width",70,"height",20,NULL);//������ť
    cbx1=CreateComponentEx(p,"combobox","text","200","left",203,"top",35,"width",60,"height",20,NULL);//������ť
    int lbl3=CreateComponentEx(p,"label", "caption","����","left",270,"top",37,"width",70,"height",20,NULL);//������ť
    tmr1=CreateComponentEx(p,"timer","interval",500,"enabled",0,"ontimer",OnTimer,NULL);//������ť
    StringsAdd(cbx1,"100");
    StringsAdd(cbx1,"200");
    StringsAdd(cbx1,"500");
    StringsAdd(cbx1,"1000");
    ShowVclWin(120);

}
