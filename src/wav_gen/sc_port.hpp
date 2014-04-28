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

template <typename T> 
class sc_port{
public:
	sc_port(RtlObjectPtr p){
		p_=p;
	}	
	sc_port(std::string name){
		p_=new RtlObject<T>(name);
	}

	sc_port(){
	}	

	void bind(sc_port port){
		if(p_.isNull()){
			p_=p;
		}
		else{
			printf("bind error\n");
		}
	}

	RtlObjectPtr getPtr(){
		return p_;
	}
	
	T getVal(){
		return p_->val_;
	}

	void setSensitive(){
		
	}
	//operation
	//Agorithm start
	void operator=(T val){
		if(p_->val_!=val){
			p_->val_=val;
			Loop::getInstance()->addEvent(p_);
		}
	}

	void operator=(sc_port& port){
		RtlObjectPtr p=port.getPtr();
		if(p_->val_!=p->val_){
			val_=p->val_;
			Loop::getInstance()->addEvent(p_);
		}
	}

	T operator+ (sc_port& port){
		RtlObjectPtr p=port.getPtr();
		return val_+p->val_;
	}	
	
	T operator- (sc_port& port){
		RtlObjectPtr p=port.getPtr();
		return val_-p->val_;
	}	
	
	T operator ~ (){
		return ~(p_->val_);
	}	

	bool operator == (const sc_port& port){
		RtlObjectPtr p=port.getPtr();
		return val_==p->val_;
	}
	bool operator != (const sc_port& port){
		RtlObjectPtr p=port.getPtr();
		return val_!=p->val_;

	//Agorithm end 	

private:
	RtlObjectPtr p_;
};

typedef sc_input sc_port;
typedef sc_output sc_port;

#endif

