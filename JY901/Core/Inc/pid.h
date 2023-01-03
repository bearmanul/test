#ifndef _PID_H_

#define _PID_H_

  

#include "stm32f1xx.h"

#include "encoder.h"

#include <stdio.h>

  

//PID三个参数的值



//速度环的
#define KP1 2000 //w3  2000

#define KI1 150   //30    20

#define KD1 0//400

#define KP4 1000 //w4   600

#define KI4 12 0//30    20

#define KD4 0//400



//角度环的
#define KP2   1
#define KD2   2

//转向环的
#define KP3  1
  
  

typedef struct _PID//PID参数结构体

{

    float kp,ki,kd;

    float p,i,d,beforede,thisde,lastde;

    //float integral,maxIntegral; //积分值

    float output,maxOutput;

}PID;

  

void PID_Init(PID* pid,int num);

void PID_SingleCal(PID* pid,float err);//一次PID计算

void Vertical(PID* pid,float Med,float Angle,float gyro_X) ;

void Turn(PID* pid,int gyro_Z);

  
  

#endif
