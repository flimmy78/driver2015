/**
  ******************************************************************************
  * @file    pid.c
  * @author  ZHAN Yubo
  * @version V9.0.0
  * @date    03-May-2014
  * @brief   This file is PID Algorithm
  *
*/

#include "pid.h"
#include "includes.h"
#include <math.h>

void iPID_Init (iPidObj *pid, int SetPoint,int Proportion,int Integral,int Derivative)
{
  pid->SetPoint=SetPoint;                                                       //��ֵ̬
  pid->Proportional=Proportion;                                                   //��������
  pid->Integral=Integral;                                                       //���ֲ���
  pid->Derivative=Derivative;                                                   //΢�ֲ���
  pid->LastError=0;                                                             //Error[-1]
  pid->SumError=0;                                                              //Sums of Errors
}

void iQPID_Init (iQPidObj *pid,int Proportion,int Integral,int Derivative)
{
  pid->Proportional=Proportion;                                                   //��������
  pid->Integral=Integral;                                                       //���ֲ���
  pid->Derivative=Derivative;                                                   //΢�ֲ���
  pid->LastError=0;                                                             //  Error[-1]
  pid->PrevError=0;                                                             //  Error[-2]
}

int iPID_Calc(iPidObj *pid, int NextPoint )
{
	int dError,Error;
	int pOut;
	pOut = pid->Proportional * NextPoint;
	Error = pid->SetPoint - NextPoint;                                           // ƫ��
	pid->SumError += (pid->Integral * Error);                                                      // ����
	if( pid->SumError > pid->MaxSumError )
	{
		pid->SumError = pid->MaxSumError;
	}
	else if(pid->SumError < -pid->MaxSumError)
	{
		pid->SumError = -pid->MaxSumError;
	}
	dError = Error - pid->LastError;                                             // ��ǰ΢��
	pid->LastError = Error;
	
	pid->Output = ( pOut +  pid->SumError + pid->Derivative * dError); 
	if(pid->Output > pid->MaxOutput)
	{
		pid->Output = pid->MaxOutput;
	}
	else if( pid->Output < -pid->MaxOutput )
	{
		pid->Output = -pid->MaxOutput;
	}
	return  pid->Output;
}

int iQPID_Calc(iQPidObj *pid,int Error)
{
	 int OutDelta;
																														//����������
	 OutDelta = pid->Proportional * (Error - pid->LastError) +
							pid->Integral * Error +
							pid->Derivative * (Error - 2 * pid->LastError + pid->PrevError);
	 pid->PrevError = pid->LastError;                                           //e(k-2)
	 pid->LastError = Error;                                                    //e(k-1)
	 return OutDelta;                                                //����˥��
}

int pPD_Calc(pPDObj *pid, int feedback)
{
	int Error = pid->SetPoint - feedback;
	int dError = Error - pid->LastError; 
	
	pid->LastError = Error;
	
	pid->Output = pid->Proportional*Error/2 + pid->Derivative*dError;
	if( pid->Output > pid->MaxOutput )
	{
		pid->Output = pid->MaxOutput;
	}
	else if( pid->Output < -pid->MaxOutput )
	{
		pid->Output = -pid->MaxOutput;
	}
	return pid->Output;
}
/*========================== END OF FILE =======================================*/


