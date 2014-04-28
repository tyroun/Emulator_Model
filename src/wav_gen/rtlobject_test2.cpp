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
#include "module.hpp"
//#include "clkobject.hpp"
#include "loop.hpp"

using namespace std;

class MyModule : public Module{
public:
	sc_input<bool>	A;
	sc_input<bool>	B;
	sc_output<bool>	C;
	sc_output<bool> D;

protected:
	void init(){
		C=sc_port("test_c");
		D=sc_port("test_d");
		sensitive(A);
		sensitive(B);
		sensitive(C);
	}

	void method(){
		C=A+B;
		if(C.getVal())		
			D=~C;
	}
};

void print_all(Module *md,unsigned long long step)
{
	std::cout<<"step= "<<step<<std::endl;
	std::cout<<"A= "<<md.A.getVal()<<std::endl;
	std::cout<<"B= "<<md.B.getVal()<<std::endl;
	std::cout<<"C= "<<md.C.getVal()<<std::endl;
	std::cout<<"D= "<<md.D.getVal()<<std::endl;
}

void loop_callback(unsigned long long step)
{
	Module *md=Loop::getInstance()->moduleList_[String("test_module")];	
	switch(step){
	case 0:
		printf_all(md,step);
		break;
	case 1:
		A=true;
		B=false;
		break;	
	case 2:
		printf_all(md,step);
		break;
	case 3:
		A=false;
		B=false;
		break;	
	case 4:
		printf_all(md,step);
		break;
	case 5:
		exit(0);
	}	
}

int main(int argc,char** argv)
{
	Loop *loop=Loop::getInstance();
	loop->setCallback(boost::bind(loop_callback,_1)(step));
	sc_port<bool> A("test_a");
	sc_port<bool> B("test_b");
	A=false;
	B=false;
	MyModule md("test_module");	
	md.A.bind(A);
	md.B.bind(B);
	loop->eventLoop();	
}

