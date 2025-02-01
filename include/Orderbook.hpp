#pragma once
#include <list>
#include <unordered_map>
#include <map>

enum Side{
    Bid,
    Ask
};

using Price = int;
using OrderId = int;
using Volume = int; 



struct Order{
    static int order_count_;
    OrderId order_id_{};
    Volume volume_{};    
    Side size_{};
};


class Orderbook{
public:
    Orderbook(){
        
    }
    
    ~Orderbook(){
        
    }
    
    void Add(const Order& order){
        
    }
    
    void Cancel(const Order& order){

    }
    
    void Modify(const Order& old_order, const Order& modify_order){
        
    }
    
private:
    std::unordered_map<OrderId, std::list<Order>::iterator> orders_{};
    std::map<Price, std::list<Order>, std::greater<Price>> asks_{};
    std::map<Price, std::list<Order>, std::less<Price>> bids_{};
};