/**
 * bondstreamingservice.hpp
 * Manages streaming information
 * Receive data and pass to BondTradeBookingService
 *
 * @author Qichong Zhou
 */
#ifndef BOND_STREAMING_SERVICE_HPP
#define BOND_STREAMING_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "streamingservice.hpp"

class BondStreamingServiceConnector;

/**
 * Bond Streaming Service to manage bid&offer info across multiple books and bonds.
 * Keyed on product identifier.
 */
class BondStreamingService: public StreamingService<Bond>{

private:
    map<string, PriceStream<Bond>> pricestreamsMap;
    vector<ServiceListener<PriceStream<Bond>> *> listenersList;
    BondStreamingServiceConnector* connector;

public:
    //ctor
    BondStreamingService(BondStreamingServiceConnector* _connector);

    //override all virtual functions
    virtual PriceStream<Bond>& GetData(string key) override;
    virtual void OnMessage(PriceStream<Bond> &pricestreamData) override;
    virtual void AddListener(ServiceListener<PriceStream<Bond>> * listener) override;
    virtual const vector< ServiceListener<PriceStream<Bond>> *>& GetListeners() const override;
    virtual void PublishPrice(const PriceStream<Bond>& pricestreamData) override;
};


BondStreamingService::BondStreamingService(BondStreamingServiceConnector* _connector) {
    pricestreamsMap=map<string, PriceStream<Bond>>();
    listenersList=vector<ServiceListener<PriceStream<Bond>> * >();
    connector=_connector;
}

PriceStream<Bond>& BondStreamingService::GetData(string key) {
    return pricestreamsMap[key];
}

void BondStreamingService::OnMessage(PriceStream<Bond> &pricestreamData) {}

void BondStreamingService::AddListener(ServiceListener<PriceStream<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<PriceStream<Bond>> *>& BondStreamingService::GetListeners() const{
    return listenersList;
}

#endif
