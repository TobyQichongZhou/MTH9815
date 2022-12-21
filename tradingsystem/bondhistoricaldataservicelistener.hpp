/**
 * bondhistoricaldataservicelistener.hpp
 * Defines service listeners to feed data to BondHistoricalDataService
 * 
 * @author Qichong Zhou
 */
#ifndef BOND_HISTORICAL_DATA_SERVICE_LISTENER_HPP
#define BOND_HISTORICAL_DATA_SERVICE_LISTENER_HPP

#include <string>
#include "soa.hpp"
#include "bondhistoricaldataservice.hpp"

class BondHistoricalPositionServiceListener : public ServiceListener<Position<Bond> > {
private:
	BondHistoricalPositionService* s;

public:
	// ctor
	BondHistoricalPositionServiceListener(BondHistoricalPositionService * _s):s(_s){}

    //override all virtual functions
	virtual void ProcessAdd(Position<Bond> &data) override{
		s->PersistData(data.GetProduct().GetProductId(),data);
	} 
	virtual void ProcessRemove(Position<Bond> &data) override{} 
	virtual void ProcessUpdate(Position<Bond> &data) override{}
};

class BondHistoricalRiskServiceListener : public ServiceListener<PV01<Bond> > {
private:
	BondHistoricalRiskService* s;

public:
	// ctor
	BondHistoricalRiskServiceListener(BondHistoricalRiskService * _s):s(_s){}

    //override all virtual functions
	virtual void ProcessAdd(PV01<Bond> &data) override{
		s->PersistData(data.GetProduct().GetProductId(),data);
	} 
	virtual void ProcessRemove(PV01<Bond> &data) override{} 
	virtual void ProcessUpdate(PV01<Bond> &data) override{}
};

class BondHistoricalExecutionServiceListener : public ServiceListener<ExecutionOrder<Bond> > {
private:
	BondHistoricalExecutionService* s;

public:
	// ctor
	BondHistoricalExecutionServiceListener(BondHistoricalExecutionService * _s):s(_s){}

    //override all virtual functions
	virtual void ProcessAdd(ExecutionOrder<Bond> &data) override{
		s->PersistData(data.GetProduct().GetProductId(),data);
	} 
	virtual void ProcessRemove(ExecutionOrder<Bond> &data) override{} 
	virtual void ProcessUpdate(ExecutionOrder<Bond> &data) override{}
};

class BondHistoricalStreamingServiceListener : public ServiceListener<PriceStream<Bond> > {
private:
	BondHistoricalStreamingService* s;

public:
	// ctor
	BondHistoricalStreamingServiceListener(BondHistoricalStreamingService * _s):s(_s){}

    //override all virtual functions
	virtual void ProcessAdd(PriceStream<Bond> &data) override{
		s->PersistData(data.GetProduct().GetProductId(),data);
	} 
	virtual void ProcessRemove(PriceStream<Bond> &data) override{} 
	virtual void ProcessUpdate(PriceStream<Bond> &data) override{}
};

class BondHistoricalInquiryServiceListener : public ServiceListener<Inquiry<Bond> > {
private:
	BondHistoricalInquiryService* s;

public:
	// ctor
	BondHistoricalInquiryServiceListener(BondHistoricalInquiryService * _s):s(_s){}

    //override all virtual functions
	virtual void ProcessAdd(Inquiry<Bond> &data) override{
		s->PersistData(data.GetProduct().GetProductId(),data);
	} 
	virtual void ProcessRemove(Inquiry<Bond> &data) override{} 
	virtual void ProcessUpdate(Inquiry<Bond> &data) override{}
};

#endif
