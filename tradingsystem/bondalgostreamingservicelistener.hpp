/**
 * bondalgostreamingservicelistener.hpp
 * Defines BondAlgoStreamingServiceListener to listen data pasing to
 * BondAlgoStreamingService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP
#define BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondalgostreamingservice.hpp"
#include "BondPricingService.hpp"

/**
 * BondAlgoStreamingServiceListener to listen data passing to BondAlgoStreaming Servicing
 * from BondPricingService
 */
class BondAlgoStreamingServiceListener: public ServiceListener<Price<Bond> > {

private:
    BondAlgoStreamingService* bass;

public:
    //ctor
    BondAlgoStreamingServiceListener(BondAlgoStreamingService * _bass) {
        bass = _bass;
    }

    //override pure virtual functions
    virtual void ProcessAdd(Price<Bond>& data) override{
        bass->GeneratePriceStream(data);
    }

    virtual void ProcessRemove(Price<Bond>& data) override {}
    virtual void ProcessUpdate(Price<Bond>& data) override {}


};

#endif
