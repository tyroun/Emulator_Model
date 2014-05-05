/*
 * =====================================================================================
 *
 *       Filename:  module.hpp
 *
 *    Description:  module is like assign module 
 *    		    signals in sensitive table drive func()
 *
 *        Version:  1.0
 *        Created:  24/04/14 11:23:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __module_H__
#define __module_H__
#include "common.h"
#include "rtlobject.hpp"
#include "sc_port.hpp"
#include <map>

typedef boost::function<void()> moduleCallback;


class Module{
public:
	Module(std::string& name,Module* parent=0):
		name_(name),
		parent_(parent)
	{
		if(!parent){
			//top module
			Loop::getInstance()->moduleMap_.insert(\
					make_pair(name,this));	

		}
	}

	
	template <typename T>
	void sensitive(sc_port<T>& obj){
		obj.setSensitive(this);	
	}

	virtual void method()=0;
	virtual void init()=0;

private:	
	String name_;
	Module* parent_;
};

#endif

