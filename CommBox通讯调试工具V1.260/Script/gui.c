#include "windows.h"

//////////////// ���ն��д��� ///////////////////////////////////
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


void ProgramData(void)// ��ѯ��������ϸ��Ϣ
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
    case 0x08: // ��ѯ����״̬            =[H]55 AA 02 FD 07 07 03
        ProgramData();
        break;

    default:
        break;
    }
}

void EncodeRxData(void)//��������
{
    BYTE i,len;
    BYTE cs;
    len=PeekRxBufByte(2);
    if(len>MAXCMDLEN)
    {
        StationCmd[0]=PeekRxBufByte(4);
        for(i=0; i<=4+len; i++)
            GetRxBufByte();//����һ���ֽ�;
        return ;
    }
    AddPrtclDetailNode(NULL,"ͬ��ͷ",RxBufHead,2);
    GetRxBufByte();//����һ���ֽ�; 55
    GetRxBufByte();//����һ���ֽ�; aa
    AddPrtclDetailNode(NULL,"����",RxBufHead,1);

    GetRxBufByte();//����һ���ֽ�; len
    AddPrtclDetailNode(NULL,"~����",RxBufHead,1);
    GetRxBufByte();//����һ���ֽ�; ~len

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

    //ConsolePutROMString((rom char *)"���յ������:");
    //ConsolePutInitData(0,StationCmd[0]);
    StationCmdLen=len-1; //������У��λ
    printf("Recv a command!");
    ProcessStationCmd();

}


//ͨѶ����
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
        else if(PeekRxBufByte(2)+PeekRxBufByte(3)!=0xff)//���ȡ�����ȡ��
        {
            DiscardRxBufBytes(4);
        }
        else
        {
            len=PeekRxBufByte(2);
            if(len>MAXCMDLEN)  //�������
            {
                DiscardRxBufBytes(4);
            }
            else if(GetRxBufLen()>len+4)
            {
                if(PeekRxBufByte(4+len)!=0x03)//�����ַ�
                {
                    DiscardRxBufBytes(1);
                }
                else
                {
                    printf("recv packet!");
                    AddPrtclDataNode(NULL,"�汾�Ų�ѯ",&RxBuf[RxBufHead],len+5,0);

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
        else if(PeekRxBufByte(2)+PeekRxBufByte(3)!=0xff)//���ȡ�����ȡ��
        {
            DiscardRxBufBytes(4);
        }
        else
        {
            len=PeekRxBufByte(2);
            if(len>MAXCMDLEN)  //�������
            {
                DiscardRxBufBytes(4);
            }
            else if(GetRxBufLen()>len+4)
            {
                if(PeekRxBufByte(4+len)!=0x03)//�����ַ�
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
    MessageBox(0,s,"��ť����",1);
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
        sprintf(s,"��ť:%d",i);
        btn=CreateComponentEx(p,"button","caption",s,"left",10+i*70,"top",10,"width",65,"onclick",click,NULL);//������ť
    }
    btn=CreateComponentEx(p,"combobox","text","��ť","left",10+i*70,"top",10,"width",80,"onclick",click1,NULL);//������ť
    StringsAdd(btn,"111");
    StringsAdd(btn,"222");    
    sprintf(s+10,"��ť876587iuytiuyt87888777666555:%d",i);
    ClearProtocolTree();
};
