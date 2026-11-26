module tachyon_tick_convertor;
import model;
import std;


template <typename T>
std::vector<std::uint8_t> GetBufferFromTickBinary(const T size) {
	std::vector<std::uint8_t> buffer(size);
	std::ifstream file("tools/tick_convertor/order.tick", std::ios::binary);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
		std::print("Error reading data from order.tick");
		return {};
	}
	return buffer;
}

Model::Trade ConvertTradeFromBinary(std::uint8_t* bytes) {
	return reinterpret_cast<Model::Trade>(bytes);
}


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

std::optional< Model::Trades> TickConvertor::ReadTicksUsingFStream() {
	// we want to convert our .ticks file to in memory representaiton of Trades so we can 
	// use it for benchmarking of our statgies 

	constexpr std::uint64_t BUFFER_SIZE = 362129 * 64;
	constexpr std::uint16_t TICK_HEADER_SIZE = 14;
	constexpr std::uint32_t TRADE_ENTRY_SIZE = 64;
	auto buffer = GetBufferFromTickBinary(TICK_HEADER_SIZE);
	if (buffer.empty()) {
		return std::nullopt;
	}
	//from i = 14 to BUFFER, updat by TRADE_ENTRY_SIZE
	//	ConvertToTrade(bytes) add auto vector
	//Go over the bufffer skip the header and read the trades into memory
	//that looks somethng like this 
	Model::Trades  trades;
	trades.reserve((BUFFER_SIZE - TICK_HEADER_SIZE) / TRADE_ENTRY_SIZE);
	for (std::uint64_t i = TICK_HEADER_SIZE + 1; i < BUFFER_SIZE; i += TRADE_ENTRY_SIZE) {
		auto trade = ConvertTradeFromBinary(buffer.data() + i);
		// add to vector
	}

	return trades;

}

std::optional< Model::TickHeader> TickConvertor::ReadTickHeader() {
	// do we really want ot have these here, it might be better to come from the model, like
	// an implentiaon need not define the sizes it hsoudl be told 
	constexpr int TICK_HEADER_MAGIC_SIZE = 4;
	constexpr int TICK_HEADER_VERSION_SIZE = 2;
	constexpr int TICK_HEADER_COUNT_SIZE = 8;
	constexpr int TICK_HEADER_SIZE = TICK_HEADER_MAGIC_SIZE + TICK_HEADER_VERSION_SIZE + TICK_HEADER_COUNT_SIZE;

	auto buffer = GetBufferFromTickBinary(TICK_HEADER_SIZE);
	if (buffer.empty()) {
		return std::nullopt;
	}
	Model::TickHeader header;

	std::memcpy(header.magic, buffer.data(), TICK_HEADER_MAGIC_SIZE);
	std::memcpy(&header.version, buffer.data() + TICK_HEADER_MAGIC_SIZE, TICK_HEADER_VERSION_SIZE);
	std::memcpy(&header.count, buffer.data() + TICK_HEADER_MAGIC_SIZE + TICK_HEADER_VERSION_SIZE, TICK_HEADER_COUNT_SIZE);
	return header;
}