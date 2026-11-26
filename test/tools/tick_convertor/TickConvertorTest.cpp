import tachyon_tick_convertor;
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

TEST_CASE("Should convert ticks to trades using WindowsAPI") {
	TickConvertor::ReadTicksUsingWindowsAPI();
	CHECK(false);
};
TEST_CASE("Should convert ticks to trades using #embedded") {
	TickConvertor::ReadTicksUsingEmbedded();
	CHECK(false);
};

TEST_CASE("Should convert ticsk to trades using fstream") {
	auto trades = TickConvertor::ReadTicksUsingFStream();
	REQUIRE(trades.has_value());
	REQUIRE(!trades->empty());
};

TEST_CASE("Should read tick header") {
	auto tickHeader = TickConvertor::ReadTickHeader();
	REQUIRE(tickHeader.has_value());
	CHECK(tickHeader->version == 1);
	CHECK(tickHeader->count == 362129);
	REQUIRE_THAT("TICK", Equals(tickHeader->magic));
};
