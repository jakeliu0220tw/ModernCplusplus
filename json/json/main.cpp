#include <iostream>
#include <fstream>
#include "json.hpp"

// for convenience
using json = nlohmann::json;

void example1() {
	// assume you want to create the JSON obj
	//{
	//	"pi": 3.141,
	//	"happy" : true,
	//	"name" : "Niels",
	//	"nothing" : null,
	//	"answer" : {
	//		"everything": 42
	//	},
	//	"list" : [1, 0, 2],
	//	"object" : {
	//		"currency": "USD",
	//		"value" : 42.99
	//	}
	//}

	// create an empty structure (null)
	json j;

	// add a number that is stored as double (note the implicit conversion of j to an object)
	j["pi"] = 3.141;

	// add a Boolean that is stored as bool
	j["happy"] = true;

	// add a string that is stored as std::string
	j["name"] = "Niels";

	// add another null object by passing nullptr
	j["nothing"] = nullptr;

	// add an object inside the object
	j["answer"]["everything"] = 42;

	// add an array that is stored as std::vector (using an initializer list)
	j["list"] = { 1, 0, 2 };

	// add another object (using an initializer list of pairs)
	j["object"] = { { "currency", "USD" },{ "value", 42.99 } };

	// serialization with pretty printing
	// pass in the amount of spaces to indent
	std::cout << j.dump(4) << std::endl;
}

void example2() {
	json j = {
		{ "pi", 3.141 },
		{ "happy", true },
		{ "name", "Niels" },
		{ "nothing", nullptr },
		{ "answer",{
			{ "everything", 42 }
		} },
		{ "list",{ 1, 0, 2 } },
		{ "object",{
			{ "currency", "USD" },
			{ "value", 42.99 }
		} }
	};

	std::cout << j.dump(4) << std::endl;
}

// string to/from json obj
void example3() {
	// create object from string literal
	json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
	std::cout << j.dump() << std::endl;

	// or even nicer with a raw string literal
	auto j2 = R"(
	  {
		"happy": true,
		"pi": 3.141
	  }
	)"_json;
	std::cout << j2.dump() << std::endl;

	// parse explicitly
	auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
	std::cout << j3.dump() << std::endl;

	// explicit conversion to string
	std::string s = j.dump();
	std::cout << s << std::endl;

	// pass in the amount of spaces to indent
	std::string str = j.dump(4);
	std::cout << str << std::endl;
}

// stream to/from json obj
void example4()
{
	//write json to a file
	json j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
	std::ofstream ofs("myfile.json");
	// the setw manipulator was overloaded to set the indentation for pretty printing
	ofs << std::setw(4) << j << std::endl;
	ofs.close();

	//read a json file
	std::ifstream ifs("myfile.json");
	json j2;
	ifs >> j2;
	ifs.close();
	std::cout << j2.dump(4) << std::endl;
}

//STL-like access
void example5() {
	// create a array using push_back
	json j;
	j.push_back("foo");
	j.push_back(1);
	j.push_back(true);
	std::cout << j.dump(4) << std::endl;

	// also use emplace_back
	j.emplace_back(1.78);
	std::cout << j.dump(4) << std::endl;

	// iterate the array
	for (auto it = j.begin(); it != j.end(); it++) {
		std::cout << *it << std::endl;
	}

	// getter / setter
	std::string str = j[0];
	j[1] = 42;
	bool fool = j.at(2);
	std::cout << "str = " << str << std::endl;
	std::cout << "j[1] = " << j[1] << std::endl;
	std::cout << "fool = " << fool << std::endl;
	std::cout << j.dump() << std::endl;

	// comparison
	std::cout << (j == "[\"foo\", 42, true, 1.78]"_json) << std::endl;

	// other stuff
	j.size();     // 4 entries
	j.empty();    // false
	j.type();     // json::value_t::array
	j.clear();    // the array is empty again

	// convenience type checkers
	j.is_null();
	j.is_boolean();
	j.is_number();
	j.is_object();
	j.is_array();
	j.is_string();
}

void example6() {
	// create an object
	json o;
	o["foo"] = 23;
	o["bar"] = false;
	o["pi"] = 3.141;

	// also use emplace
	o.emplace("weather", "sunny");
	std::cout << o.dump(4) << std::endl;

	// iterator member functions for objects
	for (auto it = o.begin(); it != o.end(); ++it) {
		std::cout << it.key() << ":" << it.value() << std::endl;
	}

	// using count()
	int foo_present = o.count("foo");	// 1
	int boo_present = o.count("boo");	// 0

	// find an entry
	if (o.find("foo") != o.end()) {
		std::cout << "there is an entry with key \"foo\"" << std::endl;
		auto find = o.find("foo");
		std::cout << "key is " << find.key() << std::endl;
		std::cout << "value is " << find.value() << std::endl;
	}
}

// JSON pointer & JSON PATCH
void example7()
{
	// a JSON value
	json j_original = R"({
	  "baz": ["one", "two", "three"],
	  "foo": "bar"
	})"_json;
	std::cout << j_original.dump(4) << std::endl;

	// access members with a JSON pointer (RFC 6901)
	j_original["/baz/1"_json_pointer];
	// "two"
	std::cout << j_original["/baz/1"_json_pointer] << std::endl;

	// a JSON patch (RFC 6902)
	json j_patch = R"([
	  { "op": "replace", "path": "/baz", "value": "boo" },
	  { "op": "add", "path": "/hello", "value": ["world"] },
	  { "op": "remove", "path": "/foo"}
	])"_json;
	std::cout << j_patch.dump(4) << std::endl;

	// apply the patch
	json j_result = j_original.patch(j_patch);
	// {
	//    "baz": "boo",
	//    "hello": ["world"]
	// }
	std::cout << j_result.dump(4) << std::endl;

	// calculate a JSON patch from two JSON values
	json diff = json::diff(j_result, j_original);
	// [
	//   { "op":" replace", "path": "/baz", "value": ["one", "two", "three"] },
	//   { "op": "remove","path": "/hello" },
	//   { "op": "add", "path": "/foo", "value": "bar" }
	// ]
	std::cout << diff.dump(4) << std::endl;

	json j_old = R"({
	  "server" : { "version" : "1_0_3" }
	})"_json;
	json j_new = R"({

	})"_json;
	diff = json::diff(j_old, j_new);
	std::cout << diff.dump(4) << std::endl;
}

int main() 
{
	//example1();
	//example2();
	//example3();
	//example4();
	//example5();
	//example6();
	example7();
	return 0;
}