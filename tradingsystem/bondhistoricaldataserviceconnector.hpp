/**
 * bondhistoricaldataserviceconnector.hpp
 * Publish all required historical data.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_HISTORICAL_DATA_SERVICE_CONNECTOR_HPP
#define BOND_HISTORICAL_DATA_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "soa.hpp"
#include "products.hpp"
#include "bondhistoricaldataservice.hpp"

using namespace std;


class BondHistoricalPositionServiceConnector: public Connector<Position<Bond> >{
public:
    // ctor
    BondHistoricalPositionServiceConnector(){};

    //override all virtual functions
	virtual void Subscribe() override{}
	virtual void Publish(Position<Bond>& data) override{
        auto bond=data.GetProduct();
        auto data_needed=data.GetAggregatePosition();
        
        ofstream out;
        out.open("positions.txt",ios::app);
        out<<bond.GetProductId()<<","<<data_needed<<endl;
    }
};

void BondHistoricalPositionService::PersistData(string persistKey, const Position<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
    dataMap.insert(pair<string, Position<Bond>>(id, data));
	connector->Publish(dataMap[id]);
}



class BondHistoricalRiskServiceConnector: public Connector<PV01<Bond> >{
public:
    // ctor
    BondHistoricalRiskServiceConnector(){};

    //override all virtual functions
	virtual void Subscribe() override{}
	virtual void Publish(PV01<Bond>& data) override{
        auto bond=data.GetProduct();
        auto data_needed=data.GetPV01();
        
        ofstream out;
        out.open("risk.txt",ios::app);
        out<<bond.GetProductId()<<","<<data_needed<<endl;
    }
};

void BondHistoricalRiskService::PersistData(string persistKey, const PV01<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
    dataMap.insert(pair<string, PV01<Bond>>(id, data));
	connector->Publish(dataMap[id]);
}



class BondHistoricalExecutionServiceConnector: public Connector<ExecutionOrder<Bond> >{
public:
    // ctor
    BondHistoricalExecutionServiceConnector(){};

    //override all virtual functions
	virtual void Subscribe() override{}
	virtual void Publish(ExecutionOrder<Bond>& data) override{
        auto bond=data.GetProduct();
        string oderType;
        switch(data.GetOrderType()) {
            case FOK: oderType = "FOK"; break;
            case MARKET: oderType = "MARKET"; break;
            case LIMIT: oderType = "LIMIT"; break;
            case STOP: oderType = "STOP"; break;
            case IOC: oderType = "IOC"; break; 
        }
        
        ofstream out;
        out.open("executions.txt",ios::app);
        out<<bond.GetProductId()<<","<<data.GetOrderId()
            <<","<<(data.GetSide()==BID? "Bid":"Ask")
            <<","<<oderType<<","<<(data.IsChildOrder()? "True":"False")
            <<","<<data.GetPrice()
            <<","<<data.GetVisibleQuantity()
            <<","<<data.GetHiddenQuantity()<<endl;
    }
};

void BondHistoricalExecutionService::PersistData(string persistKey, const ExecutionOrder<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
    dataMap.insert(pair<string, ExecutionOrder<Bond>>(id, data));
	connector->Publish(dataMap[id]);
}




class BondHistoricalStreamingServiceConnector: public Connector<PriceStream<Bond> >{
public:
    // ctor
    BondHistoricalStreamingServiceConnector(){};

    //override all virtual functions
	virtual void Subscribe() override{}
	virtual void Publish(PriceStream<Bond>& data) override{
        auto bond = data.GetProduct();
        auto bid = data.GetBidOrder();
        auto offer = data.GetOfferOrder();
        
        ofstream out;
        out.open("streaming.txt",ios::app);
        out<<bond.GetProductId()<<","
            <<bid.GetPrice()<<","<<bid.GetVisibleQuantity()
            <<","<<bid.GetHiddenQuantity()
            <<","<<offer.GetPrice()<<","<<offer.GetVisibleQuantity()
            <<","<<offer.GetHiddenQuantity()
            <<endl;
    }
};

void BondHistoricalStreamingService::PersistData(string persistKey, const PriceStream<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
    dataMap.insert(pair<string, PriceStream<Bond>>(id, data));
	connector->Publish(dataMap[id]);
}




class BondHistoricalInquiryServiceConnector: public Connector<Inquiry<Bond> >{
public:
    // ctor
    BondHistoricalInquiryServiceConnector(){};

    //override all virtual functions
	virtual void Subscribe() override{}
	virtual void Publish(Inquiry<Bond>& data) override{
        auto inquiry_id=data.GetInquiryId();
        auto id=data.GetProduct().GetProductId();
        auto price=data.GetPrice();
        auto quantity=data.GetQuantity();
        string side=(data.GetSide()==BUY? "BUY":"SELL");
        string state_;
        switch(data.GetState()){
            case RECEIVED:state_="RECEIVED";break;
            case QUOTED:state_="QUOTED";break;
            case DONE:state_="DONE";break;
            case REJECTED:state_="REJECTED";break;
            case CUSTOMER_REJECTED:state_="CUSTOMER_REJECTED";break;
        }

        ofstream out;
        out.open("allinquiries.txt",ios::app);
        out<<inquiry_id<<","<<id<<","<<price<<","<<quantity<<","<<side<<","<<state_
            <<endl;
    }
};

void BondHistoricalInquiryService::PersistData(string persistKey, const Inquiry<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
    dataMap.insert(pair<string, Inquiry<Bond>>(id, data));
	connector->Publish(dataMap[id]);
}

#endif
