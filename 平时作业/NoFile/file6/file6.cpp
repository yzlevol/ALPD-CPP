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
        cerr << "��ȷ�����������ȷ" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in) {
        cerr << "�޷��������ļ�" << endl;
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
        cout << "-*�������ļ�����*- ";
        cout << outstr.str();
        string path = argv[1];
        int index1 = path.find_last_of("\\");
        int index2 = path.find_last_of(".txt");
        string floder = path.substr(0, index1+1);
        string file = path.substr(index1 + 1, -1);
        string filename = file.substr(0, file.rfind('.'));
        //cout << filename;
        
        /*"���Ҫ���������λ���õ�һ��"*/
        
        //ofstream out(floder + filename + "_red.txt", ios::out); 
        
		/*"���Ҫ���������λ���õڶ���"*/
		
        ofstream out(filename + "_red.txt", ios::out);
        out << outstr.str();
        in.close();
        out.close();
    }
    /* ��ȡ�ļ������н��� */
    /* ���ݹ����Զ������ļ����������������������:����ļ���������������ļ�������_red*/
    return 0;
}
