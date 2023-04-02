#include "windows.h"

//////////////// 接收队列处理 ///////////////////////////////////
#define MAXRXBUFLEN (1024*20)

#define GetRxBufLen()  ((RxBufTail+MAXRXBUFLEN-RxBufHead) % MAXRXBUFLEN)
#define IsRxBufEmpty() (RxBufHead==RxBufTail)
#define IsRxBufFull()  ((RxBufTail+1)%MAXRXBUFLEN==RxBufHead)
#define ClearRxBuf()   RxBufHead=RxBufTail=0

BYTE RxBuf[MAXRXBUFLEN];
BYTE RxBufHead=0;
BYTE RxBufTail=0;

BYTE GetRxBufByte(void)
{
    BYTE dat;
    dat=RxBuf[RxBufHead];
    RxBufHead++;
    RxBufHead%=MAXRXBUFLEN;
    return dat;
}
void DiscardRxBufBytes(BYTE count)
{
    RxBufHead+=count;
    RxBufHead%=MAXRXBUFLEN;
}
BYTE PeekRxBufByte(BYTE idx)
{
    BYTE tmpHead=RxBufHead;
    tmpHead+=idx;
    tmpHead%=MAXRXBUFLEN;
    return RxBuf[tmpHead];
}

void PutRxBufByte(BYTE dat)
{

    RxBuf[RxBufTail]=dat;
    RxBufTail++;
    RxBufTail%=MAXRXBUFLEN;
}

//////////////////////////////////////////////////////////////////
#define MAXCMDLEN 20
BYTE StationCmd[MAXCMDLEN];
BYTE StationCmdLen;
BYTE RepBuf[140];

unsigned int  newId,newInterval;

void ConsolePutArray(BYTE buf[],BYTE len)
{
    BYTE i;
    for(i=0; i<len; i++)
        ;//   halPutch(buf[i]);
}


void ProgramData(void)// 查询单个团详细信息
{
    BYTE i,j;
    BYTE find;
    BYTE idx;
    BYTE cs;
    BYTE mbCount;

    if(StationCmdLen!=1+4)
    {
        // return;
    }
    newId=StationCmd[1]+StationCmd[2]*256;

}

void ProcessStationCmd(void)
{
    if(StationCmdLen==0) return;
    switch(StationCmd[0])
    {
    case 0x08: // 查询工作状态            =[H]55 AA 02 FD 07 07 03
        ProgramData();
        break;

    default:
        break;
    }
}

void EncodeRxData(void)//包裹解码
{
    BYTE i,len;
    BYTE cs;
    len=PeekRxBufByte(2);
    if(len>MAXCMDLEN)
    {
        StationCmd[0]=PeekRxBufByte(4);
        for(i=0; i<=4+len; i++)
            GetRxBufByte();//丢弃一个字节;
        return ;
    }
    AddPrtclDetailNode(NULL,"同步头",RxBufHead,2);
    GetRxBufByte();//丢弃一个字节; 55
    GetRxBufByte();//丢弃一个字节; aa
    AddPrtclDetailNode(NULL,"长度",RxBufHead,1);

    GetRxBufByte();//丢弃一个字节; len
    AddPrtclDetailNode(NULL,"~长度",RxBufHead,1);
    GetRxBufByte();//丢弃一个字节; ~len

    AddPrtclDetailNode(NULL,"data",RxBufHead,len);

    for(i=0; i<len; i++)
        StationCmd[i]=GetRxBufByte();
    GetRxBufByte(); //0x03

    cs=0;
    for(i=0; i<len-1; i++)
        cs^=StationCmd[i];

    if(cs!=StationCmd[len-1])
    {
        printf("check sum error!");
        //return;
    }

    //ConsolePutROMString((rom char *)"接收到命令包:");
    //ConsolePutInitData(0,StationCmd[0]);
    StationCmdLen=len-1; //不包含校验位
    printf("Recv a command!");
    ProcessStationCmd();

}


