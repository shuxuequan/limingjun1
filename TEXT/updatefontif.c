	 
#include "Fontupd.h"
#include "ILI93xx.h"
#include "includes.h"
//更新字体文件,UNIGBK,GBK12,GBK16,GBK24一起更新
//x,y:提示信息的显示地址
//size:字体大小
//src:字库来源磁盘."0:",SD卡;"1:",FLASH盘,"2:",U盘.
//提示信息字体大小										  
//返回值:0,更新成功;
//		 其他,错误代码.	  
u8 update_font_lcd(void)
{	
	OS_ERR err;
	LCD_Clear(WHITE);
	OSSchedLock(&err);		//调度器上锁
	LCD_ShowString(10,50,250,30,16,"Font Updataing,Please Wait...");
	update_font(10,70,16,"0:");//更新字库
	LCD_Clear(WHITE);
	POINT_COLOR = RED;
	LCD_ShowString(10,50,280,30,16,"Font Updata finshed,Please Restart!");
	OSSchedUnlock(&err);	//调度器解锁
}
