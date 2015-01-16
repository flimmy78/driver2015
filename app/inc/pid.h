#ifndef _PID_H_
#define _PID_H_

/********λ��ʽPID********/
typedef struct _PID
{
  int  SetPoint;                                                         //  �趨Ŀ�� Desired Value
  int  Proportional;                                                       //  �������� Proportional Const
  int  Integral;                                                         //  ���ֳ��� Integral Const
  int  Derivative;                                                       //  ΢�ֳ��� Derivative Const
  int  LastError;                                                        //  Error[-1]
  int SumError;                                                    //  Sums of Errors
	int MaxSumError;// Should be a positive number
	int Output;
	int MaxOutput;// Should be a positive number
}iPidObj;
/********����ʽPID********/
typedef struct _QPID
{
	int  Proportional;                                                       //  �������� Proportional Const
  int  Integral;                                                         //  ���ֳ��� Integral Const
  int  Derivative;                                                       //  ΢�ֳ��� Derivative Const
  int  LastError;                                                        //  Error[-1]
  int  PrevError;                                                        //  Error[-2]
}iQPidObj;



/********λ�û�PD********/
typedef struct _pPD
{
  int  SetPoint;                                                         //  �趨Ŀ�� Desired Value
  int  Proportional;                                                       //  �������� Proportional Const
  int  Derivative;                                                       //  ΢�ֳ��� Derivative Const
  int  LastError;                                                        //  Error[-1]
	int Output;
	int MaxOutput;// Should be a positive number
}pPDObj;






/***********************************************�����ⲿ����*********************************************/

void iPID_Init (iPidObj *pid, int SetPoint,int Proportion,int Integral,int Derivative);
void iQPID_Init (iQPidObj *pid,int Proportion,int Integral,int Derivative);
int iPID_Calc(iPidObj *pid, int NextPoint );
int iQPID_Calc(iQPidObj *pid,int Error);
int pPD_Calc(pPDObj *pid, int feedback);
#endif
