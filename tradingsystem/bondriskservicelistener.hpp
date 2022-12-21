/**
 * bondriskservicelistener.hpp
 * Defines BondRiskServiceListener to listen data pasing to
 * BondRiskService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_RISK_SERVICE_LISTENER_HPP
#define BOND_RISK_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondpositionservice.hpp"
#include "bondriskservice.hpp"

/**
 * BondRiskServiceListener to listen data passing to BondRisk Servicing
 * from BondPositionService
 */
class BondRiskServiceListener: public ServiceListener<Position<Bond> > {

private:
    BondRiskService* brs;

public:
    //ctor
    BondRiskServiceListener(BondRiskService * _brs) {
        brs = _brs;
    }

    //override pure virtual functions
    virtual void ProcessAdd(Position<Bond>& data) override{
        brs->AddPosition(data);
    }

    virtual void ProcessRemove(Position<Bond>& data) override {}
    virtual void ProcessUpdate(Position<Bond>& data) override {}


};

#endif
