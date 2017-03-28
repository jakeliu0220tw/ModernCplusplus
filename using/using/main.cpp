#include <iostream>

int main() {
	// define a function ptr, name is 'process', return int, passing parameter is 'void *'
	typedef int(*process)(void *);

	// define a function ptr, name is 'process_v2', return int, passing parameter is 'void *'
	using process_v2 = int(void *);

	return 0;
}