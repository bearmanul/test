#include "encoder.h"
#include "stm32f1xx_hal_tim.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "pid.h"
  
uint8_t voidErr = 0;//第一次速度计算有问题，直接规避掉不输出
float a=0.4;


Motor motor1;//w3
Motor motor2;//w4

extern PID pid1;//w3
extern PID pid2;//w4




  

void Motor_Init(void)

{ 

    HAL_TIM_Encoder_Start(&ENCODER_TIM, TIM_CHANNEL_ALL);      //开启编码器定时器

    __HAL_TIM_ENABLE_IT(&ENCODER_TIM,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理

    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启10ms定时器中断

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_3);            //开启PWM

    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_4);            //开启PWM

    __HAL_TIM_SET_COUNTER(&ENCODER_TIM, 10000);                //编码器定时器初始值设定为10000

    motor1.lastCount = 0;                                   //结构体内容初始化

    motor1.totalCount = 0;

    motor1.overflowNum = 0;                                  

    motor1.speed = 0;

    motor1.direct = 0;

}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度

{

    if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了

    {
		if(voidErr==0)
			voidErr=1;
		else{
			printf("%f,%f,%f\r\r\n",motor1.speed,motor2.speed,a);
		
		
		PID_SingleCal(&pid1,0.4-motor1.speed);
		PID_SingleCal(&pid2,0.4-motor2.speed);
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,pid1.output);//3
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);//3
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000-pid2.output);//4
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);//4
		}
		
//        
	}

}
