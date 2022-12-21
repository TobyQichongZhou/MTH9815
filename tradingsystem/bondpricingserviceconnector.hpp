/**
 * bondpricingserviceconnector.hpp
 * Fetches outside pricing data feeding into BondPricingService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_PRICING_SERVICE_CONNECTOR_HPP
#define BOND_PRICING_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondpricingservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Pricing Service Connector fecthes pricing data.
 */
class BondPricingServiceConnector: public Connector<Price<Bond> > {
private:
    BondPricingService* bps;
    BondProductService* products;

	// transform a string to price
	double StringToPrice(string& s);
public:
	// ctor
	BondPricingServiceConnector(BondPricingService* _bps,BondProductService* _products);

    //override all virtual functions
	virtual void Subscribe() override;
	virtual void Publish(Price<Bond>& data) override {};
};

double BondPricingServiceConnector::StringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondPricingServiceConnector::BondPricingServiceConnector(BondPricingService* _bps,BondProductService* _products) {
	bps = _bps;
	products = _products;
}

void BondPricingServiceConnector::Subscribe() {
	ifstream input;
	input.open("prices.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		getline(line, temp, ',');    
		auto bond = products->GetData(temp);
		getline(line, temp, ',');
		auto price = StringToPrice(temp);
		getline(line, temp, ',');
		auto spread = StringToPrice(temp);

		Price<Bond> priceData(bond, price, spread);

		bps->OnMessage(priceData);
	}
}


#endif
