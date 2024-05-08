#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<istream>
using namespace std;

void readFromStdin(int a[20])
{
    for (int i = 0; i < 10; i++) {
        cin >> a[i];
    }
}
void readFromFile(int a[20])
{
    FILE* fp = fopen("1.txt", "r");
    for (int j = 10; j < 20; j++) {
        fscanf(fp, "%d", &a[j]);
        fscanf(fp," ");
    }
    fclose(fp);
}
void sort(int a[20])
{
    for (int i = 0; i < 20-1; i++) {
        for (int j = 0; j < 20 - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void outToFile(int a[20])
{
    FILE* fpout = fopen("1.out", "w");
    for (int i = 0; i < 20; i++) {
        fprintf(fpout, "%d ", a[i]);
    }
    fclose(fpout);
}

int main()
{
    int a[20] = { 0 };
    readFromStdin(a);
    readFromFile(a);
    sort(a);
    outToFile(a);
    cout << "----³ÌÐò½áÊø----" << endl;
    return 0;
}