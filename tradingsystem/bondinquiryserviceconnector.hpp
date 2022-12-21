/**BondInquiryService
 * bondinquiryserviceconnector.hpp
 * Fetches outside inquiry data feeding into BondInquiryService.
 *
 * @author Qichong Zhou
 */

#ifndef BOND_INQUIRY_SERVICE_CONNECTOR_HPP
#define BOND_INQUIRY_SERVICE_CONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "bondinquiryservice.hpp"
#include "bondproductservice.hpp"


/**
 * Bond Inquiry Service Connector fecthes inquiry data.
 */
class BondInquiryServiceConnector: public Connector<Inquiry<Bond> > {
private:
    BondInquiryService* bis;
    BondProductService* products;

	// transform a string to price
	double StringToPrice(string& s);
public:
	// ctor
	BondInquiryServiceConnector(BondInquiryService* _bis,BondProductService* _products);

    //override all virtual functions
	virtual void Subscribe() override;
	virtual void Publish(Inquiry<Bond>& data) override {};
};

double BondInquiryServiceConnector::StringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondInquiryServiceConnector::BondInquiryServiceConnector(BondInquiryService* _bis,BondProductService* _products) {
	bis = _bis;
	products = _products;
}

void BondInquiryServiceConnector::Subscribe() {
	ifstream input;
	input.open("inquiries.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		
		getline(line, temp, ',');   
		string inquiry_ID = temp;
		
		getline(line, temp, ',');
		auto bond = products->GetData(temp);
		
		getline(line, temp, ',');
		Side side = (temp=="BUY" ? BUY:SELL);
            
		getline(line, temp, ',');
		long quantity = stol(temp);
		
		getline(line, temp, ',');
		double quote = StringToPrice(temp);
            
		getline(line, temp, ',');
		InquiryState state_ = RECEIVED;
		
		Inquiry<Bond> inquiry(inquiry_ID, bond, side, quantity, quote, state_);
		bis -> OnMessage(inquiry);
	}
}


#endif
