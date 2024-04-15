#pragma once
#include <set>
#include <cstdint>

template <class T>
class Order
{
    public:
    Order() : id(0), qty(0), price(0.0) {}
    Order(uint32_t i, uint32_t q, double p) : id(i), qty(q), price(p) {}

    uint32_t id;
    uint32_t qty;
    double price;

    template<class Y>
    friend bool operator==(const Order<Y>& a, const Order<Y>& b);
};

class Bid : public Order<Bid> 
{ 
    public:
    Bid() : Order () {}
    Bid(uint32_t i, uint32_t q, double p) : Order(i, q, p) {}
    friend bool operator<(const Bid& a, const Bid& b);
    friend bool operator>(const Bid& a, const Bid& b);
};
class Ask : public Order<Ask> 
{ 
    public:
    Ask() : Order() {}
    Ask(uint32_t i, uint32_t q, double p) : Order(i, q, p) {}
    friend bool operator<(const Ask& a, const Ask& b);
    friend bool operator>(const Ask& a, const Ask& b);
};

class OrderBook
{
    public:
    std::set<Bid, std::greater<Bid>> bids;
    std::set<Ask, std::less<Ask>> asks;
};
