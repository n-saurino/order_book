#include <gtest/gtest.h>
#include "Orderbook.hpp"

class OrderbookTest : public ::testing::Test {
protected:
    Orderbook orderbook;
};

// ✅ **Test 1: Adding Orders to the Orderbook**
TEST_F(OrderbookTest, AddOrder) {
    Order order1{1, 100, 10, BID};
    Order order2{2, 105, 5, ASK};

    orderbook.Add(order1);
    orderbook.Add(order2);

    EXPECT_EQ(orderbook.bids_.size(), 1);
    EXPECT_EQ(orderbook.asks_.size(), 1);
    EXPECT_EQ(orderbook.bids_.begin()->first, 100);
    EXPECT_EQ(orderbook.asks_.begin()->first, 105);
}

// ✅ **Test 2: Matching Orders**
TEST_F(OrderbookTest, MatchOrders) {
    Order bid1{1, 100, 10, BID};
    Order ask1{2, 100, 5, ASK};

    orderbook.Add(bid1);
    orderbook.Add(ask1);

    EXPECT_EQ(orderbook.bids_.begin()->second.front().quantity_, 5);
    EXPECT_EQ(orderbook.asks_.size(), 0);
}

// ✅ **Test 3: Cancel Order**
TEST_F(OrderbookTest, CancelOrder) {
    Order order1{1, 100, 10, BID};
    orderbook.Add(order1);
    orderbook.Cancel(order1);

    EXPECT_EQ(orderbook.bids_.size(), 0);
    EXPECT_EQ(orderbook.orders_.size(), 0);
}

// ✅ **Test 4: Modify Order**
TEST_F(OrderbookTest, ModifyOrder) {
    Order old_order{1, 100, 10, BID};
    Order new_order{1, 101, 15, BID};  // Modify price & quantity

    orderbook.Add(old_order);
    orderbook.Modify(old_order, new_order);

    EXPECT_EQ(orderbook.bids_.size(), 1);
    EXPECT_EQ(orderbook.bids_.begin()->first, 101);
    EXPECT_EQ(orderbook.bids_.begin()->second.front().quantity_, 15);
}

// ✅ **Test 5: Prevent Duplicate Orders**
TEST_F(OrderbookTest, PreventDuplicateOrders) {
    Order order1{1, 100, 10, BID};
    Order order2{1, 100, 10, BID};  // Duplicate order ID

    orderbook.Add(order1);
    orderbook.Add(order2);

    EXPECT_EQ(orderbook.bids_.size(), 1);
    EXPECT_EQ(orderbook.bids_.begin()->second.size(), 1);
}

// ✅ **Test 6: Ensure Partial Fills Work Correctly**
TEST_F(OrderbookTest, PartialFill) {
    Order bid1{1, 100, 10, BID};
    Order ask1{2, 100, 5, ASK};

    orderbook.Add(bid1);
    orderbook.Add(ask1);

    EXPECT_EQ(orderbook.bids_.begin()->second.front().quantity_, 5);
    EXPECT_EQ(orderbook.asks_.size(), 0);
}

// ✅ **Test 7: Full Fill Removes Orders**
TEST_F(OrderbookTest, FullFillRemovesOrders) {
    Order bid1{1, 100, 5, BID};
    Order ask1{2, 100, 5, ASK};

    orderbook.Add(bid1);
    orderbook.Add(ask1);

    EXPECT_EQ(orderbook.bids_.size(), 0);
    EXPECT_EQ(orderbook.asks_.size(), 0);
}

// ✅ **Test 8: Multiple Orders at the Same Price Level**
TEST_F(OrderbookTest, MultipleOrdersAtSamePrice) {
    Order bid1{1, 100, 5, BID};
    Order bid2{2, 100, 5, BID};  // Same price level

    orderbook.Add(bid1);
    orderbook.Add(bid2);

    EXPECT_EQ(orderbook.bids_.size(), 1);
    EXPECT_EQ(orderbook.bids_[100].size(), 2);
}

// ✅ **Test 9: Ensure Orders Are Sorted Correctly**
TEST_F(OrderbookTest, OrderSorting) {
    Order bid1{1, 100, 10, BID};
    Order bid2{2, 105, 10, BID};  // Higher price
    Order ask1{3, 110, 5, ASK};
    Order ask2{4, 115, 5, ASK};   // Higher price

    orderbook.Add(bid1);
    orderbook.Add(bid2);
    orderbook.Add(ask1);
    orderbook.Add(ask2);

    EXPECT_EQ(orderbook.bids_.begin()->first, 105);
    EXPECT_EQ(orderbook.asks_.begin()->first, 110);
}

// ✅ **Test 10: Ensure Orderbook Starts Empty**
TEST_F(OrderbookTest, OrderbookStartsEmpty) {
    EXPECT_EQ(orderbook.bids_.size(), 0);
    EXPECT_EQ(orderbook.asks_.size(), 0);
    EXPECT_EQ(orderbook.orders_.size(), 0);
}