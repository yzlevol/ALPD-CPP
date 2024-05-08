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

/*函数声明*/

void init(); //初始化窗口大小;
void end();  //重置;
void draw_pan(); //绘制表盘;
void draw_time(struct tm t, struct tm tlast);//机械表指针绘制以及数字钟绘制

//抗锯齿
void SDF_circle(int px, int py, COLORREF color, int r);//SDF绘制圆形
void FillCircle_B(int x, int y, int r, COLORREF color);//画圆另一种算法
void SDFline(int x0, int y0, int x1, int y1, int width, COLORREF color);//SDF绘制线段
int rgb_sum(struct rgb color);//组合rgb颜色
void finalcolor(struct rgb& final, struct rgb& target, struct rgb& origin, double alpha);//alpha blending算法
void rgb_split(int color, struct rgb& rgbcolor);//rgb颜色分割

//数字钟
void pic(int x0, int y0, int angle, COLORREF color);//旋转的图形
void draw_huan(int x0, int y0, int r1, double hudu, COLORREF color);//圆环绘制
void check(struct tm t);//判断进度条是否满格


