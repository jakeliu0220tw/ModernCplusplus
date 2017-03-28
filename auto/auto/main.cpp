#include <iostream>
#include <vector>

int main() {
	auto i = 5;	//i is int
	auto arr = new auto(10); // auto is int

	std::cout << "i = " << i << std::endl;

	// use iterator based on range
	int array[] = {1, 2, 3, 4, 5};
	for (auto& x : array) {
		std::cout << x << std::endl;
	}

	// old style iterator usage
	std::vector<int> arr2(5, 100);
	for (std::vector<int>::iterator i = arr2.begin(); i != arr2.end(); ++i) {
		std::cout << *i << std::endl;
	}

	// new style iterator usage
	for (auto& i : arr2) {
		std::cout << i << std::endl;
	}

	return 0;
}