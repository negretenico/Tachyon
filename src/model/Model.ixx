export module model;
import std;
export namespace Model {
	struct  TickHeader {
		char magic[5] = {}; // we need to use 5 bytes for the null terminator
		std::uint16_t  version;
		std::uint64_t  count;
	};

	/*
*			r["E"],              # event_time
			r["T"],              # trade_time
			r["t"],              # trade_id
			float(r["p"]),       # price
			float(r["q"]),       # quantity
			sym,                 # symbol
			side_from_maker(r["m"]),  # side
*/
	struct Trade {
		std::uint64_t eventTime;
		std::uint64_t tradeTime;
		std::uint64_t tradeId;
		float price;
		float quantity;
		char  symbol[2];
		bool isBuyerMarketMaker;
	};
	using Trades = std::vector<Trade>;

}