/**
 * bongpricingservice.hpp
 * Defines the data types and Service for bond internal prices.
 *
 * @author Qichong Zhou
 */
#ifndef BOND_PRICING_SERVICE_HPP
#define BOND_PRICING_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "pricingservice.hpp"

/**
 * Bond Pricing Service managing mid prices and bid/offers.
 * Keyed on product identifier.
 */
class BondPricingService: public PricingService<Bond>{

private:
    map<string, Price<Bond> > pricesMap;
    vector<ServiceListener<Price<Bond>> *> listenersList;

public:
    //ctor
    BondPricingService();

    //override all virtual functions
    virtual Price<Bond>& GetData(string key) override;
    virtual void OnMessage(Price<Bond> &priceData) override;
    virtual void AddListener(ServiceListener<Price<Bond>> * listener) override;
    virtual const vector< ServiceListener<Price<Bond>> *>& GetListeners() const override;
};


BondPricingService::BondPricingService() {
    pricesMap=map<string, Price<Bond>>();
    listenersList=vector<ServiceListener<Price<Bond>> * >();
}

Price<Bond>& BondPricingService::GetData(string key) {
    return pricesMap[key];
}

void BondPricingService::OnMessage(Price<Bond> &priceData) {
    string key=priceData.GetProduct().GetProductId();
    if (pricesMap.find(key) != pricesMap.end()) {
        pricesMap.erase(key);
    }
    pricesMap.insert(pair<string, Price<Bond>> (key, priceData));

    for (auto& l:listenersList) {l->ProcessAdd(priceData);}
}

void BondPricingService::AddListener(ServiceListener<Price<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<Price<Bond>> *>& BondPricingService::GetListeners() const{
    return listenersList;
}

#endif
