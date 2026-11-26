export module tachyon_tick_convertor;
import model;
import std;
export namespace TickConvertor {
	using namespace Model;
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 
	Trades ReadTicksUsingWindowsAPI();
	Trades ReadTicksUsingEmbedded();
	Trades ReadTicksUsingFStream();
	std::optional< TickHeader> ReadTickHeader();
}