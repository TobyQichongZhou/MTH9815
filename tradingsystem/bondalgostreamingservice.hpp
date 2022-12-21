/**
 * bondalgostreamingservice.hpp
 * Defines BondAlgoStreamingService class that manages all info of trading algo running
 *
 * @author Qichong Zhou
 */
#ifndef BOND_ALGO_STREAMING_SERVICE_HPP
#define BOND_ALGO_STREAMING_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "algostream.hpp"
#include "soa.hpp"

/**
 * Bond Algo Streaming Service to manage price streams across multiple and bonds.
 * Keyed on product identifier.
 */
class BondAlgoStreamingService: Service<string, AlgoStream>{

private:
    map<string, AlgoStream> algostreamMap;
    vector<ServiceListener<AlgoStream> *> listenersList;

public:
    //ctor
    BondAlgoStreamingService();

    //override all virtual functions
    virtual AlgoStream& GetData(string key) override;
    virtual void OnMessage(AlgoStream &algostream) override;
    virtual void AddListener(ServiceListener<AlgoStream> * listener) override;
    virtual const vector< ServiceListener<AlgoStream> *>& GetListeners() const override;

    void GeneratePriceStream(Price<Bond>& price);
};

BondAlgoStreamingService::BondAlgoStreamingService() {
    algostreamMap=map<string, AlgoStream>();
    listenersList=vector<ServiceListener<AlgoStream> * >();
}

AlgoStream& BondAlgoStreamingService::GetData(string key) {
    return algostreamMap[key];
}

void BondAlgoStreamingService::OnMessage(AlgoStream &positionData) {}

void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<AlgoStream> *>& BondAlgoStreamingService::GetListeners() const{
    return listenersList;
}

void BondAlgoStreamingService::GeneratePriceStream(Price<Bond>& price){
    auto id = price.GetProduct().GetProductId();
    auto key = algostreamMap.find(id);
    if (key != algostreamMap.end()){
        (key->second).UpdatePriceStream(price);
        for (auto& l:listenersList) {l->ProcessAdd(key->second);}
    }
    else {
        auto bid = PriceStreamOrder(0,0,0,BID);
        auto offer = PriceStreamOrder(0,0,0,OFFER);
        auto pricestream = PriceStream<Bond>(price.GetProduct(), bid, offer);
        algostreamMap.insert(pair<string, PriceStream<Bond>>(id, pricestream));
        GeneratePriceStream(price);
    }
}

#endif
