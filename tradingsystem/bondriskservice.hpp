/**
 * bondriskservice.hpp
 * Manages risk information
 *
 * @author Qichong Zhou
 */
#ifndef BOND_RISK_SERVICE_HPP
#define BOND_RISK_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "riskservice.hpp"
#include "bondinfo.h"

/**
 * Risk Service to vend out risk for a particular bond and across a risk bucketed sector.
 * Keyed on product identifier.
 */
class BondRiskService: public RiskService<Bond>{

private:
    map<string, PV01<Bond> > pv01Map;
    vector<ServiceListener<PV01<Bond>> *> listenersList;

public:
    //ctor
    BondRiskService();

    //override all virtual functions
    virtual PV01<Bond>& GetData(string key) override;
    virtual void OnMessage(PV01<Bond> &pv01) override;
    virtual void AddListener(ServiceListener<PV01<Bond>> * listener) override;
    virtual const vector< ServiceListener<PV01<Bond>> *>& GetListeners() const override;
    virtual void AddPosition(Position<Bond> &position) override;
    virtual double GetBucketedRisk(const BucketedSector<Bond> &sector) const override;
};


BondRiskService::BondRiskService() {
    pv01Map=map<string, PV01<Bond>>();
    listenersList=vector<ServiceListener<PV01<Bond>> * >();
}

PV01<Bond>& BondRiskService::GetData(string key) {
    return pv01Map[key];
}

void BondRiskService::OnMessage(PV01<Bond> &pv01) {}

void BondRiskService::AddListener(ServiceListener<PV01<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<PV01<Bond>> *>& BondRiskService::GetListeners() const{
    return listenersList;
}

void BondRiskService::AddPosition(Position<Bond> &position) {
    auto bond = position.GetProduct();
    auto id = bond.GetProductId();
    auto quantity = position.GetAggregatePosition();
    
    auto key = pv01Map.find(id);
    if (key!=pv01Map.end()) {
        (key->second).AddQuantity(quantity);
    }
    else {
        pv01Map.insert(pair<string, PV01<Bond>> (id, PV01<Bond>(bond, bondRisk[id], quantity)));
    }
    key = pv01Map.find(id);

    for (auto& l:listenersList) {l->ProcessAdd(key->second);}
}

double BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector) const {
    double ret = 0.0;
    for (auto& p : sector.GetProducts()) {
        ret += pv01Map.find(p.GetProductId())!=pv01Map.end()? pv01Map.at(p.GetProductId()).GetPV01():0.0;
    }
    return ret;
}

#endif
