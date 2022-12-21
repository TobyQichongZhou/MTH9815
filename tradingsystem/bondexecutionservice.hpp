/**
 * bondexecutionservice.hpp
 * Manages execution information
 * Receive data and pass to BondTradeBookingService
 *
 * @author Qichong Zhou
 */
#ifndef BOND_EXECUTION_SERVICE_HPP
#define BOND_EXECUTION_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "executionservice.hpp"

class BondExecutionServiceConnector;

/**
 * Bond Execution Service to manage ExecutionOrderss across multiple books and bonds.
 * Keyed on product identifier.
 */
class BondExecutionService: public ExecutionService<Bond>{

private:
    map<string, ExecutionOrder<Bond>> executionordersMap;
    vector<ServiceListener<ExecutionOrder<Bond>> *> listenersList;
    BondExecutionServiceConnector* connector;


public:
    //ctor
    BondExecutionService(BondExecutionServiceConnector* _connector);

    //override all virtual functions
    virtual ExecutionOrder<Bond>& GetData(string key) override;
    virtual void OnMessage(ExecutionOrder<Bond> &executionorderData) override;
    virtual void AddListener(ServiceListener<ExecutionOrder<Bond>> * listener) override;
    virtual const vector< ServiceListener<ExecutionOrder<Bond>> *>& GetListeners() const override;
    virtual void ExecuteOrder(const ExecutionOrder<Bond>& order, Market market) override;
};

BondExecutionService::BondExecutionService(BondExecutionServiceConnector* _connector) {
    executionordersMap=map<string, ExecutionOrder<Bond>>();
    listenersList=vector<ServiceListener<ExecutionOrder<Bond>> * >();
    connector = _connector;
}

ExecutionOrder<Bond>& BondExecutionService::GetData(string key) {
    return executionordersMap[key];
}

void BondExecutionService::OnMessage(ExecutionOrder<Bond> &executionorderData) {}

void BondExecutionService::AddListener(ServiceListener<ExecutionOrder<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<ExecutionOrder<Bond>> *>& BondExecutionService::GetListeners() const{
    return listenersList;
}

#endif
