#include "windows.h"
void OpenFileClick(void *sender);
void DownLoadClick(void *sender);
void CancelClick(void *sender);
void AddFileToLv(unsigned char* s,unsigned char *time,int save);
void UpdateLv();
int edt1;
int cancel;
int pgb1;
int txt6;
int edt2;
int tmr1;
int txt2,btn2,btn3,lv;

char *sIID="{8e120c45-4968-4188-ba19-9a82361c8fa8}";//usb 驱动程序 IID
void DownLoad()
{
    char s[200];
    CHAR *pBuffer;
    DWORD RSize;
    int fileSize = 0;
    int i;
    cancel=0;
    SetProperty(btn2,"enabled",0);
    SetProperty(btn3,"enabled",1);
    SetProperty(pgb1,"position",0);
    SetProperty(txt6,"caption","0%");

    int iTmp=GetPathName(sIID,s,200);

    if(iTmp>0)  //devName~="" then
        printf("Usb device PathName:%s",s);
    else
    {
        ShowMessage("Usb host not connected!");
        return ;
    }
    sprintf(s,"%s\\\\PIPE01",s);
    printf("usb name:%s",s);

    HANDLE Handle=CreateFile(s, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    if (Handle<=0)
    {
        printf("打开文件%s错误！",s);
        return;
    }

    GetProperty(edt1,"text",s,200);
    SaveIniString("DNW","FileName",s);
    AddFileToLv(s,0,1);
    GetProperty(edt2,"text",s,200);
    SaveIniString("DNW","Address",s);


    GetProperty(edt1,"text",s,200);

    HANDLE Handle1=CreateFile(s, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

    printf("发送文件名称：%s",s);

    if(Handle1<=0)
    {
        sprintf(s,"打开文件【%s】错误！",s);
        ShowMessage(s);//"打开文件【"..pb.edit1.text.."】错误！");
        return  ;
    }

    int Length =SetFilePointer(Handle1,0,NULL,FILE_END);
    SetFilePointer(Handle1,0,NULL,FILE_BEGIN);
    char *Buffer = malloc(Length + 10);  //   --addr(4bytes)+length(4bytes)+filedata(length bytes)+checksum(2bytes)
    int BytesRead ;
    ReadFile(Handle1, Buffer+8, Length,&BytesRead,NULL);
    CloseHandle(Handle1);
    GetProperty(edt2,"text",s,200);
    int downloadAddress=StrToInt(s); //0x32000000;

    printf("Address:0x%x",downloadAddress);
    Buffer[0]=(downloadAddress>>0)&0xff;
    Buffer[1]=(downloadAddress>>8)&0xff;
    Buffer[2]=(downloadAddress>>16)&0xff;
    Buffer[3]=(downloadAddress>>24)&0xff;
    int len1=Length+10;
    Buffer[4]=(len1>>0)&0xff;
    Buffer[5]=(len1>>8)&0xff;
    Buffer[6]=(len1>>16)&0xff;
    Buffer[7]=(len1>>24)&0xff;

    unsigned short cs=0;
    for(i=0; i<Length; i++)
    {
        cs+=Buffer[8+i];      //  计算校验和
    }
    cs&=0xffff; //                               --取16bits
    printf("check sum is :%x",cs);
    Buffer[Length+8]=(cs>>0)&0xff;
    Buffer[Length+9]=(cs>>8)&0xff;
    Length=Length+10;//addr(4bytes)+length(4bytes)+filedata(length bytes)+checksum(2bytes)
    int TxBufCount=0;
    int txBlkSize=0;
    int TX_SIZE=4096*4;
    int BytesWrite ;
    printf("Download to device ...");
    Update();
    while(1)
    {
        if (cancel==1)break;
        if((Length-TxBufCount) > TX_SIZE)
            txBlkSize =TX_SIZE;
        else
            txBlkSize = Length-TxBufCount;

        //printf("filewrite:%d...", txBlkSize);
        int wlen=WriteFile( Handle, Buffer+TxBufCount, txBlkSize, &BytesWrite,NULL);
        //printf("wrote %d",BytesWrite);
        if(BytesWrite<=0)
        {
            printf("下载失败，请重新启动开发板！");
            CloseHandle(Handle);
            free(Buffer);
            return;
        };

        TxBufCount =TxBufCount+txBlkSize;
        float fPer=1.0f;
        //fPer=
        int per=((TxBufCount+1)*100)/Length;
        SetProperty(pgb1,"position",per);
        sprintf(s,"%d%s",per,"%");
        SetProperty(txt6,"caption",s);
        Update();
        //printf("write %d of %d:%d%",TxBufCount,Length,per);
        if (TxBufCount>=  Length) break;
        Wait(0);
    };
    printf("close file ...");
    CloseHandle(Handle);
    printf("free mem ...");
    free(Buffer);
    printf("Download end");
    SetProperty(btn2,"enabled",1);
    SetProperty(btn3,"enabled",0);
}



void OnTimer()
{
    char s[200];
    //printf("aaa");
    int iTmp=GetPathName(sIID,s,200);
    //printf("bbb");
    if(iTmp>0)  //devName~="" then
    {
        //printf("Usb device PathName:%s",s);
        SetProperty(txt2,"caption","   USB:OK");
        SetProperty(txt2,"color",0x00ff00);
        SetProperty(btn2,"enabled",1);
    }
    else
    {
        //printf("Usb device PathName:%s",s);
        SetProperty(txt2,"caption","   USB:x");
        SetProperty(txt2,"color",0x0000ff);
        SetProperty(btn2,"enabled",0);
    }
    //printf("ccc");
    UpdateLv();
    //printf("ddd");
}

void Save()
{
    int i;
    char s1[200],s2[200];
    int count=GetListViewItemCount(lv);
    sprintf(s1,"%d",count);
    SaveIniString("DNW","FileCount",s1);
    for(i=0; i<count; i++)
    {
        GetListViewItem(lv,i,2,s1,200);
        sprintf(s2,"FileName%d",i);
        SaveIniString("DNW",s2,s1);

        GetListViewItem(lv,i,0,s1,200);
        sprintf(s2,"FileDt%d",i);
        SaveIniString("DNW",s2,s1);
    }
}

void KeyBtnClick(void *Sender)
{
    int tag,t;
    t=GetProperty(Sender,"tag",&tag,4);
    printf("tag:%d",t);
    SendByte(t);
}
void DelClick(void *Sender)
{
    int idx;
    idx=GetListViewItemIndex(lv);
    DelListViewItem(lv,idx);
    Save();
}
void ClearClick(void *Sender)
{
    while(GetListViewItemCount(lv)>0)
        DelListViewItem(lv,0);
    Save();
}
void lvDbClick(void *Sender)
{
    int idx;
    char s1[200];
    idx=GetListViewItemIndex(lv);

    GetListViewItem(lv,idx,2,s1,200);
    SetProperty(edt1,"text",s1);

}
void CloseClick(void *Sender)
{
    //UpdateLv();
    //return;
    ClearOutputWin();   //清除输出窗口内容

    HideVclWin();
    printf("hided");
    CloseVclWin();
}

void main()
{
    ClearOutputWin();   //清除输出窗口内容
    //ClearCommWin();

    CloseInputWin();
    ClearVclControls();
    printf("=============SAMSUNG S3C2410/2440 USB 下载工具(DNW)==============");
    int p=GetGuiWin();
    int pnl = CreateComponentEx(p,"panel","caption","","left",2,"top",2,"width",650,"height",230,NULL);
    int txt1= CreateComponentEx(pnl,"label","caption","                  SAMSUNG S3C2410/2440 USB 下载工具(DNW)","left",30,"top",10,"width",350,"color",0xff00ff,NULL);
    txt2= CreateComponentEx(pnl,"label","caption","   USB:x","left",385,"top",10,"width",60,"autosize",0,"color",0x0000ff,NULL);
    int txt3= CreateComponentEx(pnl,"label","caption","文件名称：","left",10,"top",40,"width",60,NULL);
    edt1= CreateComponentEx(pnl,"edit", "text","请输入文件名...","left",75,"top",38,"width",385,NULL);

    int txt4= CreateComponentEx(pnl,"label","caption","下载地址：","left",10,"top",68,"width",60,NULL);
    edt2= CreateComponentEx(pnl,"edit", "text","0x32000000","left",75,"top",65,"width",90,NULL);

    int txt5= CreateComponentEx(pnl,"label","caption","下载进度：","left",170,"top",68,"width",60,NULL);
    txt6= CreateComponentEx(pnl,"label","caption","0%","left",228,"top",68,"width",40,NULL);
    pgb1= CreateComponentEx(pnl,"progressbar","left",258,"top",65,"width",293,"height",20,"position",0,NULL);




    int btn1= CreateComponentEx(pnl,"button","caption","...","left",465,"top",36,"width",65,"onclick",OpenFileClick,NULL);
    btn2= CreateComponentEx(pnl,"button","caption","通过USB下载","left",535,"top",10,"width",105,"height",50,"onclick",DownLoadClick,NULL);
    btn3= CreateComponentEx(pnl,"button","caption","取  消","left",555,"top",65,"width",85,"onclick",CancelClick,NULL);

    CreateComponentEx(pnl,"button","caption","删  除","left",555,"top",110,"width",85,"onclick",DelClick,NULL);
    CreateComponentEx(pnl,"button","caption","清  空","left",555,"top",140,"width",85,"onclick",ClearClick,NULL);
    CreateComponentEx(pnl,"button","caption","关  闭","left",555,"top",190,"width",85,"onclick",CloseClick,NULL);
    int key_left=370;
    int key_top=10;


    lv=CreateComponentEx(pnl,"listview","left",12,"top",95,"width",540,"height",125,"ondblclick",lvDbClick,NULL);
    AddListViewColumn(lv,"更新",40);
    AddListViewColumn(lv,"下载时间",115);
    AddListViewColumn(lv,"更新时间",115);
    AddListViewColumn(lv,"文件名称",880);


    tmr1=CreateComponentEx(p,"timer","interval",1000,"enabled",0,"ontimer",OnTimer,NULL);//创建按钮
    ShowVclWin(230+8);
    ShowOutputWin(330);
    CloseCodeWin();
    HideLeftTools();
    HideRightTools();
    ShowTerminalWin();
    PrintToCommWin(" ");
    PrintToCommWin(" ");
    //PrintToCommWin("          ███  █  █   █ ███      ██    █    █ █    █            ");
    //PrintToCommWin("         █    █ █  █   █ █  █      █  █  ██  █ █    █            ");
    //PrintToCommWin("              █  █  █   █ █  █ ██ █   █ █ █ █ █    █            ");
    //PrintToCommWin("             █   ████ █ █  █      █   █ █  ██ █ █ █            ");
    //PrintToCommWin("           █         █   █ █  █      █  █  █    █ ████            ");
    //PrintToCommWin("         ████     █   █ ███      ██    █    █ █    █   █ █ █ ");
    /**/
    char s[200],s1[200],s2[200];
    GetIniString("DNW","FileName",s,200);
    SetProperty(edt1,"text",s);
    GetIniString("DNW","Address",s,200);
    SetProperty(edt2,"text",s);

    //printf("1...");
    GetIniString("DNW","FileCount",s,200);

    //printf("2...");
    //printf("s:%s",s);
    if(strlen(s)>0)
    {
        int count=StrToInt(s);
        //printf("2.1");
        int i;
        for(i=0; i<count; i++)
        {
            //printf("2.i:%d",i);
            sprintf(s2,"FileName%d",i);
            GetIniString("DNW",s2,s,200);
            sprintf(s2,"FileDt%d",i);
            GetIniString("DNW",s2,s1,200);
            AddFileToLv(s,s1,0);
        }
    }

    //printf("3...");
    UpdateLv();

    char *IID="{8e120c45-4968-4188-ba19-9a82361c8fa8}";//usb 驱动程序 IID
    SetProperty(btn2,"enabled",0);
    int addCount=0;
    SetProperty(tmr1,"enabled",1);

    printf("inited");
}

void AddFileToLv(unsigned char* s,unsigned char *time,int save)
{
    char s1[200],s2[200];
    int i,idx;
    idx=-1;

    int count=GetListViewItemCount(lv);
    for(i=0; i<count; i++)
    {
        GetListViewItem(lv,i,2,s1,200);
        if(strcmp(s,s1)==0)
        {
            idx=i;
            break;
        }
    }
    if(idx==-1)
    {
        StringsAdd(lv,"");
        idx=GetListViewItemCount(lv)-1;
    }
    if(time!=0)
    {
        SetListViewItem(lv,idx,0,time);
    }
    else
    {
        GetDateTimeStr(s1,50);
        SetListViewItem(lv,idx,0,s1);
    }
    GetFileWriteTime(s,s1,200);


    SetListViewItem(lv,idx,1,s1);//"2011-05-12 16:23:56");
    SetListViewItem(lv,idx,2,s);

    if(save)
        Save();
}
void UpdateLv()
{
    char s1[200],s2[200];
    char fn[200];
    int i,idx;
    idx=-1;

    int count=GetListViewItemCount(lv);
    for(i=0; i<count; i++)
    {

        GetListViewItem(lv,i,0,s1,200);
        GetListViewItem(lv,i,2,fn,200);
        GetFileWriteTime(fn,s2,200);
        SetListViewItem(lv,i,1,s2);
        //printf("%s ,%s",s1,s2);
        if(strcmp(s1,s2)<0)
        {
            SetListViewItem(lv,i,-1," Y");
        }
        else
            SetListViewItem(lv,i,-1," ");
    }
}


void OpenFileClick(void *sender)
{
    char s[200];
    GetFileName(s,200);
    SetProperty(edt1,"text",s);
    SaveIniString("DNW","FileName",s);
}
void DownLoadClick(void *sender)
{
    DownLoad();
}
void CancelClick(void *sender)
{
    //char s[100];
    cancel=1;
    //GetProperty(edt1,"text",s,100);
    //AddFileToLv(s,0,1);
}

