import TickConvertor;
#include <catch2/catch_test_macros.hpp>
TEST_CASE("Should convert ticks to trades using WindowsAPI") {
	TickConvertor::ConvertTicksUsingWindowsAPI();
	CHECK(false);
};
TEST_CASE("Should convert ticks to trades using #embedded") {
	TickConvertor::ConvertTicksUsingEmbedded();
	CHECK(false);
};

TEST_CASE("Should convert ticsk to trades using fstream") {
	TickConvertor::ConvertTicksUsingFStream();
	CHECK(false);
};