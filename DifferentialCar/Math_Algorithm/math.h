#ifndef MATH_H
#define MATH_H

#include "main.h"

#define R 0.1f // �����ĵ����ӵľ��� ��λ��m��
#define p 3.141592f
#define k_rpm p *R / 30.0f

#define D 0.06f           // ��λ��m
#define Redu_Ratio 30.0f  // ���ٱ�
#define Line_number 13.0f // ����
#define T 0.0001f         // ��������

void Mean_filtering(float a[11]);

#endif
