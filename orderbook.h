#pragma once
#include <set>
#include <cstdint>

template <class T>
class Order
{
    public:
    uint32_t id;
    uint32_t qty;
    double price;

    friend bool operator<(const Order<T>& a, const Order<T>& b);
    friend bool operator>(const Order<T>& a, const Order<T>& b);
    friend bool operator==(const Order<T>& a, const Order<T>& b);
};

class Bid : public Order<Bid>
{
};

class Ask : public Order<Ask>
{
};

class OrderBook
{
    public:
    std::set<Bid, std::greater<Bid>> bids;
    std::set<Ask, std::less<Ask>> asks;
};
