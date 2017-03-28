#include <functional>
#include <iostream>

int foo(int para) {
	return para;
};

int main() {

	// using std::function to define a function ptr, it's name is 'func', return 'int', passing parameter 'int'
	std::function<int(int)> func = foo;
	std::cout << "func(10) = " << func(10) << std::endl;

	// using lambada as a function pointer func2
	int important = 10;
	std::function<int(int)> func2 = [&](int value) -> int {
		return 1 + value + important;
	};
	std::cout << "fun2(10) = " << func2(10) << std::endl;

	return 0;
}
