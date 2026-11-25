#include <catch2/catch_test_macros.hpp>
// this is just an exmpale 
void print_some_info() {
	UNSCOPED_INFO("Info from helper");
}

TEST_CASE("Baz") {
	print_some_info();
	for (int i = 0; i < 2; ++i) {
		UNSCOPED_INFO("The number is " << i);
	}
	CHECK(true);
}

TEST_CASE("Qux") {
	INFO("First info");
	UNSCOPED_INFO("First unscoped info");
	CHECK(true);

	INFO("Second info");
	UNSCOPED_INFO("Second unscoped info");
	CHECK(true);
}