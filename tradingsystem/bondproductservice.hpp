/**
 * bongproductservice.hpp
 * Defines the data types and Service for bond internal prices.
 *
 * @author Qichong Zhou
 */
#ifndef BOND_PRODUCT_SERVICE_HPP
#define BOND_PRODUCT_SERVICE_HPP

#include <string>
#include <vector>
#include <map>
#include "soa.hpp"
#include "products.hpp"

/**
 * Bond Product Service manages infor of all bonds traded by the system.
 * Keyed on product identifier.
 */
class BondProductService: public Service<string, Bond>{

private:
    map<string, Bond > bondsMap;
    vector<ServiceListener<Bond> *> listenersList;

public:
    //ctor
    BondProductService(){
        bondsMap=map<string, Bond>();
        listenersList = vector<ServiceListener<Bond> *>();
    }


    void AddBond(Bond& _bond){
        bondsMap.insert(pair<string,Bond>(_bond.GetProductId(), _bond));
    }

    vector<Bond> GetBonds(string& _ticker){
        vector<Bond> ret;
        for (auto item=bondsMap.begin(); item!=bondsMap.end(); item++){
            if((item->second).GetTicker()==_ticker){ret.push_back(item->second);}
        }
        return ret;
    }

    //override all virtual functions
    virtual Bond& GetData(string key) override{
        return bondsMap[key];
    }

    virtual void OnMessage(Bond &data) override {};
    virtual void AddListener(ServiceListener<Bond> * listener) override {};
    virtual const vector< ServiceListener<Bond> *>& GetListeners() const override {return listenersList;};
};

#endif
