#ifndef _BACKUPIF_H
#define _BACKUPIF_H
#include "stm32f10x.h"

//字库区域占用的总扇区数大小(3个字库+unigbk表+字库信息=3238700字节,约占791个W25QXX扇区)
#define BACKUPSECSIZE	 	25   //100k 25个4096  1024是1k
//字库存放起始地址 
#define BACKUPUSRFOADDR 	1024*1024*16-25*4096					//WarShip STM32F103 V3是从12M地址以后开始存放字库
														//前面12M被fatfs占用了.
														//12M以后紧跟3个字库+UNIGBK.BIN,总大小3.09M,被字库占用了,不能动!
														//15.10M以后,用户可以自由使用.建议用最后的100K字节比较好.


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

}login_content;//用户输入参数

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
int sort;//种类 0 渐进式安全钳 2 滚柱瞬时式 3、其他瞬时式
}config_content;//测量参数设置

typedef enum{
success,
unsuccess
}result_enum;

typedef struct
{
int numb;  //序号
float v1;
float v2;
result_enum result;
int statue;//状态
int oteration;
}test_result; //测量结果

typedef struct
{
int init_v;  //初速度根据额定速度变
int accelerate_v1;//第一次加速的速度
int accelerate_v2;//第二次加速的速度
int result_v1;//电气开关标准
int result_v2;//机械开关标准
int diameter;
int scale;
}test_result_compare;//测量比较值

/*用户保存数据数据格式*/
typedef struct 
{
	u8 flagok;		//a5		说明存在
	u32 startaddr; 			//开始地址
	u32 size;			//大小	 
	login_content backupUsr_information; //真正的数据
	u32 endaddr;			//结束地址
}backupUsr_info;

/*用户保存数据数据格式*/
typedef struct 
{
	u8 boot;		//a5	存在为1 不存在为0	说明存在
	u32 startaddr; 			//开始地址
	u32 endaddr;			//结束地址
}backupUsr_boot;

extern login_content  _login_content;
extern test_result  _test_result;
extern config_content  _config_content;
extern test_result_compare  _test_result_compare;
extern backupUsr_info _backupUsr_info;
extern backupUsr_boot _backupUsr_boot;

extern void Backup_init(void);

#endif

