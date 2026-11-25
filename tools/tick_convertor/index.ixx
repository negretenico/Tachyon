export module TickConvertor;

export namespace TickConvertor {
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 
	void ConvertTicksUsingWindowsAPI();
	void ConvertTicksUsingEmbedded();
	void ConvertTicksUsingFStream();
}