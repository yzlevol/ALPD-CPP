#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<vector>
using namespace cv;
using namespace std;

class Matrix //矩阵类
{
private:
    int row, col; //行和列
    int** matx;
public:
    Matrix(int r, int c);
    Matrix(int r, int c, int** init);
    Matrix(int r, int c, uchar **init);
    // 使用二维数组初始化矩阵
    void initialize(int data[][3]) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                matx[i][j] = data[i][j];
            }
        }
    }
    // 析构函数
    ~Matrix() {
        // 释放矩阵内存
        for (int i = 0; i < row; ++i) {
            delete[] matx[i];
        }
        delete[] matx;
    }
    int getrow() {
        return row;
    }
    int getcol() {
        return col;
    }
    uchar** toUcharPtrArray() const {
        uchar** array = new uchar * [row];
        for (int i = 0; i < row; ++i) {
            array[i] = new uchar[col];
            for (int j = 0; j < col; ++j) {
                array[i][j] = static_cast<uchar>(matx[i][j]);
            }
        }
        return array;
    }
    Matrix operator+(const Matrix& x2);
    Matrix operator*(int k);
    Matrix operator/(int k);
    Matrix operator*(Matrix& x2);
    Matrix& operator=(const Matrix& x2);
    int get_sum();
    void check(Mat& img,int sum);
    Matrix Hadamard(const Matrix& x2) const;
    Matrix convolution(const Matrix& b) const;
    friend Matrix trans(const Matrix& a);
    friend istream& operator>>(istream& in, Matrix& x);
    friend ostream& operator<<(ostream& out, Matrix& x);
};
Matrix::Matrix(int r, int c) :row(r), col(c)
{
    matx = new int* [row];
    for (int i = 0; i < row; ++i)
        matx[i] = new int[col];
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            matx[i][j] = 0;
}
Matrix::Matrix(int r, int c, uchar** init)
{
    row = r;
    col = c;
    matx = new int* [row];
    for (int i = 0; i < row; ++i)
        matx[i] = new int[col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matx[i][j] = (int)init[i][j]; // 使用初始矩阵的对应元素进行初始化
        }
    }
}
Matrix::Matrix(int r, int c, int** init)
{
    row = r;
    col = c;
    matx = new int* [row];
    for (int i = 0; i < row; ++i)
        matx[i] = new int[col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matx[i][j] = init[i][j]; // 使用初始矩阵的对应元素进行初始化
        }
    }
}

Matrix& Matrix::operator=(const Matrix& x2)
{
    row = x2.row;
    col = x2.col;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matx[i][j] = x2.matx[i][j];
        }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& x2)
{
    Matrix tmp(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tmp.matx[i][j] = matx[i][j] + x2.matx[i][j];
        }
    }
    return tmp;
}
Matrix Matrix::operator*(int k)
{
    Matrix tmp(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tmp.matx[i][j] = matx[i][j] * k;
        }
    }
    return tmp;
}
Matrix Matrix::operator/(int k)
{
    Matrix tmp(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tmp.matx[i][j] = matx[i][j] / k;
        }
    }
    return tmp;
}
Matrix Matrix::operator*(Matrix& x2)
{
    Matrix result(row, x2.col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < x2.col; ++j) {
            result.matx[i][j] = 0;
            for (int k = 0; k < col; ++k) {
                result.matx[i][j] += matx[i][k] * x2.matx[k][j];
            }
        }
    }
    return result;
}
Matrix Matrix::Hadamard(const Matrix& x2) const
{
    Matrix tmp(row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            tmp.matx[i][j] = matx[i][j] * x2.matx[i][j];
        }
    }
    return tmp;
}
Matrix Matrix::convolution(const Matrix& b) const {
    int bRows = 3;
    int bCols = 3;
    int outRows = row;
    int outCols = col;
    Matrix result(outRows, outCols);

    int paddedRows = row + 2;
    int paddedCols = col + 2;
    Matrix paddedMatrix(paddedRows, paddedCols);
    // 在矩阵A的外围填充0
    for (int i = 0; i < paddedRows; ++i) {
        for (int j = 0; j < paddedCols; ++j) {
            if (i == 0 || i == paddedRows - 1 || j == 0 || j == paddedCols - 1) {
                paddedMatrix.matx[i][j] = 0;
            }
            else {
                paddedMatrix.matx[i][j] = matx[i - 1][j - 1];
            }
        }
    }
    //卷积操作
    for (int i = 0; i < outRows; ++i) {
        for (int j = 0; j < outCols; ++j) {
            int sum = 0;
            for (int k = 0; k < bRows; ++k) {
                for (int m = 0; m < bCols; ++m) {
                    sum += paddedMatrix.matx[i + k][j + m] * b.matx[k][m];
                }
            }
            result.matx[i][j] = sum;
        }
    }
    return result;
}

