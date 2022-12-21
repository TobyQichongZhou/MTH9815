#include <iostream>
#include "datageneratorinquirydata.hpp"
#include "datageneratormarketdata.hpp"
#include "datageneratorpricedata.hpp"
#include "datageneratortradedata.hpp"
#include "algoexecution.hpp"
#include "algostream.hpp"
#include "bondalgoexecutionservice.hpp"
#include "bondalgoexecutionservicelistener.hpp"
#include "bondalgostreamingservice.hpp"
#include "bondalgostreamingservicelistener.hpp"
#include "bondexecutionservice.hpp"
#include "bondexecutionserviceconnector.hpp"
#include "bondexecutionservicelistener.hpp"
#include "bondhistoricaldataservice.hpp"
#include "bondhistoricaldataserviceconnector.hpp"
#include "bondhistoricaldataservicelistener.hpp"
#include "bondinfo.h"
#include "bondinquiryservice.hpp"
#include "bondinquiryserviceconnector.hpp"
#include "bondmarketdataservice.hpp"
#include "bondmarketdataserviceconnector.hpp"
#include "bondpositionservice.hpp"
#include "bondpositionservicelistener.hpp"
#include "bondpricingservice.hpp"
#include "bondpricingserviceconnector.hpp"
#include "bondproductservice.hpp"
#include "bondriskservice.hpp"
#include "bondriskservicelistener.hpp"
#include "bondstreamingservice.hpp"
#include "bondstreamingserviceconnector.hpp"
#include "bondstreamingservicelistener.hpp"
#include "bondtradebookingservice.hpp"
#include "bondtradebookingserviceconnector.hpp"
#include "bondtradebookingservicelistener.hpp"
#include "guiservice.hpp"
#include "guiserviceconnector.hpp"
#include "guiservicelistener.hpp"

