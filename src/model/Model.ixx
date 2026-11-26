export module model;
import std;
export namespace Model {
	struct  TickHeader {
		char magic[5] = {}; // we need to use 5 bytes for the null terminator
		std::uint16_t  version;
		std::uint64_t  count;
	};
	struct Trade {
		std::string eventType;
		std::uint64_t eventTime;
		std::uint64_t tradeTime;
		std::string symbol;
		std::uint64_t tradeId;
		float price;
		float quantity;
		std::string orderType;
		bool isBuyerMarketMaker;
	};
	using Trades = std::vector<Trade>;

}