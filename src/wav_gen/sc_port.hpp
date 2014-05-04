/*
 * =====================================================================================
 *
 *       Filename:  sc_port.hpp
 *
 *    Description: wrapper of RtlobjectPtr, make use operator easy 
 *
 *        Version:  1.0
 *        Created:  28/04/14 09:06:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __sc_port_H__
#define __sc_port_H__
#include "rtlobject.hpp"
#include <iostream>
#include <boost/make_shared.hpp>

template <typename T> 
class sc_port  
{
public:
	typedef boost::shared_ptr<RtlObject<T> > RtlObjectPtr;  
	sc_port(sc_port& port)
	{
		p_=port.getPtr();
	}	

	sc_port(std::string name){
	//	p_=boost::make_shared<RtlObject<T> >(name);
		p_=RtlObjectPtr(new RtlObject<T>(name)); 
	}

	sc_port(){
	}	

	void bind(sc_port port){
		if(!p_){
			p_=port.getPtr();
		}
		else{
			std::cout<<("bind error\n")<<std::endl;
		}
	}

	RtlObjectPtr getPtr(){
		return p_;
	}
	
	T getVal(){
		return p_->val_;
	}

	void setSensitive(Module *md){
		p_->setSensitive(md);	
	}
	//operation
	//Agorithm start
	void operator=(T val){
		if(p_->val_!=val){
			p_->val_=val;
			Loop::getInstance()->addEvent(p_->moduleList);
		}
	}

	void operator=(sc_port<T>& port){
		RtlObjectPtr p=port.getPtr();
		if(p_->val_!=p->val_){
			p_->val_=p->val_;
			Loop::getInstance()->addEvent(p_->moduleList);
		}
	}

	T operator+ (sc_port<T>& port){
		RtlObjectPtr p=port.getPtr();
		return p_->val_+p->val_;
	}	
	
	T operator- (sc_port<T>& port){
		RtlObjectPtr p=port.getPtr();
		return p_->val_-p->val_;
	}	
	
	T operator ~ (){
		return ~(p_->val_);
	}	

	bool operator == (const sc_port<T>& port){
		RtlObjectPtr p=port.getPtr();
		return p_->val_==p->val_;
	}
	bool operator != (const sc_port<T>& port){
		RtlObjectPtr p=port.getPtr();
		return p_->val_!=p->val_;
	}
	//Agorithm end 	

private:
	RtlObjectPtr p_;
};

#define sc_input sc_port 
#define sc_output sc_port 

#endif

