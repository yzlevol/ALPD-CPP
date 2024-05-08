#include"ClockPlus.h"

struct rgb {
	short r;
	short g;
	short b;
};

struct point {
	int x;
	int y;
};

/*初始化*/
void init()
{
	initgraph(WIDTH, HEIGHT);
}
/*结束重置*/
void end()
{
	graphdefaults();
}

/*绘制表盘工具*/
void draw_pan()
{
	// 画渐变的背景(通过亮度逐渐增加)
	float H = 0;		// 色相
	float S = 0.32f;		// 饱和度
	float L = 0.50f;		// 亮度
	for (int y = 0; y < HEIGHT; y++)
	{
		L += 0.0002f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, WIDTH - 1, y);
	}
	graphdefaults();

	//圆盘绘制
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 4); //设置线条粗细

	SDF_circle(circle_x, circle_y, HSLtoRGB(0.0f, 0.19f, 0.63f), 230);
	SDF_circle(circle_x, circle_y, WHITE, 195);
	//FillCircle_B(circle_x, circle_y, 230, HSLtoRGB(0.0f, 0.19f, 0.63f));
	//FillCircle_B(circle_x, circle_y, 195, WHITE);
	fillcircle(circle_x, circle_y, 195);    //普通填充圆

	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = hour_font_size + 5;						// 设置字体高度为 48
	//_tcscpy_s(f.lfFaceName, _T("Consolas"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	_tcscpy_s(f.lfFaceName, _T("Segoe UI Semibold"));
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	/*数字绘制*/
	//Ⅰ Ⅱ Ⅲ Ⅳ Ⅴ Ⅵ Ⅶ Ⅷ Ⅸ Ⅹ Ⅺ Ⅻ
	/*12 3 6 9*/
	outtextxy(circle_x - hour_font_size / 2, circle_y - 197, _T("Ⅻ"));//12 
	outtextxy(500 - 3 - hour_font_size, circle_y - hour_font_size / 2, _T("Ⅲ"));//3
	outtextxy(circle_x - hour_font_size / 2, circle_y + 197 - hour_font_size, _T("Ⅵ"));//6
	outtextxy(100 + 3, circle_y - hour_font_size / 2, _T("Ⅸ"));//9
	/*12 45 78 1011*/
	int x12 = circle_x;
	int y12 = circle_y - 197 + hour_font_size / 2;
	int x3 = 500 - 3 - hour_font_size / 2;
	int y3 = circle_y;
	int x6 = circle_x;
	int y6 = circle_y + 197 - hour_font_size / 2;
	int x9 = 100 + 3 + hour_font_size / 2;
	int y9 = circle_y;
	int r_hour = circle_y - y12 + 1;
	double sin30 = sin(30 * PI / 180);
	double cos30 = cos(30 * PI / 180);

	outtextxy(x12 + (int)(r_hour * sin30) - hour_font_size / 2 + 2, circle_y - (int)(r_hour * cos30) - hour_font_size / 2 - 2, _T("Ⅰ"));//1
	outtextxy(x12 + (int)(r_hour * cos30) - hour_font_size / 2 + 2, circle_y - (int)(r_hour * sin30) - hour_font_size / 2 - 2, _T("Ⅱ"));//2
	outtextxy(x12 + (int)(r_hour * cos30) - hour_font_size / 2 + 2, circle_y + (int)(r_hour * sin30) - hour_font_size / 2 + 2, _T("Ⅳ"));//4
	outtextxy(x12 + (int)(r_hour * sin30) - hour_font_size / 2 + 2, circle_y + (int)(r_hour * cos30) - hour_font_size / 2 + 2, _T("Ⅴ"));//5
	outtextxy(x12 - (int)(r_hour * sin30) - hour_font_size / 2, circle_y + (int)(r_hour * cos30) - hour_font_size / 2, _T("Ⅶ"));//7
	outtextxy(x12 - (int)(r_hour * cos30) - hour_font_size / 2, circle_y + (int)(r_hour * sin30) - hour_font_size / 2, _T("Ⅷ"));//8
	outtextxy(x12 - (int)(r_hour * cos30) - hour_font_size / 2, circle_y - (int)(r_hour * sin30) - hour_font_size / 2, _T("Ⅹ"));//10
	outtextxy(x12 - (int)(r_hour * sin30) - hour_font_size / 2, circle_y - (int)(r_hour * cos30) - hour_font_size / 2, _T("Ⅺ"));//11


	double sina = 0;
	double cosa = 0;

	/*刻度绘制*/
	setlinecolor(HSLtoRGB(0.0f, 0.19f, 0.63f));
	setlinestyle(PS_SOLID, 6);

	int kedu = 10;
	f.lfHeight = kedu;
	int r1 = r_hour - 2;
	int r2 = r_hour + 10;
	for (int i = 1; i < 60; i++) {
		if (i % 5 == 0) {
			continue;
		}
		else {
			sina = sin((i * 6) * PI / 180);
			cosa = cos((i * 6) * PI / 180);
			if (i <= 15) {
				SDFline(x12 + (int)(r1 * sina), circle_y - (int)(r1 * cosa), x12 + (int)(r2 * sina), circle_y - (int)(r2 * cosa), 5, HSLtoRGB(0.0f, 0.19f, 0.63f));
			}
			else if (i <= 30) {
				SDFline(x12 + (int)(r1 * sina), circle_y - (int)(r1 * cosa), x12 + (int)(r2 * sina), circle_y - (int)(r2 * cosa), 5, HSLtoRGB(0.0f, 0.19f, 0.63f));
			}
			else if (i <= 45) {
				SDFline(x12 + (int)(r1 * sina), circle_y - (int)(r1 * cosa), x12 + (int)(r2 * sina), circle_y - (int)(r2 * cosa), 5, HSLtoRGB(0.0f, 0.19f, 0.63f));
			}
			else {
				SDFline(x12 + (int)(r1 * sina), circle_y - (int)(r1 * cosa), x12 + (int)(r2 * sina), circle_y - (int)(r2 * cosa), 5, HSLtoRGB(0.0f, 0.19f, 0.63f));
			}
		}
	}

}

