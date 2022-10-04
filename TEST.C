/************************Test*************************************/
#include "includes.h"
#define  TASK_STK_SIZE   512                //�����ջ����
char *s1="18001030108";
char *s2="liuxiaopeng";

OS_EVENT *Fun_Semp; //�����ź���
OS_STK   StartTaskStk[TASK_STK_SIZE];           //���������ջ��
OS_STK   MyTaskStk[TASK_STK_SIZE];          //���������ջ��
OS_STK   YouTaskStk[TASK_STK_SIZE];         //���������ջ��
INT16S   key;                       //�����˳��ļ�

INT8U err;                          
INT8U y=0;                      //�ַ���ʾλ��

void  Fun(INT8U x,INT8U y);
void  StartTask(void *data);                //������ʼ����
void  MyTask(void *data);               //��������
void  YouTask(void *data);              //��������
/************************������*********************************/
void  main (void)
{
    OSInit( );                      //��ʼ��?C/OS-II_II
    PC_DOSSaveReturn( );                //����Dos����
    PC_VectSet(uCOS, OSCtxSw);              //��װ?C/OS-II_II�ж�
    Fun_Semp= OSSemCreate(0);   	//�ź�����ֵ 
    
    OSTaskCreate(StartTask,             //��������StartTask
    (void*)0,                   //�����񴫵ݲ���
    &StartTaskStk[TASK_STK_SIZE - 1],       //���������ջջ��
    0);                     //ʹ��������ȼ���Ϊ0
    OSStart( );                     //�������������
}
/***********************����StartTask*******************************/
void  StartTask (void *pdata)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif
    pdata = pdata; 
    OS_ENTER_CRITICAL( );
    PC_VectSet(0x08, OSTickISR);        //��װʱ���ж�����
    PC_SetTickRate(OS_TICKS_PER_SEC);       //����?C/OS-II_IIʱ��Ƶ��
    OS_EXIT_CRITICAL( );

    OSStatInit( );              //��ʼ��ͳ������
    OSSemPend(Fun_Semp,0,&err);		//wait 
    OSTaskCreate(MyTask,            //��������MyTask
        (void*)0,           //�����񴫵ݲ���
        &MyTaskStk[TASK_STK_SIZE - 1],  //���������ջջ��
        1);             //ʹ��������ȼ���Ϊ1
    OSTaskCreate(YouTask,           //��������YouTask
        (void*)0,           //�����񴫵ݲ���
        &YouTaskStk[TASK_STK_SIZE - 1], //���������ջջ��
        2);             //ʹ��������ȼ���Ϊ2
  	OSSemPost(Fun_Semp);		//signal

    for (;;) 
    {
    //�������Esc�����˳�?C/OS-II_II
    if (PC_GetKey(&key) == TRUE) 
    {
            if (key == 0x1B) 
        {
                PC_DOSReturn();
            }
        }
        OSTimeDlyHMSM(0, 0, 3, 0);  //�ȴ�3��
    }
}
/************************����MyTask*******************************/
void  MyTask (void *pdata)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif
    pdata = pdata;
  for (;;) 
    {
       	PC_DispStr(0,++y,
        s1,
        DISP_BGND_BLACK+DISP_FGND_WHITE );
     Fun(12,y);                           //���ú���fun
     OSTimeDlyHMSM(0, 0, 6, 0);  //�ȴ�6��
    }
}
/************************����YouTask******************************/
void  YouTask (void *pdata)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif
    pdata = pdata;     
     
 for (;;)
 {
  	PC_DispStr(0,++y,
        s2,
        DISP_BGND_BLACK+DISP_FGND_WHITE );
  
    OSTimeDlyHMSM(0, 0, 1, 0);  //�ȴ�1��
  }
}
void Fun(INT8U x,INT8U y)
{
 PC_DispStr(x,y,"  invoked Fun()!",
  DISP_BGND_BLACK+DISP_FGND_WHITE );
}

/************************End**************************************/
