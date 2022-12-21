/**
 * bondmarketdataservice.hppPOSITION
 * Manages marketdata information
 *
 * @author Qichong Zhou
 */
#ifndef BOND_MARKET_DATA_SERVICE_HPP
#define BOND_MARKET_DATA_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "marketdataservice.hpp"
#include "bondinfo.h"

/**
 * Market Data Service which distributes market data
 * Keyed on product identifier.
 */
class BondMarketDataService: public MarketDataService<Bond>{

private:
    map<string, OrderBook<Bond> > orderbooksMap;
    vector<ServiceListener<OrderBook<Bond>> *> listenersList;

public:
    //ctor
    BondMarketDataService();

    //override all virtual functions
    virtual OrderBook<Bond>& GetData(string key) override;
    virtual void OnMessage(OrderBook<Bond> &orderbook) override;
    virtual void AddListener(ServiceListener<OrderBook<Bond>> * listener) override;
    virtual const vector< ServiceListener<OrderBook<Bond>> *>& GetListeners() const override;
    virtual BidOffer GetBestBidOffer(const string &productId) override;
    virtual OrderBook<Bond> AggregateDepth(const string &productId) override;
};


BondMarketDataService::BondMarketDataService() {
    orderbooksMap=map<string, OrderBook<Bond>>();
    listenersList=vector<ServiceListener<OrderBook<Bond>> * >();
}

OrderBook<Bond>& BondMarketDataService::GetData(string key) {
    return orderbooksMap[key];
}

void BondMarketDataService::OnMessage(OrderBook<Bond> &orderbook) {
    auto id = orderbook.GetProduct().GetProductId();
    if(orderbooksMap.find(id)!=orderbooksMap.end()){
        orderbooksMap.erase(id);
    }
    orderbooksMap.insert(pair<string, OrderBook<Bond>>(id, orderbook));

    auto best = GetBestBidOffer(id);
    vector<Order> bids, offers;
    bids.push_back(best.GetBidOrder());
    offers.push_back(best.GetOfferOrder());
    auto bestbook = OrderBook<Bond>(orderbook.GetProduct(), bids, offers);

    for (auto& l:listenersList) {l->ProcessAdd(bestbook);}
}

void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<OrderBook<Bond>> *>& BondMarketDataService::GetListeners() const{
    return listenersList;
}

BidOffer BondMarketDataService::GetBestBidOffer(const string &productId) {
    auto bids = orderbooksMap[productId].GetBidStack();
    auto bestbid = bids[0];
    for (auto& bid:bids) {bestbid = bestbid.GetPrice()<bid.GetPrice()? bid:bestbid;}

    auto offers = orderbooksMap[productId].GetOfferStack();
    auto bestoffer = offers[0];
    for (auto& offer:offers) {bestoffer = bestoffer.GetPrice()>offer.GetPrice()? offer:bestoffer;}

    return BidOffer(bestbid, bestoffer);
}

OrderBook<Bond> BondMarketDataService::AggregateDepth(const string &productId){
    auto bids = orderbooksMap[productId].GetBidStack();
    map<double,long> bidmap;
    for (auto& bid:bids){
        if(bidmap.find(bid.GetPrice())==bidmap.end()){bidmap[bid.GetPrice()]=0;}
        bidmap[bid.GetPrice()] += bid.GetQuantity();
    }
    vector<Order> bids_aggregated;
    for (auto& bid:bidmap) {bids_aggregated.push_back(Order(bid.first, bid.second, BID));}

    auto offers = orderbooksMap[productId].GetOfferStack();
    map<double,long> offermap;
    for (auto& offer:offers){
        if(offermap.find(offer.GetPrice())==offermap.end()){offermap[offer.GetPrice()]=0;}
        offermap[offer.GetPrice()] += offer.GetQuantity();
    }
    vector<Order> offers_aggregated;
    for (auto& offer:offermap) {offers_aggregated.push_back(Order(offer.first, offer.second, OFFER));}

    return OrderBook<Bond>(orderbooksMap[productId].GetProduct(), bids_aggregated, offers_aggregated);
}

#endif
