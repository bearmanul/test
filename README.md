#  一、软件功能

​		基于cubemx和stm32控制0.96寸四脚oled屏幕显示

## 	1、显示字符串

​		**OLED_ShowStr**函数用于显示英文字符串。

## 	2、显示汉字

​		**OLED_ShowCN**函数用于显示中文字符串。

## 	3、显示图片

​		**OLED_DrawBMP**函数用于显示图片。

# 二、使用环境

## 	1、软件环境

​		本工程基于cubemx的HAL库，使用keil5编译下载到stm32中实现功能。

## 	2、硬件环境

​		本工程基于stm32c8t6编写，硬件连接如下：

| oled屏 | stm32 |
| ------ | ----- |
| VCC    | 5V    |
| GND    | GND   |
| SCL    | PB6   |
| SDA    | PB7   |

# 三、使用说明

## 	1、首先初始化oled

​		OLED_Init函数进行初始化。

## 	2、编写显示函数

		#### 				OLED_FullyFill

​					全屏填充

#### 				OLED_FullyClear

​					清屏

#### 				OLED_SetPixel

​					设置坐标像素点数据

#### 				OLED_ShowStr

​					显示英文字符串

#### 				OLED_ShowCN

​					显示中文字符串

#### 				OLED_DrawBMP

​					显示图片

#### 				OLED_AreaFill

​					区域填充

#### 				OLED_AreaClear

​					区域清除

## 	3、刷新缓冲区数据到GDDRAM

​				**OLED_RefreshRAM**

# 四、常见问题说明

## 	1、有点汉字不能显示

​		codetab.h中可以添加16X16的汉字，16进制数可以通过取模软件获取。

## 	2、编写显示函数以后无法显示

​		编写显示功能以后需要刷新缓冲区数据到GDDRAM









