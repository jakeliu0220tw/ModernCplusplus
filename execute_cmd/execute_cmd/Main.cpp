#include <iostream>
using namespace std;

#include <windows.h> // ShellExecute()

int main()
{
	//ShellExecute(NULL, NULL, "http://www.hinet.net", NULL, NULL, SW_SHOW);
	ShellExecute(NULL, NULL, "D:\\GitRepo\\jakeliu0220tw\\ModernCplusplus\\execute_cmd\\test.bat", NULL, NULL, SW_SHOW);
	//ShellExecute(NULL, NULL, "cmd.exe", "/k dir c:", NULL, SW_SHOW);

	return 0;
}
