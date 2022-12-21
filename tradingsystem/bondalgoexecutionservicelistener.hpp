/**
 * bondalgoexecutionservicelistener.hpp
 * Defines BondAlgoExecutionServiceListener to listen data pasing to
 * BondAlgoExecutionService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondalgoexecutionservice.hpp"
#include "bondmarketdataservice.hpp"

/**
 * BondAlgoExecutionServiceListener to listen data passing to BondAlgoExecution Servicing
 * from BondMarketDataService
 */
class BondAlgoExecutionServiceListener: public ServiceListener<OrderBook<Bond> > {

private:
    BondAlgoExecutionService* baes;

public:
    //ctor
    BondAlgoExecutionServiceListener(BondAlgoExecutionService * _baes) {
        baes = _baes;
    }

    //override pure virtual functions
    virtual void ProcessAdd(OrderBook<Bond>& data) override{
        baes->GenerateOrder(data);
    }

    virtual void ProcessRemove(OrderBook<Bond>& data) override {}
    virtual void ProcessUpdate(OrderBook<Bond>& data) override {}


};

#endif
