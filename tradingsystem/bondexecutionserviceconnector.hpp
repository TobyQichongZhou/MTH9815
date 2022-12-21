/**
 * bondexecutionserviceconnector.hpp
 * Publish execution data from BondExecutionService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_EXECUTION_SERVICE_CONNECTOR_HPP
#define BOND_EXECUTION_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondexecutionservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Execution Service Connector publishes execution data.
 */
class BondExecutionServiceConnector: public Connector<ExecutionOrder<Bond> > {

public:
	// ctor
	BondExecutionServiceConnector() {}

    //override all virtual functions
	virtual void Subscribe() override {};
	virtual void Publish(ExecutionOrder<Bond>& data) override ;
};

void BondExecutionServiceConnector::Publish(ExecutionOrder<Bond>& data) {
    auto bond=data.GetProduct();
	string odertype;
	switch(data.GetOrderType()) {
		case FOK: odertype = "FOK"; break;
		case MARKET: odertype = "MARKET"; break;
		case LIMIT: odertype = "LIMIT"; break;
		case STOP: odertype = "STOP"; break;
		case IOC: odertype = "IOC"; break; 
	}

	std::cout<<bond.GetProductId()<<" OrderId: "<<data.GetOrderId()<< "\n"
		<<"    PricingSide: "<<(data.GetSide()==BID? "Bid":"Ask")
		<<" OrderType: "<<odertype<<" IsChildOrder: "<<(data.IsChildOrder()?"True":"False")
		<<"\n"
		<<"    Price: "<<data.GetPrice()<<" VisibleQuantity: "<<data.GetVisibleQuantity()
		<<" HiddenQuantity: "<<data.GetHiddenQuantity()<<"\n"<<std::endl;	
}


void BondExecutionService::ExecuteOrder(const ExecutionOrder<Bond>& order, Market market) {
    auto id = order.GetProduct().GetProductId();
	executionordersMap.insert(pair<string, ExecutionOrder<Bond>>(id, order));

    for (auto& l:listenersList) {l->ProcessAdd(executionordersMap[id]);}
    connector->Publish(executionordersMap[id]);
}


#endif
