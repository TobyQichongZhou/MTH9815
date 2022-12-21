/**
 * algoexecution.hpp
 * Defines algoexecution class that contains the algo for this trading system
 *
 * @author Qichong Zhou
 */
#ifndef ALGO_EXECUTION_HPP
#define ALGO_EXECUTION_HPP

#include <string>
#include <vector>
#include <map>
#include "products.hpp"
#include "executionservice.hpp"

/**
 * AlgoExecution class: algo for bond trading
 */
class AlgoExecution{

private:
    static int orderId;
    ExecutionOrder<Bond> executionorder;

public:
    //ctor
    AlgoExecution():executionorder(ExecutionOrder<Bond>(Bond(), BID, "0", MARKET, 0, 0, 0, "0", false)){}
    AlgoExecution(ExecutionOrder<Bond> _executionorder): executionorder(_executionorder) {}

    ExecutionOrder<Bond> GetExecutionOrder() const {
        return executionorder;
    }

    bool UpdateExecutionOrder(OrderBook<Bond> &orderbook);


};

int AlgoExecution::orderId = 1;

bool AlgoExecution::UpdateExecutionOrder(OrderBook<Bond> &orderbook) {
    if (orderbook.GetProduct().GetProductId()!=executionorder.GetProduct().GetProductId()) {return false;}

    auto side = orderId%2==0? BID:OFFER;

    auto order_id = std::to_string(orderId);

    OrderType order_type;
    switch (rand()%5){
        case 0: order_type = FOK;break;
        case 1: order_type = IOC;break;
        case 2: order_type = MARKET;break;
        case 3: order_type = LIMIT;break;
        case 4: order_type = STOP;break;
    }

    auto bid_order = orderbook.GetBidStack()[0];
    auto offer_order = orderbook.GetOfferStack()[0];
    if (offer_order.GetPrice() - bid_order.GetPrice() < 1.0/128.0 + 1e-6) {
        double p;
        long vQ;
        if (side == BID){
            p = offer_order.GetPrice();
            vQ = offer_order.GetQuantity();
        }
        else {
            p = bid_order.GetPrice();
            vQ = bid_order.GetQuantity();
        }
        auto hQ = vQ * 2.0;
        executionorder = ExecutionOrder<Bond>(orderbook.GetProduct(), side, order_id, order_type, p, vQ, hQ, "P", false);
        return true;
    }
    else{
        return false;
    }
}

#endif
