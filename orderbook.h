#pragma once
#include <set>
#include <cstdint>

class Order;

class OrderComparator {
    bool operator() (const Order& a, const Order& b) const;
};

class Order
{
    public:
    uint32_t id;
    uint32_t qty;
    double price;
};

class OrderBook
{
    public:
    std::set<Order, std::greater<Order>> bids;
    std::set<Order, std::less<Order>> asks;
};
