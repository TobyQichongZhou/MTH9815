/**
 * datageneratormarketdata.hpp
 * Generate Market Data
 *
 * @author Qichong Zhou
 */
#ifndef DATA_GENERATOR_MARKET_DATA_HPP
#define DATA_GENERATOR_MARKET_DATA_HPP

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "bondinfo.h"

using namespace std;

/**
 * Market Data Generator to generate market data
 */
class MarketdataGenerator {
public:
	// ctor
	MarketdataGenerator();

    // method to build data
	void generate(long N);
};

MarketdataGenerator::MarketdataGenerator() {
}

void MarketdataGenerator::generate(long N) {
	ofstream output;
	output.open("marketdata.txt");
	
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
		
		output<<cusip<<",";
        int spread;
        int mid_delta;
        mid_delta = 512 - abs(count[j] % 1024 - 512) + 256;
        spread = count[j] % 4 + 1;
		for(int k=0;k<5;++k){
            int p_ = mid_delta - spread - (k%5);
			int a=98 + p_/256;
			int b=(p_%256)/8;
			int c=p_%8;
			
			string A=to_string(a);
			string B=to_string(b);
			string C=to_string(c);
			if(b<10)B="0"+B;
			if(c==4)C="+";
			string price=A+"-"+B+C;
			
			string quantity=to_string((k%5+1)*1000000);
			
			string side="BID";
			
			output<<price<<","<<quantity<<","<<side<<",";
		}
		for(int k=0;k<5;++k){
			int p_ = mid_delta + spread + (k%5);
			int a=98 + p_/256;
			int b=(p_%256)/8;
			int c=p_%8;
			
			string A=to_string(a);
			string B=to_string(b);
			string C=to_string(c);
			if(b<10)B="0"+B;
			if(c==4)C="+";
			string price=A+"-"+B+C;
			
			string quantity=to_string((k%5+1)*1000000);
			
			string side="OFFER";
			
			output<<price<<","<<quantity<<","<<side<<",";
		}
		
		output<<endl;
	}
	output.close();
}


#endif
