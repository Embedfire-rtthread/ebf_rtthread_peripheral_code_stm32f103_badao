/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 工程模版
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               变量
*************************************************************************
*/
/* 定义线程控制块 */
static rt_thread_t test_thread = RT_NULL;

// 局部变量，用于保存转换计算后的电压值 	 
int ADC_ConvertedValueLocal;    
extern __IO uint16_t ADC_ConvertedValue;

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);


/*
*************************************************************************
*                             main 函数
*************************************************************************
*/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
    /* 
	 * 开发板硬件初始化，RTT系统初始化已经在main函数之前完成，
	 * 即在component.c文件中的rtthread_startup()函数中完成了。
	 * 所以在main函数中，只需要创建线程和启动线程即可。
	 */
	
	test_thread =                          /* 线程控制块指针 */
    rt_thread_create( "test",              /* 线程名字 */
                      test_thread_entry,   /* 线程入口函数 */
                      RT_NULL,             /* 线程入口函数参数 */
                      512,                 /* 线程栈大小 */
                      3,                   /* 线程的优先级 */
                      20);                 /* 线程时间片 */
                   
    /* 启动线程，开启调度 */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             线程定义
*************************************************************************
*/
static void test_thread_entry(void* parameter)
{	
	while (1)
	{
		ADC_ConvertedValueLocal =(int) (ADC_ConvertedValue * 825) >> 10; 
	
		rt_kprintf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_ConvertedValue); 
//		sprintf(adc_value,"\r\n The current AD value = %d mV \r\n",
//		       ADC_ConvertedValueLocal);
		rt_kprintf("\r\n The current AD value = %d mV \r\n",
								ADC_ConvertedValueLocal); 						/*rt_kprintf不能打印浮点数*/
		rt_kprintf("\r\n\r\n");
		
		rt_thread_delay(1000);   /* 延时500个tick */		 		
	}
}

/********************************END OF FILE****************************/
