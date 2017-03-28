#include <iostream>

void learn_lambda_func_1() {
	int value_1 = 1;
	// lambda function
	auto copy_value_1 = [value_1] {
		return value_1;
	};
	value_1 = 100;
	auto stored_value_1 = copy_value_1();

	std::cout << "value_1 = " << value_1 << std::endl;
	std::cout << "stored_value_1 = " << stored_value_1 << std::endl;
}

void learn_lambda_func_2() {
	int value_2 = 1;
	// lambda function
	auto copy_value_2 = [&value_2] {
		return value_2;
	};

	value_2 = 100;
	auto stored_value_2 = copy_value_2();

	std::cout << "value_2 = " << value_2 << std::endl;
	std::cout << "stored_value_2 = " << stored_value_2 << std::endl;
};

void poly_lambda() {
	auto add = [](auto x, auto y) {
		return x + y;
	};

	auto x = add(1, 2);
	auto y = add(1.1, 2.2);

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
};

void lambda_as_func_ptr() {
	auto func = [](int value) {
		std::cout << "value = " << value << std::endl;
	};

	// use lambda as a function pointer
	func(1);
};

int main() {

	learn_lambda_func_1();
	learn_lambda_func_2();
	poly_lambda();
	lambda_as_func_ptr();
	return 0;
}