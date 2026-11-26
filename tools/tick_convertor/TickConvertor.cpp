module tachyon_tick_convertor;
import model;
import std;

Model::Trades TickConvertor::ReadTicksUsingEmbedded() {
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 
	return {};
}

Model::Trades TickConvertor::ReadTicksUsingWindowsAPI() {
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 
	return {};
}

Model::Trades TickConvertor::ReadTicksUsingFStream() {
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 
	return {};

}

std::optional< Model::TickHeader> TickConvertor::ReadTickHeader() {
	constexpr int TICK_HEADER_SIZE = sizeof(Model::TickHeader);
	constexpr int TICK_HEADER_MAGIC_SIZE = 4;
	constexpr int TICK_HEADER_VERSION_SIZE = 2;
	constexpr int TICK_HEADER_COUNT_SIZE = 8;
	std::vector<std::uint8_t> buffer(TICK_HEADER_SIZE);
	std::ifstream file("tools/tick_convertor/order.tick", std::ios::binary);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), TICK_HEADER_SIZE)) {
		std::print("Error reading data from order.tick");
		return std::nullopt;
	}
	Model::TickHeader header;

	std::memcpy(header.magic, buffer.data(), TICK_HEADER_MAGIC_SIZE);
	std::memcpy(&header.version, buffer.data() + TICK_HEADER_MAGIC_SIZE, TICK_HEADER_VERSION_SIZE);
	std::memcpy(&header.count, buffer.data() + TICK_HEADER_MAGIC_SIZE + TICK_HEADER_VERSION_SIZE, TICK_HEADER_COUNT_SIZE);
	return header;
}