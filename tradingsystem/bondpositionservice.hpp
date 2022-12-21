/**
 * bondpositionservice.hpp
 * Manages position information
 * Receive data and pass to BondRiskService
 *
 * @author Qichong Zhou
 */
#ifndef BOND_POSITION_SERVICE_HPP
#define BOND_POSITION_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "positionservice.hpp"

/**
 * Bond Position Service to manage positions across multiple books and bonds.
 * Keyed on product identifier.
 */
class BondPositionService: public PositionService<Bond>{

private:
    map<string, Position<Bond> > positionsMap;
    vector<ServiceListener<Position<Bond>> *> listenersList;

public:
    //ctor
    BondPositionService();

    //override all virtual functions
    virtual Position<Bond>& GetData(string key) override;
    virtual void OnMessage(Position<Bond> &positionData) override;
    virtual void AddListener(ServiceListener<Position<Bond>> * listener) override;
    virtual const vector< ServiceListener<Position<Bond>> *>& GetListeners() const override;
    virtual void AddTrade(const Trade<Bond> &trade) override;
};


BondPositionService::BondPositionService() {
    positionsMap=map<string, Position<Bond>>();
    listenersList=vector<ServiceListener<Position<Bond>> * >();
}

Position<Bond>& BondPositionService::GetData(string key) {
    return positionsMap[key];
}

void BondPositionService::OnMessage(Position<Bond> &positionData) {}

void BondPositionService::AddListener(ServiceListener<Position<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<Position<Bond>> *>& BondPositionService::GetListeners() const{
    return listenersList;
}

void BondPositionService::AddTrade(const Trade<Bond> &trade) {
    auto bond = trade.GetProduct();
    auto id = bond.GetProductId();
    auto quantity = trade.GetSide() == BUY? trade.GetQuantity():-trade.GetQuantity();
    
    auto key = positionsMap.find(id);
    if (key!=positionsMap.end()) {
        (key->second).AddPosition(trade.GetBook(), quantity);
        for (auto& l:listenersList) {l->ProcessAdd(key->second);}
    }
    else {
        positionsMap.insert(pair<string, Position<Bond>> (id, Position<Bond>(bond)));
        AddTrade(trade);
    }
}

#endif
