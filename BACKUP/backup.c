#include "backupIF.h"
#include <string.h>
#include "w25qxx.h"

login_content _login_content;
config_content _config_content;
test_result  _test_result;
test_result_compare  _test_result_compare;
backupUsr_info _backupUsr_info;
backupUsr_boot _backupUsr_boot;






/*
20����¼��һ���û��������
*/



void Backup_init(){
	
	u32 temp;
	memset(&_login_content,0x0,sizeof(login_content));
	memset(&_config_content,0x0,sizeof(config_content));
	memset(&_test_result,0x0,sizeof(test_result));
	memset(&_test_result_compare,0x0,sizeof(test_result_compare));
	memset(&_backupUsr_info,0x0,sizeof(backupUsr_info));
	memset(&_backupUsr_boot,0x0,sizeof(backupUsr_boot));
	//W25QXX_Erase_Sector(BACKUPUSRFOADDR/4096);		//�����������
	//W25QXX_Erase_Sector((BACKUPUSRFOADDR/4096)+1);		//�����������
	//W25QXX_Erase_Sector((BACKUPUSRFOADDR/4096)+2);		//�����������
	W25QXX_Read((u8*)(&_backupUsr_info),(BACKUPUSRFOADDR/4096)*4096,sizeof(backupUsr_info));//�����û����������
	if(_backupUsr_info.flagok==0xa5){
		_backupUsr_boot.boot=1;
		do{
			temp = _backupUsr_info.startaddr;
			W25QXX_Read((u8*)(&_backupUsr_info),_backupUsr_info.endaddr,sizeof(backupUsr_info));	
		}while(0xa5==_backupUsr_info.flagok);//�ҵ�û�б�־��
		W25QXX_Read((u8*)(&_backupUsr_info),temp,sizeof(backupUsr_info));//������
	}else{
		_backupUsr_boot.boot=0;
	}
}