void check(struct tm t)
{
	if (t.tm_hour == 0) {
		FillCircle_B(circle_x + 550 - 150 + 100, circle_y - 100 + 50 - 20 - 80, 60, HSLtoRGB(152, 0.11f, 0.87f));
	}
	if (t.tm_min == 0) {
		FillCircle_B(circle_x + 500 - 150 - 20, circle_y + 50 + 20 + 50, 60, HSLtoRGB(152, 0.11f, 0.87f));
	}
	if (t.tm_sec == 0) {
		FillCircle_B(circle_x + 600 - 150 + 20 + 200, circle_y + 50 + 20 + 50, 60, HSLtoRGB(152, 0.11f, 0.87f));
	}
}

/*绘制表针工具*/
void draw_time(struct tm t, struct tm tlast)
{
	Beep(700, 300); //秒针蜂鸣
	/*指针长度*/
	int len_sec = 640 / 4;
	int len_min = len_sec * 10 / 13;
	int len_hour = len_sec * 7 / 13;

	/*指针角度*/
	double deg_sec = (t.tm_sec * 6) * PI / 180.0;
	double deg_min = (t.tm_min * 6) * PI / 180.0;
	double deg_hour = (t.tm_hour * 6 * 5) * PI / 180.0;

	double deg_sec0 = (tlast.tm_sec * 6) * PI / 180.0;
	double deg_min0 = (tlast.tm_min * 6) * PI / 180.0;
	double deg_hour0 = (tlast.tm_hour * 6 * 5) * PI / 180.0;


	settextstyle(30, 0, _T("华文琥珀"));
	draw_huan(circle_x + 550 - 150 + 100, circle_y - 100 + 50 - 20 - 80, 60, (deg_hour) / 2, HSLtoRGB(248, 0.53f, 0.58f));

	settextcolor(HSLtoRGB(0, 0.65f, 0.65f));
	outtextxy(circle_x + 550 - 150 - 15 + 100, circle_y - 100 - 13 + 50 - 20 - 80, char(t.tm_hour / 10 + 48));
	outtextxy(circle_x + 550 - 150 + 100, circle_y - 100 - 13 + 50 - 20 - 80, char(t.tm_hour % 10 + 48));

	draw_huan(circle_x + 500 - 150 - 20, circle_y + 50 + 20 + 50, 60, deg_min, HSLtoRGB(63, 0.93f, 0.75f));

	settextcolor(HSLtoRGB(0, 0.65f, 0.65f));
	outtextxy(circle_x + 500 - 150 - 15 - 20, circle_y - 13 + 50 + 20 + 50, char(t.tm_min / 10 + 48));
	outtextxy(circle_x + 500 - 150 - 20, circle_y - 13 + 50 + 20 + 50, char(t.tm_min % 10 + 48));

	draw_huan(circle_x + 600 - 150 + 20 + 200, circle_y + 50 + 20 + 50, 60, deg_sec, HSLtoRGB(126, 0.75f, 0.75f));

	settextcolor(HSLtoRGB(0, 0.65f, 0.65f));
	outtextxy(circle_x + 600 - 150 - 15 + 20 + 200, circle_y - 13 + 50 + 20 + 50, char(t.tm_sec / 10 + 48));
	outtextxy(circle_x + 600 - 150 + 20 + 200, circle_y - 13 + 50 + 20 + 50, char(t.tm_sec % 10 + 48));




	setlinestyle(PS_SOLID, 10);
	/*秒针绘制*/
	setlinecolor(WHITE);
	line(circle_x, circle_y, circle_x + (int)(len_sec * sin(deg_sec0)), circle_y - (int)(len_sec * cos(deg_sec0)));
	setlinecolor(HSLtoRGB(134, 0.32f, 0.63f));
	SDFline(circle_x, circle_y, circle_x + (int)(len_sec * sin(deg_sec)), circle_y - (int)(len_sec * cos(deg_sec)), 6, HSLtoRGB(134, 0.32f, 0.63f));

	/*分针绘制*/
	setlinecolor(WHITE);
	line(circle_x, circle_y, circle_x + (int)(len_min * sin(deg_min0)), circle_y - (int)(len_min * cos(deg_min0)));
	setlinecolor(HSLtoRGB(205, 0.50f, 0.63f));//HSLtoRGB()
	SDFline(circle_x, circle_y, circle_x + (int)(len_min * sin(deg_min)), circle_y - (int)(len_min * cos(deg_min)), 8, HSLtoRGB(205, 0.50f, 0.63f));

	/*时针绘制*/
	setlinecolor(WHITE);
	line(circle_x, circle_y, circle_x + (int)(len_hour * sin(deg_hour0)), circle_y - (int)(len_hour * cos(deg_hour0)));
	setlinecolor(HSLtoRGB(325, 0.46f, 0.32f));
	SDFline(circle_x, circle_y, circle_x + (int)(len_hour * sin(deg_hour)), circle_y - (int)(len_hour * cos(deg_hour)), 9, HSLtoRGB(325, 0.46f, 0.32f));


}


