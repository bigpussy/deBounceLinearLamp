/*********************************************************************************************
程序名： 　杨超　 
编写人： 　　 　
编写时间：　 2014年 12月 20日
硬件支持：　stc12c2052ad
接口说明：　nothing to say　  
修改日志：　　
　　NO.1-								
/*********************************************************************************************
说明：

/*********************************************************************************************/


#include <STC12C2052AD.H>

sbit LED = P1 ^ 2;
sbit BTN = P1 ^ 1;

//100微秒级别延时程序
//由于使用的是12mhz晶体，因此每60次脉冲为0.00001秒，
//也就是0.1毫秒，100微秒	    
void delay(unsigned int a){
	unsigned int i;
	while(--a != 0 ){
		for(i = 0; i < 60; i++);
	}
}

void PWM_init(){
	CMOD = 0x02;
	CH = 0x00;
	CCAPM0 = 0x42;
	CCAP0L = 0x00;
	CCAP0H = 0x00;
	
	CR = 1;
}
void PWM0_set(unsigned char a){
	CCAP0L = a;
	CCAP0H = a;
}
void main(void){
	unsigned long millis = 0;
	unsigned long lastDebounceTime;
	unsigned long debounceDelay = 50;
	int lastBtnState = 0;
	int btnState = 0;
	int reading = 0;
	int brightness = 0;
	int step = 1;

	PWM_init();
	
	while(1){
		millis ++; //增加一个计时器，每次脉冲都加一
		reading = BTN;
		//每次先判断一下读取的端口和上次的读取是否一致
		if(reading != lastBtnState){
			//不一致，说明按键正在处于抖动状态
			lastDebounceTime = millis;
			lastBtnState = reading;
			//跳出本次循环
			continue;
		}
		//当按键为一段时间内稳定之后，进行下面的动作
		if(millis > debounceDelay + lastDebounceTime){
			//判断按键是否进行改变了状态
			//只有当按键改变状态，才说明按键按下了
			//按键一直不动，也会进入，但是不会进入下面的if语句
			if(reading !=btnState){
				btnState = reading;
				
				if(btnState == 1){ //如果按键状态是由0转1说明是按键的按下过程
					brightness = brightness + step;
					//如果亮度大于9，则熄灭，从0开始
					if(brightness > 3){
						brightness = 0;
					}
				}
			}
		}
		//通过pwm脉宽调制，将灯泡的亮度进行调整
		PWM0_set(brightness * 85);
	}
}