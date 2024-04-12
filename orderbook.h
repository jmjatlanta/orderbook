#pragma once
#include <set>
#include <cstdint>

class Order
{
    public:
    uint32_t id;
    uint32_t qty;
    double price;

    friend bool operator<(const Order& a, const Order& b);
    friend bool operator>(const Order& a, const Order& b);
    friend bool operator==(const Order& a, const Order& b);
};

class OrderBook
{
    public:
    std::set<Order, std::greater<Order>> bids;
    std::set<Order, std::less<Order>> asks;
};
