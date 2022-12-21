/**
 * bondinquiryservice.hppPOSITION
 * Manages inquiry information
 *
 * @author Qichong Zhou
 */
#ifndef BOND_INQUIRY_SERVICE_HPP
#define BOND_INQUIRY_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"
#include "inquiryservice.hpp"
#include "bondinfo.h"

/**
 * Inquiry Service which handles inquiries
 * Keyed on product identifier.
 */
class BondInquiryService: public InquiryService<Bond>{

private:
    map<string, Inquiry<Bond> > inquiriesMap;
    vector<ServiceListener<Inquiry<Bond>> *> listenersList;

public:
    //ctor
    BondInquiryService();

    //override all virtual functions
    virtual Inquiry<Bond>& GetData(string key) override;
    virtual void OnMessage(Inquiry<Bond> &inquiry) override;
    virtual void AddListener(ServiceListener<Inquiry<Bond>> * listener) override;
    virtual const vector< ServiceListener<Inquiry<Bond>> *>& GetListeners() const override;
    virtual void SendQuote(const string& inquiryId, double price) override{} 
    virtual void RejectInquiry(const string &inquiryId) override{}
};


BondInquiryService::BondInquiryService() {
    inquiriesMap=map<string, Inquiry<Bond>>();
    listenersList=vector<ServiceListener<Inquiry<Bond>> * >();
}

Inquiry<Bond>& BondInquiryService::GetData(string key) {
    return inquiriesMap[key];
}

void BondInquiryService::OnMessage(Inquiry<Bond> &inquiry) {
    inquiry.SetState(inquiry.GetPrice(), DONE);
    inquiriesMap.insert(pair<string, Inquiry<Bond>>(inquiry.GetInquiryId(), inquiry));
    for (auto& l:listenersList) {l->ProcessAdd(inquiry);}
}

void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond>> * listener) {
    listenersList.push_back(listener);
}

const vector< ServiceListener<Inquiry<Bond>> *>& BondInquiryService::GetListeners() const{
    return listenersList;
}

#endif
