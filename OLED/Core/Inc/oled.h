#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f1xx_hal.h"	//����HAL��
/* BMPͼƬ����
	ͼƬ��ʽΪ��λ���飬�±�ֱ��ӦͼƬ�Ŀ�͸ߣ�
		BMP_xx[H/8][L];
*/
extern const uint8_t BMP_Picture[32 / 8][32];


/* ����������״̬ */
typedef enum
{
	SET_PIXEL = 0x01,
	RESET_PIXEL = 0x00,
} PixelStatus;


/* ���ܺ������� */
//д���ݣ�Ӳ��IICʹ��
void HAL_I2C_WriteByte(uint8_t addr, uint8_t data);
//д����
void WriteCmd(uint8_t IIC_Command);
//д����
void WriteDat(uint8_t IIC_Data);
//��ʼ��OLED
void OLED_Init(void);
//������ɱ�
void OLED_ON(void);
//�رյ�ɱ�
void OLED_OFF(void);
//ˢ�»��������ݵ�GDDRAM
void OLED_RefreshRAM(void);
//������ݻ�����OLED_RAM buffer
void OLED_ClearRAM(void);
//ȫ�����
void OLED_FullyFill(uint8_t fill_Data);
//����
void OLED_FullyClear(void);
//�����������ص�����
void OLED_SetPixel(int16_t x, int16_t y, uint8_t set_pixel);
//����������ص�����
PixelStatus OLED_GetPixel(int16_t x, int16_t y);

/* ��ʾָ���ַ���ͼƬʱ��Ҫ�ֶ�ˢ�»�������GDDRAM
* function list: OLED_ShowStr\OLED_ShowCN\OLED_Show_MixedCH\OLED_DrawBMP
*/
//��ʾӢ���ַ���
void OLED_ShowStr(int16_t x, int16_t y, uint8_t ch[], uint8_t TextSize);
//��ʾ�����ַ���
void OLED_ShowCN(int16_t x, int16_t y, uint8_t* ch);
//��ʾ��Ӣ�Ļ������
void OLED_ShowMixedCH(int16_t x, int16_t y, uint8_t* ch);
//��ʾͼƬ
void OLED_DrawBMP(int16_t x0, int16_t y0, int16_t L, int16_t H, const uint8_t BMP[]);

//�������
void OLED_AreaFill(int16_t x0, int16_t y0, int16_t L, int16_t H, uint8_t fill_data);
//�������
void OLED_AreaClear(int16_t x0, int16_t y0, int16_t L, int16_t H);
//ȫ���л���ʾ
void OLED_FullyToggle(void);
//�����л���ʾ
void OLED_AreaToggle(int16_t x0, int16_t y0, int16_t L, int16_t H);
//ȫ����ֱ��������
void OLED_VerticalShift(void);
//ȫ��ˮƽ��������
void OLED_HorizontalShift(uint8_t direction);
//ȫ��ͬʱ��ֱ��ˮƽ��������
void OLED_VerticalAndHorizontalShift(uint8_t direction);
//��Ļ����ȡ����ʾ
void OLED_DisplayMode(uint8_t mode);
//��Ļ���ȵ���
void OLED_IntensityControl(uint8_t intensity);


#endif
