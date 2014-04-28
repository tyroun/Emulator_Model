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
#include <map>

typedef boost::function<void()> moduleCallback;


class Module{
public:
	Module(std::string name,module* parent=0):
		name_(name),
		parent_(parent)
	{
		if(!parent){
			//top module
			Loop::getInstance()->moduleList_.insert(\
					make_pair(name,this));	

		}
		init();	//all sun must call this init instead of consturt function
	}

	

	void sensitive(sc_port& obj){
		obj.setSensitive(this);	
	}

protected:
	virtual void method()=0;
	virtual void init()=0;

private:	
	String name_;
	Module* parent_;
};

#endif

