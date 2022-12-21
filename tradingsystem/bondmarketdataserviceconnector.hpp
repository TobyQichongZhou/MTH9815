/**
 * bondmarketdataserviceconnector.hpp
 * Fetches outside market data feeding into BondMarketDataService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP
#define BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondmarketdataservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Market Data Service Connector fecthes market data.
 */
class BondMarketDataServiceConnector: public Connector<OrderBook<Bond> > {
private:
    BondMarketDataService* bmds;
    BondProductService* products;

	// transform a string to price
	double StringToPrice(string& s);
public:
	// ctor
	BondMarketDataServiceConnector(BondMarketDataService* _bmds,BondProductService* _products);

    //override all virtual functions
	virtual void Subscribe() override;
	virtual void Publish(OrderBook<Bond>& data) override {};
};

double BondMarketDataServiceConnector::StringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondMarketDataServiceConnector::BondMarketDataServiceConnector(BondMarketDataService* _bmds,BondProductService* _products) {
	bmds = _bmds;
	products = _products;
}

void BondMarketDataServiceConnector::Subscribe() {
	ifstream input;
	input.open("marketdata.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		vector<Order> bids,offers;
		
		getline(line, temp, ',');    
		auto bond = products->GetData(temp);
		
		for(int i=0;i<10;++i){
			getline(line, temp, ',');
			auto price = StringToPrice(temp);
			getline(line, temp, ',');
			auto quantity = stol(temp);
			getline(line, temp, ',');
			auto side = temp;
			if(i<5){
				bids.push_back(Order(price,quantity,BID));
			}
			else{
				offers.push_back(Order(price,quantity,OFFER));
			}
		}
		
		OrderBook<Bond> orderbook(bond, bids, offers);
		bmds->OnMessage(orderbook);
	}
}


#endif
