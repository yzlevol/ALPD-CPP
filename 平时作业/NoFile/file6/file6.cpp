#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

//string remove_noise(string)
//{
//
//}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "请确保输入参数正确" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }
    else {
        ostringstream outstr;
        string eveline;
        int line = 0;
        while (!in.eof()) {
            getline(in, eveline);
            line++;
            int i = 0;
            int yu = (line == 1) ? 0 : 2;
            for (char c : eveline) {
                if (i % 3 == yu) {
                    outstr << c;
                }
                i++;
            }
        }
        cout << "-*以下是文件内容*- ";
        cout << outstr.str();
        string path = argv[1];
        int index1 = path.find_last_of("\\");
        int index2 = path.find_last_of(".txt");
        string floder = path.substr(0, index1+1);
        string file = path.substr(index1 + 1, -1);
        string filename = file.substr(0, file.rfind('.'));
        //cout << filename;
        
        /*"如果要输出到绝对位置用第一个"*/
        
        //ofstream out(floder + filename + "_red.txt", ios::out); 
        
		/*"如果要输出到绝对位置用第二个"*/
		
        ofstream out(filename + "_red.txt", ios::out);
        out << outstr.str();
        in.close();
        out.close();
    }
    /* 读取文件并进行降噪 */
    /* 根据规则自动补充文件名并进行输出，规则如下:输出文件的名称是输入的文件名加上_red*/
    return 0;
}
