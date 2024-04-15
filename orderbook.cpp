#include "orderbook.h"
#include <sstream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

std::string to_string(const Bid& o)
{
    std::stringstream ss;
    ss << "Id: " << o.id << " Qty: " << o.qty << " Price: " << o.price;
    return ss.str();
}

std::string to_string(const Ask& o)
{
    std::stringstream ss;
    ss << "Id: " << o.id << " Qty: " << o.qty << " Price: " << o.price;
    return ss.str();
}

bool operator<(const Ask& a, const Ask& b)
{
    if (a.price == b.price)
	return a.id < b.id;
    return a.price < b.price;
}

bool operator<(const Bid& a, const Bid& b)
{
    if (a.price == b.price)
	return a.id > b.id;
    return a.price < b.price;
}

bool operator>(const Ask& a, const Ask& b)
{
    if (a.price == b.price)
	return a.id > b.id;
    return a.price > b.price;
}

bool operator>(const Bid& a, const Bid& b)
{
    if (a.price == b.price)
	return a.id < b.id;
    return a.price > b.price;
}

template<class T>
bool operator==(const T& a, const T& b)
{
    return a.price == b.price && a.id == b.id;
}

/***
 * boost multi_index collections
 */
struct IdIndex {};
struct IdAndPriceIndex {};

typedef boost::multi_index_container<
    Bid,
    boost::multi_index::indexed_by<
	boost::multi_index::ordered_unique<
	    boost::multi_index::tag<IdAndPriceIndex>,
	    boost::multi_index::identity<Bid>,
	    std::greater<Bid>
	>,
	boost::multi_index::ordered_unique<
	    boost::multi_index::tag<IdIndex>,
	    boost::multi_index::member<Bid, uint32_t, &Bid::id>
	>
    >
> BidSet;
typedef boost::multi_index_container<
    Ask,
    boost::multi_index::indexed_by<
	boost::multi_index::ordered_unique<
	    boost::multi_index::tag<IdAndPriceIndex>,
	    boost::multi_index::identity<Ask>,
	    std::less<Ask>
	>,
	boost::multi_index::ordered_unique<
	    boost::multi_index::tag<IdIndex>,
	    boost::multi_index::member<Ask, uint32_t, &Ask::id>
	>
    >
> AskSet;

class OrderBookImpl
{
    public:
    BidSet bids;
    AskSet asks;
};

/****
* OrderBook
*/

OrderBook::OrderBook()
{
    impl = new OrderBookImpl{};
}
OrderBook::~OrderBook()
{
    delete impl;
}

template<class T>
bool OrderBook::add(const T& in)
{
    //static_assert(false);
    return false;
}

template<>
bool OrderBook::add(const Bid& in)
{
    impl->bids.insert(in);
    return true;
}

template<>
bool OrderBook::add(const Ask& in)
{
    impl->asks.insert(in);
    return true;
}

template<class T>
bool OrderBook::update(const T& in)
{
    //static_assert(false);
    return false;
}

template<>
bool OrderBook::update(const Bid& in)
{
    auto itr = impl->bids.get<IdIndex>().find(in.id);
    if (itr != impl->bids.get<IdIndex>().end())
    {
	Bid newBid = *itr;
	newBid.qty = in.qty;
	newBid.price = in.price;
	impl->bids.get<IdIndex>().replace(itr, newBid);
	return true;
    }
    return false;
}

template<>
bool OrderBook::update(const Ask& in)
{
    auto itr = impl->asks.get<IdIndex>().find(in.id);
    if (itr != impl->asks.get<IdIndex>().end())
    {
	Ask newObj = *itr;
	newObj.qty = in.qty;
	newObj.price = in.price;
	impl->asks.get<IdIndex>().replace(itr, newObj);
	return true;
    }
    return false;
}

template<class T>
bool OrderBook::remove(const T& in)
{
    //static_assert(false);
    return false;
}
template<>
bool OrderBook::remove(const Bid& in)
{
    auto itr = impl->bids.get<IdIndex>().find(in.id);
    if (itr != impl->bids.get<IdIndex>().end())
    {
	impl->bids.get<IdIndex>().erase(itr);
	return true;
    }
    return false;
}
template<>
bool OrderBook::remove(const Ask& in)
{
    auto itr = impl->asks.get<IdIndex>().find(in.id);
    if (itr != impl->asks.get<IdIndex>().end())
    {
	impl->asks.get<IdIndex>().erase(itr);
	return true;
    }
    return false;
}

std::string to_string(const OrderBook& ob)
{
    std::stringstream ss;
    ss << "OrderBook -> Bids: \n";
    for(auto o : ob.impl->bids)
	ss << " " << to_string(o) << "\n";
    ss << "OrderBook -> Asks: \n";
    for(auto o : ob.impl->asks)
	ss << " " << to_string(o) << "\n";
    return ss.str();
}

