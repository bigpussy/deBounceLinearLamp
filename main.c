/*********************************************************************************************
程序名： 　　 
编写人： 　　 　
编写时间：　 年 月 日
硬件支持：　　
接口说明：　　  
修改日志：　　
　　NO.1-								
/*********************************************************************************************
说明：

/*********************************************************************************************/



#include <STC12C2052AD.H>

sbit LED = P1 ^ 1;
sbit BTN = P1 ^ 2;

void delay(unsigned int a){
	unsigned int i;
	while(--a != 0 ){
		for(i = 0; i < 60; i++);
	}
}


void main(void){
	unsigned long millis = 0;
	unsigned long lastDebounceTime;
	unsigned long debounceDelay = 50;
	int lastBtnState = 0;
	int btnState = 0;
	int reading = 0;
	int brightness = 0;
	int step = 2;
	while(1){
		millis ++;
		reading = BTN;
		if(reading != lastBtnState){
			lastDebounceTime = millis;
			lastBtnState = reading;
			continue;
		}
		if(millis > debounceDelay + lastDebounceTime){
			if(reading !=btnState){
				btnState = reading;
				
				if(btnState == 1){
					brightness = brightness + step;
					
					if(brightness >= 10 || brightness <= 0){
						step = - step;
					}
				}
			}
		}
		//delay(1);
		if(brightness < 10){
			LED = 1;
			delay(10 - brightness);
		}
		if(brightness > 0){
			LED = 0;
			delay(brightness);
		}
	}
}