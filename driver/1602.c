  #include "1602.h"


/********************************************************************************
�������ƣ�SMG_Init()
��    �ܣ������IO��ʼ��
��    ������
�� �� ֵ����
*********************************************************************************/
void lcd1602IO_Init(void)
{
     GPIO_InitTypeDef        GPIO_InitStructure;
     
     /* GPIOA��GPIOBʱ��ʹ�� */
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);   //��AHB������
	
     /* ���������λ�˿� �ⲿ�������ģʽ */
     GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | \
																		 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | \
																		 GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12  ;
     GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;  //IO����Ϊ���ģʽ (��������롢���ù��ܡ�ģ�⹦��)
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //�������ģʽ   (���졢��©���ģʽ)
     GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;   //�ڲ�����������  (��������������������������)
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //I/O�����ת�ٶ�  (2M��10M��50MHz)
     GPIO_Init(GPIOA , &GPIO_InitStructure);
	
		 /* ��������ܶζ˿� �ⲿ�������ģʽ */
     GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
																		  
     GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/********************************************************************************
�������ƣ�DATA()
��    �ܣ�д����
��    ����i : Ҫд�������
�� �� ֵ����
*********************************************************************************/
void DATA(uchar i)
{
		if(i&0x01)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}
		/*****************************************/
		if(i&0x02)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
		/*****************************************/
		if(i&0x04)
		{
				GPIO_SetBits(GPIOB,GPIO_Pin_4);
    }
		else
		{
				GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		}
		/*****************************************/
		if(i&0x08)
		{
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
    }
		else
		{
				GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		}
		/*****************************************/
		if(i&0x10)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		}
		/*****************************************/
		if(i&0x20)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		}
		/*****************************************/
		if(i&0x40)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		}
		/*****************************************/
		if(i&0x80)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
    }
		else
		{
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		}	
}

void E(unsigned char i)	//ģ��ʹ�ܶˣ��ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ�鿪ʼִ������
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)i);	 //��E0д��i                          
}

void RS(unsigned char i)//�Ĵ���ѡ��Ϊ1ʱѡ�����ݼĴ�����Ϊ0ʱѡ��ָ��Ĵ���	
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)i);	//��D3д��i                           
}


void RW(unsigned char i)//��/дѡ��Ϊ1ʱ����Ϊ0ʱд	
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)i);	//��E6д��i                   
}



/********************************************************************
* ���� : delay()
* ���� : ��ʱ,��ʱʱ����Ϊ140US��
* ���� : ��
* ��� : ��
***********************************************************************/
void delay(uint a)
{
	int i,j;
	for(i=0; i<=a; i++)
	for(j=0;j<=80;j++);

}
/********************************************************************
* ���� : enable(uchar del)
* ���� : 1602�����
* ���� : ���������ֵ
* ��� : ��
***********************************************************************/
void enable(uchar del)//1602�����
{	 
	RS(0);
	RW(0);
	E(0);
	DATA(del); 
	delay(10);
	E(1);        //E��Ҫ���ָ����壬��0-1-0
	delay(10);
	E(0);
}
/********************************************************************
* ���� : write(uchar del)
* ���� : 1602д���ݺ���
* ���� : ��Ҫд��1602������
* ��� : ��
***********************************************************************/
void write(uchar del)
{	
	RS(1);
	RW(0);
	E(0);
	DATA(del);
	delay(10);
	E(1);        //E��Ҫ���ָ����壬��0-1-0
	delay(10);
	E(0);
}
/********************************************************************
* ���� : L1602_init()
* ���� : 1602��ʼ������ο�1602������
* ���� : ��
* ��� : ��
***********************************************************************/
void L1602_init(void)
{
		enable(0x38);
		delay(10);
		enable(0x0c);
		delay(10);
		enable(0x06);
		delay(10);
		enable(0x01);
		delay(10);
}
/********************************************************************
* ���� : L1602_char(uchar hang,uchar lie,char sign)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʾ"b" �����øú�������
		 L1602_char(1,5,'b')
* ���� : �У��У���Ҫ����1602������
* ��� : ��
***********************************************************************/
void L1602_char(uchar hang,uchar lie,char sign)
{
		uchar a;
		if(hang == 1) a = 0x80;
		if(hang == 2) a = 0xc0;
		a = a + lie - 1;
		enable(a);
		write(sign);
}
/********************************************************************
* ���� : L1602_string(uchar hang,uchar lie,uchar *p)
* ���� : �ı�Һ����ĳλ��ֵ�����Ҫ�õ�һ�У�������ַ���ʼ��ʾ"ab cd ef" �����øú�������
	 	 L1602_string(1,5,"ab cd ef;")
* ���� : �� : 1��2
				 �� : ��1��ʼ 
				 ��Ҫ����1602������
				 
* ��� : ��
***********************************************************************/
void L1602_string(uchar hang,uchar lie,uchar *p)
{
		uchar a;
		if(hang == 1) a = 0x80;
		if(hang == 2) a = 0xc0;
		a = a + lie - 1;
		enable(a);
		while(1)
		{
				if(*p == '\0') break;
				write(*p);
				p++;
		}
}



