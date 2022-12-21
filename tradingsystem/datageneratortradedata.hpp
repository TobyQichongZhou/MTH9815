/**
 * datageneratortradedata.hpp
 * Generate Trade Data
 *
 * @author Qichong Zhou
 */
#ifndef DATA_GENERATOR_TRADE_DATA_HPP
#define DATA_GENERATOR_TRADE_DATA_HPP

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "bondinfo.h"

using namespace std;

/**
 * Trade Data Generator to generate trade data
 */
class TradedataGenerator {
public:
	// ctor
	TradedataGenerator();

    // method to build data
	void generate(long N);
};

TradedataGenerator::TradedataGenerator() {
}

void TradedataGenerator::generate(long N) {
	ofstream output;
	output.open("trades.txt");
	
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
		
		j=rand()%4;
		string tradeID;
		switch(j){
			case 0:tradeID="Alice";break;
			case 1:tradeID="Bob";break;
			case 2:tradeID="Carol";break;
			case 3:tradeID="Eric";break;
		}
		output<<cusip<<","<<tradeID<<",";
		
		int a=rand()%2+99;
		int b=rand()%32;
		int c=rand()%8;		
		string A=to_string(a);
		string B=to_string(b);
		string C=to_string(c);
		if(b<10)B="0"+B;
		if(c==4)C="+";
		string price=A+"-"+B+C;
		output<<price<<",";

        string book;
        switch (rand()%3)
        {
        case 0: book = "TRSY1";break;
        case 1: book = "TRSY2";break;
        case 2: book = "TRSY3";break;
        }
		
		output<<book<<",";
		output<<to_string((rand()%5+1)*1000000)<<",";
		output<<(rand()%2==0?"BUY":"SELL");
		
		output <<endl;
	}
	output.close();
}


#endif
