#include"FileHead.h"

int main(int argc, char* argv[]) {
	cout << "+----------------------------------------------------------------------------------+" << endl;
	cout << "|                                                                                  |" << endl;
	cout << "|                           Huffman解压缩小程序V1.0            Author : @Root      |" << endl;
	cout << "|                                                                                  |" << endl;
	cout << "|                    Usage: exe fileIN fileOUT [zip]|[unzip]                       |" << endl;
	cout << "+----------------------------------------------------------------------------------+" << endl;
	clock_t ta, tb;
	int size0, size1;
	double t;
	if (argc != 4) {
		std::cerr << "用法说明: " << argv[0] << " <输入文件> <输出文件> [zip|unzip]" << std::endl;
		return 1;
	}

	if (strcmp(argv[3], "zip")==0) {
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman压缩开始 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		ta = clock();
		size0 = getfilesize(argv[1]);
		size1 = huffman_compress(argv[1], argv[2],size0);
		tb = clock();
		cout << endl << endl;
		cout << "原始文件大小为：" << setw(10) << setiosflags(ios::right) << size0 << "字节" << endl;
		cout << "压缩文件大小为：" << setw(10) << setiosflags(ios::right) << size1 << "字节" << endl;
		cout << "文件压缩比率为：" << setw(11) << setiosflags(ios::right) << 100.00 * size1 / (double)size0 << "%" << endl;
		cout << "压缩用时: " << setw(16) << setiosflags(ios::right) << (t = ((double)tb - (double)ta)) / CLOCKS_PER_SEC << "秒" << endl << endl;
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman压缩成功 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	}
	else if (strcmp(argv[3], "unzip")==0) {
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman解压开始 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		ta = clock();
		huffman_decompress(argv[1], argv[2]);
		tb = clock();	
		size0 = getfilesize(argv[1]);
		size1 = getfilesize(argv[2]);
		cout << endl <<endl << "压缩文件大小为：" << setw(10) << setiosflags(ios::right) << size0 << "字节" << endl;
		cout << "解压文件大小为：" << setw(10) << setiosflags(ios::right) << size1 << "字节" << endl;
		cout << "解压用时: " << setw(16) << setiosflags(ios::right) << (t = ((double)tb - (double)ta)) / CLOCKS_PER_SEC << "秒" << endl << endl;
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Huffman解压完成 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	}
	else {
		std::cerr << "非法用法: " << argv[3] << std::endl;
		std::cerr << "用法说明: " << argv[0] << " <输入文件> <输出文件> [zip|unzip]" << std::endl;
		return 1;
	}

	return 0;
}

