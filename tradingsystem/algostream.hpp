/**
 * algostream.hpp
 * Defines algostream class that contains the algo for price stream this trading system
 *
 * @author Qichong Zhou
 */
#ifndef ALGO_STREAM_HPP
#define ALGO_STREAM_HPP

#include <string>
#include <vector>
#include <map>
#include <random>
#include <time.h>
#include "products.hpp"
#include "pricingservice.hpp"
#include "streamingservice.hpp"

/**
 * AlgoStream class: algo for bond pricing
 */
class AlgoStream{

private:
    PriceStream<Bond> pricestream;

    static std::default_random_engine eng;
    static std::uniform_int_distribution<long> gnt;

    long GetRandomQuantity();

public:
    //ctor
    AlgoStream(PriceStream<Bond> _pricestream): pricestream(_pricestream) {}
    AlgoStream(){}

    PriceStream<Bond> GetPriceStream() const {
        return pricestream;
    }
    void UpdatePriceStream(Price<Bond> &price);
};

std::default_random_engine AlgoStream::eng = std::default_random_engine(time(NULL));
std::uniform_int_distribution<long> AlgoStream::gnt = std::uniform_int_distribution<long>(1000000,2000000);


long AlgoStream::GetRandomQuantity(){
    return gnt(eng);
}


void AlgoStream::UpdatePriceStream(Price<Bond> &price) {
    if (price.GetProduct().GetProductId()!=pricestream.GetProduct().GetProductId()) {return;}

    double bidp = price.GetMid() - price.GetBidOfferSpread() / 2.0;
    long bidvQ = GetRandomQuantity();
    auto bid = PriceStreamOrder(bidp, bidvQ, bidvQ*2, BID);

    double offerp = price.GetMid() + price.GetBidOfferSpread() / 2.0;
    long offervQ = GetRandomQuantity();
    auto offer = PriceStreamOrder(offerp, offervQ, bidvQ*2.0, OFFER);
    
    pricestream = PriceStream<Bond>(price.GetProduct(), bid, offer);

}

#endif
