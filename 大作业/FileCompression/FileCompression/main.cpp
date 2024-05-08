#include"FileHead.h"

int main(int argc, char* argv[]) {
	cout << "+----------------------------------------------------------------------------------+" << endl;
	cout << "|                                                                                  |" << endl;
	cout << "|                           Huffman��ѹ��С����V1.0            Author : @Root      |" << endl;
	cout << "|                                                                                  |" << endl;
	cout << "|                    Usage: exe fileIN fileOUT [zip]|[unzip]                       |" << endl;
	cout << "+----------------------------------------------------------------------------------+" << endl;
	clock_t ta, tb;
	int size0, size1;
	double t;
	if (argc != 4) {
		std::cerr << "�÷�˵��: " << argv[0] << " <�����ļ�> <����ļ�> [zip|unzip]" << std::endl;
		return 1;
	}

	if (strcmp(argv[3], "zip")==0) {
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffmanѹ����ʼ *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		ta = clock();
		size0 = getfilesize(argv[1]);
		size1 = huffman_compress(argv[1], argv[2],size0);
		tb = clock();
		cout << endl << endl;
		cout << "ԭʼ�ļ���СΪ��" << setw(10) << setiosflags(ios::right) << size0 << "�ֽ�" << endl;
		cout << "ѹ���ļ���СΪ��" << setw(10) << setiosflags(ios::right) << size1 << "�ֽ�" << endl;
		cout << "�ļ�ѹ������Ϊ��" << setw(11) << setiosflags(ios::right) << 100.00 * size1 / (double)size0 << "%" << endl;
		cout << "ѹ����ʱ: " << setw(16) << setiosflags(ios::right) << (t = ((double)tb - (double)ta)) / CLOCKS_PER_SEC << "��" << endl << endl;
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffmanѹ���ɹ� *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	}
	else if (strcmp(argv[3], "unzip")==0) {
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman��ѹ��ʼ *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		ta = clock();
		huffman_decompress(argv[1], argv[2]);
		tb = clock();	
		size0 = getfilesize(argv[1]);
		size1 = getfilesize(argv[2]);
		cout << endl <<endl << "ѹ���ļ���СΪ��" << setw(10) << setiosflags(ios::right) << size0 << "�ֽ�" << endl;
		cout << "��ѹ�ļ���СΪ��" << setw(10) << setiosflags(ios::right) << size1 << "�ֽ�" << endl;
		cout << "��ѹ��ʱ: " << setw(16) << setiosflags(ios::right) << (t = ((double)tb - (double)ta)) / CLOCKS_PER_SEC << "��" << endl << endl;
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman��ѹ��� *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	}
	else {
		std::cerr << "�Ƿ��÷�: " << argv[3] << std::endl;
		std::cerr << "�÷�˵��: " << argv[0] << " <�����ļ�> <����ļ�> [zip|unzip]" << std::endl;
		return 1;
	}

	return 0;
}

