/**
 * guiservicelistener.hpp
 * Defines GUIServiceListener to listen data pasing to
 * GUIService
 * 
 * @author Qichong Zhou
 */
#ifndef GUI_SERVICE_LISTENER_HPP
#define GUI_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "guiservice.hpp"

/**
 * GUIServiceListener to listen data passing to GUI Servicing
 * from BondPricingService
 */
class GUIServiceListener: public ServiceListener<Price<Bond>> {

private:
    GUIService* gs;

public:
    //ctor
    GUIServiceListener(GUIService * _gs) {
        gs = _gs;
    }

    //override pure virtual functions
    virtual void ProcessAdd(Price<Bond>& data) override{
        gs->SendToThrotte(data);
    }

    virtual void ProcessRemove(Price<Bond>& data) override {}
    virtual void ProcessUpdate(Price<Bond>& data) override {}


};

#endif
