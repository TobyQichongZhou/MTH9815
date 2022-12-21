/**
 * bondstreamingserviceconnector.hpp
 * Publish price stream data from BondStreamingService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_STREAMING_SERVICE_CONNECTOR_HPP
#define BOND_STREAMING_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondstreamingservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Streaming Service Connector publishes price stream data.
 */
class BondStreamingServiceConnector: public Connector<PriceStream<Bond> > {

public:
	// ctor
	BondStreamingServiceConnector() {}

    //override all virtual functions
	virtual void Subscribe() override {};
	virtual void Publish(PriceStream<Bond>& data) override ;
};

void BondStreamingServiceConnector::Publish(PriceStream<Bond>& data) {
    auto bond = data.GetProduct();
    auto bid = data.GetBidOrder();
    auto offer = data.GetOfferOrder();
	
    std::cout<<bond.GetProductId()<<"\n"
		<<"    bid: "<<"Price: "<<bid.GetPrice()<<"  VisibleQuantity: "<<bid.GetVisibleQuantity()
		<<"  HiddenQuantity: "<<bid.GetHiddenQuantity()<<"\n"
		<<"    offerOrder: "<<"Price: "<<offer.GetPrice()<<"  VisibleQuantity: "<<offer.GetVisibleQuantity()
		<<"  HiddenQuantity: "<<offer.GetHiddenQuantity()<<"\n"
		<<std::endl;
}


void BondStreamingService::PublishPrice(const PriceStream<Bond>& pricestreamData) {
    auto id = pricestreamData.GetProduct().GetProductId();
    pricestreamsMap.insert(pair<string, PriceStream<Bond>>(id, pricestreamData));

    for (auto& l:listenersList) {l->ProcessAdd(pricestreamsMap[id]);}
    connector->Publish(pricestreamsMap[id]);
}


#endif
