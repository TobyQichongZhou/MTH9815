/**
 * datageneratorpricedata.hpp
 * Generate Price Data
 *
 * @author Qichong Zhou
 */
#ifndef DATA_GENERATOR_PRICE_DATA_HPP
#define DATA_GENERATOR_PRICE_DATA_HPP

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "bondinfo.h"

using namespace std;

/**
 * Price Data Generator to generate price data
 */
class PricedataGenerator {
public:
	// ctor
	PricedataGenerator();

    // method to build data
	void generate(long N);
};

PricedataGenerator::PricedataGenerator() {
}

void PricedataGenerator::generate(long N) {
	ofstream output;
	output.open("prices.txt");
	
	// record every product's data number, each should equal to N at end
	vector<long> count={-1,-1,-1,-1,-1,-1,-1};
	
	for(long i=0;i<7*N;i++){
		int j=rand()%7;
		// if jth bond already has n data
		while(count[j]==N-1){
			j=rand()%7;
		}
		string cusip=bondCusip[j];
		++count[j];
		
        int price_;
        price_ = 512 - abs(count[j] % 1024 - 512) + 256;
        int a=98 + price_/256;
        int b=(price_%256)/8;
        int c=price_%8;

        string A=to_string(a);
		string B=to_string(b);
		string C=to_string(c);
		if(b<10)B="0"+B;
		if(c==4)C="+";
		string price=A+"-"+B+C;


        string spread;
        switch (count[j] % 4 + 1)
        {
        case 1: spread = "0-001";break;
        case 2: spread = "0-002";break;
        case 3: spread = "0-003";break;
        case 4: spread = "0-00+";break;
        }
		output << cusip << "," << price << "," << spread << endl;
	}
	output.close();
}


#endif
