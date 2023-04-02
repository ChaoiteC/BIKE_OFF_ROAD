#include "script\\ucosii\\includes.h"
#pragma comment(lib,"script\\ucosii\\os_cpu_c.c")
#pragma comment(lib,"script\\ucosii\\os_dbg_r.c")
#pragma comment(lib,"script\\ucosii\\os_trace.c")
#pragma comment(lib,"script\\ucosii\\ucos_ii.c")

#define  TASK_STK_SIZE    128
//extern INT32U              OSTerminateCtxSwW32;
OS_STK        AppStk_one[TASK_STK_SIZE];
OS_STK        AppStk_two[TASK_STK_SIZE];
OS_STK        AppStk_three[TASK_STK_SIZE];
//int stop=0;
static void App_one(void *p_arg);
static void App_two(void *p_arg);
static void App_three(void *p_arg);
static void print_task_ready_tab(void);
int btn;
void OnTerminate()
{
    OS_STOP();
    printf("terminate");
    
}
void CreateGui()
{
    int p;
    ClearVclControls();
    ShowVclWin(300);
    ShowOutputWin(-1);
    ClearOutputWin();
    p=GetGuiWin(0);
    btn=CreateComponentEx(p,"button","caption","÷’÷πUCOS","left",10,"top",5,"width",80,"height",20,"OnClick",OnTerminate,0);
    AutoSetVclWinWidth();
}
void main(int argc, char *argv[])
{
    CreateGui();
    printf("CommBox ucos ver2.80 start...");

    OSInit();//                              /* Initialize "uC/OS-II"*/
    OSTaskCreate(App_one,NULL,(OS_STK *)&AppStk_one[TASK_STK_SIZE-1],(INT8U)11);
    OSTaskCreate(App_two,NULL,(OS_STK *)&AppStk_two[TASK_STK_SIZE-1],(INT8U)30);
    OSTaskCreate(App_three,NULL,(OS_STK *)&AppStk_three[TASK_STK_SIZE-1],(INT8U)50);
    OSStart();                             /* Start multitasking */
    printf("CommBox ucos end");
    SetProperty(btn,"enabled",0);
    
}


void App_one(void *p_arg)
{
    p_arg = p_arg;
    printf("current prio=%d,OSPrioHighRdy=%d\n",OSPrioCur,OSPrioHighRdy);
    while (TRUE)
    {
        printf("");
        OS_Printf("\nthis is App_one, Delay 6 second and start again\n");
        printf("current prio=%d,OSPrioHighRdy=%d\n",OSPrioCur,OSPrioHighRdy);
        //OS_Printf("Resume prio=30 task\n");
        //OSTaskResume(30);
        //print_task_ready_tab();
        OSTimeDlyHMSM(0, 0, 2, 0);
        
    }
    printf("App_one terminated!");
}

void App_two(void *p_arg)
{
    p_arg = p_arg;
    while (TRUE)
    {
        printf("");
        OS_Printf("\n\nthis is App_two,Delay 5 second and start again\n");
        printf("current prio=%d,OSPrioHighRdy=%d\n",OSPrioCur,OSPrioHighRdy);
        OS_Printf("suspend prio=30 task\n");
        OSTaskSuspend(10);
        //print_task_ready_tab();
        OSTimeDlyHMSM(0, 0, 1, 0);
      
    }
    printf("App_two terminated!");
}


void App_three(void *p_arg)
{
    p_arg = p_arg;
    while (TRUE)
    {
        printf("");
        OS_Printf("\nthis is App_three, Delay 8 second and start again\n");
        printf("current prio=%d,OSPrioHighRdy=%d\n",OSPrioCur,OSPrioHighRdy);
        //print_task_ready_tab();
        //getchar();
        OSTimeDlyHMSM(0, 0, 3, 0);
      
    }
    printf("App_three terminated!");
}

void print_task_ready_tab(void)
{
    int i;
    printf("OSRdyGrp=%u\n",OSRdyGrp);
    for(i=0; i<8; i++)
        printf("OSRdyTbl[%d]=%d\n",i,OSRdyTbl[i]);
    printf("\n");
}
