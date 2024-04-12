#include "orderbook.h"

bool OrderComparator::operator () (const Order& a, const Order& b) const
{
    // for now, order by price and then id
    if (a.price == b.price)
	return a.id < b.id;
    return a.price < b.price;
}

