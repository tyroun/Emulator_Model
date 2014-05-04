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
#include "common.h"
#include <map>
#include <list>
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

	void addEvent(std::list<Module*> &moduleList);
	void eventLoop(unsigned long long step); //main loop
	void setCallback(loopCallback fn){
		fn_=fn;
	}
	std::map<std::string,Module*> moduleList_;
  private:
	Loop():
		step_(0)
	{	
		eventList_.clear();
	}

	void init();
	std::list<Module*> eventList_;
	unsigned long long step_;
	loopCallback fn_;
};


#endif

