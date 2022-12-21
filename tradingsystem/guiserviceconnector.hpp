/**
 * guiserviceconnector.hpp
 * Publish data from GUIService.
 *
 * @author Qichong Zhou
 */

#ifndef GUI_SERVICE_CONNECTOR_HPP
#define GUI_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "guiservice.hpp"


/**
 * GUI Service Connector publishes gui data.
 */
class GUIServiceConnector: public Connector<PriceWithTime > {

public:
	// ctor
	GUIServiceConnector() {}

    //override all virtual functions
	virtual void Subscribe() override {};
	virtual void Publish(PriceWithTime& data) override ;
};

void GUIServiceConnector::Publish(PriceWithTime& data) {
    auto timeStamp=data.GetTimeStamp();
	auto bond=data.GetProduct();
	auto mid=data.GetMid();
	auto spread=data.GetBidOfferSpread();
	
    ofstream out;
    out.open("gui.txt",ios::app);
	out<<timeStamp<<","<<bond.GetProductId()<<","<<mid<<","<<spread<<endl;

}

void GUIService::SendToThrotte(Price<Bond>& data){
    auto newTime = boost::posix_time::microsec_clock::local_time();
    auto duration = newTime - lastTime;
    if (duration >= throtteTime){
        lastTime=newTime;
        auto temp = PriceWithTime(newTime, data);
        connector->Publish(temp);
    }
}


#endif
