	 
#include "Fontupd.h"
#include "ILI93xx.h"
#include "includes.h"
//���������ļ�,UNIGBK,GBK12,GBK16,GBK24һ�����
//x,y:��ʾ��Ϣ����ʾ��ַ
//size:�����С
//src:�ֿ���Դ����."0:",SD��;"1:",FLASH��,"2:",U��.
//��ʾ��Ϣ�����С										  
//����ֵ:0,���³ɹ�;
//		 ����,�������.	  
u8 update_font_lcd(void)
{	
	OS_ERR err;
	LCD_Clear(WHITE);
	OSSchedLock(&err);		//����������
	LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
	update_font(10,70,16,"0:");//�����ֿ�
	LCD_Clear(WHITE);
	POINT_COLOR = RED;
	LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
	OSSchedUnlock(&err);	//����������
}
