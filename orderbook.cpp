#include "orderbook.h"

bool operator<(const Order<Ask>& a, const Order<Ask>& b)
{
    if (a.price == b.price)
	return a.id < b.id;
    return a.price < b.price;
}

bool operator<(const Order<Bid>& a, const Order<Bid>& b)
{
    if (a.price == b.price)
	return a.id > b.id;
    return a.price < b.price;
}

bool operator>(const Order<Ask>& a, const Order<Ask>& b)
{
    if (a.price == b.price)
	return a.id > b.id;
    return a.price > b.price;
}

bool operator>(const Order<Bid>& a, const Order<Bid>& b)
{
    if (a.price == b.price)
	return a.id < b.id;
    return a.price > b.price;
}

template<class T>
bool operator==(const Order<T>& a, const Order<T>& b)
{
    return a.price == b.price && a.id == b.id;
}

