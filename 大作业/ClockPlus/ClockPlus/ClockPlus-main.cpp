#include"ClockPlus.h"

int main()
{
	struct tm t;
	struct tm tlast;
	time_t now;
	time_t last;
	time(&now); //时间戳
	last = now;
	localtime_s(&t, &now); //当地时
	tlast = t;
	init();
	draw_pan();
	int angle = 0;
	int k = 0;

	setfillcolor(HSLtoRGB(152, 0.11f, 0.87f));
	FillCircle_B(circle_x + 550 - 150 + 100, circle_y - 100 + 50 - 20 - 80, 58, HSLtoRGB(152, 0.11f, 0.87f));
	FillCircle_B(circle_x + 500 - 150 - 20, circle_y + 50 + 20 + 50, 58, HSLtoRGB(152, 0.11f, 0.87f));
	FillCircle_B(circle_x + 600 - 150 + 20 + 200, circle_y + 50 + 20 + 50, 58, HSLtoRGB(152, 0.11f, 0.87f));


	SDFline(circle_x + 550 - 150 + 100, circle_y - 100 + 50 - 20 - 80, circle_x + 500 - 150 - 20, circle_y + 50 + 20 + 50, 15, WHITE);
	SDFline(circle_x + 550 - 150 + 100, circle_y - 100 + 50 - 20 - 80, circle_x + 600 - 150 + 20 + 200, circle_y + 50 + 20 + 50, 15, WHITE);
	SDFline(circle_x + 600 - 150 + 20 + 200, circle_y + 50 + 20 + 50, circle_x + 500 - 150 - 20, circle_y + 50 + 20 + 50, 15, WHITE);

	int angle2 = 0;
	while (!_kbhit())
	{

		if (k % 250 == 0) {
			int r = rand() % 256;
			pic(circle_x + 500, circle_y + 24, angle2 - 1, HSLtoRGB(213, 0.63f, 0.96f));
			pic(circle_x + 500, circle_y + 24, ++angle2, HSLtoRGB(float(r), 0.90f, 0.60f));


			if (angle2 >= (INT_MAX - 100000)) {
				angle2 = 0;
			}
		}
		k++;
		if (k >= (INT_MAX - 100000)) {
			k = 1;
		}

		time(&now);
		if (now > last) { //判断时间戳
			tlast = t;
			last = now;
			localtime_s(&t, &now);
			cout << "时间戳:" << now << " 当前时间: " << t.tm_hour << "时" << t.tm_min << "分" << t.tm_sec << "秒" << endl;
			check(t);
			draw_time(t, tlast);
			FillCircle_B(circle_x, circle_y, 10, BROWN);
		}
		else {
			continue;
		}
	}
	_getch();
	closegraph();
	end();
	return 0;
}

