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
            if(bids_[order.price_].empty()){
                bids_.erase(order.price_);
            }
        }else{
            asks_[order.price_].erase(order_it);
            if(asks_[order.price_].empty()){
                asks_.erase(order.price_);
            }
        }

        orders_.erase(order.order_id_);
    } 

    void Fill(std::list<Order>::iterator ask_it, 
              std::list<Order>::iterator bid_it){
        // check if front order of bids or asks is larger
        // decrement each order's quantity by the smaller of the two
        // if one order is 0, remove it from the book
        int fill_qty{std::min(ask_it->quantity_, bid_it->quantity_)}; 
        ask_it->quantity_ -= fill_qty;
        bid_it->quantity_ -= fill_qty;

        if(!ask_it->quantity_){
            asks_[ask_it->price_].erase(ask_it);
        }
        
        if(!bid_it->quantity_){
            bids_[bid_it->price_].erase(bid_it);
        }
    }

    void Modify(const Order& old_order, const Order& modify_order){
        if(orders_.count(old_order.order_id_)){
            Cancel(old_order);
        } 
        Add(modify_order);
        Match();
    }
    
    void Match(){
        // need to loop while we have overlapping prices
        // call fill on the first two orders
        if(asks_.empty() || bids_.empty()){
            return;
        }

        auto asks_it{asks_.begin()};
        auto bids_it{bids_.begin()};
        
        while(!asks_.empty() && !bids_.empty()
              && asks_it->first <= bids_it->first){
            // call fill
            Fill(asks_it->second.begin(), bids_it->second.begin());

            if(asks_it->second.empty()){
                asks_.erase(asks_it);
                asks_it = asks_.begin();
            } 

            if(bids_it->second.empty()){
                bids_.erase(bids_it);
                bids_it = bids_.begin();
            } 
        }
    }
    
    std::unordered_map<OrderId, std::list<Order>::iterator> orders_{};
    std::map<Price, std::list<Order>, std::greater<Price>> asks_{};
    std::map<Price, std::list<Order>, std::less<Price>> bids_{};

private:
};