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

	MyModule(std::string name,Module* parent=0):
		Module(name,parent),
		C(std::string("test_c")),
		D(std::string("test_d"))
		//iD(std::string("test_d"))
	{

		sensitive(A);
		sensitive(B);
		sensitive(C);
	}

protected:

	void method(){
		C=A+B;
		if(C.getVal())		
			D=~C;
	}
};

void print_all(Module *md,unsigned long long step)
{
	MyModule *my_md=static_cast<MyModule*>(md);
	std::cout<<"step= "<<step<<std::endl;
	std::cout<<"A= "<<my_md->A.getVal()<<std::endl;
	std::cout<<"B= "<<my_md->B.getVal()<<std::endl;
	std::cout<<"C= "<<my_md->C.getVal()<<std::endl;
	std::cout<<"D= "<<my_md->D.getVal()<<std::endl;
}

void loop_callback(unsigned long long step)
{
	Module *md=Loop::getInstance()->moduleList_[String("test_module")];
	MyModule *my_md=static_cast<MyModule*>(md);
	switch(step){
	case 0:
		print_all(md,step);
		break;
	case 1:
		my_md->A=true;
		my_md->B=false;
		break;	
	case 2:
		print_all(md,step);
		break;
	case 3:
		my_md->A=false;
		my_md->B=false;
		break;	
	case 4:
		print_all(md,step);
		break;
	case 5:
		exit(0);
	}	
}

int main(int argc,char** argv)
{
	Loop *loop=Loop::getInstance();
	loop->setCallback(boost::bind(loop_callback,_1));
	sc_port<bool> A(std::string("test_a"));
	sc_port<bool> B(std::string("test_b"));
	A=false;
	B=false;
	MyModule md(std::string("test_module"));	
	md.A.bind(A);
	md.B.bind(B);
	loop->eventLoop(10);	
}

