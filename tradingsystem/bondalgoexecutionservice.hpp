/**
 * bondalgoexecutionservice.hpp
 * Defines BondAlgoExecutionService class that manages all info of trading algo running
 *
 * @author Qichong Zhou
 */
#ifndef BOND_ALGO_EXECUTION_SERVICE_HPP
#define BOND_ALGO_EXECUTION_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "algoexecution.hpp"
#include "soa.hpp"

/**
 * Bond Algo Execution Service to manage execution orders across multiple and bonds.
 * Keyed on product identifier.
 */
class BondAlgoExecutionService: Service<string, AlgoExecution>{

private:
    map<string, AlgoExecution> algoexecutionMap;
    vector<ServiceListener<AlgoExecution> *> listenersList;

public:
    //ctor
    BondAlgoExecutionService();

    //override all virtual functions
    virtual AlgoExecution& GetData(string key) override;
    virtual void OnMessage(AlgoExecution &algoexecution) override;
    virtual void AddListener(ServiceListener<AlgoExecution> * listener) override;
    virtual const vector< ServiceListener<AlgoExecution> *>& GetListeners() const override;

    void GenerateOrder(OrderBook<Bond> & orderbook);
};

BondAlgoExecutionService::BondAlgoExecutionService() {
    algoexecutionMap=map<string, AlgoExecution>();
    listenersList=vector<ServiceListener<AlgoExecution> * >();
}

AlgoExecution& BondAlgoExecutionService::GetData(string key) {
    return algoexecutionMap[key];
}

void BondAlgoExecutionService::OnMessage(AlgoExecution &positionData) {}

void BondAlgoExecutionService::AddListener(ServiceListener<AlgoExecution> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<AlgoExecution> *>& BondAlgoExecutionService::GetListeners() const{
    return listenersList;
}

void BondAlgoExecutionService::GenerateOrder(OrderBook<Bond> & orderbook){
    auto id = orderbook.GetProduct().GetProductId();
    auto key = algoexecutionMap.find(id);
    if (key != algoexecutionMap.end()){
        if ((key->second).UpdateExecutionOrder(orderbook)){
            for (auto& l:listenersList) {l->ProcessAdd(key->second);}
        }
    }
    else {
        auto executionorder = ExecutionOrder<Bond>(orderbook.GetProduct(),BID, "0", FOK, 0.0, 0, 0.0, "P", false);
        algoexecutionMap.insert(pair<string, ExecutionOrder<Bond>>(id, executionorder));
        GenerateOrder(orderbook);
    }
}


#endif
