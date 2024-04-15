#include <gtest/gtest.h>
#include <random>

#include "orderbook.h"

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

TEST(basic, ctor)
{
    OrderBook ob;

    for(uint32_t i = 0; i < 10; ++i)
    {
	Bid bid{i, i * 100, ((double)i + 100) / 100};
	Ask ask{i + 100, i * 100, ((double)i + 200) / 100};
	ob.add(bid);
	ob.add(ask);
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
			    ob.add( Ask{ counter, 100, std::round(in*100)/100 } );
			else
			    ob.add( Bid{counter, 100, std::round(in*100)/100});
			++counter;
		  });
    std::cout << to_string(ob) << "\n";
}
