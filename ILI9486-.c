#include <includes.h>

  u16 id;	

/********************************************************************************************************
*	函 数 名: Delay
*	功能说明: 延时
*	形    参: nCount 延时计数
*	返 回 值: 无
*********************************************************************************************************/
static void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(u16 regval)
{    TFT_CMD_TO_FSMC(regval);//写入要写的寄存器序号	 
}

//写LCD数据
//data:要写入的值
void LCD_WR_DATA(u16 data)
{										    	   
	LCDx->LCD_RAM=data;		 
}

//读LCD数据
//返回值:读到的值
u16 LCD_RD_DATA(void)
{										    	   
	return LCDx->LCD_RAM;		 
}		

//指定寄存器写数据
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	TFT_CMD_TO_FSMC(LCD_Reg);  //写入要写的寄存器序号	 
	LCDx->LCD_RAM = LCD_RegValue;//写入数据	    		 
}	   
   
//开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
 	TFT_CMD_TO_FSMC(0x002C);	  
}	 

//画点
//x,y:坐标
//color:此点的颜色
void LCD_PutPixel(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);//设置光标位置 
	TFT_CMD_TO_FSMC(0x002C);	//开始写入GRAM
	LCDx->LCD_RAM=color; 
} 

//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 color; 
	LCD_SetCursor(x,y);	    
	LCD_WR_REG(0X2E);     //发送读GRAM指令
  LCD_RD_DATA();        //无效数据
//	 	color=LCD->LCD_RAM;  //无效数据(开优化时会被优化掉造成程序错误)	 
 	color=LCDx->LCD_RAM;  //实际坐标颜色	  						
  return color;						
}			 

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
	LCD_WR_REG(0X2A); 
	LCD_WR_DATA(Xpos>>8); 
	LCD_WR_DATA(Xpos&0XFF);	 
//			LCD_WR_DATA((480-1)>>8);
//	  LCD_WR_DATA((480-1)&0XFF);
	LCD_WR_REG(0X2B); 
	LCD_WR_DATA(Ypos>>8); 
	LCD_WR_DATA(Ypos&0XFF);	 
//	      LCD_WR_DATA((320-1)>>8);
//	   LCD_WR_DATA((320-1)&0XFF); 
} 

//初始化lcd

void ILI9486_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  FSMC_TimingInitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); //使能FSMC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTD,E时钟

	/*===========GPIO - LCD 背光控制========================*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PD13 推挽输出 背光
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	
	/*===========GPIO - LCD 数据总线========================*/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
									GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
									GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*===========GPIO - LCD 复位=============
	*	PE1 -> LCD_RESET
	 =======================================*/	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*===========GPIO - LCD 控制========================*/
	/**	
	 *	PD4(NOE) -> RD	,	PD5(NWE)	-> WR 
	 *	PD7(NE1) -> CS	,	PD11(A16) -> D/C 
	 */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
		
	/*===========FSMC初始化=======================*/
	
  FSMC_TimingInitStructure.FSMC_AddressSetupTime = 0x01;
  FSMC_TimingInitStructure.FSMC_AddressHoldTime = 0x00;
  FSMC_TimingInitStructure.FSMC_DataSetupTime = 0x02;
  FSMC_TimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  FSMC_TimingInitStructure.FSMC_CLKDivision = 0x00;
  FSMC_TimingInitStructure.FSMC_DataLatency = 0x00;
  FSMC_TimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_TimingInitStructure;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_TimingInitStructure;	  

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 
	
 	/*===========LCD 复位=======================*/
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
  Delay(0xAFFf<<2);					   
  GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
	Delay(0xAFFf<<2);

  /*===========读取LCD ID=======================*/	
	//尝试9486 ID的读取		
	LCD_WR_REG(0XD3);				   
	LCD_RD_DATA(); 				//dummy read 	
	LCD_RD_DATA();   	    	//读到0X00
	id=LCD_RD_DATA();   	//读取94								   
	id<<=8;
	id|=LCD_RD_DATA();  	//读取86 	

		LCD_WR_REG(0xB0);
		LCD_WR_DATA(0x00);
		LCD_WR_REG(0x11);
		Delay(2000);

		LCD_WR_REG(0xB3);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC0);
		LCD_WR_DATA(0x10);//13
		LCD_WR_DATA(0x3B);//480
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x02);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x00);//NW
		LCD_WR_DATA(0x43);

		LCD_WR_REG(0xC1);
		LCD_WR_DATA(0x10);//LCD_WR_DATA(0x08);
		LCD_WR_DATA(0x10);//LCD_WR_DATA(0x16);//CLOCK
		LCD_WR_DATA(0x08);
		LCD_WR_DATA(0x08);

		LCD_WR_REG(0xC4);
		LCD_WR_DATA(0x11);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x03);

		LCD_WR_REG(0xC6);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0xC8);//GAMMA
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x13);
		LCD_WR_DATA(0x5C);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x14);
		LCD_WR_DATA(0x08);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x21);
		LCD_WR_DATA(0x08);
		LCD_WR_DATA(0x14);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x53);
		LCD_WR_DATA(0x0C);
		LCD_WR_DATA(0x13);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x21);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0x35);
		LCD_WR_DATA(0x00);

		LCD_WR_REG(0x36);  
		LCD_WR_DATA(0x08);

		LCD_WR_REG(0x3A);
		LCD_WR_DATA(0x55);

		LCD_WR_REG(0x44);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);

		LCD_WR_REG(0xB6);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x22);//0 GS SS SM ISC[3:0];其中GS SS控制显示方向，同时修改R36
		LCD_WR_DATA(0x3B);

		LCD_WR_REG(0xD0);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x07);//VCI1
		LCD_WR_DATA(0x1D);//VRH

		LCD_WR_REG(0xD1);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x03);//VCM
		LCD_WR_DATA(0x00);//VDV

		LCD_WR_REG(0xD2);
		LCD_WR_DATA(0x03);
		LCD_WR_DATA(0x14);
		LCD_WR_DATA(0x04);

		LCD_WR_REG(0x29);
		Delay(2000);

		LCD_WR_REG(0xB4);
		LCD_WR_DATA(0x00);
		Delay(2000);
		LCD_WR_REG(0x2C);

}  

//清屏函数
//color:要清屏的填充色
void LCD_Clear(u16 color)
{
	u32 index=0;      
	LCD_SetCursor(0x00,0x00);	//设置光标位置 
	LCD_WriteRAM_Prepare();     //开始写入GRAM	 	  
	for(index=0;index<153600;index++)
	{
		LCDx->LCD_RAM=color;	   
	}
}  

//LCD开启显示
void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0X29);
}	 

//LCD关闭显示
void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0X28);	//关闭显示
} 

