/*
 * =====================================================================================
 *
 *       Filename:  loop.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/04/14 02:50:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tyroun (), 
 *   Organization:  Verisilicon
 *
 * =====================================================================================
 */
#ifndef __loop_H__
#define __loop_H__
#include "rtlobject.hpp"
#include "common.h"
#include <map>
#include <boost/function.hpp>

class Module;
typedef boost::function<void(unsigned long long)> loopCallback;

class Loop{
  public:
	static Loop* getInstance(){
		static Loop* instance=0;
		if(!instance){
			instance = new Loop();
		}
		return instance;
	}

	void addEvent(RtlObjectPtr obj){
		if(obj->isSensitive())
			eventList.push_back(obj);
	}
	
	void eventLoop(void) //main loop
	{
		init();
		RtlObjectPtr objPtr;
		while(1){
			step++;
			fn_(step);
			//do method	
			while(!eventList.empty()){
				objPtr=eventList.front();
				objPtr->update();		
				eventlist.pop_front();
			}
		}
	}

	void setCallback(loopCallback fn){
		fn_=fn;
	}

	std::map<std::string,Module*> moduleList_;
  private:
	Loop():
		step(0)
	{}

	void init(){
		std::map<std::string,Module*>::iterator it;
		for(it=moduleList_.begin();it!=moduleList_.end();++it){
			if((it->second)->method)
				it->second->method();
		}
	}

	std::list<RtlObjectPtr> eventList;
	unsigned long long step;
	loopCallback fn_;
};


#endif