/*旋转图形*/
void pic(int x0, int y0, int angle, COLORREF color)
{
	setorigin(x0, y0);

	//编写功能代码    
	setcolor(color);
	setlinestyle(PS_SOLID, 10);
	setaspectratio(0.30f, 0.30f);
	double x = 0, y = 0;
	int x1, y1;
	for (double t = -50 * PI; t < 50 * PI; t += 1) {
		x = 100 * (cos(t / 50) + cos(3 * t / 50));
		y = 100 * (sin(t / 50.0) + sin(5 * t / 50));
		x1 = (int)(x * cos(angle) - y * sin(angle));
		y1 = (int)(x * sin(angle) + y * cos(angle));
		if (t == -50 * PI)
			moveto(x1, y1);  //移动到起始位置
		lineto(x1, y1);
		moveto(x1, y1);
	}
	setorigin(0, 0);
	setaspectratio(1, 1);
}

int inside_circle_or_not(int px, int py, int x0, int y0, int r)
{
	if ((px - x0) * (px - x0) + (py - y0) * (py - y0) <= r * r) {
		return 1;
	}
	else
		return 0;
}

void draw_huan(int x0, int y0, int r1, double hudu, COLORREF color)
{
	int px, py;
	double angle = 0;
	if (angle < 0) {
		angle *= -1;
	}
	if (angle > 2 * PI)
		angle = 2 * PI;
	for (py = y0 - r1; py <= y0 + r1; py++) {
		for (px = x0 - r1; px <= x0 + r1; px++) {
			if (inside_circle_or_not(px, py, x0, y0, r1)) {
				if (py == y0) {
					angle = px >= x0 ? 0 : PI;
				}
				else if (px == x0) {
					angle = py > y0 ? 0 : PI + PI / 2;
				}
				else {
					angle = atan((double)(py - y0) / (double)(px - x0));
					if (px < x0)
						angle += PI;
					else if (py < y0)
						angle += 2 * PI;

				}
				if (angle < hudu) {
					putpixel(py - y0 + x0, y0 - px + x0, color);
				}
			}
		}
	}
	FillCircle_B(x0, y0, 20, WHITE);
}

/*抗锯齿画圆画线*/

void SDF_circle(int px, int py, COLORREF color, int r)
{
	for (int i = px - r - 10; i < px + r + 10; i++) {
		for (int j = py - r - 10; j < py + r + 10; j++) {
			int p1x = i;
			int p1y = j;
			double d;
			d = sqrt((pow(p1x - px, 2) + pow(p1y - py, 2))) - r;

			double alpha = 1 - d / 4;
			if (d < 0)
				continue;
			if (alpha >= 0 && alpha <= 1) {
				COLORREF origin = getpixel(i, j);
				//COLORREF result = mix_color(origin, color, alpha);
				COLORREF result = RGB(GetRValue(origin) * (1 - alpha) + GetRValue(color) * alpha, GetGValue(origin) * (1 - alpha) + GetGValue(color) * alpha, GetBValue(origin) * (1 - alpha) + GetBValue(color) * alpha);
				putpixel(i, j, result);
			}
		}
	}
	setfillcolor(color);
	setlinecolor(color);
	fillcircle(px, py, r);
}
//

