/**
 * bondstreamingservicelistener.hpp
 * Defines BondStreamingServiceListener to listen data pasing to
 * BondStreamingService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_STREAMING_SERVICE_LISTENER_HPP
#define BOND_STREAMING_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondstreamingservice.hpp"
#include "bondalgostreamingservice.hpp"

/**
 * BondStreamingServiceListener to listen data passing to BondStreaming Servicing
 * from BondAlgoStreamingService
 */
class BondStreamingServiceListener: public ServiceListener<AlgoStream> {

private:
    BondStreamingService* bss;

public:
    //ctor
    BondStreamingServiceListener(BondStreamingService * _bss) {
        bss = _bss;
    }

    //override pure virtual functions
    virtual void ProcessAdd(AlgoStream& data) override{
        auto pricestream = data.GetPriceStream();

        bss->PublishPrice(pricestream);
    }

    virtual void ProcessRemove(AlgoStream& data) override {}
    virtual void ProcessUpdate(AlgoStream& data) override {}


};

#endif
