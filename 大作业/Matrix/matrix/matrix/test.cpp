#include <iostream>
#include <vector>
#include <cmath>

// ����OSTU�㷨�������ֵ
int calculateOSTUThreshold(const std::vector<int>& histogram) {
    int totalPixels = 0;
    for (int pixelCount : histogram) {
        totalPixels += pixelCount;
    }

    int bestThreshold = 0;
    double bestVariance = 0.0;

    for (int t = 0; t < 256; ++t) {
        int n1 = 0; // ��1��������
        int n2 = 0; // ��2��������
        int sum1 = 0; // ��1�ĻҶ�ֵ�ܺ�
        int sum2 = 0; // ��2�ĻҶ�ֵ�ܺ�

        for (int i = 0; i <= t; ++i) {
            n1 += histogram[i];
            sum1 += i * histogram[i];
        }

        for (int i = t + 1; i < 256; ++i) {
            n2 += histogram[i];
            sum2 += i * histogram[i];
        }

        if (n1 == 0 || n2 == 0) {
            continue; // �������ܵ��³���������
        }

        // ��1����2�ĸ��ʷֲ�
        double w1 = static_cast<double>(n1) / totalPixels;
        double w2 = static_cast<double>(n2) / totalPixels;

        // ��1����2��ƽ���Ҷ�ֵ
        double mean1 = static_cast<double>(sum1) / n1;
        double mean2 = static_cast<double>(sum2) / n2;

        // ��1����2�ķ���
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

        // ��䷽��
        double betweenClassVariance = w1 * variance1 + w2 * variance2;

        if (betweenClassVariance > bestVariance) {
            bestVariance = betweenClassVariance;
            bestThreshold = t;
        }
    }

    return bestThreshold;
}

int main() {
    // ������һ������256���Ҷȼ����ֱ��ͼ
    std::vector<int> histogram(256, 0);
    // ���ֱ��ͼ�������Ϊʾ��
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