void FillCircle_B(int x, int y, int r, COLORREF color)
{
	int tx = 0, ty = r, d = 3 - 2 * r, i;
	while (tx < ty)
	{
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			if (tx != 0)
				putpixel(i, y + tx, color);
		}

		if (d < 0)
			d += 4 * tx + 6;
		else
		{

			for (i = x - tx; i <= x + tx; i++)
			{
				putpixel(i, y - ty, color);
				putpixel(i, y + ty, color);
			}

			d += 4 * (tx - ty) + 10, ty--;
		}

		tx++;
	}

	if (tx == ty)
		for (i = x - ty; i <= x + ty; i++)
		{
			putpixel(i, y - tx, color);
			putpixel(i, y + tx, color);
		}
}


void SDFline(int x0, int y0, int x1, int y1, int width, COLORREF color)
{
	if (x0 < x1) {
		SDFline(x1, y1, x0, y0, width, color);
	}
	rgb final, target, origin;
	rgb_split(color, target);
	double k, dy, dx, dxy, dAB;
	if (x0 != x1) {
		k = (double)(y0 - y1) / (x0 - x1);
	}
	else {
		k = K_MAX;
	}
	double k2;
	if (y0 != y1) {
		k2 = -1 / k;
	}
	else {
		k2 = K_MAX;
	}

	point sizemax, sizemin;
	if (x0 < x1)
		sizemin.x = x0;
	else
		sizemin.x = x1;
	if (y0 < y1)
		sizemin.y = y0;
	else
		sizemin.y = y1;
	if (x0 > x1)
		sizemax.x = x0;
	else
		sizemax.x = x1;
	if (y0 > y1)
		sizemax.y = y0;
	else
		sizemax.y = y1;

	sizemax.x += int((width + 1) / 2);
	sizemax.y += int((width + 1) / 2);
	sizemin.x -= int((width + 1) / 2);
	sizemin.y -= int((width + 1) / 2);

	point A, B;
	if (y0 > y1) {
		A.x = x0;
		A.y = y0;
		B.x = x1;
		B.y = y1;
	}
	else {
		A.x = x1;
		A.y = y1;
		B.x = x0;
		B.y = y0;
	}
	int pixelcolor = 0;
	for (int i = sizemin.x; i < sizemax.x; i++) {
		for (int j = sizemin.y; j < sizemax.y; j++) {
			dx = i - A.x;
			dy = k2 * dx;
			if (A.y + dy <= j) {
				dy = j - A.y;
				dxy = sqrt(dx * dx + dy * dy);
			}
			else {
				dx = i - B.x;
				dy = k2 * dx;
				if (B.y + dy >= j) {
					dy = j - B.y;
					dxy = sqrt(dx * dx + dy * dy);
				}
				else {
					dx = (B.x - A.x);
					dy = (B.y - A.y);
					dAB = sqrt(dx * dx + dy * dy);
					dxy = abs((B.y - A.y) * i - (B.x - A.x) * j + B.x * A.y - A.x * B.y) / dAB;
				}
				dxy = dxy - (double)width / 2;
				double alpha = 0.5 - dxy;
				if (alpha >= 0.5 && alpha <= 2.5) {
					alpha = alpha / 2.5;
					pixelcolor = getpixel(i, j);
					rgb_split(pixelcolor, origin);
					finalcolor(final, target, origin, alpha);
					pixelcolor = rgb_sum(final);
					putpixel(i, j, pixelcolor);
				}
				else if (dxy < 0) {
					pixelcolor = rgb_sum(target);
					putpixel(i, j, pixelcolor);
				}

			}
		}
	}
}

void rgb_split(int color, struct rgb& rgbcolor)
{
	rgbcolor.r = color / 65536;
	rgbcolor.g = (color - rgbcolor.r * 65536) / 256;
	rgbcolor.b = color % 256;
}

int rgb_sum(struct rgb color)
{
	return (color.r * 65536 + color.g * 256 + color.b);
}

void finalcolor(struct rgb& final, struct rgb& target, struct rgb& origin, double alpha)
{
	final.r = (short)(origin.r * (1 - alpha) + target.r * alpha);
	final.g = (short)(origin.g * (1 - alpha) + target.g * alpha);
	final.b = (short)(origin.b * (1 - alpha) + target.b * alpha);
}