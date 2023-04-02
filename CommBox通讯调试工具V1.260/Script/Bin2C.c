#include <stdio.h>
#include <string.h>

#define BUF_LEN 1
#define LINE     15
int p;

int edt1,edt2,edt3;
void Trans();
long int filesize( FILE *fp )
{
    long int save_pos, size_of_file;

    save_pos = ftell( fp );
    fseek( fp, 0L, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
}

void Upper_chars(char *buffer)
{
    unsigned int c;

    for (c=0; c <= strlen(buffer)-1; c++) *(buffer+c)=toupper( *(buffer+c) );
}
void OpenFileClick(void *sender)
{
    char s[200];
    GetFileName(s,200);
    if(strlen(s)>0)
    {
        SetProperty(edt1,"text",s);
    }
}
void OpenFileClick1(void *sender)
{
    char s[200];
    GetFileName(s,200);
    if(strlen(s)>0)
    {
        SetProperty(edt2,"text",s);
    }
}
void CloseClick(void *Sender)
{

    ClearOutputWin();   //清除输出窗口内容
    HideVclWin();

    CloseVclWin();
    CloseForm(p);
}

void ViewC()
{
    char s[200],s1[200];
    GetProperty(edt2,"text",s,200);
    sprintf(s1,"notepad.exe %s",s);
    WinExec(s1);

}
void CreateGui()
{
    //ShowVclWin(170);
    //ShowOutputWin(310);
    CloseCodeWin();
    ClearVclControls();
    //HideLeftTools();
    //HideRightTools();

    int GuiMode=2;
    if((GuiMode==0)||(GuiMode==1))
        p=GetGuiWin(GuiMode);
    else
        p=CreateComponentEx(0,"form","caption","Bin2C工具","Width",560,"height",170,"BorderIcons","[biSystemMenu]","position","poMainFormCenter","formstyle","fsstayontop", "visible",1,NULL);//创建form;borderIcons:[biSystemMenu,biMinimize,biMaximize]

    int pnl = p;
    int txt2= CreateComponentEx(pnl,"label","caption","二进制文件名称：","left",10,"top",40-30,"width",60,NULL);
    edt1= CreateComponentEx(pnl,"edit", "text","c:\\boot.ini","left",75,"top",38-30,"width",385,NULL);
    int txt3= CreateComponentEx(pnl,"label","caption","C文件名称：","left",10,"top",68-30,"width",60,NULL);
    edt2= CreateComponentEx(pnl,"edit", "text","c:\\tmp.c","left",75,"top",65-30,"width",385,NULL);

    int txt4= CreateComponentEx(pnl,"label","caption","结构名称：","left",10,"top",96-30,"width",60,NULL);
    edt3= CreateComponentEx(pnl,"edit", "text","data","left",75,"top",92-30,"width",385,NULL);

    int btn1= CreateComponentEx(pnl,"button","caption","...","left",465,"top",36-30,"width",65,"onclick",OpenFileClick,NULL);
    int btn2= CreateComponentEx(pnl,"button","caption","...","left",465,"top",63-30,"width",65,"onclick",OpenFileClick1,NULL);
    int btn3= CreateComponentEx(pnl,"button","caption","转    换" ,"left",75,"top",93+28-25,"width",120,"onclick",Trans,NULL);
    int btn4= CreateComponentEx(pnl,"button","caption","查看C文件","left",215,"top",93+28-25,"width",120,"onclick",ViewC,NULL);
    int btn5= CreateComponentEx(pnl,"button","caption","退    出" ,"left",375,"top",93+28-25,"width",120,"onclick",CloseClick,NULL);
}
void main()
{
    printf("BIN2C V1.0 by baohongjie\n");
    CreateGui();
}
void Trans()
{
    char  argv[4][255];
    char s[100];
    FILE *source,*dest;
    unsigned char buffer[BUF_LEN], Dummy[20];
    int c;
    GetProperty(edt1,"text",argv[1],200);
    GetProperty(edt2,"text",argv[2],200);
    GetProperty(edt3,"text",argv[3],200);
    if( (source=fopen( argv[1], "rb" )) == NULL )
    {
        sprintf(s,"二进制文件[%s]不存在!",argv[1]);
        ShowMessage(s);
        return;
    }
    strcpy(Dummy,argv[2]);

    if( (dest=fopen( Dummy, "wb+" )) == NULL )
    {
        sprintf(s,"目标文件[%s]无法创建!",argv[1]);
        ShowMessage(s);
        return;
    }

    strcpy(Dummy,argv[3]);
    Upper_chars(Dummy);  /* lower to upper chars */
    strcat(Dummy,"_LEN");  /* add the suffix _LEN to the struct name */
    fprintf( dest, "\r\n//CommBox V1.256\r\n\r\n", Dummy, filesize(source) );
    fprintf( dest, "#define %s %d\r\n", Dummy, filesize(source) );
    fprintf( dest, "static unsigned char %s[]=\r\n{\r\n", argv[3] );

    if( ferror( dest ) )
    {
        printf( "ERROR writing on target file:  %s\n",argv[2] );
        return;
    }

    do
    {
        fprintf(dest,"    ");
        for ( c=0; ((c <= LINE) && (! feof( source ) )) ; c++)
        {
            fread(buffer,1,1,source);

            if (!feof( source ) && c != 0)
            {
                fprintf(dest,",");
            }

            if (! feof( source ) )
            {
                fprintf(dest,"0x%02x",*buffer);
            }
        }
        fprintf(dest,",\r\n");
    }
    while( ! feof( source ) );

    fprintf(dest,"};\r\n\r\n");

    fclose(dest);
    fclose(source);
    printf("OK!");
    ShowMessage("-------------转换完成!-----------------");
}





