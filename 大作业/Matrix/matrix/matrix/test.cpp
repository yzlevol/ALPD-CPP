#include <iostream>
#include <vector>
#include <cmath>

// 计算OSTU算法的最佳阈值
int calculateOSTUThreshold(const std::vector<int>& histogram) {
    int totalPixels = 0;
    for (int pixelCount : histogram) {
        totalPixels += pixelCount;
    }

    int bestThreshold = 0;
    double bestVariance = 0.0;

    for (int t = 0; t < 256; ++t) {
        int n1 = 0; // 类1的像素数
        int n2 = 0; // 类2的像素数
        int sum1 = 0; // 类1的灰度值总和
        int sum2 = 0; // 类2的灰度值总和

        for (int i = 0; i <= t; ++i) {
            n1 += histogram[i];
            sum1 += i * histogram[i];
        }

        for (int i = t + 1; i < 256; ++i) {
            n2 += histogram[i];
            sum2 += i * histogram[i];
        }

        if (n1 == 0 || n2 == 0) {
            continue; // 跳过可能导致除以零的情况
        }

        // 类1和类2的概率分布
        double w1 = static_cast<double>(n1) / totalPixels;
        double w2 = static_cast<double>(n2) / totalPixels;

        // 类1和类2的平均灰度值
        double mean1 = static_cast<double>(sum1) / n1;
        double mean2 = static_cast<double>(sum2) / n2;

        // 类1和类2的方差
        double variance1 = 0.0;
        double variance2 = 0.0;

        for (int i = 0; i <= t; ++i) {
            variance1 += (i - mean1) * (i - mean1) * histogram[i];
        }

        for (int i = t + 1; i < 256; ++i) {
            variance2 += (i - mean2) * (i - mean2) * histogram[i];
        }

        variance1 /= n1;
        variance2 /= n2;

        // 类间方差
        double betweenClassVariance = w1 * variance1 + w2 * variance2;

        if (betweenClassVariance > bestVariance) {
            bestVariance = betweenClassVariance;
            bestThreshold = t;
        }
    }

    return bestThreshold;
}

int main() {
    // 假设有一个包含256个灰度级别的直方图
    std::vector<int> histogram(256, 0);
    // 填充直方图，这里仅为示例
    for(int i=0;i<histogram.size();++i)
    {
    	if(i<128)
    		histogram[i]=i*2;
    	else
    		histogram[i]=(256-i);
	}

    int threshold = calculateOSTUThreshold(histogram);
    std::cout << "Best threshold: " << threshold << std::endl;

    return 0;
}



