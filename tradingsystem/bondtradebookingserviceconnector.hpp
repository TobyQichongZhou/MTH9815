/**
 * bondtradebookingserviceconnector.hpp
 * Fetches outside trade data feeding into BondTradeBookingService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP
#define BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondtradebookingservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Trade Booking Service Connector fecthes trade data.
 */
class BondTradeBookingServiceConnector: public Connector<Trade<Bond> > {
private:
    BondTradeBookingService* btbs;
    BondProductService* products;

	// transform a string to price
	double StringToPrice(string& s);
public:
	// ctor
	BondTradeBookingServiceConnector(BondTradeBookingService* _btbs,BondProductService* _products);

    //override all virtual functions
	virtual void Subscribe() override;
	virtual void Publish(Trade<Bond>& data) override {};
};

double BondTradeBookingServiceConnector::StringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondTradeBookingServiceConnector::BondTradeBookingServiceConnector(BondTradeBookingService* _btbs,BondProductService* _products) {
	btbs = _btbs;
	products = _products;
}

void BondTradeBookingServiceConnector::Subscribe() {
    ifstream input;
	input.open("trades.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		getline(line, temp, ',');    
		auto bond = products->GetData(temp);
		
		getline(line, temp, ',');
		auto tradeID = temp;
		getline(line, temp, ',');
		auto price = StringToPrice(temp);
		getline(line, temp, ',');
		auto book = temp;
		getline(line, temp, ',');
		long quantity = stol(temp);
		getline(line, temp, ',');
		Side side=temp=="BUY"? BUY:SELL;		
		
		Trade<Bond> trade(bond,tradeID,price,book,quantity,side);
		btbs->BookTrade(trade);
	}
}


#endif
