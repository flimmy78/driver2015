#ifndef _ENCODER_H_
#define _ENCODER_H_

#define ENCODER_COUNTER TIM3->CNT

#define INC_ENC_REVOLUTION (int)(500*4) // �����������ֱ���
#define ABS_ENC_REVOLUTION (int)(500*4)//����ֵ�������ֱ���
#define MOTOR_POLE (4)
#define ELEC_REVOLUTION_INC (INC_ENC_REVOLUTION/MOTOR_POLE)
#define ELEC_REVOLUTION_ABS (ABS_ENC_REVOLUTION/MOTOR_POLE)

#define K (1.38) 	//���Ա�������4096ÿȦ���������������ֱ���֮��
#define D (int)(4096/K)			//�����������ķֱ���

/*�����������ṹ��*/
typedef struct _encoderReadType
{
	int V; //�ٶ�
	int DP;	//λ�ñ仯��
	int LastV;
	int LastP;//��һ�ε�λ��
	int CNT32;//32bits soft encoder counter
	int Multi;
	int Single;
	int Value;
	int Delta;
}encoderReadType;

typedef struct
{
	char flag;
	char buf[15];
	int counter;
	int num;
	int value;
	int multi;
	int single;
	int sign;
	
}absObj;

///*�����������Ķ�ȡ���ݵĽṹ��*/
extern encoderReadType Encoder;
extern absObj absEnc;

#define MOTOR_POSITION (int)(Encoder.S+Encoder.CNT32)
void Encoder_Configuration(void);
void USART4_Configuration( void );
void encoderTask ( void *pvParameters );
#endif
