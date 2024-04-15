#pragma once
#include <cstdint>
#include <string>

class Bid
{ 
    public:
    Bid() {}
    Bid(uint32_t i, uint32_t q, double p) : id(i), qty(q), price(p) {}
    friend bool operator<(const Bid& a, const Bid& b);
    friend bool operator>(const Bid& a, const Bid& b);
    friend bool operator==(const Bid& a, const Bid& b);

    uint32_t id;
    uint32_t qty;
    double price;
};
class Ask
{ 
    public:
    Ask() {}
    Ask(uint32_t i, uint32_t q, double p) : id(i), qty(q), price(p) {}
    friend bool operator<(const Ask& a, const Ask& b);
    friend bool operator>(const Ask& a, const Ask& b);
    friend bool operator==(const Ask& a, const Ask& b);

    uint32_t id;
    uint32_t qty;
    double price;
};

class OrderBookImpl;

class OrderBook
{
    public:
    OrderBook();
    ~OrderBook();

    template<class T>
    bool add(const T& in);
    template<class T>
    bool update(const T& in);
    template <class T>
    bool remove(const T& in);

    friend std::string to_string(const OrderBook& in);

    private:
    OrderBookImpl* impl;
};
