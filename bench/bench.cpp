#include <benchmark/benchmark.h>
#include <random>
#include <cstdint>
#include "orderbook.h"


// globals to store random data
const uint32_t orders_per_round = 512;
const uint32_t rounds = 10;
const uint32_t sz = orders_per_round * rounds;
Bid bids[sz];
Ask asks[sz];

// the function to benchmark
void add_orders(OrderBook& ob, const Bid& bid, const Ask& ask)
{
    ob.bids.insert(bid);
    ob.asks.insert(ask);
}

// this function actually does the benchmarking
static void push_orders(benchmark::State& state)
{
    // this will be called (rounds) times
    while(state.KeepRunning())
    {
	OrderBook ob;
	// add bids and asks (orders_per_round) times
	for(uint32_t i = 0; i < orders_per_round; ++i)
	    add_orders(ob, bids[(state.range(0) * orders_per_round) + i], asks[(state.range(0) * orders_per_round) + i] );
    }
}

// need to build up some randomized data for the benchmarks
// The data should be normally distributed
void args(benchmark::internal::Benchmark* b)
{
    double avg = 10.0;
    std::default_random_engine eng;
    std::normal_distribution<double> dist(avg, 1.0);
    // fill arrays with (orders_per_round * rounds) random values
    for(uint32_t i = 0; i < sz; ++i)
    {
	double x = dist(eng);
	if (x > avg)
	    asks[i] = Ask{i, 100, x};
	else
	    bids[i] = Bid{i, 100, x};
    }
    // this will call the function (rounds) times
    for(uint32_t i = 0; i < rounds; ++i)
	b->Arg(i);
}

BENCHMARK(push_orders)->Apply(args);

BENCHMARK_MAIN();
