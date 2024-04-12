#include <gtest/gtest.h>
#include "orderbook.h"

std::string to_string(const Order& o)
{
    std::stringstream ss;
    ss << "Id: " << o.id << " Qty: " << o.qty << " Price: " << o.price;
    return ss.str();
}

std::string to_string(const OrderBook& ob)
{
    std::stringstream ss;
    ss << "OrderBook -> Bids: \n";
    for(auto o : ob.bids)
	ss << " " << to_string(o) << "\n";
    ss << "OrderBook -> Asks: \n";
    for(auto o : ob.asks)
	ss << " " << to_string(o) << "\n";
    return ss.str();
}

TEST(basic, ctor)
{
    OrderBook ob;

    for(uint32_t i = 0; i < 10; ++i)
    {
	Order bid{i, i * 100, ((double)i + 100) / 100};
	Order ask{i + 100, i * 100, ((double)i + 200) / 100};
	ob.bids.insert(bid);
	ob.asks.insert(ask);
    }
    std::cout << to_string(ob) << "\n";
}
