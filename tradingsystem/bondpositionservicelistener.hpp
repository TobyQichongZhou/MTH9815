/**
 * bondpositionservicelistener.hpp
 * Defines BondPositionServiceListener to listen data pasing to
 * BondPositionService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_POSITION_SERVICE_LISTENER_HPP
#define BOND_POSITION_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondpositionservice.hpp"
#include "bondtradebookingservice.hpp"

/**
 * BondPositionServiceListener to listen data passing to BondPosition Servicing
 * from BondTradeBookingService
 */
class BondPositionServiceListener: public ServiceListener<Trade<Bond> > {

private:
    BondPositionService* bps;

public:
    //ctor
    BondPositionServiceListener(BondPositionService * _bps) {
        bps = _bps;
    }

    //override pure virtual functions
    virtual void ProcessAdd(Trade<Bond>& data) override{
        bps->AddTrade(data);
    }

    virtual void ProcessRemove(Trade<Bond>& data) override {}
    virtual void ProcessUpdate(Trade<Bond>& data) override {}


};

#endif
