#include <gtest/gtest.h>
#include <random>

#include "orderbook.h"

template<class T>
std::string to_string(const Order<T>& o)
{
    std::stringstream ss;
    ss << "Id: " << o.id << " Qty: " << o.qty << " Price: " << o.price;
    return ss.str();
}

std::vector<double> generateRandom(double mean, double stddev, uint32_t cnt)
{
    std::default_random_engine eng;
    std::normal_distribution<double> dist(mean, stddev);
    std::vector<double> retval;
    for(auto i = 0; i < cnt; ++i)
    {
	retval.push_back(dist(eng));
    }
    return retval;
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
	Bid bid{i, i * 100, ((double)i + 100) / 100};
	Ask ask{i + 100, i * 100, ((double)i + 200) / 100};
	ob.bids.insert(bid);
	ob.asks.insert(ask);
    }
    std::cout << to_string(ob) << "\n";
}

TEST(basic, random)
{
    std::vector<double> prices = generateRandom(100.0, 1.0, 300);
    OrderBook ob;
    uint32_t counter = 0;
    std::for_each(prices.begin(), prices.end(), [&ob, &counter](double in) {
			if (in > 100)
			    ob.asks.insert( Ask{ counter, 100, std::round(in*100)/100 } );
			else
			    ob.bids.insert( Bid{counter, 100, std::round(in*100)/100});
			++counter;
		  });
    std::cout << to_string(ob) << "\n";
}
