# Implement a Simple Order Book in C++

**Difficulty:** Medium-Hard  
**Tags:** C++, Data Structures, Heap, Multimap, Simulation

## Problem Statement

You are tasked with implementing a simple order book that handles limit buy and sell orders for a stock trading system.

An order book is a system that keeps track of buy (BID) and sell (ASK) orders, matching them when possible based on price and time priority.

## Task

Design a class `OrderBook` that supports the following operations:

### `void addOrder(int orderId, int price, int quantity, char side)`

Adds a new order to the book.

Parameters:
- `orderId`: Unique ID for the order
- `price`: The price at which the order is placed
- `quantity`: The number of shares in the order
- `side`: 'B' for buy orders (BID), 'S' for sell orders (ASK)

Matching Rules:
- A BUY (BID) order can be executed if there is a SELL (ASK) order at the same or lower price
- A SELL (ASK) order can be executed if there is a BUY (BID) order at the same or higher price
- If multiple matching orders exist, they are matched in FIFO order (earliest order gets executed first)
- If an order is partially filled, it remains in the book with the remaining quantity

### `void cancelOrder(int orderId)`

Cancels an order with the given orderId, removing it from the book.

### `vector<string> getTopOrders(int k)`

Returns the top k orders (highest buy and lowest sell prices) formatted as strings:
- "BID price quantity" (for buy orders)
- "ASK price quantity" (for sell orders)

## Examples

### Example 1: Basic Operations

```cpp
OrderBook orderBook;
orderBook.addOrder(1, 100, 10, 'B');  // Buy 10 shares at $100
orderBook.addOrder(2, 105, 5, 'S');   // Sell 5 shares at $105
orderBook.addOrder(3, 102, 8, 'B');   // Buy 8 shares at $102
orderBook.addOrder(4, 101, 6, 'S');   // Sell 6 shares at $101

vector<string> topOrders = orderBook.getTopOrders(2);
// Output: ["BID 102 8", "ASK 101 6"]
```

### Example 2: Order Matching

```cpp
OrderBook orderBook;
orderBook.addOrder(1, 100, 10, 'B');  // Buy 10 at 100
orderBook.addOrder(2, 99, 5, 'S');    // Sell 5 at 99 (matches)
orderBook.addOrder(3, 101, 7, 'S');   // Sell 7 at 101
orderBook.cancelOrder(3);              // Cancel order 3

vector<string> topOrders = orderBook.getTopOrders(2);
// Output: ["BID 100 5"]  // Buy order at 100 has 5 shares left
```

## Constraints

- 1 <= orderId <= 10^6
- 1 <= price <= 10^9
- 1 <= quantity <= 10^6
- side ∈ {'B', 'S'}
- 1 <= k <= min(number of active orders, 100)

## Follow-Up Questions

1. How would you optimize order matching in a high-frequency trading system?
2. Can you implement a market order system where orders execute immediately at the best available price?