//通讯处理
void ProcessRxComm(void)
{
    BYTE len;
    while(GetRxBufLen()>=7)
    {
        if(PeekRxBufByte(0)!=0x55)
        {
            DiscardRxBufBytes(1);
        }
        else if(PeekRxBufByte(1)!=0xaa)
        {
            DiscardRxBufBytes(2);
        }
        else if(PeekRxBufByte(2)+PeekRxBufByte(3)!=0xff)//长度、长度取反
        {
            DiscardRxBufBytes(4);
        }
        else
        {
            len=PeekRxBufByte(2);
            if(len>MAXCMDLEN)  //命令过长
            {
                DiscardRxBufBytes(4);
            }
            else if(GetRxBufLen()>len+4)
            {
                if(PeekRxBufByte(4+len)!=0x03)//结束字符
                {
                    DiscardRxBufBytes(1);
                }
                else
                {
                    printf("recv packet!");
                    AddPrtclDataNode(NULL,"版本号查询",&RxBuf[RxBufHead],len+5,0);

                    DiscardRxBufBytes(len+5);
                }
            }
            else
            {
                break;
            }
        }
    }	//while
}



void ProcessRxCommDetail(void)
{
    BYTE len;
    while(GetRxBufLen()>=7)
    {
        if(PeekRxBufByte(0)!=0x55)
        {
            DiscardRxBufBytes(1);
        }
        else if(PeekRxBufByte(1)!=0xaa)
        {
            DiscardRxBufBytes(2);
        }
        else if(PeekRxBufByte(2)+PeekRxBufByte(3)!=0xff)//长度、长度取反
        {
            DiscardRxBufBytes(4);
        }
        else
        {
            len=PeekRxBufByte(2);
            if(len>MAXCMDLEN)  //命令过长
            {
                DiscardRxBufBytes(4);
            }
            else if(GetRxBufLen()>len+4)
            {
                if(PeekRxBufByte(4+len)!=0x03)//结束字符
                {
                    DiscardRxBufBytes(1);
                }
                else
                {
                    printf("recv packet!");


                    EncodeRxData();
                }
            }
            else
            {
                break;
            }
        }
    }	//while
}


//////////////////////////////////////////////////////////////////////

void RecvSerialData(char *buf,int count)
{
    int i;
    for(i=0; i<count; i++)
    {
        PutRxBufByte(buf[i]);
    }

    printf("RecvSerialData,len(%d)",count);
    ProcessRxComm();
}


void click(int btn)
{
    char s[20];
    printf("clicked");
    //SetProperty(btn,"enabled","false");
    GetProperty(btn,"caption",s,20);
    printf("button caption is %s",s);
    MessageBox(0,s,"按钮标题",1);
};

void click1(int btn)
{
    char s[20];
    printf("clicked");
    //SetProperty(btn,"enabled","false");
    GetProperty(btn,"text",s,20);
    printf("text is %s",s);
    MessageBox(0,s,"text",1);
};


void AnaProtocolData(char *buf,int count)
{
    int node;
    int i;
    //printf("AnaProtocolData,len(%d):%s",count,buf);
    ClearRxBuf();
    for(i=0; i<count; i++)
        PutRxBufByte(buf[i]);
    ProcessRxCommDetail();
  
}


void main()
{
    int i;
    int btn;
    int node;
    char s[100];
    ShowProtocolWin();
    ClearVclControls();
    ShowVclWin(150);
    ShowOutputWin(300);
    int p=GetGuiWin();
    for(  i=0; i<5; i++)
    {
        sprintf(s,"按钮:%d",i);
        btn=CreateComponentEx(p,"button","caption",s,"left",10+i*70,"top",10,"width",65,"onclick",click,NULL);//创建按钮
    }
    btn=CreateComponentEx(p,"combobox","text","按钮","left",10+i*70,"top",10,"width",80,"onclick",click1,NULL);//创建按钮
    StringsAdd(btn,"111");
    StringsAdd(btn,"222");    
    sprintf(s+10,"按钮876587iuytiuyt87888777666555:%d",i);
    ClearProtocolTree();
};