int main(){

    // Generate Data
    PricedataGenerator pg = PricedataGenerator();
    MarketdataGenerator mg = MarketdataGenerator();
    TradedataGenerator tg = TradedataGenerator();
    InquirydataGenerator ig = InquirydataGenerator();

    pg.generate(1000000);
    mg.generate(1000000);
    tg.generate(10);
    ig.generate(10);





    vector<Bond> bonds;
    for(int i=0; i<bondCusip.size(); i++){
        bonds.push_back(Bond(bondCusip[i], CUSIP, "Treasury", bondCoupon[i], bondMaturity[i]));
    }

    BondProductService* bondproductservice = new BondProductService();
    for(int i=0; i<bondCusip.size(); i++){
        bondproductservice->AddBond(bonds[i]);
    }

    BondPricingService* bondpricingservice= new BondPricingService();
    BondPricingServiceConnector* bondpricingserviceconnector = new BondPricingServiceConnector(bondpricingservice, bondproductservice);

    BondAlgoStreamingService* bondalgostreamingservice = new BondAlgoStreamingService();
    BondAlgoStreamingServiceListener* bondalgostreamingservicelistener = new BondAlgoStreamingServiceListener(bondalgostreamingservice);

    bondpricingservice->AddListener(bondalgostreamingservicelistener);

    BondStreamingServiceConnector* bondstreamingserviceconnector = new BondStreamingServiceConnector();
    BondStreamingService* bondstreamingservice = new BondStreamingService(bondstreamingserviceconnector);
    BondStreamingServiceListener* bondstreamingservicelistener = new BondStreamingServiceListener(bondstreamingservice);

    bondalgostreamingservice->AddListener(bondstreamingservicelistener);




    BondMarketDataService* bondmarketdataservice = new BondMarketDataService();
    BondMarketDataServiceConnector* bondmarketdataserviceconnector = new BondMarketDataServiceConnector(bondmarketdataservice, bondproductservice);

    BondAlgoExecutionService * bondalgoexecutionservice = new BondAlgoExecutionService();
    BondAlgoExecutionServiceListener* bondalgoexecutionservicelistener = new BondAlgoExecutionServiceListener(bondalgoexecutionservice);

    bondmarketdataservice->AddListener(bondalgoexecutionservicelistener);

    BondExecutionServiceConnector* bondexecutionserviceconnector = new BondExecutionServiceConnector();
    BondExecutionService* bondexecutionservice = new BondExecutionService(bondexecutionserviceconnector);
    BondExecutionServiceListener* bondexecutionservicelistener = new BondExecutionServiceListener(bondexecutionservice);

    bondalgoexecutionservice->AddListener(bondexecutionservicelistener);




    BondTradeBookingService* bondtradebookingservice = new BondTradeBookingService();
    BondTradeBookingServiceConnector* bondtradebookingserviceconnector = new BondTradeBookingServiceConnector(bondtradebookingservice, bondproductservice);
    BondTradeBookingServiceListener* bondtradebookingservicelistener = new BondTradeBookingServiceListener(bondtradebookingservice);

    bondexecutionservice->AddListener(bondtradebookingservicelistener);

    BondPositionService* bondpositionservice = new BondPositionService();
    BondPositionServiceListener* bondpositionservicelistener = new BondPositionServiceListener(bondpositionservice);

    bondtradebookingservice->AddListener(bondpositionservicelistener);

    BondRiskService* bondriskservice = new BondRiskService();
    BondRiskServiceListener* bondriskservicelistener = new BondRiskServiceListener(bondriskservice);

    bondpositionservice->AddListener(bondriskservicelistener);




    BondInquiryService* bondinquiryservice = new BondInquiryService();
    BondInquiryServiceConnector* bondinquiryserviceconnector = new BondInquiryServiceConnector(bondinquiryservice, bondproductservice);

    GUIServiceConnector* guiserviceconnector = new GUIServiceConnector();
    GUIService* guiservice = new GUIService(guiserviceconnector);
    GUIServiceListener* guiservicelistener = new GUIServiceListener(guiservice);

    bondpricingservice->AddListener(guiservicelistener);




    BondHistoricalPositionServiceConnector* bondhistoricalpositionserviceconnector = new BondHistoricalPositionServiceConnector();
    BondHistoricalPositionService* bondhistoricalpositionservice = new BondHistoricalPositionService(bondhistoricalpositionserviceconnector);
    BondHistoricalPositionServiceListener* bondhistoricalpositionservicelistener = new BondHistoricalPositionServiceListener(bondhistoricalpositionservice);
    bondpositionservice->AddListener(bondhistoricalpositionservicelistener);

    BondHistoricalRiskServiceConnector* bondhistoricalriskserviceconnector = new BondHistoricalRiskServiceConnector();
    BondHistoricalRiskService* bondhistoricalriskservice = new BondHistoricalRiskService(bondhistoricalriskserviceconnector);
    BondHistoricalRiskServiceListener* bondhistoricalriskservicelistener = new BondHistoricalRiskServiceListener(bondhistoricalriskservice);
    bondriskservice->AddListener(bondhistoricalriskservicelistener);

    BondHistoricalExecutionServiceConnector* bondhistoricalexecutionserviceconnector = new BondHistoricalExecutionServiceConnector();
    BondHistoricalExecutionService* bondhistoricalexecutionservice = new BondHistoricalExecutionService(bondhistoricalexecutionserviceconnector);
    BondHistoricalExecutionServiceListener* bondhistoricalexecutionservicelistener = new BondHistoricalExecutionServiceListener(bondhistoricalexecutionservice);
    bondexecutionservice->AddListener(bondhistoricalexecutionservicelistener);

    BondHistoricalStreamingServiceConnector* bondhistoricalstreamingserviceconnector = new BondHistoricalStreamingServiceConnector();
    BondHistoricalStreamingService* bondhistoricalstreamingservice = new BondHistoricalStreamingService(bondhistoricalstreamingserviceconnector);
    BondHistoricalStreamingServiceListener* bondhistoricalstreamingservicelistener = new BondHistoricalStreamingServiceListener(bondhistoricalstreamingservice);
    bondstreamingservice->AddListener(bondhistoricalstreamingservicelistener);

    BondHistoricalInquiryServiceConnector* bondhistoricalinquiryserviceconnector = new BondHistoricalInquiryServiceConnector();
    BondHistoricalInquiryService* bondhistoricalinquiryservice = new BondHistoricalInquiryService(bondhistoricalinquiryserviceconnector);
    BondHistoricalInquiryServiceListener* bondhistoricalinquiryservicelistener = new BondHistoricalInquiryServiceListener(bondhistoricalinquiryservice);
    bondinquiryservice->AddListener(bondhistoricalinquiryservicelistener);


    bondpricingserviceconnector->Subscribe();
    bondmarketdataserviceconnector->Subscribe();
    bondtradebookingserviceconnector->Subscribe();
    bondinquiryserviceconnector->Subscribe();

    return 0;

}