#include "print.h"

void printer_print(char *s){
	char *ch;
	int i = strlen(s);
	ch = s;
	
	while(i--)

	{
	USART_SendData(USART3, *(ch++));

	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
   	USART_SendData(USART3, 0x0d);

	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	USART_SendData(USART3, 0x0a);

	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
    
}

