/*
 * =====================================================================================
 *
 *       Filename:  rtlobject_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 07:08:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#include "common.h"
#include "rtlobject.hpp"
#include "clkobject.hpp"
//#include "rtlloop.h"

using namespace std;


struct AlwaysModule{
	//input 
	RtlObjectPtr B;
	RtlObjectPtr reset;	
	//output
	RtlObject A;
	RtlObject C;

	void func()
	{
		if(reset->getVal()){
			A=false;
			C=false;
		}
		else{
			A = B;
			if(B->getVal())	
				C=A;
		}
	}

	AlwaysModule(ClkObject& clk):
		A(string("test_a")),
		C(string("test_c"))
	{
		clk.addPosLoad(boost::bind(&AlwaysModule::func,this));
	}
};

//struct AssignModule{
//	AssignModule(){
//		A.addLoad(boost::bind(AssignModule::func,this));
//		B.addLoad(boost::bind(AssignModule::func,this));
//	}
//	//output
//	RtlObject D;
//	//input
//	RtlObjectPtr A;
//	RtlObjectPtr B;
//
//	void func()
//	{
//		D=A&(~B);
//	}
//};

int main(int argc,char** argv)
{
	int step=0;

	ClkObject clk(string("test_clk"),100);
	AlwaysModule md(clk);
	RtlObjectPtr B(new RtlObject("test_b"));
	RtlObjectPtr reset(new RtlObject("test_reset"));
	md.B=B;
	md.reset=reset;
	clk.setReset(reset,Neg);
	*reset = true;
	(*B)=true;

	/*loop*/
	while(1){
		step++;
		if(step==100)
			*(md.reset)=false;
		clk.update(step);
		if(0==(step%100)){
			std::cout<<"step: "<<step<<std::endl;
			std::cout<<"B: "<<B->getVal()<<std::endl;
			std::cout<<"reset: "<<reset->getVal()<<std::endl;
			std::cout<<"A: "<<md.A.getVal()<<std::endl;
			std::cout<<"C: "<<md.C.getVal()<<std::endl;
		}
	}
}

