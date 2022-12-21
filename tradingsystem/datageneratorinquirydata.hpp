/**price
 * datageneratorinquirydata.hpp
 * Generate Inquiry Data
 *
 * @author Qichong Zhou
 */
#ifndef DATA_GENERATOR_INQUIRY_DATA_HPP
#define DATA_GENERATOR_INQUIRY_DATA_HPP

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "bondinfo.h"

using namespace std;

/**
 * Inquiry Data Generator to generate inquiry data
 */
class InquirydataGenerator {

    string Format(string v, int width, char c);
public:
	// ctor
	InquirydataGenerator();

    // method to build data
	void generate(long N);
};

string InquirydataGenerator::Format(string v, int width, char c){
	string result;
	std::stringstream inter;
	inter << std::setw(width) << std::setfill(c) << v;
	inter >> result;
	return result;
}

InquirydataGenerator::InquirydataGenerator() {
}

void InquirydataGenerator::generate(long N) {
	ofstream output;
	output.open("inquiries.txt");
	
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
		
		auto id=Format(to_string(i+1),8,'0');
		output<<id<<","<<cusip<<",";
		output<<(rand()%2==0?"BUY":"SELL")<<",";
		output<<to_string((rand()%5+1)*1000000)<<",";
		
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
		
		output<<"QUOTED"<<",";
		output <<endl;
	}
	output.close();
}


#endif
