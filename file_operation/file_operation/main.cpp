#include <iostream>
#include <string>
#include <fstream>

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

	return 0;
}