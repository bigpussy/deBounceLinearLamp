/*********************************************************************************************
�������� ����� 
��д�ˣ� ���� ��
��дʱ�䣺�� 2014�� 12�� 20��
Ӳ��֧�֣���stc12c2052ad
�ӿ�˵������nothing to say��  
�޸���־������
����NO.1-								
/*********************************************************************************************
˵����

/*********************************************************************************************/


#include <STC12C2052AD.H>

sbit LED = P1 ^ 2;
sbit BTN = P1 ^ 1;

//100΢�뼶����ʱ����
//����ʹ�õ���12mhz���壬���ÿ60������Ϊ0.00001�룬
//Ҳ����0.1���룬100΢��	    
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
		millis ++; //����һ����ʱ����ÿ�����嶼��һ
		reading = BTN;
		//ÿ�����ж�һ�¶�ȡ�Ķ˿ں��ϴεĶ�ȡ�Ƿ�һ��
		if(reading != lastBtnState){
			//��һ�£�˵���������ڴ��ڶ���״̬
			lastDebounceTime = millis;
			lastBtnState = reading;
			//��������ѭ��
			continue;
		}
		//������Ϊһ��ʱ�����ȶ�֮�󣬽�������Ķ���
		if(millis > debounceDelay + lastDebounceTime){
			//�жϰ����Ƿ���иı���״̬
			//ֻ�е������ı�״̬����˵������������
			//����һֱ������Ҳ����룬���ǲ�����������if���
			if(reading !=btnState){
				btnState = reading;
				
				if(btnState == 1){ //�������״̬����0ת1˵���ǰ����İ��¹���
					brightness = brightness + step;
					//������ȴ���9����Ϩ�𣬴�0��ʼ
					if(brightness > 3){
						brightness = 0;
					}
				}
			}
		}
		//ͨ��pwm������ƣ������ݵ����Ƚ��е���
		PWM0_set(brightness * 85);
	}
}