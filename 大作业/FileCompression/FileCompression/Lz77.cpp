#include"FileHead.h"

const int LZ77_WINDOW = 1024;
vector<char>window_of_lz77;
const int LZ77_ZOOM = 100;
vector<char> zoom_of_lz77;

const int WINDOW_for_delz77 = 1024;

int prgs = 0;
int getlen(int win, int zo)
{
	int len = 0;
	int p_win = win;
	int p_zoom = zo;
	while (1)
	{
		if (window_of_lz77[p_win] == zoom_of_lz77[p_zoom])
		{
			p_win++;
			p_zoom++;
			len++;
			if (p_win == window_of_lz77.size() || p_zoom == zoom_of_lz77.size()) {
				return len;
			}
		}
		else
			return len;
	}
}

int get_size(fstream& ff)
{
	ff.seekg(0, ios::end);
	return ff.tellg();
}
void log_lz77(const char inn[], const char outt[],int size0)
{
	fstream infp, outfp;
	char tmp;
	int p_win, p_zoom;
	bool flag = true;
	int len = 0, lenmax , leni;
	char buff1;
	short buff2;
	//文件打开
	infp.open(inn, ios::in | ios::binary);
	if (!infp.is_open()) {
		cerr << "文件打开失败!程序退出" << endl;
		exit(-1);
	}
	outfp.open(outt, ios::out | ios::binary);
	if (!outfp.is_open()) {
		cerr << "文件打开失败!程序退出" << endl;
		exit(-1);
	}

	for (int i = 0; i < LZ77_ZOOM; ++i) {
		infp >> noskipws >> tmp;
		zoom_of_lz77.push_back(tmp);
	}
	for (int i = 0; i < LZ77_WINDOW; ++i) {
		window_of_lz77.push_back('\0');
	}
	while(1)
	{
		if (zoom_of_lz77.empty())
			break;
		lenmax = -1;
		p_zoom = 0;
		p_win = 0;
		for (int i = 0; i < LZ77_WINDOW; ++i) {
			if (window_of_lz77[i] == zoom_of_lz77[0]) {
				len = getlen(i, 0);
				if (len > lenmax) {
					lenmax = len;
					leni = i;
				}
			}
		}
		if (lenmax <= 3) {
			buff1 = '0';
			outfp.write((char*)&buff1, sizeof(buff1));
			buff1 = zoom_of_lz77[0];
			outfp.write((char*)&buff1, sizeof(buff1));
			window_of_lz77.erase(window_of_lz77.begin());
			window_of_lz77.push_back(zoom_of_lz77[0]);
			zoom_of_lz77.erase(zoom_of_lz77.begin());
			if (zoom_of_lz77.empty())
				break;
			if (flag) {
				infp >> noskipws >> tmp;
				zoom_of_lz77.push_back(tmp);
			}
			if (infp.eof()) {
				flag = false;
			}
		}
		else {
			buff1 = '1';
			outfp.write((char*)&buff1, sizeof(buff1));
			buff2 = leni;
			outfp.write((char*)&buff2, sizeof(buff2));
			buff2 = lenmax;
			outfp.write((char*)&buff2, sizeof(buff2));
			for (int j = 0; j < lenmax; ++j)
			{
				window_of_lz77.erase(window_of_lz77.begin());
				window_of_lz77.push_back(zoom_of_lz77[0]);
				zoom_of_lz77.erase(zoom_of_lz77.begin());
				if (zoom_of_lz77.empty())
					break;
				if (flag) {
					infp >> noskipws >> tmp;
					zoom_of_lz77.push_back(tmp);
				}
				if (infp.eof())
					flag = false;
			}
			buff1 = zoom_of_lz77[0];
			outfp.write((char*)&buff1, sizeof(buff1));
			window_of_lz77.erase(window_of_lz77.begin());
			window_of_lz77.push_back(zoom_of_lz77[0]);
			zoom_of_lz77.erase(zoom_of_lz77.begin());
			if (zoom_of_lz77.empty())
				break;
			if (flag) {
				infp >> noskipws >> tmp;
				zoom_of_lz77.push_back(tmp);
			}
			if (infp.eof())
				flag = false;
		}
	}
	infp.close();
	outfp.close();
}



vector <char> window_for_delz77;
void decompressLZ77(const char inn[], const char outt[]) {
	ifstream fin(inn, ios::binary);
	ofstream fout(outt, ios::binary);
	if (!fin.is_open()) {
		cerr << "无法打开输入文件！" << endl;
		exit(-1);
	}
	if (!fout.is_open()) {
		cerr << "无法打开输出文件！" << endl;
		exit(-1);
	}

	vector<char> window(WINDOW_for_delz77, '\0');

	while (!fin.eof()) {
		char flag;
		fin.read((char*)&flag, sizeof(flag));
		if (fin.eof()) {
			break;
		}
		if (flag == '0') {
			char ch;
			fin.read((char*)&ch, sizeof(ch));
			fout.write((char*)&ch, sizeof(ch));
			window.erase(window.begin());
			window.push_back(ch);
		}
		else {
			short offset;
			short length;
			fin.read((char*)&offset, sizeof(offset));
			fin.read((char*)&length, sizeof(length));
			for (int i = 0; i < length; i++) {
				char ch = window[offset];
				fout.write((char*)&ch, sizeof(ch));
				window.erase(window.begin());
				window.push_back(ch);
			}
			char ch;
			fin.read((char*)&ch, sizeof(ch));
			fout.write((char*)&ch, sizeof(ch));
			window.erase(window.begin());
			window.push_back(ch);
		}
	}

	fin.close();
	fout.close();
}
