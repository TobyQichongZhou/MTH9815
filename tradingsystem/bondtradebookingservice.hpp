/**
 * bondtradebookingservice.hpp
 * Receive data and pass to BondPositionService
 *
 * @author Qichong Zhou
 */
#ifndef BOND_TRADE_BOOKING_SERVICE_HPP
#define BOND_TRADE_BOOKING_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "tradebookingservice.hpp"

/**
 * Bond Trade Booking Service to book Bond trades.
 * Keyed on trade id.
 */
class BondTradeBookingService: public TradeBookingService<Bond>{

private:
    map<string, Trade<Bond> > tradesMap;
    vector<ServiceListener<Trade<Bond>> *> listenersList;

public:
    //ctor
    BondTradeBookingService();

    //override all virtual functions
    virtual Trade<Bond>& GetData(string key) override;
    virtual void OnMessage(Trade<Bond> &tradeData) override;
    virtual void AddListener(ServiceListener<Trade<Bond>> * listener) override;
    virtual const vector< ServiceListener<Trade<Bond>> *>& GetListeners() const override;
    virtual void BookTrade(Trade<Bond> &trade) override;
};


BondTradeBookingService::BondTradeBookingService() {
    tradesMap=map<string, Trade<Bond>>();
    listenersList=vector<ServiceListener<Trade<Bond>> * >();
}

Trade<Bond>& BondTradeBookingService::GetData(string key) {
    return tradesMap[key];
}

void BondTradeBookingService::OnMessage(Trade<Bond> &tradeData) {
    string key=tradeData.GetProduct().GetProductId();
    if (tradesMap.find(key) != tradesMap.end()) {
        tradesMap.erase(key);
    }
    tradesMap.insert(pair<string, Trade<Bond>> (key, tradeData));

    for (auto& l:listenersList) {l->ProcessAdd(tradeData);}
}

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<Trade<Bond>> *>& BondTradeBookingService::GetListeners() const{
    return listenersList;
}

void BondTradeBookingService::BookTrade(Trade<Bond> &trade) {
    OnMessage(trade);
}

#endif
