#include "pid.h"
#include "encoder.h"

  


PID pid1;//w3
PID pid2;//w4
extern Motor motor1;//w3
extern Motor motor2;//w4

  

void PID_Init(PID* pid,int num)//PID参数初始化,num代表轮子编号

{

	if(num==3)
	{
		pid->kp = KP1;

		pid->ki = KI1;

		pid->kd = KD1;
	}
	else{
		pid->kp = KP4;

		pid->ki = KI4;

		pid->kd = KD4;
	}
	
	
	pid->maxOutput = 900;

    pid->output = 0;

	pid->p=0;
	
	pid->i=0;
	
	pid->d=0;
	
	pid->beforede=0;
	
	pid->lastde=0;
	
	pid->thisde=0;
	
	

}

  
  

/****************************************

 * 作用：进行一次PID计算

 * 参数：PID参数结构体地址；目标值；反馈值

 * 返回值：无

 * ****************************************/

void PID_SingleCal(PID* pid,float err)
{
	pid->thisde=err;
	
	pid->p=pid->kp*pid->thisde;
	
	pid->i=(pid->i+pid->lastde);
	
	pid->d=pid->kd*(pid->thisde-pid->lastde);
	
	pid->lastde=pid->thisde;
	
	pid->output=pid->p+pid->ki*pid->i+pid->d;
	
	if(pid->output>pid->maxOutput)
	{
		pid->output=pid->maxOutput;
	}
	if(pid->output < 0)
	{
		pid->output = 0;
	}
	

}


/*

void PID_SingleCal(PID* pid,float target,float feedback)//一次PID计算

{
//    static int erro,erro_last;
    float a=0.7;
	float b=0.4;
    pid->err=target - feedback;

    pid->err = (1-a)*pid->err + a*pid->lastErr; // 使得波形更加平滑，滤除高频干扰，放置速度突变
    //erro_last = pid->err;   // 防止速度过大影响直立环的正常工作

   //pid->err = target - feedback;

    





    pid->integral += pid->err;

    //printf("pid->integral = %f\r\n",pid->integral);

  

    if(pid->integral < -pid1.maxIntegral) pid->integral = -pid1.maxIntegral;//限制积分值

    else if(pid->integral > pid1.maxIntegral) pid->integral = pid1.maxIntegral;

    //pid->output = pid->err * pid->kp ;


  

   pid->output = (pid->kp * pid->err) + (pid->ki * pid->integral) + (pid1.kd * (pid->err - pid->lastErr));//全量式PID

  

    if(pid->output < 0) pid->output = 0;//限制积分值

    else if(pid->output > pid1.maxOutput) pid->output = pid1.maxOutput;

  
  

    pid->lastErr = pid->err;


	printf("%f,%f\r\n",motor1.speed,b);
}
*/

/*****************  
直立环PD控制器：Kp*Ek+Kd*Ek_D
入口：Med:机械中值(期望角度)，Angle:真实角度，gyro_X:真实角速度
出口：直立环输出
******************/
void Vertical(PID* pid,float Med,float Angle,float gyro_X) 
{
  
  
  pid->output = KP2*(Angle-Med)+KD2*(gyro_X-0);
  
  
} 

/*****************  
转向环：系数*Z轴角速度
******************/
void Turn(PID* pid,int gyro_Z)
{
  
  
  pid->output = KP3*gyro_Z;

}










