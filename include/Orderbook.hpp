#pragma once
#include <list>
#include <unordered_map>
#include <map>

enum Side{
    BID,
    ASK
};

using Price = int;
using OrderId = int;
using Quantity = int; 

struct Order{
    static int order_count_;
    OrderId order_id_{};
    Price price_{};
    Quantity quantity_{};    
    Side side_{};
};



class Orderbook{
public:
    Orderbook(): orders_{}, asks_{}, bids_{}{
        
    }
    
    ~Orderbook(){
        
    }
    
    void Add(const Order& order){
        if(orders_.count(order.order_id_)){
            return;
        }
        
        if(order.side_ == BID){
            bids_[order.price_].emplace_back(order);
            orders_[order.order_id_] = --bids_[order.price_].end();
        }else{
            asks_[order.price_].emplace_back(order);
            orders_[order.order_id_] = --asks_[order.price_].end();
        } 
        
        Match();
    }
    
    void Cancel(const Order& order){
        if(!orders_.count(order.order_id_)){
            return;
        }
        
        auto order_it{orders_[order.order_id_]};

        if(order.side_ == BID){
            bids_[order.price_].erase(order_it);
        }else{
            asks_[order.price_].erase(order_it);
        }

        orders_.erase(order.order_id_);
    }
    
    void Modify(const Order& old_order, const Order& modify_order){
        if(orders_.count(old_order.order_id_)){
            Cancel(old_order);
        } 
        Add(modify_order);
        Match();
    }
    
    bool Match(){

        return false;
    }
    
private:
    std::unordered_map<OrderId, std::list<Order>::iterator> orders_{};
    std::map<Price, std::list<Order>, std::greater<Price>> asks_{};
    std::map<Price, std::list<Order>, std::less<Price>> bids_{};
};