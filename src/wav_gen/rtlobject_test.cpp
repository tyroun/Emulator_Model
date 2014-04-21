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
#include "rtlobject.h"
#include "rtlloop.h"

using namespace std;
typedef boost::shared_ptr<RtlObject> RtlObjectPtr;

struct AlwaysModule{
	AlwaysModule(ClkObject& clk){
		clk.addPosLoad(boost::bind(AlwaysModule::func,this));
	}
	//input 
	RtlObjectPtr B;
	RtlObjectPtr reset;	
	//output
	RtlObject A;
	RtlObject C;
		void func()
	{
		if(reset){
			A=0;
			B=0;
			C=0;
		}
		else{
			A = B;
			if(B)	
				C=A;
		}
	}
};

struct AssignModule{
	AssignModule(){
		A.addLoad(boost::bind(AssignModule::func,this));
		B.addLoad(boost::bind(AssignModule::func,this));
	}
	//output
	RtlObject D;
	//input
	RtlObjectPtr A;
	RtlObjectPtr B;

	void func()
	{
		D=A&(~B);
	}
};

int main(int argc,char** argv)
{
	int step=0;

	ClkObject clk(string("test_clk"),100);
	AlwaysModule md;
	RtlObject B("test_b",1);
	RtlObject reset("test_reset",1);
	md.B=&B;



	/*loop*/
	while(1){
		step++;
		if(step==100)
			md.reset=0;
		clk.update(step);
	}
}