istream& operator>>(istream& in, Matrix& x)
{
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < x.col; j++) {
            in >> x.matx[i][j];
        }
    }
    return in;
}
ostream& operator<<(ostream& out, Matrix& x)
{
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < x.col; j++) {
            out << x.matx[i][j] << " ";
        }
        out << endl;
    }
    return out;
}


int Matrix::get_sum() 
{
    int sum = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j) {
            sum += matx[i][j];
        }
    }
    return sum;
}
void Matrix::check(Mat &img,int sum)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j) {
            matx[i][j] /= sum;
            if (matx[i][j] < 0)
                matx[i][j] = 0;
            if (matx[i][j] > 255)
                matx[i][j] = 255;
            img.at<uchar>(i, j) = matx[i][j];
        }
    }
}

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
    cin.clear();
    cin.ignore(1024, '\n');
}

uchar** Mat2Vec(Mat mat)
{

    uchar** array = new uchar * [mat.rows];
    for (int i = 0; i < mat.rows; ++i)
        array[i] = new uchar[mat.cols];
    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {

            array[i][j] = mat.at<uchar>(i, 3*j);
            if (mat.at<uchar>(i, 3 * j) < 0) {
                array[i][j] = 0;
            }
            if (mat.at<uchar>(i, 3 * j) > 255) {
                array[i][j] = 255;
            }
        }
    }

    return array;
}
Mat Vector2Mat(vector<vector<int>>& imageVec)
{
    int numRows = (int)imageVec.size();
    int numCols = (int)imageVec[0].size();

    Mat imageMat(numRows, numCols, CV_8UC1);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            imageMat.at<uchar>(i, j) = static_cast<uchar>(imageVec[i][j]);
        }
    }

    return imageMat;
}
cv::Mat Vec2Mat(uchar** imageData, int numRows, int numCols)
{
    cv::Mat imageMat(numRows, numCols, CV_8UC1);

    for (int i = 0; i < numRows; i++) {
        uchar* rowPtr = imageMat.ptr<uchar>(i);
        for (int j = 0; j < numCols; j++) {
            rowPtr[j] = imageData[i][j];
        }
    }

    return imageMat;
}

