#ifndef _BACKUPIF_H
#define _BACKUPIF_H
#include "stm32f10x.h"

//�ֿ�����ռ�õ�����������С(3���ֿ�+unigbk��+�ֿ���Ϣ=3238700�ֽ�,Լռ791��W25QXX����)
#define BACKUPSECSIZE	 	25   //100k 25��4096  1024��1k
//�ֿ�����ʼ��ַ 
#define BACKUPUSRFOADDR 	1024*1024*16-25*4096					//WarShip STM32F103 V3�Ǵ�12M��ַ�Ժ�ʼ����ֿ�
														//ǰ��12M��fatfsռ����.
														//12M�Ժ����3���ֿ�+UNIGBK.BIN,�ܴ�С3.09M,���ֿ�ռ����,���ܶ�!
														//15.10M�Ժ�,�û���������ʹ��.����������100K�ֽڱȽϺ�.


typedef struct
{
char userNAME[36];
char userNAMElong;
char liftManufactureNAME[36];
char liftManufactureNAMElong;
char liftManufactureMODEL[36];
char liftManufactureMODELlong;
char govenorManufactureNAME[36];
char govenorManufactureNAMElong;
char govenorfactureMODEL[36];
char govenorfactureMODELlong;
char govenorfactureNAME[36];
char govenorfactureNAMElong;

}login_content;//�û��������

typedef struct
{
float nominalSpeed;
float diameter;
float initSpeed;
float SpeedV1;
float SpeedV2;
float accelerate1;
float accelerate2;
float accelerate3;
float calibration;
int sort;//���� 0 ����ʽ��ȫǯ 2 ����˲ʱʽ 3������˲ʱʽ
}config_content;//������������

typedef enum{
success,
unsuccess
}result_enum;

typedef struct
{
int numb;  //���
float v1;
float v2;
result_enum result;
int statue;//״̬
int oteration;
}test_result; //�������

typedef struct
{
int init_v;  //���ٶȸ��ݶ�ٶȱ�
int accelerate_v1;//��һ�μ��ٵ��ٶ�
int accelerate_v2;//�ڶ��μ��ٵ��ٶ�
int result_v1;//�������ر�׼
int result_v2;//��е���ر�׼
int diameter;
int scale;
}test_result_compare;//�����Ƚ�ֵ

/*�û������������ݸ�ʽ*/
typedef struct 
{
	u8 flagok;		//a5		˵������
	u32 startaddr; 			//��ʼ��ַ
	u32 size;			//��С	 
	login_content backupUsr_information; //����������
	u32 endaddr;			//������ַ
}backupUsr_info;

/*�û������������ݸ�ʽ*/
typedef struct 
{
	u8 boot;		//a5	����Ϊ1 ������Ϊ0	˵������
	u32 startaddr; 			//��ʼ��ַ
	u32 endaddr;			//������ַ
}backupUsr_boot;

extern login_content  _login_content;
extern test_result  _test_result;
extern config_content  _config_content;
extern test_result_compare  _test_result_compare;
extern backupUsr_info _backupUsr_info;
extern backupUsr_boot _backupUsr_boot;

extern void Backup_init(void);

#endif

