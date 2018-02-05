  #include "1602.h"


/********************************************************************************
函数名称：SMG_Init()
功    能：数码管IO初始化
参    数：无
返 回 值：无
*********************************************************************************/
void lcd1602IO_Init(void)
{
     GPIO_InitTypeDef        GPIO_InitStructure;
     
     /* GPIOA、GPIOB时钟使能 */
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);   //在AHB总线上
	
     /* 配置数码管位端口 外部输出上拉模式 */
     GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | \
																		 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | \
																		 GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12  ;
     GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;  //IO配置为输出模式 (输出、输入、复用功能、模拟功能)
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出模式   (推挽、开漏输出模式)
     GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;   //内部接上拉电阻  (上拉、下拉、不接上下拉电阻)
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //I/O输出翻转速度  (2M、10M、50MHz)
     GPIO_Init(GPIOA , &GPIO_InitStructure);
	
		 /* 配置数码管段端口 外部输出上拉模式 */
     GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
																		  
     GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/********************************************************************************
函数名称：DATA()
功    能：写数据
参    数：i : 要写入的数据
返 回 值：无
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

void E(unsigned char i)	//模块使能端，由高电平跳变成低电平时，液晶模块开始执行命令
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)i);	 //向E0写入i                          
}

void RS(unsigned char i)//寄存器选择，为1时选择数据寄存器，为0时选择指令寄存器	
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)i);	//向D3写入i                           
}


void RW(unsigned char i)//读/写选择，为1时读，为0时写	
{
	 GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)i);	//向E6写入i                   
}



/********************************************************************
* 名称 : delay()
* 功能 : 延时,延时时间大概为140US。
* 输入 : 无
* 输出 : 无
***********************************************************************/
void delay(uint a)
{
	int i,j;
	for(i=0; i<=a; i++)
	for(j=0;j<=80;j++);

}
/********************************************************************
* 名称 : enable(uchar del)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
***********************************************************************/
void enable(uchar del)//1602命令函数
{	 
	RS(0);
	RW(0);
	E(0);
	DATA(del); 
	delay(10);
	E(1);        //E脚要出现高脉冲，即0-1-0
	delay(10);
	E(0);
}
/********************************************************************
* 名称 : write(uchar del)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
***********************************************************************/
void write(uchar del)
{	
	RS(1);
	RW(0);
	E(0);
	DATA(del);
	delay(10);
	E(1);        //E脚要出现高脉冲，即0-1-0
	delay(10);
	E(0);
}
/********************************************************************
* 名称 : L1602_init()
* 功能 : 1602初始化，请参考1602的资料
* 输入 : 无
* 输出 : 无
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
* 名称 : L1602_char(uchar hang,uchar lie,char sign)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符显示"b" ，调用该函数如下
		 L1602_char(1,5,'b')
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
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
* 名称 : L1602_string(uchar hang,uchar lie,uchar *p)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符开始显示"ab cd ef" ，调用该函数如下
	 	 L1602_string(1,5,"ab cd ef;")
* 输入 : 行 : 1或2
				 列 : 从1开始 
				 需要输入1602的数据
				 
* 输出 : 无
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