char menu()
{
    cout << "********************************************************" << endl;
    cout << " *      1 矩阵加法      2 矩阵数乘      3 矩阵转置    *" << endl;
    cout << " *      4 矩阵乘法      5 Hadamard乘积  6 矩阵卷积    *" << endl;
    cout << " *      7 卷积应用      8 OTSU 算法     0 退出系统    *" << endl;
    cout << "********************************************************" << endl;
    char menu;
    while (1) {
        menu = _getch();
        if (menu >= '0' && menu <= '8') {
            break;
        }
        else {
            cout << "输入错误" << endl;
            getchar();
            continue;
        }
    }
    system("cls");
    return menu;
}
void matriplus()
{
    int row, col;
    cout << "请输入矩阵A的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵A的数据:" << endl;
    cin >> a;
    cout << "矩阵A为:" << endl;
    cout << a;
    int row2, col2;
    cout << "请输入矩阵B的行和列数:" << endl;
    cin >> row2 >> col2;
    if (row != row2 || col != col2)
    {
        cout << "矩阵行和列不匹配，无法加和" << endl;
        return;
    }
    else {
        Matrix b(row, col);
        cout << "请输入矩阵B的数据:" << endl;
        cin >> b;
        cout << "矩阵B为:" << endl;
        cout << b;
        Matrix c(row, col);
        c = a + b;
        cout << "矩阵A+B的和为:" << endl;
        cout << c;
    }
}
void nummulti()
{
    int row, col;
    cout << "请输入矩阵的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵的数据:" << endl;
    cin >> a;
    cout << "矩阵为:" << endl;
    cout << a;
    int k;
    cout << "请输入要数乘的整数k" << endl;
    cin >> k;
    a = a * k;
    cout << "数乘 " << k << " 后,矩阵为:" << endl;
    cout << a;
}
Matrix trans(const Matrix& a)
{
    Matrix a2(a.col, a.row);
    for (int i = 0; i < a.row; ++i) {
        for (int j = 0; j < a.col; j++) {
            a2.matx[j][i] = a.matx[i][j];
        }
    }
    return a2;
}
void matritrans()
{
    int row, col;
    cout << "请输入矩阵的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵的数据:" << endl;
    cin >> a;
    cout << "矩阵为:" << endl;
    cout << a;
    Matrix a2(col, row);
    cout << "矩阵转置后为:" << endl;
    a2 = trans(a);
    cout << a2;
}
void matrimulti()
{
    int row, col;
    cout << "请输入矩阵A的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵A的数据:" << endl;
    cin >> a;
    cout << "矩阵A为:" << endl;
    cout << a;
    int row2, col2;
    cout << "请输入矩阵B的行和列数:" << endl;
    cin >> row2 >> col2;


    //判断是否可以做乘法
    if (col!=row2) {
        cout << "行和列不匹配，无法进行矩阵乘法" << endl;
        return;
    }
    else {
        Matrix b(row2, col2);
        cout << "请输入矩阵B的数据:" << endl;
        cin >> b;
        cout << "矩阵B为:" << endl;
        cout << b;
        Matrix c(row, col2);
        c = a * b;
        cout << "矩阵A和B的乘积为:" << endl;
        cout << c;
    }
}
void hadamulti()
{
    int row, col;
    cout << "请输入矩阵A的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵A的数据:" << endl;
    cin >> a;
    cout << "矩阵A为:" << endl;
    cout << a;
    int row2, col2;
    cout << "请输入矩阵B的行和列数:" << endl;
    cin >> row2 >> col2;
    if(row!=row2||col!=col2)
    {
        cout << "矩阵行和列不匹配，无法做Hadamard乘积" << endl;
        return;
    }
    else {
        Matrix b(row2, col2);
        cout << "请输入矩阵B的数据:" << endl;
        cin >> b;
        cout << "矩阵B为:" << endl;
        cout << b;
        Matrix c(row, col);
        c = a.Hadamard(b);
        cout << "矩阵A+B的Hadamard乘积为:" << endl;
        cout << c;
    }

}
void conv(Matrix& b) //传入卷积核
{
    int row, col;
    cout << "请输入矩阵A的行和列数:" << endl;
    cin >> row >> col;
    Matrix a(row, col);
    cout << "请输入矩阵A的数据:" << endl;
    cin >> a;
    cout << "矩阵A为:" << endl;
    cout << a;
    Matrix result(row,col);
    result = a.convolution(b);
    cout << "卷积结果为:" << endl;
    cout << result << endl;
    cout << result.getrow() << "行 " << result.getcol()<<"列 " << endl;
}
void demo()
{

    int init1[3][3] = { {1,1,1},
                      { 1,1,1},
                      { 1,1,1} };
    Matrix B1(3, 3);
    B1.initialize(init1);
    int init2[3][3] = { {-1,-2,-1},
                  { 0,0,0},
                  { 1,2,1} };
    Matrix B2(3, 3);
    B2.initialize(init2);
    int init3[3][3] = { {-1,0,1},
                  { -2,0,2},
                  { -1,0,1} };
    Matrix B3(3, 3);
    B3.initialize(init3);
    int init4[3][3] = { {-1,-1,-1},
                  { -1,9,-1},
                  { -1,-1,-1} };
    Matrix B4(3, 3);
    B4.initialize(init4);
    int init5[3][3] = { {-1,-1,0},
                  { -1,0,1},
                  { 0,1,1} };
    Matrix B5(3, 3);
    B5.initialize(init5);
    int init6[3][3] = { {1,2,1},
                  { 2,4,2},
                  { 1,2,1} };
    Matrix B6(3, 3);
    B6.initialize(init6);
     Mat image =
         imread("demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
     int sum = 0;
     Matrix a(image.rows, image.cols, Mat2Vec(image));
     Matrix c1(image.rows, image.cols);
     c1 = a.convolution(B1);
     sum = B1.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img1(image.rows, image.cols, CV_8UC1);
     c1.check(img1,sum);
     imshow("B1", img1);
     cv::moveWindow("B1", 300, 150);

     Matrix c2(image.rows, image.cols);
     c2 = a.convolution(B2);
     sum = B2.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img2(image.rows, image.cols, CV_8UC1);
     c2.check(img2,sum);
     imshow("B2", img2);
     cv::moveWindow("B2", 600, 150);

     Matrix c3(image.rows, image.cols);
     c3 = a.convolution(B3);
     sum = B3.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img3(image.rows, image.cols, CV_8UC1);
     c3.check(img3,sum);
     imshow("B3", img3);
     cv::moveWindow("B3", 900, 150);

     Matrix c4(image.rows, image.cols);
     c4 = a.convolution(B4);
     sum = B4.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img4(image.rows, image.cols, CV_8UC1);
     c4.check(img4,sum);
     imshow("B4", img4);
     cv::moveWindow("B4", 300, 450);

     Matrix c5(image.rows, image.cols);
     c5 = a.convolution(B5);
     sum = B5.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img5(image.rows, image.cols, CV_8UC1);
     c5.check(img5,sum);
     imshow("B5", img5);
     cv::moveWindow("B5", 600, 450);

     Matrix c6(image.rows, image.cols);
     c6 = a.convolution(B6);
     sum = B6.get_sum();
     if (sum == 0)
         sum = 1;
     Mat img6(image.rows, image.cols, CV_8UC1);
     c6.check(img6,sum);
     imshow("B6", img6);
     cv::moveWindow("B6", 900, 450);
     waitKey(0);
     return;
}

/* 有问题，阈值计算不对
double calculateVariance(const std::vector<int>& histogram, int threshold)
{
    int totalPixels = 0;
    int sum = 0;
    for (int i = 0; i <= threshold; i++)
    {
        totalPixels += histogram[i];
        sum += i * histogram[i];
    }
    if (totalPixels == 0)
        return 0;
    double mean1 = sum / static_cast<double>(totalPixels);

    int totalPixels2 = 0;
    int sum2 = 0;
    for (int i = threshold + 1; i < histogram.size(); i++)
    {
        totalPixels2 += histogram[i];
        sum2 += i * histogram[i];
    }
    if (totalPixels2 == 0)
        return 0;
    double mean2 = sum2 / static_cast<double>(totalPixels2);

    double variance1 = 0.0;
    double variance2 = 0.0;

    for (int i = 0; i <= threshold; i++)
    {
        double diff = i - mean1;
        variance1 += diff * diff * histogram[i];
    }
    variance1 /= (totalPixels + totalPixels2);

    for (int i = threshold + 1; i < histogram.size(); i++)
    {
        double diff = i - mean2;
        variance2 += diff * diff * histogram[i];
    }
    variance2 /= (totalPixels + totalPixels2);

    return variance1 + variance2;
}

void OSTUbin(const vector<int>& histogram, int& bestThreshold, double& bestVariance)// OTSU二值化
{
    int totalPixels = 0;
    for (int i = 0; i < 256; ++i)
    {
        totalPixels += histogram[i];
    }
    bestThreshold = 0; //最佳阈值
    bestVariance = 0.0;//最佳方差
    for (int threshold = 0; threshold < 256; ++threshold)
    {
        double variance = calculateVariance(histogram, threshold);
        //cout << variance <<"@@" << endl;
        if (variance > bestVariance) {
            bestVariance = variance;
            bestThreshold = threshold;
            cout <<"最好阈值"<< bestThreshold << endl;
        }
    }
}
*/  

void binImg(const vector<vector<int>>& image, vector<vector<int>>& binImage, int threshold)
{
    int row_img = (int)image.size();
    int col_img = (int)image[0].size();
    //调整二值化图像大小
    binImage.resize(row_img, std::vector<int>(col_img, 0));
    //根据阈值将图像像素点二值化
    for (int i = 0; i < row_img; ++i) {
        for (int j = 0; j < col_img; ++j) {
            if (image[i][j] >= threshold) {
                binImage[i][j] = 255;
            }
            else
                binImage[i][j] = 0;
        }
    }
}
void OSTUCUT(uchar** originImage,const vector<vector<int>>& image, vector<vector<int>>& binImage, int threshold)
{
    int row_img = (int)image.size();
    int col_img = (int)image[0].size();
    binImage.resize(row_img, std::vector<int>(col_img, 0));
    for (int i = 0; i < row_img; ++i) {
        for (int j = 0; j < col_img; ++j) {
            if (image[i][j] >= threshold) {
                binImage[i][j] = originImage[i][j];
            }
            else
                binImage[i][j] = 0;
        }
    }
}
int BestThreshold(const std::vector<int>& histogram)//计算最佳阈值
{
    int totalPixels = 0;
    for (int i = 0; i < histogram.size(); ++i)
    {
        totalPixels += histogram[i];
    }

    float sumWeight = 0.0f;
    for (int i = 0; i < histogram.size(); ++i)
    {
        sumWeight += i * histogram[i];
    }

    int sumB = 0;
    int weightBK = 0;
    int weightFG = 0;

    float bestVariance = 0.0f;
    int threshold = 0;

    for (int i = 0; i < histogram.size(); ++i)
    {
        weightBK += histogram[i];     
        if (weightBK == 0) continue;

        weightFG = totalPixels - weightBK;    
        if (weightFG == 0) break;

        sumB += i * histogram[i];

        float averageBK = static_cast<float>(sumB) / weightBK;             
        float averageFG = static_cast<float>(sumWeight - sumB) / weightFG; 

        float varBetween = static_cast<float>(weightBK) * static_cast<float>(weightFG) * (averageBK - averageFG) * (averageBK - averageFG);

        if (varBetween > bestVariance)
        {
            bestVariance = varBetween;
            threshold = i;
        }
    }

    return threshold;
}

void OTSU(Mat imageMat,int choice) //choice==1二值化  //choice==2截取图像
{
    vector<vector<int>> image;
    int numRows = imageMat.rows;
    int numCols = imageMat.cols;
    imshow("Ori", imageMat);
    uchar** imageVec=Mat2Vec(imageMat);
    for (int i = 0; i < numRows; i++) {
        std::vector<int> rowVector;
        for (int j = 0; j < numCols; j++) {
            rowVector.push_back(imageVec[i][j]); // 将每个像素值添加到行向量中
        }
        image.push_back(rowVector); // 将每一行的向量添加到图像向量中
    }
    vector<int> histogram(256, 0);
    for (int i = 0; i < image.size(); i++) {
        const std::vector<int>& row = image[i];
        for (int j = 0; j < row.size(); j++) {
            int pixel = row[j];
            histogram[pixel]++;
        }
    }
    //OTSU二值化
    int bestThreshold = 0;
    double bestVariance = 0.0;
    bestThreshold = BestThreshold(histogram);
    //bestThreshold = 100;
    //图像二值化 
    vector<vector<int>> binImage;
    if (choice == 1) {
        binImg(image, binImage, bestThreshold);
        imshow("OTSU二值化", Vector2Mat(binImage));
        cv::moveWindow("OTSU二值化", 500, 250);
    }
    if (choice == 2) {
        OSTUCUT(imageVec, image, binImage, bestThreshold);
        imshow("OTSU截取主体", Vector2Mat(binImage));
        cv::moveWindow("OTSU截取主体", 500, 250);
    }
    waitKey(0);
}
void show_otsu()
{
    Mat image1 =
        imread("demolena.jpg");
    cout << "Choice=1,下面演示利用OTSU算法二值化lena图像" << endl;
    OTSU(image1,1); //二值化lena
    Mat image2 =
        imread("brain.jpg",1);
    cout << "Choice=2,下面演示利用OTSU算法截取brain图像" << endl;
    OTSU(image2,2); //截取
    Mat image3 =
        imread("ship.jpg",1);
    cout << "Choice=2,下面演示利用OTSU算法截取ship图像" << endl;
    OTSU(image3,2); //截取
    Mat image4 =
        imread("polyhedrosis.jpg",1);
    cout << "Choice=2,下面演示利用OTSU算法截取polyhedrosis图像" << endl;
    OTSU(image4,2); //截取
    Mat image5 =
        imread("snowball.jpg",1);
    cout << "Choice=2,下面演示利用OTSU算法截取snowball图像" << endl;
    OTSU(image5,2); //截取
    waitKey(0);
}

int main()
{
    // 定义相关变量
    char choice = 0;
    char ch = 0;
    int init[3][3] = {{-1,0,1},
                      { -1,0,1},
                      { -1,0,1} };
    Matrix B0(3, 3);
    B0.initialize(init);
    while (true) 
    {
        system("cls"); 
        choice = menu(); 
        if (choice == '0') // 选择退出
        {
            cout << "\n 确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

    switch (choice)
        {
            case '1':
                matriplus();
                wait_for_enter();
                break;
            case '2':
                nummulti();
                wait_for_enter();
                break;
            case '3':
                matritrans();
                wait_for_enter();
                break;
            case '4':
                matrimulti();
                wait_for_enter();
                break;
            case '5':
                hadamulti();
                wait_for_enter();
                break;
            case '6':
                conv(B0);
                wait_for_enter();
                break;
            case '7':
                demo();
                wait_for_enter();
                break;
            case'8':
                show_otsu();
                break;
            default:
                cout << "\n 输入错误，请从新输入" << endl;
                wait_for_enter();
        }
    }
    return 0;
}