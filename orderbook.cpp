#include "orderbook.h"

bool operator<(const Order& a, const Order& b)
{
    if (a.price == b.price)
	return a.id < b.id;
    return a.price < b.price;
}

bool operator>(const Order& a, const Order& b)
{
    if (a.price == b.price)
	return a.id > b.id;
    return a.price > b.price;
}

bool operator==(const Order& a, const Order& b)
{
    return a.price == b.price && a.id == b.id;
}

