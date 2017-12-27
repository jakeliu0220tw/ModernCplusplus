#include <windows.h>
#include <string.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

int main()
{
	char path[1024]{};
	strcpy(path, "C:\\Program Files(x86)\\Audacity\\audacity.exe -aa");
	PathRemoveFileSpecA(path);

	char path2[1024]{};
	strcpy(path2, "C:/Program Files(x86)/Audacity/audacity.exe -aa");
	PathRemoveFileSpecA(path2);


	return 0;
}
