/**
 * bondhistoricaldataservice.hpp
 * Manages historicaldata information
 * Receive and persist data
 *
 * @author Qichong Zhou
 */
#ifndef BOND_HISTORICAL_DATA_SERVICE_HPP
#define BOND_HISTORICAL_DATA_SERVICE_HPP

#include <iostream>
#include "historicaldataservice.hpp"
#include "bondpositionservice.hpp"
#include "bondriskservice.hpp"
#include "bondexecutionservice.hpp"
#include "bondstreamingservice.hpp"
#include "bondinquiryservice.hpp"

class BondHistoricalPositionServiceConnector;
class BondHistoricalRiskServiceConnector;
class BondHistoricalExecutionServiceConnector;
class BondHistoricalStreamingServiceConnector;
class BondHistoricalInquiryServiceConnector;

class BondHistoricalPositionService: public HistoricalDataService<Position<Bond> > {
private:
    map<string, Position<Bond> > dataMap;
	BondHistoricalPositionServiceConnector* connector;
	vector<ServiceListener<Position<Bond> > *> listenersList;
public:
	// ctor
	BondHistoricalPositionService(BondHistoricalPositionServiceConnector* _connector):connector(_connector){
		listenersList = vector<ServiceListener<Position<Bond> > *>();
	}

	//override all virtual functions
	virtual Position<Bond>  & GetData(string id) override {return dataMap.at(id);}
	virtual void OnMessage(Position<Bond>  & data) override {}
	virtual void AddListener(ServiceListener<Position<Bond>  > *listener) override {}
	virtual const vector<ServiceListener<Position<Bond>  > *>& GetListeners() const override {return listenersList;}
	virtual void PersistData(string persistKey, const Position<Bond>& data) override;
};

class BondHistoricalRiskService: public HistoricalDataService<PV01<Bond> > {
private:
    map<string, PV01<Bond> > dataMap;
	BondHistoricalRiskServiceConnector* connector;
	vector<ServiceListener<PV01<Bond> > *> listenersList;
public:
	// ctor
	BondHistoricalRiskService(BondHistoricalRiskServiceConnector* _connector):connector(_connector){
		listenersList = vector<ServiceListener<PV01<Bond> > *>();
	}

	//override all virtual functions
	virtual PV01<Bond>  & GetData(string id) override {return dataMap.at(id);}
	virtual void OnMessage(PV01<Bond>  & data) override {}
	virtual void AddListener(ServiceListener<PV01<Bond>  > *listener) override {}
	virtual const vector<ServiceListener<PV01<Bond>  > *>& GetListeners() const override {return listenersList;}
	virtual void PersistData(string persistKey, const PV01<Bond>& data) override;
};

class BondHistoricalExecutionService: public HistoricalDataService<ExecutionOrder<Bond> > {
private:
    map<string, ExecutionOrder<Bond> > dataMap;
	BondHistoricalExecutionServiceConnector* connector;
	vector<ServiceListener<ExecutionOrder<Bond> > *> listenersList;
public:
	// ctor
	BondHistoricalExecutionService(BondHistoricalExecutionServiceConnector* _connector):connector(_connector){
		listenersList = vector<ServiceListener<ExecutionOrder<Bond> > *>();
	}

	//override all virtual functions
	virtual ExecutionOrder<Bond>  & GetData(string id) override {return dataMap.at(id);}
	virtual void OnMessage(ExecutionOrder<Bond>  & data) override {}
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>  > *listener) override {}
	virtual const vector<ServiceListener<ExecutionOrder<Bond>  > *>& GetListeners() const override {return listenersList;}
	virtual void PersistData(string persistKey, const ExecutionOrder<Bond>& data) override;
};

class BondHistoricalStreamingService: public HistoricalDataService<PriceStream<Bond> > {
private:
    map<string, PriceStream<Bond> > dataMap;
	BondHistoricalStreamingServiceConnector* connector;
	vector<ServiceListener<PriceStream<Bond> > *> listenersList;
public:
	// ctor
	BondHistoricalStreamingService(BondHistoricalStreamingServiceConnector* _connector):connector(_connector){
		listenersList = vector<ServiceListener<PriceStream<Bond> > *>();
	}

	//override all virtual functions
	virtual PriceStream<Bond>  & GetData(string id) override {return dataMap.at(id);}
	virtual void OnMessage(PriceStream<Bond>  & data) override {}
	virtual void AddListener(ServiceListener<PriceStream<Bond>  > *listener) override {}
	virtual const vector<ServiceListener<PriceStream<Bond>  > *>& GetListeners() const override {return listenersList;}
	virtual void PersistData(string persistKey, const PriceStream<Bond>& data) override;
};

class BondHistoricalInquiryService: public HistoricalDataService<Inquiry<Bond> > {
private:
    map<string, Inquiry<Bond> > dataMap;
	BondHistoricalInquiryServiceConnector* connector;
	vector<ServiceListener<Inquiry<Bond> > *> listenersList;
public:
	// ctor
	BondHistoricalInquiryService(BondHistoricalInquiryServiceConnector* _connector):connector(_connector){
		listenersList = vector<ServiceListener<Inquiry<Bond> > *>();
	}

	//override all virtual functions
	virtual Inquiry<Bond>  & GetData(string id) override {return dataMap.at(id);}
	virtual void OnMessage(Inquiry<Bond>  & data) override {}
	virtual void AddListener(ServiceListener<Inquiry<Bond>  > *listener) override {}
	virtual const vector<ServiceListener<Inquiry<Bond>  > *>& GetListeners() const override {return listenersList;}
	virtual void PersistData(string persistKey, const Inquiry<Bond>& data) override;
};

#endif
