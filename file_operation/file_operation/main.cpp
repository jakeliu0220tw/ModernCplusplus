#include <iostream>
#include <string>
#include <fstream>
//#include <WinBase.h>

int main(int, char*[])
{
	// dump string into file
	std::ofstream ofs("myfile.txt");
	ofs << "testA\ntestB\ntestC";
	ofs.close();

	// read file content into string
	std::ifstream ifs("myfile.txt");
	std::string str;
	while (ifs >> str)
	{
		std::cout << str << std::endl;
	}
	ifs.close();

	// read file content into string
	std::ifstream ifs2("myfile.txt");
	while (std::getline(ifs2, str))
	{
		std::cout << str << std::endl;
	}
	ifs2.close();

	// rename file
	std::rename("D:/GitRepo/jakeliu0220tw/ModernCplusplus/file_operation/Debug/myfile.txt", "D:/GitRepo/jakeliu0220tw/ModernCplusplus/file_operation/Debug/myfile.txt.old");
	std::rename("7z.dll", "7z.dll.old");


	return 0;
}