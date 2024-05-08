#pragma once
#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <cmath>
#include <conio.h>  
#include <time.h>  
using namespace std;

#define PI 3.1415926 
#define circle_x 300
#define circle_y 240
#define hour_font_size 30
#define WIDTH 640+400
#define HEIGHT 480
#define K_MAX 1.797e308 

/*��������*/

void init(); //��ʼ�����ڴ�С;
void end();  //����;
void draw_pan(); //���Ʊ���;
void draw_time(struct tm t, struct tm tlast);//��е��ָ������Լ������ӻ���

//�����
void SDF_circle(int px, int py, COLORREF color, int r);//SDF����Բ��
void FillCircle_B(int x, int y, int r, COLORREF color);//��Բ��һ���㷨
void SDFline(int x0, int y0, int x1, int y1, int width, COLORREF color);//SDF�����߶�
int rgb_sum(struct rgb color);//���rgb��ɫ
void finalcolor(struct rgb& final, struct rgb& target, struct rgb& origin, double alpha);//alpha blending�㷨
void rgb_split(int color, struct rgb& rgbcolor);//rgb��ɫ�ָ�

//������
void pic(int x0, int y0, int angle, COLORREF color);//��ת��ͼ��
void draw_huan(int x0, int y0, int r1, double hudu, COLORREF color);//Բ������
void check(struct tm t);//�жϽ������Ƿ�����


